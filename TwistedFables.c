#include "TwistedFables.h"
#include "vector.h"

int16_t Map[11][3]={0};// Map[x][0]) 遺跡排的紀錄 Map[x][1]) 第一排和單人模式時使用的地圖 Map[x][2]) 第二排// 1v1 9格
//棄牌堆

vector basicBuyDeck[4][3];  // attack(0) LV1~3 defense(1) LV1~3 move(2) LV1~3 generic(3)

vector skillBuyDeck[4][3];  // 4 player 


player Player[4];
int8_t Right_MAX = 0;
int8_t mode=-1;
int8_t RelicOn = -1;
int8_t BotOn = -1;
int8_t player1_char = -1;
int8_t player2_char = -1;
int8_t player3_char = -1;
int8_t player4_char = -1;
int8_t turn = 0;
int8_t gui_mode = 1;


int RedHoodHPtemp=30;
int MulanHPtemp=34;
void handle_sigint(int sig) {
    printf("\n收到 Ctrl+C，中止程式...\n");
    exit(0);
}

int8_t initialize_player(player *P){
	if(P->character == 0){
		P->Redhoodsave[0] = -1;
		P->Redhoodsave[1] = -1;
		P->Redhoodsave[2] = -1;
		
	}
	return 0;
}
int8_t check_location(int8_t coor){
	if(coor == Player[0].coordinate){
		return -1;
	}else if(coor == Player[1].coordinate){
		return -1;
	}else if(coor == Player[2].coordinate){
		return -1;
	}else if(coor == Player[3].coordinate){
		return -1;
	}
	return 0;
}
int get_next_player(int prev, player Player[4]) {
	int team0_alive[2], team1_alive[2];
	int t0_count = 0, t1_count = 0;

	// 分別找出每隊的存活玩家
	for (int i = 0; i < 4; i++) {
		if (Player[i].alive) {
			if (Player[i].team == 0)
				team0_alive[t0_count++] = i;
			else
				team1_alive[t1_count++] = i;
		}
	}

	// 1v1
	if (t0_count == 1 && t1_count == 1) {
		// 交替進行，prev = 上一位，下一位就是另一隊的人
		if (Player[prev].team == 0) return team1_alive[0];
		else return team0_alive[0];
	}

	// 若有隊伍只剩一人，該人執行兩次（模擬死隊友的輪次）
	if (t0_count == 1) {
		if (Player[prev].team == 1) return team0_alive[0]; // 敵人剛動完，換該隊唯一生存者
		else return team1_alive[(team1_alive[0] != prev) ? 0 : 1]; // 換敵隊其他人
	}

	if (t1_count == 1) {
		if (Player[prev].team == 0) return team1_alive[0];
		else return team0_alive[(team0_alive[0] != prev) ? 0 : 1];
	}

	// 四人都活著 → 正常順時針循環（P0→P1→P2→P3→P0）
	int next = (prev + 1) % 4;
	while (!Player[next].alive)
		next = (next + 1) % 4;
	return next;
}

int8_t target(player *you){
	if(you->coordinate > 0){
		if(Player[0].coordinate > 0 && Player[0].coordinate != you->coordinate) return Player[0].num;
		if(Player[1].coordinate > 0 && Player[1].coordinate != you->coordinate) return Player[1].num;
		if(Player[2].coordinate > 0 && Player[2].coordinate != you->coordinate) return Player[2].num;
		if(Player[3].coordinate > 0 && Player[3].coordinate != you->coordinate) return Player[3].num;
	}else{
		if(Player[0].coordinate < 0 && Player[0].coordinate != you->coordinate) return Player[0].num;
		if(Player[1].coordinate < 0 && Player[1].coordinate != you->coordinate) return Player[1].num;
		if(Player[2].coordinate < 0 && Player[2].coordinate != you->coordinate) return Player[2].num;
		if(Player[3].coordinate < 0 && Player[3].coordinate != you->coordinate) return Player[3].num;
	}
	return 0;
}

int8_t end_game_detection(){

	if(Player[0].hp ==0){
		Player[0].alive = 0;
		Player[0].coordinate = 99;
	}
	if(Player[1].hp ==0){
		Player[1].alive = 0;
		Player[1].coordinate = 99;
	}
	if(Player[2].hp ==0){
		Player[2].alive = 0;
		Player[2].coordinate = 99;
	}
	if(Player[3].hp ==0){
		Player[3].alive = 0;
		Player[3].coordinate = 99;
	}
	if(mode == 1){
		if(Player[0].hp <=0){
			
			return 1;
			
		}else if(Player[1].hp <=0){
			
			return 1;
		}}else{
		if(Player[0].hp <=0 && Player[2].hp <=0){
			
			return 1;
			
		}else if(Player[3].hp <=0 && Player[1].hp <=0){
			
			return 1;
		}
	}
	return 0;
}
	

int8_t print_end_game(){
	if(mode == 1){
		if(Player[0].hp <=0){
			if(BotOn ==1){
				system("clear");
				printf("電腦-%s勝利\n",Player[1].charname);
				return 1;
			}else{
				system("clear");
				printf("玩家二-%s勝利\n",Player[1].charname);
				return 1;
			}
		}else{
			system("clear");
			printf("玩家一-%s勝利\n",Player[0].charname);
			return 1;
		}
	}else{
			if(Player[0].hp <=0 && Player[2].hp <=0){
			if(BotOn ==1){
				system("clear");
				printf("電腦 勝利\n");
				return 1;
			}else{
				system("clear");
				printf("玩家二-%s 和 玩家四-%s 勝利\n",Player[1].charname,Player[3].charname);
				return 1;
			}
		}else if(Player[1].hp <=0 && Player[3].hp <=0){
			system("clear");
			printf("玩家一-%s 和 玩家三-%s 勝利\n",Player[0].charname,Player[2].charname);
			return 1;
		}
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
	
	for(int i = 0 ; i < 5 ; i++)shuffle(&P->deck);
				
	return 0;	
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
		basicBuyDeck[3][0].array[k] = 10; 
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
			int16_t temp1[] = {138,13,13,13,135,12,12,11};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][0].array[i] = temp1[i];
			}
			int16_t temp2[] = {138,16,16,16,136,15,15,14};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][1].array[i] = temp2[i];
			}
			int16_t temp3[] = {138,19,19,19,137,18,18,17};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][2].array[i]  = temp3[i];
			}	
			P->Ult_deck[0] = 20;
			P->Ult_deck[1] = 21;
			P->Ult_deck[2] = 22;
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
			
			P->Ult_deck[0] = 32;
			P->Ult_deck[1] = 33;
			P->Ult_deck[2] = 34;
			break;
		}
		
		case 2:
		{
			int temp7[] = {146,37,37,37,143,36,36,35};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][0].array[i] = temp7[i];
			}

			int temp8[] = {146,40,40,40,144,39,39,38};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][1].array[i] = temp8[i];
			}

			int temp9[] = {146,43,43,43,145,42,42,41};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][2].array[i] = temp9[i];
			}
			
			P->Ult_deck[0] = 44;
			P->Ult_deck[1] = 45;
			P->Ult_deck[2] = 46;
			break;
		}
		case 4:
		{
			int16_t temp13[] = {154,61,61,61,151,60,60,59};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][0].array[i] = temp13[i];
			}

			int16_t temp14[] = {154,64,64,64,152,63,63,62};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][1].array[i] = temp14[i];
			}

			int16_t temp15[] = {154,67,67,67,153,66,66,65};
			for (int i = 0; i < 8; ++i) {
			    skillBuyDeck[P->num][2].array[i] = temp15[i];
			}

			P->Ult_deck[0] = 68;
			P->Ult_deck[1] = 69;
			P->Ult_deck[2] = 70;
			break;
		}
		case 5:
		{
			int16_t temp16[] = {158, 73, 73, 73, 155, 72, 72, 71};
			for (int i = 0; i < 8; ++i) {
				skillBuyDeck[P->num][0].array[i] = temp16[i];
			}

			int16_t temp17[] = {158, 76, 76, 76, 156, 75, 75, 74};
			for (int i = 0; i < 8; ++i) {
				skillBuyDeck[P->num][1].array[i] = temp17[i];
			}

			int16_t temp18[] = {158, 79, 79, 79, 157, 78, 78, 77};
			for (int i = 0; i < 8; ++i) {
				skillBuyDeck[P->num][2].array[i] = temp18[i];
			}
			break;
		}
		case 7: // 火柴女孩
		{
			int16_t temp_atk[] = {156, 85, 85, 85, 155, 84, 84, 83};
			for (int i = 0; i < 8; ++i) {
				skillBuyDeck[P->num][0].array[i] = temp_atk[i];
			}

			int16_t temp_def[] = {158, 88, 88, 88, 157, 87, 87, 86};
			for (int i = 0; i < 8; ++i) {
				skillBuyDeck[P->num][1].array[i] = temp_def[i];
			}

			int16_t temp_mov[] = {160, 91, 91, 91, 159, 90, 90, 89};
			for (int i = 0; i < 8; ++i) {
				skillBuyDeck[P->num][2].array[i] = temp_mov[i];
			}

			P->Ult_deck[0] = 92;
			P->Ult_deck[1] = 93;
			P->Ult_deck[2] = 94;
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
	return 0;
}

int8_t printf_skill_shop(int8_t player_num){
	
	system("clear");
	
	card cardtemp1;
	if(skillBuyDeck[player_num][0].SIZE >0)Card_Define(skillBuyDeck[player_num][0].array[skillBuyDeck[player_num][0].SIZE-1], &cardtemp1);
	card cardtemp2;
	if(skillBuyDeck[player_num][1].SIZE >0)Card_Define(skillBuyDeck[player_num][1].array[skillBuyDeck[player_num][1].SIZE-1], &cardtemp2);
	card cardtemp3;
	if(skillBuyDeck[player_num][2].SIZE >0)Card_Define(skillBuyDeck[player_num][2].array[skillBuyDeck[player_num][2].SIZE-1], &cardtemp3);
	
	
	if(skillBuyDeck[player_num][0].SIZE>0){
		printf("1.）攻擊技能鏈   升級費用 %hhd 點能量  卡片剩餘數:%hhd\n",cardtemp1.cost ,skillBuyDeck[player_num][0].SIZE);
		printf("目前的卡片：%s\n效果：%s\n\n",cardtemp1.cardname,cardtemp1.inf);
	}else{
		printf("1.）攻擊技能鏈  已售完\n\n");
	}
	
	if(skillBuyDeck[player_num][1].SIZE>0){
		printf("2.）防禦技能鏈   升級費用 %hhd 點能量  卡片剩餘數:%hhd\n",cardtemp2.cost ,skillBuyDeck[player_num][1].SIZE);
		printf("目前的卡片：%s\n效果：%s\n\n",cardtemp2.cardname,cardtemp2.inf);
	}else{
		printf("2.）防禦技能鏈  已售完\n\n");
	}
	
	if(skillBuyDeck[player_num][2].SIZE>0){
		
		printf("3.）移動技能鏈   升級費用 %hhd 點能量  卡片剩餘數:%hhd\n",cardtemp3.cost ,skillBuyDeck[player_num][2].SIZE);
		printf("目前的卡片：%s\n效果：%s\n\n",cardtemp3.cardname,cardtemp3.inf);
	}else{
		printf("3.）移動技能鏈 已售完\n\n");
	}
	return 0;
}

