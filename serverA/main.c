#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/sysctl.h>
#include <netinet/in.h>
#include <sys/fcntl.h>


#define IN_CONNECT      "connect"
#define IN_DISCONNECT   "disconnect"
#define IN_SHUTDOWN     "shutdown"

#define ARG_CACHE   "cache"
#define ARG_VM_USE  "vmuse"

#define ARG_SERVER  "server"
#define ARG_CLIENT  "client"

#define ARG_NOTHING "nothing"
#define ARG_WRONG   "wrong server"


const int text_size=256;
int server_sock, client_sock,fifo_file;

struct sockaddr_in address_server;
const int port_serverA=9101;
const char fifo_path[256]="/Users/izuard/inform_ptushkin/log_servA/fifo";

char request[text_size];
char answer1[text_size];
char answer2[text_size];
char last_answer[text_size];
char slog[text_size];


void exit_handler(){
    close(server_sock);
    close(fifo_file);
    printf("\n\nServer is going off now....\n");
    kill(0,SIGKILL);
}
void set_address(){
    address_server.sin_family=AF_INET;
    address_server.sin_port=htons(port_serverA);
    address_server.sin_addr.s_addr=INADDR_ANY;
}

void to_log(char log1[text_size]){
    int pid=fork();
    if(pid==0) {
        fifo_file = open(fifo_path, O_WRONLY);
        if (fifo_file == -1) {
            printf("\n\nError on open fifo: %s", strerror(errno));
            exit(0);
        }
        write(fifo_file, log1, text_size);
        close(fifo_file);
        exit(1);
    }
}

void get_answer1(){ //l1 I , l1 d,l2,l3 cache
    int L1_cache_I;
    int L1_cache_D;
    int L2_cache;
    int L3_cache;
    int req[4][2]={{CTL_HW,HW_L1ICACHESIZE},{CTL_HW,HW_L1DCACHESIZE},{CTL_HW,HW_L2CACHESIZE},{CTL_HW,HW_L3CACHESIZE}};
    size_t size= sizeof(int);

    sysctl(req[0],sizeof(req[0]),&L1_cache_I,&size,NULL,0);  //get L1 I cache size
    sysctl(req[1],sizeof(req[1]),&L1_cache_D,&size,NULL,0);  //get L1 D cache size
    sysctl(req[2],sizeof(req[2]),&L2_cache,&size,NULL,0);    //get L2 cache size
    sysctl(req[3],sizeof(req[3]),&L3_cache,&size,NULL,0);    //get L3 cache size

    sprintf(answer1,"CPU cache sizes (kb): L1I - %d, L1D - %d, L2 - %d, L3 - %d",
            L1_cache_I/1024,L1_cache_D/1024,L2_cache/1024,L3_cache/1024);
}
void get_answer2(){
    struct xsw_usage vm_usage;
    int req[2]={CTL_VM,VM_SWAPUSAGE};
    size_t size= sizeof(vm_usage);

    sysctl(req, sizeof(req),&vm_usage,&size,NULL,0);

    sprintf(answer2,"Virtual memory in use: %llu",vm_usage.xsu_used);
}
void handle_cache(){
    get_answer1();
    sprintf(slog,"Socket %d - sent data: %s",client_sock,answer1);          to_log(slog);
    send(client_sock,answer1,text_size,0);
}
void handle_vm_use(){
    get_answer2();
    sprintf(slog,"Socket %d - sent data: %s",client_sock,answer2);          to_log(slog);
    send(client_sock,answer2,text_size,0);
}
void handle_shutdown(){
    to_log(IN_SHUTDOWN);
    kill(getppid(),SIGTERM);
}
void handle_disconnect(){
    sprintf(slog,"Socket %d - disconnected\n",client_sock);         to_log(slog);
    close(client_sock);
    exit(1);
}

_Noreturn void handle_client_update(){
    while(1) {
        recv(client_sock, &request, text_size, 0);
        if(strcmp(request,IN_DISCONNECT)==0) handle_disconnect();
        get_answer1();
        get_answer2();

        if(strcmp(answer2,last_answer)==0) {
            send(client_sock,ARG_NOTHING,text_size,0);
        }
        else{
            send(client_sock,answer1,text_size,0);
            send(client_sock,answer2,text_size,0);
            strcpy(last_answer,answer2);
        }
    }
}
_Noreturn void handle_server_update() {
    printf("gere\n");
    int pid=fork();
    if (pid == 0) { //timer for terminate update on server process
        sleep(120);
        kill(getppid(), SIGKILL);
        handle_disconnect();
    }
    else {
        while (1) {
            get_answer1();
            get_answer2();
            printf("answer2 %s\nlast_answer %s",answer2,last_answer);

            if (strcmp(answer2, last_answer) != 0) {
                send(client_sock, answer1, text_size, 0);
                send(client_sock, answer2, text_size, 0);
                strcpy(last_answer, answer2);
            }
            sleep(3);
        }
    }
}

_Noreturn void query(){
    server_sock=socket(AF_INET,SOCK_STREAM,0);
    set_address();

    int pid;

    //close(server_sock);
    if(bind(server_sock,(struct sockaddr*)&address_server, sizeof(address_server))<0){
        printf("\nCould not start the server: One copy of the server is already running\n");
        kill(0,SIGTERM);
    }

    printf("Server started successfully\n");                            to_log("Server started successfully");
    listen(server_sock,10);
    printf("Listen established\n");                                     to_log("Listen established");
    while(1){
        client_sock= accept(server_sock,NULL,NULL);
        sprintf(slog,"Connected new socket - %d",client_sock);          to_log(slog);

        pid=fork();
        if(pid==0){
            while(1) {
                recv(client_sock, &request, text_size, 0);
                sprintf(slog,"Socket %d - new request: %s",client_sock,request);    to_log(slog);
                if (strcmp(request, ARG_CACHE) == 0) handle_cache();
                else if (strcmp(request, ARG_VM_USE) == 0) handle_vm_use();
                else if (strcmp(request, IN_DISCONNECT) == 0) handle_disconnect();
                else if (strcmp(request, ARG_CLIENT) == 0) handle_client_update();
                else if (strcmp(request, ARG_SERVER) == 0) handle_server_update();
                else if (strcmp(request, IN_SHUTDOWN) == 0) handle_shutdown();
            }
        }
    }
}


int main() {

    signal(SIGTERM, exit_handler);
    query();
}
