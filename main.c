/*
	1				getBalance			(char *publicAddress);
	2				unForbidden			(char *publicAddress);
	3				unlockAccount		(char *publicAddress, char *password);
	4				void withdrawReward	(char *fromAddress, char *delegateAddress);
*/

#include "titans.h"

int main (int argc, char *argv[])
{
	 int i;

	 i = 1;
	 if (argc == 1)
	{
		switch (i)
		{
			case 1:
				printf("getBalance:\t%s <1> <publicAddress>\n", argv[0]);
			case 2:
				printf("unForbidden:\t%s <2> <publicAddress>\n", argv[0]);
			case 3:
				printf("unlockAccount:\t%s <3> <publicAddres> <password>\n", argv[0]);
			case 4:
				printf("withdrawReward:\t%s <4> <fromAddress> <delegateAddress>\n", argv[0]);
			default:
				printf("\n");
		}
	}
	return 0;
}