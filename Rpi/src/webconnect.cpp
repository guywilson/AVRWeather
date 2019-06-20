#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "webconnect.h"

#define WEB_HOST			"localhost"
#define WEB_PORT			3000
#define WEB_PATH_AVG		"/api/avg-tph"
#define WEB_PATH_MIN		"/api/min-tph"
#define WEB_PATH_MAX		"/api/max-tph"

#ifdef TEST_WEB
int main(void)
{
	postAvgTPH("19.98", "1008.25", "57.32");
}
#endif

int post(const char * pszHost, const int port, const char * pszPath, char * pszBody)
{
    struct hostent *	server;
    struct sockaddr_in 	serv_addr;
    int					sockfd;
    int					bytes;
    int					sent;
    int					received;
    int					total;
    int					message_size;
    char *				message;
    char				response[4096];
    const char *		pszMsgTemplate = "POST %s HTTP/1.0\r\nContent-Type: application/json\r\nContent-Length: %ld\r\n\r\n";

     /* How big is the message? */
    message_size = 0;
	message_size += strlen(pszMsgTemplate) + 10;
	message_size += strlen(pszPath);
	message_size += strlen(pszBody);

    /* allocate space for the message */
    message = (char *)malloc(message_size);

    if (message == NULL) {
    	printf("ERROR allocating message buffer\n");
    	return -1;
    }
    /* fill in the parameters */
	sprintf(message, pszMsgTemplate, pszPath, strlen(pszBody));
	strcat(message, pszBody);

    /* What are we going to send? */
    printf("Request:\n%s\n", message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
    	printf("ERROR opening socket\n");
    	return -1;
    }

    /* lookup the ip address */
    server = gethostbyname(pszHost);

    if (server == NULL) {
    	printf("ERROR, no such host\n");
    	return -1;
    }

    /* fill in the structure */
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    /* connect the socket */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("ERROR connecting\n");
        return -1;
    }

    /* send the request */
    total = strlen(message);

    sent = 0;

    do {
        bytes = write(sockfd, message + sent, total - sent);

        if (bytes < 0) {
            printf("ERROR writing message to socket\n");
            return -1;
        }

        if (bytes == 0) {
            break;
        }

        sent += bytes;
    }
    while (sent < total);

    /* receive the response */
    memset(response, 0, sizeof(response));

    total = sizeof(response) - 1;

    received = 0;

    do {
        bytes = read(sockfd, response + received, total - received);

        if (bytes < 0) {
            printf("ERROR reading response from socket\n");
            return -1;
        }

        if (bytes == 0) {
            break;
        }

        received += bytes;
    }
    while (received < total);

    if (received == total) {
        printf("ERROR storing complete response from socket\n");
        return -1;
    }

    /* close the socket */
    close(sockfd);

    /* process response */
    printf("Response:\n%s\n",response);

    free(message);

    return 0;
}

int postAvgTPH(char * pszTemperature, char * pszPressure, char * pszHumidity)
{
	char		szBody[1024];

	sprintf(
		szBody,
		"{\n\t\"temperature\": \"%s\",\n\t\"pressure\": \"%s\",\n\t\"humidity\": \"%s\"\n}",
		pszTemperature,
		pszPressure,
		pszHumidity);

	return post(WEB_HOST, WEB_PORT, WEB_PATH_AVG, szBody);
}

int postMinTPH(char * pszTemperature, char * pszPressure, char * pszHumidity)
{
	char		szBody[1024];

	sprintf(
		szBody,
		"{\n\t\"temperature\": \"%s\",\n\t\"pressure\": \"%s\",\n\t\"humidity\": \"%s\"\n}",
		pszTemperature,
		pszPressure,
		pszHumidity);

	return post(WEB_HOST, WEB_PORT, WEB_PATH_MIN, szBody);
}

int postMaxTPH(char * pszTemperature, char * pszPressure, char * pszHumidity)
{
	char		szBody[1024];

	sprintf(
		szBody,
		"{\n\t\"temperature\": \"%s\",\n\t\"pressure\": \"%s\",\n\t\"humidity\": \"%s\"\n}",
		pszTemperature,
		pszPressure,
		pszHumidity);

	return post(WEB_HOST, WEB_PORT, WEB_PATH_MAX, szBody);
}
