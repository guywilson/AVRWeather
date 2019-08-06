#include <stdlib.h>
#include <string.h>

#include "mongoose.h"
#include "exception.h"

#ifndef _INCL_WEBCONNECT
#define _INCL_WEBCONNECT

#define WEB_PATH_AVG		"avg-tph"
#define WEB_PATH_MIN		"min-tph"
#define WEB_PATH_MAX		"max-tph"

class PostData
{
private:
	char *		pszBody;
	char *		pszPath;

public:
	PostData() {
	}

	PostData(char * path, char * body) : PostData() {
		setPath(path);
		setBody(body);
	}

	~PostData() {
		free(this->pszPath);
		free(this->pszBody);
	}

	char *		getBody() {
		return this->pszBody;
	}
	void		setBody(char * body) {
		this->pszBody = (char *)malloc(strlen(body));

		if (this->pszBody == NULL) {
			throw new Exception("Failed to allocate memeory for post data");
		}

		memcpy(this->pszBody, body, strlen(body));
		this->pszBody[strlen(body)] = 0;
	}
	char *		getPath() {
		return this->pszPath;
	}
	void		setPath(char * path) {
		this->pszPath = (char *)malloc(strlen(path));

		if (this->pszPath == NULL) {
			throw new Exception("Failed to allocate memeory for post data");
		}

		memcpy(this->pszPath, path, strlen(path));
		this->pszPath[strlen(path)] = 0;
	}
};

class WebConnector
{
public:
	static WebConnector & getInstance()
	{
		static WebConnector instance;
		return instance;
	}

private:
	char			szHost[256];
	int				port;
	char			szListenPort[8];
	char			szBasePath[128];

	struct mg_mgr			mgr;
	struct mg_connection *	connection;

	WebConnector();

	void		queryConfig();
	void		setupListener();

public:
	void		postTPH(const char * pszPathSuffix, bool save, char * pszTemperature, char * pszPressure, char * pszHumidity);
	void		registerHandler(const char * pszURI, void (* handler)(struct mg_connection *, int, void *));
	void		listen();

	char *		getHost() {
		return this->szHost;
	}
	int			getPort() {
		return this->port;
	}
};

void * webPostThread(void * pArgs);

#endif
