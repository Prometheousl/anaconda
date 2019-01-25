/*
 * lexer.c
 *
 *  Created on: Jan 24, 2019
 *      Author: alexl
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "errors.h"

static Lexeme *lexNumber(FILE *, Lexer *);
static Lexeme *lexVariableOrKeyword(FILE *, Lexer *);
static Lexeme *lexString(FILE *, Lexer *);
static char readChar(FILE *);
static void skipWhiteSpace(FILE *, Lexer *);
static char *charToString(char c);

struct lexer {
  char *fileName;
  int currentLine;
};

Lexer *newLexer(char *fn) {
  Lexer *p = malloc(sizeof(Lexer));
  if (p == 0) {
    fprintf(stderr,"out of memory\n"); exit(1);
  }
  p->fileName = fn;
  p->currentLine = 0;
  return p;
}

Lexeme *lex(Lexer *lexer) {
  FILE *fp = fopen(lexer->fileName, "r");
  if(fp == NULL) Error("Error in opening file.");
  char ch;
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
    case '/': return newLexeme(DIVIDE, lexer->currentLine);
    case '<': return newLexeme(LESS_THAN, lexer->currentLine);
    case '>': return newLexeme(GREATER_THAN, lexer->currentLine);

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
          UNKNOWN, charToString(ch), lexer->currentLine));
      }
    }
}

// static functions

static Lexeme *lexNumber(FILE *fp, Lexer *lexer) {
  int real = 0;
  char *buffer = "";
  char ch;
  ch = readChar(fp);
  while(ch != EOF && (isdigit(ch) || ch == '.')) {
    strcat(buffer,charToString(ch));
    if(ch == '.' && real)
      ErrorLexeme(newLexemeString(BAD_NUMBER, buffer, lexer->currentLine));
    if(ch == '.')
      real = 1;
    ungetc(ch, fp);
    if(real)
      return newLexemeReal(atof(buffer), lexer->currentLine);
    else
      return newLexemeInt(atoi(buffer), lexer->currentLine);
  }
}

static Lexeme *lexVariableOrKeyword(FILE *fp, Lexer *lexer) {
  char ch;
  char *buffer = "";

  ch = readChar(fp);
  while(isalpha(ch) || isdigit(ch)) {
    strcat(buffer,charToString(ch));
    ch = readChar(fp);
  }

  // push back character bc might be punctuation
  ungetc(ch,fp);
  int curr_line = lexer->currentLine;
  // token either variable or keyword
  // test all keywords
  if(strcmp(buffer,IF) == 0) return newLexeme(IF, curr_line);
  else if(strcmp(buffer,ELSE) == 0) return newLexeme(ELSE, curr_line);
  else if(strcmp(buffer,WHILE) == 0) return newLexeme(WHILE, curr_line);
  else if(strcmp(buffer,INCLUDE) == 0) return newLexeme(INCLUDE, curr_line);
  else if(strcmp(buffer,VAR) == 0) return newLexeme(VAR, curr_line);
  else if(strcmp(buffer,DEF) == 0) return newLexeme(DEF, curr_line);
  else if(strcmp(buffer,RETURN) == 0) return newLexeme(RETURN, curr_line);
  else if(strcmp(buffer,BREAK) == 0) return newLexeme(BREAK, curr_line);
  else if(strcmp(buffer,END) == 0) return newLexeme(END, curr_line);
  else if(strcmp(buffer,FOR) == 0) return newLexeme(FOR, curr_line);
  else if(strcmp(buffer,CLASS) == 0) return newLexeme(CLASS, curr_line);
  else if(strcmp(buffer,ENDCLASS) == 0) return newLexeme(ENDCLASS, curr_line);
  else // must be an identifier (ID)
    return newLexemeString(ID, buffer, curr_line);
}

static Lexeme *lexString(FILE *fp, Lexer *lexer) {
  char ch;
  char *buffer = "";

  ch = readChar(fp);
  while(ch != '\"' && ch != '\'') {
    strcat(buffer,charToString(ch));
    ch = readChar(fp);
  }
  // don't need to push back bc last char is " or '
  return newLexemeString(STRING, buffer, lexer->currentLine);
}

// these are partially co-opted from Lusth's scanner.c
// returns a single char from the specified file
static char readChar(FILE *fp) {
  int result;
  char x;
  result = fscanf(fp," %c",&x);
  if (result == EOF) {
    return EOF;
  }
  if (result == 0) {
    Error("SCAN ERROR: attempt to read a non-whitespace character failed\n");
    exit(2);
  }
  return x;
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

/** Turns a char into a char* */
static char *charToString(char c) {
  char *s = malloc(2*sizeof(char));
  s[0] = c;//asdkjh
  s[1] = '\0';
  //printf("Just allocated a string. String is %s\n",getSTRING(str));
  return s;
}
