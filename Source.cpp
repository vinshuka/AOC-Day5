#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>


//Day5 Part 1
//The first 7 characters will either be F or B; these specify exactly one of the 128 rows on the plane(numbered 0 through 127).Each letter tells you
//which half of a region the given seat is in.Start with the whole list of rows; the first letter indicates whether the seat is in the front(0 through 
//63) or the back(64 through 127).The next letter indicates which half of that region the seat is in, and so on until 
//you're left with exactly one row.
//The last three characters will be either L or R; these specify exactly one of the 8 columns of seats on the plane(numbered 0 through 7).The same process
//as above proceeds again, this time with only three steps.L means to keep the lower half, while R means to keep the upper half.
//Once you have the row and col, simply multiply the row by 8 and add the col to get the seat ID, the answer is the highest seat id out of all seats
//in the puzzle input.

//After a bit of research I discovered that the seat codes are just representative of 1 and 0s in binary and the result will be the decimal value of that
//binary number, in this case F = 0 and B = 1, and L = 0 and R = 1. So our example code of FBFBBFFRLR is FBFBBFF = 0101100 = 44 and RLR = 101 = 5 so
//44 * 8 + 5 = 357. We can get our answer by calculating each code and comparing it to a current highest number if its greater it becomes the new
//highest number, repeat until the whole list is done.

//Day5 Part 2
//Now that we know the maximum id we need to find our seat ID, the plan doesn't have some of the seats at the very front or very back, but you will have
//the ids that are 1 < your id and 1 > your id, only your id will be missing as the flight is full.

//Since we know the max seat id, lets also find the minimum seat id, then we can divide the max in half, and have two values one will go from the center
//value to the lowest and the other will go from the center value to the highest, each time we will search our ids to see if that number is there, if it
//is we will decrement our lower value and increment our higher value, when we do get a value that is not in the list that will be our seat id so return it

int rowArr[8] = { 64, 32, 16, 8, 4, 2, 1 };
int colArr[3] = { 4, 2, 1 };

std::vector<std::string> getPuzzleInput()
{
	std::vector<std::string> input;

	std::ifstream file;
	std::string line;
	file.open("puzzle-input.txt");
	int count = 0;
	while (std::getline(file, line))
	{
		input.push_back(line);
	}

	return input;
}

int findAnswerPart1(std::vector<std::string> input)
{
	int highest = 0;

	for (auto s : input)
	{
		std::string row = s.substr(0, 7);
		std::string col = s.substr(7);

		int x = 0;
		int y = 0;

		for (int i = 0; i < row.length(); i++)
		{
			if (row[i] == 'B')
				x += rowArr[i];
		}

		for (int i = 0; i < col.length(); i++)
		{
			if (col[i] == 'R')
				y += colArr[i];
		}

		int result = x * 8 + y;

		if (result > highest)
			highest = result;
	}

	return highest;
}

std::vector<int> findHighestLowest(std::vector<std::string> input)
{
	int highest = 0;
	int lowest = INT_MAX;

	std::vector<int> list;

	for (auto s : input)
	{
		std::string row = s.substr(0, 7);
		std::string col = s.substr(7);

		int x = 0;
		int y = 0;

		for (int i = 0; i < row.length(); i++)
		{
			if (row[i] == 'B')
				x += rowArr[i];
		}

		for (int i = 0; i < col.length(); i++)
		{
			if (col[i] == 'R')
				y += colArr[i];
		}

		int result = x * 8 + y;

		list.push_back(result);

		if (result > highest)
			highest = result;
		if (result < lowest)
			lowest = result;
	}
	std::cout << "Highest: " << highest << '\n';
	std::cout << "Lowest: " << lowest << '\n';

	return list;
}

int findAnswerPart2(std::vector<int> input)
{
	int minus = 493;
	int plus = 494;

	while (minus > 96 || plus < 987)
	{
		auto m = find(input.begin(), input.end(), minus);
		if (m != input.end())
		{
			minus--;
		}
		else
		{
			return minus;
		}
		
		auto p = find(input.begin(), input.end(), plus);
		if (p != input.end())
		{
			plus++;
		}
		else
		{
			return plus;
		}

	}
}




int main()
{
	std::vector<std::string> input = getPuzzleInput();

	//std::cout << findAnswerPart1(input) << '\n';

	std::vector<int> ids = findHighestLowest(input);

	std::cout << findAnswerPart2(ids) << '\n';

	return 0;
}