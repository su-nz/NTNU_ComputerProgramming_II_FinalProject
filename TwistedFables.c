#include "TwistedFables.h"

void print_game_broad_9(){
	system("clear");
	
		printf("玩家一 │ 遊玩角色：%s 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n",player_1.charname,player_1.hp,player_1.armor,player_1.power,player_1.hands,player_1.Maxhp,player_1.Maxarmor,player_1.Ult_threshold);
		printf("玩家二 │ 遊玩角色：%s 血量：%hhd 防禦值：%hhd 能量：%hhd 手牌數：%hhd 血量上限：%hhd 防禦上限：%hhd 必殺閥值:%hhd\n",player_2.charname,player_2.hp,player_2.armor,player_2.power,player_2.hands,player_2.Maxhp,player_2.Maxarmor,player_2.Ult_threshold);
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

int8_t command(player *P){
	printf("現在是%s的回合，現在是你的執行階段\n");
}

int8_t inputcharacter(player *P, int8_t characternum) { //寫入角色資訊
    (*P).character = characternum;

    switch (characternum) {
        case 0: // 小紅帽
            (*P).charname = "小紅帽  ";
            (*P).Maxhp = 30;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 15;
            break;

        case 1: // 白雪公主
            (*P).charname = "白雪公主";
            (*P).Maxhp = 34;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 17;
            break;

        case 2: // 睡美人
            (*P).charname = "睡美人  ";
            (*P).Maxhp = 42;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 21;
            break;

        case 3: // 愛麗絲
            (*P).charname = "愛麗絲  ";
            (*P).Maxhp = 32;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 16;
            break;

        case 4: // 花木蘭
            (*P).charname = "花木蘭  ";
            (*P).Maxhp = 34;
            (*P).Maxarmor = 3;
            (*P).Ult_threshold = 17;
            break;

        case 5: // 輝夜姬
            (*P).charname = "輝夜姬  ";
            (*P).Maxhp = 32;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 16;
            break;

        case 6: // 美人魚
            (*P).charname = "美人魚  ";
            (*P).Maxhp = 36;
            (*P).Maxarmor = 3;
            (*P).Ult_threshold = 18;
            break;

        case 7: // 火柴女孩
            (*P).charname = "火柴女孩";
            (*P).Maxhp = 36;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 18;
            break;

        case 8: // 桃樂絲
            (*P).charname = "桃樂絲  ";
            (*P).Maxhp = 40;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 20;
            break;

        case 9: // 山魯佐德
            (*P).charname = "山魯佐德";
            (*P).Maxhp = 36;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 18;
            break;

        default:
            return -1; // 無效的角色編號
    }

    // 共通初始化
    (*P).hp = (*P).Maxhp;
    (*P).armor = 0;
    (*P).power = 0;
    (*P).hands = 0;
    (*P).token = 0;

    return 0; // 成功
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
	player_1.coordinate = 0;
	player_2.coordinate = 8;
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
