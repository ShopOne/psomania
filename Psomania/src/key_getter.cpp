#include "DxLib.h"
#include "GloV.hpp"
namespace getKey {
	void key_printer() {
		for (int i = 0; i < USE_KEY_MAX; i++) {
			printfDx("%d ", key[i]);
		}
		printfDx("\n");
	}
	void get_serial(char tmpKey[]) {
		DWORD errors;
		COMSTAT com_stat;
		ClearCommError(port, &errors, &com_stat);
		int length_of_rec = com_stat.cbInQue,can_read;

		char recieved_data[200]; //文字列サイズを入れたかった人生だった
		DWORD num_of_put;
		can_read = ReadFile(port, recieved_data, length_of_rec, &num_of_put,NULL);
		if (can_read == FALSE) {
			return;
		}
		if (recieved_data[0]=='A') tmpKey[KEY_INPUT_A]++;
		if (recieved_data[0]=='S') tmpKey[KEY_INPUT_S]++;
		if (recieved_data[0]=='J') tmpKey[KEY_INPUT_J]++;
		if (recieved_data[0]=='K') tmpKey[KEY_INPUT_K]++;
		if (recieved_data[0]=='L') tmpKey[KEY_INPUT_L]++;
		/*
		int add_list[USE_KEY_MAX] = {};
		for (int i = 0; i < length_of_rec-5; i+=5) {
			for (int j = 0; j < 5; j++) {
				if (recieved_data[i + j] == '1') add_list[j] = 1;
				printfDx("%c ", recieved_data[i + j]);
			}
			printfDx("\n");
		}
		for (int i = 0; i < USE_KEY_MAX; i++) {
			tmpKey[use_key_id[i]] += add_list[i];
		}
		*/
		
	}
	void get_key_frame() {
		char tmpKey[256];
		int get_key_bool;
		get_key_bool = GetHitKeyStateAll(tmpKey);
		//get_serial(tmpKey);
		/*
		usekey is {a,s,j,k,l} 
		*/
		for (int i = 0; i < USE_KEY_MAX; i++) {
			if (tmpKey[use_key_id[i]] != 0) {
				key[i]++;
			}
			else {
				key[i] = 0;
			}
		}
	//key_printer();
	}
}