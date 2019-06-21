#ifndef _INCL_WEBCONNECT
#define _INCL_WEBCONNECT

#define WEB_PATH_AVG		"/api/avg-tph"
#define WEB_PATH_MIN		"/api/min-tph"
#define WEB_PATH_MAX		"/api/max-tph"

class WebConnector
{
public:
	static WebConnector & getInstance()
	{
		static WebConnector instance;
		return instance;
	}

private:
	char			szTimeStr[20];
	char			szHost[256];
	int				port;

	WebConnector();

	char *		getTimeStamp();
	void		queryConfig();
	void		post(
					const char * pszHost,
					const int port,
					const char * pszPath,
					char * pszBody);

public:
	void postAvgTPH(char * pszTemperature, char * pszPressure, char * pszHumidity);
	void postMinTPH(char * pszTemperature, char * pszPressure, char * pszHumidity);
	void postMaxTPH(char * pszTemperature, char * pszPressure, char * pszHumidity);
};

#endif
