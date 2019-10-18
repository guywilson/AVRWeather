#include "version.h"

#define __BDATE__      "2019-10-18 07:31:26"
#define __BVERSION__   "1.5.002"

const char * getVersion()
{
    return __BVERSION__;
}

const char * getBuildDate()
{
    return __BDATE__;
}
