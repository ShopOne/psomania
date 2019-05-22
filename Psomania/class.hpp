#ifndef CLASSES
#define CLASSES
#include<string>
#include<vector>
class music_description {
	std::string title;
	int id;
	public:
	music_description(std::string s, int i) {
		title = s;
		id = i;
	}
	std::string get_title() { return title; }
	int get_id() { return id; }
};
class note {
	int note_time;
	int counter;
	bool long_note; //Ç‡ÇµêLÇŒÇ∑Ç‚Ç¬Ç»ÇÁÇ±Ç±ÇÕtrue
public:
	note(int time, bool long_n) {
		note_time = time;
		long_note = long_n;
		counter = 0;
	}
	int get_note() { return note_time; }
	bool is_long() { return long_note; }
	int get_count() { return counter; }
	void add_count() { counter++; }
};
#endif