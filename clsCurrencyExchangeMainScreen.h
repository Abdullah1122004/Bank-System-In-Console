#pragma once

#include"clsScreen.h"
#include<iomanip>
#include"clsInputValidate.h"
#include"clsCurrenciesListScreen.h"
#include"clsFindCurrencyScreen.h"
#include"clsUpdateCurrencyRateScreen.h"
#include"clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeMainScreen : protected clsScreen
{

	enum _enCurrencyExchangeOpetions {
		ListCurrencies = 1, FindCurrency = 2,
		UpdateCurrency = 3, CurrencyCalculator = 4, MainMenue = 5
	};

	static short _ReadCurrencyMenueOpetion()
	{
		short Number;
        cout << setw(37) << left << "" << "Choose what do you want to do ? [1 to 5] ? ";
		Number = clsInputValidate::ReadNumberBetween(1, 5);

		return Number;
	}



	static void _GoBackToCurrencyExchangeMenue()
	{
		cout << setw(37) << left << "" << "\n\n\n\tPress any key to go back to Main Menue...\n";
		system("pause > 0");

		ShowCurrencyExchangeMenue();
	}



	static void _ShowListCurrenciesScreen()
	{
		clsCurrenciesListScreen::_ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::_ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyScreen();
	}

	static void _ShowCurrencyCaculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}



	static void _PerformCurrencyMenueOpetions(_enCurrencyExchangeOpetions Option)
	{
		switch (Option)
		{
		case _enCurrencyExchangeOpetions::ListCurrencies:
		{
			system("cls");
			_ShowListCurrenciesScreen();
			_GoBackToCurrencyExchangeMenue();
			break;

		}
		case _enCurrencyExchangeOpetions::FindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		case _enCurrencyExchangeOpetions::UpdateCurrency:
		{
			system("cls");
			_ShowUpdateCurrencyScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		case _enCurrencyExchangeOpetions::CurrencyCalculator:
		{
			system("cls");
			_ShowCurrencyCaculatorScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		case _enCurrencyExchangeOpetions::MainMenue:
		{
			break;
		}
		}
	}

public: 

	static void ShowCurrencyExchangeMenue()
	{

		system("cls");
		_DrawScreenHeader("\tCurrency Exchange Main Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Currency.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformCurrencyMenueOpetions((_enCurrencyExchangeOpetions)_ReadCurrencyMenueOpetion());
	}
};

