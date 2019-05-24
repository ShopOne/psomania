#ifndef GROV
#define GROV
#ifdef MAIN
#define GLOBAL 
#else
#define GLOBAL extern
#endif
#include<utility>
#include<list>
#include<vector>
#include<Windows.h>
#include"class.hpp"
#define USE_KEY_MAX 5
#define KEY_ID_A 0
#define KEY_ID_S 1
#define KEY_ID_J 2
#define KEY_ID_K 3
#define KEY_ID_L 4
#define FLASH_TIME 3
#define MUSIC_DESCRIPTION_NUM 2
#define KEY_FLAME_SAVE_MAX 1000
#define BLACK GetColor(0,0,0)
#define WHITE GetColor(255,255,255)
#define NOTE_FLOW_COUNT 60
#define BAR_START 40
#define BAR_END 560
#define BAUDRATE 38600
GLOBAL int reset_move;
GLOBAL int key[USE_KEY_MAX];
GLOBAL int music_count;
GLOBAL int note_push_length[USE_KEY_MAX];
GLOBAL int use_key_id[USE_KEY_MAX];
GLOBAL int end_game_count;
GLOBAL int note_effect_handle;
GLOBAL int j_effect_handle;
GLOBAL int score;
GLOBAL char this_dir[MAX_PATH];
GLOBAL int judge_score[USE_KEY_MAX];
GLOBAL int combo;
GLOBAL std::string judge;
GLOBAL std::string music_path;
GLOBAL std::vector<int> long_bar[USE_KEY_MAX];
GLOBAL std::list<music_description> music_list;
GLOBAL std::list<music_description>::iterator list_iterator;
GLOBAL std::vector<note> all_notes[USE_KEY_MAX];
GLOBAL std::vector<note> now_notes[USE_KEY_MAX];
GLOBAL std::vector<note> memory_notes[USE_KEY_MAX];
GLOBAL int flash_count;
GLOBAL int sound_handle;
GLOBAL HANDLE port;
#endif