#include "main.h"
#include "categories.h"
namespace ssbm
{

	double balance;
	void ssbm::getVersion()
	{
		char* logBuff = new char[100];
		sprintf_s(logBuff, 100, "%s version %s%s for %s", name, MajorVersion, minorVersion, platform);
		ssbm::writeLog(logBuff, 2);
		delete[] logBuff;
	}

	int ssbm::menu()
	{
		std::ifstream balance_file;
		std::vector<category> category_hold = *category::loadCategories();
		balance_file.open("balance.db", std::ios::in);
		if (balance_file.is_open() == 0)
		{
			balance = 0;
		}
		else
		{
			balance_file >> balance;
			balance_file.close();
		}
		unsigned int Changer = 0;
		while (Changer != 3)
		{
			system("cls");
			ssbm::getVersion();
			char* logbuff = new char[100];
			sprintf(logbuff, "Your current balance is %.2f RUR", balance);
			writeLog(logbuff, 2);
			delete[] logbuff;
			//	std::cout << name << " " << MajorVersion << minorVersion << " for " << platform << std::endl;
			std::cout << "1) Expense" << std::endl;
			std::cout << "2) Income" << std::endl;
			std::cout << "3) Exit" << std::endl;

			std::cin >> Changer;
			double summ;
			CATID category = 0;
			switch (Changer)
			{
			case 1:
				std::cout << "What categories of Expence did you specify" << std::endl;
				category = category::selectCategory(&category_hold, 0);
				std::cout << "Specify how much money did you spent" << std::endl;
				std::cin >> summ;
				get(summ, category, &category_hold);
				break;
			case 2:
				std::cout << "What categories of income did you specify" << std::endl;
				category = category::selectCategory(&category_hold, 1);
				std::cout << "Specify how much money did you get" << std::endl;
				std::cin >> summ;
			//	get(summ, category, *category_hold);
				break;
			case 3:
				break;
			}

			std::ofstream balance_out;
			balance_out.open("balance.db", std::ios::out);
			balance_out << balance;
			balance_out.close();
		}
		return 0;
	}

	int ssbm::pay(double summ, CATID id, std::vector<ssbm::category>* category_hold)
	{
		balance -= summ;
		ssbm::category::changeCount(id, summ, category_hold, false);
		return 0;
	}
	int ssbm::get(double summ, CATID id, std::vector<ssbm::category>* category_hold)
	{
		balance += summ;
		ssbm::category::changeCount(id, summ, category_hold, true);
		return 0;
	}
	void addOperation(double summ, CATID id, bool type, std::vector<ssbm::category>& cat)
	{
		std::ofstream file("operations.ops", std::ios::app);
		time_t t;
		struct tm *t_m;
		t = time(NULL);
		t_m = localtime(&t);
		char side[20];
		if (type == false)
		{
			strcpy(side, "expence");
		}
		else
		{
			strcpy(side, "profit");
		}
		char catName[100];
		file << t_m->tm_hour << ":" << t_m->tm_min << ":" << t_m->tm_sec << " " << summ << " " << side << " " << "" << std::endl;
		file.close();
	}

}