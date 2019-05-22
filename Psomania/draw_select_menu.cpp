#include"GloV.hpp"
#include"Dxlib.h"
namespace selectMenu {
	void draw_music_list() {
		int x = 280, y = 200;
		auto save_now_i = list_iterator;
		if (list_iterator == music_list.begin()) {
			list_iterator = music_list.end();
		}
		list_iterator--;
		if (list_iterator == music_list.begin()) {
			list_iterator = music_list.end();
		}
		list_iterator--;
		for (int i = -2; i <= 2; i++) {
			DrawFormatString(x + i * 120, y, WHITE, "%s", list_iterator->get_title().c_str());
			list_iterator++;
			if (list_iterator == music_list.end()) {
				list_iterator = music_list.begin();
			}
		}
		list_iterator = save_now_i;
	}
	void draw_select_menu_main() {
		draw_music_list();
	}
}