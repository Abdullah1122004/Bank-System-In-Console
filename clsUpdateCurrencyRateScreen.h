#pragma once

#include"clsScreen.h"
#include"clsCurrency.h"
#include"clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{

	static void _Print(clsCurrency Currency)
	{
		cout << "\n\nCurrency Card:\n";
		cout << "_______________________________\n";
		cout << "\nCountry     : " << Currency.Country();
		cout << "\nCode        : " << Currency.CurrencyCode();
		cout << "\nName        : " << Currency.CurrencyName();
		cout << "\nRate/(1$)   : " << Currency.Rate();
		cout << "\n______________________________\n";
	}

	static float _ReadRate()
	{
		float NewRate = 0;
		cout << "\nEnter New Rate: ";
		NewRate = clsInputValidate::ReadNumber<float>();

		return NewRate;
	}

public:

	static void ShowUpdateCurrencyScreen()
	{
		clsScreen::_DrawScreenHeader("\tUpdate Currency Screen");

		string CurrencyCode = "";
		cout << "\nPlease enter Currency code: ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, please enter another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_Print(Currency);


		char Answer = 'n';
		cout << "\nAre you sure you want to Update the rate of this Currecny? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			

			cout << "\nUpdate Currency Rate: \n";
			cout << "\n_________________________\n";
			
			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_Print(Currency);
		}
	}
};          