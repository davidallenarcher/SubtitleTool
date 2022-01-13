#include "SrtReader.h"

ifstream srtFile;

string indexPattern = "\\d+";
string timePattern = "\\d\\d:\\d\\d:\\d\\d,\\d\\d\\d --> \\d\\d:\\d\\d:\\d\\d,\\d\\d\\d$";

SrtReader::SrtReader()
{
}

void SrtReader::read(string srtFileName, list<SrtSubtitleLine> &srtSubtitleLines)
{
	srtFile.open(srtFileName);
	
	if (srtFile.good())
	{
		SrtSubtitleLine subtitleLine;
		string line;

		regex index(indexPattern);
		regex time(timePattern);

		int count = 0;
		while (getline(srtFile, line))
		{
			subtitleLine = {};
			if (regex_match(line, index)) {
				subtitleLine.index = stoi(line);
				getline(srtFile, line);
				if (regex_match(line, time))
				{
					subtitleLine.startTime.hour = stoi(line.substr(0, 2));
					subtitleLine.startTime.minute = stoi(line.substr(3, 2));
					subtitleLine.startTime.second = stoi(line.substr(6, 2));
					subtitleLine.startTime.milliSecond = stoi(line.substr(9, 3));
					subtitleLine.endTime.hour = stoi(line.substr(17, 2));
					subtitleLine.endTime.minute = stoi(line.substr(20, 2));
					subtitleLine.endTime.second = stoi(line.substr(23, 2));
					subtitleLine.endTime.milliSecond = stoi(line.substr(26, 3));

					getline(srtFile, line);
					do {
						subtitleLine.lines.push_back(line);
						getline(srtFile, line);
					} while (line.size() > 0);

					srtSubtitleLines.push_back(subtitleLine);
				}
			}
			count++;
		}

		printf("count: %d\n",count);

		srtFile.close();
	}
}

bool SrtReader::readSubtitleLine(SrtSubtitleLine &subtitleLine)
{
	regex index(indexPattern);

	return false;
}

