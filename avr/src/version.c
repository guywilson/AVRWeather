#include "version.h"

#define __BDATE__      "2019-10-16 19:06:44"
#define __BVERSION__   "1.5.001"

const char * getVersion()
{
    return __BVERSION__;
}

const char * getBuildDate()
{
    return __BDATE__;
}
