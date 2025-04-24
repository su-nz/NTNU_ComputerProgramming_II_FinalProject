#include "TwistedFables.h"
#include "vector.h"

int16_t Map[11][3]={0};// Map[x][0]) 遺跡排的紀錄 Map[x][1]) 第一排和單人模式時使用的地圖 Map[x][2]) 第二排// 1v1 9格
//棄牌堆

vector basicBuyDeck[4][3];  // attack(0) LV1~3 defense(1) LV1~3 move(2) LV1~3 generic(3)

vector skillBuyDeck[4][3];  // 4 player 



player player_1,player_2,player_3,player_4;
int8_t mode=-1;
int8_t RelicOn = -1;
int8_t BotOn = -1;
int8_t player1_char = -1;
int8_t player2_char = -1;
int8_t player3_char = -1;
int8_t player4_char = -1;
int8_t turn = 0;
int8_t print_hands(player *P){
	for(int i = 0 ; i < P->hands ; i++){
		printf("%d) %s 效果：%s\n",i+1,P->hands_card[i].cardname,P->hands_card[i].inf);
	}
	return 0;
}

int8_t initialization_deck(player *P){
	for(int i = 0 ; i < 3 ; i++){ //attack 
		pushbackVector(&P->deck, basicBuyDeck[0][0].array[basicBuyDeck[0][0].SIZE-1]);
		popbackVector(&basicBuyDeck[0][0]);
	}
	for(int i = 0 ; i < 3 ; i++){ //defend
		pushbackVector(&P->deck, basicBuyDeck[1][0].array[basicBuyDeck[1][0].SIZE-1]);
		popbackVector(&basicBuyDeck[1][0]);
	}
	for(int i = 0 ; i < 3 ; i++){ //movement 
		pushbackVector(&P->deck, basicBuyDeck[2][0].array[basicBuyDeck[2][0].SIZE-1]);
		popbackVector(&basicBuyDeck[2][0]);
	}
	
	pushbackVector(&P->deck, skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1]);
	popbackVector(&skillBuyDeck[P->num][0]);
	
	pushbackVector(&P->deck, skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1]);
	popbackVector(&skillBuyDeck[P->num][1]);
	
	pushbackVector(&P->deck, skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1]);
	popbackVector(&skillBuyDeck[P->num][2]);
	
				
						
}

int8_t initialization_basic_shop(){
	for(int i = 0 ; i < 3 ; i ++){
		for(int j = 0 ; j < 3 ; j++){
			basicBuyDeck[i][j].SIZE = 18;
			for(int k = 1 ; k <=18 ; k++){
				basicBuyDeck[i][j].array[k] = 1+j+i*3;
			}
			
		}
	}
	basicBuyDeck[3][0].SIZE = 18;
	for(int k = 1 ; k <=18 ; k++){
		basicBuyDeck[4][0].array[k] = 10; 
	}
	return 0; // 成功
}

int8_t initialization_skill_shop(player *P){
	skillBuyDeck[P->num][0].SIZE = 8;
	skillBuyDeck[P->num][1].SIZE = 8;
	skillBuyDeck[P->num][2].SIZE = 8; 
	
	switch (P->character){
		case 0:
		{
			int8_t temp1[] = {138,13,13,13,135,12,12,11};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][0].array[i] = temp1[i];
			}
			int8_t temp2[] = {138,16,16,16,136,15,15,14};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][1].array[i] = temp2[i];
			}
			int8_t temp3[] = {138,19,19,19,137,18,18,17};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][2].array[i]  = temp3[i];
			}	
			break;
		}
		
		case 1:
		{
			int temp4[] = {142,25,25,25,139,24,24,23};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][0].array[i] = temp4[i];
			}

			int temp5[] = {142,28,28,28,140,27,27,26};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][1].array[i] = temp5[i];
			}

			int temp6[] = {142,31,31,31,141,30,30,29};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][2].array[i] = temp6[i];
			}
			break;
		}
	}
	return 0; // 成功
}

