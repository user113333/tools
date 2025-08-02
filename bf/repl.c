#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DATA_SIZE 30000
#define SOURCE_SIZE 30000
#define JUMPLIST_SIZE 3000

int supplements_enabled = 0; // TODO: enable by flag

struct program_state_t {
    unsigned char data[DATA_SIZE];
    char source[SOURCE_SIZE];
    unsigned int source_pointer;
    unsigned int instruction_pointer;
    unsigned int data_pointer;
    unsigned int stop_execution; // ie. execution status
    unsigned int jumplist[JUMPLIST_SIZE];
    unsigned int jumplist_pointer;
} p;

void program_state_reset(struct program_state_t* program_state)
{
    program_state->source_pointer = 0;
    program_state->instruction_pointer = 0;
    program_state->data_pointer = 0;
    program_state->stop_execution = 0;
    program_state->jumplist_pointer = 0;
    memset(program_state->data, 0, DATA_SIZE);
    memset(program_state->source, 0, SOURCE_SIZE);
    memset(program_state->jumplist, 0, JUMPLIST_SIZE);
}

void parse_dot()
{
    printf("%c", p.data[p.data_pointer]);
    p.source_pointer++;
}

void parse_comma()
{
    int c = getchar();
    p.data[p.data_pointer] = (unsigned char)c;
    p.source_pointer++;
}

void parse_gt()
{
    if (p.data_pointer == DATA_SIZE - 1) {
        printf("Data overflow\n");
        p.stop_execution = 1;
        return;
    }
    p.data_pointer++;
    p.source_pointer++;
}

void parse_lt()
{
    if (p.data_pointer == 0) {
        printf("Data underflow");
        p.stop_execution = 1;
        return;
    }
    p.data_pointer--;
    p.source_pointer++;
}

void parse_plus()
{
    p.data[p.data_pointer]++;
    p.source_pointer++;
}

void parse_minus()
{
    p.data[p.data_pointer]--;
    p.source_pointer++;
}

// left bracket
void parse_lb()
{
    // TODO: it does not skip to the ] if current cell is 0
    p.jumplist[p.jumplist_pointer++] = p.source_pointer;
    p.source_pointer++;
}

// right bracket
void parse_rb()
{
    if (p.data[p.data_pointer] == 0) {
        p.source_pointer++;
        p.jumplist_pointer--;
        return;
    }
    p.source_pointer = p.jumplist[--p.jumplist_pointer];
}

// SUPPLEMENT
// prints integral value of a cell
void parse_p()
{
    printf("%d\n", p.data[p.data_pointer]);
    p.source_pointer++;
}

// SUPPLEMENT
// reads integral value from stdin and writes it into cell
void parse_r()
{
    int input = 0;
    scanf("%d", &input);
    p.data[p.data_pointer] = (unsigned char)input;
    p.source_pointer++;
}

void repl()
{
    program_state_reset(&p);
    while (!p.stop_execution) {
        int input;

        if (p.source[p.source_pointer] == 0) {
            input = getchar();
            if (input == EOF) {
                p.stop_execution = 1;
                continue;
            }
            p.source[p.source_pointer] = (char)input;
        } else {
            input = p.source[p.source_pointer];
        }
        switch (input) {
            case '.': parse_dot(); break;
            case ',': parse_comma(); break;
            case '>': parse_gt(); break;
            case '<': parse_lt(); break;
            case '+': parse_plus(); break;
            case '-': parse_minus(); break;
            case '[': parse_lb(); break;
            case ']': parse_rb(); break;
            default: break;
        }
        if (supplements_enabled) {
            switch (input) {
                case 'r': parse_r(); break;
                case 'p': parse_p(); break;
                default: break;
            }
        }
        /* printf("%s\n", p.source); */
        /* for (int i = 0; i < p.source_pointer - 1; i++) { */
        /*     printf(" "); */
        /* } */
        /* printf("| %d\n", p.jumplist_pointer); */
    }
}
