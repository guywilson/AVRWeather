#include "mongoose.h"

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
		this->pszBody = NULL;
		this->pszPath = NULL;
	}

	PostData(char * path, char * body) : PostData() {
		this->pszPath = path;
		this->pszBody = body;
	}

	char *		getBody() {
		return this->pszBody;
	}
	void		setBody(char * body) {
		this->pszBody = body;
	}
	char *		getPath() {
		return this->pszPath;
	}
	void		setPath(char * path) {
		this->pszPath = path;
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
