/*
 * lexer.c
 *
 *  Created on: Jan 24, 2019
 *  Author: alexl
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "errors.h"
#include "types/m_string.h"

// static functions
static int checkForComments(FILE *, Lexer *);
static Lexeme *lexNumber(FILE *, Lexer *);
static Lexeme *lexVariableOrKeyword(FILE *, Lexer *);
static Lexeme *lexString(FILE *, Lexer *);
// helper functions
static char readChar(FILE *);
static void skipWhiteSpace(FILE *, Lexer *);
static void *allocate(size_t);
static void *reallocate(void *s, size_t size);

struct lexer {
  FILE *fp;
  int currentLine;
};

Lexer *newLexer(FILE *f) {
  Lexer *p = malloc(sizeof(Lexer));
  if (p == 0) {
    fprintf(stderr,"out of memory\n"); exit(1);
  }
  p->fp = f;
  p->currentLine = 1;
  return p;
}

/** Returns a single lexeme based on where the file pointer
  * is pointing.
  * Skips all whitespace and comments.
  * Throws an UNKNOWN error if unknown token encountered
  */
Lexeme *lex(Lexer *lexer) {
  FILE *fp = lexer->fp;
  char ch;
  int comments = 0;
  skipWhiteSpace(fp,lexer);
  // read a character at a time
  ch = readChar(fp);
  if(ch == EOF) return newLexeme(ENDofINPUT, lexer->currentLine);
  switch(ch) {
    // single character tokens
    case '[': return newLexeme(OPEN_BRACKET, lexer->currentLine);
    case ']': return newLexeme(CLOSE_BRACKET, lexer->currentLine);
    case '(': return newLexeme(OPEN_PAREN, lexer->currentLine);
    case ')': return newLexeme(CLOSE_PAREN, lexer->currentLine);
    case ',': return newLexeme(COMMA, lexer->currentLine);
    case ':': return newLexeme(COLON, lexer->currentLine);
    case '.': return newLexeme(DOT, lexer->currentLine);
    case '+': return newLexeme(PLUS, lexer->currentLine);
    case '=': return newLexeme(ASSIGN, lexer->currentLine);
    case '-': return newLexeme(MINUS, lexer->currentLine);
    case '*': return newLexeme(TIMES, lexer->currentLine);
    case '<': return newLexeme(LESS_THAN, lexer->currentLine);
    case '>': return newLexeme(GREATER_THAN, lexer->currentLine);
    case '&': return newLexeme(AND, lexer->currentLine);
    case '|': return newLexeme(OR, lexer->currentLine);
    case '/':
      comments = checkForComments(fp,lexer);
      if(!comments)
        return newLexeme(DIVIDE, lexer->currentLine);
      else {
        // continue lexing
        skipWhiteSpace(fp,lexer);
        return lex(lexer);
      }
    default:
      // multi-character tokens
      // (numbers, variables/keywords, and strings)
      if(isdigit(ch)) {
        ungetc(ch,fp); // built-in pushback
        return lexNumber(fp,lexer);
      }
      else if(isalpha(ch)) {
        ungetc(ch,fp);
        return lexVariableOrKeyword(fp,lexer);
      }
      else if(ch == '\"' || ch == '\'') {
        return lexString(fp,lexer);
      }
      else {
        ErrorLexeme(newLexemeString(
          UNKNOWN, &ch, lexer->currentLine));
      }
    }
}

// static functions

/** Checks for signle-line and multi-line comments
  * of the form // or /*.
  * If it finds a comment, it ignores following
  * characters until the comment section has been
  * left.
  */
static int checkForComments(FILE *fp, Lexer *lexer) {
  int comments = 0;
  char ch;
  ch = readChar(fp);
  if(ch == '/') { // single-line comment
    comments = 1;
    // ignore everything until \n
    while(ch != '\n') {
      ch = readChar(fp);
    }
    lexer->currentLine++;
  }
  else if(ch == '*') { // multi-line comment
    comments = 1;
    // ignore everything until */
    while(1) {
      ch = readChar(fp);
      if(ch == '*') {
        ch = readChar(fp);
        if(ch != '/')
          ungetc(ch,fp);
        else
          return comments;
      }
      else if(ch == '\n') {
        lexer->currentLine++;
      }
    }
  }
  else
    ungetc(ch,fp);

  return comments;
}

/** reads a token in as a number (integer or real)
  * and returns a lexeme corresponding to that number.
  *
  * If it gets a bad number, it throws an error and exits.
  */
