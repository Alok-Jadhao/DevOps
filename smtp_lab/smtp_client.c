#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void send_email(const char *server_ip, int port, const char *email_content) {
    int sock;
    struct sockaddr_in server_addr;
    char response[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection error");
        exit(1);
    }

    write(sock, email_content, strlen(email_content));
    read(sock, response, BUFFER_SIZE);
    printf("Server Response: %s\n", response);

    close(sock);
}

int main() {
    char sender[50], recipient[50], subject[100], message[500], email_content[BUFFER_SIZE];
    int port;
    char server_ip[20];

    printf("Enter sender email: ");
    scanf("%s", sender);
    printf("Enter recipient email: ");
    scanf("%s", recipient);
    printf("Enter subject: ");
    scanf(" %[^\n]", subject);
    printf("Enter message: ");
    scanf(" %[^\n]", message);

    sprintf(email_content, "From: %s\nTo: %s\nSubject: %s\n\n%s", sender, recipient, subject, message);

    if (strstr(recipient, "comp.com")) {
        strcpy(server_ip, "127.0.0.1");
        port = 2525;
    } else if (strstr(recipient, "cse.com")) {
        strcpy(server_ip, "127.0.0.1");
        port = 2526;
    } else {
        printf("Invalid recipient domain!\n");
        return 1;
    }

    send_email(server_ip, port, email_content);
    return 0;
}
