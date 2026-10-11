#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

struct sClients {
	string AccountNumber;
	string PinCode;
	string Name;
	string phone;
	double AccountBalance;
	bool MarckCorrect = false;
};

enum enClientData { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Trans = 6, Exit = 7 };
enum enTransData { Deposit = 1, WithDraw = 2, Total = 3, Main = 4 };

const string FileName = "Clients.txt";

sClients ConvertLineToRecord(string Line);
void ShowTransaction();
void ShowMain();
void GoBackToMainMenue();

bool ClientExistsByAccountNumber(string AccountNumber, string
	FileName) {

	fstream MyFile(FileName, ios::in);
	vector<sClients>vClients;
	sClients Clients;
	string Line;
	if (MyFile.is_open()) {

		while (getline(MyFile, Line)) {
			Clients = ConvertLineToRecord(Line);
			if (AccountNumber == Clients.AccountNumber) {
				MyFile.close();
				return true;

			}
			vClients.push_back(Clients);
		}
		MyFile.close();
	}
	return false;
}
sClients ReadNewClient() {
	sClients Client;

	while (ClientExistsByAccountNumber(Client.AccountNumber, FileName)) {
		cout << "The AccountNumber Already exist" << Client.AccountNumber;
		cout << "please enter Client.AcccountNumber Again\n";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "please enter Client.PinCode\n";

	getline(cin >> ws, Client.PinCode);
	cout << "please enter Client.Name\n";

	getline(cin, Client.Name);
	cout << "please enter Client.Phone\n";

	getline(cin, Client.phone);
	cout << "please enter Client.AccountBalance\n";

	cin >> Client.AccountBalance;
	return Client;
}
string ConvertToOneLine(sClients Client, string Seprator = "#//#") {
	string sWord = "";
	sWord += Client.AccountNumber + Seprator;
	sWord += Client.PinCode + Seprator;
	sWord += Client.Name + Seprator;
	sWord += Client.phone + Seprator;
	sWord += to_string(Client.AccountBalance);
	return sWord;
}
vector<string> SpiltLine(string Line, string Seprator = "#//#") {
	size_t pos = 0;
	vector<string> vLine;
	string sWord;

	while ((pos = Line.find(Seprator)) != string::npos) {
		sWord = Line.substr(0, pos);
		if (sWord != "") {
			vLine.push_back(sWord);
		}
		Line.erase(0, pos + Seprator.length());
	}

	if (Line != "") {
		vLine.push_back(Line);   // آخر كلمة بعد آخر فاصل
	}

	return vLine;
}
sClients ConvertLineToRecord(string Line) {
	sClients Client;
	vector<string>vClient = SpiltLine(Line);

	Client.AccountNumber = vClient[0];
	Client.PinCode = vClient[1];
	Client.Name = vClient[2];
	Client.phone = vClient[3];
	Client.AccountBalance = stod(vClient[4]);
	return Client;

}
void PrintClientData(sClients Client) {
	cout << "\nAccount.Numbe :" << Client.AccountNumber << endl;
	cout << "Account.PinCode :" << Client.PinCode << endl;
	cout << "Account.Name :" << Client.Name << endl;
	cout << "Account.Phone :" << Client.phone << endl;
	cout << "Account.AccountBalance :" << Client.AccountBalance << endl;
}
void ReadDataClientFromFile() {
	char c = 'y';
	do {
		system("cls");

		sClients Client = ReadNewClient();
		string Line = ConvertToOneLine(Client);
		fstream MyFile(FileName, ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << Line << endl;
			MyFile.close();
		}

		cout << "The process sucsissful,Do you want to add new client(y/n)yes/no\n";
		cin >> c;
	} while (toupper(c) == 'Y');

}
vector<sClients>LoadDataFromFile(string FileName) {

	string Line;
	sClients Client;
	vector<sClients>vClients;
	fstream MyFile(FileName, ios::in);
	if (MyFile.is_open()) {

		while (getline(MyFile, Line)) {

			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();

	}
	return vClients;
}
void PrintDataClientRecordeOrder(sClients Client) {

	cout << "| " << left << setw(15) << Client.AccountBalance;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;

}
void PrintDataClientRecordeOrderTrans(sClients Client) {

	cout << "| " << left << setw(15) << Client.AccountBalance;

	cout << "| " << left << setw(40) << Client.Name;

	cout << "| " << left << setw(12) << Client.AccountBalance;

}
void PrintAllDataClient(vector<sClients>vClients) {

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << "clients(s)" << endl;

	cout << "____________________________________________________________________________________\n" << endl;
	cout << "____________________________________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "____________________________________________________________________________________\n" << endl;
	cout << "____________________________________________________________________________________\n" << endl;

	for (sClients Client : vClients)
	{
		PrintDataClientRecordeOrder(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
void PrintAllDataClientTrans(vector<sClients>vClients) {

	cout << "____________________________________________________________________________________\n" << endl;
	cout << "\t\t\t\tClient List (" << vClients.size() << "clients(s)" << endl;

	cout << "____________________________________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";

	cout << "| " << left << setw(40) << "Client Name";

	cout << "| " << left << setw(12) << "Balance";
	cout << "\n____________________________________________________________________________________\n" << endl;
	cout << "____________________________________________________________________________________\n" << endl;
	double sum = 0;
	for (sClients Client : vClients)
	{
		sum = sum + Client.AccountBalance;
		PrintDataClientRecordeOrderTrans(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout <<
		"__________________________________________\n" << endl;
	cout << "\t\t" << "Total Balance for All AccountNumber in File" << sum << endl;
}
bool FindClientData(sClients& Clients, string AccountNumber, vector<sClients>& vClients) {
	vClients = LoadDataFromFile(FileName);
	for (sClients C : vClients) {

		if (AccountNumber == C.AccountNumber) {

			Clients = C;
			return true;
		}
	}
	return false;
}
string SearchAccountNumber() {
	string AccountNumber;
	cout << "Please string Account Number for Search\n";
	getline(cin >> ws, AccountNumber);
	return AccountNumber;
}
bool MakeTrueOrFalse(string AccountNumber, vector<sClients>& vClients) {

	for (sClients& C : vClients) {
		if (AccountNumber == C.AccountNumber) {
			C.MarckCorrect = true;
			return true;

		}
	}

	return false;
}
vector<sClients> SaveCleintsDataToFile(string FileName, vector<sClients>vClients) {
	fstream MyFile(FileName, ios::out);
	sClients Client;
	string Line;
	if (MyFile.is_open()) {

		for (sClients C : vClients) {
			if (C.MarckCorrect == false) {

				Line = ConvertToOneLine(C);
				MyFile << Line << endl;
			}

		}
		MyFile.close();
	}
	return vClients;
}
bool DeleteAccountNumberFromFile(string AccountNumber, vector<sClients>vClients) {
	sClients Clients;
	char answare = 'y';

	if (FindClientData(Clients, AccountNumber, vClients)) {

		PrintClientData(Clients);
		cout << "\n\n are you shure you want delete AccountNumber(y/n)?";
		cin >> answare;
		if (toupper(answare) == 'Y') {
			MakeTrueOrFalse(AccountNumber, vClients);
			SaveCleintsDataToFile(FileName, vClients);
			vClients = LoadDataFromFile(FileName);
			cout << "\n\n The delete succesful\n";
		}
		else {
			cout << "\nThe Account still\n";
		}
	}
	else { cout << "\nThe Account Not Found\n"; }
	return true;

}
sClients ReadDataClientafterUpdete(string AccountNumber) {
	sClients Client;
	Client.AccountNumber = AccountNumber;
	cout << "Please enter PinCode\n";
	getline(cin >> ws, Client.PinCode);
	cout << "Please enter Name\n";
	getline(cin, Client.Name);
	cout << "Please enter phone\n";
	getline(cin, Client.phone);
	cout << "Please enter AccountBalance\n";
	cin >> Client.AccountBalance;
	return Client;
}
void ShowExitClientData() {

	cout << "--------------------------------\n";
	cout << "\t The Program End)\n";
	cout << "--------------------------------\n";
}
bool UpdeterAccountNumber(string AccountNumber, vector<sClients>& vClients) {

	char Answer = 'y';

	sClients Clients;
	if (FindClientData(Clients, AccountNumber, vClients)) {

		cout << "\nAre you shure you want Updete Account Number\n";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {
			for (sClients& C : vClients) {
				if (AccountNumber == C.AccountNumber) {
					C = ReadDataClientafterUpdete(AccountNumber);
					break;
				}

			}

			SaveCleintsDataToFile(FileName, vClients);
		}
		else { cout << "\nThe AccoutNumber still,Thank you"; }

	}
	else { cout << "Not Found AccountNumber " << AccountNumber << endl; }
	return 0;
}

//////////////////////deposit

void CalculateDeposite(string AccountNumber, vector<sClients>& vClients) {
	double Amount;
	cout << "Please enter deposit amount?\n";
	cin >> Amount;

	char c;
	cout << "Are you sure you want perform this transaction? y/n ?\n";
	cin >> c;

	if (toupper(c) == 'Y') {
		for (sClients& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += Amount;
				break;
			}
		}
		SaveCleintsDataToFile(FileName, vClients);
		cout << "The Transaction is successful\n";
	}
}
void ShowDeposit() {
	cout << "\n------------------------------------------------------------\n";
	cout << "\t\t\t\tDeposit Screen";
	cout << "\n------------------------------------------------------------\n";
}
void Depoist() {
	ShowDeposit();
	cout << "\n\n";

	vector<sClients> vClients;
	sClients Client;
	string AccountNumber = SearchAccountNumber();

	while (!FindClientData(Client, AccountNumber, vClients)) {
		cout << "\nClient with Account Number (" << AccountNumber << ") does not exist.\n";
		AccountNumber = SearchAccountNumber();
	}

	cout << "\nThe following are the Client Details:\n";
	cout << "--------------------------\n";
	PrintClientData(Client);
	cout << "--------------------------\n";

	CalculateDeposite(AccountNumber, vClients);
}

//////////////////////withdraw

void WithDrawScreen() {
	cout << "____________________________\n";
	cout << "\tWidthdraw Scren:)\n";
	cout << "____________________________\n";
}
void WithDrawClientDataCalculate() {
	vector<sClients>vClients;
	sClients Client;
	string AccountNumber = SearchAccountNumber();

	while (!FindClientData(Client, AccountNumber, vClients)) {
		cout << "\nClient with Account Number (" << AccountNumber << ") does not exist.\n";
		AccountNumber = SearchAccountNumber();
	}

	cout << "\nThe following are the Client Details:\n";
	cout << "--------------------------\n";
	PrintClientData(Client);
	cout << "--------------------------\n";

	double Widthdraw;
	cout << "Please enter Widtdraw amount?\n";
	cin >> Widthdraw;

	char c;
	cout << "Are you sure you want Withdraw from a Bank y/n ?\n";
	cin >> c;
	double sum = 0;
	if (toupper(c) == 'Y') {
		for (sClients& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				if (C.AccountBalance > 0) {
					if (C.AccountBalance >= Widthdraw) {
						C.AccountBalance -= Widthdraw;
					}
					else { cout << "\nSorry you dont widthdraw because Widthdraw more than AccountBalance\n"; }
				}
				else { cout << "\nSorry you don't have many for widthdraw\n" << C.AccountBalance; }
		cout << "The WidthDraw is successful\n";

				break;

			}
		}
		SaveCleintsDataToFile(FileName, vClients);
	}

}
void showWithDraw() {
	WithDrawScreen();
	WithDrawClientDataCalculate();

}

//////////////////////menus

short ReadWhatDoYou() {
	short read;
	cout << "Choose what do you want to do?[1 to 7]?\n";
	cin >> read;
	return read;

}
short ReadWhatDoYouTrans() {
	short read;
	cout << "Choose what do you want to do?[1 to 4]?\n";
	cin >> read;
	return read;
}
void GoBackToMainMenue() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMain();
}
void GoBackToTransactionsMenue() {
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransaction();
}
void SwitchTrans(enTransData Read) {

	switch (Read) {
	case enTransData::Deposit: {
		system("cls");
		Depoist();
		GoBackToTransactionsMenue();
		break;
	}
	case enTransData::Total: {

		system("cls");
		vector<sClients>vClients = LoadDataFromFile(FileName);
		PrintAllDataClientTrans(vClients);

		GoBackToTransactionsMenue();
		break;
	}
	case enTransData::WithDraw: {
		system("cls");

		showWithDraw();
		GoBackToTransactionsMenue();
		break;

	}
	case enTransData::Main: {
		system("cls");

		GoBackToMainMenue();
		break;

	}

	}

}
void ShowTransaction() {
	system("cls");
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "\t\t\t\t\t Transactions Menue Screen\n\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "\t[1]" << "Deposit.\n";
	cout << "\t[2]" << "Withdraw.\n";
	cout << "\t[3]" << "Total Balances.\n";
	cout << "\t[4]" << "Main Menue.\n";

	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	short read = ReadWhatDoYouTrans();

	SwitchTrans((enTransData)read);

}
bool SwitchClientData(enClientData Read) {

	switch (Read) {
	case enClientData::Show: {
		system("cls");
		vector<sClients>vClients = LoadDataFromFile(FileName);
		PrintAllDataClient(vClients);
		GoBackToMainMenue();
		break;
	}
	case enClientData::Add: {
		system("cls");
		ReadDataClientFromFile();
		GoBackToMainMenue();
		break;
	}

	case enClientData::Delete: {
		system("cls");
		vector<sClients>vClients = LoadDataFromFile(FileName);
		string AccountNumber = SearchAccountNumber();
		DeleteAccountNumberFromFile(AccountNumber, vClients);
		GoBackToMainMenue();
		break;

	}
	case enClientData::Update: {
		system("cls");
		vector<sClients>vClients = LoadDataFromFile(FileName);
		string AccountNumber = SearchAccountNumber();
		UpdeterAccountNumber(AccountNumber, vClients);
		GoBackToMainMenue();
		break;

	}
	case enClientData::Find: {

		system("cls");
		vector<sClients>vClients = LoadDataFromFile(FileName);
		string AccountNumber = SearchAccountNumber();
		sClients Client;
		if (FindClientData(Client, AccountNumber, vClients)) {
			cout << "The Client Data Found This is Data\n";
			PrintClientData(Client);

		}
		else {
			cout << "\nNot Found Client Data:" << AccountNumber << "Sorry!" << endl;
		}
		GoBackToMainMenue();
		break;
	}
	case enClientData::Trans: {
		ShowTransaction();
		GoBackToMainMenue();
		break;

	}
	case enClientData::Exit: {
		system("cls");

		ShowExitClientData();
		GoBackToMainMenue();
		break;
	}
	}

	return true;
}
void ShowMain() {
	system("cls");
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "\t\t\t\t\tMain Menue Screen\n\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "\t[1]" << "Show Client List.\n";
	cout << "\t[2]" << "Add New Client.\n";
	cout << "\t[3]" << "Delete Client.\n";
	cout << "\t[4]" << "Update Client Infor.\n";
	cout << "\t[5]" << "Find Client.\n";
	cout << "\t[6]" << "Transactions.\n";
	cout << "\t[7]" << "Exit.\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	short read = ReadWhatDoYou();
	SwitchClientData((enClientData)read);
}

int main()
{

	ShowMain();

	return 0;
}