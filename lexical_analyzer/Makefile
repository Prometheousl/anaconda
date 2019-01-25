CC=gcc
CFLAGS=-g
OPTS = -Wall -Wextra -std=c99
TYPES = types/int.o types/m_string.o types/real.o
OBJS = lexeme.o scanner.o types.o lexer.o errors.o $(TYPES)
TESTS = test1 test2 test3 test4 test5

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

scanner: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(OPTS) -lm

test1 : scanner
	./scanner test1

test2 : scanner
	./scanner test2

test3 : scanner
	./scanner test3

test4 : scanner
	./scanner test4

test5 : scanner
	./scanner test5

run : $(TESTS)

clean :
	rm -f $(OBJS)
	rm -f scanner
