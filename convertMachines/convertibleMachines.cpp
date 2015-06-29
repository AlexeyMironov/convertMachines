#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct vectorItem
{
	string condition;
	string outputSymbol;
};

int inpSymbCount = 0, outpSymbCount = 0, topsCount = 0;
string automaticType;

bool operator ==(const vectorItem &n1, const vectorItem &n2)
{
	return (n1.condition == n2.condition) && (n1.outputSymbol == n2.outputSymbol);
}

int StringToInteger(const string &strToInt)
{
	return atoi(strToInt.c_str() + 1);
}

void FromMiliToMura(ifstream &inputFile, ofstream &outputFile)
{
	vector<vector<vectorItem>> mainTable2(inpSymbCount);	
	vector<vectorItem> topLine;
	for (int i = 0; i < inpSymbCount; ++i)
	{
		mainTable2[i].resize(topsCount);
		vectorItem currNode;
		for (int j = 0; j < topsCount; ++j)
		{
			inputFile >> currNode.condition >> currNode.outputSymbol;

			if (find(topLine.begin(), topLine.end(), currNode) == topLine.end())
			{
				topLine.push_back(currNode);
			}
			mainTable2[i][j] = currNode;
		}
	}

	vector<string> outputSymbols;
	sort(topLine.begin(), topLine.end(), [](const vectorItem &first, const vectorItem &second){return StringToInteger(first.condition) < StringToInteger(second.condition); });
	for (unsigned int i = 0; i < topLine.size(); ++i)
	{
		int index = 0, mainIndex = 0;
		index = StringToInteger(topLine[i].condition);
		for (int j = 0; j < inpSymbCount; ++j)
		{
			mainIndex = find(topLine.begin(), topLine.end(), mainTable2[j][index]) - topLine.begin();
			outputFile << "Q" << mainIndex;
			if (j == inpSymbCount - 1)
			{
				outputFile << "\n";
			}
			else
			{
				outputFile << ' ';
			}
		}
	}
}

void FromMuraToMili(ifstream &inputFile, ofstream &outputFile)
{
	vector<string> outputSymbols;
	vector<vector<string>> mainTable;
	string outputSymbol;
	for (int i = 0; i < topsCount; i++)  //считытваем выходные символы
	{
		inputFile >> outputSymbol;
		outputSymbols.push_back(outputSymbol);
	}

	mainTable.resize(inpSymbCount);
	for (int i = 0; i < inpSymbCount; ++i) //считываем таблицу переходов
	{
		mainTable[i].resize(topsCount);
		for (int j = 0; j < topsCount; ++j)
		{
			inputFile >> mainTable[i][j];
		}
	}
	string first, second;
	int number = 0;
	for (int i = 0; i < inpSymbCount; ++i)
	{
		for (int j = 0; j < topsCount; ++j)
		{
			first = mainTable[i][j];
			number = StringToInteger(first);
			outputFile << first << outputSymbols[number] << " ";
		}
		outputFile << "\n";
	}
}

int main(int argc, char* argv[])
{
	string fileInputName = "input.txt";
	string fileOutputName = "output.txt";
	ifstream inputFile(fileInputName, ifstream::in);
	if (!inputFile.good())
	{
		return 1;
	}
	ofstream outputFile(fileOutputName, ios::out);

	inputFile >> inpSymbCount >> outpSymbCount >> topsCount >> automaticType;
	if (automaticType == "MR")
	{
		FromMuraToMili(inputFile, outputFile);
	}

	else if (automaticType == "ML")
	{
		FromMiliToMura(inputFile, outputFile);
	}
	inputFile.close();
	outputFile.close();
	return 0;
}