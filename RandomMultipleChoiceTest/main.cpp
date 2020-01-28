
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include <boost/algorithm/string.hpp>

class CSVReader
{
	std::string fileName;
	std::string delimeter;

public:
	CSVReader(std::string filename, std::string delm = ",") :
		fileName(filename), delimeter(delm)
	{ }

	std::vector<std::vector<std::string> > getData();
};

std::vector<std::vector<std::string> > CSVReader::getData()
{
	std::ifstream file(fileName);

	std::vector<std::vector<std::string> > dataList;

	std::string line = "";
	
	while (getline(file, line))
	{
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		dataList.push_back(vec);
	}

	file.close();

	return dataList;
}
int main()
{
	CSVReader reader("D:\\Programming\\Github Repositories\\RandomMultipleChoiceTest\\Debug\\spanish_tpr.csv");

	std::vector<std::vector<std::string> > dataList = reader.getData();
	std::map<std::string, std::string> translations = {};
	std::vector<std::string> spanishWords = {};

	for (std::vector<std::string> vec : dataList)
	{
		translations.insert({ vec[0], vec[1] });
		spanishWords.push_back(vec[0]);
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(spanishWords.begin(), spanishWords.end(), std::default_random_engine(seed));

	int answeredCorrect = 0, answeredIncorrect = 0;
	for (int i = 0; i < spanishWords.size(); ++i)
	{
		std::string optionA, optionB, optionC, optionD;
		std::string spanishWord = spanishWords[i];
		int correctAnswer = int(rand() % 4);
		
		if (correctAnswer == 0)
		{
			optionA = spanishWord;
			optionB, optionC, optionD;
			while (true)
			{
				optionB = spanishWords[int(rand() % spanishWords.size())];
				if (optionB != optionA)
					break;
			}
			while (true)
			{
				optionC = spanishWords[int(rand() % spanishWords.size())];
				if (optionC != optionA && optionC != optionB)
					break;
			}
			while (true)
			{
				optionD = spanishWords[int(rand() % spanishWords.size())];
				if (optionD != optionA && optionD != optionB && optionD != optionC)
					break;
			}
		}

		if (correctAnswer == 1)
		{
			optionB = spanishWord;
			optionA, optionC, optionD;
			while (true)
			{
				optionA = spanishWords[int(rand() % spanishWords.size())];
				if (optionA != optionB)
					break;
			}
			while (true)
			{
				optionC = spanishWords[int(rand() % spanishWords.size())];
				if (optionC != optionB && optionC != optionA)
					break;
			}
			while (true)
			{
				optionD = spanishWords[int(rand() % spanishWords.size())];
				if (optionD != optionB && optionD != optionA && optionD != optionC)
					break;
			}
		}

		if (correctAnswer == 2)
		{
			optionC = spanishWord;
			optionB, optionA, optionD;
			while (true)
			{
				optionB = spanishWords[int(rand() % spanishWords.size())];
				if (optionB != optionC)
					break;
			}
			while (true)
			{
				optionA = spanishWords[int(rand() % spanishWords.size())];
				if (optionA != optionC && optionA != optionB)
					break;
			}
			while (true)
			{
				optionD = spanishWords[int(rand() % spanishWords.size())];
				if (optionD != optionC && optionD != optionB && optionD != optionA)
					break;
			}
		}

		if (correctAnswer == 3)
		{
			optionD = spanishWord;
			optionB, optionC, optionA;
			while (true)
			{
				optionB = spanishWords[int(rand() % spanishWords.size())];
				if (optionB != optionD)
					break;
			}
			while (true)
			{
				optionC = spanishWords[int(rand() % spanishWords.size())];
				if (optionC != optionD && optionC != optionB)
					break;
			}
			while (true)
			{
				optionA = spanishWords[int(rand() % spanishWords.size())];
				if (optionA != optionD && optionA != optionB && optionA != optionC)
					break;
			}
		}

		std::cout << std::endl;
		std::cout << translations[spanishWord] << " Significa:" << std::endl;
		std::cout << "1. " << optionA << std::endl;
		std::cout << "2. " << optionB << std::endl;
		std::cout << "3. " << optionC << std::endl;
		std::cout << "4. " << optionD << std::endl;
		std::cout << std::endl;
		std::string answer;
		std::cin >> answer;
		if (atoi(answer.c_str()) - 1 == correctAnswer)
		{
			std::cout << "Correct" << std::endl;
			answeredCorrect++;
		}
		else
		{
			std::cout << "Incorrect " << correctAnswer + 1 << std::endl;
			answeredIncorrect++;
		}
		std::cout << std::endl;

		Sleep(2000);
		system("cls");
	}

	std::cout << std::endl;
	std::cout << "Accuracy: " << answeredCorrect << "/" << answeredIncorrect + answeredCorrect << std::endl;

	return 0;
}