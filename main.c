#include "titans.h"

void	show_Help(char	**argv)
{
	printf("getBalance:\t%1$s 1 <publicAddress>\n"
	"unForbidden:\t%1$s 2 <publicAddress>\n"
	"unlockAccount:\t%1$s 3 <publicAddres> <password>\n"
	"withdrawReward:\t%1$s 4 <fromAddress> <delegateAddress>\n"
	"...\n", argv[0]);
}

int main (int argc, char *argv[])
{
	int ret;

	ret = 0;
	if (argc == 1)
		show_Help(argv);
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
			show_Help(argv);
	}
	if (ret != 0)
		printf("An error occured. Return code: %d\n", ret);
	// printf("ret = %d\n", ret); // debug
	return (ret);
}
