#include"song.h"
#include"playlist.h"
#include <stdio.h>

typedef char* string;

struct Playlist* Playlist_New(const char* name) {
	struct Playlist* playlist = (struct Playlist*)malloc(sizeof(struct Playlist));

	if (playlist) {

		int len = strlen(name) + 1;
		playlist->name = (string)malloc(len);
		if (playlist->name)
			strcpy_s(playlist->name, len, name);
		else
			printf("Couldn't allocate memory: for Playlist name");

		playlist->firstSong = NULL;
		playlist->lastSong = NULL;
		playlist->numberOfSongs = 0;
		playlist->totalDuration = 0;
	}
	else {
		printf("Couldn't allocate memory: for Playlist");
		playlist = NULL;
	}

	return playlist;
}


// is list empty
int isEmpty(const struct Playlist* playlist) {
	return playlist->firstSong == NULL;
}

// before
void Playlist_Add(struct Playlist* playlist, struct Song* song) {

	if (isEmpty(playlist)) {
		playlist->firstSong = song;
		playlist->lastSong = song;
	}
	else {
		song->nextSong = playlist->firstSong;
		playlist->firstSong = song;
	}

	playlist->numberOfSongs++;
	playlist->totalDuration += song->duration;
}


void Playlist_Add_After(struct Playlist* playlist, struct Song* song) {

	if (isEmpty(playlist)) {
		playlist->firstSong = song;
		playlist->lastSong = song;
	}
	else {
		playlist->lastSong->nextSong = song;
		playlist->lastSong = song;
	}


	playlist->numberOfSongs++;
	playlist->totalDuration += song->duration;
}


void Playlist_Delete_byName(struct Playlist* playlist, const char* name) {
	// function which takes a name of song, and delete it from playlist.

	if (isEmpty(playlist)) {
		printf("Playlist is empty");
	}
	else if (strcmp(playlist->firstSong->name, name) == 0) { // if equal
		struct Song* removedSong = playlist->firstSong;
		playlist->firstSong = playlist->firstSong->nextSong;

		playlist->totalDuration -= removedSong->duration;
		playlist->numberOfSongs--;

		free(removedSong);

		if (playlist->firstSong == NULL) playlist->lastSong = NULL;
	}
	else {

		struct Song* songPtr = playlist->firstSong;
		int find = 0;

		while (songPtr->nextSong != NULL) {

			if (strcmp(songPtr->nextSong->name, name) == 0) { // if equal

				if (songPtr->nextSong->nextSong == NULL) {
					playlist->totalDuration -= songPtr->nextSong->duration;
					free(songPtr->nextSong);
					songPtr->nextSong = NULL;
					playlist->lastSong = songPtr;
				}
				else {
					struct Song* removedSong = songPtr->nextSong;
					songPtr->nextSong = songPtr->nextSong->nextSong;
					playlist->totalDuration -= removedSong->duration;
					free(removedSong);
				}


				playlist->numberOfSongs--;
				find = 1;
				break;
			}
			else {
				songPtr = songPtr->nextSong;
			}
		}

		if (find == 0) {
			printf("Can not find");
		}

	}

}


void Playlist_Delete_byID(struct Playlist* playlist, const int id) {
	// function which takes an ID of song, and delete it from playlist.


	if (isEmpty(playlist)) {
		printf("Playlist is empty");
	}
	else if (playlist->firstSong->ID == id) {
		struct Song* removedSong = playlist->firstSong;
		playlist->firstSong = playlist->firstSong->nextSong;

		playlist->totalDuration -= removedSong->duration;
		playlist->numberOfSongs--;

		free(removedSong);

		if (playlist->firstSong == NULL) playlist->lastSong = NULL;
	}
	else {

		struct Song* songPtr = playlist->firstSong;
		int find = 0;

		while (songPtr->nextSong != NULL) {

			if (songPtr->nextSong->ID == id) {

				if (songPtr->nextSong->nextSong == NULL) {
					playlist->totalDuration -= songPtr->nextSong->duration;
					free(songPtr->nextSong);
					songPtr->nextSong = NULL;
					playlist->lastSong = songPtr;
				}
				else {
					struct Song* removedSong = songPtr->nextSong;
					songPtr->nextSong = songPtr->nextSong->nextSong;
					playlist->totalDuration -= removedSong->duration;
					free(removedSong);
				}


				playlist->numberOfSongs--;
				find = 1;
				break;
			}
			else {
				songPtr = songPtr->nextSong;
			}
		}

		if (find == 0) {
			printf("Can not find");
		}
	}
}


void Playlist_Find_byName(struct Playlist* playlist, const char* name) {
	// function which takes a name of song, and print its artist, duration, genreand ID_in_playlist.

	if (isEmpty(playlist)) {
		printf("Playlist is empty");
	}
	else {
		int find = 0;

		struct Song* songPtr = playlist->firstSong;
		while (songPtr != NULL) {

			if (strcmp(songPtr->name, name) == 0) { // if equal
				Song_Print(songPtr);
				find = 1;
				break;
			}

			songPtr = songPtr->nextSong;
		}

		if (find == 0) {
			printf("Can not find");
		}
	}
}


