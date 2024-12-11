#pragma once

#include"clsPerson.h"
#include"clsString.h"
#include<string>
#include<vector>
#include<fstream>
#include"clsDate.h"

class clsBankClient : public clsPerson
{
private:

	enum _enMode { _EmptyMode = 1, _UpdateMode = 2, _AddNewMode };
	_enMode _Mode;

	string _AccountNumber;
	double _AccountBalance;
	string _PinCode;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Delim = "#//#")
	{
		vector <string> vClient = clsString::Split(Line, Delim);

		return clsBankClient(_enMode::_UpdateMode, vClient[0], vClient[1], vClient[2],
			vClient[3], vClient[4], vClient[5], stod(vClient[6]));
	};

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(_enMode::_EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient>	vClients;

		fstream File;

		File.open("Clients.txt", ios::in);

		if (File.is_open())
		{
			string line;

			while (getline(File, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);
				vClients.push_back(Client);
			}

			File.close();
		}

		return vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Delim = "#//#")
	{
		string line;

		line += Client.FirstName + Delim;
		line += Client.LastName + Delim;
		line += Client.Email + Delim;
		line += Client.Phone + Delim;
		line += Client.AccountNumber() + Delim;
		line += Client.PinCode + Delim;
		line += to_string(Client.AccountBalance);
		return line;
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream File;

		File.open("Clients.txt", ios::out);

		if (File.is_open())
		{
			string line;

			for (clsBankClient C : vClients)
			{
				if (C.MarkedForDelete() == false)
				{
					line = _ConvertClientObjectToLine(C);
					File << line << endl;
				}

			}

			File.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string Line)
	{
		fstream File;

		File.open("Clients.txt", ios::out | ios::app);

		if (File.is_open())
		{
			File << Line << endl;

			File.close();
		}
	}

	void _AddNew()
	{
		return _AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRecord(clsBankClient DestinationClient, double Amount,
		string Username, string Delim = "#//#")
	{
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Delim;
		TransferLogRecord += _AccountNumber + Delim;
		TransferLogRecord += DestinationClient.AccountNumber() + Delim;
		TransferLogRecord += to_string(Amount) + Delim;
		TransferLogRecord += to_string(_AccountBalance) + Delim;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Delim;
		TransferLogRecord += Username;
		

		return TransferLogRecord;
	}

	void _RegisterTransferLog(clsBankClient DestinationClient, double Amount, string Username)
	{
		string DataLine = _PrepareTransferLogRecord(DestinationClient, Amount, Username);

		fstream File;
		File.open("TransferLog.txt", ios::out | ios::app);

		if (File.is_open())
		{
			File << DataLine << endl;

			File.close();
		}
	}

	struct stTransferLogRecord;

	static stTransferLogRecord _ConvertTransferLogLineToRecord(string line,
		string Delim = "#//#")
	{
		stTransferLogRecord TransferLogRecord;

		vector <string> vTransferLogRecord = clsString::Split(line, Delim);

		TransferLogRecord.DateTime = vTransferLogRecord[0];
		TransferLogRecord.SourceAccountNumber = vTransferLogRecord[1];
		TransferLogRecord.DestinationAccountNumber = vTransferLogRecord[2];
		TransferLogRecord.Amount = stod(vTransferLogRecord[3]);
		TransferLogRecord.srcBalanceAfter = stod(vTransferLogRecord[4]);
		TransferLogRecord.DesBalanceAfter = stod(vTransferLogRecord[5]);
		TransferLogRecord.Username = vTransferLogRecord[6];

		return TransferLogRecord;
	}
	

public:

	struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount;
		double srcBalanceAfter;
		double DesBalanceAfter;
		string Username;
	};

	clsBankClient(_enMode Mode, string FirstName, string LastName, string Email, string
		phone, string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, phone)
	{

		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	bool MarkedForDelete()
	{
		return _MarkForDelete;
	}

	static clsBankClient Find(string AccountNumber)
	{
		fstream File; vector <clsBankClient> vClients;

		File.open("Clients.txt", ios::in);

		if (File.is_open())
		{
			string line;
			
			while (getline(File, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);
				
				if (Client._AccountNumber == AccountNumber)
				{
					File.close();
					return Client;
				}

				vClients.push_back(Client);
			}

			File.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream File; vector <clsBankClient> vClients;

		File.open("Clients.txt", ios::in);

		if (File.is_open())
		{
			string line;

			while (getline(File, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);

				if (Client._AccountNumber == AccountNumber && Client._PinCode == PinCode)
				{
					File.close();
					return Client;
				}

				vClients.push_back(Client);
			}

			File.close();
		}

		return _GetEmptyClientObject();
	}

	bool IsEmpty()
	{
		return (_Mode == _enMode::_EmptyMode);
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	// No UI Related code inside object. 
	//void Print()
	//{

	//	cout << "\nInfo:";
	//	cout << "\n___________________";
	//	cout << "\nFirstName      : " << FirstName;
	//	cout << "\nLastName       : " << LastName;
	//	cout << "\nFull Name      : " << FullName();
	//	cout << "\nEmail          : " << Email;
	//	cout << "\nPhone          : " << Phone;
	//	cout << "\nAccountNumber  : " << _AccountNumber;
	//	cout << "\nPinCode        : " << _PinCode;
	//	cout << "\nAccountBalance : " << _AccountBalance;
	//	cout << "\n___________________\n";
	//}

	enum enSaveResults{svFaildEptyObject = 0, svSucceded = 1, svFaildAccountNumberExists};

   	enSaveResults Save()
	{
		switch (_Mode)
		{
		case _enMode::_EmptyMode:
		{

			return enSaveResults::svFaildEptyObject;
			break;
		}

		case _enMode::_UpdateMode:
		{
			
			_Update();

			return enSaveResults::svSucceded;

			break;
		}

		case _enMode::_AddNewMode:

			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				_Mode = _enMode::_UpdateMode;

				return enSaveResults::svSucceded;

				break;
			}
		}
	}

	static clsBankClient GetAddNewClient(string AccountNumber)
	{
		return clsBankClient(_enMode::_AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	 bool Delete()
	 {
		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	 }

	 static vector <clsBankClient> GetClientsList()
	 {
		 return _LoadClientsDataFromFile();
	 }

	 static double GetTotalBalances()
	 {
		 vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		 double TotalBalances = 0;

		 for (clsBankClient Client : vClients)
		 {

			 TotalBalances += Client.AccountBalance;
		 }

		 return TotalBalances;

	 }

	 void Deposit(double Amount)
	 {

		 _AccountBalance += Amount;
		 Save();
	 }

	 bool Withdraw(double Amount)
	 {
		 if (Amount > _AccountBalance)
		 {
			 return false;
		 }
		 else
		 {
			 _AccountBalance -= Amount;
			 Save();
		 }
	 }

	 bool Transfer(double Amount, clsBankClient& DestinationClient, string Username)
	 {
		 if (Amount > AccountBalance)
		 {
			 return false;
		 }

		 Withdraw(Amount);
		 DestinationClient.Deposit(Amount);
		 _RegisterTransferLog(DestinationClient, Amount, Username);

		 return true;
	 }

	 static vector <stTransferLogRecord> GetTransfersLogList()
	 {
		 vector <stTransferLogRecord> vTransferLogRecord;

		 fstream File;
		 File.open("Transferlog.txt", ios::in);

		 if (File.is_open())
		 {
			 string line;

			 stTransferLogRecord TransferRecord;

			 while (getline(File, line))
			 {
				 TransferRecord = _ConvertTransferLogLineToRecord(line);

				 vTransferLogRecord.push_back(TransferRecord);
			 }

			 File.close();
		 }

		 return vTransferLogRecord;
	 }
};