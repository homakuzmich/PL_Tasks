#include <iostream>
#include <fstream>
#include <regex>
#include "Point.h"
#include "CheckingInputFile.h"
#include "CheckingUsersPoint.h"

using namespace std;


int main()
{
	if (checkingInputFile())
	{
		vector<Point> myVector;//вектор хранит координаты вершин(Point) четырехугольника
		myVector.reserve(stringsQuantityMustBeInInput);

		ifstream fin("input.txt");
		regex rxStringForApex("-?[0-9]+(\\.[0-9]{1,8})?");

		smatch result;//строка в которую
		string buffer;

		for (int i = 0; i < stringsQuantityMustBeInInput; i++)
		{													  
			fin >> buffer; 
			Point apex;
			for (int j = 0; j < coordinatesQuantity; j++)
			{
				regex_search(buffer, result, rxStringForApex);
															  
				if (!j)
					apex.SetX(stod(result[0]));
				else
					apex.SetY(stod(result[0]));
				buffer = result.suffix().str();
											   										   
			}
			myVector.push_back(apex);
		}

		fin.close();


		Point myPoint;
		string temp;

		regex rxStringInInput("(((0|(-?[1-9][0-9]{0,7}))(\\.[0-9]{0,8})?)|(-0\\.[0-9]{0,8}))");
		

		bool checkX = false, checkY = false;
											
		while (!checkX || !checkY)
		{
			if (checkX == false)
			{
				cout << "Enter X value for a point: ";
				cin >> temp;

				if (regex_match(temp, rxStringInInput))
													   
				{
					myPoint.SetX(stod(temp));
					checkX = true;			 
				}
				else                          
				{
					cout << "Invalid value\n" << temp << endl;
					continue;								  
				}
			} 
			if (checkY == false)
			{
				cout << "Enter Y value for a point: ";
				cin >> temp;

				if (regex_match(temp, rxStringInInput))
				{
					myPoint.SetY(stod(temp));
					checkY = true;
				}
				else
				{
					cout << "Invalid value\n";
					continue;
				}
			}
		}

		checkingUsersPoint(myPoint, myVector);  
											  
	}
	return 0;
}