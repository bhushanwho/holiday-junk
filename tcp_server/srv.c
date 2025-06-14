#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8181

int main() {
    
    int s, c;
    socklen_t addrlen;
    struct sockaddr_in srv, cli;
    char buf[512];
    char *data;

    memset( &srv, 0, sizeof(srv) );
    memset( &cli, 0, sizeof(cli) );

    s = socket( AF_INET, SOCK_STREAM, 0 );

    if( s < 0 ) {
        printf("socket() fail\n");
        close(s);
        return -1;
    }

    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = 0;
    srv.sin_port = htons(PORT);

    if( bind( s, (struct sockaddr *)&srv, sizeof(srv) ) ) {
        printf("bind() fail\n");
        close(s);
        return -1;
    }

    if( listen(s, 5) ) {
        printf("listen() fail\n");
        close(s);
        return -1;
    }
    printf("listening on 0.0.0.0:$d\n", PORT);

    c = accept( s, (struct sockaddr *)&srv, &addrlen );
    if( c < 0 ) {
        printf("accept() fail\n");
        close(s);
        return -1;
    }

    printf("client connected\n");

    read( c, buf, 511 );
    data = "httpd v1.0\n";
    write( c, data, strlen(data) );

    close(c);
    close(s);

    return 0;

}