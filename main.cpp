#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
    int sock_listen;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    socklen_t len;
    int sock_client;

    sock_listen = socket(AF_INET, SOCK_STREAM, 0);

    //addr.sin_family = AF_INET;
    //addr.sin_port = htons(12345);
    //addr.sin_addr.s_addr = INADDR_ANY;
    //bind(sock_listen, (struct sockaddr *)&addr, sizeof(addr));
    if(listen(sock_listen, 5) != 0)
    {
        perror("listen");
        return 1;
    }
    print_port_num(sock_listen);

    len = sizeof(client);
    sock_client = accept(sock_listen, (struct sockaddr *)&client, &len);
    if(sock_client < 0)
    {
        perror("accept");
        return 1;
    }

    write(sock_client, "HELLO\n", 6);
    close(sock_client);
    close(sock_listen);

    return 0;
}
