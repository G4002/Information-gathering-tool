#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <hostname>\n", argv[0]);
        return 1;
    }

    char *hostname = argv[1];
    struct hostent *he = gethostbyname(hostname);
    if (he == NULL) {
        herror("gethostbyname");
        return 1;
    }

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, he->h_addr_list[0], ip, sizeof(ip));
    printf("IP address of %s: %s\n\n", hostname, ip);

    // Connect to ipinfo.io
    struct hostent *ipinfo = gethostbyname("ipinfo.io");
    if (ipinfo == NULL) {
        herror("gethostbyname ipinfo.io");
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    server.sin_addr = *(struct in_addr *)ipinfo->h_addr;

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        return 1;
    }

    char request[1024];
    snprintf(request, sizeof(request),
             "GET /%s/json HTTP/1.1\r\nHost: ipinfo.io\r\nConnection: close\r\n\r\n",
             ip);

    send(sockfd, request, strlen(request), 0);

    char response[8192];
    int bytes;
    int started = 0;
    printf("Geolocation JSON:\n");
    while ((bytes = recv(sockfd, response, sizeof(response) - 1, 0)) > 0) {
        response[bytes] = '\0';
        for (int i = 0; i < bytes; i++) {
            if (response[i] == '{') started = 1;
            if (started) putchar(response[i]);
        }
    }
    close(sockfd);

    return 0;
}
