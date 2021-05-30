#pragma once

typedef char* string;

struct Playlist {
	string name;
	struct Song* firstSong; // head
	struct Song* lastSong;  // tail
	int numberOfSongs;
	double totalDuration;
};


struct Playlist* Playlist_New(const char* name);

void Playlist_Add(struct Playlist* playlist, struct Song* song);

void Playlist_Add_After(struct Playlist* playlist, struct Song* song);

void Playlist_Delete_byName(struct Playlist* playlist, const char* name);

void Playlist_Delete_byID(struct Playlist* playlist, const int id);

void Playlist_Find_byName(struct Playlist* playlist, const char* name);

void Playlist_Find_byID(struct Playlist* playlist, const int id);

void Playlist_Sort_byName(struct Playlist* playlist);

void Playlist_Sort_byID(struct Playlist* playlist, const int Asc);

void Playlist_Print(const struct Playlist* playlist);

void Playlist_To_File(const struct Playlist* playlist);

void Playlist_Statistics(const struct Playlist* playlist);