#include <stdlib.h>
#include <string.h>
#include "genre.h"
#include "song.h"
#include "song.c"
#include "playlist.h"
#include "playlist.c"




int main()
{
	struct Playlist* playlistSport = Playlist_New("Sport");

	struct Song* song1 = Song_New("New Rules", "Dua Lipa", 3.45, Pop);
	struct Song* song2 = Song_New("Lose Yourself", "Eminem", 5.23, HipHop);
	struct Song* song3 = Song_New("Mata Hari", "Efendi", 3.13, Disco);
	struct Song* song4 = Song_New("Lovely", "Billie Eilish", 3.21, Pop);

	Playlist_Add_After(playlistSport, song1);
	Playlist_Add_After(playlistSport, song3);
	Playlist_Add_After(playlistSport, song2);
	Playlist_Add_After(playlistSport, song4);
	// Playlist_Add(playlistSport, song4); // Add before


	//Playlist_Print(playlistSport);

	// Playlist_Delete_byName(playlistSport, "Lose Yourself");
	// Playlist_Delete_byID(playlistSport, 2);

	// Playlist_Find_byName(playlistSport, "Lose Yourself");
	// Playlist_Find_byID(playlistSport, 1);

	// Playlist_Sort_byName(playlistSport);
	// Playlist_Sort_byID(playlistSport, 0);

	// Playlist_Statistics(playlistSport);

	//Playlist_Print(playlistSport);






	// User section

	char playlistNname[30];
	char songName[30];
	char artistName[30];
	double duration;
	enum Genre genre = No;

	printf("Enter playlist name: ");
	gets(playlistNname);
	struct Playlist* playlistRelax = Playlist_New(playlistNname);

	printf("Enter song name: ");
	gets(songName);

	printf("Enter artist name: ");
	gets(artistName);

	printf("Enter duration: ");
	scanf("%lf", &duration);


	printf("0: No\n1: Rock\n2: Pop\n3: Jazz\n4: Disco\n5: HipHop\n");
	printf("Enter genre: ");
	scanf("%i", &genre);



	struct Song* song5 = Song_New(songName, artistName, duration, genre);
	Playlist_Add_After(playlistRelax, song5);

	Playlist_Print(playlistRelax);




	free(playlistSport);
	free(playlistRelax);
	free(song1);
	free(song2);
	free(song3);
	free(song4);
}