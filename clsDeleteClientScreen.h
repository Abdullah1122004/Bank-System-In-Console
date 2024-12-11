#pragma once

#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
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

	static void ShowDeleteClientScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }

		clsScreen::_DrawScreenHeader("\tDelete Client");

		string AccountNumber = "";
        cout << "\nPlease Enter Account Number you want to delete : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Not Found, Please Enter another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);

        cout << "\nAre you sure you want delete this Client? y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully.";
            }
            else
            {
                cout << "\nClient Delete falid.";
            }
        }

	}
};

