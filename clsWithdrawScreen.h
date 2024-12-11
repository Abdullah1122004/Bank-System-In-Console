#pragma once

#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
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

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";

        cout << "\nEnter Account Number you want: ";
        AccountNumber = clsInputValidate::ReadString();

        return AccountNumber;
    }

public:
    static void ShowDepsitScreen()
    {
        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number Not Found, enter another one. \n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);

        cout << "\nEnter Amount You want Deposit it ";
        double Amount = clsInputValidate::ReadNumber <double> ();

        cout << "\nAre you sure you want to perform this transaction? y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nAmount Withdraw Successfuly.\n";
                cout << "\n New Balance is: " << Client.AccountBalance;
            }
            else
            {
                cout << "\nCannot Withdraw, Insuffecient Balance!\n";
                cout << "\nAmount to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client.AccountBalance;
            }

        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};

