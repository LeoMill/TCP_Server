#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  int sock_listen;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  socklen_t len;
  int sock_client;

  sock_listen = socket(AF_INET, SOCK_STREAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(sock_listen, (struct sockaddr *)&addr, sizeof(addr));
  listen(sock_listen, 5);

  len = sizeof(client);
  sock_client = accept(sock_listen, (struct sockaddr *)&client, &len);

  write(sock_client, "HELLO", 5);
  close(sock_client);
  close(sock_listen);

  return 0;
}
