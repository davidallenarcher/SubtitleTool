#pragma once
#include <string>
#include <list>
#include "SrtSubtitleLine.h"

using namespace std;

struct SrtSubtitle
{
	string language;
	list<SrtSubtitleLine> subtitles;
};

