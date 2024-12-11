#pragma once

#include"clsScreen.h"
#include"Global.h"
#include"clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{

	static bool _Login()
	{
		bool LoginFaild = false;

		string UserName, Password; short LoginFaildCount = 0;

		do
		{
			if (LoginFaild)
			{
				LoginFaildCount++;

				cout << "\nInvalid Username/Password\n";
				cout << "You have " << 3-LoginFaildCount << " Trials To Login.\n";

			}

			if (LoginFaildCount == 3)
			{
				return false;
			}

			cout << "\nEnter Username: ";
			cin >> UserName;

			cout << "\nEnter Password: ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogin();

		clsMainScreen::ShowMainMenue();

		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		clsScreen::_DrawScreenHeader("\t    Login Screen");

		return _Login();
	}
};

