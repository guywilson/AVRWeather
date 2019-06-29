#include <string>
#include <vector>

using namespace std;

#ifndef _INCL_WCTLCONFIG
#define _INCL_WCTLCONFIG

#define CONFIG_NAME             "./wctl.cfg"

class WCTLConfig
{
public:
	static WCTLConfig & getInstance()
	{
		static WCTLConfig instance;
		return instance;
	}

private:
    vector<string>  keys;
    vector<string>  values;

    WCTLConfig();
    void            queryConfig();

public:
    ~WCTLConfig();

    string &        getValue(string & key);
};

#endif