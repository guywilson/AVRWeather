#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "exception.h"
#include "currenttime.h"
#include "webconnect.h"

extern "C" {
#include "mongoose.h"
}

#define INT_LENGTH				10

//#define TEST_WEB

#ifdef TEST_WEB
int main(void)
{
	int				i = 0;
	char			szTemperature[8];
	char			szPressure[8];
	char			szHumidity[8];

	const char * 	temp[24] = {
						"19.54", "21.43", "20.87", "20.46", "20.87", "21.23",
						"19.54", "21.43", "20.87", "20.46", "20.87", "21.23",
						"19.54", "21.43", "20.87", "20.46", "20.87", "21.23",
						"19.54", "21.43", "20.87", "20.46", "20.87", "21.23"
	};

	const char * 	pres[24] = {
						"1008.25", "1009.65", "1009.78", "1010.01", "1011.25", "1011.34",
						"1008.25", "1009.65", "1009.78", "1010.01", "1011.25", "1011.34",
						"1008.25", "1009.65", "1009.78", "1010.01", "1011.25", "1011.34",
						"1008.25", "1009.65", "1009.78", "1010.01", "1011.25", "1011.34"
	};

	const char *	humi[24] = {
						"57.25", "58.54", "58.54", "59.25", "59.87", "60.03",
						"57.25", "58.54", "58.54", "59.25", "59.87", "60.03",
						"57.25", "58.54", "58.54", "59.25", "59.87", "60.03",
						"57.25", "58.54", "58.54", "59.25", "59.87", "60.03"
	};

	try {
		WebConnector & web = WebConnector::getInstance();

		for (i = 0;i < 24;i++) {
			strcpy(szTemperature, temp[i]);
			strcpy(szPressure, pres[i]);
			strcpy(szHumidity, humi[i]);

			web.postAvgTPH(false, szTemperature, szPressure, szHumidity);
		}
	}
	catch (Exception * e) {
		cout << "Caught exception " << e->getMessage() << endl;
	}
}
#endif

static void resetAVRHandler(struct mg_connection * connection, int event, void * p)
{
	struct http_message *			message;
	char *							pszMethod;

	switch (event) {
		case MG_EV_HTTP_REQUEST:
			message = (struct http_message *)p;

			pszMethod = (char *)malloc(message->method.len + 1);

			if (pszMethod == NULL) {
				throw new Exception("Failed to allocate memory for method...");
			}

			memcpy(pszMethod, message->method.p, message->method.len);
			pszMethod[message->method.len] = 0;

			cout << "Got " << pszMethod << " request..." << endl;

			if (strncmp(pszMethod, "POST", 4) == 0) {
				cout << "Resetting AVR..." << endl;
			}

			free(pszMethod);

			mg_printf(connection, "HTTP/1.0 200 OK");
			connection->flags |= MG_F_SEND_AND_CLOSE;
			break;

		default:
			break;
	}
}

