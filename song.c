#include"song.h"
#include <stdio.h>

int Id = 0;

struct Song* Song_New(const char* name,
	const char* artist, const double duration, const enum Genre genre)
{
	struct Song* song = (struct Song*)malloc(sizeof(struct Song));

	if (song) {

		song->ID = ++Id;

		int len;

		len = strlen(name) + 1;
		song->name = (string)malloc(len);
		if (song->name)
			strcpy_s(song->name, len, name);
		else
			printf("Couldn't allocate memory: for Song->name");


		len = strlen(artist) + 1;
		song->artist = (string)malloc(len);
		if (song->artist)
			strcpy_s(song->artist, len, artist);
		else
			printf("Couldn't allocate memory: for Song->artist");


		song->duration = duration;
		song->genre = genre;
		song->nextSong = NULL;

	}
	else {
		printf("Couldn't allocate memory: for Song");
		song = NULL;
	}

	return song;
}

void Song_Print(struct Song* song) {

	printf("\n---------- Song Info ----------\n");

	printf("Id:\t\t %i\n", song->ID);
	printf("Name:\t\t %s\n", song->name);
	printf("Artist:\t\t %s\n", song->artist);
	printf("Duration:\t %.2lf\n", song->duration);


	switch (song->genre)
	{
	case No:
		printf("Genre:\t\t No");
		break;
	case Rock:
		printf("Genre:\t\t Rock");
		break;
	case Pop:
		printf("Genre:\t\t Pop");
		break;
	case Jazz:
		printf("Genre:\t\t Jazz");
		break;
	case Disco:
		printf("Genre:\t\t Disco");
		break;
	case HipHop:
		printf("Genre:\t\t HipHop");
		break;
	}


	printf("\n-------------------------------\n\n");
}
