#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

void print_port_num(int sock)
{
    char buf[48];
    struct sockaddr_in s;
    socklen_t sz;

    sz = sizeof(s);

    //get socket name
    if(getsockname(sock, (struct sockaddr*)&s, &sz) != 0)
    {
        perror("getsockname");
        return;
    }
    // bind ip to char
    inet_ntop(AF_INET, &s.sin_addr, buf, sizeof(buf));
    printf("%s : %d\n", buf, ntohs(s.sin_port));
}

int main()
{
    int sock0;
    struct sockaddr_in client;
    socklen_t len;
    int sock;
    struct addrinfo hints, *res;
    int err;
    int fd;
    int n, ret;
    char buf[65536];

    fd = open("hogesave.txt", O_WRONLY | O_CREAT, 0600);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    err = getaddrinfo(NULL, "12345", &hints, &res);
    if (err != 0)
    {
        printf("getaddrinfo : %s\n", gai_strerror(err));
        return 1;
    }

    sock0 = socket(res->ai_family, res->ai_socktype, 0);
    if(sock0 < 0)
    {
        perror("socket");
        return 1;
    }

    if(bind(sock0, res->ai_addr, res->ai_addrlen) != 0)
    {
        perror("bind");
        return 1;
    }

    freeaddrinfo(res);

    listen(sock0, 5);

    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr *)&client, &len);
    if(sock < 0)
    {
        perror("accept");
        return 1;
    }

    while((n = read(sock, buf, sizeof(buf))) > 0)
    {
        ret = write(fd, buf, n);
        if (ret < 1)
        {
            perror("write");
            break;
        }
    }

    close(sock);
    close(sock0);

    return 0;
}