void Playlist_Find_byID(struct Playlist* playlist, const int id) {
	// function which takes an ID of song, and print its name, artist, duration and genre.

	if (isEmpty(playlist)) {
		printf("Playlist is empty");
	}
	else {
		int find = 0;

		struct Song* songPtr = playlist->firstSong;
		while (songPtr != NULL) {

			if (songPtr->ID == id) {
				Song_Print(songPtr);
				find = 1;
				break;
			}

			songPtr = songPtr->nextSong;
		}

		if (find == 0) {
			printf("Can not find");
		}
	}
}


void swap(struct Song* list) {
	int tempId;
	string tmpString;
	double tmpDuration;
	enum Genre tmpGenre;


	tempId = list->ID;
	list->ID = list->nextSong->ID;
	list->nextSong->ID = tempId;

	tmpString = list->name;
	list->name = list->nextSong->name;
	list->nextSong->name = tmpString;

	tmpString = list->artist;
	list->artist = list->nextSong->artist;
	list->nextSong->artist = tmpString;

	tmpDuration = list->duration;
	list->duration = list->nextSong->duration;
	list->nextSong->duration = tmpDuration;

	tmpGenre = list->genre;
	list->genre = list->nextSong->genre;
	list->nextSong->genre = tmpGenre;
}

void Playlist_Sort_byName(struct Playlist* playlist) {
	// function which sorts a playlist in the alphabetical order(by first letter only).

	// bubbleSort
	int swapped;
	struct Song* list;
	struct Song* lptr = NULL;


	if (playlist->firstSong == NULL) {
		printf("Playlist is empty");
		return;
	}
	do
	{
		swapped = 0;
		list = playlist->firstSong;

		while (list->nextSong != lptr)
		{
			if (list->name[0] > list->nextSong->name[0])
			{
				swap(list);

				swapped = 1;
			}
			list = list->nextSong;

		}
		lptr = list;
	} while (swapped);
}


void Playlist_Sort_byID(struct Playlist* playlist, const int Asc) {
	// function which sorts a playlist in the ascending or descending order.

	// bubbleSort
	int swapped;
	struct Song* list;
	struct Song* lptr = NULL;


	if (playlist->firstSong == NULL) {
		printf("Playlist is empty");
		return;
	}
	do
	{
		swapped = 0;
		list = playlist->firstSong;

		while (list->nextSong != lptr)
		{
			if (Asc) {
				if (list->ID > list->nextSong->ID)
				{
					swap(list);
					swapped = 1;
				}
				list = list->nextSong;
			}
			else {
				if (list->ID < list->nextSong->ID)
				{
					swap(list);
					swapped = 1;
				}
				list = list->nextSong;
			}


		}
		lptr = list;
	} while (swapped);
}


void Playlist_Print(const struct Playlist* playlist) {
	// function that prints the whole playlist.

	printf("++++++++++ Playlist +++++++++++\n");

	if (playlist->name == NULL)
		printf("\nPlaylist name:\t\t Empty\n");
	else
		printf("\nPlaylist name:\t\t %s\n", playlist->name);

	if (playlist->firstSong == NULL)
		printf("First song name:\t Empty\n");
	else
		printf("First song name:\t %s\n", playlist->firstSong->name);

	if (playlist->lastSong == NULL)
		printf("Last song name:\t\t Empty\n");
	else
		printf("Last song name:\t\t %s\n", playlist->lastSong->name);

	printf("Total Duration:\t\t %.2lf\n", playlist->totalDuration);
	printf("Number of songs:\t %i\n\n", playlist->numberOfSongs);


	struct Song* songPtr = playlist->firstSong;
	while (songPtr != NULL) {
		Song_Print(songPtr);
		songPtr = songPtr->nextSong;
	}

	printf("\n+++++++++++++++++++++++++++++++\n");
}


void Playlist_To_File(const struct Playlist* playlist) {
	// Exercise 3: Save the playlist in the file	//

	// function that take the playlist, and save its songs with
	//		corresponding ID, Name, Artist, Duration, Genre in the file.
}


void Playlist_Statistics(const struct Playlist* playlist) {
	printf("\n========== Genre Info ==========\n");

	int count_No = 0;
	int count_Rock = 0;
	int count_Pop = 0;
	int count_Jazz = 0;
	int count_Disco = 0;
	int count_HipHop = 0;


	struct Song* songPtr = playlist->firstSong;
	while (songPtr != NULL) {

		if (songPtr->genre == No) count_No++;
		else if (songPtr->genre == Rock) count_Rock++;
		else if (songPtr->genre == Pop) count_Pop++;
		else if (songPtr->genre == Jazz) count_Jazz++;
		else if (songPtr->genre == Disco) count_Disco++;
		else if (songPtr->genre == HipHop) count_HipHop++;
		songPtr = songPtr->nextSong;
	}


	printf("Genre:\t No\t     Count: %i\n", count_No);
	printf("Genre:\t Rock\t     Count: %i\n", count_Rock);
	printf("Genre:\t Pop\t     Count: %i\n", count_Pop);
	printf("Genre:\t Jazz\t     Count: %i\n", count_Jazz);
	printf("Genre:\t Disco\t     Count: %i\n", count_Disco);
	printf("Genre:\t HipHop\t     Count: %i\n", count_HipHop);


	printf("\n================================\n\n");
}