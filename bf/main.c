#include <stdio.h>
#include <unistd.h>

#include "repl.h"

enum MODE_ {
    MODE_REPL = 0,
    MODE_COMPILER = 1,
    MODE_INTERPRETER = 2
};

struct options_t {
    int mode;
} options;

#define OPTSTRING "hs"

void parse_args(int argc, char** argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "hs")) != -1) {
        switch (opt) {
            case 'h':
                printf("bf [-" OPTSTRING "]\n");
                printf("  -h       print this message\n");
                printf("  -s       enable brainfuck supplement commands\n");
                printf("  -i FILE  interpret FILE (no repl)\n");
                printf("  -c FILE  compile FILE (no repl)\n");
                break;
            /* case 's': supplements_enabled = 1; break; */
            /* case 'i': mode = MODE_INTERPRETER; break; */
            /* case 'c': mode = MODE_COMPILER; break; */
        }
    }
}

int main(int argc, char** argv)
{
    parse_args(argc, argv);

    switch (options.mode) {
        /* case MODE_COMPILER: compiler(); break; */
        /* case MODE_INTERPRETER: interpreter(); break; */
        case MODE_REPL: repl(); break;
    }
}
