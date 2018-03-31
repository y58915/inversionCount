#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int lines = 0;			//record the lines of problems
int inversion;			//record the total inversion counts
vector <int> input;		//record the input for each problem

void mergeSort(vector <int> & input);
void merge(vector <int> & tempB, vector <int> & tempC, vector <int> & input);

int main()
{
	string tempInput;			//temp variable for input the lines

	ifstream inf("input.txt");

	//get the total lines of problems
	if (!inf)
	{
		cout << "Cannot find the file" << endl;
	}
	else
	{
		inf >> lines;
	}

	//ignore the enter and get ready for input
	inf.ignore();


	while (lines != 0)
	{
		//initiate the recorder;
		inversion = 0;

		//get the line of problem
		getline(inf, tempInput);

		//transfer string into vector of ints
		istringstream iss(tempInput);
		int tempNum;
		while(iss >> tempNum)
		{
			input.push_back(tempNum);
		}

		//core function
		mergeSort(input);

		cout << "The sequence has "
			<< inversion
			<< " inversions." << endl;

		//clean the data
		lines--;
		input.clear();
		tempInput = "";
	}

	return 0;
}


//this function is to split the vectors recursively
void mergeSort(vector <int> & input)
{
	//the two temp vectors for breaking the input
	vector <int> tempB, tempC;

	if (input.size() > 1)
	{
		for (int i = 0; i < input.size() / 2; i++)
		{
			tempB.push_back(input[i]);
		}
		for (int i = input.size() / 2; i < input.size(); i++)
		{
			tempC.push_back(input[i]);
		}


		//recursion
		mergeSort(tempB);
		mergeSort(tempC);

		//merge function
		merge(tempB, tempC, input);
	}
}


//this function is to merge and sort the splited vectors
//meanwhile, count the inversion counts at the same time
void merge(vector <int> & tempB, vector <int> & tempC, vector <int> & input)
{

	//initiate indexes
	int i = 0, j = 0, k = 0;

	while (i < tempB.size() && j < tempC.size())
	{
		if (tempB[i] <= tempC[j])
		{
			input[k] = tempB[i];
			i++;
		}
		else
		{
			input[k] = tempC[j];
			j++;
			//inversion counts will increase in this case
			inversion += tempB.size() - i;
		}
		k++;
	}

	if (i == tempB.size())
	{
		for (j; j < tempC.size(); j++)
		{
			input[k] = tempC[j];
			k++;
		}
	}
	else
	{
		for (i; i < tempB.size(); i++)
		{
			input[k] = tempB[i];
			k++;
		}
	}
}