#pragma once

#include"clsString.h"
#include<string>
#include<vector>
#include<fstream>

class clsCurrency
{

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;


	static clsCurrency _ConvertLineToCurrencyObject(string Line,
		string Seperator = "#//#")
	{
		vector <string> vCurrency = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrency[0], vCurrency[1],
			vCurrency[2], stof(vCurrency[3]));
	}

	static vector <clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector <clsCurrency> vCurrencys;

		fstream File;
		File.open("Currencies.txt", ios::in);

		if (File.is_open())
		{
			string line;

			while (getline(File, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);

				vCurrencys.push_back(Currency);
			}

			File.close();
		}

		return vCurrencys;
	}

	string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Sepertor = "#//#")
	{
		string line;

		line += Currency.Country() + Sepertor;
		line += Currency.CurrencyCode() + Sepertor;
		line += Currency.CurrencyName() + Sepertor;
		line += to_string(Currency.Rate()) + Sepertor;

		return line;
	}

	void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys)
	{
		fstream File;
		File.open("Currencies.txt", ios::out);

		if (File.is_open())
		{
			string line;

			for (clsCurrency& C : vCurrencys)
			{
				line = _ConvertCurrencyObjectToLine(C);

				File << line << endl;
			}

			File.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> vCurrencys;

		for (clsCurrency C : vCurrencys)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(vCurrencys);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string
		CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	static vector <clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrencyDataFromFile();
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	string Country()
	{
		return _Country;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;

		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);

				if (Currency.CurrencyCode() == CurrencyCode)
				{
					file.close();
					return Currency;
				}
			}

			file.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);

				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					file.close();
					return Currency;
				}
			}

			file.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);

		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.Rate());

	}

};