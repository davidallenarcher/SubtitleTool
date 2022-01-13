#pragma once
#include <string>
#include <list>
#include "SrtSubtitle.h"

using namespace std;

class AssWriter
{
public:
	AssWriter();
	void write(const char* assFileName, list<SrtSubtitle>& srtSubtitles);
};

