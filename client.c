#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <server_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *server_ip = argv[1];
    int port = atoi(argv[2]);

    /*
    Create a socket file descriptor
    AF_INET: IPv4, SOCK_STREAM: TCP, 0: default protocol (OS decides)
    */

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Fill info about the server that the client will connect to
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    // Connecting to the server
    int connect_rval = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (connect_rval == -1) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to %s:%d\n", server_ip, port);
    printf("Type messages to send to the server (type 'exit' to quit):\n");

    char send_buffer[BUFFER_SIZE];
    char recv_buffer[BUFFER_SIZE];

    /*
    Send data to the server
    send(sockfd, send_buffer, strlen(send_buffer), 0);

    Receive data from the server
    recv(sockfd, recv_buffer, sizeof(recv_buffer), 0);
    printf("Server: %s\n", recv_buffer);
    */

    while (1) {

        printf("Client: ");
        fflush(stdout);

        // Read user input
        char *result = fgets(send_buffer, sizeof(send_buffer), stdin);

        if (result == NULL) {
            break;
        }

        // Remove the newline character from input
        size_t newline_index = strcspn(send_buffer, "\n");
        send_buffer[newline_index] = '\0';

        // Check if the user wants to exit
        int should_exit = strcmp(send_buffer, "exit") == 0;

        if (should_exit) {
            break;
        }

        // Send message to the server
        ssize_t bytes_sent = send(sockfd, send_buffer, strlen(send_buffer), 0);

        if (bytes_sent == -1) {
            perror("Send failed");
            break;
        }

        // Receive response from the server
        ssize_t bytes_received = recv(sockfd, recv_buffer, sizeof(recv_buffer) - 1, 0);

        if (bytes_received > 0) {
            recv_buffer[bytes_received] = '\0';
            printf("Server: %s\n", recv_buffer);
        } else if (bytes_received == 0) {
            // Server sends 0 bytes when it wants to close the connection
            printf("Server closed the connection.\n");
            break;
        } else {
            perror("Receive failed");
            break;
        }
    }

    // Close the socket/connection
    close(sockfd);
    return 0;
}
