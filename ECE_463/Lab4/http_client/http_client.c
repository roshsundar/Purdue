/* The code is subject to Purdue University copyright policies.
 * DO NOT SHARE, DISTRIBUTE, OR POST ONLINE
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "usage: ./http_client [host] [port number] [filepath]\n");
        exit(1);
    }

    // ========================== Exract arguments from call into vars
    char * servername = argv[1];
    int port = atoi(argv[2]);
    char * fpath = argv[3];
    //printf("\nServer: %s, Port: %d, Filepath: %s\n", servername, port, fpath); // DEBUG

    // ========================== Resolve server name into server IP
    struct addrinfo* serverinf;
    if (getaddrinfo(servername, NULL, NULL, &serverinf) != 0)
    {
        //fprintf(stderr, "\nUnable to resolve server name into IP\n"); // DEBUG
        //exit(1);
    }
    struct sockaddr_in* saddr = (struct sockaddr_in*) serverinf -> ai_addr;
    char* serverIP = inet_ntoa(saddr -> sin_addr);
    //printf("\nResolved server IP is %s\n", serverIP); // DEBUG

    // ========================== Create socket connection & Sever obj
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(serverIP);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // ========================== Connect to server
    if (connect(fd, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        //fprintf(stderr, "\nUnable to connect\n"); // DEBUG
        //exit(1);
    }
    else
    {
        //printf("\nConnected to server\n"); // DEBUG
    }

    // ========================== Create HTTP header
    char http_header[1024] = {0};
    sprintf(http_header + strlen(http_header), "GET %s HTTP/1.0\r\n", fpath);
    sprintf(http_header + strlen(http_header), "Host: %s:%d\r\n", servername, port);
    sprintf(http_header + strlen(http_header), "\r\n");
    //printf("\nHTTP request header:\n============\n%s\n============\n\n", http_header); // DEBUG

    // ========================== Send HTTP request
    if (send(fd, http_header, strlen(http_header), 0) < 0)
    {
        //fprintf(stderr, "\nSend failed\n"); // DEBUG
        //exit(1);
    }
    else
    {
        //printf("\nRequest sent\n"); // DEBUG
    }

    // ========================== Receive HTTP response
    int max_buf_len = 16 * 1024;
    unsigned char recv_buf[max_buf_len];

    int header_flag = 1;

    FILE * file;

    while(1)
    {
        int recv_bytes = recv(fd, recv_buf, sizeof(recv_buf), 0);
        recv_buf[recv_bytes] = '\0';
        
        if (recv_bytes < 0)
        {
            //printf("\nReceive failed\n"); // DEBUG
            //exit(1);
        }
        else if (recv_bytes == 0)
        {
            // All data has been recieved
            break;
        }
        else
        {
            unsigned char * cont_ptr = recv_buf; // assume file content starts at buffer

            if (header_flag == 1)
            {
                //printf("\nThis packet is header + some content\n"); // DEBUG

                // Get first line and check if HTTP response is valid
                char fl[100];
                memcpy(fl, recv_buf, 100 * sizeof(char)); // copy(first line + some) since strtok() modifies input string
                char * firstline = strtok(fl, "\r\n"); // extract first line from copy
                if (strstr(firstline, "200") == NULL) // code 200 = valid response
                {
                    fprintf(stdout, "%s\n", firstline);
                    exit(1);
                }

                // check for "Content-Length" field in header
                if (strstr(recv_buf, "Content-Length") == NULL)
                {
                    fprintf(stdout, "Error: could not download the requested file (file length unknown)\n");
                    exit(1);
                }

                // Extract filename from filepath, and open a file with said name
                char* fname = strrchr(fpath, '/');
                fname++;
                file = fopen(fname, "w+");

                // Update file content pointer to be the newline after header
                cont_ptr = strstr(recv_buf, "\r\n\r\n");
                cont_ptr += 4;
                
                // Get number of bytes for content in packet write into file
                int header_bytes = cont_ptr - recv_buf;
                int cont_bytes = recv_bytes - header_bytes;
                fwrite(cont_ptr, cont_bytes, 1, file);

                // recieved header, so set flag to 0
                header_flag = 0;
            }
            else
            {
                // Write recieved content into file
                fwrite(cont_ptr, recv_bytes, 1, file);
            }

            //printf("\nReceive success: %d bytes\n", recv_bytes); // DEBUG
            //printf("%s", recv_buf); // DEBUG
        }
    }

    fclose(file);
    return 0;
}