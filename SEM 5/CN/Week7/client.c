/*
Implement a basic chat application where multiple clients can send and receive messages through a server.

Client Requirements:
1.	Each client should be able to connect to the server.
2.	Clients should be able to send messages to the server.
3.	Clients should be able to receive and display messages from other clients.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 10200

int sockfd;

void *receive_messages(void *arg) {
    char buffer[1024];
    int n;
    while ((n = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[n] = '\0';
        printf("\n[Chat] %s\n> ", buffer);
        fflush(stdout);
    }
    return NULL;
}

int main() {
    struct sockaddr_in servaddr;
    char msg[1024];
    pthread_t recv_thread;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("172.31.1.38"); // or server IP

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect failed");
        exit(1);
    }

    printf("Connected to chat server. Type messages...\n");

    // Start receiving thread
    pthread_create(&recv_thread, NULL, receive_messages, NULL);

    while (1) {
        printf("> ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = '\0';
        if (strlen(msg) > 0) {
            send(sockfd, msg, strlen(msg), 0);
        }
    }

    close(sockfd);
    return 0;
}
