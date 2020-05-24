#include "version.h"

#define __BDATE__      "2020-05-24 09:40:39"
#define __BVERSION__   "1.5.004"

const char * getVersion()
{
    return __BVERSION__;
}

const char * getBuildDate()
{
    return __BDATE__;
}