int8_t skill_shop_command(player *P){
	int8_t ssc =-1;

	while(1){
		// 將卡片資訊的讀取與商店介面的刷新都放到迴圈內
		// 這樣每次購買後都能顯示最新的狀態
		card cardtemp1, cardtemp2, cardtemp3;
		if(skillBuyDeck[P->num][0].SIZE > 0) Card_Define(skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1], &cardtemp1);
		if(skillBuyDeck[P->num][1].SIZE > 0) Card_Define(skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1], &cardtemp2);
		if(skillBuyDeck[P->num][2].SIZE > 0) Card_Define(skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1], &cardtemp3);

		printf_skill_shop(P->num);

		if(check_passive(P , 146) != 0){
				 regenerate_hp(P,5);
				 quicksort(P->passive,0,P->passive_n -1);
					for(int i = 0 ; i < P->passive_n ; i++){
						if(P->passive[i]==146){
							P->passive[i] = 999;
							P->passive_n--;
						}
					}
		}
		printf("目前剩餘能量："ANSI_BOLD ANSI_GREEN"%d"ANSI_RESET"\n", P->power);
		printf("請輸入你要做什麼？\n");
		printf("1. 升級技能\n");
		printf("2. 退出商店\n");
		printf("> ");

		if(P->bot == 1) {
			// === 機器人邏輯：決定要「升級」還是「退出」 ===
			int8_t num_valid_upgrades = 0;
			if (skillBuyDeck[P->num][0].SIZE > 0 && P->power >= cardtemp1.cost) num_valid_upgrades++;
			if (skillBuyDeck[P->num][1].SIZE > 0 && P->power >= cardtemp2.cost) num_valid_upgrades++;
			if (skillBuyDeck[P->num][2].SIZE > 0 && P->power >= cardtemp3.cost) num_valid_upgrades++;

			if (num_valid_upgrades > 0) {
				// 如果有東西可買，讓機器人隨機決定要不要買 (1=買, 2=不買/退出)
				// 這讓機器人有機會存錢，而不是無腦花光
				ssc = botChoice(0, 1, 2, 0); 
			} else {
				ssc = 2; // 如果沒有，就必須退出
			}
			printf("%hhd\n", ssc);
			usleep(1000000);
		} else {
			scanf("%hhd",&ssc);
			getchar();
		}

		if(ssc == 1){
			int8_t cc =-1;

			if(P->bot == 1){
				// === 機器人邏輯：從「有效選項」中決定要買哪一個 ===
				int8_t valid_options[3];
				int8_t num_valid_options = 0;

				// 建立可購買選項的陣列
				if (skillBuyDeck[P->num][0].SIZE > 0 && P->power >= cardtemp1.cost) {
					valid_options[num_valid_options++] = 1;
				}
				if (skillBuyDeck[P->num][1].SIZE > 0 && P->power >= cardtemp2.cost) {
					valid_options[num_valid_options++] = 2;
				}
				if (skillBuyDeck[P->num][2].SIZE > 0 && P->power >= cardtemp3.cost) {
					valid_options[num_valid_options++] = 3;
				}

				// 從有效選項陣列中隨機挑一個
				int random_index = botChoice(0, 0, num_valid_options - 1, 1);
				cc = valid_options[random_index];

				printf("請輸入你要升級的技能：%hhd\n", cc);
				usleep(1000000);
			} else {
				printf("請輸入你要升級的技能：") ;
				scanf("%hhd",&cc);
			}

			switch(cc){
				case 1: // 攻擊
					if(P->power < cardtemp1.cost){
						printf(ANSI_BOLD ANSI_RED"你的能量不夠\n"ANSI_RESET) ;
						wait_for_space();
					}else if(skillBuyDeck[P->num][0].SIZE == 0){
						printf(ANSI_BOLD ANSI_RED"此卡已經賣光了\n"ANSI_RESET) ;
						wait_for_space();
					}else{
						pushbackVector(&P->discard, skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1]);
						skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1] = 0;
						skillBuyDeck[P->num][0].SIZE--;
						P->power -=cardtemp1.cost;
						Card_Define(skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1], &cardtemp1);
						writeinRHU(P,4,0,0,0,0,cc,0,0);
						if(cardtemp1.cost == 0){
							P->passive[P->passive_n] = skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1];
							skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1] = 0;
							skillBuyDeck[P->num][0].SIZE--;
							if(skillBuyDeck[P->num][0].SIZE <=0) skillBuyDeck[P->num][0].SIZE = 0;
							P->passive_n++;
							if(skillBuyDeck[P->num][0].SIZE >0)Card_Define(skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1], &cardtemp1);
						}
						printf_skill_shop(P->num);
					}
					
				break;

				case 2: // 防禦
					if(P->power < cardtemp2.cost){
						printf(ANSI_BOLD ANSI_RED"你的能量不夠\n"ANSI_RESET) ;
						wait_for_space();
					}else if(skillBuyDeck[P->num][1].SIZE == 0){
						printf(ANSI_BOLD ANSI_RED"此卡已經賣光了\n"ANSI_RESET) ;
						wait_for_space();
					}else{
						pushbackVector(&P->discard, skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1]);
						skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1] = 0;
						skillBuyDeck[P->num][1].SIZE--;
						P->power -=cardtemp2.cost;
						Card_Define(skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1], &cardtemp2);
						if(cardtemp2.cost == 0){
							P->passive[P->passive_n] = skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1];
							skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1] = 0;
							skillBuyDeck[P->num][1].SIZE--;
							if(skillBuyDeck[P->num][1].SIZE <=0) skillBuyDeck[P->num][1].SIZE = 0;
							P->passive_n++;
							if(skillBuyDeck[P->num][1].SIZE >0)Card_Define(skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1], &cardtemp2);
						}
						printf_skill_shop(P->num);
					}
					writeinRHU(P,4,0,0,0,0,cc,0,0);
				break;

				case 3: // 移動
					if(P->power < cardtemp3.cost){
						printf(ANSI_BOLD ANSI_RED"你的能量不夠\n"ANSI_RESET) ;
						wait_for_space();
					}else if(skillBuyDeck[P->num][2].SIZE == 0){
						printf(ANSI_BOLD ANSI_RED"此卡已經賣光了\n"ANSI_RESET) ;
						wait_for_space();
					}else{
						pushbackVector(&P->discard, skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1]);
						skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1] = 0;
						skillBuyDeck[P->num][2].SIZE--;
						P->power -=cardtemp2.cost;
						Card_Define(skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][2].SIZE-1], &cardtemp2);
						if(cardtemp2.cost == 0){
							P->passive[P->passive_n] = skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1];
							skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1] = 0;
							skillBuyDeck[P->num][2].SIZE--;
							if(skillBuyDeck[P->num][2].SIZE <=0) skillBuyDeck[P->num][2].SIZE = 0;
							P->passive_n++;
							if(skillBuyDeck[P->num][2].SIZE >0)Card_Define(skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][1].SIZE-1], &cardtemp2);
						}
						printf_skill_shop(P->num);
					}
					writeinRHU(P,4,0,0,0,0,cc,0,0);
				break;

				default:
					printf(ANSI_BOLD ANSI_RED"不存在此選項\n"ANSI_RESET);
					wait_for_space();
				break;
			}
		} else if (ssc == 2){
			if(mode == 1){
				print_game_broad_9();
				return 0;
			}else{
				// other mode logic here
			}
			return 0;
		} else {
			printf(ANSI_BOLD ANSI_RED"不合法輸入！！\n"ANSI_RESET) ;
			wait_for_space();
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
			
			if(P->bot ==1 ){
				cc = botChoice(0,1,P->discard.SIZE,3);
			}else{
				scanf("%hhd",&cc);
			}
			
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
				print_game_broad_11();
				return 0;
			}
			
			return 0;
		}
	}
}

// 幫助函式：取得 bot 可購買的卡片列表，回傳數量
int get_affordable_card_choices(player *P, int* choices_out) {
    int count = 0;
    const int costs[10] = {1, 3, 6, 1, 3, 6, 1, 3, 6, 2};  // 各卡費用
    const int stock_row[10] = {0,0,0,1,1,1,2,2,2,3};
    const int stock_col[10] = {0,1,2,0,1,2,0,1,2,0};

    for (int i = 0; i < 10; i++) {
        int cost = costs[i];
        int row = stock_row[i], col = stock_col[i];
        if (P->power >= cost && basicBuyDeck[row][col].SIZE > 0) {
            choices_out[count++] = i + 1; // 卡片編號為 1~10
        }
    }
    return count;
}

int8_t basic_shop_command(player *P) {
    int8_t bsc = -1;
    printf_basic_shop();
    while (1) {
        printf("目前剩餘能量：" ANSI_BOLD ANSI_GREEN "%d" ANSI_RESET "\n", P->power);
        printf("請輸入你要做什麼？\n");
        printf("1. 購買卡片\n");
        printf("2. 退出商店\n");
        printf("> ");
        if (P->bot == 1) {
            bsc = botChoice(0, 1, 2, 4);
            printf("%d", bsc);
        } else {
            scanf("%hhd", &bsc);
            getchar();
        }

        if (bsc == 1) {
            int8_t cc = -1;
            printf("請輸入你要購買的卡片：");
            if (P->bot == 1) {
                int valid_cards[10];
                int num_choices = get_affordable_card_choices(P, valid_cards);
                if (num_choices == 0) {
                    printf(ANSI_BOLD ANSI_RED"（BOT）沒有可購買的卡\n"ANSI_RESET);
                    wait_for_space();
                    printf_basic_shop();
                    continue;
                }
                cc = valid_cards[rand() % num_choices];
            } else {
                scanf("%hhd", &cc);
            }

            if (cc >= 1 && cc <= 10) {
                writeinRHU(P, 3, 0, 0, 0, 0, 0, cc, 0);
            }

            const int costs[10] = {1, 3, 6, 1, 3, 6, 1, 3, 6, 2};
            const int row[10]   = {0,0,0,1,1,1,2,2,2,3};
            const int col[10]   = {0,1,2,0,1,2,0,1,2,0};

            if (cc >= 1 && cc <= 10) {
                int c = costs[cc - 1];
                int r = row[cc - 1];
                int cl = col[cc - 1];

                if (P->power < c) {
                    printf(ANSI_BOLD ANSI_RED"你的能量不夠\n" ANSI_RESET);
                } else if (basicBuyDeck[r][cl].SIZE == 0) {
                    printf(ANSI_BOLD ANSI_RED"此卡已經賣光了\n" ANSI_RESET);
                } else {
                    pushbackVector(&P->discard, basicBuyDeck[r][cl].array[basicBuyDeck[r][cl].SIZE - 1]);
                    basicBuyDeck[r][cl].array[basicBuyDeck[r][cl].SIZE - 1] = 0;
                    basicBuyDeck[r][cl].SIZE--;
                    P->power -= c;
                }

                wait_for_space();
                printf_basic_shop();
            } else {
                printf(ANSI_BOLD ANSI_RED"不存在此選項\n" ANSI_RESET);
                wait_for_space();
                printf_basic_shop();
            }
        } else if (bsc == 2) {
            if (mode == 1) {
                print_game_broad_9();
            } else {
                print_game_broad_11();
            }
            return 0;
        } else {
            printf(ANSI_BOLD ANSI_RED"不合法輸入！！\n" ANSI_RESET);
            wait_for_space();
            printf_basic_shop();
        }
    }
    return 1;
}



