#pragma once

#include"clsScreen.h"
#include"clsCurrency.h"
#include"clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
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

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrecny Found :-)\n";
			_Print(Currency);
		}
		else
		{
			cout << "\n\nCurrency was not found :-(\n";
		}
	}

public:

	static void _ShowFindCurrencyScreen()
	{
		clsScreen::_DrawScreenHeader("\tFind Currency Screen");

		short Number = 0;
		cout << "\n\n[1] Code or [2] Country? ";
		Number = clsInputValidate::ReadNumberBetween(1, 2);

		if (Number == 1)
		{
			string CurrencyCode = "";
			cout << "\nEnter CurrencyCode: ";
			CurrencyCode = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
		}
		else
		{
			string Country = "";
			cout << "\nEnter Country: ";
			Country = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}
	}
};