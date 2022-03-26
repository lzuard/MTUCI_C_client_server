#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define IN_SHUTDOWN    "shutdown"

int fifo_file;
FILE *log_file;
const char fifo_path[512]="/Users/izuard/inform_ptushkin/log_servB/fifo";
const char logs_path[512]="/Users/izuard/inform_ptushkin/log_servB/log";


void exit_handler(){
    close(fifo_file);
    fclose(log_file);
    printf("\n\n[Server] Going off\n\n");
    kill(0,SIGKILL);
}

_Noreturn void i_am_out_of_ideas_for_functions_names(){
    char log[512];

    if((log_file=fopen(logs_path, "w")) == NULL){
        printf("[Server] Error on open log file: %s\n", strerror(errno));
        kill(0, SIGTERM);
    }

    while(1) {
        fifo_file = open(fifo_path, O_RDONLY);
        if (fifo_file == -1) {
            printf("[Server] Error on open fifo file: %s\n", strerror(errno));
            kill(0, SIGTERM);
        }
        read(fifo_file, &log, sizeof(log));
        close(fifo_file);
        printf("[Log] %s\n", log);
        if(fprintf(log_file, "%s\n", log) < 0){
            printf("[Server] Error on write into log file: %s\n", strerror(errno));
        }
        if(strcmp(log, IN_SHUTDOWN) == 0) kill(0, SIGTERM);
    }
}

int main() {
    signal(SIGTERM, exit_handler);
    i_am_out_of_ideas_for_functions_names();
}
