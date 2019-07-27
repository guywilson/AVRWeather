#include "mongoose.h"

#ifndef _INCL_WEBCONNECT
#define _INCL_WEBCONNECT

#define WEB_PATH_AVG		"avg-tph"
#define WEB_PATH_MIN		"min-tph"
#define WEB_PATH_MAX		"max-tph"

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
	void		post(
					const char * pszHost,
					const int port,
					const char * pszPath,
					char * pszBody);

	void		setupListener();

public:
	void		postAvgTPH(bool save, char * pszTemperature, char * pszPressure, char * pszHumidity);
	void 		postMinTPH(bool save, char * pszTemperature, char * pszPressure, char * pszHumidity);
	void 		postMaxTPH(bool save, char * pszTemperature, char * pszPressure, char * pszHumidity);

	void		registerHandler(const char * pszURI, void (* handler)(struct mg_connection *, int, void *));
	
	void		listen();
};

#endif
