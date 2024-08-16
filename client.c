#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void download_file(int socket, const char *filename) {
    char buffer[BUFFER_SIZE] = {0};
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("File creation failed");
        return;
    }

    int bytesReceived = 0;
    while ((bytesReceived = recv(socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytesReceived, file);
    }

    printf("File '%s' downloaded successfully.\n", filename);
    fclose(file);
}

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    int wsaStartup = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaStartup != 0) {
        printf("WSAStartup failed: %d\n", wsaStartup);
        return 1;
    }
#endif

    int client_socket;
    struct sockaddr_in server_address;
    char filename[BUFFER_SIZE] = {0};

    printf("Enter the message: ");
    scanf("%s", filename);

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address");
        closesocket(client_socket);
        return 1;
    }

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        closesocket(client_socket);
        return 1;
    }

    send(client_socket, filename, strlen(filename), 0);
    download_file(client_socket, filename);

    closesocket(client_socket);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
