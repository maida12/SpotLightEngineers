#include<iostream>
#include<fstream>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

class Bill;
class LESCO;
class Costumer;
class Employee;


//     ============================================  HELPER ============================================

class Helper
{

public:
	static void CheckDateValidity(int  year, int  month, int date)
	{
		bool validDate = false;
		int count = 0;
		if (year > 999 && year <= 9999)
		{
			if (month <= 12)
			{
				if (date <= 31)
				{
					validDate = true;
				}
				else validDate = false;
			}

		}

		if (validDate == true)
		{
			return;
		}
		else
		{
			cout << "Invalid Date!Enter again:\n";
			cin >> year >> month >> date;
			CheckDateValidity(year, month, date);
		}


	}
};


//     ============================================  EMPLOYEE ============================================
class Employee
{
	string UserName;
	string Password;
public:
	Employee();
	void LoadDataFromFile(ifstream&);
	void InputEmployeeData(string, string);
	void SaveData(ofstream&);
	bool CheckCredentials(string, string);
	void ChangeStatus();
	~Employee();
};

Employee::Employee()                            // Constructor
{
	UserName = "0";
	Password = "0";
}
                                           // This will get data from "EmployeesData.txt"
void Employee::LoadDataFromFile(ifstream& inputEmployee)
{
	string temp;
	int count = 0;

	getline(inputEmployee, UserName, ',');
	getline(inputEmployee, Password);
}

void Employee::InputEmployeeData(string Name, string Pass)
{

	UserName = Name;
	Password = Pass;
}
                                             // Saving Employees Name and Password
void Employee::SaveData(ofstream& OutputEmployee)
{
	OutputEmployee << UserName << ",";
	OutputEmployee << Password << endl;
}
                                    // This will validate the name and password of the employee  
bool Employee::CheckCredentials(string name, string pass)
{

	return  (name == UserName && Password == pass);
}
										//destructor
Employee::~Employee()
{
}



//     ============================================  TARRIF ============================================

class Tarrif
{
	friend class LESCO;
	friend class Bill;
private:

	int RegularUnitPrice[4];
	int PeakHourUnit_Price[4];
	int Percentage_Tax_Domestic;
	int Percentage_Tax_Commercial;
	int Fixed_Charges_Domestic;
	int Fixed_Charges_Commercial;
public:
	Tarrif()                                        // Constructor 
	{
		for (int i = 0; i < 4; i++)
		{
			RegularUnitPrice[i] = 0;
			PeakHourUnit_Price[i] = 0;
		}
		Percentage_Tax_Domestic = 0;
		Percentage_Tax_Commercial = 0;
		Fixed_Charges_Domestic = 0;
		Fixed_Charges_Commercial = 0;
	}

	                                  // This will load the file (TariffTaxInfo.txt) that contains the taxs information 
	bool LoadTarrifFile()
	{
		string temp;
		ifstream Tariff("TarrifTaxInfo.txt");
		if (Tariff)
		{
			for (int i = 0; i < 4; i++)
			{
				getline(Tariff, temp, ',');


				getline(Tariff, temp, ',');
				RegularUnitPrice[i] = stoi(temp);

				getline(Tariff, temp, ',');
				if (temp == "")
				{
					PeakHourUnit_Price[i] = 0;
				}
				else
					PeakHourUnit_Price[i] = stoi(temp);


				if (i == 0 || i == 2)
				{
					getline(Tariff, temp, ',');
					Percentage_Tax_Domestic = stoi(temp);

					getline(Tariff, temp, '\n');
					Fixed_Charges_Domestic = stoi(temp);
				}
				if (i == 1 || i == 3)
				{
					getline(Tariff, temp, ',');
					Percentage_Tax_Commercial = stoi(temp);

					getline(Tariff, temp, '\n');
					Fixed_Charges_Commercial = stoi(temp);
				}
			}
			return 1;
		}

		else                      //If file not loaded
		{
			cout << endl << "Sorry Tariff File couldn't be open " << endl;
			return 0;
		}

	}
	                                // This will change the taxes percentage if required (by Lesco Employees ) 
	void UpdateTarrifFile()
	{
		system("cls");
		int entered_value = 0;
		cout << "Enter 1- To change Tax Percentage for Domestic Customers\n"
			<< "Enter 2- To change Tax Percentage for Commercial Customers\n"
			<< "Enter 3- To change Fixed Charges for Domestic Customers\n"
			<< "Enter 4- To change Fixed Charges for Commercial Customers\n"
			<< "Enter 5- To change Regular Unit Price\n"
			<< "Enter 6- To change Peak Hour Unit Price\n\n\n";
		cin >> entered_value;
		if (entered_value == 1)
		{
			cout << "Enter Tax Percentage for Domestic Customers";
			cin >> Percentage_Tax_Domestic;
		}
		if (entered_value == 2)
		{
			cout << "Enter Tax Percentage for Commercial Customers";
			cin >> Percentage_Tax_Commercial;
		}
		if (entered_value == 3)
		{
			cout << "Enter Fixed Charges for Domestic Customers";
			cin >> Fixed_Charges_Domestic;
		}
		if (entered_value == 4)
		{
			cout << "Enter  Fixed Charges for Commercial Customers";
			cin >> Fixed_Charges_Commercial;
		}
		system("cls");
		if (entered_value == 5)
		{
			int count;
			cout << "============Regular Unit Price ===============\n\n";
			cout << "Enter 1- Phase 1 and Domestic\n "
				<< "Enter 2- Phase 1 and Commercial\n"
				<< "Enter 3- Phase 3 and Domestic\n"
				<< "Enter 4- Phase 3 and Commercial\n\n";
			cin >> count;
			if (count == 1)
			{
				cout << "Enter Regular Unit Price for Phase 1 Domestic Customers\n";
				cin >> RegularUnitPrice[0];
			}
			if (count == 2)
			{
				cout << "Enter Regular Unit Price for Phase 1 Commercial Customers\n";
				cin >> RegularUnitPrice[1];
			}
			if (count == 3)
			{
				cout << "Enter Regular Unit Price for Phase 3 Domestic Customers\n";
				cin >> RegularUnitPrice[2];
			}
			if (count == 4)
			{
				cout << "Enter Regular Unit Price for Phase 3 Commercial Customers\n";
				cin >> RegularUnitPrice[3];
			}
		}
		if (entered_value == 6)
		{
			int count;
			cout << "============Peak Hour Unit ===============\n\n";
			cout << "Enter 1 Phase 3 Domestic \n"
				<< "Enter 2 Phase 3 Commercial \n\n";
			cin >> count;
			if (count == 1)
			{
				cout << "Enter Peak Hour Unit for Phase 3 Domestic\n ";
				cin >> PeakHourUnit_Price[2];
			}
			if (count == 2)
			{
				cout << "Enter Peak Hour Unit for Phase 3 Commercial\n ";
				cin >> PeakHourUnit_Price[3];
			}
		}

		InputUpdateTarrif();


	}                        
	void InputUpdateTarrif()                    // This file contains the taxes related to phases(1 phase or 3 phase)
	{                                          //  and  commercial or domestic
		ofstream Update("TarrifTaxInfo.txt");
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				Update << "1Phase, "
					<< RegularUnitPrice[i] << ","
					<< PeakHourUnit_Price[i] << ","
					<< Percentage_Tax_Domestic << ","
					<< Fixed_Charges_Domestic << endl;
			}
			if (i == 1)
			{
				Update << "1Phase, "
					<< RegularUnitPrice[i] << ","
					<< PeakHourUnit_Price[i] << ","
					<< Percentage_Tax_Commercial << ","
					<< Fixed_Charges_Commercial << endl;
			}
			if (i == 2)
			{
				Update << "3Phase, "
					<< RegularUnitPrice[i] << ","
					<< PeakHourUnit_Price[i] << ","
					<< Percentage_Tax_Domestic << ","
					<< Fixed_Charges_Domestic << endl;
			}
			if (i == 3)
			{
				Update << "3Phase, "
					<< RegularUnitPrice[i] << ","
					<< PeakHourUnit_Price[i] << ","
					<< Percentage_Tax_Commercial << ","
					<< Fixed_Charges_Commercial << endl;
			}

		}
	}
};

