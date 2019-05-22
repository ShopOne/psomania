#define MAIN
#include "DxLib.h"
#include<string>
#include "main_function.hpp"
#include"GloV.hpp"
#define FLAME 60
int fps_count, count0t;
int f[FLAME];
double ave;

enum Game_process {
	start_init, start_menu, select_menu,game_init, games, result_menu,reset, undefined,
};
bool loop_process() {
	bool process_move = true;
	if (ProcessMessage() != 0) process_move = false;
	if (ClearDrawScreen() != 0) process_move = false;
	getKey::get_key_frame();
	return process_move;
}

void global_value_reset() {
	music_count = 0;
	end_game_count = 0;
	flash_count = 0;
	score = 0;
	combo = 0;
	score = 0;
	judge = "";
}
void init_serial_connection() {
	port = CreateFile(_T("COM3"), GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, 0, NULL);
	if (port == INVALID_HANDLE_VALUE) {
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
	if (port == INVALID_HANDLE_VALUE) return;
	DCB dcb;
	GetCommState(port, &dcb);
	dcb.BaudRate = 38400; // speed
	dcb.ByteSize = 8; //date length
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;
	
	SetCommState(port, &dcb);
	
}
void global_value_init() {
	GetCurrentDirectory(MAX_PATH,this_dir);
	note_effect_handle = LoadSoundMem("./dat/Explosion2.wav");
	j_effect_handle = LoadSoundMem("./dat/Explosion.wav");
	global_value_reset();
	//init_serial_connection();
	int key_list[USE_KEY_MAX] = { KEY_INPUT_A,KEY_INPUT_S,KEY_INPUT_J,KEY_INPUT_K,KEY_INPUT_L };
	for (int i = 0; i < USE_KEY_MAX; i++) {
		use_key_id[i] = key_list[i];
		key[i] = 0;
		note_push_length[i] = 0;
	}
	
}
void fps_wait() {
	int term, i, gnt;
	static int t = 0;
	if (fps_count == 0) {
		if (t == 0)
			term = 0;
		else
			term = count0t + 1000 - GetNowCount();
	}
	else 
		term = (int)(count0t + fps_count * (1000.0 / FLAME)) - GetNowCount();

	if (term > 0)
		Sleep(term);

	gnt = GetNowCount();

	if (fps_count == 0)
		count0t = gnt;
	f[fps_count] = gnt - t;
	t = gnt;
	if (fps_count == FLAME - 1) {
		ave = 0;
		for (i = 0; i < FLAME; i++)
			ave += f[i];
		ave /= FLAME;
	}
	fps_count = (++fps_count) % FLAME;
}
void draw_fps(int x, int y) {
	if (ave != 0) {
		DrawFormatString(x, y,WHITE, "[%.1f]", 1000 / ave);
	}
	return;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	int game_process = start_init;
	global_value_init();
	while (loop_process()) {
		switch (game_process) {
		case start_init:
			sInit::start_init_main();
			game_process = start_menu;
			break;
		case start_menu:
			start::start_menu_main();
			if (key[KEY_ID_K] == 1) {
				game_process = select_menu;
			}
			break;
		case select_menu:
			selectMenu::select_menu_main();
			selectMenu::draw_select_menu_main();
			if (key[KEY_ID_L] == 1) {
				game_process = start_menu;
			}
			if (key[KEY_ID_K] == 1) {
				game_process = game_init;
			}
			break;
		case game_init:
			bool is_sucsess;
			is_sucsess = gameInit::game_init_main();
			game_process = (is_sucsess == true) ? games : select_menu;
			break;
		case games:
			gameMain::game_move_main();
			gameMain::draw_game_main();
			fps_wait();
			draw_fps(500,450);
			if (end_game_count >= 100) {
				game_process = result_menu;
				reset_move = 0;
			}
			break;
		case result_menu:
			result::result_main();
			if (reset_move == 1) {
				game_process = reset;
			}else if (reset_move == 2) {
				game_process = games;
			}
			break;
		case reset:
			global_value_reset();
			game_process = start_init;
			break;
		default:
			printfDx("format");
			break;
		}
		ScreenFlip();
	};
	DxLib_End();
	CloseHandle(port);
	return 0;
}

