#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf helpMeOut;

void handlerSegFault(int errNum) {
    printf("Definitely not a segmentation fault :-)\n");
    exit(0);
}

void handlerSigFpe(int errNum) {
    printf("Totally not the programmers fault :-P\n");
    longjmp(helpMeOut, 1);
}

int main(int argc, char *argv[])
{
    int* corruptPointer = (int*) 0;

    signal(SIGFPE, handlerSigFpe);
    signal(SIGSEGV, handlerSegFault);

    if (0 == setjmp(helpMeOut)) {
        int divideProblem = 420;
        divideProblem /= 0;
    } else {
        *corruptPointer = 42;
    }

    return 0;
}
