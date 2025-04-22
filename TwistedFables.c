#include "TwistedFables.h"
#include "vector.h"

int16_t Map[11][3]={0};// Map[x][0]) 遺跡排的紀錄 Map[x][1]) 第一排和單人模式時使用的地圖 Map[x][2]) 第二排// 1v1 9格
//棄牌堆
card hands1[50],hands2[50],hands3[50],hands4[50];

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

int8_t initialization_basic_shop(){
	for(int i = 0 ; i < 3 ; i ++){
		for(int j = 0 ; j < 3 ; j++){
			basicBuyDeck[i][j].SIZE = 12;
			for(int k = 1 ; k <=12 ; k++){
				basicBuyDeck[i][j].array[k] = (k + 12*j + 36*i);
			}
			
		}
	}
	basicBuyDeck[3][0].SIZE = 12;
	for(int k = 1 ; k <=12 ; k++){
		basicBuyDeck[4][0].array[k] = (k + 36*3); 
	}
	return 0; // 成功
}

int8_t initialization_skill_shop(player *P){
	skillBuyDeck[P->num][0].SIZE = 8;
	skillBuyDeck[P->num][1].SIZE = 8;
	skillBuyDeck[P->num][2].SIZE = 8;
	switch (P->character){
		case 0:
			for(int i = 0 ; i < 3 ; i++){
				for(int j = 0 ; j < 8 ; j++){
					skillBuyDeck[P->num][i].array[j] = (128+i*8) - j ;
				}
			}
		break;
		
		case 1:
			for(int i = 0 ; i < 3 ; i++){
				for(int j = 0 ; j < 8 ; j++){
					skillBuyDeck[P->num][i].array[j] = (155+i*8) - j ;
				}
			}
		break;
		
		case 2:
			for(int i = 0 ; i < 3 ; i++){
				for(int j = 0 ; j < 8 ; j++){
					skillBuyDeck[P->num][i].array[j] = (200+i*8) - j ;
				}
			}
		break;
		
		case 3:
			for(int i = 0 ; i < 3 ; i++){
				for(int j = 0 ; j < 8 ; j++){
					skillBuyDeck[P->num][i].array[j] = (227+i*8) - j ;
				}
			}
			
		break;
		
		case 4:
			for(int i = 0 ; i < 3 ; i++){
				for(int j = 0 ; j < 8 ; j++){
					skillBuyDeck[P->num][i].array[j] = (254+i*8) - j ;
				}
			}
			
		break;
		
		case 5:
			for(int i = 0 ; i < 3 ; i++){
				for(int j = 0 ; j < 8 ; j++){
					skillBuyDeck[P->num][i].array[j] = (274+i*8) - j ;
				}
			}
			
		break;
		
		case 6:
			for(int i = 0 ; i < 3 ; i++){
				for(int j = 0 ; j < 8 ; j++){
					skillBuyDeck[P->num][i].array[j] = (308+i*8) - j ;
				}
			}
			
		break;
		
		case 7:
			for(int i = 0 ; i < 3 ; i++){
				for(int j = 0 ; j < 8 ; j++){
					skillBuyDeck[P->num][i].array[j] = (335+i*8) - j ;
				}
			}
			
		break;
		
		case 8:
			for(int i = 0 ; i < 3 ; i++){
				for(int j = 0 ; j < 8 ; j++){
					skillBuyDeck[P->num][i].array[j] = (374+i*8) - j ;
				}
			}
			
		break;
		
		case 9:
			for(int i = 0 ; i < 3 ; i++){
				for(int j = 0 ; j < 8 ; j++){
					skillBuyDeck[P->num][i].array[j] = (401+i*8) - j ;
				}
			}
			
		break;
		
			
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
		printf("請輸入你要做什麼？1.)升級技能 2.)退出商店：");
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
						pushbackVector(&P->discard, skillBuyDeck[P->num][0].array[basicBuyDeck[0][0].SIZE-1]);
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
						pushbackVector(&P->discard, skillBuyDeck[P->num][1].array[basicBuyDeck[1][1].SIZE-1]);
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
						pushbackVector(&P->discard, skillBuyDeck[P->num][2].array[basicBuyDeck[2][2].SIZE-1]);
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
int8_t basic_shop_command(player *P){
	int8_t bsc =-1;
	printf_basic_shop();
	while(1){
		
		printf("請輸入你要做什麼？1.)購買卡片 2.)退出商店：");
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
	



int8_t action_command(player *P){
	int8_t comm=-1;
	printf("現在是%s的回合，現在是你的執行階段請從以下的動作中選一個執行\n",(*P).charname);
	printf("0.)專注 1.)購買基礎牌 2.)購買技能牌 3.)打牌 4.)查看自己的棄牌堆 5.)查看別人的棄牌堆 6.)結束回合\n");
	printf("輸入指令：");
	scanf("%hhd",&comm);
	switch(comm){
		case 0:  // 專注
		
		
            	break;
            	
            	case 1:  // 購買基礎牌
			basic_shop_command(P);
		
            	break;
            	
            	case 2:  // 購買技能牌
			skill_shop_command(P);
		
            	break;
            	
            	case 3:  // 打牌
		
		
            	break;
            	
            	case 4:  // 查看自己的棄牌
		
		
            	break;
            	
            	case 5:  // 查看別人的棄牌堆
		
		
            	break;
            	
            	case 6:  // 結束遊戲階段
		
		
            	break;
	}
}



void print_skills_shop(player *P){

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

void print_game_broad_9(){
	system("clear");
	
		printf("玩家一 │ 遊玩角色：%s 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n",player_1.charname,player_1.hp,player_1.armor,player_1.power,player_1.hands,player_1.Maxhp,player_1.Maxarmor,player_1.Ult_threshold);
		print_extra_inf(&player_1);
		printf("玩家二 │ 遊玩角色：%s 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n",player_2.charname,player_2.hp,player_2.armor,player_2.power,player_2.hands,player_2.Maxhp,player_2.Maxarmor,player_2.Ult_threshold);
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
		printf("Coordinate│ 0 1 2 3 4 5 6 7 8 │座標                   \n");
		printf("          └───────────────────┘           \n");
	action_command(&player_1);
		return ;
}




int main(){ //mainfuc

	srand( time(NULL) );
	
	initialization_basic_shop();
	//mode=-1
	printf("請你選擇你想要遊玩的模式：(1.)1對1 (2.)2對2 （請輸入數字來做決定\n");
	while (scanf("%hhd",&mode)!=1 || !(mode == 1 || mode ==2 )){
		getchar();
		printf("請你重新輸入\n");
		printf("請你選擇你想要遊玩的模式：(1.)1對1 (2.)2對2 （請輸入數字來做決定\n");
		
	} 
	player_1.num = 0;
	player_2.num = 1;
	player_3.num = 2;
	player_4.num = 3;
	initialization_skill_shop(&player_1);
	initialization_skill_shop(&player_2);
	player_1.coordinate = 3;
	player_2.coordinate = 5;
	//RelicOn = -1
	printf("是否要啟動遺跡模式？：(1.)是 (2.)否 （請輸入數字來做決定\n");
	while (scanf("%hhd",&RelicOn)!=1 || !(RelicOn == 1 || RelicOn == 2 )){
		getchar();
		printf("請你重新輸入\n");
		printf("是否要啟動遺跡模式？：(1.)是 (2.)否 （請輸入數字來做決定\n");
	} 
	//BotOn = -1
	printf("是否要啟用機器人？：(1.)是 (2.)否 （請輸入數字來做決定\n");
	while (scanf("%hhd",&BotOn)!=1 || !(BotOn == 1 || BotOn == 2 )){
		getchar();
		printf("請你重新輸入\n");
		printf("是否要啟用機器人？：(1.)是 (2.)否 （請輸入數字來做決定\n");
	} 
	//player1_char = -1
	printf("\n====================\n");
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
		player1_char = (rand()%9+1); 
	}
	inputcharacter(&player_1, player1_char);
	
	printf("\n====================\n");
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
		player2_char = (rand()%9+1); 
	}
	inputcharacter(&player_2, player2_char);
	
	if(mode == 2 ){
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
			player3_char = (rand()%9+1); 
		}
		inputcharacter(&player_3, player3_char);
		printf("\n====================\n");
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
			player4_char = (rand()%9+1); 
		}
		inputcharacter(&player_4, player4_char);
	}
	
	
	//遊戲開始
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
	if(mode == 1){
		print_game_broad_9();
		
	}
	
	while(1){
		print_game_broad_9();
		
	}
	
	
	
	
  
	return 0;
}
