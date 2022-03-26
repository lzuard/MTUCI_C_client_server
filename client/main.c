#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>


///List of main commands
#define IN_HELP         "help"
#define IN_CONNECT      "connect"
#define IN_DISCONNECT   "disconnect"
#define IN_SHUTDOWN     "shutdown"
#define IN_UPDATE       "update"
#define IN_GET          "get"

///List of arguments for commands
#define ARG_SERV_A  "servA"
#define ARG_SERV_B  "servB"

#define ARG_CACHE   "cache"
#define ARG_VM_USE  "vmuse"
#define ARG_FREQ      "freq"
#define ARG_VM_AVAIL  "vmavail"

#define ARG_SERVER  "server"
#define ARG_CLIENT  "client"
#define ARG_ALL     "all"

#define ARG_PLS     "please"
#define ARG_NOTHING "nothing"
#define ARG_WRONG   "wrong server"

const int text_size=256;            //size for all strings
int sock, child_sock, child_pid;    //client socket, update process socket, update process pid
char current_server[text_size];     //current server
char response1[text_size];          //string for 1st line in server answer
char response2[text_size];          //string for 2nd line in server answer


struct sockaddr_in address_serverA; //server A address
struct sockaddr_in address_serverB; //server B address
const int port_serverA=9101; //server A port
const int port_serverB=9200; //server B port

//storage for user input (command+argument)
struct user_input{
    char cmd[text_size];
    char arg[text_size];
};
struct user_input input;


///Setup functions
void exit_handler(){
    close(sock);
    printf("\n\nClient is going off now....\n");
    kill(0,SIGKILL);
}
void term_child(){
    send(child_sock,IN_DISCONNECT,text_size,0);
    usleep(100);
    close(child_sock);
    kill(child_pid,SIGKILL);
    child_pid=-1;
}
void setup_addresses(){
    address_serverA.sin_family=AF_INET;
    address_serverA.sin_port= htons(port_serverA);
    address_serverA.sin_addr.s_addr=INADDR_ANY;

    address_serverB.sin_family=AF_INET;
    address_serverB.sin_port= htons(port_serverB);
    address_serverB.sin_addr.s_addr=INADDR_ANY;
}
void close_connection(){
    close(sock);
    sock= socket(AF_INET,SOCK_STREAM,0);
}

///Print functions
void print_help(){
    printf("********************************\n");
    printf("Available commands and attributes:\n");
    printf("1. help please - show help page\n");
    printf("2. connect - connect to server:\n\tservA - connect to server A\n\tservB - connect to server B\n");
    printf("3. disconnect please - disconnect from current server\n");
    printf("4. get - get info from server:\n\tcache - CPU cache info (A)\n\tvmuse - virtual memory in use (A)");
    printf("\n\tfreq - CPU frequency (B)\n\tvmavail - virtual memory available (B)\n");
    printf("5. update - set up a data update process:\n\tclient - method on client\n\tserver - methdo on server\n");
    printf("6. shutdown - terminate program:\n\tall - client and all servers\n\tclient - client only\n");
    printf("********************************\n");

}
void print_wrong_arg(){
    printf("\nWrong argument \"%s\" for command \"%s\".\n",input.arg,input.cmd);
    printf("Type \"help please\" to see valid commands and arguments\n\n");
}

///Update functions
_Noreturn void update_on_client_work(){
    child_sock=socket(AF_INET,SOCK_STREAM,0);

    if(strcmp(current_server,ARG_SERV_A)==0) {
        if (connect(child_sock, (struct sockaddr *) &address_serverA, sizeof(address_serverA))<0){
            close(child_sock);
            exit(1);
        }
    }
    else if (strcmp(current_server,ARG_SERV_B)==0) {
        if (connect(child_sock, (struct sockaddr *) &address_serverB, sizeof(address_serverB))<0){
            close(child_sock);
            exit(1);
        }
    }
    else{
        sleep(2);
        close(child_sock);
        exit(1);
    }

    send(child_sock,ARG_CLIENT,text_size,0);

    while(1) {
        send(child_sock, ARG_CLIENT, text_size, 0);
        recv(child_sock,&response1,text_size, 0);

        if(strcmp(response1,ARG_NOTHING)!=0){
            recv(child_sock,&response2,text_size, 0);
            printf("\nData update on server:\n%s\n%s\n",response1,response2);
        }
        sleep(3);
    }
}

_Noreturn void update_on_server_work(){
    child_sock=socket(AF_INET,SOCK_STREAM,0);

    if(strcmp(current_server,ARG_SERV_A)==0) {
        if (connect(child_sock, (struct sockaddr *) &address_serverA, sizeof(address_serverA))<0){
            close(child_sock);
            exit(1);
        }
    }
    else if (strcmp(current_server,ARG_SERV_B)==0) {
        if (connect(child_sock, (struct sockaddr *) &address_serverB, sizeof(address_serverB))<0){
            close(child_sock);
            exit(1);
        }
    }
    else{
        sleep(2);
        close(child_sock);
        exit(1);
    }

    send(child_sock,ARG_SERVER,text_size,0);
    while(1){
        recv(child_sock,&response1,text_size, 0);
        recv(child_sock,&response2,text_size, 0);
        printf("\nData update on server:\n%s\n%s\n",response1,response2);
    }
}

