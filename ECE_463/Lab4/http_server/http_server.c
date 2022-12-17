/* The code is subject to Purdue University copyright policies.
 * DO NOT SHARE, DISTRIBUTE, OR POST ONLINE
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <arpa/inet.h>

#define LISTEN_QUEUE 50 /* Max outstanding connection requests; listen() param */

#define DBADDR "127.0.0.1"


/* FUNCTION: setup 
** PURPOSE: setup connection between http client and server
** VARS:
**      int port: port # server runs on
*/
int setup(int port);
int setup(int port)
{
    /* create socket */
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    /* stops "Adress already in use" error from bind() */
    int optval = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *) &optval, sizeof(int));

    /* bind port to socket */
    struct sockaddr_in serveraddr;
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short) port);
    if (bind(fd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {/*fprinf(stderr, "\nBind error\n"); exit(1); // DEBUG*/}

    /* make server start looking for connection requests */
    listen(fd, LISTEN_QUEUE);

    /* return socket */
    return fd;
}


/* FUNCTION: dbtransfer 
** PURPOSE: handle query requests to db server from client
** VARS:
**      char * searchstr: query/filename from client
**      int clientfd: socket connection to client
**      int dbport: port # database server runs on
*/
void dbtransfer(char * searchstr, int clientfd, int dbport);
void dbtransfer(char * searchstr, int clientfd, int dbport)
{
    /* creake socket connection to database */
    int dbfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    /* setup a timeout feature on the send and recieve operations of db socket */
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(dbfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(dbfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    /* fill in database server's info */
    struct sockaddr_in dbserver;
    dbserver.sin_addr.s_addr = inet_addr(DBADDR);
    dbserver.sin_family = AF_INET;
    dbserver.sin_port = htons(dbport);

    /* send the client query to db server */
    sendto(dbfd, (const char *) searchstr, strlen(searchstr), MSG_CONFIRM, (struct sockaddr *) &dbserver, sizeof(dbserver));

    /* get and process response from db server */
    unsigned char recvbuf[4096]; // 4K size
    int header_flag = 1;
    while (1)
    {
        /* read a response from db server */
        int len;
        int recvbytes = recvfrom(dbfd, (unsigned char *) recvbuf, sizeof(recvbuf), MSG_WAITALL, (struct sockaddr *) &dbserver, &len);
        if (recvbytes < 0) // timeout has occured, send a 408 Request Timeout to client
        {
            char * response = "HTTP/1.0 408 Request Timeout\r\n\r\n<html><body><h1>408 Request Timeout</h1></body></html>";
            send(clientfd, response, strlen(response), MSG_NOSIGNAL);
            fprintf(stdout, "%s\n", "408 Request Timeout");
            break; 
        }
        recvbuf[recvbytes] = '\0';

        /* database does not contain requested file name. send a 404 error to client */
        if (strcmp(recvbuf, "File Not Found") == 0)
        {
            char * response = "HTTP/1.0 404 Not Found\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
            send(clientfd, response, strlen(response), MSG_NOSIGNAL);
            fprintf(stdout, "%s\n", "404 Not Found"); 
            break;
        }
        /* got a "DONE" response from database, stop recieving data */
        else if(strcmp(recvbuf, "DONE") == 0) { break; }
        else
        {
            // if this is first valid send, send HTTP respone header first
            if (header_flag == 1)
            {
                char * header = "HTTP/1.0 200 OK\r\n\r\n";
                send(clientfd, header, strlen(header), MSG_NOSIGNAL);
                fprintf(stdout, "%s\n", "200 OK");
                header_flag = 0;
            }
            // send db data to client
            send(clientfd, recvbuf, recvbytes, MSG_NOSIGNAL);
        }
    }
    
    /* close connection to db */
    close(dbfd);
}


/* FUNCTION: webtransfer 
** PURPOSE: handle query requests to web server from client
** VARS:
**      int clientfd: socket connection to client
**      char * fullpath: full path to file content
*/
void webtransfer(int clientfd, char * fullpath);
void webtransfer(int clientfd, char * fullpath)
{
    /* test if file exists*/
    FILE * readfile = fopen(fullpath, "r+");
    if (readfile == NULL)
    {
        char * response = "HTTP/1.0 404 Not Found\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
        send(clientfd, response, strlen(response), MSG_NOSIGNAL);
        fprintf(stdout, "%s\n", "404 Not Found");
        return;
    }

    /* transmit file */

    // send http response header
    char * header = "HTTP/1.0 200 OK\r\n\r\n";
    send(clientfd, header, strlen(header), MSG_NOSIGNAL);
    fprintf(stdout, "%s\n", "200 OK");

    // send data in chunks
    unsigned char sendbuf[4096];
    while (1)
    {
        int bytesRead = fread(sendbuf, 1, sizeof(sendbuf), readfile);
        if (bytesRead <= 0) {break;}
        send(clientfd, sendbuf, bytesRead, MSG_NOSIGNAL);
    }

    // close file
    fclose(readfile);
}


/* FUNCTION: process 
** PURPOSE: handle data (requests in this case) from client
** VARS:
**      int clientfd: socket connection to client
**      char * webroot: string that represents root folder of web content
**      int dbport: port # database server runs on
*/
void process(int clientfd, char * webroot, int dbport);
void process(int clientfd, char * webroot, int dbport)
{
    /* open client socket as readable byte stream */
    // could also use other methods such as recv() to fetch client data
    FILE * recvstream = fdopen(clientfd, "r+");
    const int RECVSIZE = 2048;
    char recvbuf[RECVSIZE];

    /* fetch the HTTP request first line */
    fgets(recvbuf, RECVSIZE, recvstream);

    char method[RECVSIZE];
    char url[RECVSIZE];
    char version[RECVSIZE];
    sscanf(recvbuf, "%s %s %s \r\n", method, url, version);
    fprintf(stdout, "\"%s %s %s\" ", method, url, version);

    /* test for GET method and for correct HTTP version */
    if (strcmp(method, "GET") != 0 || (strcmp(version, "HTTP/1.0") != 0 && strcmp(version, "HTTP/1.1") != 0))
    {
        // send response to client that server only has GET method implemented
        char * response = "HTTP/1.0 501 Not Implemented\r\n\r\n<html><body><h1>501 Not Implemented</h1></body></html>";
        send(clientfd, response, strlen(response), MSG_NOSIGNAL);
        fprintf(stdout, "%s\n", "501 Not Implemented");

        fclose(recvstream);
        return;
    }

    /* test for url correctness */
    // url should start with '/', i.e /index.html
    // url should not contain ".."
    if (url[0] != '/' || strstr(url, "..") != NULL)
    {
        char * response = "HTTP/1.0 400 Bad Request\r\n\r\n<html><body><h1>400 Bad Request</h1></body></html>";
        send(clientfd, response, strlen(response), MSG_NOSIGNAL);
        fprintf(stdout, "%s\n", "400 Bad Request");

        fclose(recvstream);
        return;
    }
    
    /* dynamic content from database */
    if (strstr(url, "?key=") != NULL)
    {
        /* get the search string, and replace all '+' with ' ' */
        char * searchstr = strstr(url, "?key=") + 5;

        int i = 0;
        while (searchstr[i] != '\0')
        {
            if (searchstr[i] == '+') {searchstr[i] = ' ';}
            i++;
        }
        
        /* communicate with database server to get data to client */
        dbtransfer(searchstr, clientfd, dbport);
    }
    /* static content from webpage */
    else
    {
        /* create a full path to server content by combining the root path with the url */
        char fullpath[100];
        strcpy(fullpath, webroot);
        strcat(fullpath, url);
        
        /* do some processing on full path */
        struct stat path_stat;
        stat(fullpath, &path_stat);
        if (fullpath[strlen(fullpath) - 1] == '/') { strcat(fullpath, "index.html"); } // if last char of full path is '/' append "index.html"
        else if (S_ISREG(path_stat.st_mode) == 0) { strcat(fullpath, "/index.html"); } // if path leads to folder, append "/index.html"

        /* transmit requested web content to client */
        webtransfer(clientfd, fullpath);
    }

    fclose(recvstream);
}


/* FUNCTION: main 
** PURPOSE: main function of server program
** VARS:
**      int argc: # of arguments
**      char *argv[]: array of args
*/
int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: ./http_server [server port] [DB port]\n");
        exit(1);
    }

    /* capture program inputs into vars*/
    int serverport = atoi(argv[1]);
    int dbport = atoi(argv[2]);

    /* setup server-side connection */
    int serverfd = setup(serverport);
    
    /* get the root for the webpage the server references */
    char webroot[100];
    getcwd(webroot, sizeof(webroot));
    strcat(webroot, "/Webpage");
    
    /* main server loop */
    while (1)
    {
        /* accept client socket */
        struct sockaddr_in clientaddr;
        int clientlen = sizeof(clientaddr);
        int clientfd = accept(serverfd, (struct sockaddr *) &clientaddr, &clientlen);

        /* get client IP */
        struct hostent * clientinfo = gethostbyaddr((const char *) &clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        char * clientIP = inet_ntoa(clientaddr.sin_addr);
        fprintf(stdout, "%s ", clientIP);

        /* conduct rest of server processing */
        process(clientfd, webroot, dbport);

        /* terminate connection to client */
        fflush(stdout); // stdout is buffered, so need to flush (force write) before anything is visible on screen
        close(clientfd);
    }
    
    return 0;
}
