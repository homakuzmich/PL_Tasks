#include "FindMax.h"

vector<rushHourPeriod>  FindMax(array<float, stringsQuantityMustBeInInput> & sumdDistToCashBoxesEachHalfHour) {

	float max = sumdDistToCashBoxesEachHalfHour[0];
	

	for (int i = 0; i < stringsQuantityMustBeInInput; i++)
		if (sumdDistToCashBoxesEachHalfHour[i] > max)
			max = sumdDistToCashBoxesEachHalfHour[i];

	vector<int> maxLengthsTimes;
	for (int i = 0; i < stringsQuantityMustBeInInput; i++)
		if (max == sumdDistToCashBoxesEachHalfHour[i])
			maxLengthsTimes.push_back(i);

	
	time_t now = time(NULL);

	struct tm nowInTm = *localtime(&now);

	
	nowInTm.tm_hour = 10;
	nowInTm.tm_min = 0;
	nowInTm.tm_sec = 0;

	time_t openingTime = mktime(&nowInTm);

	vector<rushHourPeriod> rushHourPeriods;

										   
	for (unsigned int i = 0, consecutivePeriodsQuantity = 0; i < maxLengthsTimes.size(); i++)
	{																					 
																						
		while ((i != maxLengthsTimes.size() - 1) && (maxLengthsTimes[i + 1] - maxLengthsTimes[i] == 1))
		{
			consecutivePeriodsQuantity++; 
			i++;
		}

		time_t begin = openingTime + halfHour*maxLengthsTimes[i - consecutivePeriodsQuantity];
																							  
		time_t end = begin + halfHour*(consecutivePeriodsQuantity + 1);
		consecutivePeriodsQuantity = 0;

		struct tm begInInTm = *localtime(&begin);
		struct tm endInTm = *localtime(&end);

		rushHourPeriod newOnePeriod;
									 
		newOnePeriod.begin = to_string(begInInTm.tm_hour) + ":" + to_string(begInInTm.tm_min);
		newOnePeriod.end = to_string(endInTm.tm_hour) + ":" + to_string(endInTm.tm_min);
		rushHourPeriods.push_back(newOnePeriod);
	}

	return rushHourPeriods;
}