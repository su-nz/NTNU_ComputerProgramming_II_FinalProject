#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h> 
#include <unistd.h>
#include <termios.h>
#include "vector.h"
#define Ult_threshold Ultt
#define Maxpower 25
#define DeckMax 200
#define GREEN "\033[32m"
#define RED   "\033[31m"
#define BLUE  "\033[34m"
#define BOLD  "\033[1m"
#define RESET "\033[0m"

typedef struct Character{
	int8_t Maxhp;
	int8_t Maxarmor;
	int8_t Ult_threshold;
	int8_t character_code; // 角色代碼
	int8_t token_code; // 偷肯代碼 0)為沒有
}character;

typedef struct Card{
	int8_t clone ;
	int8_t remain;
	int8_t cost;
	int8_t level;
	int8_t range; //for attack 0 means its doesn't need range
	int8_t type; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
	int8_t power_generate;
	int8_t value; // for example value = 1 on attack => deal 1 damage
	int8_t damage;
	int8_t shield;
	int8_t require_basic_card; // 0)attack 1)defend 2)movement
	int16_t cardcode; // for skill card 
	char * inf;
	char * cardname;
}card;

typedef struct Redhoodult{
	int8_t action; // 0 
	int8_t range;
	int8_t atk;
	int8_t def;
	int8_t mov;
	int8_t spel_buy;
	int8_t bas_buy;
	int8_t cardid;
}RHU;

typedef struct Player{
	int8_t alive;     // 1: still in game, 0: defeated
	int8_t team;      // 0 or 1
	int8_t bot;
	int8_t end_turn;
	int8_t num; //0 1 2 3
	int8_t character; // 0 - 9
	char * charname;
	int8_t layer;
	int8_t Maxhp;
	int8_t hp;
	int8_t Maxarmor;
	int8_t armor;
	int8_t Ult_threshold;
	int8_t power;
	int8_t hands;
	int8_t coordinate;
	int8_t first;
	int8_t atk_buff;
	int8_t defend_buff;
	int8_t speed_buff;
	int8_t atk_bb1; //basic buff
	int8_t atk_bb2; //basic buff
	int8_t atk_bb3; //basic buff
	int8_t sleep_passive1_cd;
	int8_t sleep_passive2_cd;
	int8_t sleep_hp;
	int8_t poison ;
	
	int8_t matches;
	int8_t sleep_token;
	int8_t sleep_token_max;
	int8_t sleep;
	int8_t alice; //愛麗絲 狀態 -1代表不是愛麗絲
	int8_t qi; //花木蘭 氣 -1代表不是花木蘭
	int8_t combo; //桃樂絲 連擊 -1代表不是桃樂絲
	int8_t tentacle;
	int8_t Scheherazade_token;
	vector discard;
	vector deck;
	int16_t passive_n;
	int16_t passive[7];//蛻變牌 美人魚多一個
	int16_t starting_size;//持續牌數量
	int16_t playcard[256];//出牌區
	int16_t playcardnum;//出牌區數量
	int16_t starting[256];//持續牌
	int16_t clone[256];
	int16_t combo_basic[256];//搭配持續牌
	int16_t starting_lv[256];//搭配持續牌等級
	card hands_card[50];
	int16_t hands_select[50];//手牌選取
	int16_t Ult_deck[3];
	int16_t Redhoodsave[3];
	RHU RedUlt;
	
}player;







typedef struct Deck{
	card C[256];
	int16_t size;
}deck;
int8_t check_passive(player *P , int check_num);
int8_t printf_skill_shop(int8_t num);
int8_t deal_damage(player *P , int8_t damage);
int8_t check_starting(player *P,player *Enemy);
int8_t use_skill(player* you,player *P,int16_t card_id , int8_t *damage_output , int8_t *armor_output, int8_t lv ,int8_t combo_cardid, int8_t mode,int8_t BotOn);
int8_t use_Ult(player* you,player *P,int16_t card_id , int8_t *damage_output , int8_t *armor_output, int8_t mode ,vector (*skillBuyDeck)[3],vector (*basicBuyDeck)[3],int8_t BotOn);
int8_t startingskill(player* you ,player *P,int16_t card_id,int16_t lv );
int8_t clear_select(player *P);
void print_game_broad_9();
void print_game_broad_11();
int8_t action_command(player *P);
int8_t inputcharacter(player *P, int8_t characternum);
int16_t Card_Define(int16_t CardID , card *C);
int8_t discard_back_to_deck(player *P);
int8_t draw_card(int8_t amount , player *P);
int8_t print_discard(player *P);
int8_t discard_command(player *P);
void print_header();
int8_t get_random_unused_character(int8_t remaining_roles[], int8_t remaining_count);
void enable_raw_mode();
void disable_raw_mode();
void wait_for_space();
int8_t str_display_width(const char *s);
void print_aligned_charname(const char* name, int8_t width);
void shuffle(vector *v);
int8_t range_counter(player *P,player*P2 , int8_t range);
int8_t print_hands(player *P);
int8_t initialization_starting(player *P);
int8_t initialization_deck(player *P);
int8_t discard_card_from_hand(player *P,int8_t index);
void quicksort(int16_t *arr, int low, int high);
int8_t gain_sleeptoken(player *P , int8_t amount);
int8_t regenerate_hp(player *P,int8_t amount);
int8_t remove_sleeptoken(player *P , int8_t amount);
int8_t recv_card_sleep(player *P , int8_t dama);
int8_t handaddplaycardnum(player *P, int16_t select);
int8_t remove_card_from_hand(player *P , int8_t select);
int8_t playcardnum_clear(player *P);
int8_t botChoice(int16_t mode , int16_t min , int16_t  max  , int16_t situation);
int8_t Redhoodsavefile(player *P,int BotOn);
int8_t clearRHU(player *P);
int8_t writeinRHU(player *P,int8_t a1,int8_t a2,int8_t a3,int8_t a4,int8_t a5,int8_t a6,int8_t a7,int8_t a8);
int8_t check_location(int8_t coor);
int8_t swap_place(player *P1 ,player *P2);

