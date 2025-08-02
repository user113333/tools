.PHONY: all build

all: build

build:
	gcc main.c repl.c -o bf

test:
	gcc test.c repl.c -o test && test

hello_world: build
	echo -n "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++." | ./bf -s