int8_t printf_basic_shop(){
	system("clear");
	printf("1.） 攻擊卡 Lv1 費用 1 點能量  卡片剩餘數:%hhd\n",basicBuyDeck[0][0].SIZE);
	printf("2.） 攻擊卡 Lv2 費用 3 點能量  卡片剩餘數:%hhd\n",basicBuyDeck[0][1].SIZE);
	printf("3.） 攻擊卡 Lv3 費用 6 點能量  卡片剩餘數:%hhd\n",basicBuyDeck[0][2].SIZE);
	printf("4.） 防禦卡 Lv1 費用 1 點能量  卡片剩餘數:%hhd\n",basicBuyDeck[1][0].SIZE);
	printf("5.） 防禦卡 Lv2 費用 3 點能量  卡片剩餘數:%hhd\n",basicBuyDeck[1][1].SIZE);
	printf("6.） 防禦卡 Lv3 費用 6 點能量  卡片剩餘數:%hhd\n",basicBuyDeck[1][2].SIZE);
	printf("7.） 移動卡 Lv1 費用 1 點能量  卡片剩餘數:%hhd\n",basicBuyDeck[2][0].SIZE);
	printf("8.） 移動卡 Lv2 費用 3 點能量  卡片剩餘數:%hhd\n",basicBuyDeck[2][1].SIZE);
	printf("9.） 移動卡 Lv3 費用 6 點能量  卡片剩餘數:%hhd\n",basicBuyDeck[2][2].SIZE);
	printf("10.）通用卡 Lv1 費用 2 點能量  卡片剩餘數:%hhd\n",basicBuyDeck[3][0].SIZE);
}

int8_t printf_skill_shop(int8_t player_num){
	
	system("clear");
	
	card cardtemp1;
	Card_Define(skillBuyDeck[player_num][0].array[skillBuyDeck[player_num][0].SIZE-1], &cardtemp1);
	card cardtemp2;
	Card_Define(skillBuyDeck[player_num][1].array[skillBuyDeck[player_num][1].SIZE-1], &cardtemp2);
	card cardtemp3;
	Card_Define(skillBuyDeck[player_num][2].array[skillBuyDeck[player_num][2].SIZE-1], &cardtemp3);
	
	printf("1.）攻擊技能鏈   升級費用 %hhd 點能量  卡片剩餘數:%hhd\n",cardtemp1.cost ,skillBuyDeck[player_num][0].SIZE);
	if(skillBuyDeck[player_num][0].SIZE!=0)printf("目前的卡片：%s\n效果：%s\n\n",cardtemp1.cardname,cardtemp1.inf);
	printf("2.）防禦技能鏈   升級費用 %hhd 點能量  卡片剩餘數:%hhd\n",cardtemp2.cost ,skillBuyDeck[player_num][1].SIZE);
	if(skillBuyDeck[player_num][1].SIZE!=0)printf("目前的卡片：%s\n效果：%s\n\n",cardtemp2.cardname,cardtemp2.inf);
	printf("3.）移動技能鏈   升級費用 %hhd 點能量  卡片剩餘數:%hhd\n",cardtemp3.cost ,skillBuyDeck[player_num][2].SIZE);
	if(skillBuyDeck[player_num][2].SIZE!=0)printf("目前的卡片：%s\n效果：%s\n\n",cardtemp2.cardname,cardtemp2.inf);
}

int8_t skill_shop_command(player *P){
	printf_skill_shop(P->num);
	card cardtemp1;
	Card_Define(skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1], &cardtemp1);
	card cardtemp2;
	Card_Define(skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1], &cardtemp2);
	card cardtemp3;
	Card_Define(skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1], &cardtemp3);
	int8_t ssc =-1;
	printf_skill_shop(P->num);
	while(1){
		printf("請輸入你要做什麼？\n");
		printf("1. 升級技能\n");
		printf("2. 退出商店\n");
		printf("> ");

		scanf("%hhd",&ssc);
		getchar();
		if(ssc == 1){
			int8_t cc =-1;
			printf("請輸入你要升級的技能：") ;
			scanf("%hhd",&cc);
			switch(cc){
				case 1: // 攻擊
					if(P->power < cardtemp1.cost){
						printf("你的能量不夠\n") ;
						
					}else if(skillBuyDeck[P->num][0].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1]);
						skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1] = 0;
						skillBuyDeck[P->num][0].SIZE--;
						P->power -=cardtemp1.cost;
						Card_Define(skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1], &cardtemp1);
						printf_skill_shop(P->num);
					}
				
				break;
				
				case 2: // 防禦
					if(P->power < cardtemp2.cost){
						printf("你的能量不夠\n") ;
						
					}else if(skillBuyDeck[P->num][1].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1]);
						skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1] = 0;
						skillBuyDeck[P->num][1].SIZE--;
						P->power -=cardtemp2.cost;
						Card_Define(skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1], &cardtemp2);
						printf_skill_shop(P->num);
					}
				
				break;
				
				case 3: // 移動
					if(P->power < cardtemp3.cost){
						printf("你的能量不夠\n") ;
						
					}else if(skillBuyDeck[P->num][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1]);
						skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1] = 0;
						skillBuyDeck[P->num][2].SIZE--;
						P->power -=cardtemp3.cost;
						Card_Define(skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1], &cardtemp3);
						printf_skill_shop(P->num);
					}
				
				break;
			
				
				default:
					printf("不存在此選項\n");
				break;
			}
		}else if (ssc == 2){
			
			if(mode == 1){
				print_game_broad_9();
				return 0;
			}else{
				
			}
			action_command(P);
			return 0;
		}else{
			printf("不合法輸入！！\n") ;
		}
	}
	return 0;
}

