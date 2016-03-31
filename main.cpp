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

string srtToWebVtt(string srt)
{
	string res("WEBVTT\n\n");
	regex r("(\\d{2}:\\d{2}:\\d{2}),(\\d{3}\\s+)-->(\\s+\\d{2}:\\d{2}:\\d{2}),(\\d{3}\\s*)");

	regex_replace(back_inserter(res), srt.begin(), srt.end(), r, "$1.$2-->$3,$4");

	return res;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cout << "usage: " << argv[0] << " <input format: [vtt|srt]> <inputfile> <outputfile>\n";
	}
	else
	{
		string in(readFile(argv[2]));
		if (!in.empty()) 
		{
			if (string("srt").compare(argv[1]))
			{
				writeFile(webVttToSrt(in), argv[3]);
			}
			else if (string("vtt").compare(argv[1]))
			{
				writeFile(srtToWebVtt(in), argv[3]);
			}
			else
			{
				cout << "Please input either 'srt' or 'vtt' as first argument (found: " << argv[1] << ")";
			}
		}
		else
		{
			cout << "Input file not found\n";
		}
	}
	return 0;
}
