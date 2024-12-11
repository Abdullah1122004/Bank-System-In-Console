#pragma once

#include"clsScreen.h"
#include"vector"
#include"clsUser.h"
#include"clsString.h"
#include<iomanip>

class clsLoginRegisterScreen : protected clsScreen
{

	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterLogin)
	{

		cout << setw(8) << left << "" << "| " << setw(30) << left << LoginRegisterLogin.Date_Time;
		cout << "| " << setw(20) << left << LoginRegisterLogin.UserName;
		cout << "| " << setw(15) << left << LoginRegisterLogin.Password;
		cout << "| " << setw(10) << left << LoginRegisterLogin.Permissions;
	}

public:

	static void ShowLoginRegisterScreen()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
		{
			return;
		}

		vector <clsUser::stLoginRegisterRecord> vLoginReisterRecord = clsUser::GetLoginRegisterList();


		string Title = "\tLogin Register List Screen\n";
		string SubTitle = "\t\t(" + to_string(vLoginReisterRecord.size()) + ") Record(s)";

		clsScreen::_DrawScreenHeader(Title, SubTitle);


		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
		cout << "| " << left << setw(20) << "Username";
		cout << "| " << left << setw(15) << "Password";
		cout << "| " << left << setw(10) << "permissions";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vLoginReisterRecord.size() == 0)
		{
			cout << "\t\t\t\tNo Users Available In the System!";
		}

		for (clsUser::stLoginRegisterRecord LoignRegesterRecord : vLoginReisterRecord)
		{
			_PrintLoginRegisterRecordLine(LoignRegesterRecord);

			cout << endl;
		}

	}
};

