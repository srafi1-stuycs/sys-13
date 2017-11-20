#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int mario[2];
    int luigi[2];
    int READ = 0;
    int WRITE = 1;
    pipe(mario);
    pipe(luigi);

    int f = fork();
    if (f) {
        //parent
        close(mario[READ]);
        close(luigi[WRITE]);
        int send = 10;
        printf("[parent] sending: %d\n", send);
        write(mario[WRITE], &send, sizeof(send));
        close(mario[WRITE]);
        int receive;
        read(luigi[READ], &receive, sizeof(receive));
        close(luigi[READ]);
        printf("[parent] received: %d\n", receive);
    } else {
        //child
        close(mario[WRITE]);
        close(luigi[READ]);
        int receive;
        read(mario[READ], &receive, sizeof(receive));
        printf("[child] received: %d\n", receive);
        receive += 15;
        printf("[child] applied da mathematics: %d\n", receive);
        write(luigi[WRITE], &receive, sizeof(receive));
        close(mario[READ]);
        close(luigi[WRITE]);
    }
    return 0;
}
