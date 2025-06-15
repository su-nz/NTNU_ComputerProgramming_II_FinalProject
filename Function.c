#include "TwistedFables.h"

#define waken_token_MAX 9
#define qi_token_MAX 12
#define tentacle_token_MAX 4
#define combo_token_MAX 12
#define Scheherazade_token_MAX 6
#define matches_MAX 12
#define poison_MAX 18
#define STR_RESET   "\033[0m"
#define STR_BLUE    "\033[34m"

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

int8_t swap_coor(int8_t coor){
	if(coor < 0){
		return 11-coor*(-1)+1;
	}else{
		return (11-coor+1)*(-1);
	}
}

int8_t swap_place(player *P1 ,player *P2){
	system("clear");
	print_game_broad_11();
	print_hands(P1);
	printf("%s請輸入你要捨棄的移動卡(輸入0取消)\n>",P1->charname);
	int8_t cn =-1;
	int p1_C =0;
	int p2_C =0;
	
	if(check_location(swap_coor(P1->coordinate))==-1) return 0;
	if(check_location(swap_coor(P2->coordinate))==-1) return 0;
	while(cn!=0){		
		scanf("%hhd",&cn);
		if(cn == 0)return 0;
		if(P1->hands_card[cn-1].type == 2 || P1->hands_card[cn-1].type == 3){
			p1_C = cn-1;
			break;
		}else{
			printf("這不是移動卡\n>");
		}
	}
	cn =-1;
	system("clear");
	print_game_broad_11();
	print_hands(P2);
	printf("%s請輸入你要捨棄的移動卡\n>",P2->charname);
	while(cn!=0){		
		scanf("%hhd",&cn);
		if(cn == 0)return 0;
		if(P2->hands_card[cn-1].type == 2 || P2->hands_card[cn-1].type == 3){
			p2_C = cn-1;
			break;
		}else{
			printf("這不是移動卡\n>");
		}
		
	}
	
	
							
	discard_card_from_hand(P1,p1_C);
	discard_card_from_hand(P2,p2_C);
	
	P1->coordinate = swap_coor(P1->coordinate);
	P2->coordinate = swap_coor(P2->coordinate);
	
	
	
	
	
	return 0;
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

int8_t showplaycardnum(player *P){
	
	printf("出牌區：");
	
	for(int i = 0 ; i < P->playcardnum ; i++){
	
	}
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

int8_t botChoice(int16_t mode , int16_t min , int16_t  max  , int16_t situation){
	srand((unsigned int)time(NULL));
	if(mode ==0){
		if (min > max) {
			// 自動交換範圍
			int temp = min;
			min = max;
			max = temp;
	    	}
	    	int r = rand() % (max - min + 1) + min;
	    printf(ANSI_BLUE"%d\n"ANSI_BLUE, r);
	    usleep(2000000);
	    return r;	    
	}
	return 0;
}

int8_t clearRHU(player *P){
	P->RedUlt.action =-1; // 0 
	P->RedUlt.range =0;
	P->RedUlt.atk=0;
	P->RedUlt.def=0;
	P->RedUlt.mov=0;
	P->RedUlt.spel_buy=0;
	P->RedUlt.bas_buy=0;
	P->RedUlt.cardid=0;
	return 0;
}

int8_t writeinRHU(player *P,int8_t a1,int8_t a2,int8_t a3,int8_t a4,int8_t a5,int8_t a6,int8_t a7,int8_t a8){
	P->RedUlt.action =a1; // 0 basic 1 skill 2 pass 3 basicbuy 4 spellbuy
	P->RedUlt.range =a2;
	P->RedUlt.atk=a3;
	P->RedUlt.def=a4;
	P->RedUlt.mov=a5;
	P->RedUlt.spel_buy=a6;
	P->RedUlt.bas_buy=a7;
	P->RedUlt.cardid=a8;
	return 0;
}



int8_t inputcharacter(player *P, int8_t characternum) { //寫入角色資訊
	(*P).character = characternum; 
	(*P).bot = 0;
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
    (*P).power = 0;
    (*P).hands = 0;
  	

    return 0; // 成功
}

int8_t Redhoodsavefile(player *P,int BotOn){
	
	while(1){
		system("clear");
	if(check_passive(P,138) >=1){
		if(P->Redhoodsave[0]==-1) P->Redhoodsave[0] = 0;
		card cardtemp1;
		Card_Define(P->Redhoodsave[0], &cardtemp1);
		printf("板載緩存1： %s %s\n",cardtemp1.cardname,cardtemp1.inf);
	}
	if(check_passive(P,138) >=2 ){
		if(P->Redhoodsave[1]==-1) P->Redhoodsave[1] = 0;
		card cardtemp1;
		Card_Define(P->Redhoodsave[1], &cardtemp1);
		printf("板載緩存2： %s %s\n",cardtemp1.cardname,cardtemp1.inf);
	}else{
		printf("板載緩存2： 未開啟\n");
	}
	if(check_passive(P,138) >=3 ){
		if(P->Redhoodsave[2]==-1) P->Redhoodsave[2] = 0;
		card cardtemp1;
		Card_Define(P->Redhoodsave[2], &cardtemp1);
		printf("板載緩存3： %s %s\n",cardtemp1.cardname,cardtemp1.inf);
	}else{
		printf("板載緩存3： 未開啟\n");
	}
	print_hands(P);
	printf("請輸入你要存入卡片還是拿出卡片\n0)存入 1)拿出 2)取消\n");
		int choice_r = -1;
		if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
			choice_r = botChoice(0,0,2,0);
								
		}else{
			scanf("%d",&choice_r);
			getchar();
		}
		
		if(choice_r == 0){
			printf("你要存哪一張牌？(輸入0取消)\n>");
			int8_t cn = -1;
					while(cn!=0){
						if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
										cn = botChoice(0,0,P->hands,0);
										
						}else{
											scanf("%hhd",&cn);
						}
						if(cn == 0 ) break;
						if(cn>=1 && cn <= P->hands){
							printf("你要存哪一個板載緩存？\n>");
							int8_t s = -1;
							
							if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
										s = botChoice(0,1,3,0);
										
							}else{
												scanf("%hhd",&s);
												getchar();
							}
							
							if(s >= 1 && s <= 3){
								if(P->Redhoodsave[s-1] == 0){
									P->Redhoodsave[s-1] = (*P).hands_card[cn-1].cardcode;
									Card_Define(0 , &(*P).hands_card[cn-1]);
									for (int8_t i = cn-1; i < (*P).hands - 1; i++) {
										Card_Define(0, &(*P).hands_card[i]);
										Card_Define((*P).hands_card[i + 1].cardcode , &(*P).hands_card[i]);
									}
									(*P).hands--;
									break;
								}else{
									printf("已有卡片存在\n");
									break;
								}
							}else{
								printf("錯誤數字(範圍0-2)\n");
								break;
							}
						}else{
							printf("沒有這張牌\n");
						}
						
					}
		}else if(choice_r == 1){
		
					while(1){
							printf("你從哪一個板載緩存拿牌？\n>");
							int8_t s = -1;
							if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
										s = botChoice(0,1,3,0);
										
							}else{
												scanf("%hhd",&s);
												getchar();
							}
							
							if(s >= 1 && s <= 3){
								if(P->Redhoodsave[s-1] != 0){
									Card_Define(P->Redhoodsave[s-1] , &P->hands_card[P->hands]);
									P->hands++;
									P->Redhoodsave[s-1] = 0;
									break;
								}else{
									printf("沒有卡片存在\n");
									break;
								}
							}else{
								printf("錯誤數字(範圍0-2)\n");
								break;
							}
							writeinRHU(P,2,0,0,0,0,0,0,0);
					}
					
		}else if(choice_r == 2){
			return 0;
		}							
	}						
	return 0;
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
		printf("請問你要拿哪一牌？（輸入0取消）\n");
		printf("輸入數字：");//TODO: wrong input
		if(P->bot && (P->num == 1 || P->num == 3) ){
			cc = botChoice(0,1,P->discard.SIZE-1	,0);
								
		}else{
			scanf("%hhd",&cc);
		}
		if(cc==0) break;
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
	return 0;
}