//     ============================================  BILL ============================================

class Bill
{
	Costumer *Consumer;
	Tarrif *TarrifFile;
	int CostumerId;
	int BillMonth;
	int MeterReadingPeak;
	int MeterReadingReg;
	string IssueDate;
	int ElectricityCost;
	int SalesTax;
	int FixedCharges;
	int TotalBill;
	string CurrentMeterReading;
	string DueDate;
	bool billPaidStatus;
	string BillPayementDate;
public:
	Bill();
	int GetId();
	int GetMonth();
	int getMeterReadingPeak();
	int getMeterReadingRegulaer();
	void SetConsumer(Costumer*);
	int CalculationOfBill(int, int, int, int, int, int);
	void GenerateBill(int, int, int, int, int);
	int calculateBillPhase1Domestic(int, int, int, int);
	int  calculateBillPhase3Domestic(int, int, int, int, int, int);
	int  calculateBillPhase1Commercial(int, int, int, int);
	int calculateBillPhase3Commercial(int, int, int, int, int, int);
	void LoadDataFromFile(ifstream&);
	void SaveBillInFile(ofstream &);
	void ChangeBillStatus();
	bool GetBillStatus() ;
	void ShowBill();

	string GetDate();
	~Bill();

};

Bill::Bill()                            // Constructor
{
	Consumer=0;
	TarrifFile=0;
	CostumerId = 0;
	BillMonth = 0;
	MeterReadingPeak = 0;
	MeterReadingReg = 0;
	IssueDate = "";
	ElectricityCost = 0;
	SalesTax = 0;
	FixedCharges = 0;
	TotalBill = 0;
	DueDate = "";
	CurrentMeterReading = "";
	billPaidStatus = 0;
	BillPayementDate = "";
}

int Bill::GetId()
{
	return CostumerId;
}
int Bill::GetMonth()
{
	return BillMonth;
} 
string Bill::GetDate()
{
	return IssueDate;
}										
											// This will take data(customer ID, Billing Month ,Meter Reading Peak etc) from  file "BillInfo.txt"                       
void Bill::LoadDataFromFile(ifstream& inputBill)
{
	char ign;
	inputBill >> CostumerId;
	inputBill >> ign;
	inputBill >> BillMonth;
	inputBill >> ign;
	inputBill >> MeterReadingPeak;
	inputBill >> ign;
	inputBill >> MeterReadingReg;
	inputBill >> ign;
	getline(inputBill, IssueDate, ',');
	inputBill >> ElectricityCost;
	inputBill >> ign;
	inputBill >> SalesTax;
	inputBill >> ign;
	inputBill >> FixedCharges;
	inputBill >> ign;
	inputBill >> TotalBill;
	inputBill >> ign;
	getline(inputBill, DueDate, ',');
	inputBill >> billPaidStatus;
	inputBill >> ign;
	getline(inputBill, BillPayementDate, '\n');
}
void Bill::SetConsumer(Costumer* costumer)
{
	Consumer = costumer;
}
                                              // This function generates the bill by taking input from the customer
void Bill::GenerateBill(int id, int MeterType, int CostumerType, int regUnit, int PeakUnit)
{
	TarrifFile = new Tarrif;
	TarrifFile->LoadTarrifFile();
	//regunit previous meter reading
	CostumerId = id;
	int Year, Month, Day;
	string tempYear, tempMonth, tempDay;
	cout << "Enter Billing Month: ";cin >> BillMonth;
	if (MeterType == 3)
	{
		cout << "Enter Meter Reading PEAK : ";
		cin >> MeterReadingPeak;
		if(MeterReadingPeak<PeakUnit)
		{
			cout<<"Meter reading Peak cannot be Less than previous Month's reading!"<<endl;
			return;
		}
	}
	cout << "Enter Meter Reading REGULAR : ";
	cin >> MeterReadingReg;
	if(MeterReadingReg<regUnit)
	{
		cout<<"Meter reading regular cannot be Less than previous Month's reading!"<<endl;
		return;
	}
	cout << "\nEnter Issue Date of Bill in the format YYYY MM DD :\t";
	cin >> Year >> Month >> Day;
	if(BillMonth!=Month)
	{
		cerr<<"Bill Cannot be Generated As months are not Equal"<<endl;
		return ;
	}
	Helper::CheckDateValidity(Year, Month, Day);
	tempYear = to_string(Year);
	tempMonth = to_string(Month);
	tempDay = to_string(Day);
	if (Month < 10 && Day < 10)
	{
		IssueDate = tempYear + '0' + tempMonth + '0' + tempDay;
	}
	else
		IssueDate = tempYear + tempMonth + tempDay;
	if (Month < 10 && Day>9)
		IssueDate = tempYear + '0' + tempMonth + tempDay;
	if (Day < 10 && Month>9)
		IssueDate = tempYear + tempMonth + '0' + tempDay;


	cout << "\nEnter Due Date of Bill in the format YYYY MM DD :\t";
	cin >> Year >> Month >> Day;
	Helper::CheckDateValidity(Year, Month, Day);
	tempYear = to_string(Year);
	tempMonth = to_string(Month);
	tempDay = to_string(Day);
	if (Month < 10 && Day < 10)
	{
		DueDate = tempYear + '0' + tempMonth + '0' + tempDay;
	}
	else
		DueDate = tempYear + tempMonth + tempDay;
	if (Month < 10 && Day>9)
		DueDate = tempYear + '0' + tempMonth + tempDay;
	if (Day < 10 && Month>9)
		DueDate = tempYear + tempMonth + '0' + tempDay;


	if (MeterType == 1 && CostumerType == 2)//phase1 and domestic
		calculateBillPhase1Domestic(regUnit, TarrifFile->Percentage_Tax_Domestic, TarrifFile->RegularUnitPrice[0], TarrifFile->Fixed_Charges_Domestic);
	if (MeterType == 3 && CostumerType == 2)		//phase3 and domestic
		calculateBillPhase3Domestic(regUnit, PeakUnit, TarrifFile->Percentage_Tax_Domestic, TarrifFile->RegularUnitPrice[2], TarrifFile->Fixed_Charges_Domestic, TarrifFile->PeakHourUnit_Price[2]);
	if (MeterType == 1 && CostumerType == 1)		//phase1 and commercial
		calculateBillPhase1Commercial(regUnit, TarrifFile->Percentage_Tax_Commercial, TarrifFile->RegularUnitPrice[1], TarrifFile->Fixed_Charges_Commercial);
	if (MeterType == 3 && CostumerType == 1)		//phase3 and commercial
		calculateBillPhase3Commercial(regUnit, PeakUnit, TarrifFile->Percentage_Tax_Commercial, TarrifFile->RegularUnitPrice[3], TarrifFile->Fixed_Charges_Commercial, TarrifFile->PeakHourUnit_Price[3]);

	cout << "Bill Generated Successfully!" << endl;
	delete TarrifFile;

}
                                                  // Calculation of Bill for  Phase1 (Domestic) Consumers 
