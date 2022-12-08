#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ws2tcpip.h>
#include <ws2spi.h>

int init()
{
    WSADATA wsaData;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
}

void clean()
{
    WSACleanup();
}

int main()
{
    init();
    int create_socket, new_socket;
    socklen_t addrlen;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    struct sockaddr_in address;

    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0)
    {
        printf("The socket was created\n");
    }

    getchar();

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15000);

    if (bind(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0)
    {
        printf("Binding socket\n");
    }

    while (1)
    {
        if (listen(create_socket, 10) < 0)
        {
            perror("server: listen");
            exit(1);
        }

        if ((new_socket = accept(create_socket, (struct sockaddr *)&address, &addrlen)) < 0)
        {
            perror("server: accept");
        }

        if (new_socket > 0)
        {
            printf("The Client is connected...\n");
        }

        recv(new_socket, buffer, bufsize, 0);
        printf("%s\n", buffer);
        write(new_socket, "Hello, World!\n", 12);
        close(new_socket);
    }
    close(create_socket);
    clean();
    return 0;
}