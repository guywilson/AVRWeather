#include "version.h"

#define __BDATE__      "2019-09-24 22:46:18"
#define __BVERSION__   "1.2.003"

const char * getVersion()
{
    return __BVERSION__;
}

const char * getBuildDate()
{
    return __BDATE__;
}