int8_t discard_card_from_hand(player *P,int8_t index){
	pushbackVector(&P->discard,(*P).hands_card[index].cardcode);
	for (int8_t i = index; i < (*P).hands - 1; i++) {
		Card_Define(0, &(*P).hands_card[i]);
		Card_Define((*P).hands_card[i + 1].cardcode , &(*P).hands_card[i]);
	}
	(*P).hands--;
	return 0;
}
	
int8_t remove_card(player *P){
	system("clear");
	int8_t comm=-1;
	printf("現在是"ANSI_GREEN ANSI_BOLD"%s"ANSI_RESET"在進行\n",P->charname);
	printf("請問你要對哪一個地方使用專注？\n");
	printf("0. 手牌\n");
	printf("1. 棄牌堆\n");
	printf("2. 返回\n");
	printf("> ");
	if(P->bot ==1 ){
		comm = botChoice(0,0,2,6);
	}else{
		scanf("%hhd",&comm);
	}
	switch(comm){
		case 0:
			while(1){
				print_hands(P);
				int8_t select=-1;
				if((*P).hands == 0){
					if(mode == 1){
						print_game_broad_9();
						
					}else{
						print_game_broad_11();
					}
					printf("你沒有手牌了！\n");
					
				}
				printf("請問你要移除哪一牌？\n");
				printf("輸入數字：");
				
				if(P->bot ==1 ){
				select = botChoice(0,0,P->hands,7);
			}else{
				scanf("%hhd",&select);
			}
				if(select == 0)break;
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
						print_game_broad_11();
					}
					printf("你的棄牌堆沒有牌！\n");
					
					return 0;
				}
				int8_t cc=-1;
				printf("請問你要移除哪一牌？\n");
				printf("輸入數字：");//TODO: wrong input
				if(P->bot ==1 ){
					cc = botChoice(0,1,P->discard.SIZE,8);
				}else{
					scanf("%hhd",&cc);
				}
				if(cc > P->discard.SIZE || cc <=0){
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
			print_game_broad_11();	
		}
		
		return 0;
		
		break;
		
	}
	return 0;
}




int8_t deal_damage(player *attacker, player *target, int8_t damage){
    int gap = damage - target->armor;

    // 檢查睡美人的被動技能 ID 144 (血祭之禮)，這裡要直接使用 target 變數
    if(gap > 0 && check_passive(target, 144) != 0 && target->sleep_passive2_cd == 0){
        target->sleep_passive2_cd = 1;
        recv_card_sleep(target, gap);
    }

    for(int i = 0; i < damage; i++){
        if(target->armor > 0){
            target->armor--;
        } else if(target->armor == 0){
            if(target->hp > 0){
                target->hp--;
                if(target->sleep == 1) gain_sleeptoken(target, 1);
                if(target->sleep_hp > 0) target->sleep_hp--;
            }
        }
    }

    // 檢查白雪公主的被動技能 ID 139 (水晶之棺)
    if (attacker != NULL && damage >= 2 && check_passive(attacker, 139) > 0) {
        printf("觸發了水晶之棺的效果！\n");
        add_poison_to_discard(attacker, target, 1);
    }

    return 0;
}

int8_t gain_armor(player *P , int8_t def){
	if(P->sleep != 0){
		P->armor += def;
		if(P->armor > P-> Maxarmor)	{
			def -= (P-> Maxarmor - P-> armor);
			P-> armor = P-> Maxarmor;
		}
	}
	return 0;
}

