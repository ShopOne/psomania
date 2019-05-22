#include"Glov.hpp"
#include"Dxlib.h"
#include<fstream>
#include<iostream>
namespace gameInit {
	void load_init();
}
namespace result {
	bool name_entered=false;
	bool inputed_k = false;
	int key_point = 0;
	std::string music_name;
	void reset_gv() {
		end_game_count = 0;
		music_count = 0;
		reset_move = 2;
		score = 0;
		judge = "";
		music_name = "";
		name_entered = false;
		inputed_k = false;
		key_point = 0;
	}
	void cpy_memo_notes() {
		for (int i = 0; i < USE_KEY_MAX; i++) {
			all_notes[i] = std::move(memory_notes[i]);
			now_notes[i].clear();
			memory_notes[i].clear();
		}
		all_notes[KEY_ID_J].push_back(note(61, false));
	}
	void save_or_continue() {
		if (key[KEY_ID_K] == 1&&inputed_k==false) {
			inputed_k = true;
			return;
		}
		if (inputed_k==true) {
			int flag = 0;
			inputed_k = true;
			bool b;
			int create_id = (--music_list.end())->get_id() + 1;
			std::string now_path="/dat/";
			DrawString(0, 50, "曲名を入力してください", WHITE);
			DrawFormatString(0, 70, WHITE,"%s", music_name.c_str());
			if (name_entered == false) {
				if ((key[KEY_ID_S]>=30&&key[KEY_ID_S] % 10 == 0)||key[KEY_ID_S]==1) {
					key_point = (key_point + 1) % 27; //アルファベットとエンター
				}
				if ((key[KEY_ID_A]>=30&&key[KEY_ID_A] % 10 == 0||key[KEY_ID_A]==1)) {
					key_point = (key_point + 26) % 27;
				}
				if (key[KEY_ID_K] == 1) {
					if (key_point == 26) {
						name_entered = true;
					}
					else {
						char c = 'a' + key_point;
						music_name.push_back(c);
					}
				}
				if (key[KEY_ID_L]==1) {
					if (music_name.size() != 0) {
						music_name.erase(music_name.end() - 1);
					}
				}
				for (int i = 0; i < 27; i++) {
					int x = i * 15;
					int y = 200;
					if (i == key_point) {
						y -= 30;
					}
					if (i != 26) DrawFormatString(x, y, WHITE, "%c", 'a' + i);
					else DrawFormatString(x + 10, y, WHITE, "Enter");
				}
				if (name_entered != true) {
					return;
				}
			}
			now_path += music_name;
			now_path += ".wav";
			TCHAR now[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, now);
			now_path = this_dir + now_path;
			b = CopyFile(music_path.c_str(),now_path.c_str(), FALSE);
			if (!b) {
				LPVOID lpMsgBuf;
				FormatMessage(				//エラー表示文字列作成
					FORMAT_MESSAGE_ALLOCATE_BUFFER |
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR)& lpMsgBuf, 0, NULL);

				MessageBox(NULL, (const char*)lpMsgBuf, NULL, MB_OK);	//メッセージ表示
			}
			std::string notes_path = this_dir;
			notes_path += "/dat/musicID" + std::to_string(create_id) + ".csv";
			std::ofstream outputfile(notes_path);
			for (int i = 0; i < USE_KEY_MAX; i++) {
				std::string note_time="";
				std::string long_note="";
				memory_notes[i].push_back(note(-60, 0));  //データが一つもなかった場合バグる
				for (auto j = memory_notes[i].begin(); j != memory_notes[i].end(); j++) {
					note_time += std::to_string(j->get_note());
					long_note += (j->is_long() == true) ? "1" : "0";
					if (j != memory_notes[i].end() - 1) {
						note_time += ',';
						long_note += ',';
					}
				}
				note_time += '\n';
				long_note += '\n';
				outputfile << note_time;
				outputfile << long_note;
			}
			outputfile.close();
			std::string list_path = this_dir;
			list_path += "/dat/music_list.csv";
			std::fstream fs;
			fs.open(list_path, std::ios::app);
			fs << music_name << "," << std::to_string(create_id) << std::endl;
			fs.close();
			for (int i = 0; i < USE_KEY_MAX; i++) {
				memory_notes[i].clear();
				now_notes[i].clear();
				all_notes[i].clear();
			}
			reset_move = 1;
		}
		if (key[KEY_ID_L] == 1) {
			cpy_memo_notes();
			reset_gv();
			return;
		}
		if (key[KEY_ID_A] == 1) {
			reset_move = 1;
			for (int i = 0; i < USE_KEY_MAX; i++) {
				all_notes[i].clear();
				memory_notes[i].clear();
				now_notes[i].clear();
			}
		}
	}
	void draw_save_result() {
		DrawString(0, 0, "今のデータをセーブする:K やりなおす:L タイトルへ:A",WHITE);
	}
	void draw_continue_or_reset() {
		DrawString(0, 0, "タイトルへ:K やりなおす:L", WHITE);
	}
	void wait_move() {
		if (key[KEY_ID_K] == 1) {
			for (int i = 0; i < USE_KEY_MAX; i++) {
				memory_notes[i].clear();
				now_notes[i].clear();
				all_notes[i].clear();
				long_bar[i].clear();
			}
			reset_move = 1;
		}
		else if(key[KEY_ID_L]==1){
			reset_gv();
			reset_move = 2;
		}
	}
	void result_main() {
		switch (list_iterator->get_id()) {
		case 0:
			draw_save_result();
			save_or_continue();
			break;
		default:
			draw_continue_or_reset();
			wait_move();
		}
	}
}