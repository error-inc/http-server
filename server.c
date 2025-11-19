
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main (void)
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;

    //create socket
    server_socket = socket( AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("Error creating a socket!\n");
        return 1;
    }

    //add port no to the addr so bind knows which port to bind to i guess (also protocol too)
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //bind socket
    if(bind( server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1)
    {
        printf("Error binding the socket to port.\n");
        return 2;
    }

    //listen
    if(listen(server_socket, 5) == 0)
    {
        printf("Listening on port....\n");
    }
    else
    {
        printf("Error listening to port.\n");
    }

    //accept conn
    addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &addr_len); 
    if(client_socket == -1)
    {
        printf("Error accepting connection.\n");
    }

    //send message when connection is accepted
    char* response = "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "Hello, world!";
    send(client_socket, response, strlen(response),0);

    return 0;
}


