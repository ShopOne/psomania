#include "GloV.hpp"
#include "Dxlib.h"
#include<fstream>
#include<string>
namespace sInit {
	void print_string(std::string s) {
		printfDx("string out");
		for (auto i = 0; i < s.size(); i++) {
			printfDx("%c", s[i]);
		}
		printfDx("\n");
	}

	music_description split(std::string line) {
		std::string descript_text[MUSIC_DESCRIPTION_NUM];
		int cnt = 0;
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ',') {
				cnt++;
				continue;
			}
			if (line[i] == '\n') {
				break;
			}
			descript_text[cnt].push_back(line[i]);
		}
		return music_description(descript_text[0], std::stoi(descript_text[1]));
	}
	void load_music_csv_file() {
		std::string file_path = this_dir;
		file_path += "/dat/music_list.csv";
		std::ifstream ifs(file_path);
		std::string line;
		bool first_line = true;
		while (std::getline(ifs, line)) {
			if (first_line) {
				first_line = false;
				continue;
			}
			music_list.push_back(split(line));
		}
		list_iterator = music_list.begin();
	}
	void print_list() {
		for (auto i = music_list.begin(); i != music_list.end(); i++) {
			for (int j = 0; j < i->get_title().size(); j++) {
				printfDx("%c", i->get_title()[j]);
			}
			printfDx(" ");
			printfDx("%d\n", i->get_id());
		}
	}
	void start_init_main() {
		load_music_csv_file();
	//	print_list();
	}
}