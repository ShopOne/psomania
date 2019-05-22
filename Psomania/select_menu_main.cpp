#include<list>
#include<string>
#include"GloV.hpp"
#include"DxLib.h"
namespace selectMenu {
		void move_menu() {
		if (key[KEY_ID_S] == 1) {
			list_iterator++;
			if (list_iterator == music_list.end()) {
				list_iterator = music_list.begin();
			}
		}
		if (key[KEY_ID_A] == 1) {
			if (list_iterator == music_list.begin()) {
				list_iterator = music_list.end();
			}
			list_iterator--;
		}
	}
	void select_menu_main() {
		move_menu();
	}
}