///Commands handlers
void handle_help(){
    if(strcmp(input.arg,ARG_PLS)==0) print_help();
    else printf("Be more kind and polite. Do not forget to say \"please\"\n");
}
void handle_connect(){
    if(strcmp(current_server,ARG_CLIENT)==0) { //we can connect only if there is no connection
        if (strcmp(input.arg, ARG_SERV_A) == 0) {
            close_connection();
            if (connect(sock, (struct sockaddr *) &address_serverA, sizeof(address_serverA)) < 0)
                printf("Could not connect to Server A: %s\n", strerror(errno));
            else {
                //send(sock, IN_SHUTDOWN, text_size, 0);
                printf("Server A: Connection successful\n");
                strcpy(current_server,ARG_SERV_A);
            }
        }
        else if (strcmp(input.arg, ARG_SERV_B) == 0) {
            close_connection();
            if (connect(sock, (struct sockaddr *) &address_serverB, sizeof(address_serverB)) < 0)
                printf("Could not connect to Server B: %s\n", strerror(errno));
            else {
                //send(sock, IN_SHUTDOWN, text_size, 0);
                printf("Server B: Connection successful\n");
                strcpy(current_server,ARG_SERV_B);
            }
        }
        else print_wrong_arg();
    }
    else printf("Can not connect to any server: Connection is already established with: %s\n",current_server);
}
void handle_disconnect(){
    if(strcmp(input.arg,ARG_PLS)==0){               //if please
        if(strcmp(current_server,ARG_CLIENT)!=0) {  //if there is connection
            if(child_sock>0) term_child();          //disconnect update process if alive
            send(sock,IN_DISCONNECT,text_size,0);
            printf("Disconnected from %s successful\n",current_server);
            strcpy(current_server,ARG_CLIENT);
        }
        else printf("There is no connection to disconnect\n");
    }
    else printf("Be more kind and polite. Do not forget to say \"please\"\n");
}
void handle_shut_down(){
    if(strcmp(input.arg, ARG_CLIENT) == 0){
        printf("NOTE: Servers won't be shut down!\n");
        kill(0,SIGTERM);
    }
    else if(strcmp(input.arg, ARG_ALL) == 0){
        close_connection();
        printf("\nServer A group: ");
        if(connect(sock,(struct sockaddr*)&address_serverA, sizeof(address_serverA))<0)
            printf("%s\n", strerror(errno));
        else{
            send(sock,IN_SHUTDOWN,text_size,0);
            printf("Shut down\n");
        }
        close_connection();
        printf("Server B group: ");
        if(connect(sock,(struct sockaddr*)&address_serverB, sizeof(address_serverB))<0)
            printf("%s\n", strerror(errno));
        else{
            send(sock,IN_SHUTDOWN,text_size,0);
            printf("Shut down\n");
        }
        kill(0,SIGTERM);
    }
    else print_wrong_arg();
}
void handle_update(){
    printf("child %d\n",child_pid);
    if(strcmp(current_server,ARG_CLIENT)!=0) {
        if (strcmp(input.arg, ARG_CLIENT) == 0) {
            if (child_pid > 0) term_child();
            sleep(1);
            child_pid = fork();
            if (child_pid == 0) update_on_client_work();
        }
        else if (strcmp(input.arg, ARG_SERVER) == 0) {
            if (child_pid > 0) term_child();
            sleep(1);
            child_pid = fork();
            if (child_pid == 0) update_on_server_work();
        }
        else print_wrong_arg();
    }
    else printf("Could not set up an update process: There is no connection available\n");
}
void handle_get(){
    if(strcmp(current_server,ARG_CLIENT)!=0) {
        if(strcmp(input.arg,ARG_CACHE)==0 || strcmp(input.arg, ARG_VM_USE) == 0 ||
                strcmp(input.arg,ARG_FREQ)==0 || strcmp(input.arg,ARG_VM_AVAIL)==0)
        {
            send(sock,input.arg,text_size,0);
            recv(sock,&response1,text_size,0);

            printf("Server response: ");
            if(strcmp(response1,ARG_WRONG)==0) printf("Could not execute your request\n");
            else printf("\n%s\n",response1);

        }
        else print_wrong_arg();
    }
    else printf("Could not get anything: There is no connection available\n");
}


///Main program function
_Noreturn void terminal(){
    sock=socket(AF_INET,SOCK_STREAM,0);
    setup_addresses();

    child_pid=-1;

    strcpy(current_server,ARG_CLIENT);
    printf("Client is now on\n");
    printf("Type \"help please\" to see help page\n");

    while(1){
        printf("Type the command: ");
        scanf(" %s %s",input.cmd,input.arg);


        if(strcmp(input.cmd,IN_HELP)==0)                handle_help();
        else if(strcmp(input.cmd,IN_CONNECT)==0)        handle_connect();
        else if(strcmp(input.cmd, IN_DISCONNECT)==0)    handle_disconnect();
        else if(strcmp(input.cmd, IN_SHUTDOWN)==0)      handle_shut_down();
        else if(strcmp(input.cmd, IN_UPDATE)==0)        handle_update();
        else if(strcmp(input.cmd, IN_GET)==0)           handle_get();
        else printf("Unknown command \"%s\".\nType \"help please\" to see valid commands and arguments\n",input.cmd);
    }

}

int main() {
    signal(SIGTERM,exit_handler);
    terminal();
}
