#include "TwistedFables.h"

int main(){
	srand( time(NULL) );
	//mode=-1
	printf("請你選擇你想要遊玩的模式：(1.)1對1 (2.)2對2 （請輸入數字來做決定\n");
	while (scanf("%hhd",&mode)!=1 || !(mode == 1 || mode ==2 )){
		getchar();
		printf("請你重新輸入\n");
		printf("請你選擇你想要遊玩的模式：(1.)1對1 (2.)2對2 （請輸入數字來做決定\n");
		
	} 
	//RelicOn = -1
	printf("是否要啟動遺跡模式？：(1.)是 (2.)否 （請輸入數字來做決定\n");
	while (scanf("%hhd",&RelicOn)!=1 || !(RelicOn == 1 || RelicOn == 2 )){
		getchar();
		printf("請你重新輸入\n");
		printf("是否要啟動遺跡模式？：(1.)是 (2.)否 （請輸入數字來做決定\n");
	} 
	//player1_char = -1
	printf("====================\n");
	printf("0)小紅帽\n");
	printf("1)白雪公主\n");
	printf("2)睡美人\n");
	printf("10)隨機\n");
	printf("====================\n");
	printf("玩家一請選擇你要遊玩的角色：");
	while (scanf("%hhd",&player1_char)!=1 || !(player1_char >= 0 && player1_char <= 10 )){
		getchar();
		printf("請你重新輸入\n");
		printf("====================\n");
		printf("0)小紅帽\n");
		printf("1)白雪公主\n");
		printf("2)睡美人\n");
		printf("10)隨機\n");
		printf("====================\n");
		printf("玩家一請選擇你要遊玩的角色：");
		
	} 
	if(mode == 2){
		printf("====================\n");
		printf("0)小紅帽\n");
		printf("1)白雪公主\n");
		printf("2)睡美人\n");
		printf("10)隨機\n");
		printf("====================\n");
		printf("玩家二請選擇你要遊玩的角色：");
		while (scanf("%hhd",&player2_char)!=1 || !(player2_char >= 0 && player2_char <= 10 )){
			getchar();
			printf("請你重新輸入\n");
			printf("====================\n");
			printf("0)小紅帽\n");
			printf("1)白雪公主\n");
			printf("2)睡美人\n");
			printf("10)隨機\n");
			printf("====================\n");
			printf("玩家二請選擇你要遊玩的角色：");
		} 
	}
	
	
	
  
	return 0;
}
