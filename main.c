#include "titans.h"

int main (int argc, char *argv[])
{
	int ret;
	int i;

	ret = 0;
	i = 1;
	if (argc == 1)
	{
		switch (i)
		{
			case 1:
				printf("getBalance:\t%s 1 <publicAddress>\n", argv[0]);
			case 2:
				printf("unForbidden:\t%s 2 <publicAddress>\n", argv[0]);
			case 3:
				printf("unlockAccount:\t%s 3 <publicAddres> <password>\n", argv[0]);
			case 4:
				printf("withdrawReward:\t%s 4 <fromAddress> <delegateAddress>\n", argv[0]);
			default:
				printf("\n");
		}
	}
	else
	{
		if (atoi(argv[1]) == 1 && argc == 3)
			ret = getBalance(argv[2]);
		else if (atoi(argv[1]) == 2 && argc == 3)
			ret = unForbidden(argv[2]);
		else if (atoi(argv[1]) == 3 && argc == 4)
			ret = unlockAccount(argv[2], argv[3]);
		else if (atoi(argv[1]) == 4 && argc == 4)
			ret = withdrawReward(argv[2], argv[3]);
		else
			printf("Error\n");
	}
	if (ret != 0)
		printf("An error occured. Return code: %d\n", ret);
	// printf("ret = %d\n", ret); // debug
	return (ret);
}
