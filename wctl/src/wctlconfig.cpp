#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "wctlconfig.h"
#include "exception.h"
#include "logger.h"

using namespace std;

WCTLConfig::WCTLConfig()
{
    queryConfig();
}

void WCTLConfig::queryConfig()
{
	FILE *		fptr;
	char *		pszToken;
	char *		config;
    long int    fileLength;
	int			i = 0;

    Logger & log = Logger::getInstance();

	fptr = fopen(CONFIG_NAME, "rt");

	if (fptr == NULL) {
		throw new Exception("ERROR reading config");
	}

    /*
    ** Get length of config file...
    */
    fseek(fptr, 0L, SEEK_END);
    fileLength = ftell(fptr);
    rewind(fptr);

    config = (char *)malloc((fileLength + 1) * sizeof(char));

    if (config == NULL) {
        throw new Exception("ERROR: failed to allocate config memory");
    }

	do {
		config[i++] = (char)fgetc(fptr);
	}
	while (!feof(fptr));

	config[i] = 0;

	fclose(fptr);

	pszToken = strtok(config, "=\n\r ");

	while (pszToken != NULL) {
        keys.push_back(pszToken);

        log.logDebug("Got key [%s]", pszToken);

        pszToken = strtok(NULL, "=\n\r ");

        values.push_back(pszToken);

        log.logDebug("value [%s]", pszToken);

        pszToken = strtok(NULL, "=\n\r ");
	}

    free(config);
}

string & WCTLConfig::getValue(string & key)
{
    static string empty = "";

    int         i;

    for (i = 0;i < keys.size();i++) {
        if (keys.at(i) == key) {
            return values.at(i);
        }
    }

    return empty;
}