int Bill::calculateBillPhase1Domestic(int regUnit, int taxdomestic, int regUnitPrice, int fixedChargeDomestic)
{
	int cost;
	cost =  MeterReadingReg-regUnit;
	cost = cost * regUnitPrice;
	ElectricityCost = cost;
	SalesTax = taxdomestic;
	cost = (cost*taxdomestic) / 100;
	FixedCharges = fixedChargeDomestic;
	cost = cost + fixedChargeDomestic;
	TotalBill = cost;
	return TotalBill;
}

                                               // Calculation of Bill for  Phase3 (Domestic) Consumers 
int Bill::calculateBillPhase3Domestic(int regUnit, int PeakUnit, int taxdomestic, int regUnitPrice, int fixedChargeDomestic, int PeakUnitPrice)
{
	int cost, peakCost;
		cost = MeterReadingReg-regUnit;
		peakCost = MeterReadingPeak-PeakUnit;

	cost = cost * regUnitPrice;
	peakCost = peakCost * PeakUnitPrice;
	cost = cost + peakCost;
	ElectricityCost = cost;
	cost = (cost*taxdomestic) / 100;
	SalesTax = taxdomestic;
	cost = cost + fixedChargeDomestic;
	FixedCharges = fixedChargeDomestic;
	TotalBill = cost;
	return TotalBill;
}
                                           // Calculation of Bill for  Phase1 (Commercial) Consumers 
int Bill::calculateBillPhase1Commercial(int regUnit, int taxCommercial, int regUnitPriceForCommercial, int fixedChargeCommercial)
{
	int cost;
		cost = MeterReadingReg-regUnit;
	cost = cost * regUnitPriceForCommercial;
	ElectricityCost = cost;
	cost = (cost*taxCommercial) / 100;
	SalesTax = taxCommercial;
	cost += fixedChargeCommercial;
	FixedCharges = fixedChargeCommercial;
	TotalBill = cost;
	return TotalBill;
}

                                          // Calculation of Bill for Phase3 (Commercial) Consumers 
int Bill::calculateBillPhase3Commercial(int regUnit, int PeakUnit, int taxCommercial, int regUnitPrice, int fixedChargeCommercial, int PeakUnitPrice)
{
	int cost, peakCost;
	cost =  MeterReadingReg-regUnit;

	
	peakCost =  MeterReadingPeak-PeakUnit;
	
	cost = cost * regUnitPrice;
	peakCost = peakCost * PeakUnitPrice;
	cost = peakCost + cost;
	ElectricityCost = cost;
	cost = (cost*taxCommercial) / 100;
	SalesTax = taxCommercial;
	cost = cost + fixedChargeCommercial;
	FixedCharges = fixedChargeCommercial;
	TotalBill = cost;
	return TotalBill;
}
int Bill::CalculationOfBill(int regUnit, int merterreading, int peakUnit, int peakreading, int meterType, int CostumType)
{
	
	int TotalAmount = 0;
	TarrifFile = new Tarrif;
	if (TarrifFile->LoadTarrifFile())
	{
		MeterReadingReg = merterreading;
		MeterReadingPeak = peakreading;
		if (MeterReadingReg < regUnit)
		{
			cout << "Meter Reading Regular Cannot be smaller than Previous meter Reading!" << endl;
			return 0;
		}
		if (MeterReadingPeak < peakUnit)
		{
			cout << "Meter Reading  Peak Cannot be smaller than Previous meter Reading!" << endl;
			return 0;
		}
		if (meterType == 1 && CostumType == 2)//phase1 and domestic
			calculateBillPhase1Domestic(regUnit, TarrifFile->Percentage_Tax_Domestic, TarrifFile->RegularUnitPrice[0], TarrifFile->Fixed_Charges_Domestic);
		if (meterType == 3 && CostumType == 2)		//phase3 and domestic
			TotalAmount = calculateBillPhase3Domestic(regUnit, peakUnit, TarrifFile->Percentage_Tax_Domestic, TarrifFile->RegularUnitPrice[2], TarrifFile->Fixed_Charges_Domestic, TarrifFile->PeakHourUnit_Price[2]);
		if (meterType == 1 && CostumType == 1)		//phase1 and commercial
			TotalAmount = calculateBillPhase1Commercial(regUnit, TarrifFile->Percentage_Tax_Commercial, TarrifFile->RegularUnitPrice[1], TarrifFile->Fixed_Charges_Commercial);
		if (meterType == 3 && CostumType == 1)		//phase3 and commercial
			TotalAmount = calculateBillPhase3Commercial(regUnit, peakUnit, TarrifFile->Percentage_Tax_Commercial, TarrifFile->RegularUnitPrice[3], TarrifFile->Fixed_Charges_Commercial, TarrifFile->PeakHourUnit_Price[3]);
		return TotalAmount;
	}
	else
	{
		cerr << "Tarrif File is Not Found!\nBill cannot Be calculated!" << endl;
		return 0;
	}
	delete TarrifFile;
}
                              // This will change the bill status from unpaid to paid  
void Bill::ChangeBillStatus()
{
	billPaidStatus = 1;

}
                                                  // Store bill in a file 
