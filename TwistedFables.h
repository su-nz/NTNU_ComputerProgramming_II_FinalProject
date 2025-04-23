#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h> 
#include <unistd.h> 
#include "vector.h"
#define Ult_threshold Ultt
#define Maxpower 25
#define DeckMax 200

typedef struct Character{
	int8_t Maxhp;
	int8_t Maxarmor;
	int8_t Ult_threshold;
	int8_t character_code; // 角色代碼
	int8_t token_code; // 偷肯代碼 0)為沒有
}character;

typedef struct Card{
	int8_t cost;
	int8_t level;
	int8_t range; //for attack 0 means its doesn't need range
	int8_t type; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
	int8_t power_generate;
	int8_t value; // for example value = 1 on attack => deal 1 damage
	int8_t damage;
	int8_t shield;
	int8_t require_basic_card; // 0 means do not requires
	int16_t cardcode; // for skill card 
	char * inf;
	char * cardname;
}card;

typedef struct Player{
	int8_t num; //1 2 3 4
	int8_t character; // 0 - 9
	char * charname;
	int8_t Maxhp;
	int8_t hp;
	int8_t Maxarmor;
	int8_t armor;
	int8_t Ult_threshold;
	int8_t power;
	int8_t hands;
	int8_t coordinate;
	int8_t first;
	
	int8_t poison ;
	
	int8_t matches;
	int8_t sleep;
	int8_t alice; //愛麗絲 狀態 -1代表不是愛麗絲
	int8_t qi; //花木蘭 氣 -1代表不是花木蘭
	int8_t combo; //桃樂絲 連擊 -1代表不是桃樂絲
	int8_t tentacle;
	int8_t Scheherazade_token;
	vector discard;
	vector deck;
	card hands_card[50];
	
}player;



typedef struct Deck{
	card C[256];
	int16_t size;
}deck;



void print_game_broad_9();
int8_t action_command(player *P);
int8_t inputcharacter(player *P, int8_t characternum);
int16_t Card_Define(int16_t CardID , card *C);
int8_t discard_back_to_deck(player *P);
int8_t draw_card(int8_t amount , player *P);
int8_t print_discard(player *P);
int8_t discard_command(player *P);


	
