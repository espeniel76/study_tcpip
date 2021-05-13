#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int nSockServer;
    int nSockClient;

    struct sockaddr_in oAddrServer;
    struct sockaddr_in oAddrClient;
    socklen_t nClientAddressSize;

    char message[] = "Hello World";

    nSockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSockServer == -1)
    {
        error_handling("Socker error");
    }

    memset(&oAddrServer, 0, sizeof(oAddrServer));
    oAddrServer.sin_family = AF_INET;
    oAddrServer.sin_addr.s_addr = htonl(INADDR_ANY);
    oAddrServer.sin_port = htons(7325);

    if (bind(nSockServer, (struct sockaddr *)&oAddrServer, sizeof(oAddrServer)) == -1)
    {
        error_handling("bind() error");
    }

    if (listen(nSockServer, 5) == -1)
    {
        error_handling("listen() error");
    }

    nClientAddressSize = sizeof(nSockClient);
    nSockClient = accept(nSockServer, (struct sockaddr *)&oAddrClient, &nClientAddressSize);
    if (nSockClient == -1)
    {
        error_handling("accept() error");
    }

    write(nSockClient, message, sizeof(message));
    close(nSockClient);
    close(nSockServer);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}