int8_t remove_sleeptoken(player *P , int8_t amount){
	for(int i = 0 ; i < amount ; i++){
		if(P->sleep_token > 0){
			P->sleep_token--;
		}
	}
	if(P->sleep_token == 0) P->sleep = 1;
	return 0;
}

int8_t remove_hp(player *P , int8_t damage){
	for(int i = 0 ; i < damage ; i++){
		if(P->hp > 0){
			P->hp--;
		}
	}
	return 0;
}

int8_t regenerate_hp(player *P,int8_t amount){
	for(int i = 0 ; i < amount ; i++){
		if(P->hp < P->Maxhp){
			P->hp++;
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
	return 0;
}

int8_t range_counter(player *P1,player *P2,int8_t range){
	if(abs(P1->coordinate - P2->coordinate) <= range){
		return 1;//in range
	}else{
		return 0;//out of range
	}
	return 0;
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
	return 0;
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
	return 0;
}

int8_t clear_select(player *P){
	for(int i = 0 ; i < 50 ; i++){
		P->hands_select[i] = 0; 
	}
	return 0;
}

/**
 * @brief 將目標玩家牌庫頂的 N 張牌移入棄牌堆
 * @param target 目標玩家
 * @param amount 要棄置的數量
 */
int8_t discard_from_top_of_deck(player* target, int8_t amount) {
    for (int i = 0; i < amount; i++) {
        if (target->deck.SIZE == 0) {
            // 如果牌庫沒牌了，就將棄牌堆洗回去
            if (target->discard.SIZE == 0) {
                // 如果連棄牌堆都沒牌，就無法再棄
                break; 
            }
            discard_back_to_deck(target);
        }
        // 從牌庫頂（陣列末端）棄牌
        pushbackVector(&target->discard, BottomVector(&target->deck));
        popbackVector(&target->deck);
    }
    return 0;
}

/**
 * @brief 將中毒牌放入目標玩家的棄牌堆
 * @param you 技能施放者（白雪公主）
 * @param target 目標玩家
 * @param amount 中毒牌數量
 */
int8_t add_poison_to_discard(player* you, player* target, int8_t amount) {
    for (int i = 0; i < amount; i++) {
        if (you->poison > 0) {
            pushbackVector(&target->discard, POISON_CARD_ID);
            you->poison--;

            // 檢查被動技能 ID 142 (至純之毒)
            // 效果：當一張中毒牌進入對手的棄牌堆時，他額外失去1點生命
            if(check_passive(you, 142) > 0) {
                // 直接扣除生命值，繞過護甲
                if(target->hp > 0) {
                    target->hp--;
                }
            }
        } else {
            // 白雪公主的中毒牌沒了
            break;
        }
    }
    return 0;
}

/**
 * @brief 將玩家 you 移動到玩家 target 的相鄰格子
 * @param you 要移動的玩家
 * @param target 目標玩家
 */
int8_t move_adjacent_to_player(player* you, player* target) {
    int8_t left_pos = target->coordinate - 1;
    int8_t right_pos = target->coordinate + 1;
    int8_t choice = -1;

    // 檢查左右兩邊的位置是否可以移動
    bool can_move_left = (left_pos >= 1);
    bool can_move_right = (right_pos <= 9); // 假設1v1地圖邊界為9

    if (can_move_left && can_move_right) {
        printf("你要移動到對手的哪一側？ (1: 左側, 2: 右側)\n> ");
        if(you->bot == 1) {
            choice = botChoice(0, 1, 2, 0);
            printf("%d\n", choice);
        } else {
            scanf("%hhd", &choice);
            getchar();
        }

        if (choice == 1) {
            you->coordinate = left_pos;
        } else {
            you->coordinate = right_pos;
        }
    } else if (can_move_left) {
        printf("你移動到了對手的左側。\n");
        you->coordinate = left_pos;
    } else if (can_move_right) {
        printf("你移動到了對手的右側。\n");
        you->coordinate = right_pos;
    } else {
        printf("對手處於邊界，沒有可移動的相鄰位置。\n");
    }
    return 0;
}