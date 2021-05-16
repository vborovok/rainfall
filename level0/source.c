#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av, char **envp) {
    int num;

    num = atoi(av[1]);
    if (num != 423) {
        printf("No !");
        return 0;
    }
    execve("/bin/bash", NULL, envp);
}
