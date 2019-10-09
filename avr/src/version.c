#include "version.h"

#define __BDATE__      "2019-10-09 12:54:13"
#define __BVERSION__   "1.4.003"

const char * getVersion()
{
    return __BVERSION__;
}

const char * getBuildDate()
{
    return __BDATE__;
}
