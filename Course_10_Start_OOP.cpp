#include"clsLoginScreen.h"

int main()
{
	
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}

	//clsMainScreen::ShowMainMenue();

	system("pause > 0");

	return 0;
}
