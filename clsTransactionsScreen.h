#pragma once

#include"clsScreen.h"
#include<string>
#include<iomanip>
#include"clsInputValidate.h"
#include"clsMainScreen.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalancesScreen.h"
#include"clsTransfer.h"
#include"clsTransferLogScreen.h"

class clsTransactionsScreen : protected clsScreen
{

    enum _enTransactionsOptions {
        Deposit = 1, Withdraw = 2, TotalBalances = 3,
        Transfer = 4, TransferLog = 5, MainMenue = 6
    };

    static short _ReadTransactionsMenueOption()
    {
        short Number = 0;

        cout << setw(37) << left << "" << "Choose What do you watnt to do [1 to 6]? ";
        Number = clsInputValidate::ReadNumberBetween(1, 6, "Enter Number Between 1,6");

        return Number;
    }

    static  void _GoBackToTransactionsMenue()
    {
        cout << setw(37) << left << "" << "\n\n\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowTransactionsMenueScreen();
    }

    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepsitScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowDepsitScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _showTransferscreen()
    {
        clsTransfer::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

   static void _PerformTransactionsMenueOptions(_enTransactionsOptions Option)
    {
        switch (Option)
        {
        case _enTransactionsOptions::Deposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case _enTransactionsOptions::Withdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case _enTransactionsOptions::TotalBalances:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case _enTransactionsOptions::Transfer:
        {
            system("cls");
            _showTransferscreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case _enTransactionsOptions::TransferLog:
        {
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case _enTransactionsOptions::MainMenue:
        {
            break;
        }
        }
    }

public:

	static void ShowTransactionsMenueScreen()
	{

        if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
        {
            return;
        }


        system("cls");

        _DrawScreenHeader("\tTransactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tTransactions Menue \n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit\n";
        cout << setw(37) << left << "" << "\t[2] WithDraw\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances\n";
        cout << setw(37) << left << "" << "\t[4] Transfer\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOptions((_enTransactionsOptions)_ReadTransactionsMenueOption());
	}
};