int8_t discard_command(player *P){
	int8_t dc =-1;
	print_discard(P);
	while(1){
		printf("請輸入你要做什麼？\n");
		printf("1. 查看\n");
		printf("2. 返回\n");
		printf("> ");
		scanf("%hhd",&dc);
		getchar();
		if(dc == 1){
			int8_t cc =-1;
			printf("請輸入你要查看的牌：");
			scanf("%hhd",&cc);
			if(cc > P->discard.SIZE){
				printf("沒有這張卡！\n");
			}else{
				card temp_card;
				Card_Define(P->discard.array[cc-1] , &temp_card);
				printf("卡名：%s 效果：%s\n",temp_card.cardname,temp_card.inf);
			}
		}else{
			if(mode == 1){
				print_game_broad_9();
				return 0;
			}else{
				
			}
			action_command(P);
			return 0;
		}
	}
}

int8_t basic_shop_command(player *P){
	int8_t bsc =-1;
	printf_basic_shop();
	while(1){	
		printf("請輸入你要做什麼？\n");
		printf("1. 購買卡片\n");
		printf("2. 退出商店\n");
		printf("> ");
		scanf("%hhd",&bsc);
		getchar();
		if(bsc == 1){
			int8_t cc =-1;
			printf("請輸入你要購買的卡片：") ;
			scanf("%hhd",&cc);
			switch(cc){
				case 1: // 攻擊卡 1
					if(P->power < 1){
						printf("你的能量不夠\n") ;
						
					}else if(basicBuyDeck[0][0].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, basicBuyDeck[0][0].array[basicBuyDeck[0][0].SIZE-1]);
						basicBuyDeck[0][0].array[basicBuyDeck[0][0].SIZE-1] = 0;
						basicBuyDeck[0][0].SIZE--;
						P->power--;
						printf_basic_shop();
					}
				
				break;
				
				case 2: // 攻擊卡 2
					if(P->power < 3){
						printf("你的能量不夠\n") ;
						
					}else if(basicBuyDeck[0][1].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, basicBuyDeck[0][1].array[basicBuyDeck[0][1].SIZE-1]);
						basicBuyDeck[0][1].array[basicBuyDeck[0][1].SIZE-1] = 0;
						basicBuyDeck[0][1].SIZE--;
						P->power-=3;
						printf_basic_shop();
					}
				
				break;
				
				case 3: // 攻擊卡 3
					if(P->power < 6){
						printf("你的能量不夠\n") ;
						
					}else if(basicBuyDeck[0][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, basicBuyDeck[0][2].array[basicBuyDeck[0][2].SIZE-1]);
						basicBuyDeck[0][2].array[basicBuyDeck[0][2].SIZE-1] = 0;
						basicBuyDeck[0][2].SIZE--;
						P->power-=6;
						printf_basic_shop();
					}
				
				break;
				
				case 4: // 防禦卡 1
					if(P->power < 1){
						printf("你的能量不夠\n") ;
						
					}else if(basicBuyDeck[1][0].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, basicBuyDeck[1][0].array[basicBuyDeck[1][0].SIZE-1]);
						basicBuyDeck[1][0].array[basicBuyDeck[1][0].SIZE-1] = 0;
						basicBuyDeck[1][0].SIZE--;
						P->power--;
						printf_basic_shop();
					}
				
				break;
				
				case 5: // 防禦卡 2
					if(P->power < 3){
						printf("你的能量不夠\n") ;
						
					}else if(basicBuyDeck[1][1].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, basicBuyDeck[1][1].array[basicBuyDeck[1][1].SIZE-1]);
						basicBuyDeck[1][1].array[basicBuyDeck[1][1].SIZE-1] = 0;
						basicBuyDeck[1][1].SIZE--;
						P->power-=3;
						printf_basic_shop();
					}
				
				break;
				
				case 6: // 防禦卡 3
					if(P->power < 6){
						printf("你的能量不夠\n") ;
						
					}else if(basicBuyDeck[1][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, basicBuyDeck[1][2].array[basicBuyDeck[1][2].SIZE-1]);
						basicBuyDeck[1][2].array[basicBuyDeck[1][2].SIZE-1] = 0;
						basicBuyDeck[1][2].SIZE--;
						P->power-=6;
						printf_basic_shop();
					}
				
				break;
				
				case 7: // 移動卡 1
					if(P->power < 1){
						printf("你的能量不夠\n") ;
						
					}else if(basicBuyDeck[2][0].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, basicBuyDeck[2][0].array[basicBuyDeck[2][0].SIZE-1]);
						basicBuyDeck[2][0].array[basicBuyDeck[2][0].SIZE-1] = 0;
						basicBuyDeck[2][0].SIZE--;
						P->power--;
						printf_basic_shop();
					}
				
				break;
				
				case 8: // 移動卡 2
					if(P->power < 3){
						printf("你的能量不夠\n") ;
						
					}else if(basicBuyDeck[2][1].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, basicBuyDeck[2][1].array[basicBuyDeck[2][1].SIZE-1]);
						basicBuyDeck[2][1].array[basicBuyDeck[2][1].SIZE-1] = 0;
						basicBuyDeck[2][1].SIZE--;
						P->power-=3;
						printf_basic_shop();
					}
				
				break;
				
				case 9: // 移動卡 3
					if(P->power < 6){
						printf("你的能量不夠\n") ;
						
					}else if(basicBuyDeck[2][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, basicBuyDeck[2][2].array[basicBuyDeck[2][2].SIZE-1]);
						basicBuyDeck[2][2].array[basicBuyDeck[2][2].SIZE-1] = 0;
						basicBuyDeck[2][2].SIZE--;
						P->power-=6;
						printf_basic_shop();
					}
				
				break;
				
				case 10: // 通用卡 
					if(P->power < 2){
						printf("你的能量不夠\n") ;
						
					}else if(basicBuyDeck[2][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, basicBuyDeck[3][0].array[basicBuyDeck[3][0].SIZE-1]);
						basicBuyDeck[3][0].array[basicBuyDeck[3][0].SIZE-1] = 0;
						basicBuyDeck[3][0].SIZE--;
						P->power-=2;
						printf_basic_shop();
					}
				
				break;
				
				default:
					printf("不存在此選項\n");
				break;
			}
		}else if (bsc == 2){
			
			if(mode == 1){
				print_game_broad_9();
				return 0;
			}else{
				
			}
			action_command(P);
			return 0;
		}else{
			printf("不合法輸入！！\n") ;
		}
	}
	return 0;
}
	
