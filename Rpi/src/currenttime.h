#include <time.h>

#ifndef _INCL_CURRENTTIME
#define _INCL_CURRENTTIME

class CurrentTime
{
public:
	static CurrentTime & getInstance()
	{
		static CurrentTime instance;
		return instance;
	}

private:
	CurrentTime();

	struct tm *		localTime;
	char			szTimeStr[20];


public:
	time_t			updateTime();
	time_t			updateTime(time_t * t);

	char *			getTimeStamp();

	int				getYear();
	int				getMonth();
	int				getDay();

	int				getHour();
	int				getMinute();
	int				getSecond();
};

#endif
