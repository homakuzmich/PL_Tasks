#include "CheckingUsersPoint.h"


void checkingUsersPoint(Point point, vector<Point> &apex)
{   
	if (apex[0] == point || apex[1] == point || apex[2] == point || apex[3] == point)
	{
		cout << "The point is the quadrangles apex\n";
		return;										  
	}
	
	double firstSideChek = FindPointsLocationRelativelyToQuadranglesSide(apex[0], apex[1], apex[2], point);
	double secondSideCheck = FindPointsLocationRelativelyToQuadranglesSide(apex[1], apex[2], apex[3], point);
	double thirdSideCheck = FindPointsLocationRelativelyToQuadranglesSide(apex[2], apex[3], apex[0], point);
	double fourthSideCheck = FindPointsLocationRelativelyToQuadranglesSide(apex[3], apex[0], apex[1], point);
	

	if (firstSideChek >= 0 && secondSideCheck >= 0 && thirdSideCheck >= 0 && fourthSideCheck >= 0)
		
	{
		if (firstSideChek == 0 || secondSideCheck == 0 || thirdSideCheck == 0 || fourthSideCheck == 0)
			
			cout << "The point belongs to the side of quadrangle\n";
		else
			
			cout << "The point belongs to quadrangle\n";
	}
	else
		
		cout << "The point is outside the quadrangle\n";
}

double FindPointsLocationRelativelyToQuadranglesSide(Point linesFirstPoint, Point linesSecondPoint, Point quadranglesNotInLinePoint, Point checkedPoint) {

	return ((quadranglesNotInLinePoint.GetX() - linesFirstPoint.GetX())*(linesSecondPoint.GetY() - linesFirstPoint.GetY()) -
		(quadranglesNotInLinePoint.GetY() - linesFirstPoint.GetY())*(linesSecondPoint.GetX() - linesFirstPoint.GetX()))
		*
		((checkedPoint.GetX() - linesFirstPoint.GetX())*(linesSecondPoint.GetY() - linesFirstPoint.GetY()) -
		(checkedPoint.GetY() - linesFirstPoint.GetY())*(linesSecondPoint.GetX() - linesFirstPoint.GetX()));
}