int8_t remove_card(player *P){
	system("clear");
	int8_t comm=-1;
	printf("請問你要對哪一個地方使用專注？\n");
	printf("0. 手牌\n");
	printf("1. 棄牌堆\n");
	printf("2. 返回\n");
	printf("> ");
	scanf("%hhd",&comm);
	switch(comm){
		case 0:
			while(1){
				print_hands(P);
				int8_t select=-1;
				if((*P).hands == 0){
					if(mode == 1){
						print_game_broad_9();
						
					}else{
							
					}
					printf("你沒有手牌了！\n");
					action_command(P);
				}
				printf("請問你要移除哪一牌？\n");
				printf("輸入數字：");
				scanf("%hhd",&select);
				if(select > P->hands || select <= 0 ){
						printf("沒有這張卡！\n");
				}else{
					Card_Define(0 , &(*P).hands_card[select-1]);
					for (int8_t i = select-1; i < (*P).hands - 1; i++) {
						Card_Define(0, &(*P).hands_card[i]);
						Card_Define((*P).hands_card[i + 1].cardcode , &(*P).hands_card[i]);
					}
					(*P).hands--;
					return -1;
				}
				
			}
			return -1;
		break;
		
		case 1:
			while(1){//
				if(P->discard.SIZE == 0){
					if(mode == 1){
						print_game_broad_9();
						
					}else{
							
					}
					printf("你的棄牌堆沒有牌！\n");
					action_command(P);
					return 0;
				}
				int8_t cc=-1;
				printf("請問你要移除哪一牌？\n");
				printf("輸入數字：");
				scanf("%hhd",&cc);
				if(cc > P->discard.SIZE){
					printf("沒有這張卡！\n");
					break;
				}else{
					eraseVector(&P->discard, cc);
					break;
				}
				
			}
			return -1;
		break;
		
		case 2:
		
		if(mode == 1){
			print_game_broad_9();
			
		}else{
				
		}
		action_command(P);
		return 0;
		
		break;
		
	}
}