int8_t play_a_card(player *P){
	system("clear");
	if(mode == 1){
				print_game_broad_9();
						
				}else{		
				print_game_broad_11();
			
	}
	print_hands(P);
	// 尋找場上的火柴女孩玩家
	player* match_girl = NULL;
	for (int i=0; i<4; ++i) {
		if (Player[i].character == 7) {
			match_girl = &Player[i];
			break;
		}
	}
	printf("\n1.)攻擊牌\n2.)防禦牌\n3.)移動牌\n4.)技能牌\n5.)大招牌\n");
	printf("你要打哪一種張牌？（輸入0返回）\n>");
	while(1){
		int8_t select=-1;
		if((*P).hands == 0){
			if(mode == 1){
				print_game_broad_9();
						
				}else{	
				print_game_broad_11();
			}
			printf("你沒有手牌了！\n");
			
		}
		
		if(P->bot ==1 ){
				select = botChoice(0,0,5,9);
				}else{
					scanf("%hhd",&select);
		}
			if(select == 0){
				if(mode == 1){
					print_game_broad_9();
					return 0;
				}else{
					print_game_broad_11();
					return 0;
				}
				
				return 0;
			}else if(select == 1){
				int atk =0;
				int power_generate =0;
				if(range_counter(P,&Player[target(P)],1) == 1){
					printf("請選擇所有你想打出的攻擊牌，選擇完後請輸入0\n");
					
					
					int8_t cn = -1;
					while(cn!=0){
						if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0)printf("你可以獻祭2/4/6點生命來視作你打出一張 Lv1/Lv2/Lv3的進攻牌（不能因此獲得能量），輸入-2/-4/-6即可\n");
						if(P->bot ==1 ){
						
							if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0){
								cn = -4;
							}else{
								cn = botChoice(0,0,P->hands,10);
							}
							
							
							}else{
								scanf("%hhd",&cn);
						}
						if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0){
							if(cn == -2 && P->hp >2){
								P->hp-=2;
								atk += 1 + P->atk_buff;
								system("clear");
								if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
								print_hands(P);
								P->sleep_passive1_cd = 1;
								printf("請選擇所有你想打出的攻擊牌，選擇完後請輸入0\n");
								continue;
							}else if(cn == -4 && P->hp > 4){
								P->hp-=4;
								atk += 2 + P->atk_buff;
								system("clear");
								if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
								print_hands(P);
								P->sleep_passive1_cd = 1;
								printf("請選擇所有你想打出的攻擊牌，選擇完後請輸入0\n");
								continue;
							}else if(cn == -6 && P->hp > 6){
								P->hp-=6;
								atk += 3 + P->atk_buff;
								system("clear");
								if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
								print_hands(P);
								P->sleep_passive1_cd = 1;
								printf("請選擇所有你想打出的攻擊牌，選擇完後請輸入0\n");
								continue;
							}
						}
						if(cn == 0)break;
						if(P->hands_card[cn-1].type == 0 || P->hands_card[cn-1].type == 3){
							if (P->hands_card[cn-1].cardcode == MATCH_CARD_ID) {
								if (match_girl != NULL && check_passive(match_girl, 156) > 0) { // 火焰的捉弄
									printf("火柴牌不能作為攻擊牌使用！ %s 獲得 1 點能量。\n", match_girl->charname);
									match_girl->power++;
								} else {
									printf("你點燃了一根火柴，但什麼也沒發生...\n");
								}
								handaddplaycardnum(P, cn-1); // 消耗掉火柴牌
								continue; // 繼續選擇下一張牌
							}
							atk += P->hands_card[cn-1].value + P->atk_buff;
							power_generate += P->hands_card[cn-1].power_generate;
							
							handaddplaycardnum(P,cn-1);//handaddplaycardnum
							system("clear");
							if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
							print_hands(P);
							
							printf("請選擇所有你想打出的攻擊牌，選擇完後請輸入0\n");
							
						}else{
							printf("這不是攻擊牌請重新輸入\n>");
						}
						
					}
				P->power += power_generate;
				if(P->atk_bb1 !=0){
					atk +=1;
				}
				if(P->atk_bb2 !=0){
					atk +=2;
				}
				if(P->atk_bb3 !=0){
					atk +=3;
				}
				deal_damage(P, &Player[target(P)], atk);
				writeinRHU(P,0,1,atk,0,0,0,0,0);
				
				printf("你對對手造成了\033[1;31m%hhd\033[0m點傷害\n",atk);
				return 0;
					
			}else{
				printf("對手不在你的攻擊範圍！\n");
				return 0;
			}
			
		}else if(select == 2){
			int def =0;
			int power_generate =0;
			printf("請選擇所有你想打出的防禦牌，選擇完後請輸入0\n>");
			int8_t cn = -1;
			while(cn!=0){
				if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0)printf("你可以獻祭2/4/6點生命來視作你打出一張 Lv1/Lv2/Lv3的防禦牌（不能因此獲得能量），輸入-2/-4/-6即可\n");
						if(P->bot ==1 ){
						
							if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0){
								cn = -4;
							}else{
								cn = botChoice(0,0,P->hands,11);
							}
							
							
							}else{
								scanf("%hhd",&cn);
						}
						if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0){
							if(cn == -2 && P->hp >2){
								P->hp-=2;
								def += 1 + P->defend_buff;
								system("clear");
								if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
								print_hands(P);
								P->sleep_passive1_cd = 1;
								printf("請選擇所有你想打出的防禦牌，選擇完後請輸入0\n");
								continue;
							}else if(cn == -4 && P->hp > 4){
								P->hp-=4;
								def += 2 + P->defend_buff;
								system("clear");
								if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
								print_hands(P);
								P->sleep_passive1_cd = 1;
								printf("請選擇所有你想打出的防禦牌，選擇完後請輸入0\n");
								continue;
							}else if(cn == -6 && P->hp > 6){
								P->hp-=6;
								def += 3 + P->defend_buff;
								system("clear");
								if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
								print_hands(P);
								P->sleep_passive1_cd = 1;
								printf("請選擇所有你想打出的防禦牌，選擇完後請輸入0\n");
								continue;
							}
						}
				if(cn == 0)break;
				if(P->hands_card[cn-1].type == 1 || P->hands_card[cn-1].type == 3){
					
					def += P->hands_card[cn-1].value + P->defend_buff;
					power_generate += P->hands_card[cn-1].power_generate;						
					handaddplaycardnum(P,cn-1);
					system("clear");
					if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
					print_hands(P);
					printf("請選擇所有你想打出的防禦牌，選擇完後請輸入0\n>");
					
				}else{
						printf("這不是防禦牌請重新輸入\n>");
					}
				
			}	
			if(P->sleep != 0) gain_armor(P , def);
			P->power += power_generate;
			writeinRHU(P,0,0,0,def,0,0,0,0);
			
			
			
			printf("你獲得了\033[1;31m%hhd\033[0m個盾\n",def);
			return 0;
			
		}else if(select == 3){
			int move =0;
			int save = move;
			int power_generate =0;
			printf("請選擇所有你想打出的移動牌，選擇完後請輸入0\n>");
			int8_t cn = -1;
			while(cn!=0){
				if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0)printf("你可以獻祭2/4/6點生命來視作你打出一張 Lv1/Lv2/Lv3的移動牌（不能因此獲得能量），輸入-2/-4/-6即可\n");
						if(P->bot ==1 ){
						
							if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0){
								cn = -4;
							}else{
								cn = botChoice(0,0,P->hands,12);
							}
							
							
							}else{
								scanf("%hhd",&cn);
						}
						if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0){
							if(cn == -2 && P->hp >2){
								P->hp-=2;
								move += 1 + P->speed_buff;
								system("clear");
								if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
								print_hands(P);
								P->sleep_passive1_cd = 1;
								printf("請選擇所有你想打出的移動牌，選擇完後請輸入0\n");
								continue;
							}else if(cn == -4 && P->hp > 4){
								P->hp-=4;
								move += 2 + P->speed_buff;
								system("clear");
								if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
								print_hands(P);
								P->sleep_passive1_cd = 1;
								printf("請選擇所有你想打出的移動牌，選擇完後請輸入0\n");
								continue;
							}else if(cn == -6 && P->hp > 6){
								P->hp-=6;
								move += 3 + P->speed_buff;
								system("clear");
								if(mode == 1){
									print_game_broad_9();	
								}else{		
									print_game_broad_11();
								}
								print_hands(P);
								P->sleep_passive1_cd = 1;
								printf("請選擇所有你想打出的移動牌，選擇完後請輸入0\n");
								continue;
							}
						}
				if(cn == 0)break;
				if(P->hands_card[cn-1].type == 2 || P->hands_card[cn-1].type == 3){
					move += P->hands_card[cn-1].value + P->speed_buff;
					power_generate += P->hands_card[cn-1].power_generate;						
					handaddplaycardnum(P,cn-1);
					system("clear");
					if(mode == 1){
						print_game_broad_9();	
					}else{		
						print_game_broad_11();
					}
					print_hands(P);
					printf("請選擇所有你想打出的移動牌，選擇完後請輸入0\n>");
					
				}else{
						printf("這不是移動牌請重新輸入\n>");
						
					}
				
			}	
			
			if(check_passive(P, 153) > 0 && P->qi > 0) {
				int8_t spend_qi = 0;
				int max_spend = (P->qi > 3) ? 3 : P->qi;
				printf("你擁有'長驅直入'，可以花費X點氣額外移動X格 (X至多為3)。\n");
				printf("你目前有 %d 氣。要花費多少氣？ (0-%d)\n> ", P->qi, max_spend);
				
				if(P->bot == 1) {
					spend_qi = botChoice(0, 0, max_spend, 0);
				} else {
					scanf("%hhd", &spend_qi);
					getchar();
				}

				if (spend_qi > 0 && spend_qi <= max_spend) {
					move += spend_qi;
					P->qi -= spend_qi;
					printf("你花費了 %d 氣，額外移動 %d 格。\n", spend_qi, spend_qi);
				}
			}
			int8_t way = 0;
			printf("你要向左還是向右？1.)向左 2.)向右 ：");
			
			if(P->bot ==1 ){
								way = botChoice(0,1,2,13);
			}else{
								scanf("%hhd",&way);
			}
			while(move !=0){
							
						if(way == 1){ //左
							writeinRHU(P,0,1,0,0,move*(-1),0,0,0);
							if(P->coordinate -1 != 0){
								if(P->coordinate -1 == Player[target(P)].coordinate && P->coordinate - 2 != 0 && move >= 2 ){
										P->coordinate-=2 ;
										move -=2 ;
								}else{										
								if(P->coordinate -1 !=Player[target(P)].coordinate)P->coordinate-- ;
										move --;
								}
							}
							
						}else{
							writeinRHU(P,0,0,0,0,move,0,0,0);
							if(P->coordinate +1 != Right_MAX){
								if(P->coordinate +1 == Player[target(P)].coordinate && P->coordinate + 2 != Right_MAX && move >= 2 ){
										P->coordinate+=2 ;
										move -=2 ;
								}else{
										if(P->coordinate +1 !=Player[target(P)].coordinate)P->coordinate++ ;
										move --;
								}
							}
						}							
			}
			P->power += power_generate ;
			return 0;
			
		}else if(select == 4){
			
			
			system("clear");
			if(mode == 1){
				print_game_broad_9();	
			}else{		
				print_game_broad_11();
			}
			print_hands(P);
			
			int8_t combo_card =-1;
			int8_t damage_deal=0;
			int8_t armor_get=0;
			int8_t levels = -1;
			int8_t cn = -1;
			int8_t atk = 0;
			int8_t sleepbasic=-1;
			int8_t lv=-1;
			while(cn!=0){
				printf("請問你要打哪一張技能牌？(輸入0返回)\n");
				printf(">");
				if(P->bot ==1 ){
								cn = botChoice(0,0,P->hands,14);
								
				}else{
									scanf("%hhd",&cn);
				}
				if(cn == 0)return 0;
				if(P->hands_card[cn-1].type == 4){
					if(P->hands_card[cn-1].require_basic_card == 0){
					printf("你要搭配哪一張基礎攻擊卡？\n>");
				}else if(P->hands_card[cn-1].require_basic_card == 1){
					printf("你要搭配哪一張基礎防禦卡？\n>");
				}else if(P->hands_card[cn-1].require_basic_card == 2){
					printf("你要搭配哪一張基礎移動卡？\n>");
				}
				if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0)printf("你可以獻祭2/4/6點生命來視作你打出一張 Lv1/Lv2/Lv3的基礎牌（不能因此獲得能量），輸入-2/-4/-6即可\n");
						
						
				while(1){
					
					if(P->bot ==1 ){
									
									for(int i = 0 ; i <= P->hands -1 ; i++){
										card tempc;
										Card_Define(P->hands_card[i].cardcode , &(tempc));
										if(tempc.type == P->hands_card[cn-1].require_basic_card ){
											combo_card = i+1;
											
											break;
										}
									}
					}else{
										scanf("%hhd",&combo_card);
										getchar();
					}
					if(combo_card>=1 && combo_card <=P->hands) break;
					if(check_passive(P , 143) != 0 && P->sleep_passive1_cd == 0){
							if(cn == -2 && P->hp >2){
								P->hp-=2;
								
								if(P->hands_card[cn-1].require_basic_card == 0){
									sleepbasic =1;
									lv=1;
								}else if(P->hands_card[cn-1].require_basic_card == 1){
									sleepbasic =4;
									lv=1;
								}else if(P->hands_card[cn-1].require_basic_card == 2){
									sleepbasic =7;
									lv=1;
								}
								P->sleep_passive1_cd = 1;
								break;
							}else if(cn == -4 && P->hp > 4){
								P->hp-=4;
								if(P->hands_card[cn-1].require_basic_card == 0){
									sleepbasic =2;
										lv=2;
								}else if(P->hands_card[cn-1].require_basic_card == 1){
									sleepbasic =5;
									lv=2;
								}else if(P->hands_card[cn-1].require_basic_card == 2){
									sleepbasic =8;
									lv=2;
								}
								
								P->sleep_passive1_cd = 1;
								break;
							}else if(cn == -6 && P->hp > 6){
								P->hp-=6;
								if(P->hands_card[cn-1].require_basic_card == 0){
									sleepbasic =3;
									lv=3;
								}else if(P->hands_card[cn-1].require_basic_card == 1){
									sleepbasic =6;
									lv=3;
								}else if(P->hands_card[cn-1].require_basic_card == 2){
									sleepbasic =9;
								  lv=3;
								}
								
								P->sleep_passive1_cd = 1;
								break;
							}
						}
					
					
				}
				if(P->hands_card[combo_card-1].type == P->hands_card[cn-1].require_basic_card && sleepbasic ==-1){
				int rr=0;
					if(check_passive(P , 137) != 0){
								while(1){
									int choices_R=0;
									printf("使用移動/攻擊技能時，可捨棄1張技能牌獲得射程+X（X為等級）\n");
									printf("0)不捨棄 1)捨棄\n>");
									
									if(P->bot ==1 ){
													choices_R = botChoice(0,0,1,15);
													
									}else{
														scanf("%d",&choices_R);
														getchar();
									}
							
									if(choices_R!= 0 && choices_R!= 1){
										printf("輸入錯誤！\n");
									}else if(choices_R == 0){
										break;
									}else if(choices_R == 1){
										int8_t cn = -1;
										while(cn!=0){
											printf("請選擇一張你要捨棄的牌，輸入0取消\n>");
											if(P->bot ==1 ){
						
													cn = botChoice(0,0,P->hands,16);
												
											}else{
													scanf("%hhd",&cn);
											}
											
											if(cn == 0)break;
											if(P->hands_card[cn-1].type == 4){
												rr += P->hands_card[cn-1].level;
												discard_card_from_hand(P,cn-1);
												break;
											}else{
												printf("這不是技能牌請重新輸入\n>");
											}
											
										}
										break;
									}
									
								}
								
					}
				
					if(range_counter(P,&Player[target(P)],P->hands_card[cn-1].range-rr) == 1 || P->hands_card[cn-1].range == 0){
						use_skill(P,&Player[target(P)], P->hands_card[cn-1].cardcode , &damage_deal , &armor_get , P->hands_card[combo_card-1].level , P->hands_card[combo_card-1].cardcode , mode ,BotOn );
						// 檢查蛻變1 氣慣全身 (ID: 151)
						card skill_card_temp;
						Card_Define(P->hands_card[cn-1].cardcode, &skill_card_temp);
						// 判斷是否為攻擊型技能
						if(skill_card_temp.damage > 0 && check_passive(P, 151) > 0 && P->qi > 0) {
							int8_t spend_qi = 0;
							int max_spend = (P->qi > 3) ? 3 : P->qi;
							printf("你擁有'氣慣全身'，可以花費X點氣來獲得傷害+X (X至多為3)。\n");
							printf("你目前有 %d 氣。要花費多少氣？ (0-%d)\n> ", P->qi, max_spend);

							if(P->bot == 1) {
								spend_qi = botChoice(0, 0, max_spend, 0);
							} else {
								scanf("%hhd", &spend_qi);
								getchar();
							}

							if (spend_qi > 0 && spend_qi <= max_spend) {
								damage_deal += spend_qi;
								P->qi -= spend_qi;
								printf("你花費了 %d 氣，獲得 %d 點額外傷害。\n", spend_qi, spend_qi);
							}
						}
						if(P->hands_card[combo_card-1].require_basic_card == 0 || P->hands_card[combo_card-1].require_basic_card == 2){
							if(check_passive(P , 135) != 0){
								while(1){
									int choices_R=0;
									printf("可以捨棄至多一張技能牌來獲得傷害X，X為你捨棄的技能牌等級\n");
									printf("0)不捨棄 1)捨棄\n>");
									if(P->bot ==1 ){
													choices_R = botChoice(0,0,1,17);
													
									}else{
														scanf("%d",&choices_R);
														getchar();
									}
									
									if(choices_R!= 0 && choices_R!= 1){
										printf("輸入錯誤！\n");
									}else if(choices_R == 0){
										break;
									}else if(choices_R == 1){
										int8_t cn = -1;
										while(cn!=0){
											printf("請選擇一張你要捨棄的牌，輸入0取消\n>");
											
											if(P->bot ==1 ){
															cn = botChoice(0,0,P->hands,18);
															
											}else{
																scanf("%hhd",&cn);
											}
											if(cn == 0)break;
											if(P->hands_card[cn-1].type == 4){
												atk += P->hands_card[cn-1].level;
												discard_card_from_hand(P,cn-1);
												break;
											}else{
												printf("這不是技能牌請重新輸入\n>");
											}
											
										}
										break;
									}
									
								}
								
							}
						}
						
						deal_damage(P, &Player[target(P)], damage_deal+atk+ P->atk_buff);
						
						if(P->sleep != 0) gain_armor(P , armor_get+ P->defend_buff);
						writeinRHU(P,1,0,damage_deal+atk+ P->atk_buff,armor_get+ P->defend_buff,0,P->hands_card[combo_card-1].level,P->hands_card[combo_card-1].cardcode,P->hands_card[cn-1].cardcode);
						if(check_passive(&Player[target(P)],145) !=0 && P->hands_card[cn-1].require_basic_card ==2 ){
							gain_armor(P , P->hands_card[cn-1].level);
							
						}
						
						if(P->hands_card[cn-1].remain ==1){
							if(cn-1 > combo_card -1){
							
								Card_Define(0 , &(*P).hands_card[cn-1]);
								for (int8_t i = cn-1; i < (*P).hands - 1; i++) {
									Card_Define(0, &(*P).hands_card[i]);
									Card_Define((*P).hands_card[i + 1].cardcode , &(*P).hands_card[i]);
								}
								(*P).hands--;
								
								Card_Define(0 , &(*P).hands_card[combo_card-1]);
								for (int8_t i = combo_card-1; i < (*P).hands - 1; i++) {
									Card_Define(0, &(*P).hands_card[i]);
									Card_Define((*P).hands_card[i + 1].cardcode , &(*P).hands_card[i]);
								}
								(*P).hands--;
								
							}else{
								Card_Define(0 , &(*P).hands_card[cn-1]);
								for (int8_t i = cn-1; i < (*P).hands - 1; i++) {
									Card_Define(0, &(*P).hands_card[i]);
									Card_Define((*P).hands_card[i + 1].cardcode , &(*P).hands_card[i]);
								}
								(*P).hands--;
								
								Card_Define(0 , &(*P).hands_card[combo_card]);
								for (int8_t i = combo_card; i < (*P).hands - 1; i++) {
									Card_Define(0, &(*P).hands_card[i]);
									Card_Define((*P).hands_card[i + 1].cardcode , &(*P).hands_card[i]);
								}
								(*P).hands--;
							}
						}else{
							if(cn-1 > combo_card -1){
								handaddplaycardnum(P,cn-1); // 4 5
								handaddplaycardnum(P,combo_card-1);// 4
							}else{
								handaddplaycardnum(P,cn-1); // 4 5
								handaddplaycardnum(P,combo_card);
							}
						}
						return 0;
						
					}else{
						printf("對手不在你的攻擊範圍！\n");
						
					}
							
				}else if(sleepbasic >=1 && sleepbasic <=9){
					int rr=0;
					if(range_counter(P,&Player[target(P)],P->hands_card[cn-1].range-rr) == 1 || P->hands_card[cn-1].range == 0){
						use_skill(P,&Player[target(P)], P->hands_card[cn-1].cardcode , &damage_deal , &armor_get , lv , sleepbasic  , mode ,BotOn);
						
						deal_damage(P, &Player[target(P)], damage_deal+atk+ P->atk_buff);
						
						if(P->sleep != 0) gain_armor(P , armor_get+ P->defend_buff);
						
						if(check_passive(&Player[target(P)],145) !=0 && P->hands_card[cn-1].require_basic_card ==3 ){
							gain_armor(P , P->hands_card[cn-1].level);
							
						}
						
						if(P->hands_card[cn-1].remain ==1){
								Card_Define(0 , &(*P).hands_card[cn-1]);
								for (int8_t i = cn-1; i < (*P).hands - 1; i++) {
									Card_Define(0, &(*P).hands_card[i]);
									Card_Define((*P).hands_card[i + 1].cardcode , &(*P).hands_card[i]);
								}
								(*P).hands--;
								
								
							
						}else{
							
								handaddplaycardnum(P,cn-1); // 4 5
							
						}
						return 0;
						
					}else{
						printf("對手不在你的攻擊範圍！\n");
						
					}
				}else{
					printf("你所選擇的卡片並不能搭配這張卡！\n");
					
					
				}
				//TODO:逃樂思	
			}else{
				printf("這不是技能牌請重新輸入\n>");
			}
		}
						
					
					
		}else if(select == 5){
			system("clear");
			if(mode == 1){
				print_game_broad_9();	
			}else{		
				print_game_broad_11();
			}
			print_hands(P);
			
			int8_t combo_card =-1;
			int8_t damage_deal=0;
			int8_t armor_get=0;
			int8_t levels = -1;
			int8_t cn = -1;
			
			while(cn!=0){
				printf("請問你要打哪一張大招牌？(輸入0返回)\n");
				printf(">");
				if(P->bot ==1 ){
								for(int i = 0 ; i < P->hands-1 ; i++){
									if(P->hands_card[i].type == 5){
										cn = i+1;
										break;
									}else{
										cn = 0;
									}
								}
								
				}else{
									scanf("%hhd",&cn);
				}
				if(cn == 0)return 0;
				
				
				
				if(P->hands_card[cn-1].type == 5){
					if(P->hands_card[cn-1].cardcode == 21){
						P->hands_card[cn-1].range = P->RedUlt.range;
					}
					if(range_counter(P,&Player[target(P)],P->hands_card[cn-1].range) == 1 || P->hands_card[cn-1].range == 0){
						use_Ult(P,&Player[target(P)],P->hands_card[cn-1].cardcode , &damage_deal , &armor_get, mode , skillBuyDeck , basicBuyDeck,BotOn);
						deal_damage(P, &Player[target(P)], damage_deal);
						gain_armor(P , armor_get);
						
						handaddplaycardnum(P,cn-1);
						
						
						return 0;
						
					}else{
						printf("對手不在你的攻擊範圍！\n");
						
					}
							
				
				
			}else{
				printf("這不是技能牌請重新輸入\n>");
			}
		}
		}	
					
					
		}
	return 0;
}





