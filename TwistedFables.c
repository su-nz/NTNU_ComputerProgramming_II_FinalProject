#include "TwistedFables.h"

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
		
		return ;
}




int main(){

	srand( time(NULL) );
	//mode=-1
	printf("請你選擇你想要遊玩的模式：(1.)1對1 (2.)2對2 （請輸入數字來做決定\n");
	while (scanf("%hhd",&mode)!=1 || !(mode == 1 || mode ==2 )){
		getchar();
		printf("請你重新輸入\n");
		printf("請你選擇你想要遊玩的模式：(1.)1對1 (2.)2對2 （請輸入數字來做決定\n");
		
	} 
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
	
	
	
	
	
	
  
	return 0;
}
