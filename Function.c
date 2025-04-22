#include "TwistedFables.h"





int8_t action_command(player *P){
	int8_t comm=-1;
	printf("現在是%s的回合，現在是你的執行階段請從以下的動作中選一個執行\n",(*P).charname);
	printf("0.)專注 1.)購買基礎牌 2.)購買技能牌 3.)打牌 4.)查看自己的棄牌堆 5.)查看別人的棄牌堆\n");
	printf("輸入指令：");
	scanf("%hhd",&comm);
}


int8_t inputcharacter(player *P, int8_t characternum) { //寫入角色資訊
    (*P).character = characternum;
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
            (*P).poison = 12 ;
            break;

        case 2: // 睡美人
            (*P).charname = "睡美人  ";
            (*P).Maxhp = 42;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 21;
            (*P).sleep = 1;
            break;

        case 3: // 愛麗絲
            (*P).charname = "愛麗絲  ";
            (*P).Maxhp = 32;
            (*P).Maxarmor = 6;
            (*P).Ult_threshold = 16;
            (*P).alice=0;
            break;

        case 4: // 花木蘭
            (*P).charname = "花木蘭  ";
            (*P).Maxhp = 34;
            (*P).Maxarmor = 3;
            (*P).Ult_threshold = 17;
            (*P).qi= 0;
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
            (*P).charname = "桃樂絲  ";
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
