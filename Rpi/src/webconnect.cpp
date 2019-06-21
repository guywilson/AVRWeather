#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "exception.h"
#include "webconnect.h"

#define INT_LENGTH				10

//#define TEST_WEB

#ifdef TEST_WEB
int main(void)
{
	try {
		WebConnector & web = WebConnector::getInstance();

		web.postAvgTPH("19.98", "1008.25", "57.32");
	}
	catch (Exception * e) {
		cout << "Caught exception " << e->getMessage() << endl;
	}
}
#endif

void WebConnector::queryConfig()
{
	FILE *		fptr;
	char *		pszToken;
	char		config[1024];
	int			i = 0;

	fptr = fopen("./webconfig.cfg", "rt");

	if (fptr == NULL) {
		throw new Exception("ERROR reading config");
	}

	do {
		config[i++] = (char)fgetc(fptr);
	}
	while (!feof(fptr));

	config[i] = 0;

	fclose(fptr);

	pszToken = strtok(config, "=\n\r ");

	while (pszToken != NULL) {
		if (strcmp(pszToken, "host") == 0) {
			pszToken = strtok(NULL, "=\n\r ");

			strcpy(this->szHost, pszToken);
		}
		else if (strcmp(pszToken, "port") == 0) {
			pszToken = strtok(NULL, "=\n\r ");

			this->port = atoi(pszToken);
		}
		else {
			pszToken = strtok(NULL, "=\n\r ");
		}
	}
}

void WebConnector::post(const char * pszHost, const int port, const char * pszPath, char * pszBody)
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
	message_size += strlen(pszMsgTemplate) + INT_LENGTH;
	message_size += strlen(pszPath);
	message_size += strlen(pszBody);

    /* allocate space for the message */
    message = (char *)malloc(message_size);

    if (message == NULL) {
    	throw new Exception("ERROR allocating message buffer");
    }

    /* fill in the parameters */
	sprintf(message, pszMsgTemplate, pszPath, strlen(pszBody));
	strcat(message, pszBody);

    /* What are we going to send? */
//    printf("Request:\n%s\n", message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
    	throw new Exception("ERROR opening socket");
    }

    /* lookup the ip address */
    server = gethostbyname(pszHost);

    if (server == NULL) {
    	throw new Exception("ERROR, no such host");
    }

    /* fill in the structure */
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    /* connect the socket */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        throw new Exception("ERROR connecting");
    }

    /* send the request */
    total = strlen(message);

    sent = 0;

    do {
        bytes = write(sockfd, message + sent, total - sent);

        if (bytes < 0) {
            throw new Exception("ERROR writing message to socket");
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
            throw new Exception("ERROR reading response from socket");
        }

        if (bytes == 0) {
            break;
        }

        received += bytes;
    }
    while (received < total);

    if (received == total) {
        throw new Exception("ERROR storing complete response from socket");
    }

    /* close the socket */
    close(sockfd);

    /* process response */
//    printf("Response:\n%s\n",response);

    free(message);
}

void WebConnector::postAvgTPH(char * pszTemperature, char * pszPressure, char * pszHumidity)
{
	char		szBody[1024];

	sprintf(
		szBody,
		"{\n\t\"temperature\": \"%s\",\n\t\"pressure\": \"%s\",\n\t\"humidity\": \"%s\"\n}",
		pszTemperature,
		pszPressure,
		pszHumidity);

	post(this->szHost, this->port, WEB_PATH_AVG, szBody);
}

void WebConnector::postMinTPH(char * pszTemperature, char * pszPressure, char * pszHumidity)
{
	char		szBody[1024];

	sprintf(
		szBody,
		"{\n\t\"temperature\": \"%s\",\n\t\"pressure\": \"%s\",\n\t\"humidity\": \"%s\"\n}",
		pszTemperature,
		pszPressure,
		pszHumidity);

	post(this->szHost, this->port, WEB_PATH_MIN, szBody);
}

void WebConnector::postMaxTPH(char * pszTemperature, char * pszPressure, char * pszHumidity)
{
	char		szBody[1024];

	sprintf(
		szBody,
		"{\n\t\"temperature\": \"%s\",\n\t\"pressure\": \"%s\",\n\t\"humidity\": \"%s\"\n}",
		pszTemperature,
		pszPressure,
		pszHumidity);

	post(this->szHost, this->port, WEB_PATH_MAX, szBody);
}

WebConnector::WebConnector()
{
	queryConfig();
}
