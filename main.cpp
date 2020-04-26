#include <iostream>
#include <fstream>
#include <string>
#include <cfloat>

#include "CETSP.h"
#include "City.h"
#include "Vector.h"

using namespace std;

int main(int argc, char **argv)
{
	/*cout << "\n\t\t\tWelcome to TCESP problem solver \n";

	if (argc != 3)
	{
		cout << " APPLICATION INPUT ERROR : " << endl << " Please use CETSP.exe in this way,\n  " <<
			"CETSP.exe [address : input file] [address : output file]" << endl;

		return EXIT_FAILURE;
	}
	
	fstream inputFileStream(argv[1], ios::in);
	*/

	fstream inputFileStream("example.txt", ios::in);
	if (!inputFileStream.is_open())
	{
		cout << " FILE ERROR: input file can not be opened ... " << endl;

		return EXIT_FAILURE;
	}
	else
		cout << " Reading from input file, Please wait ..." << endl;

	index problemsNumber = 0; // number of problems ( test cases )
	inputFileStream >> problemsNumber;

	for (size_t i = 0; i < problemsNumber; i++)
	{
		cout << endl << " Problem Number " << i+1 << endl << endl;

		index cityNumbers, startPointIndex;
		inputFileStream >> cityNumbers >> startPointIndex;

		cout << endl << " Number Of cities : " << cityNumbers << endl << " Start Point : " << startPointIndex << endl;

		if (startPointIndex > cityNumbers)
		{
			cout << endl << "INPUT ERROR : Sorry but problem #" << i << " has wrong start point!"
				<< endl << "-> skipped ." << endl;

			continue;
		}

		if (cityNumbers < 3)
		{
			cout << endl << "INPUT ERROR : Sorry but problem #" << i << " has not enough number of cities, \n\tit must contain more than 2 cities."
				<< endl << "-> skipped ." << endl ;

			continue;
		}

		vector<City> cityList;

		for (index i = 0; i < cityNumbers; i++)
		{
			City objCity(i);

			inputFileStream >> objCity;

			cityList.push_back(objCity);
		}

		CETSP objCETSP(cityList, --startPointIndex);

		string result = objCETSP.solve();

		cout << endl << endl << "Result : " << endl << endl << 
			result << endl << "Done ! going for next problem ..." <<
			endl << endl << endl;
	}

	cout << " All done ! Press enter to exit ...";

	inputFileStream.close();

	fflush(stdin);
	getchar();

	return EXIT_SUCCESS;
}