static Lexeme *lexNumber(FILE *fp, Lexer *lexer) {
  int real = 0;
  char *buffer;
  char ch;
  int size = 80, index = 0;

  buffer = allocate(size);

  ch = readChar(fp);
  while(ch != EOF && (isdigit(ch) || ch == '.')) {
    // check if needs to be reallocated (no explicit limits)
    if (index > size - 2) {
      ++size;
      buffer = reallocate(buffer,size);
    }
    buffer[index] = ch;
    ++index;
    if(ch == '.' && real) // 8..7234
      ErrorLexeme(newLexemeString(BAD_NUMBER, buffer, lexer->currentLine));
    if(ch == '.') // must be a real
      real = 1;
    ch = readChar(fp);
  }
  ungetc(ch, fp);
  if(real)
    return newLexemeReal(atof(buffer), lexer->currentLine);
  else
    return newLexemeInt(atoi(buffer), lexer->currentLine);
}

/** Reads a token in as either a variable(identifier) or a keyword
  * It then returns that id/keyord as a lexeme
  */
static Lexeme *lexVariableOrKeyword(FILE *fp, Lexer *lexer) {
  char ch;
  char *buffer;
  int size = 512, index = 0;

  buffer = allocate(size);

  ch = readChar(fp);
  while(isalpha(ch) || isdigit(ch)) {
    // check if needs to be reallocated (no explicit limits)
    if (index > size - 2) {
      ++size;
      buffer = reallocate(buffer,size);
    }
    buffer[index] = ch;
    ++index;
    ch = readChar(fp);
  }

  // push back character bc might be punctuation
  ungetc(ch,fp);
  int curr_line = lexer->currentLine;
  // token either variable or keyword
  // test all keywords
  if(strcmp(buffer,"if") == 0) return newLexeme(IF, curr_line);
  else if(strcmp(buffer,"else") == 0) return newLexeme(ELSE, curr_line);
  else if(strcmp(buffer,"while") == 0) return newLexeme(WHILE, curr_line);
  else if(strcmp(buffer,"include") == 0) return newLexeme(INCLUDE, curr_line);
  else if(strcmp(buffer,"var") == 0) return newLexeme(VAR, curr_line);
  else if(strcmp(buffer,"def") == 0) return newLexeme(DEF, curr_line);
  else if(strcmp(buffer,"return") == 0) return newLexeme(RETURN, curr_line);
  else if(strcmp(buffer,"break") == 0) return newLexeme(BREAK, curr_line);
  else if(strcmp(buffer,"end") == 0) return newLexeme(END, curr_line);
  else if(strcmp(buffer,"for") == 0) return newLexeme(FOR, curr_line);
  else if(strcmp(buffer,"in") == 0) return newLexeme(IN, curr_line);
  else if(strcmp(buffer,"class") == 0) return newLexeme(CLASS, curr_line);
  else if(strcmp(buffer,"endclass") == 0) return newLexeme(ENDCLASS, curr_line);
  else if(strcmp(buffer,"true") == 0) return newLexeme(TRUE, curr_line);
  else if(strcmp(buffer,"false") == 0) return newLexeme(FALSE, curr_line);
  else // must be an identifier (ID)
    return newLexemeString(ID, buffer, curr_line);
}

/** Reads all characters between two double or
  * single quotations form the specified file
  */
static Lexeme *lexString(FILE *fp, Lexer *lexer) {
  char ch;
  char *buffer;
  int size = 80;
  buffer = allocate(size);

  ch = readChar(fp);
  int index = 0;
  while(ch != '\"' && ch != '\'') {
    // check if needs to be reallocated (no explicit limits)
    if (index > size - 2) {
      ++size;
      buffer = reallocate(buffer,size);
    }
    buffer[index] = ch;
    ++index;
    ch = readChar(fp);
  }
  // don't need to push back bc last char is " or '
  return newLexemeString(STRING, buffer, lexer->currentLine);
}

// The following funcs are partially co-opted from Lusth's scanner.c

// returns a single char from the specified file
static char readChar(FILE *fp) {
  char result;
  result = fgetc(fp);

  if (result == EOF) {
    return EOF;
  }
  if (result == 0) {
    Error("SCAN ERROR: attempt to read a non-whitespace character failed\n");
    exit(2);
  }
  return result;
}

/** Skips all white space
  * Here ungetc acts as the pushback operator
  * because it pushes the character back on the filestream.
  */
static void skipWhiteSpace(FILE *fp, Lexer *lexer) {
  int ch;
  // read chars until a non-whitespace character is encountered
  while ((ch = fgetc(fp)) != EOF && isspace(ch)) {
    if (ch == '\n') lexer->currentLine++;
  }

  // a non-space character got us out of the loop, so push it back

  if (ch != EOF) ungetc(ch,fp);
}
// allocates a buffer of size size
static void *allocate(size_t size) {
  char *s;
  s = malloc(size);
  if(s == 0) {
    Error("Could not allocate string. Out of memory!");
  }
  return s;
}
// reallocates memory for s of size size
static void *reallocate(void *s, size_t size) {
  char *t;
  t = realloc(s,size);
  if(t == 0) {
    Error("Could not reallocate string. Out of memory!");
  }
  return t;
}
