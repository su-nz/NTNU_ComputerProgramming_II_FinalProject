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

int8_t playcardnum_clear(player *P){
	for(int i = 0 ; i < P->playcardnum ; i++){
		pushbackVector(&P->discard,P->playcard[i]);
		P->playcard[i] = 0;
	}
	P->playcardnum = 0;
	return 0;
}

int8_t handaddplaycardnum(player *P, int16_t select){
	
	P->playcard[P->playcardnum] = P->hands_card[select].cardcode;
	P->playcardnum++;
	remove_card_from_hand(P ,select+1);
	return 0;
}

int8_t remove_card_from_hand(player *P , int8_t select){
	Card_Define(0 , &(*P).hands_card[select-1]);
	for (int8_t i = select-1; i < (*P).hands - 1; i++) {
		Card_Define(0, &(*P).hands_card[i]);
		Card_Define((*P).hands_card[i + 1].cardcode , &(*P).hands_card[i]);
	}
	(*P).hands--;
	return 0;
}



int8_t inputcharacter(player *P, int8_t characternum) { //寫入角色資訊
	(*P).character = characternum; 
	(*P).passive_n = 0;
	(*P).atk_buff = 0;
	(*P).defend_buff = 0;
	(*P).speed_buff = 0;
    	(*P).sleep_token_max =-1;
    	(*P).sleep_token = -1;
	(*P).poison= -1;
	(*P).matches= -1;
	(*P).sleep = -1;
	(*P).playcardnum=0;
	P->atk_bb1=0;
	P->atk_bb2=0;
	P->atk_bb3=0;
	P->sleep_hp=-1;
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
            (*P).sleep_token = 0;
            (*P).sleep_token_max = 6;
            P->sleep_hp=-2;
            (*P).sleep_passive1_cd = 0;
            (*P).sleep_passive2_cd = 0;
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
    (*P).power = 50;
    (*P).hands = 0;
  	

    return 0; // 成功
}


int8_t recv_card_sleep(player *P , int8_t dama){
	if(dama<2) return 0;
	while(1){
		system("clear");
		print_discard(P);
		printf("你可以從棄牌堆拿：\n");
		if(dama >=2){
			printf("Lv1的攻擊牌\n");
		}
		if(dama >=4){
			printf("Lv2的攻擊牌\n");
		}
		if(dama >=6){
			printf("Lv3的攻擊牌\n");
		}
		int8_t cc=-1;
		printf("請問你要拿哪一牌？\n");
		printf("輸入數字：");//TODO: wrong input
		scanf("%hhd",&cc);
		if(cc > P->discard.SIZE || cc < 0){
			printf("沒有這張卡！\n");
			break;
		}else if(P->discard.array[cc] == 1 && dama >=2){
			eraseVector(&P->discard, cc);
			Card_Define(1 , &P->hands_card[P->hands]);
			P->hands++;
			break;
		}else if(P->discard.array[cc] == 2 && dama >=4){
			eraseVector(&P->discard, cc);
			Card_Define(2 , &P->hands_card[P->hands]);
			P->hands++;
			break;
		}else if(P->discard.array[cc] == 3 && dama >=6){
			eraseVector(&P->discard, cc);
			Card_Define(3 , &P->hands_card[P->hands]);
			P->hands++;
			break;
		}else{
			printf("你不能選那張卡！");
		}
	}
	return 0;
}



// 交換兩個 int16_t 整數的函式
void swap(int16_t *a, int16_t *b) {
    int16_t temp = *a;
    *a = *b;
    *b = temp;
}

// 快速排序的 partition 函式
int32_t partition(int16_t *arr, int32_t low, int32_t high) {
    int16_t pivot = arr[high];
    int32_t i = low - 1;
    for (int32_t j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// 快速排序主函式
void quicksort(int16_t *arr, int32_t low, int32_t high) {
    if (low < high) {
        int32_t p = partition(arr, low, high);
        quicksort(arr, low, p - 1);
        quicksort(arr, p + 1, high);
    }
}


int8_t check_passive(player *P , int check_num){
	int times=0;
	for(int i = 0 ; i < P->passive_n ; i++){
		if(P->passive[i] == check_num){
			times++;
		}
	}
	return times;
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


int8_t gain_sleeptoken(player *P , int8_t amount){
	for(int i = 0 ; i < amount ; i++){
		if(P->sleep_token < P->sleep_token_max){
			P->sleep_token++;
		}
	}
	if(P->sleep_token >= 6 ) P->sleep = 0;
}

int8_t remove_sleeptoken(player *P , int8_t amount){
	for(int i = 0 ; i < amount ; i++){
		if(P->sleep_token > 0){
			P->sleep_token--;
		}
	}
	if(P->sleep_token == 0) P->sleep = 1;
}

int8_t remove_hp(player *P , int8_t damage){
	for(int i = 0 ; i < damage ; i++){
		if(P->hp > 0){
			P->hp--;
		}
	}
}

int8_t regenerate_hp(player *P,int8_t amount){
	for(int i = 0 ; i < amount ; i++){
		if(P->hp < P->Maxhp){
			P->hp++;
		}
	}
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

int8_t print_hands(player *P){
	for(int i = 0 ; i < P->hands ; i++){
		printf("%d) %s 效果：%s\n",i+1,P->hands_card[i].cardname,P->hands_card[i].inf);
	}
	return 0;
}

int8_t check_starting(player *P,player *Enemy){
	for(int i = 0 ; i < P->starting_size ; i++){
		startingskill(P,Enemy,P->starting[i],P->starting_lv[i]);
	}
	initialization_starting(P);
}

int8_t initialization_starting(player *P){
	while(P->starting_size != 0){
		pushbackVector(&P->discard, P->starting[P->starting_size-1]);
		if( P->combo_basic[P->starting_size-1] != 0) pushbackVector(&P->discard, P->combo_basic[P->starting_size-1]);
		P->combo_basic[P->starting_size-1] = 0;
		P->starting_lv[P->starting_size-1] = 0;
		P->starting[P->starting_size-1] = 0;
		P->starting_size--;
	}
}

int8_t clear_select(player *P){
	for(int i = 0 ; i < 50 ; i++){
		P->hands_select[i] = 0; 
	}
}




