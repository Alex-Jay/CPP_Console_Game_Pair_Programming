//
// Title: C++ CA1 Console Game
// Authors: Aleksandrs Jevdokimovs & Ryan Dullaghan
// License: GNU GENERAL PUBLIC LICENSE V3
// Description: C++ Console Game using ASCII characters as visuals.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> parseMapFile(const string fileName)
{
	vector<string> mapArray;

	ifstream file(fileName);
	string line;

	if (file.is_open()) //Test if File Opens Successfully
	{
		while (file.good()) //Loop While File Is In A Good State
		{
			getline(file, line);

			if (!line.empty()) //Make Sure Line is Not Empty
			{
				mapArray.push_back(line);
			}
		}
		file.close(); //Close File
	}

	return mapArray;
}

void drawMap(const vector<string>& mapArray)
{
	for (string line : mapArray)
	{
		cout << line << endl;
	}
}

int main()
{
	drawMap(parseMapFile("Map1.txt")); //Parse Map File and Draw It In Console

	system("pause");
    return 0;
}