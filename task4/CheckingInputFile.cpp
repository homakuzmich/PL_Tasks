#include "CheckingInputFile.h"

bool checkingInputFile(vector<Interval>* intervalsVector)
{
	string buffer;
	ifstream fin("input.txt");
	if (!fin.is_open()) 
	{
		cout << "File can not be opened\n"; 
		return false;
	}

	else
	{
		//проверка заполнен ли файл вообще чем либо================================================================
		fin >> buffer;
		if (buffer == "") {
			cout << "Input file is empty\n";
			return false;
		}
		fin.seekg(0, ios::beg);


		regex rxForStringInInput("((((0[8-9])|(1[0-9])|(2[0-1])):[0-5][0-9]))-((((0[8-9])|(1[0-9])|(2[0-1])):[0-5][0-9])|(22:00))");
		//регулярное выражение, которым проверяется подходит ли слово, чтоб стать временем прихода и ухода клиента
		regex rxForParsing("[0-9][0-9]"); //регулярное выражение для парсинга строки из входного файла
		smatch result;
		int numberOfCheckedStrings = 0;

		while (true)
		{

			fin >> buffer; 

			if (fin) 
			{
				Interval newInterval;
				if (regex_match(buffer, rxForStringInInput))
				{
					numberOfCheckedStrings++;

					tm IntervalsCameTime;
					localtime_s(&IntervalsCameTime, &now);
					tm IntervalsGoneTime;
					localtime_s(&IntervalsGoneTime, &now);


					for (int i = 0; i < 4; i++)

						regex_search(buffer, result, rxForParsing);

						switch (i)
						{
						case 0: {
							IntervalsCameTime.tm_hour = stoi(result[0]);
							break;
						}
						case 1: {
							IntervalsCameTime.tm_min = stoi(result[0]);
							break;
						}
						case 2: {
							IntervalsGoneTime.tm_hour = stoi(result[0]);
							break;
						}
						case 3: {
							IntervalsGoneTime.tm_min = stoi(result[0]);
							break;
						}
						default:
							break;
						}

						buffer = result.suffix().str();
					}


					newInterval.setBeginTime(mktime(&IntervalsCameTime));
					newInterval.setEndTime(mktime(&IntervalsGoneTime));

																	   
					if (static_cast<int>(difftime(newInterval.getEndTime(), newInterval.getBeginTime())) < oneMinute)
					{//в случае не выполнения данного условия выводится соответствующее сообщение об ошибке
						cout << "Error in value " << numberOfCheckedStrings << ". Each  client's gone time musn't be less than clients came \n";
						return false;
					}
					//проверка упорядоченности входного файла (для удобства было решено чтобы время прихода кажого последующего клиента банка было
					//не раньше предыдущего)
					if ((intervalsVector->size() > 0) && (intervalsVector->back().getBeginTime() > newInterval.getBeginTime()))
					{//в случае не выполнения данного условия выводится соответствующее сообщение об ошибке
						cout << "Error in value " << numberOfCheckedStrings
							<< ". Each subsequent Interval's coming time musn't be less than coming time of the previous one\n";
						return false;
					}
					else //в случае удачных предыдущих проверок записываем в вектор новый интервал
						intervalsVector->push_back(newInterval);

				}

				else//в противном случае если слово не подходит под регулярное выраение 
				{//выводим соответствующее сообщение об ошибке
					cout << "There is some error in input file in value number " << numberOfCheckedStrings + 1 << "\n";
					return false;
				}
			}


			else//в противном случае (когда файл завершен)
				break;//завершаем выполнение цикла

		}
		fin.close();

	}
	return true;
}