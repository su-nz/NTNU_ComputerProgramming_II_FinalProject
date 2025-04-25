#include "TwistedFables.h"

#define waken_token_MAX 9
#define qi_token_MAX 12
#define tentacle_token_MAX 4
#define combo_token_MAX 12
#define Scheherazade_token_MAX 6
#define matches_MAX 12
#define poison_MAX 18

void shuffle(vector *v) {
    if (!v || v->SIZE <= 1) return;
	int times = rand() % (10+ 1);
	for(int k = 0 ; k < times ; k++){
		for (uint32_t i = v->SIZE - 1; i > 0; --i) {
		    uint32_t j = rand() % (i + 1);
		    int32_t temp = v->array[i];
		    v->array[i] = v->array[j];
		    v->array[j] = temp;
		}
	}
}

int8_t inputcharacter(player *P, int8_t characternum) { //寫入角色資訊
    (*P).character = characternum;
    (*P).atk_buff = 0;
    (*P).defend_buff = 0;
    (*P).speed_buff = 0;
	(*P).poison= -1;
	(*P).matches= -1;
	(*P).sleep = -1;
	(*P).alice=-1; //愛麗絲 狀態 -1代表不是愛麗絲
	(*P).qi=-1; //花木蘭 氣 -1代表不是花木蘭
	(*P).combo=-1; //桃樂絲 連擊 -1代表不是桃樂絲
	(*P).tentacle= -1;
	(*P).Scheherazade_token=-1;
    switch (characternum) {
        case 0: // 小紅帽
            (*P).charname = "小紅帽";
            (*P).Maxhp = 30;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 15;
            break;

        case 1: // 白雪公主
            (*P).charname = "白雪公主";
            (*P).Maxhp = 34;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 17;
            (*P).poison = 12 ;
            break;

        case 2: // 睡美人
            (*P).charname = "睡美人";
            (*P).Maxhp = 42;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 21;
            (*P).sleep = 1;
            break;

        case 3: // 愛麗絲
            (*P).charname = "愛麗絲";
            (*P).Maxhp = 32;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 16;
            (*P).alice=0;
            break;

        case 4: // 花木蘭
            (*P).charname = "花木蘭";
            (*P).Maxhp = 34;
            (*P).Maxarmor = 3;
            (*P).Ult_threshold = 17;
            (*P).qi= 0;
            break;

        case 5: // 輝夜姬
            (*P).charname = "輝夜姬";
            (*P).Maxhp = 32;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 16;
            break;

        case 6: // 美人魚
            (*P).charname = "美人魚";
            (*P).Maxhp = 36;
            (*P).Maxarmor = 3;
            (*P).Ult_threshold = 18;
            (*P).tentacle = 2;
            break;

        case 7: // 火柴女孩
            (*P).charname = "火柴女孩";
            (*P).Maxhp = 36;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 18;
            (*P).matches= 12;
            break;

        case 8: // 桃樂絲
            (*P).charname = "桃樂絲";
            (*P).Maxhp = 40;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 20;
            (*P).combo= 1;
            break;

        case 9: // 山魯佐德
            (*P).charname = "山魯佐德";
            (*P).Maxhp = 36;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 18;
            (*P).Scheherazade_token = 3;
            break;

        default:
            return -1; // 無效的角色編號
    }
	
    // 共通初始化
    (*P).hp = (*P).Maxhp;
    (*P).armor = 0;
    (*P).power = 0;
    (*P).hands = 0;
  	

    return 0; // 成功
}

int8_t discard_back_to_deck(player *P){
	while(P->discard.SIZE !=0){
		pushbackVector(&P->deck, BottomVector(&P->discard));
		popbackVector(&P->discard);
	}
	shuffle(&P->deck);
	return 0;
}

int8_t draw_card(int8_t amount , player *P){
	for(int i = 0 ; i < amount ; i++){
		if(P->deck.SIZE !=0){
			Card_Define(P->deck.array[P->deck.SIZE-1] , &P->hands_card[P->hands]);
			popbackVector(&P->deck); //remove card
			P->hands++;
		}else{
			discard_back_to_deck(P);
			if(P->deck.SIZE == 0){
				break;
			}
			Card_Define(P->deck.array[P->deck.SIZE-1] , &P->hands_card[P->hands]);
			popbackVector(&P->deck); //remove card
			P->hands++;
		}
	}
	return 0;
}

int8_t print_discard(player *P){
	system("clear");
	printf("%s的棄牌堆：\n",P->charname);
	for(int i = 0 ; i < P->discard.SIZE ; i++){
		card temp_card;
		Card_Define(P->discard.array[i] , &temp_card);
		printf("%d.)%s ",i+1,temp_card.cardname);
	}
}

int8_t range_counter(player *P1,player *P2,int8_t range){
	if(abs(P1->coordinate - P2->coordinate) <= range){
		return 1;//in range
	}else{
		return 0;//out of range
	}
}