int8_t action_command(player *P){
	int32_t comm=-1;
	if(end_game_detection() == 1){
		P->end_turn = 1;
		return -1;
	}
	printf("現在是"ANSI_GREEN ANSI_BOLD"%s"ANSI_RESET"的回合，現在是你的執行階段請從以下的動作中選一個執行\n",(*P).charname);
	if(mode == 2) printf("0. 與隊友換位置\n");
	printf("1. 購買基礎牌\n");
	printf("2. 購買技能牌\n");
	printf("3. 打牌\n");
	printf("4. 查看自己的棄牌堆\n");
	printf("5. 查看別人的棄牌堆\n");
	printf("6. 結束回合\n");
	if(check_passive(P,138) !=0 ) printf("7. 放入拿出板載緩存\n\n");
	printf("你的手牌：\n");
	print_hands(P);
	printf("輸入指令：");
	if(P->bot == 1){
								
		do {
			comm = botChoice(0, 1, 6, 19);
		} while (comm == 4 || comm == 5);

	}else{
										
		scanf("%d",&comm);
		getchar();
	}
	
	switch(comm){
				case 0:  // 購買基礎牌
							if(P->num ==1 || P->num ==3){
							swap_place(&Player[1],&Player[3]);
							}else if(P->num ==0 || P->num ==2){
								swap_place(&Player[0],&Player[2]);
							}
							return 0;
			
            	break;
						
            	case 1:  // 購買基礎牌
							basic_shop_command(P);
							return 0;
			
            	break;
            	
            	case 2:  // 購買技能牌
							skill_shop_command(P); 
							return 0;
			
            	break;
            	
            	case 3:  // 打牌
				play_a_card(P);
				if(RedHoodHPtemp != Player[target(P)].hp && check_passive(&Player[target(P)],136) !=0){
					
					while(1){
									int choices_R=0;
									printf(ANSI_GREEN ANSI_BOLD"%s"ANSI_RESET"你可以捨棄至多一張技能牌來將傷害減少X，X為你捨棄的技能牌等級\n",Player[target(P)].charname);
									printf("0)不捨棄 1)捨棄\n>");
									
									if(P->bot ==1 ){
										
											choices_R = botChoice(0,0,1,21);
										
										
									}else{
											scanf("%d",&choices_R);
											getchar();
									}
									
									if(choices_R!= 0 && choices_R!= 1){
										printf("輸入錯誤！\n");
									}else if(choices_R == 0){
										break;
									}else if(choices_R == 1){
										
										int8_t cn = -1;
										while(cn!=0){
											printf("請選擇一張你要捨棄的牌(輸入0取消)\n");
											print_hands(&Player[target(P)]);
											printf(">");
												
												if(P->bot ==1 ){
																cn = botChoice(0,0,P->hands,22);
																
												}else{
																	scanf("%hhd",&cn);
												}
											if(cn == 0)break;
											if(Player[target(P)].hands_card[cn-1].type == 4){
												Player[target(P)].hp += Player[target(P)].hands_card[cn-1].level;
												discard_card_from_hand(&Player[target(P)],cn-1);
												break;
											}else{
												printf("這不是技能牌請重新輸入\n>");
											}
											
										}
										
										RedHoodHPtemp = Player[target(P)].hp;
										break;
									}
							else if (MulanHPtemp != Player[target(P)].hp && Player[target(P)].character == 4) {
								player* mulan = &Player[target(P)];
								printf(ANSI_GREEN ANSI_BOLD"%s"ANSI_RESET" 你可以棄掉至多一張防禦牌或通用牌來減少傷害並獲得氣。\n", mulan->charname);
								printf("0) 不棄牌 1) 棄牌\n> ");
								
								int8_t choice = 0;
								if(mulan->bot == 1) {
									choice = botChoice(0, 0, 1, 0);
								} else {
									scanf("%hhd", &choice);
									getchar();
								}

								if (choice == 1) {
									printf("請選擇你要棄掉的防禦或通用牌 (輸入數字，0取消):\n");
									print_hands(mulan);
									printf("> ");
									
									int8_t card_idx = 0;
									if(mulan->bot == 1) {
										// Bot 邏輯：找到第一張可用的牌
										for(int i = 0; i < mulan->hands; ++i) {
											if(mulan->hands_card[i].type == 1 || mulan->hands_card[i].type == 3) {
												card_idx = i + 1;
												break;
											}
										}
									} else {
										scanf("%hhd", &card_idx);
										getchar();
									}

									if (card_idx > 0 && card_idx <= mulan->hands && 
									(mulan->hands_card[card_idx-1].type == 1 || mulan->hands_card[card_idx-1].type == 3)) {
										
										int8_t level = mulan->hands_card[card_idx-1].level;
										int8_t actual_damage_taken = MulanHPtemp - mulan->hp;
										int8_t reduction = (level > actual_damage_taken) ? actual_damage_taken : level;

										mulan->hp += reduction; // 恢復生命 (等同於減傷)
										mulan->qi += level;
										if (mulan->qi > 12) mulan->qi = 12;

										printf("%s 棄掉了 %s，減少了 %d 點傷害，獲得了 %d 點氣！\n", mulan->charname, mulan->hands_card[card_idx-1].cardname, reduction, level);
										discard_card_from_hand(mulan, card_idx - 1);
									}
								}
								MulanHPtemp = Player[target(P)].hp; // 更新血量紀錄
							}
						}
				}
				return 0;
            	break;
            	
            	case 4:  // 查看自己的棄牌
            		
								discard_command(P);
								return 0;
			
		
            	break;
            	
            	case 5:  // 查看別人的棄牌堆
				        		if(mode ==1){// 新增不同回合要換人
											discard_command(&Player[target(P)]);
											return 0; 
										}
					
		
            	break;
            	
            	case 6:  // 結束遊戲階段
            	P->end_turn = 1;
							return 0;
						 
							case 7:
							if(check_passive(P,138) !=0 ){
								Redhoodsavefile(P,BotOn);
								writeinRHU(P,2,0,0,0,0,0,0,0);
							}
							return 0;
				
            	break;
            	
            	case 20060314:
            		P->power = 100;
            		
            	break;
            	
            	case 1111111:
            		P->hp = 10;
            		
            	break;
            	
            	default:
            	
            	break;
	}
	
	return 0;
}





