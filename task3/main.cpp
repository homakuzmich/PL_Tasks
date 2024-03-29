#include "CheckingInputFile.h"
#include "FindMax.h"
#include <ctime>
#include <array>
using namespace std;

int main() {

	if (checkingInputFile())
	{
		array<float, stringsQuantityMustBeInInput> sumdDistToCashBoxesEachHalfHour = { { 0.f } };

		for (int i = 0; i < inputFilesQuantity; i++)
			
		{	
			string filesName = "Cash" + to_string(i + 1) + ".txt";

			string buffer;  
			ifstream fin(filesName);

			for (int j = 0; j < stringsQuantityMustBeInInput; j++)
			{
				fin >> buffer;//считываем по слову из файла
				sumdDistToCashBoxesEachHalfHour[j] += stof(buffer);
																   
			}
			fin.close();
			
		}

		
		vector<rushHourPeriod> rushHourPeriods = FindMax(sumdDistToCashBoxesEachHalfHour);
		cout << "RushHour periods are:\n";//вывод на экран интервалов максимальной нагрузки
		for (unsigned int i = 0; i < rushHourPeriods.size(); i++)
		{
			cout << rushHourPeriods[i].begin << " - " << rushHourPeriods[i].end << endl;
		}


	}
	return 0;
}