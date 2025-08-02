#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

// struct winsize {
//     unsigned short ws_row;
//     unsigned short ws_col;
//     unsigned short ws_xpixel;
//     unsigned short ws_ypixel;
struct winsize fetch_term_size()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}

void progress(double proc, unsigned int term_width)
{
    printf("\r");
    for (int i = 1; i < term_width * proc; i++) {
        printf("-");
    }
    if (proc < 1.0) printf(">");
    printf("%d\n", proc * 100);
    fflush(stdout);
}

int main()
{
    const double exetime = 1;
    const double refresh_time = 0.1;
    struct winsize w = fetch_term_size();
    for (double i = 0; i < 1; i += 1 / (exetime / refresh_time)) {
        progress(i, w.ws_col);
        usleep(refresh_time * 1000000);
    }
    /* printf("\r"); */
    return 0;
}