void Bill::SaveBillInFile(ofstream & OutputBill)
{
	OutputBill << CostumerId << ",";
	OutputBill << BillMonth << ",";
	OutputBill << MeterReadingPeak << ",";
	OutputBill << MeterReadingReg << ",";
	OutputBill << IssueDate << ",";
	OutputBill << ElectricityCost << ",";
	OutputBill << SalesTax << ",";
	OutputBill << FixedCharges << ",";
	OutputBill << TotalBill << ",";
	OutputBill << DueDate << ",";
	OutputBill << billPaidStatus << ",";
	OutputBill << BillPayementDate << endl;
}
                                      // Shows the Customer Bill
void Bill::ShowBill()
{

	cout << " Cost of Electricity : " << ElectricityCost << endl << endl;
	cout << "Tax  percentage :" << SalesTax << endl << endl;
	cout << "Fixed Charges : " << FixedCharges << endl << endl;
	cout << "Total amount due :" << TotalBill << endl << endl;
	cout << "Due Date :" << DueDate << endl << endl;
	cout << "Billing month: " << BillMonth << endl << endl;
	if (billPaidStatus)
		cout << "paid Bill Status: " << "Paid" << endl;
	else
		cout << "paid Bill Status: " << "UnPaid" << endl;

}
bool Bill::GetBillStatus() 
{
	return billPaidStatus;
}
int Bill::getMeterReadingPeak()
{
	return MeterReadingPeak;
}
int Bill::getMeterReadingRegulaer()
{
	return MeterReadingReg;
}
 Bill::~Bill()
 {
	 if(TarrifFile)
		 delete TarrifFile;
 }

//     ============================================  CUSTOMER ============================================

class Costumer
{
	string UserName;
	int CostumerId;
	string DateOfBirth;
	string PhoneNumber;
	string Address;
	int CostumerType;
	int MeterType;
	string ConnectionDate;
	int RegUnits;
	int PeakHourUnits;
	Bill **CurrentBill;
	int NoofBill;
public:
	Costumer();
	int GetId()
	{
		return CostumerId;
	}
	int  GetMeterType()
	{
		return MeterType;
	}
	int  GetCostumerType()
	{
		return CostumerType;
	}
	int GetRegUnits()
	{
		return RegUnits;
	}
	int GetPeakHourUnits()
	{
		return PeakHourUnits;
	}
	string  GetPhoneNo()
	{
		return PhoneNumber;
	}
	string GetUsername()
	{
		return UserName;
	}
	string Getaddress()
	{
		return Address;
	}
	string GetdateofBirth()
	{
		return DateOfBirth;
	}

	void SetRegUnits(int i)
	{
		RegUnits = i;
	}
	void SetPeakHourUnits(int i)
	{
		PeakHourUnits = i;
	}

	bool UserExist(int id, string date, int metertype, int);
	void LoadDataFromFile(ifstream&);
	void InputCostumerData();
	void SaveData(ofstream&);
	bool CheckCredentials(int, string);
	void SetBill(Bill*);
	void ViewBill();
	void  UpdateInfo();
	bool CheckId(int );
	~Costumer();
};


Costumer::Costumer()                         // Constructor
{
	UserName = "";
	CostumerId = 0;
	PhoneNumber = "";
	Address = "";
	DateOfBirth = "";
	ConnectionDate = "";
	CostumerType = 0;
	MeterType = 0;
	RegUnits = 0;
	PeakHourUnits = NULL;
	CurrentBill = 0;
	NoofBill = 0;
}
                                       // Load data from file name "CustomerInfo.txt"
void Costumer::LoadDataFromFile(ifstream& InputCostumer)
{
	string y, m, d;
	char ign;
	InputCostumer >> CostumerId;
	InputCostumer >> ign;
	getline(InputCostumer, DateOfBirth, ',');
	getline(InputCostumer, UserName, ',');
	getline(InputCostumer, Address, ',');
	getline(InputCostumer, PhoneNumber, ',');
	InputCostumer >> CostumerType;
	InputCostumer >> ign;
	InputCostumer >> MeterType;
	InputCostumer >> ign;
	getline(InputCostumer, ConnectionDate, ',');
	InputCostumer >> RegUnits;
	InputCostumer >> ign;
	InputCostumer >> PeakHourUnits;

}
                                 // Takes Data(Name ,Address , Date of Birth) from the Customer 
void Costumer::InputCostumerData()
{
	int Year, Month, Day, Valid = 0;
	string tempYear, tempMonth, tempDay;
	srand(time(0));
	CostumerId = rand() % 9000 + 1000;

	cout << "Enter Costumer Name:\t";
	getline(cin, UserName);

	cout << "\nEnter Costumer Phone number:\t";
	getline(cin, PhoneNumber);

	cout << "\nEnter Costumer Address:\t";
	getline(cin, Address);

	cout << "\nEnter Costumer date of birth in the format YYYYMMDD :\t";
	cin >> Year >> Month >> Day;
	Helper::CheckDateValidity(Year, Month, Day);        // check if the entered date is correct or not 
	tempYear = to_string(Year);
	tempMonth = to_string(Month);
	tempDay = to_string(Day);
	if (Month < 10 && Day < 10)
	{
		DateOfBirth = tempYear + '0' + tempMonth + '0' + tempDay;
	}
	else
		DateOfBirth = tempYear + tempMonth + tempDay;
	if (Month < 10 && Day>9)
		DateOfBirth = tempYear + '0' + tempMonth + tempDay;
	if (Day < 10 && Month>9)
		DateOfBirth = tempYear + tempMonth + '0' + tempDay;


	cout << "\nEnter Your Customer type (Enter 1 for Commercial Or Enter 2 For Domestic ):\t";
	cin >> CostumerType;

	int count = 0;
	cout << "\nEnter Your Meter Type ( 1 for Single phase , 3 for Three Phase) : \t";
	cin >> MeterType;
	while (count < 2 && Valid != true)
	{
		if (MeterType == 1 || MeterType == 3)
		{
			Valid = true;
			break;
		}
		else
		{
			cout << "Incorrect meter type! \nenter 1 for single phase meter and 3 for three phase meter\n";
			cin >> MeterType;
			count++;
			Valid = false;
		}

	}

	if (Valid == true)
	{
		cout << "\nEnter Connection Date (YYYYMMDD):\t";
		cin >> Year >> Month >> Day;
		Helper::CheckDateValidity(Year, Month, Day);             // Checks if the date entered is valid or not 
		tempYear = to_string(Year);
		tempMonth = to_string(Month);
		tempDay = to_string(Day);
		if (Month < 10 && Day < 10)
		{
			ConnectionDate = tempYear + '0' + tempMonth + '0' + tempDay;
		}
		else
			ConnectionDate = tempYear + tempMonth + tempDay;
		if (Month < 10 && Day>9)
			ConnectionDate = tempYear + '0' + tempMonth + tempDay;
		if (Day < 10 && Month>9)
			ConnectionDate = tempYear + tempMonth + '0' + tempDay;

		if (MeterType == 1)
		{
			cout << "\nEnter Regular units consumed:\t";
			cin >> RegUnits;
			cout << endl;
		}
		else
			if (MeterType == 3)
			{
				cout << "\nEnter Regular units consumed:\t";
				cin >> RegUnits;
				cout << endl;

				cout << "\nEnter Peak Hour units consumed:\t";
				cin >> PeakHourUnits;
				cout << endl;
			}
		cout << "You are registered sucessfully\n";
		cout << "Your customer id is " << " \"" << CostumerId << "\" \n";
	}
	else
	{
		cout << "Sorry you cannot be registered. Try again later.Thankyou!";
	}
}
void Costumer::SaveData(ofstream& outputCostumer)
{
	outputCostumer << CostumerId << ",";
	outputCostumer << DateOfBirth << ",";
	outputCostumer << UserName << ",";
	outputCostumer << Address << " ,";
	outputCostumer << PhoneNumber << ",";
	outputCostumer << CostumerType << ",";
	outputCostumer << MeterType << ",";
	outputCostumer << ConnectionDate << ",";
	outputCostumer << RegUnits << "," << PeakHourUnits << endl;
}
                                       // This will enable the user to see his Current bill
