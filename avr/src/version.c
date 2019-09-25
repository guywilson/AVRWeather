#include "version.h"

#define __BDATE__      "2019-09-25 07:44:03"
#define __BVERSION__   "1.3.001"

const char * getVersion()
{
    return __BVERSION__;
}

const char * getBuildDate()
{
    return __BDATE__;
}
