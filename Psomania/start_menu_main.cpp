#include"GloV.hpp"
#include"DxLib.h"
namespace start {
	bool check_key_input() {
		bool is_input = false;
		for (int i = 0; i < USE_KEY_MAX; i++) {
			if (key[i]!=0) {
				is_input = true;
			}
		}
		return is_input;
	}
	void draw_start_menu() {
		 DrawString(0, 0, "PsOmania", WHITE);
	}
	bool start_menu_main() {

		bool go_next = check_key_input();
		draw_start_menu();
		return go_next;
		
	}
}