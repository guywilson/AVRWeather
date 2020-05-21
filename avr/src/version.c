#include "version.h"

#define __BDATE__      "2020-05-21 17:42:30"
#define __BVERSION__   "1.5.003"

const char * getVersion()
{
    return __BVERSION__;
}

const char * getBuildDate()
{
    return __BDATE__;
}