void Costumer::ViewBill()
{
	system("cls");
	cout << "\n\t\t ==============CUSTOMER'S BILL=============" << endl<<endl;
	cout << "Cotumer Id: " << CostumerId << endl << endl;
	cout << "Costumer UserName: " << UserName << endl << endl;
	cout << "Adress :" << Address << endl << endl;
	cout << "Phone Number: " << PhoneNumber << endl << endl;
	if (CostumerType == 1)
		cout << "Costumer Type:		Commercial Costumer" << endl << endl;
	else
		cout << "Costumer Type:		Domestic Costumer" << endl << endl;
	if (MeterType == 1)
		cout << "Meter Type:	Single Phase Meter" << endl << endl;
	else
		cout << "MeterType:	3Phase Phase Meter" << endl << endl;
	CurrentBill[NoofBill - 1]->ShowBill();
	return;
}
                                       // check validity of Customer(id , date ,meter type ) by comparing from File Data
bool Costumer::UserExist(int id, string date, int metertype, int CostumType)
{
	return (id == CostumerId && date == DateOfBirth && MeterType == metertype && CostumerType == CostumType);
}

void Costumer::UpdateInfo()
{
	int Option;
	cout << "Enter 1 to Update All the enteries belonging to this Customer id\n"
		<< "Enter 2 to Update Specific information of this Customer\n";

	cin >> Option;

	if (Option == 1)
	{
		cin.ignore();
		InputCostumerData();
	}
	if (Option == 2)
	{
		int choice;
		system("cls");
		cout << "Press 1 to Update UserName \n"
			<< "Press 2 to Update Phone Number\n"
			<< " Press 3 to update address\n"
			<< "Press 4 to update DateOfBirth\n"
			<< "Press 5 to Update Customer Type\n"
			<< "Press 6 to Update Meter Type\n"
			<< "Press 7 to Update Regular units consumed\n"
			<< "Press 8 to Update Units consumed in Peak hour\n";
		          // Customer will enter the choice number from the menu according to the task to be  performed
		cin >> choice;

		if (choice == 1)
		{
			cin.ignore();
			cout << "Enter new UserName \n";
			cin >> UserName;
		}
		if (choice == 2)
		{
			cin.ignore();
			cout << "Enter new phone Number \n";
			getline(cin, PhoneNumber);
		}
		if (choice == 3)
		{
			cin.ignore();
			cout << "Enter new Address \n";
			getline(cin, Address);
		}
		if (choice == 4)
		{
			cin.ignore();
			cout << "Enter new Date of Birth of format(YYYY MM DD) \n";
			int Year, Month, Day;
			cin >> Year >> Month >> Day;
			Helper::CheckDateValidity(Year, Month, Day);
			string tempYear = to_string(Year);
			string tempMonth = to_string(Month);
			string tempDay = to_string(Day);

			if (Month < 10 && Day < 10)
			{
				DateOfBirth = tempYear + '0' + tempMonth + '0' + tempDay;
			}
			else
				DateOfBirth = tempYear + tempMonth + tempDay;
			if (Month < 10 && Day>9)
				DateOfBirth = tempYear + '0' + tempMonth + tempDay;
			if (Day < 10 && Month>9)
				DateOfBirth = tempYear + tempMonth + '0' + tempDay;

		}
		if (choice == 5)
		{
			cin.ignore();
			cout << "Enter new costumer type \n";
			cin >> CostumerType;
		}
		if (choice == 6)
		{
			cin.ignore();
			cout << "Enter new MeterType \n";
			cin >> MeterType;
		}
		if (choice == 7)
		{
			cin.ignore();
			cout << "Enter new regular Unit Consumed \n";
			cin >> RegUnits;
		}
		if (choice == 8)
		{
			cin.ignore();
			cout << "Enter new PeakUnit Hours Consumed \n";
			cin >> PeakHourUnits;
		}
	}
}           
		                                         // For crosschecking the ID and Date of Birth of the customer
bool Costumer::CheckCredentials(int id, string dob)
{
	return (id == CostumerId && dob == DateOfBirth);
}
												//associate bills with costumers
void Costumer::SetBill(Bill* newBill)
{
	if (CurrentBill == 0)
	{
		CurrentBill = new Bill*[30];
	}
	CurrentBill[NoofBill] = newBill;
	CurrentBill[NoofBill + 1] = 0;
	NoofBill++;
}
											//for check id
bool Costumer:: CheckId(int id)
{
	return (CostumerId==id);
}

Costumer ::~Costumer()
{
	
}


//     ============================================  LESCO ============================================

class LESCO
{
	Costumer **costumerList;
	Employee** EmployeeList;
	Costumer* CurrentCostumer;
	Employee*CurrentEmployee;
	Bill**BillingList;
	Tarrif File;
	int TotalCostumers;
	int TotalEmployees;
	int TotalBills;
public:
	LESCO();
	void LoadDataFromFileCostumers();
	void LoadDataFromFileEmployees();
	void LoadDataFromFileBills();
	void LoadDataFromTarrifFile();

	void RegisterUsers();
	void RegisterEmplyees();

	bool CheckCorrectName(string);
	bool CheckCorrectPassword(string);

	void SaveDataAfterRegisterationEmployee();
	void SaveDataAfterRegisterationCostumer();
	void SaveDataAfterGenerationOfBill();
	void UpdateStatus_of_Bill();
	void ShowCalculatedBill();

	Costumer* SearchCostumerById(int);
	bool UserExist(int id, string Date, int, int,int, int);
	void AssociateCostumerToBill();
	void AssociateBill();
	void GenerateBill();
	bool SetCurrentCostumer();
	bool SetCurrentEmployee();
	void Add_or_Update_Entry();
	bool Changepassword();
	void Showbill();
	void ShowReport();
	~LESCO();
};

