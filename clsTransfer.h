#pragma once

#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBankClient.h"
#include"Global.h"

class clsTransfer : protected clsScreen
{

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n\nClient Card";
		cout << "\n_____________________\n";
		cout << "\nFull name   : " << Client.FullName();
		cout << "\nAcc.Number  : " << Client.AccountNumber();
		cout << "\nBalance     : " << to_string(Client.AccountBalance);
		cout << endl << "____________________________\n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber;
		cout << "\nPlease Enter Account Number to transfer From: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number not found, enter another one:	";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient SourceClient)
	{

		double Amount = 0;
		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadNumber <double> ();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\n\nAmount Exeeds the available Balance, Enter another Amount:	";
			Amount = clsInputValidate::ReadNumber<double>();
		}

		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
		clsScreen::_DrawScreenHeader("\tTransfer Screen");


		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(SourceClient);


		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(DestinationClient);


		double Amount = _ReadAmount(SourceClient);


		char Answer = 'n';
		cout << "\nAre you sure you want perform this operation? y/n? ";
		cin >> Answer;


		if (Answer == 'y' || Answer == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
			{
				cout << "\n\nTransfer done successfully\n";

				
			}
			else
			{
				cout << "\n\nTransfer falid.\n";
			}
		}

		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);
	}
};