void print_extra_inf(player *P){
	if(P-> passive_n){
		printf("已啟動蛻變牌： \n");
		quicksort(P->passive,0,P->passive_n-1);
		for(int i = 0 ; i < P->passive_n ; i++){
			if(P->passive[i] && P->passive[i]){
				card cardtemp1;
				Card_Define(P->passive[i], &cardtemp1);
				printf("%d)%s %s \n",i+1,cardtemp1.cardname,cardtemp1.inf);
			}
		}
	}
	if(check_passive(P,138) >=1 ){
		card cardtemp1;
		Card_Define(P->Redhoodsave[0], &cardtemp1);
		if(P->Redhoodsave[0] != 0){
			printf("板載緩存1： %s\n",cardtemp1.cardname);
		}else{
			printf("板載緩存1： 空\n");
		}
	}
	if(check_passive(P,138) >=2 ){
		card cardtemp1;
		Card_Define(P->Redhoodsave[1], &cardtemp1);
		if(P->Redhoodsave[1] != 0){
			printf("板載緩存2： %s\n",cardtemp1.cardname);
		}else{
			printf("板載緩存2： 空\n");
		}
	}
	if(check_passive(P,138) >=3 ){
		card cardtemp1;
		Card_Define(P->Redhoodsave[2], &cardtemp1);
		if(P->Redhoodsave[2] != 0){
			printf("板載緩存3： %s\n",cardtemp1.cardname);
		}else{
			printf("板載緩存3： 空\n");
		}
	}
	if((*P).poison != -1){
		printf("中毒牌組：%hhd\n",(*P).poison);
	}
	if((*P).matches!= -1){
		printf("火柴牌組：%hhd\n",(*P).matches);
	}
	if((*P).sleep_token != -1){
		printf("覺醒TOKEN⬖ ：%hhd\n",(*P).sleep_token);
	}
	if((*P).sleep != -1){
		if((*P).sleep == 1){ //沉睡
			printf("睡美人目前是\033[1;32m沉睡狀態\033[0m，他的白馬王子在哪？\n");
		}else{ //覺醒
			printf("睡美人目前是\033[1;32m覺醒狀態\033[0m，她不需要白馬王子！\n");
		}
	}
	if((*P).alice != -1){ //愛麗絲 狀態 -1代表不是愛麗絲
		if((*P).alice == 0){ 
			printf("愛麗絲目前是\033[1;31m紅心皇后\033[0m，注意你的人頭！\n");
		}else if((*P).alice == 1){ 
			printf("愛麗絲目前是\033[1;34m瘋帽子\033[0m，請不要跟她說話！\n");
		}else{ 
			printf("愛麗絲目前是\033[1;35m柴郡貓\033[0m，你追不上她的速度！\n");
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
	if((*P).matches != -1){ //火柴女孩
		printf("火柴牌庫剩餘：%hhd\n",(*P).matches);
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
	
	if(end_game_detection() == 1) return ;
	int8_t len = 0;
	if(utf8_strlen(Player[0].charname) == 3 && utf8_strlen(Player[1].charname) == 3) len = 6;
	else len = 8;
	system("clear");
	//printf("%d %d",BotOn,Player[1].num);
	printf("玩家一 │ 遊玩角色：");
	print_aligned_charname(Player[0].charname, len);
	
	printf(" 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n", Player[0].hp, Player[0].armor, Player[0].power, Player[0].hands, Player[0].Maxhp, Player[0].Maxarmor, Player[0].Ult_threshold);
	printf("出牌區：");
	for(int i = 0 ; i < Player[0].playcardnum ; i++){
			if(Player[0].playcardnum){
				card cardtemp1;
				Card_Define(Player[0].playcard[i], &cardtemp1);
				printf("%d.%s ",i+1,cardtemp1.cardname);
			}
		}
	printf("\n");
	printf("持續牌區：");
	for(int i = 0 ; i < Player[0].starting_size ; i++){
			if(Player[0].starting_size){
				card cardtemp1;
				Card_Define(Player[0].starting[i], &cardtemp1);
				card cardtemp2;
				Card_Define(Player[0].combo_basic[i], &cardtemp2);
				printf("%d.%s -%s  ",i+1,cardtemp1.cardname, cardtemp2.cardname);
			}
		}
	printf("\n");
	print_extra_inf(&Player[0]);

	printf("玩家二 │ 遊玩角色：");
	print_aligned_charname(Player[1].charname, len);
	printf(" 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n", Player[1].hp, Player[1].armor, Player[1].power, Player[1].hands, Player[1].Maxhp, Player[1].Maxarmor, Player[1].Ult_threshold);
	printf("出牌區：");
	for(int i = 0 ; i < Player[1].playcardnum ; i++){
			if(Player[1].playcardnum){
				card cardtemp1;
				Card_Define(Player[1].playcard[i], &cardtemp1);
				printf("%d.%s ",i+1,cardtemp1.cardname);
			}
		}
	printf("\n");
	printf("持續牌區：");
	for(int i = 0 ; i < Player[1].starting_size ; i++){
			if(Player[1].starting_size){
				card cardtemp1;
				Card_Define(Player[1].starting[i], &cardtemp1);
				card cardtemp2;
				Card_Define(Player[1].combo_basic[i], &cardtemp2);
				printf("%d.%s -%s  ",i+1,cardtemp1.cardname, cardtemp2.cardname);
			}
		}
	printf("\n");
	print_extra_inf(&Player[1]);
	

	printf("          ┌───────────────────┐           \n");
	
	printf("     Board│ ");
	for(int i = 1 ; i <= 9 ; i++){
		if(Player[0].coordinate == i){
			printf("1 ");
		}else if(Player[1].coordinate == i){
			printf("2 ");
		}else{
			printf("_ ");
		}	
	}
	printf("│版面                   \n");
	printf("          ├───────────────────┤           \n");
	printf("Coordinate│ 1 2 3 4 5 6 7 8 9 │座標                   \n");
	printf("          └───────────────────┘           \n");

	update_coordinates(Player[0].coordinate, Player[1].coordinate);
	
	return ;
}
void print_game_broad_11(){
	if(end_game_detection() == 1) return ;
	int8_t len = 0;
	if(utf8_strlen(Player[0].charname) == 3 && utf8_strlen(Player[1].charname) == 3) len = 6;
	else len = 8;
	system("clear");
	//printf("%d %d",BotOn,Player[1].num);
	printf("玩家一 │ 遊玩角色：");
	print_aligned_charname(Player[0].charname, len);
	printf(" 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n", Player[0].hp, Player[0].armor, Player[0].power, Player[0].hands, Player[0].Maxhp, Player[0].Maxarmor, Player[0].Ult_threshold);
	printf("出牌區：");
	for(int i = 0 ; i < Player[0].playcardnum ; i++){
			if(Player[0].playcardnum){
				card cardtemp1;
				Card_Define(Player[0].playcard[i], &cardtemp1);
				printf("%d.%s ",i+1,cardtemp1.cardname);
			}
		}
	printf("\n");
	printf("持續牌區：");
	for(int i = 0 ; i < Player[0].starting_size ; i++){
			if(Player[0].starting_size){
				card cardtemp1;
				Card_Define(Player[0].starting[i], &cardtemp1);
				card cardtemp2;
				Card_Define(Player[0].combo_basic[i], &cardtemp2);
				printf("%d.%s -%s  ",i+1,cardtemp1.cardname, cardtemp2.cardname);
			}
		}
	printf("\n");
	print_extra_inf(&Player[0]);

	printf("玩家二 │ 遊玩角色：");
	print_aligned_charname(Player[1].charname, len);
	printf(" 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n", Player[1].hp, Player[1].armor, Player[1].power, Player[1].hands, Player[1].Maxhp, Player[1].Maxarmor, Player[1].Ult_threshold);
	printf("出牌區：");
	for(int i = 0 ; i < Player[1].playcardnum ; i++){
			if(Player[1].playcardnum){
				card cardtemp1;
				Card_Define(Player[1].playcard[i], &cardtemp1);
				printf("%d.%s ",i+1,cardtemp1.cardname);
			}
		}
	printf("\n");
	printf("持續牌區：");
	for(int i = 0 ; i < Player[1].starting_size ; i++){
			if(Player[1].starting_size){
				card cardtemp1;
				Card_Define(Player[1].starting[i], &cardtemp1);
				card cardtemp2;
				Card_Define(Player[1].combo_basic[i], &cardtemp2);
				printf("%d.%s -%s  ",i+1,cardtemp1.cardname, cardtemp2.cardname);
			}
		}
	printf("\n");
	print_extra_inf(&Player[1]);
	
	printf("玩家三 │ 遊玩角色：");
	print_aligned_charname(Player[2].charname, len);
	printf(" 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n", Player[2].hp, Player[2].armor, Player[2].power, Player[2].hands, Player[2].Maxhp, Player[2].Maxarmor, Player[2].Ult_threshold);
	printf("出牌區：");
	for(int i = 0 ; i < Player[2].playcardnum ; i++){
			if(Player[2].playcardnum){
				card cardtemp1;
				Card_Define(Player[2].playcard[i], &cardtemp1);
				printf("%d.%s ",i+1,cardtemp1.cardname);
			}
		}
	printf("\n");
	printf("持續牌區：");
	for(int i = 0 ; i < Player[2].starting_size ; i++){
			if(Player[2].starting_size){
				card cardtemp1;
				Card_Define(Player[2].starting[i], &cardtemp1);
				card cardtemp2;
				Card_Define(Player[2].combo_basic[i], &cardtemp2);
				printf("%d.%s -%s  ",i+1,cardtemp1.cardname, cardtemp2.cardname);
			}
		}
	printf("\n");
	print_extra_inf(&Player[2]);
	
	printf("玩家四 │ 遊玩角色：");
	print_aligned_charname(Player[3].charname, len);
	printf(" 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n", Player[3].hp, Player[3].armor, Player[3].power, Player[3].hands, Player[3].Maxhp, Player[3].Maxarmor, Player[3].Ult_threshold);
	printf("出牌區：");
	for(int i = 0 ; i < Player[3].playcardnum ; i++){
			if(Player[3].playcardnum){
				card cardtemp1;
				Card_Define(Player[3].playcard[i], &cardtemp1);
				printf("%d.%s ",i+1,cardtemp1.cardname);
			}
		}
	printf("\n");
	printf("持續牌區：");
	for(int i = 0 ; i < Player[3].starting_size ; i++){
			if(Player[3].starting_size){
				card cardtemp1;
				Card_Define(Player[3].starting[i], &cardtemp1);
				card cardtemp2;
				Card_Define(Player[3].combo_basic[i], &cardtemp2);
				printf("%d.%s -%s  ",i+1,cardtemp1.cardname, cardtemp2.cardname);
			}
		}
	printf("\n");
	print_extra_inf(&Player[3]);

	printf("          ┌────────────────────────┐           \n");
	
	printf("     Board│ ");
	for(int i = 1 ; i <= 11 ; i++){
		if(Player[0].coordinate == i){
			if(i ==10){
				printf(" 1 ");
			}else if(i ==11){
				printf(" 1");
			}else{
				printf("1 ");
			}
		}else if(Player[1].coordinate == i){
			if(i ==10){
				printf(" 2 ");
			}else if(i ==11){
				printf(" 2");
			}else{
				printf("2 ");
			}
		}else if(Player[2].coordinate == i){
			if(i ==10){
				printf(" 3 ");
			}else if(i ==11){
				printf(" 3");
			}else{
				printf("3 ");
			}
		}else if(Player[3].coordinate == i){
			if(i ==10){
				printf(" 4 ");
			}else if(i ==11){
				printf(" 4");
			}else{
				printf("4 ");
			}
		}else{
			if(i ==10){
				printf(" _ ");
			}else if(i ==11){
				printf(" _");
			}else{
				printf("_ ");
			}
		}	
	}
	printf("│版面                   \n");
	printf("          ├────────────────────────┤           \n");
	printf("Coordinate│ 1 2 3 4 5 6 7 8 9 10 11│座標                   \n");
	printf("          ├────────────────────────┤           \n");
	printf("     Board│ ");
	for(int i = -11 ; i < 0 ; i++){
		if(Player[0].coordinate == i){
			if(i ==-1){
				printf(" 1 ");
			}else if(i ==-2){
				printf(" 1");
			}else{
				printf("1 ");
			}
		}else if(Player[1].coordinate == i){
			if(i ==-1){
				printf(" 2 ");
			}else if(i ==-2){
				printf(" 2");
			}else{
				printf("2 ");
			}
		}else if(Player[2].coordinate == i){
			if(i ==-1){
				printf(" 3 ");
			}else if(i ==-2){
				printf(" 3");
			}else{
				printf("3 ");
			}
		}else if(Player[3].coordinate == i){
			if(i ==-1){
				printf(" 4 ");
			}else if(i ==-2){
				printf(" 4");
			}else{
				printf("4 ");
			}
		}else{
		
			if(i ==-1){
				printf(" _ ");
			}else if(i ==-2){
				printf(" _");
			}else{
				printf("_ ");
			}
		}	
	}
	printf("│版面                   \n");
	printf("          └────────────────────────┘           \n");
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
	if(Player[0].charname) printf("%s\n", Player[0].charname);	
	else printf("（未選擇）\n");
	
	printf("玩家二　　：");        
	if(Player[1].charname) printf("%s\n", Player[1].charname);        
	else printf("（未選擇）\n");

	printf("玩家三　　：");        
	if(Player[2].charname) printf("%s\n", Player[2].charname);        
	else printf("（未選擇）\n");

	printf("玩家四　　：");        
	if(Player[3].charname) printf("%s\n\n", Player[3].charname);        
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
	printf("按下空白鍵繼續遊戲");
	int8_t ch;
	while ((ch = getchar()) != ' ') {}
	disable_raw_mode();
}

void wait_for_space_end() {
	enable_raw_mode();
	printf("按下空白鍵結束遊戲");
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

int8_t focus(player *P){
	system("clear");
	int8_t focus = -1;
	printf("現在是"ANSI_GREEN ANSI_BOLD"%s"ANSI_RESET"在進行\n",P->charname);
	printf("請問本回合你要進行專注嘛？\n0. 要\n1. 不要\n");
	printf(">");

	if(P->bot ==1 ){
			focus = botChoice(0,0,1,23);
																
	}else{
			scanf("%hhd",&focus);
	}
	if(focus == 0){
		if(remove_card(P) ==-1){
			return -1;
		}
	}
	system("clear");
	return 0;
	
}

int8_t discard_all_hands(player *P){
	while(P->hands !=0){
		discard_card_from_hand(P,0);
	}
	return 0;
}

int8_t ending_phase(player *P){
	clearRHU(P);
	P->power = 0;
	discard_all_hands(P);
	playcardnum_clear(P);
	// 檢查花木蘭防禦技/必殺的抽牌buff (ID 62-64, 68)
    if (P->character == 4 && P->mulan_draw_buff > 0) {
        int max_spend = (P->qi > P->mulan_draw_buff) ? P->mulan_draw_buff : P->qi;
        if (max_spend > 0) {
            printf("你可以在此階段花費X點氣額外抽X張牌 (至多 %d 張)。\n", max_spend);
            printf("你目前有 %d 氣。要花費多少氣？ (0-%d)\n> ", P->qi, max_spend);
            int8_t spend_qi = 0;
            if(P->bot == 1) {
                spend_qi = botChoice(0, 0, max_spend, 0);
            } else {
                scanf("%hhd", &spend_qi);
                getchar();
            }

            if (spend_qi > 0 && spend_qi <= max_spend) {
                P->qi -= spend_qi;
                printf("你花費了 %d 氣，額外抽取 %d 張牌。\n", spend_qi, spend_qi);
                draw_card(spend_qi, P);
            }
        }
        P->mulan_draw_buff = 0; // 重置buff
    }
	draw_card(6,P);
	// 檢查蛻變1 主宰命運 (ID: 152)
    if (check_passive(P, 152) > 0) {
        printf("你擁有'主宰命運'，可以棄掉1張手牌再抽1張。\n");
        printf("0) 不使用 1) 使用\n> ");
        int8_t choice = 0;
        if(P->bot == 1) {
            choice = botChoice(0, 0, 1, 0);
        } else {
            scanf("%hhd", &choice);
            getchar();
        }

        if(choice == 1 && P->hands > 0) {
            printf("請選擇要棄掉的牌 (1-%d):\n", P->hands);
            print_hands(P);
            printf("> ");
            int8_t card_idx = 0;
             if(P->bot == 1) {
                card_idx = botChoice(0, 1, P->hands, 0);
            } else {
                scanf("%hhd", &card_idx);
                getchar();
            }
            if(card_idx > 0 && card_idx <= P->hands) {
                discard_card_from_hand(P, card_idx - 1);
                printf("你棄掉一張牌，並重新抽取一張。\n");
                draw_card(1, P);
            }
        }
    }
	P->atk_buff = 0;
	P->defend_buff = 0;
	P->speed_buff = 0;
	P->atk_bb1 = 0;
	P->atk_bb2 = 0;
	P->atk_bb3 = 0;

	
	return 0;
}

int8_t starting_phase(player *P){
	MulanHPtemp = Player[target(P)].hp;
	P->sleep_passive1_cd = 0;
	P->sleep_passive2_cd = 0;
	check_starting(P,&Player[target(P)]);
	if(RedHoodHPtemp != Player[target(P)].hp && check_passive(&Player[target(P)],136) !=0){
					
					while(1){
									int choices_R=0;
									printf(ANSI_GREEN ANSI_BOLD"%s"ANSI_RESET"你可以捨棄至多一張技能牌來將傷害減少X，X為你捨棄的技能牌等級\n",Player[target(P)].charname);
									printf("0)不捨棄 1)捨棄\n>");
									
									if(P->bot ==1 ){
														choices_R = botChoice(0,0,1,24);
																								
									}else{
														scanf("%d",&choices_R);
														getchar();
									}
									
									if(choices_R!= 0 && choices_R!= 1){
										printf("輸入錯誤！\n");
									}else if(choices_R == 0){
										break;
									}else if(choices_R == 1){
										
										int8_t cn = -1;
										while(cn!=0){
											printf("請選擇一張你要捨棄的牌(輸入0取消)\n");
											print_hands(&Player[target(P)]);
											printf(">");
											if(P->bot ==1 ){
															cn = botChoice(0,0,P->hands,25);
															
											}else{
																scanf("%hhd",&cn);
											}
											if(cn == 0)break;
											if(Player[target(P)].hands_card[cn-1].type == 4){
												Player[target(P)].hp += Player[target(P)].hands_card[cn-1].level;
												discard_card_from_hand(&Player[target(P)],cn-1);
												break;
											}else{
												printf("這不是技能牌請重新輸入\n>");
											}
											
										}
										RedHoodHPtemp = Player[target(P)].hp;
										break;
									}
						}
	}
	P->armor = 0;
	P->end_turn = 0;
	//TODO : 其他結算
	
	return 0;
}

int8_t Ult_Gain(player *P){
	if(P->hp <= P->Ult_threshold && P->Ult_deck[0] != 0){
		system("clear");
		
		card cardtemp1;
		card cardtemp2;
		card cardtemp3;
		Card_Define(P->Ult_deck[0], &cardtemp1);
		printf("%d) %s 效果：%s\n",0,cardtemp1.cardname,cardtemp1.inf);
		Card_Define(P->Ult_deck[1], &cardtemp2);
		printf("%d) %s 效果：%s\n",1,cardtemp2.cardname,cardtemp2.inf);
		Card_Define(P->Ult_deck[2], &cardtemp3);
		printf("%d) %s 效果：%s\n",2,cardtemp3.cardname,cardtemp3.inf);
		while(1){
			printf(ANSI_GREEN ANSI_BOLD"%s"ANSI_RESET"請選擇你要的必殺牌：\n>",P->charname);
			int cho = -1;
			if(P->bot ==1 ){
				cho = botChoice(0,0,1,26);
			}else{
				scanf("%d",&cho);
				getchar();
			}
			
			if(cho == 0){
				Card_Define(P->Ult_deck[0], &P->hands_card[P->hands]);
				P->hands++;
				P->Ult_deck[0] =0;
				P->Ult_deck[1] =0;
				P->Ult_deck[2] =0;
				break;
			}else if(cho == 1){
				Card_Define(P->Ult_deck[1], &P->hands_card[P->hands]);
				P->hands++;
				P->Ult_deck[0] =0;
				P->Ult_deck[1] =0;
				P->Ult_deck[2] =0;
				break;
			}else if(cho == 2){
				Card_Define(P->Ult_deck[2], &P->hands_card[P->hands]);
				P->hands++;
				P->Ult_deck[0] =0;
				P->Ult_deck[1] =0;
				P->Ult_deck[2] =0;
				break;
			}else{
				printf("錯誤輸入！！\n");
			}
		}
	}
	return 0;
}



//=====================================================


int main(){ //mainfuc

	signal(SIGINT, handle_sigint);
	 if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio error: %s\n", Mix_GetError());
        return 1;
    }

    Mix_Music* bgm = Mix_LoadMUS("music.mp3");
    if (!bgm) {
        fprintf(stderr, "Load BGM error: %s\n", Mix_GetError());
        return 1;
    }

    Mix_PlayMusic(bgm, -1); // -1 = 無限循環播放（背景音樂）	
	Mix_VolumeMusic(16);


	SetTraceLogLevel(LOG_NONE);
	printf("是否要使用圖形介面（GUI）？\n");
	printf("1. 是\n");
	printf("2. 否（預設使用文字介面）\n");
	printf("> ");
	while (scanf("%hhd", &gui_mode) != 1 || !(gui_mode == 1 || gui_mode == 2)) {
		getchar(); // 清除錯誤輸入
		printf("輸入錯誤，請重新輸入（1 或 2）：\n> ");
	}
	if (gui_mode == 1) {
	#ifdef __linux__
		// 可加強偵測是否是 Ubuntu
		char *desktop_env = getenv("XDG_CURRENT_DESKTOP");
		if (desktop_env && (strstr(desktop_env, "Ubuntu") || strstr(desktop_env, "GNOME") || strstr(desktop_env, "ubuntu:GNOME"))) {
 
			printf("檢測到 Ubuntu 環境，啟用 GUI 模式...\n");
		} else {
			printf("警告：你選擇了 GUI 模式，但未檢測到 Ubuntu 環境，可能會發生相容性問題。\n");
			wait_for_space();
		}
	#else
		printf("目前僅支援 Ubuntu 環境的 GUI 模式，將使用文字介面（TUI）進行遊戲。\n");
		wait_for_space();
		gui_mode = 2;
	#endif
	}

	

	
	Player[0].starting_size = 0;
	Player[1].starting_size = 0;
	Player[2].starting_size = 0;
	Player[3].starting_size = 0;
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
	Player[0].num = 0;
	Player[1].num = 1;
	Player[2].num = 2;
	Player[3].num = 3;
	
	
	
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
	inputcharacter(&Player[0], player1_char);
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
        inputcharacter(&Player[1], player2_char);
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
	        inputcharacter(&Player[2], player3_char);
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
	        inputcharacter(&Player[3], player4_char);
	        remaining_roles[player4_char] = 0;
	        remaining_count--;
	}
	
	initialization_skill_shop(&Player[0]);
	initialization_skill_shop(&Player[1]);
	initialization_deck(&Player[0]);
	initialization_deck(&Player[1]);	
	
	print_header();	
	wait_for_space();
	
	if(mode == 1){
		Right_MAX = 9;
	}else{
		Right_MAX = 11;
	}
	//遊戲開始
	int8_t round = 0;
	int8_t flip_coins=0;
	 int current = -1;
	flip_coins = rand()%2+1;
	
	initialize_player(&Player[0]);
	initialize_player(&Player[1]);
	if (gui_mode == 1) {
		update_coordinates(Player[0].coordinate, Player[1].coordinate);
		update_characters(player1_char, player2_char);
		update_characters_info(Player[0], Player[1]);
		start_board_gui();
	}
	if(mode ==2){
		initialization_skill_shop(&Player[2]);
		initialization_skill_shop(&Player[3]);
		initialization_deck(&Player[2]);
		initialization_deck(&Player[3]);	
		initialize_player(&Player[2]);
		initialize_player(&Player[3]);
		Player[0].coordinate = 5;
		Player[1].coordinate = 7;
		Player[2].coordinate = -7;
		Player[3].coordinate = -5;
		
		Player[0].team = 1;
		Player[1].team = 0;
		Player[2].team = 1;
		Player[3].team = 0;
		
		
		Player[0].alive = 1;
		Player[1].alive = 1;
		Player[2].alive = 1;
		Player[3].alive = 1;
	}else{
		Player[2].character = -1;
		Player[3].character = -1;
		Player[0].coordinate = 4;
		Player[1].coordinate = 6;
		
	}
	if(BotOn == 1){
	Player[1].bot = 1;
	Player[3].bot = 1;
	}
	
	if(flip_coins == 1){
		//player 1 first
		
			Player[0].first = 1;
		
	}else{
		//player 2 first
			Player[1].first = 1;
		
	}
	
	
	while(1){
		update_characters_info(Player[0], Player[1]);
		 round++;
		 turn = 0;
		if(mode == 1){//單人模式
			
			if(Player[0].first == 1){
				if(round % 2 == 1){
					starting_phase(&Player[0]);
					Ult_Gain(&Player[target(&Player[0])]);
					Ult_Gain(&Player[0]);
				}else{
					starting_phase(&Player[1]);
					Ult_Gain(&Player[target(&Player[1])]);
					Ult_Gain(&Player[1]);
				}
				if(round == 1){
					draw_card(4,&Player[0]);
					draw_card(6,&Player[1]);
					update_characters_info(Player[0], Player[1]);
				}
			}else{
				if(round % 2 == 1){
					starting_phase(&Player[1]);
					Ult_Gain(&Player[target(&Player[1])]);
					Ult_Gain(&Player[1]);
				}else{
					starting_phase(&Player[0]);
					Ult_Gain(&Player[target(&Player[0])]);
					Ult_Gain(&Player[0]);
				}
			
				if(round == 1){
					draw_card(4,&Player[1]);
					draw_card(6,&Player[0]);
					update_characters_info(Player[0], Player[1]);	
				}
			}
			
			while(1){ // 執行階段
				turn ++;
				if(Player[0].first == 1){//玩家一先手
					if(round % 2 == 1){
						if(turn == 1){
							if(focus(&Player[0])==-1) break;
						}
						Ult_Gain(&Player[target(&Player[0])]);
					Ult_Gain(&Player[0]);
						print_game_broad_9();
						if(round == 1){
							printf("玩家一先手\n");
							
						}
						action_command(&Player[0]);
						if( Player[0].end_turn == 1) break;
						
					}else{
						if(turn == 1){
							if(focus(&Player[1])== -1) break;
						}
						Ult_Gain(&Player[target(&Player[1])]);
					Ult_Gain(&Player[1]);
						print_game_broad_9();
						action_command(&Player[1]);
						if( Player[1].end_turn == 1) break;
					}
				}else{
					
					if(round % 2 == 1){
						if(turn == 1){
							if(focus(&Player[1])==-1) break;
						}
						Ult_Gain(&Player[target(&Player[1])]);
					Ult_Gain(&Player[1]);
						print_game_broad_9();
						if(round == 1) printf("玩家二先手\n");
						action_command(&Player[1]);
						if( Player[1].end_turn == 1  ) break;
					}else{
						if(turn == 1){
							if(focus(&Player[0])==-1) break;
						}
						Ult_Gain(&Player[target(&Player[0])]);
					Ult_Gain(&Player[0]);
						print_game_broad_9();
						action_command(&Player[0]);
						if( Player[0].end_turn == 1) break;
					}
				}
			} // 執行階段結束
			
			
			
			if(Player[0].first == 1){
				if(round % 2 == 1){	
					ending_phase(&Player[0]);
				}else{
					ending_phase(&Player[1]);
				}
			}else{
				if(round % 2 == 1){	
					ending_phase(&Player[1]);
				}else{
					ending_phase(&Player[0]);
				}
			}
			
			if(end_game_detection() == 1){
				print_end_game();
				wait_for_space_end();
				return 0;
			}
			//判斷輸贏
		}else{
			while(1){
			turn++;
			if (round == 1) {
						
                for (int i = 0; i < 4; i++) draw_card((i == 0) ? 4 : 6, &Player[i]);
                current = (Player[0].first) ? 0 : 1;
                starting_phase(&Player[current]);
            } else {
            		
                starting_phase(&Player[current]);
            }
						
            Ult_Gain(&Player[target(&Player[current])]);
            Ult_Gain(&Player[current]);

           	if(turn==1){
           		if (focus(&Player[current]) == -1) break;
           		turn= 2;
           	}
            print_game_broad_11();
            action_command(&Player[current]);
            
						
            if (Player[current].end_turn == 1) {
            	
                ending_phase(&Player[current]);
                if (end_game_detection() == 1) {
                    print_end_game();
                    wait_for_space_end();
                    return 0;
                }
                current = get_next_player(current, Player);
                break;
            }
            }
            
		}
			}
	Mix_HaltMusic();
	Mix_FreeMusic(bgm);
	Mix_CloseAudio();
	SDL_Quit();	
	return 0;
}
