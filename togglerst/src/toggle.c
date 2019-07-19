#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gpioc.h>

int main(int argc, char * argv[])
{
    int         rc = 0;
    int         i = 0;
    int         pin = 0;

	if (argc > 1) {
		for (i = 1;i < argc;i++) {
			if (argv[i][0] == '-') {
				if (strcmp(&argv[i][1], "pin") == 0) {
                    pin = atoi(&argv[++i][0]);
				}
			}
		}
	}
	else {
		printf("Usage:\n");
		printf("\toggle -pin [pin No]\n\n");
		return -1;
	}

    rc = gpioc_open();

    gpioc_setPinOff(pin);

    usleep(50L);

    gpioc_setPinOn(pin);

    return 0;
}