#pragma once

#include <iostream>
#include <fstream>
#include <iterator>
#include <set>
#include <string>

using namespace std;

class Utility
{
public:
	static set<int> WriteHighScore(int score)
	{
		//Read in text files for player scores
		string file = "HighScore.txt";
		ifstream highScoreFile(file);
		istream_iterator<int> start(highScoreFile), end;
		set<int> highscores(start, end);
		highScoreFile.close();

		//Populate and save player scores
		if (highscores.size() == 0)
		{
			highscores.insert(100);
			highscores.insert(50);
			highscores.insert(20);
			highscores.insert(10);
			highscores.insert(5);
			ofstream outfile(file);

			ostream_iterator<int> output_iterator(outfile, "\n");
			copy(highscores.begin(), highscores.end(), output_iterator);

			outfile.close();
		}

		highscores.insert(score);
		highscores.erase(highscores.begin());

		ofstream outfile(file);
		ostream_iterator<int> output_iterator(outfile, "\n");
		copy(highscores.begin(), highscores.end(), output_iterator);
		outfile.close();

		return highscores;
	}
};