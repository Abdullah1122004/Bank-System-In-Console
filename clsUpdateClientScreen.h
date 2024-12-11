#pragma once

#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen
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

    static void _ReadUpdatedClientData(clsBankClient& Client)
    {
        cout << "\nEnter First Name: "; 
        Client.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();
        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();
        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();
        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadNumber<float>();
    }

public:

	static void ShowUpdateClientScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }

        _DrawScreenHeader("\t  Update Client");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number Not Found, Enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);

        cout << "\nAre you sure you want to Update this Client Info? y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate Client Info:";
            cout << "\n______________________\n";

            _ReadUpdatedClientData(Client);

            clsBankClient::enSaveResults SaveResult;

            SaveResult = Client.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceded:
            {
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClientCard(Client);
                break;
            }
            case clsBankClient::enSaveResults::svFaildEptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;

            }
            case clsBankClient::enSaveResults::svFaildAccountNumberExists:
            {
                cout << "\nError account was not saved because account number is used!\n";
                break;

            }
            }
        }
	}
};