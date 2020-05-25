#include "version.h"

#define __BDATE__      "2020-05-25 17:11:26"
#define __BVERSION__   "1.5.005"

const char * getVersion()
{
    return __BVERSION__;
}

const char * getBuildDate()
{
    return __BDATE__;
}
