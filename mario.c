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
        int send = 10;
        printf("[parent] sending: %d\n", send);
        write(mario[WRITE], &send, sizeof(send));
        int receive;
        read(luigi[READ], &receive, sizeof(receive));
        printf("[parent] received: %d\n", receive);
    } else {
        int receive;
        read(mario[READ], &receive, sizeof(receive));
        printf("[child] received: %d\n", receive);
    }
    return 0;
}
