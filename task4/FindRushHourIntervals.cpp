
#include "FindRushHourIntervals.h"

multiset<Interval> FindRushHourIntervals(vector<Interval>* intervalsVector)
{
	vector<Interval> &rIntervalsVeсtor = *intervalsVector;

	multiset<Interval>* intervalsSet = new multiset<Interval>;

	
	Interval nominal;

	tm IntervalsCameTime;
	localtime_s(&IntervalsCameTime, &now);
	tm IntervalsGoneTime;
	localtime_s(&IntervalsGoneTime, &now);

	IntervalsCameTime.tm_hour = 8;//устанавливаем в начало интервала время открытия банка
	IntervalsCameTime.tm_min = 0;
	IntervalsGoneTime.tm_hour = 22;//устанавливаем в конец интервала время закрытия банка
	IntervalsGoneTime.tm_min = 0;

	nominal.setBeginTime(mktime(&IntervalsCameTime));
	nominal.setEndTime(mktime(&IntervalsGoneTime));
	nominal.setClientsQuantity(0);

	intervalsSet->insert(nominal);
	multiset<Interval> * willBeInsertedSet = new multiset<Interval>;
	
	for (unsigned int i = 0; i < rIntervalsVeсtor.size(); i++)
	{
		EraseIndexes eraseIndexesInstance;

		Interval temp = rIntervalsVeсtor[i];

											
		for (auto j = intervalsSet->begin(); j != intervalsSet->end(); j++, eraseIndexesInstance.incrementEraseEndIndex())
		{

			
			if (temp.getBeginTime() >= j->getBeginTime() && temp.getBeginTime() < j->getEndTime())
			{

				
				eraseIndexesInstance.setEraseBeginIndex(eraseIndexesInstance.getEraseEndIndex() - 1);

				
				int leftDifference = static_cast<int>(difftime(temp.getBeginTime(), j->getBeginTime()));
				int rightDifference = static_cast<int>(difftime(j->getEndTime(), temp.getEndTime()));

				
				if (leftDifference == 0) 
				{
					Interval prevInterval;
										  
					if (j != intervalsSet->begin()) 
					{
						j--;
						prevInterval = *j;
						j++;
					}
					if ((j->getClientsQuantity() + 1) == prevInterval.getClientsQuantity())
						
					{
						
						eraseIndexesInstance.setEraseBeginIndex(eraseIndexesInstance.getEraseBeginIndex() - 1);

						if (rightDifference > 0)
						{
							prevInterval.setEndTime(temp.getEndTime());

							Interval leftoverInterval = *j;
							leftoverInterval.setBeginTime(temp.getEndTime());

							willBeInsertedSet->insert(prevInterval);
							willBeInsertedSet->insert(leftoverInterval);

							break;
						}
						else
						{
							prevInterval.setEndTime(j->getEndTime());
							willBeInsertedSet->insert(prevInterval);
							if (rightDifference == 0)
								break;
							else
								temp.setBeginTime(j->getEndTime());
						}

					}
					else
					{
						if (rightDifference > 0)
						{
							Interval layeredInterval = temp;
							layeredInterval.setClientsQuantity(j->getClientsQuantity() + 1);

							Interval leftoverInterval = *j;
							leftoverInterval.setBeginTime(temp.getEndTime());

							willBeInsertedSet->insert(layeredInterval);
							willBeInsertedSet->insert(leftoverInterval);

							break;
						}
						else
						{
							Interval layeredInterval = *j;
							layeredInterval.setClientsQuantity(layeredInterval.getClientsQuantity() + 1);
							willBeInsertedSet->insert(layeredInterval);
							if (rightDifference == 0)
								break;
							else
								temp.setBeginTime(j->getEndTime());
						}

					}
				}

				if (leftDifference > 0 && rightDifference <= 0)
				{
					Interval layeredInterval = temp;
					layeredInterval.setClientsQuantity(j->getClientsQuantity() + 1);
					layeredInterval.setEndTime(j->getEndTime());

					Interval leftoverInterval = *j;
					leftoverInterval.setEndTime(temp.getBeginTime());

					willBeInsertedSet->insert(layeredInterval);
					willBeInsertedSet->insert(leftoverInterval);

					if (rightDifference == 0)
					{
						break;
					}
					else
					{
						temp.setBeginTime(j->getEndTime());
					}
				}

				if (leftDifference > 0 && rightDifference > 0)
				{
					Interval layeredInterval = temp;
					layeredInterval.setClientsQuantity(j->getClientsQuantity() + 1);

					Interval leftLeftoverInterval = *j;
					leftLeftoverInterval.setEndTime(temp.getBeginTime());

					Interval rightLeftoverInterval = *j;
					rightLeftoverInterval.setBeginTime(temp.getEndTime());


					willBeInsertedSet->insert(layeredInterval);
					willBeInsertedSet->insert(leftLeftoverInterval);
					willBeInsertedSet->insert(rightLeftoverInterval);

					break;
				}
				
			}
		}

		multiset<Interval>::iterator beginIterator = intervalsSet->begin();
		advance(beginIterator, eraseIndexesInstance.getEraseBeginIndex()); 
																		   

		multiset<Interval>::iterator endIterator = intervalsSet->begin();
		advance(endIterator, eraseIndexesInstance.getEraseEndIndex());
																	  

		intervalsSet->erase(beginIterator, endIterator);
		intervalsSet->insert(willBeInsertedSet->begin(), willBeInsertedSet->end());
		willBeInsertedSet->erase(willBeInsertedSet->begin(), willBeInsertedSet->end());
	}

	/*тут можно посмотреть в какие интервалы времени сколько людей было===========================================================================
	for (multiset<Interval>::iterator j = intervals->begin(); j != intervals->end(); j++)
	{
	struct tm a;
	const time_t IntervalsCameTime = j->getBeginTime();
	localtime_s(&a, &IntervalsCameTime);
	struct tm b;
	const time_t IntervalsGoneTime = j->getEndTime();
	localtime_s(&b, &IntervalsGoneTime);
	cout << a.tm_hour << ":" << a.tm_min << "-" << b.tm_hour << ":" << b.tm_min << "	" << j->getClientsQuantity() << endl;
	}
	//==============================================================================================================================================
	//*/

	//находим интервал с самым большим колличеством людей в нем
	//==========================================================================================
	int peopleQuantity = 0;

	for (auto i = intervalsSet->begin(); i != intervalsSet->end(); i++)
	{
		if (i->getClientsQuantity() > (unsigned)peopleQuantity)
			peopleQuantity = i->getClientsQuantity();
	}
	//==========================================================================================
	multiset<Interval> rushHourIntervalsSet;

	//все интервалы с наибольшим колличеством людей в нем записываем в возвращаемое функцией множество rushHourIntervalsSet
	//==========================================================================================
	for (auto i = intervalsSet->begin(); i != intervalsSet->end(); i++)
	{
		if (i->getClientsQuantity() == peopleQuantity)
			rushHourIntervalsSet.insert(*i);
	}
	//==========================================================================================

	//удаляем лишние указатели на объекты в динамической памяти
	//==========================================================================================
	delete intervalsSet;
	delete &rIntervalsVeсtor;
	delete willBeInsertedSet;
	//==========================================================================================

	return rushHourIntervalsSet;
}