LESCO::LESCO()
{
	CurrentCostumer=0;
	CurrentEmployee=0;
	costumerList = 0;
	EmployeeList = 0;
	TotalCostumers = 0;
	TotalEmployees = 0;
	BillingList = 0;
	TotalBills = 0;
}
                                          // Loading the file "CustomerInfo.txt"
void LESCO::LoadDataFromFileCostumers()
{
	ifstream InputCostumers("CustomerInfo.txt");

	if (InputCostumers)
	{
		InputCostumers >> TotalCostumers;
		costumerList = new Costumer*[100];
		for (int i = 0; i < TotalCostumers;i++)
		{
			costumerList[i] = new Costumer;
			costumerList[i]->LoadDataFromFile(InputCostumers);
		}
		InputCostumers.close();
	}

}
                                           // Loading the File "EmployeesData.txt"
void LESCO::LoadDataFromFileEmployees()
{
	ifstream inputEmployee("EmployeesData.txt");
	if (inputEmployee)
	{
		inputEmployee >> TotalEmployees;
		string ign;
		getline(inputEmployee, ign);
		EmployeeList = new Employee*[10];
		for (int i = 0; i < TotalEmployees;i++)
		{
			EmployeeList[i] = new Employee;
			EmployeeList[i]->LoadDataFromFile(inputEmployee);
		}
		inputEmployee.close();
	}
	else
	{
		cerr << "No File can be found of employee's Data!" << endl;
	}
}
	
                                              // Loading the file "BillingInfo.txt"
void LESCO::LoadDataFromFileBills()
{
	ifstream inputBills("BillingInfo.txt");
	if (inputBills)
	{
		inputBills >> TotalBills;
		BillingList = new Bill*[100];
		for (int i = 0;i < TotalBills;i++)
		{
			BillingList[i] = new Bill;
			BillingList[i]->LoadDataFromFile(inputBills);
		}
		inputBills.close();
	}
}
											//  Loading the file "TarrifAndTax.txt"
void  LESCO::LoadDataFromTarrifFile()
{
	File.LoadTarrifFile();
}
                                        // This function registers a new Customer
void LESCO::RegisterUsers()
{
	if (costumerList == 0)
	{
		costumerList = new Costumer*[100];
	}
	costumerList[TotalCostumers] = new Costumer;

	costumerList[TotalCostumers]->InputCostumerData();
	TotalCostumers++;
	SaveDataAfterRegisterationCostumer();
}
                                        // This register a new Employee
void LESCO::RegisterEmplyees()
{
	if (EmployeeList == 0)
	{
		EmployeeList = new Employee*[10];
	}

	string Name, pass;
	int PasswordCount = 3;
	cout << "Enter UserName : ";
	cin.ignore();
	getline(cin, Name);

	if (CheckCorrectName(Name))
	{
		cout << "Enter your password of 5 digits: ";
		getline(cin, pass);
		if (CheckCorrectPassword(pass) == 0)
		{
			while (CheckCorrectPassword(pass) != true)
			{
				if (PasswordCount < 0)
				{
					cout << "Sorry you can't be registered.....You have attempted all your 3 extra tries " << endl;
					break;
				}
				cout << "Invalid Password. You have " << PasswordCount - 1 << "  Attempts left" << endl;
				PasswordCount--;

				cout << "Enter your password of 5 digits: ";
				getline(cin, pass);
			}

		}
		                     // Check if the password entered by the employee exist or not 
		if (CheckCorrectPassword(pass))         
		{
			cout << "Your Registeration is Done. Welcome to LESCO Company as Employee " << endl;
			EmployeeList[TotalEmployees] = new Employee;
			EmployeeList[TotalEmployees]->InputEmployeeData(Name, pass);
			TotalEmployees++;
		}
	}
	else
	{
		cerr << "Sorry the name is already registered. Please Try Again " << endl;
		return;
	}

	SaveDataAfterRegisterationEmployee();


}
                                           // Check the name of the employee from the File 
bool LESCO::CheckCorrectName(string Name)
{
	ifstream inputEmployee("EmployeesData.txt");
	string temp;
	if (TotalEmployees == 0)
	{
		return true;
	}
	else
	{
		getline(inputEmployee, temp);
		for (int i = 0; i < TotalEmployees; i++)
		{
			getline(inputEmployee, temp, ',');
			if (Name.compare(temp) == 0)
				return false;
			else
			{
				return true;
			}
		}
	}
}
                                           // For checking the password
bool LESCO::CheckCorrectPassword(string Password)
{
	bool ValidPassword = false;
	if (Password.length() < 5 || Password.length() > 5)
	{
		ValidPassword = false;
	}
	if (Password.length() == 5)
	{
		ValidPassword = true;
	}
	return ValidPassword;
}

void LESCO::SaveDataAfterRegisterationCostumer()
{
	ofstream OutputCostumer("CustomerInfo.txt");
	OutputCostumer << TotalCostumers << endl;
	for (int i = 0;i < TotalCostumers;i++)
	{
		costumerList[i]->SaveData(OutputCostumer);
	}
}
                                 // This will save the data of the new employee(just registered)
void LESCO::SaveDataAfterRegisterationEmployee()
{
	ofstream Outputemployee("EmployeesData.txt");
	Outputemployee << TotalEmployees << endl;
	for (int i = 0;i < TotalEmployees;i++)
	{
		EmployeeList[i]->SaveData(Outputemployee);
	}
}
                              // Save Data of the Bill after Generating it 
void  LESCO::SaveDataAfterGenerationOfBill()
{
	ofstream OutputBill("BillingInfo.txt");
	OutputBill << TotalBills << endl;
	for (int i = 0;i < TotalBills;i++)
	{
		BillingList[i]->SaveBillInFile(OutputBill);
	}
}
                                        // This will search or check a customer by his ID
Costumer*  LESCO::SearchCostumerById(int id)
{
	for (int i = 0;i < TotalCostumers;i++)
	{
		if (costumerList[i]->GetId() == id)
			return costumerList[i];
	}
	cerr << "No Id is Found" << endl;
	return 0;

}
                                 // This Function associates Bill with Customer's ID
void LESCO::AssociateCostumerToBill()
{
	for (int i = 0;i < TotalBills;i++)
	{
		BillingList[i]->SetConsumer(SearchCostumerById(BillingList[i]->GetId()));
	}
}
void LESCO::AssociateBill()
{
	for (int i = 0;i < TotalCostumers;i++)
	{
		for (int j = 0;j < TotalBills;j++)
			if (costumerList[i]->GetId() == BillingList[j]->GetId())
			{
				costumerList[i]->SetBill(BillingList[j]);

			}
	}
}

void LESCO::Add_or_Update_Entry()
{
	cout << "Enter Customer'id for updation:\t";
	int  id;
	cin >> id;

	Costumer* temp = SearchCostumerById(id);
	if (temp)
	{
		temp->UpdateInfo();
		SaveDataAfterRegisterationCostumer();

		cout<<"The information is Updated Successfully "<<endl;
	}
}
                                          
