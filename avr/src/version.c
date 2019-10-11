#include "version.h"

#define __BDATE__      "2019-10-11 21:55:31"
#define __BVERSION__   "1.4.007"

const char * getVersion()
{
    return __BVERSION__;
}

const char * getBuildDate()
{
    return __BDATE__;
}
