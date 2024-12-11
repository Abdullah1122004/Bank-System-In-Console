#pragma once

#include"clsScreen.h"
#include "clsCurrency.h"
#include<iomanip>

class clsCurrenciesListScreen : protected clsScreen
{

	static void _PrintCurrencyInfo(clsCurrency Currency)
	{

		cout << setw(15) << left << "" << "| " << setw(40) << left <<
			Currency.Country()
			<< "| " << setw(20) << left << Currency.CurrencyCode() << "| " << setw(39)
			<< left << Currency.CurrencyName() << "| " << setw(20) << left <<
			Currency.Rate();
	}

public:

	static void _ShowCurrenciesListScreen()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		string title = "\tCurrencies list screen\n";
		string suptitle = "\t (" + to_string(vCurrencies.size()) + ") Currency(s).\n";

		clsScreen::_DrawScreenHeader(title, suptitle);

		cout << "\n\n" << setw(15) << left << "" << "____________________________________________";
		cout << "_________________________________________________________________________\n";
		cout << "\n" << setw(15) << left << "" << "| " << setw(40) << left << "Country"
			<< "| " << setw(20) << left << "Code" << "| " << setw(39)
			<< left << "Name" << "| " << setw(20) << left << "Rate/(1$)\n";
		cout << "     ___________________________________________";
		cout << "__________________________________________________________________________\n";

		if (vCurrencies.size() == 0)
		{
			cout << "\t\t\t\tNo Currencies Available in the system.\n";
			return;
		}
		else
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				_PrintCurrencyInfo(Currency);
				cout << endl;
			}
		}

		cout << "     ___________________________________________";
		cout << "__________________________________________________________________________\n";

	}
};