int8_t play_a_card(player *P){
	system("clear");
	print_game_broad_9();
	print_hands(P);
	printf("你要打哪一張牌？（輸入0返回）\n");
	while(1){
		int8_t select=-1;
		if((*P).hands == 0){
			if(mode == 1){
				print_game_broad_9();
						
				}else{			
			}
			printf("你沒有手牌了！\n");
			action_command(P);
		}
		printf("請問你要打哪一張牌？\n");
		printf("輸入數字：");
		scanf("%hhd",&select);
		if(select == 0){
			if(mode == 1){
				print_game_broad_9();
				return 0;
			}else{
				
			}
			action_command(P);
			return 0;
		}
	
		if(select > P->hands || select < 0 ){
				printf("沒有這張卡！\n");
		}else{
			switch (P->hands_card[select-1].type){
				case 0:
					
				break;
					
			}
			return -1;
		}
				
	}
}

int8_t action_command(player *P){
	int8_t comm=-1;
	
	printf("現在是"GREEN BOLD"%s"RESET"的回合，現在是你的執行階段請從以下的動作中選一個執行\n",(*P).charname);
	printf("1. 購買基礎牌\n");
	printf("2. 購買技能牌\n");
	printf("3. 打牌\n");
	printf("4. 查看自己的棄牌堆\n");
	printf("5. 查看別人的棄牌堆\n");
	printf("6. 結束回合\n\n");

	printf("你的手牌：\n");
	print_hands(P);
	printf("輸入指令：");
	scanf("%hhd",&comm);
	getchar();
	switch(comm){
		
		
            	
            	
            	case 1:  // 購買基礎牌
			basic_shop_command(P);
		
            	break;
            	
            	case 2:  // 購買技能牌
			skill_shop_command(P);
		
            	break;
            	
            	case 3:  // 打牌
			play_a_card(P);
		
            	break;
            	
            	case 4:  // 查看自己的棄牌
            		
			discard_command(P);
			
		
            	break;
            	
            	case 5:  // 查看別人的棄牌堆
            		if(mode ==1){// 新增不同回合要換人
				discard_command(&player_2);
			}
		
            	break;
            	
            	case 6:  // 結束遊戲階段
		return -1;
		
            	break;
	}
	print_game_broad_9();
	action_command(P);
	return 0;
}




void print_extra_inf(player *P){
	if((*P).poison != -1){
		printf("中毒牌組：%hhd\n",(*P).poison);
	}
	if((*P).matches!= -1){
		printf("火柴牌組：%hhd\n",(*P).matches);
	}
	if((*P).sleep != -1){
		if((*P).sleep == 1){ //沉睡
			printf("睡美人目前是\033[1;32m沉睡狀態\033[0m，他的白馬王子在哪？\n");
		}else{ //覺醒
			printf("睡美人目前是\033[1;32m覺醒狀態\033[0m，她不需要白馬王子？\n");
		}
	}
	if((*P).alice != -1){ //愛麗絲 狀態 -1代表不是愛麗絲
		if((*P).alice == 0){ 
			printf("愛麗絲目前是\033[1;31m紅心皇后\033[0m，注意你的人頭！\n");
		}else if((*P).alice == 1){ 
			printf("睡美人目前是\033[1;34m瘋帽子\033[0m，請不要跟她說話！\n");
		}else{ 
			printf("睡美人目前是\033[1;35m柴郡貓\033[0m，你追不上她的速度！\n");
		}
	}
	if((*P).qi != -1){ //花木蘭 氣 -1代表不是花木蘭
		printf("氣：%hhd\n",(*P).qi);
	}
	if((*P).combo != -1){ //桃樂絲 連擊 -1代表不是桃樂絲
		printf("連擊：%hhd\n",(*P).combo);
	}
	if((*P).tentacle != -1){
		printf("觸手：%hhd\n",(*P).tentacle);
	}
	if((*P).Scheherazade_token != -1){
		printf("Token數量：%hhd\n",(*P).Scheherazade_token);
	}
}

int8_t utf8_strlen(const char *s) {
	int8_t len = 0;
	while (*s) {
		if ((*s & 0x80) == 0) s += 1;         // 英文
		else if ((*s & 0xE0) == 0xC0) s += 2; // 少見
		else if ((*s & 0xF0) == 0xE0) s += 3; // 中文
		else if ((*s & 0xF8) == 0xF0) s += 4; // emoji
		else s += 1;
		len++;
	}
	return len;
}

