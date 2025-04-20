#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h> 
#include <unistd.h> 
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

typedef struct Player{
	int8_t character; // 0 - 9
	char * charname;
	int8_t Maxhp;
	int8_t hp;
	int8_t Maxarmor;
	int8_t armor;
	int8_t Ult_threshold;
	int8_t power;
	int8_t hands;
	int8_t token;
	
}player;

typedef struct Card{
	int8_t cost;
	int8_t level;
	int8_t range; //for attack 0 means its doesn't need range
	int8_t type; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
	int8_t power_generate;
	int8_t value; // for example value = 1 on attack => deal 1 damage
	int8_t require_basic_card; // 0 means do not requires
	int16_t cardcode; // for skill card 
}card;

int16_t Map[11][3]={0};// Map[x][0]) 遺跡排的紀錄 Map[x][1]) 第一排和單人模式時使用的地圖 Map[x][2]) 第二排// 1v1 9格
card player1[DeckMax],player2[DeckMax],player3[DeckMax],player4[DeckMax]; 
card attack_shop[54],armor_shop[54],movement_shop[54],wild_shop[18]; 
player player_1,player_2,player_3,player_4;
int8_t mode=-1;
int8_t RelicOn = -1;
int8_t BotOn = -1;
int8_t player1_char = -1;
int8_t player2_char = -1;
int8_t player3_char = -1;
int8_t player4_char = -1;





	
