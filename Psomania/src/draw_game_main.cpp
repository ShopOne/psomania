#include"GloV.hpp"
#include"Dxlib.h"
namespace gameMain {
	int line0(int y) { return ((y-50)*(-120-290))/(670-50) + 290; }
	int line1(int y) { return ((y-50)*(100-300))/(670-50) + 300; }
	int line2(int y) { return ((y-50)*(320-310))/(670-50) + 310; }
	int line3(int y) { return ((y-50)*(540-320))/(670-50) + 320; }
	int line4(int y) { return ((y-50)*(760-330))/(670-50) + 330; }
	int dummy(int y) { return 0; }
	int (*funcs[])(int)= { line0, line1,line2,line2, line3, line4 };
	void draw_note() {
		int x, y;
		for (int i = 0; i < USE_KEY_MAX; i++) {
			for (auto j = now_notes[i].begin(); j != now_notes[i].end(); j++) {
				if (j->is_long())continue;
				y = 50 + (j->get_count()*350)/60;
				if (i != KEY_ID_J) {
					DrawLineAA(funcs[i](y), y, funcs[i+1](y),y, WHITE);
				}
				else {
					DrawLineAA(funcs[0](y), y, funcs[5](y),y, GetColor(255, 255, 0));
				}
				
			}
		}
	}
	void draw_bar() {
		int  y1, y2;
		y1 = 50;
		y2 = 670;
		DrawLine(0, 400, 670, 400, GetColor(255, 0, 0));
		for (int i = 0; i < 5; i++) {
			DrawLineAA(290 + i * 10, y1, i * 220-120 , y2, WHITE);
		}
	}
	void draw_flash() {
		bool is_inputed = false;
		for (int i = 0; i < USE_KEY_MAX; i++) {
			if (key[i] == 1) {
				is_inputed = true;
				break;
			}
		}
		if (is_inputed == false) return;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		DrawBoxAA(0.0, 0.0, 700.0, 600.0, WHITE,true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	void draw_long_bar() {
		int  y, ty;
		bool end = false;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		for (int i = 0; i < USE_KEY_MAX; i++) {
			if (i == KEY_ID_J) continue;
			end = false;
			for (auto j = long_bar[i].begin(); j != long_bar[i].end(); j+=2) {
				y = 50 + (*j*350)/60;
				if ((j + 1) == long_bar[i].end()) {
					ty =50;
					end = true;
				}
				else {
				ty = 50 + (*(j+1)*350)/60;
				}
				for (int k = ty; k <= y; k++) {
					DrawLineAA(funcs[i](k), k, funcs[i + 1](k), k, GetColor(0, 255, 0));
				}
				DrawBoxAA(funcs[i](y), y,funcs[i+1](ty) ,ty, GetColor(0, 255,0), true);
				if (end) break;
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	void draw_judge() {
		DrawFormatString(0, 0, WHITE, "score:%d\ncombo:%d\n%s\n",score,combo, judge.c_str());
	}
	void draw_game_main() {
		draw_flash();
		draw_note();
		draw_bar();
		draw_long_bar();
		draw_judge();
	}
}