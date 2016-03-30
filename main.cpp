#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

string readFile(string path) {
	fstream infile;
	infile.open(path);

	string line;
	string res;
	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			res += line;
			res += "\n";
		}
		infile.close();
	}
	return res;
}

void writeFile(string contents, string path)
{
	ofstream outfile;
	outfile.open(path);

	if (outfile.is_open())
	{
		outfile << contents;
	}
	outfile.close();
}

string webVttToSrt(string vtt)
{
	regex r1("(WEBVTT\\s+)");
	regex r2("(\\d{2}:\\d{2}:\\d{2}).(\\d{3}\\s+)-->(\\s+\\d{2}:\\d{2}:\\d{2}).(\\d{3}\\s*)");
	
	string res1;
	regex_replace(back_inserter(res1), vtt.begin(), vtt.end(), r1, "");

	string res2;
	regex_replace(back_inserter(res2), res1.begin(), res1.end(), r2, "$1,$2-->$3,$4");

	return res2;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "usage: " << argv[0] << " <inputfile> <outputfile>\n";
	}
	else
	{
		string vtt(readFile(argv[1]));
		if (!vtt.empty()) 
		{
			writeFile(webVttToSrt(vtt), argv[2]);
		}
		else
		{
			cout << "Input file not found\n";
		}
	}
	return 0;
}
