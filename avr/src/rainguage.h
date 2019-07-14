#ifndef _INCL_RAINGUAGE
#define _INCL_RAINGUAGE

#define RAINGUAGE_CHANNEL				 1
#define RAINGUAGE_AVG_COUNT				64

void 	rainGuageTask(PTASKPARM p);
int		getRainfall(char * pszDest);

#endif