void LESCO::GenerateBill()
{
	if (File.LoadTarrifFile())
	{
		int id;
		cout << "======================ADD Information Into A Bill========================" << endl << endl;
		cout << "enter the Costumer Id: ";
		cin >> id;
		Costumer* temp = SearchCostumerById(id);
		if (temp)
		{
			if (BillingList == 0)
			{
				BillingList = new Bill*[100];
			}
			BillingList[TotalBills] = new Bill;
			BillingList[TotalBills + 1] = 0;
			BillingList[TotalBills]->GenerateBill(id, temp->GetMeterType(), temp->GetCostumerType(), temp->GetRegUnits(), temp->GetPeakHourUnits());
			TotalBills++;
			SaveDataAfterGenerationOfBill();
		}
		else
		{
			cerr << "Enter correct Costumer Id to Generate a bill" << endl;
		}
	}
}
                                     // This will update the status of the bill after checking customer ID
void LESCO::UpdateStatus_of_Bill()
{
	int Id;
	cout << "Enter Customer Id of whom you want to change paid Status " << endl;
	cin >> Id;
	int greatestPeakReading = 0, greatestregularReading = 0;
	for (int i = 0; i < TotalBills; i++)
	{
		if (Id == BillingList[i]->GetId())
		{
			BillingList[i]->ChangeBillStatus();

			if (BillingList[i]->getMeterReadingRegulaer() >= greatestregularReading)
				greatestregularReading = BillingList[i]->getMeterReadingRegulaer();

			if (BillingList[i]->getMeterReadingPeak() >= greatestPeakReading)
				greatestPeakReading = BillingList[i]->getMeterReadingPeak();

		}
	}
	int Index = 0;
	for (int i = 0; i < TotalCostumers; i++)
	{
		if (Id == costumerList[i]->GetId())
		{
			if ((costumerList[i]->GetMeterType() == 1) )//if 1 for domestic
			{

				costumerList[i]->SetRegUnits(greatestregularReading);
			}
			
			if ((costumerList[i]->GetMeterType() == 3) )
			{

				costumerList[i]->SetRegUnits(greatestregularReading);
				costumerList[i]->SetPeakHourUnits(greatestPeakReading);

			}
			
			break;
		}
	}
	SaveDataAfterRegisterationCostumer();//to store changes after updation...same function call
	SaveDataAfterGenerationOfBill();
	cout<<"The Status of Bill is updated Successfully!"<<endl<<endl;
}
                                           // Set the current Employee ( Logged in) 
bool LESCO::SetCurrentEmployee()
{
	cout << "--------------------------Employee Login ------------------------------" << endl;
	string Name, Password;
	cin.ignore();
	cout << "Enter your name :  ";
	getline(cin, Name);

	cout << "Enter your Password : ";
	getline(cin, Password);
	for (int i = 0;i < TotalEmployees;i++)
	{
		if (EmployeeList[i]->CheckCredentials(Name, Password))
		{
			CurrentEmployee = EmployeeList[i];
			cout << "You are logged in ;) " << endl;
			return 1;
		}
	}
	cout << "You are not Logged in !!! No match Found!" << endl;
	return 0;
}
                                        // Set the current Employee ( Logged in)
bool LESCO::SetCurrentCostumer()
{
	cout << "--------------------------Costumer Login ------------------------------" << endl;
	int Id;
	string Dob;
	cout << "Enter your Costumer Id :  ";
	cin >> Id;

	cout << "Enter your Date of Birth (Without Spaces of Format YYYYMMDD) : ";
	cin.ignore();
	getline(cin, Dob);
	for (int i = 0;i < TotalCostumers;i++)
	{
		if (costumerList[i]->CheckCredentials(Id, Dob))
		{
			CurrentCostumer = costumerList[i];
			cout << "You are logged in ;) " << endl;
			return 1;
		}
	}
	cout << "You are not Logged in !!! No match Found!" << endl;
	return  0;
}
                                          // This enables the Employee to Change his password
bool LESCO::Changepassword()
{
	if (CurrentEmployee == 0)
	{
		cout << "you have to be login First" << endl;
		return 0;
	}
	else
	{
		string Name, Password;
		cout << "Enter your name :  ";
		cin.ignore();
		getline(cin, Name);

		cout << "Enter your Password : ";
		getline(cin, Password);
		if (CurrentEmployee->CheckCredentials(Name, Password))
		{
			cout << "Enter your  New Password : ";
			getline(cin, Password);
			if (CheckCorrectPassword(Password))
			{
				CurrentEmployee->InputEmployeeData(Name, Password);
				SaveDataAfterRegisterationEmployee();
				cout << "Your Password is updated successfully !!!!! " << endl;
				return 1;
			}
			else
			{
				cerr << "your Password's Syntax is not Right! Try again Later" << endl;
				return 0;
			}
		}
		else
		{
			cerr << "UserName or Password is Incorrect." << endl;
		}
	}

}
bool LESCO::UserExist(int id, string Date, int meterType, int CostumType, int meterReading,int peakReading)
{
	for (int i = 0;i < TotalCostumers;i++)
	{
		if (costumerList[i]->UserExist(id, Date, meterType, CostumType))
		{
			if(costumerList[i]->GetRegUnits()<=meterReading)
			{
				if(costumerList[i]->GetPeakHourUnits()<=peakReading)
						return 1;
				else
				{
					cerr<<"Meter Reading Peak Cannot be Greater than Previous Meter Reading.... Thank you!"<<endl;
					return 0;
				}
			}
			else
			{
				cerr<<"Meter Reading Regular Cannot be Greater than Previous Meter Reading.... Thank you!"<<endl;
				return 0;
			}
		}
	}
	return 0;
}
                                   // This function shows the Bill to the Customer
void LESCO::Showbill()
{
	int id;
	cout << "Enter your Costumer Id :  ";
	cin >> id;
	if(CurrentCostumer==0)
	{
		for (int i = 0;i < TotalCostumers;i++)
		{
			if (costumerList[i]->CheckId(id))
			{
				CurrentCostumer = costumerList[i];
			}
		}
	}
		
	if (SearchCostumerById(id))
	{
		CurrentCostumer->ViewBill();
	}
	else
		cerr << "Sorry No Bill is Found Against provided Costumer id" << endl;


}
                                          // This will show the bill after taking input from the customer( meter reading)
