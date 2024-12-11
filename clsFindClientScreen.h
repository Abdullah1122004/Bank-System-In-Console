#pragma once

#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
{

    static void _PrintClientCard(clsBankClient Client)
    {

        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public:

	static void ShowFindClientScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }

		clsScreen::_DrawScreenHeader("\tFind Client");

		cout << "\nEnter Account Number you want to find it: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Not Found, Pleast Enter again: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (!Client.IsEmpty())
        {
            cout << "\nClient Found.\n";
        }
        else
        {
            cout << "\nClient was NOt FOund.\n";
        }

        _PrintClientCard(Client);
	}
};

