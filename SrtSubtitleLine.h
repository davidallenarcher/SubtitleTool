#pragma once
#include <string>
#include <list>
using namespace std;

struct SrtTime
{
	int hour;
	int minute;
	int second;
	int milliSecond;
};

struct SrtSubtitleLine
{
	int index;
	SrtTime startTime;
	SrtTime endTime;
	list<string> lines;
};