void  LESCO::ShowCalculatedBill()
{

	int id, Year, Day, Month, meterType, CurrentMeterReading, costumType, peakreading, TotalBill;
	string Date, tempYear, tempMonth, tempDay;
	Costumer* temp;
	cout << "Enter your Costumer Id :  ";
	cin >> id;
	temp = SearchCostumerById(id);
	if (SearchCostumerById(id))
	{
		cout << "\nEnter Date of Birth in the format YYYY MM DD :\t";
		cin >> Year >> Month >> Day;
		Helper::CheckDateValidity(Year, Month, Day);
		tempYear = to_string(Year);
		tempMonth = to_string(Month);
		tempDay = to_string(Day);
		if (Month < 10 && Day < 10)
		{
			Date = tempYear + '0' + tempMonth + '0' + tempDay;
		}
		else
			Date = tempYear + tempMonth + tempDay;
		if (Month < 10 && Day>9)
			Date = tempYear + '0' + tempMonth + tempDay;
		if (Day < 10 && Month>9)
			Date = tempYear + tempMonth + '0' + tempDay;
		cout << "Enter YOur Meter Type: ";
		cin >> meterType;
		cout << "Enter YOur Costumer Type (1 For Commercial, 2 For Domestic) : ";
		cin >> costumType;

		cout << "Enter Your Current Meter Reading  Regular: ";
		cin >> CurrentMeterReading;
		if (meterType == 3)
		{
			cout << "Enter Your Peak Current Meter Reading : ";
			cin >> peakreading;
		}
		else
			peakreading = 0;

		if (UserExist(id, Date, meterType, costumType,CurrentMeterReading,peakreading))
		{
			Bill *TempBill = new Bill;
			TotalBill = TempBill->CalculationOfBill(temp->GetRegUnits(), CurrentMeterReading, temp->GetPeakHourUnits(), peakreading, meterType, costumType);
			cout << "Your Total Billing Amount Against Your Meter Reading is = " << TotalBill << endl;
			delete TempBill;
		}
	}
}
										//show amount of paid and unpaid bills
void LESCO::ShowReport()
{
	if (CurrentEmployee == 0)
	{
		cout << "you have to be login First" << endl;
		return;
	}
	else
	{
		cout<<"The amount Of Bills Paid and Unpaid in Current Month "<<endl;
		string tempMonth="";
		for (int i = 0; i < TotalBills; i++)
		{
			if(BillingList[i]->GetDate().compare(tempMonth)>0)
			{
				tempMonth=BillingList[i]->GetDate();
			}
		}
		int paid_count = 0, unpaid_count = 0;
		for (int i = 0; i < TotalBills; i++)
		{
			if (BillingList[i]->GetBillStatus() == 1&& tempMonth==BillingList[i]->GetDate())
				paid_count++;
			else
				if(tempMonth==BillingList[i]->GetDate())
				unpaid_count++;
		}
		cout << endl << "Paid Bills :	 " << paid_count << endl<<endl;
		cout << "Unpaid Bills :	    " << unpaid_count << endl<<endl<<endl;
	}

}


LESCO::~LESCO()
{
	if(costumerList)
	{
		for(int i=0;i<TotalCostumers;i++)
		delete costumerList[i];
		delete costumerList;
	}

	if( EmployeeList)
	{
		for(int i=0;i<TotalCostumers;i++)
		delete EmployeeList[i];
		delete EmployeeList;
	}

	if(BillingList)
	{
		for(int i=0;i<TotalBills;i++)
		delete BillingList[i];
		delete BillingList;
	}

	
}

void RunProgram()
{
	int choice = 0;
	Bill bill;
	LESCO lesco;
	cout << "					!!Welcome To the LESCO Official Website!!					" << endl << endl << endl;
	while(choice!=-1)
	{
			cout << "=====================================================Menue!==========================================" << endl << endl;
			cout << "Press 1 For Employee Registeration-------------" << endl;
			cout << "Press 2 for Costumer Login------------" << endl;
			cout << "Press 3 For Employee Login-------------" << endl;
			cout << "Press -1 For Exit----------------" << endl;
			cin >> choice;
			if (choice == 1)
			{
				int turn = 0;
				while (turn != -1)
				{
					lesco.LoadDataFromFileEmployees();
					lesco.RegisterEmplyees();
					lesco.LoadDataFromFileEmployees();
					cout << "Enter -1 to Exit or 1 for Again Registeration.. Thank you" << endl;
					cin >> turn;
				}
				cout << "----Going To Main Menue----" << endl;
			}
			if (choice == 2)
			{
				lesco.LoadDataFromFileCostumers();
				lesco.LoadDataFromFileEmployees();
				lesco.LoadDataFromFileBills();
				lesco.LoadDataFromTarrifFile();
				lesco.AssociateBill();
				lesco.AssociateCostumerToBill();

				if (lesco.SetCurrentCostumer())
				{
					int option = 0;
					system("cls");
					while (option != -1)
					{
						cout << "=============================Costumer Portal================================" << endl << endl;
						cout << "Enter 1 to View Your Bill" << endl;
						cout << "Enter 2 to Calculate Bill with Your Current Meter Reading" << endl;
						cout << "Enter -1 To Exit!" << endl;
						cin >> option;
						if (option == 1)
							lesco.Showbill();
						else
							if (option == 2)
								lesco.ShowCalculatedBill();
							else
								if (option != 2 && option != 1 && option != -1)
									cerr << "Enter correct Number... You Stupid!" << endl;
					}
					cout << "----Going To Main Menue----" << endl;

				}
			}
			if (choice == 3)
			{
				lesco.LoadDataFromFileCostumers();
				lesco.LoadDataFromFileBills();
				lesco.LoadDataFromFileEmployees();
				lesco.LoadDataFromTarrifFile();
				lesco.AssociateBill();
				lesco.AssociateCostumerToBill();

				if (lesco.SetCurrentEmployee())
				{
					int option = 0;
					system("cls");
					while (option != -1)
					{
						int choice=0;
						
						cout << "Enter 1 to change your Password" << endl<< endl;
						cout << "Enter 2 to Generate A new Bill" << endl<< endl;
						cout << "Enter 3 to view Costumer Bill" << endl<< endl;
						cout << "Enter 4 to view List of Paid and Unpaid bills " << endl<< endl;
						cout << "Enter 5 to Update the costumer's File " << endl<< endl;
						cout << "Enter 6 to Add a new Costumer " << endl<< endl;
						cout << "Enter 7 To Update The status of Unpaid Bill" << endl<< endl;
						cout << "Enter -1 To Exit" << endl<< endl;
						cin >> option;
						if (option == 1)
						{
							lesco.Changepassword();
						}
						if (option == 2)
						{
							lesco.GenerateBill();
						}
						if (option == 3)
						{
							lesco.Showbill();
						}
						if(option==4)
						{
							lesco.ShowReport();
						}
						if(option==5)
						{
							lesco.Add_or_Update_Entry();
						}
						if(option==6)
						{
							lesco.RegisterUsers();
						}
						if(option==7)
						{
							lesco.UpdateStatus_of_Bill();
						}
						if(option>7||option<-1||option==0)
						{
							cerr<<"Enter Correct Option To Function You Idiot!!"<<endl;
						}


					}
					cout<<"Going To main Mnue!"<<endl;
				}

			}
		}
	}

void main()
{
	RunProgram();
}