static void nullHandler(struct mg_connection * connection, int event, void * p)
{
	struct http_message *	message;
	const char * 			szMsg = "HTTP/1.0 200 OK\r\n\r\n[No handler registered for URI '%s']";
	char *					pszMethod;
	char *					pszURI;

	switch (event) {
		case MG_EV_HTTP_REQUEST:
			message = (struct http_message *)p;

			pszMethod = (char *)malloc(message->method.len + 1);

			if (pszMethod == NULL) {
				throw new Exception("Failed to allocate memory for method...");
			}

			memcpy(pszMethod, message->method.p, message->method.len);
			pszMethod[message->method.len] = 0;

			pszURI = (char *)malloc(message->uri.len + 1);

			if (pszURI == NULL) {
				throw new Exception("Failed to allocate memory for URI...");
			}

			memcpy(pszURI, message->uri.p, message->uri.len);
			pszURI[message->uri.len] = 0;

			cout << "Null Handler: Got " << pszMethod << " request for '" << pszURI << "'" << endl;
			mg_printf(connection, szMsg, pszURI);
			connection->flags |= MG_F_SEND_AND_CLOSE;

			free(pszMethod);
			free(pszURI);
			break;

		default:
			break;
	}
}

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
		else if (strcmp(pszToken, "basepath") == 0) {
			pszToken = strtok(NULL, "=\n\r ");

			strcpy(this->szBasePath, pszToken);
		}
		else if (strcmp(pszToken, "listenport") == 0) {
			pszToken = strtok(NULL, "=\n\r ");

			strcpy(this->szListenPort, pszToken);
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

void WebConnector::postAvgTPH(bool save, char * pszTemperature, char * pszPressure, char * pszHumidity)
{
	char				szBody[128];
	char				szPath[256];

	CurrentTime & time = CurrentTime::getInstance();

	sprintf(
		szBody,
		"{\n\t\"time\": \"%s\",\n\t\"save\": \"%s\",\n\t\"temperature\": \"%s\",\n\t\"pressure\": \"%s\",\n\t\"humidity\": \"%s\"\n}",
		time.getTimeStamp(),
		save ? "true" : "false",
		pszTemperature,
		pszPressure,
		pszHumidity);

//	cout << "Posting Avg TPH JSON: " << endl << szBody << endl << endl;

	strcpy(szPath, this->szBasePath);
	strcat(szPath, WEB_PATH_AVG);

	post(this->szHost, this->port, szPath, szBody);
}

void WebConnector::postMinTPH(bool save, char * pszTemperature, char * pszPressure, char * pszHumidity)
{
	char				szBody[128];
	char				szPath[256];

	CurrentTime & time = CurrentTime::getInstance();

	sprintf(
		szBody,
		"{\n\t\"time\": \"%s\",\n\t\"save\": \"%s\",\n\t\"temperature\": \"%s\",\n\t\"pressure\": \"%s\",\n\t\"humidity\": \"%s\"\n}",
		time.getTimeStamp(),
		save ? "true" : "false",
		pszTemperature,
		pszPressure,
		pszHumidity);

//	cout << "Posting Min TPH JSON: " << endl << szBody << endl << endl;

	strcpy(szPath, this->szBasePath);
	strcat(szPath, WEB_PATH_MIN);

	post(this->szHost, this->port, szPath, szBody);
}

void WebConnector::postMaxTPH(bool save, char * pszTemperature, char * pszPressure, char * pszHumidity)
{
	char				szBody[128];
	char				szPath[256];

	CurrentTime & time = CurrentTime::getInstance();

	sprintf(
		szBody,
		"{\n\t\"time\": \"%s\",\n\t\"save\": \"%s\",\n\t\"temperature\": \"%s\",\n\t\"pressure\": \"%s\",\n\t\"humidity\": \"%s\"\n}",
		time.getTimeStamp(),
		save ? "true" : "false",
		pszTemperature,
		pszPressure,
		pszHumidity);

//	cout << "Posting Max TPH JSON: " << endl << szBody << endl << endl;

	strcpy(szPath, this->szBasePath);
	strcat(szPath, WEB_PATH_MAX);

	post(this->szHost, this->port, szPath, szBody);
}

void WebConnector::setupListener()
{
	struct mg_connection *	connection;

	mg_mgr_init(&mgr, NULL);

	cout << "Setting up listener on port " << szListenPort << endl;

	connection = mg_bind(&mgr, szListenPort, nullHandler);

	if (connection == NULL) {
		throw new Exception("Faled to bind to address");
	}

	cout << "Bound default handler..." << endl;

	/*
	** Register URI handlers...
	*/
	mg_register_http_endpoint(connection, "/api/avr/reset-avr", resetAVRHandler);

	cout << "Registered endpoint handlers..." << endl;

	mg_set_protocol_http_websocket(connection);
}

void WebConnector::listen()
{
	cout << "Listening..." << endl;

	while (1) {
		mg_mgr_poll(&mgr, 1000);
	}

	mg_mgr_free(&mgr);
}

WebConnector::WebConnector()
{
	queryConfig();

	setupListener();
}
