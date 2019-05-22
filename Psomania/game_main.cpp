#include"GloV.hpp"
#include"Dxlib.h"
namespace gameMain {
	void create_notes() {
		for (int i = 0; i < USE_KEY_MAX; i++) {
			if (key[i] >= 1&&music_count>=60) {
				note_push_length[i]++;
				if (note_push_length[i] == 1) {
					flash_count = 1;
				}
			}
			else if(note_push_length[i]!=0){
				if (note_push_length[i]<= 30||i==KEY_ID_J) {
					memory_notes[i].push_back(note(music_count - note_push_length[i], false));
				}
				else {
					memory_notes[i].push_back(note(music_count - note_push_length[i],true));
					memory_notes[i].push_back(note(music_count,true));
				}
				note_push_length[i] = 0;
			}
		}
	}
	void flow_notes(){
		for (int i = 0; i < USE_KEY_MAX; i++) {
			for (auto j = all_notes[i].begin(); j != all_notes[i].end(); j++) {
				if (music_count == j->get_note()- NOTE_FLOW_COUNT) {
					if (j->is_long()) {
					long_bar[i].push_back(0);
					}
					else {
					now_notes[i].push_back(*j);
					}
				}
			}
		}
	}
	void count_notes() {
		for (int i = 0; i < USE_KEY_MAX; i++) {
			for (auto j = now_notes[i].begin(); j != now_notes[i].end(); j++) {
				j->add_count();
				if (j->get_count() > 100) {
					j = now_notes[i].erase(j);
					if (j != now_notes[i].begin()) {
						j--;
					}
					else if(j== now_notes[i].end()){
						break;
					}
				}
			}
		}
	}
	void sound_count_music() {
		music_count++;
		if (music_count == 60) {
			PlaySoundMem(sound_handle, DX_PLAYTYPE_BACK);
		}
		if (CheckSoundMem(sound_handle) == 0&&music_count>60) {
			end_game_count++;
		}
	}
	void increment_flash() {
		if (flash_count > FLASH_TIME) {
			flash_count = 0;
		}
		if (flash_count != 0 && flash_count <= FLASH_TIME) {
			flash_count++;
		}
	}
	void sound_effect() {
		for (int i = 0; i < USE_KEY_MAX; i++) {
			if (key[i] == 1) {
				if (i == KEY_ID_J) {
					PlaySoundMem(j_effect_handle, DX_PLAYTYPE_BACK);
				}
				else {
					PlaySoundMem(note_effect_handle, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
	void erase_long_bar() {
		for (int i = 0; i < USE_KEY_MAX; i++) {
			if (i == KEY_ID_J) continue;
			for (auto j = long_bar[i].begin(); j != long_bar[i].end(); j++) {
				*j += 1;
				if (j != long_bar[i].end()-1) {
					if ((*j + 1) >= 400) {
						j = long_bar[i].erase(j, j + 2);
						if (j != long_bar[i].begin()) {
							j--;
						}
						else if (j == long_bar[i].end()) {
							break;
						}
					}
				}
			}
		}
	}
	void judge_long() {
		if (list_iterator->get_id() == 0)return;
		int c1, c2;
		bool end_f;
		static int long_cnt=0;
		for (int i = 0; i < USE_KEY_MAX; i++) {
			if (i == KEY_ID_J) continue;
			end_f = false;
			for (auto j = long_bar[i].begin(); j != long_bar[i].end(); j+=2) {
				c1 = *j;
				if (j + 1 == long_bar[i].end()) {
					c2 = 0;
					end_f = true;
				}
				else {
					c2 = *(j + 1);
				}
				if (key[i] >= 1 && c1 >= 60 && c2 <= 60) {
					long_cnt++;
				}
				if (long_cnt == 10) {
					combo++;
					score++;
					judge = "Perfect";
					long_cnt = 0;
				}
				if (end_f) break;
			}
		}
	}
	void judge_notes() {
		if (list_iterator->get_id() == 0)return;
		int cnt, num;
		bool is_checked;
		if (list_iterator->get_id() == 0) return;
		for (int i = 0; i < USE_KEY_MAX; i++) {
			for (auto j = now_notes[i].begin(); j != now_notes[i].end();) {
				if (j->get_count() >= 65) {
					j = now_notes[i].erase(j);
					judge = "Miss";
					combo = 0;
				}
				else j++;
			}
			if (key[i] == 1) {
				if (now_notes[i].empty())continue;
				auto j = now_notes[i].begin();
				cnt = j->get_count();
				is_checked = true;
				num = std::abs(cnt - 60);
				if (num <= 3) {
					judge = "Perfect";
					score += (combo / 10 +1) * 100;
					combo++;
				}
				else if (num <= 10) {
					judge = "Great";
					score += (combo / 10+1) * 80;
					combo++;
				}
				else if (num <= 15) {
					judge = "Good";
					score += (combo / 10+1) * 30;
					combo++;
				}
				else if (num <= 20) {
					judge = "Miss";
					combo = 0;
				}
				else {
					is_checked = false;
				}
				if (is_checked) {
					now_notes[i].erase(j);
				}
				break;
			}
		}
	}
	void game_move_main() {
		switch (list_iterator->get_id()) {
		case 0:
			increment_flash();
			create_notes();
		default:
			sound_effect();
			flow_notes();
			sound_count_music();
			count_notes();
			erase_long_bar();
			judge_notes();
			judge_long();
		}
	}
}