void print_game_broad_9(){
	int8_t len = 0;
	if(utf8_strlen(player_1.charname) == 3 && utf8_strlen(player_2.charname) == 3) len = 6;
	else len = 8;
	system("clear");
	printf("玩家一 │ 遊玩角色：");
	print_aligned_charname(player_1.charname, len);
	printf(" 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n", player_1.hp, player_1.armor, player_1.power, player_1.hands, player_1.Maxhp, player_1.Maxarmor, player_1.Ult_threshold);
	print_extra_inf(&player_1);

	printf("玩家二 │ 遊玩角色：");
	print_aligned_charname(player_2.charname, len);
	printf(" 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n", player_2.hp, player_2.armor, player_2.power, player_2.hands, player_2.Maxhp, player_2.Maxarmor, player_2.Ult_threshold);
	print_extra_inf(&player_2);

	printf("          ┌───────────────────┐           \n");
	
	//printf("     Board│ O O O O O O O O O │版面                   \n");//10
	printf("     Board│ ");
	for(int i = 0 ; i < 9 ; i++){
		if(player_1.coordinate == i){
			printf("1 ");
		}else if(player_2.coordinate == i){
			printf("2 ");
		}else{
			printf("_ ");
		}	
	}
	printf("│版面                   \n");
	printf("          ├───────────────────┤           \n");
	printf("Coordinate│ 1 2 3 4 5 6 7 8 9 │座標                   \n");
	printf("          └───────────────────┘           \n");
	return ;
}

void print_header()
{
	printf("\033[2J");
	printf("\033[H");
	printf("╔═══════════════════════╗\n");
	printf("║     Twisted Fables    ║\n");
	printf("║    反轉寓言：文字版   ║\n");
	printf("╚═══════════════════════╝\n");

	printf("遊戲模式　：");
	if(mode == 1) printf("1對1\n");
	else if(mode == 2) printf("2對2\n");
	else printf("（未選擇）\n");

	printf("遺跡模式　：");        
	if(RelicOn == 1) printf("是\n");        
	else if(RelicOn == 2) printf("否\n");        
	else printf("（未選擇）\n");

	printf("啟用機器人：");        
	if(BotOn == 1) printf("是\n");        
	else if(BotOn == 2) printf("否\n");        
	else printf("（未選擇）\n");

	printf("玩家一　　：");	
	if(player_1.charname) printf("%s\n", player_1.charname);	
	else printf("（未選擇）\n");
	
	printf("玩家二　　：");        
	if(player_2.charname) printf("%s\n", player_2.charname);        
	else printf("（未選擇）\n");

	printf("玩家三　　：");        
	if(player_3.charname) printf("%s\n", player_3.charname);        
	else printf("（未選擇）\n");

	printf("玩家四　　：");        
	if(player_4.charname) printf("%s\n\n", player_4.charname);        
	else printf("（未選擇）\n\n");
}

int8_t get_random_unused_character(int8_t remaining_roles[], int8_t remaining_count) {
	if (remaining_count <= 0) return -1;

	int8_t pick = rand() % remaining_count;
	for (int8_t i = 0; i < 10; i++) {        
		if (remaining_roles[i]) {            
			if (pick == 0) return i;            
			pick--;        
		}    
	}
	return -1;
}

