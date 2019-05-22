#include"GloV.hpp"
#include"Dxlib.h"
#include<Windows.h>
#include<tchar.h>
#include<fstream>
namespace gameInit {
	static bool funcFileOpen(HWND hWnd)
	{
		static OPENFILENAME     ofn;
		static TCHAR            szPath[MAX_PATH];
		static TCHAR            szFile[MAX_PATH];

		if (szPath[0] == TEXT('\0')) {
			GetCurrentDirectory(MAX_PATH, szPath);
		}
		if (ofn.lStructSize == 0) {
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hWnd;
			ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
			ofn.lpstrFile = szFile;       // 選択ファイル格納
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrFilter = TEXT("wavファイル(*.wav)\0*.wav");
			ofn.lpstrTitle = TEXT("音楽ファイルを選択します。");
			ofn.Flags = OFN_FILEMUSTEXIST;
		}
		if (GetOpenFileName(&ofn)) {
			sound_handle = LoadSoundMem(szFile);
			all_notes[KEY_ID_J].push_back(note(61, false));
			music_path = szFile;
			return true;
		}
		else {
			return false;
		}
	}
	bool music_create_init() {
		return funcFileOpen(0);
	}
	void load_init() {
		std::string file_path=this_dir;
		file_path += "/dat/"+ list_iterator->get_title() + ".wav";
		sound_handle = LoadSoundMem(file_path.c_str());
		file_path = this_dir;
		file_path += "/dat/musicID" + std::to_string(list_iterator->get_id()) + ".csv";
		std::ifstream ifs(file_path);
		std::string line0,line1;
		int note_line = 0;
		while (std::getline(ifs, line0)) {
			std::getline(ifs, line1);
			std::string counter="";
			int line1_index = 0;
			for (int i = 0; i < line0.size(); i++) {
				if (line0[i] != ',') {
					counter += line0[i];
				}
				else {
					bool tmp = (line1[line1_index] == '0') ? false : true;
					all_notes[note_line].push_back(note(std::stoi(counter), tmp));
					counter = "";
					line1_index+=2;
				}
			}
			bool tmp = (line1[line1_index] == '0') ? false : true;
			all_notes[note_line].push_back(note(std::stoi(counter), tmp));
			note_line++;
		}
	}
	void game_gv_init() {
		for (int i = 0; i < USE_KEY_MAX; i++) {
			judge_score[i] = 0;
		}
	}
	bool game_init_main() {
		bool is_sucsess = true;
		switch (list_iterator->get_id()) {
		case 0:
			is_sucsess = music_create_init();
			break;
		default:
			load_init();
			break;
		}
		return is_sucsess;
	}
}