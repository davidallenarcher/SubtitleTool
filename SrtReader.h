#pragma once
//#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>
#include "SrtSubtitleLine.h"

using namespace std;

class SrtReader
{
private:
	

public:
	SrtReader();
	void read(string srtFileName, list<SrtSubtitleLine> &srtSubtitleLines);
private:
	bool readSubtitleLine(SrtSubtitleLine &subtitleLine);
};