void enable_raw_mode() {
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void disable_raw_mode() {
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= ICANON | ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void wait_for_space() {
	enable_raw_mode();
	printf("按下空白鍵開始遊戲");
	int8_t ch;
	while ((ch = getchar()) != ' ') {}
	disable_raw_mode();
}

int8_t str_display_width(const char *s) {
	int8_t width = 0;
    	while (*s) {
		if ((*s & 0x80) == 0) {
			width += 1;
			s++;
		} else {
			width += 2;
			s += 3;
		}
	}
	return width;
}

void print_aligned_charname(const char* name, int8_t width) {    
	int8_t actual_width = str_display_width(name);    
	printf("%s", name);    
	for (int8_t i = 0; i < width - actual_width; i++) putchar(' ');
}

int main(){ //mainfuc
	system("clear");
	print_header();
	srand( time(NULL) );
	
	initialization_basic_shop();
	
	//mode=-1
	printf("請選擇遊戲模式：\n");
	printf("1. 1對1\n");
	printf("2. 2對2\n");
	printf("> ");
	while (scanf("%hhd",&mode)!=1 || !(mode == 1 || mode ==2 )){
		getchar();
		print_header();
		printf("請你重新輸入\n");
		printf("請選擇遊戲模式：\n");
	        printf("1. 1對1\n");
        	printf("2. 2對2\n");
		printf("> ");
	} 
	player_1.num = 0;
	player_2.num = 1;
	player_3.num = 2;
	player_4.num = 3;
	
	player_1.coordinate = 4;
	player_2.coordinate = 6;
	
	//RelicOn = -1
	print_header();
	printf("是否要啟動遺跡模式：\n");
	printf("1. 是\n");
	printf("2. 否\n");
	printf("> ");
	while (scanf("%hhd",&RelicOn)!=1 || !(RelicOn == 1 || RelicOn == 2 )){
		getchar();
		print_header();
		printf("請你重新輸入\n");
		printf("是否要啟動遺跡模式：\n");
	        printf("1. 是\n");
       		printf("2. 否\n");
	        printf("> ");
	} 
	
	//BotOn = -1
	print_header();
	printf("是否要啟用機器人：\n");
	printf("1. 是\n");
        printf("2. 否\n");
        printf("> ");
	while (scanf("%hhd",&BotOn)!=1 || !(BotOn == 1 || BotOn == 2 )){
		getchar();
		print_header();
		printf("請你重新輸入\n");
		printf("是否要啟用機器人：\n");
	        printf("1. 是\n");
        	printf("2. 否\n");
	        printf("> ");
	} 
	
	//player1_char = -1
	int8_t remaining_roles[10];
	for (int8_t i = 0; i < 10; i++) {
		remaining_roles[i] = 1;
	}
	int8_t remaining_count = 10;
	print_header();
	printf("====================\n");
	printf("0)小紅帽\n");
	printf("1)白雪公主\n");
	printf("2)睡美人\n");
	printf("3)愛麗絲\n");
	printf("4)花木蘭\n");
	printf("5)輝夜姬\n");
	printf("6)美人魚\n");
	printf("7)火柴女孩\n");
	printf("8)逃樂絲\n");
	printf("9)山魯佐德\n");
	printf("10)隨機\n");
	printf("====================\n");
	printf("玩家一請選擇你要遊玩的角色：");
	while (scanf("%hhd",&player1_char)!=1 || !(player1_char >= 0 && player1_char <= 10 )){
		getchar();
		print_header();
		printf("輸入了不可選的角色或是其他人已選擇的角色\n");
		printf("====================\n");
		printf("0)小紅帽\n");
		printf("1)白雪公主\n");
		printf("2)睡美人\n");
		printf("3)愛麗絲\n");
		printf("4)花木蘭\n");
		printf("5)輝夜姬\n");
		printf("6)美人魚\n");
		printf("7)火柴女孩\n");
		printf("8)逃樂絲\n");
		printf("9)山魯佐德\n");
		printf("10)隨機\n");
		printf("====================\n");
		printf("玩家一請選擇你要遊玩的角色：");
		
	} 
	if(player1_char == 10){
		player1_char = get_random_unused_character(remaining_roles, remaining_count);
	}
	inputcharacter(&player_1, player1_char);
	remaining_roles[player1_char] = 0;
	remaining_count--;
	
	print_header();
	printf("====================\n");
	printf("0)小紅帽\n");
	printf("1)白雪公主\n");
	printf("2)睡美人\n");
	printf("3)愛麗絲\n");
	printf("4)花木蘭\n");
	printf("5)輝夜姬\n");
	printf("6)美人魚\n");
	printf("7)火柴女孩\n");
	printf("8)逃樂絲\n");
	printf("9)山魯佐德\n");
	printf("10)隨機\n");
	printf("====================\n");
	if(BotOn==1){
		printf("請選擇電腦要遊玩的角色：");
	}else{
		printf("玩家二請選擇你要遊玩的角色：");
	}
	while (scanf("%hhd",&player2_char)!=1 || !(player2_char >= 0 && player2_char <= 10 )||(player2_char == player1_char)){
		getchar();
		print_header();
		printf("輸入了不可選的角色或是其他人已選擇的角色\n");
		printf("====================\n");
		printf("0)小紅帽\n");
		printf("1)白雪公主\n");
		printf("2)睡美人\n");
		printf("3)愛麗絲\n");
		printf("4)花木蘭\n");
		printf("5)輝夜姬\n");
		printf("6)美人魚\n");
		printf("7)火柴女孩\n");
		printf("8)逃樂絲\n");
		printf("9)山魯佐德\n");
		printf("10)隨機\n");
		printf("====================\n");
		if(BotOn==1){
			printf("請選擇電腦要遊玩的角色：");
		}else{
			printf("玩家二請選擇你要遊玩的角色：");
		}
		
	} 
	if(player2_char == 10){
                player2_char = get_random_unused_character(remaining_roles, remaining_count);
        }
        inputcharacter(&player_2, player2_char);
        remaining_roles[player2_char] = 0;
        remaining_count--;
	
	if(mode == 2 ){
		print_header();
		printf("====================\n");
		printf("0)小紅帽\n");
		printf("1)白雪公主\n");
		printf("2)睡美人\n");
		printf("3)愛麗絲\n");
		printf("4)花木蘭\n");
		printf("5)輝夜姬\n");
		printf("6)美人魚\n");
		printf("7)火柴女孩\n");
		printf("8)逃樂絲\n");
		printf("9)山魯佐德\n");
		printf("10)隨機\n");
		printf("====================\n");
		printf("玩家三請選擇你要遊玩的角色：");
		while (scanf("%hhd",&player3_char)!=1 || !(player3_char >= 0 && player3_char <= 10 )||(player3_char == player1_char)||(player3_char == player2_char)){
			getchar();
			print_header();
			printf("輸入了不可選的角色或是其他人已選擇的角色\n");
			printf("====================\n");
			printf("0)小紅帽\n");
			printf("1)白雪公主\n");
			printf("2)睡美人\n");
			printf("3)愛麗絲\n");
			printf("4)花木蘭\n");
			printf("5)輝夜姬\n");
			printf("6)美人魚\n");
			printf("7)火柴女孩\n");
			printf("8)逃樂絲\n");
			printf("9)山魯佐德\n");
			printf("10)隨機\n");
			printf("====================\n");
			printf("玩家三請選擇你要遊玩的角色：");
		} 
		if(player3_char == 10){
	                player3_char = get_random_unused_character(remaining_roles, remaining_count);
	        }
	        inputcharacter(&player_3, player3_char);
	        remaining_roles[player3_char] = 0;
	        remaining_count--;
		
		print_header();
		printf("====================\n");
		printf("0)小紅帽\n");
		printf("1)白雪公主\n");
		printf("2)睡美人\n");
		printf("3)愛麗絲\n");
		printf("4)花木蘭\n");
		printf("5)輝夜姬\n");
		printf("6)美人魚\n");
		printf("7)火柴女孩\n");
		printf("8)逃樂絲\n");
		printf("9)山魯佐德\n");
		printf("10)隨機\n");
		printf("====================\n");
		if(BotOn==1){
			printf("請選擇電腦二要遊玩的角色：");
		}else{
			printf("玩家四請選擇你要遊玩的角色：");
		}
		while (scanf("%hhd",&player4_char)!=1 || !(player4_char >= 0 && player4_char <= 10 )||(player4_char == player1_char)||(player4_char == player2_char)||(player4_char == player3_char)){
			getchar();
			print_header();
			printf("輸入了不可選的角色或是其他人已選擇的角色\n");
			printf("====================\n");
			printf("0)小紅帽\n");
			printf("1)白雪公主\n");
			printf("2)睡美人\n");
			printf("3)愛麗絲\n");
			printf("4)花木蘭\n");
			printf("5)輝夜姬\n");
			printf("6)美人魚\n");
			printf("7)火柴女孩\n");
			printf("8)逃樂絲\n");
			printf("9)山魯佐德\n");
			printf("10)隨機\n");
			printf("====================\n");
			if(BotOn==1){
				printf("請選擇電腦二要遊玩的角色：");
			}else{
				printf("玩家四請選擇你要遊玩的角色：");
			}
			
		} 
		if(player4_char == 10){
	                player4_char = get_random_unused_character(remaining_roles, remaining_count);
	        }
	        inputcharacter(&player_4, player4_char);
	        remaining_roles[player4_char] = 0;
	        remaining_count--;
	}
	
	initialization_skill_shop(&player_1);
	initialization_skill_shop(&player_2);
	initialization_deck(&player_1);
	initialization_deck(&player_2);	

	print_header();	
	wait_for_space();
	//遊戲開始
	int8_t round = 0;
	int8_t flip_coins=0;
	flip_coins = rand()%2+1;
	if(flip_coins == 1){
		//player 1 first
		if(mode == 1){
			player_1.first = 1;
		}
	}else{
		//player 2 first
		if(mode == 1){
			player_2.first = 1;
		}
	}
	
	if(player_1.first == 1){//玩家一先手
		
	}
	while(1){
		if(mode == 1){//單人模式
			round++;
			while(1){ // 執行階段
				 turn = 0;
				if(player_1.first == 1){//玩家一先手
					if(round == 1){
						draw_card(4,&player_1);
					}else{
						draw_card(6,&player_1);
					}
					draw_card(6,&player_2);
					//補一個專注
					print_game_broad_9();
					if(round % 2 == 1){
						if(round == 1) printf("玩家一先手\n");	
						if(action_command(&player_1) == -1) break;
						
					}else{
						if(action_command(&player_2)== -1) break;
					}
				}else{
					draw_card(6,&player_1);
					if(round == 1){
						draw_card(4,&player_2);
					}else{
						draw_card(6,&player_2);
					}
					print_game_broad_9();
					if(round % 2 == 1){
						if(round == 1) printf("玩家二先手\n");
						if(action_command(&player_2)== -1) break;
					}else{
						if(action_command(&player_1) == -1) break;
					}
				}
			}
			//判斷輸贏
		}
		
		
		
	} 
	return 0;
}
