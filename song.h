#pragma once
#include"genre.h"

typedef char* string;

struct Song {
	int ID;
	string name;
	string artist;
	double duration;
	enum Genre genre;
	struct Song* nextSong;
};


struct Song* Song_New(const char* name, const char* artist, const double duration, const enum Genre genre);
void Song_Print(struct Song* song);