#include "TwistedFables.h"

int16_t Card_Define(int16_t CardID , card *C){
	//初始化
	
	(*C).cardname = " ";
	(*C).clone = 0;
	(*C).cost = 0;
	(*C).level = 0;
	(*C).range = 0; //for attack 0 means its doesn't need range
	(*C).type = -1; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
	(*C).power_generate = 0;
	(*C).value = 0; // for example value = 1 on attack => deal 1 damage
	(*C).shield = 0;
	(*C).damage = 0;
	(*C).require_basic_card = 0; // 0 means do not requires
	(*C).remain = 0;
	(*C).cardcode = CardID;
	(*C).inf = " ";	
	
	//初始化完成
	
	if(CardID ==0){ //基礎 攻擊牌 等級一
		(*C).cardname = " ";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0; 
		(*C).type = 0; 
		(*C).power_generate = 0;
		(*C).value = 0;
		(*C).shield = 0;
		(*C).damage = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = " ";	
	}
	
	if(CardID ==1){ //基礎 攻擊牌 等級一
		(*C).cardname = "攻擊牌 等級一";
		(*C).cost = 1 ;
		(*C).level = 1;
		(*C).range = 1; //for attack 0 means its doesn't need range
		(*C).type = 0; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 1;
		(*C).value = 1; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "射程1、傷害1 的攻擊，獲得1點能量";
	}
	
	if(CardID == 2){ //基礎 攻擊牌 等級二
		(*C).cardname = "攻擊牌 等級二";
		(*C).cost = 3 ;
		(*C).level = 2;
		(*C).range = 1; //for attack 0 means its doesn't need range
		(*C).type = 0; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 2;
		(*C).value = 2; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "射程1、傷害2 的攻擊，獲得2點能量";
	}
	
	if(CardID == 3){ //基礎 攻擊牌 等級三
		(*C).cardname = "攻擊牌 等級三";
		(*C).cost = 6 ;
		(*C).level = 3;
		(*C).range = 1; //for attack 0 means its doesn't need range
		(*C).type = 0; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 3;
		(*C).value = 3; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "射程1、傷害3 的攻擊，獲得3點能量";
	}
	
	if(CardID == 4){ //基礎 防禦牌 等級一
		(*C).cardname = "防禦牌 等級一";
		(*C).cost = 1 ;
		(*C).level = 1;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 1; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 1;
		(*C).value = 1; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "獲得1點防禦，獲得1點能量";
	}
	
	if(CardID == 5){ //基礎 防禦牌 等級二
		(*C).cardname = "防禦牌 等級二";
		(*C).cost = 3 ;
		(*C).level = 2;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 1; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 2;
		(*C).value = 2; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "獲得2點防禦，獲得2點能量";
	}
	
	if(CardID == 6){ //基礎 防禦牌 等級三
		(*C).cardname = "防禦牌 等級三";
		(*C).cost = 6 ;
		(*C).level = 3;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 1; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 3;
		(*C).value = 3; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "獲得3點防禦，獲得3點能量";
	}
	
	if(CardID == 7){ //基礎 移動牌 等級一
		(*C).cardname = "移動牌 等級一";
		(*C).cost = 1 ;
		(*C).level = 1;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 2; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 1;
		(*C).value = 1; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "向任意方向移動1格（如果可能的話），獲得1點能量";
	}
	
	if(CardID == 8){ //基礎 移動牌 等級二
		(*C).cardname = "移動牌 等級二";
		(*C).cost = 3 ;
		(*C).level = 2;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 2; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 2;
		(*C).value = 2; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "向任意方向移動2格（如果可能的話），獲得2點能量";
	}
	
	if(CardID == 9){ //基礎 移動牌 等級三
		(*C).cardname = "移動牌 等級三";
		(*C).cost = 6 ;
		(*C).level = 3;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 2; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 3;
		(*C).value = 3; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "向任意方向移動3格（如果可能的話），獲得3點能量";
	}
	
	if(CardID == 10){ //基礎 通用牌 等級一
		(*C).cardname = "通用牌 等級一";
		(*C).cost = 2 ;
		(*C).level = 1;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 3; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 1;
		(*C).value = 1; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "可以當作 攻擊、防禦、移動的等級一";
	}
	
	//小紅帽_技能牌-----------------------------------------------------------------
	if(CardID == 11){ //快速射擊
		(*C).cardname = "快速射擊";
		(*C).cost = 0 ;
		(*C).level = 1;
		(*C).range = 1; //for attack 0 means its doesn't need range
		(*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).damage = 1; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0)attack 1)defend 2)movement 3)
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1+O";
	}
	if(CardID == 12){ //精準射擊 x2
		(*C).cardname = "精準射擊";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 2;//for attack 0 means its doesn't need range
		(*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).damage = 2;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程2 傷害2+O";
	}
	if(CardID == 13){ //致命狙擊 x3
		(*C).cardname = "致命狙擊";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 3; //for attack 0 means its doesn't need range
		(*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).damage = 3;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程3 傷害3+O";
	}
	if(CardID == 14){ //能量護盾
		(*C).cardname = "能量護盾";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).range = 1; //for attack 0 means its doesn't need range
		(*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).remain = 1;
		(*C).power_generate = 0;
		(*C).shield = 1;
		(*C).damage = 1;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1 防禦1\n持續：在你下個回合的開始階段 如果防禦不為0\n對射程1內的對手造成 2點傷害";
	}
	if(CardID == 15){ //電流護盾 x2
		(*C).cardname = "電流護盾";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 2; //for attack 0 means its doesn't need range
		(*C).remain = 1;
		(*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).shield = 1;
		(*C).damage = 2;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "射程2 傷害2 防禦1\n持續：在你下個回合的開始階段 如果防禦不為0\n對射程2內的對手造成 4點傷害";
	}
	if(CardID == 16){ //終極護盾 x3
		(*C).cardname = "終極護盾";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 3; //for attack 0 means its doesn't need range
		(*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).remain = 1;
		(*C).shield = 1;
		(*C).damage = 3;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "射程3 傷害3 防禦1\n持續：在你下個回合的開始階段 如果防禦不為0\n對射程3內的對手造成 6點傷害";
	}
	if(CardID == 17){ //彈道噴射
	    (*C).cardname = "彈道噴射";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 1; //for attack 0 means its doesn't need range
	    (*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
	    (*C).power_generate = 0;
	    (*C).damage = 1;
	    (*C).shield = 0;
	    (*C).require_basic_card = 2;
	    (*C).cardcode = CardID;
	    (*C).inf = "將對手擊退至多O格";
	}
	if(CardID == 18){ //火力噴射 x2
	    (*C).cardname = "火力噴射";
	    (*C).cost = 2;
	    (*C).level = 2;
	    (*C).range = 2;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 2;
	    (*C).shield = 0;
	    (*C).require_basic_card = 2;
	    (*C).cardcode = CardID;
	    (*C).inf = "將對手擊退至多O格";
	}
	if(CardID == 19){ //暴怒噴射 x3
	    (*C).cardname = "暴怒噴射";
	    (*C).cost = 4;
	    (*C).level = 3;
	    (*C).range = 3;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 3;
	    (*C).shield = 0;
	    (*C).require_basic_card = 2;
	    (*C).cardcode = CardID;
	    (*C).inf = "將對手擊退至多O格";
	}
	
	//必殺技
	if(CardID == 20){ //餓狼吞噬
	    (*C).cardname = "餓狼吞噬";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 5; // Ult
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "從任意技能供應牌庫頂部獲得2張牌";
	}
	if(CardID == 21){ //系統入侵
	    (*C).cardname = "系統入侵";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 5;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "重複你本回合使用過的一個攻擊、移動、或行動的效果（含蛻變）";
	}
	if(CardID == 22){ //復仇之雨
	    (*C).cardname = "復仇之雨";
	    (*C).cost = 0;	
	    (*C).level = 0;
	    (*C).range = 3;
	    (*C).type = 5;
	    (*C).power_generate = 0;
	    (*C).damage = 3;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程3 傷害3 擊退3格，對手捨棄3張手牌";
	}
	
	//蛻變牌
	if(CardID == 135){ //過載燃燒
		(*C).cardname = "過載燃燒";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0;//for attack 0 means its doesn't need range
		(*C).type = 6; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).value = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "當你使用一個移動技能或是攻擊技能時，可以捨棄至多一張技能牌來獲得傷害X，X為你捨棄的技能牌等級";
	}
	if(CardID == 136){ //兜帽系統
		(*C).cardname = "兜帽系統";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 6; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).value = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "每當對手對你造成傷害時，可以捨棄至多一張技能牌來將傷害減少X，X為你捨棄的技能牌等級";
	}
	if(CardID == 137){ //變異感應
	    (*C).cardname = "變異感應";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 0;
	    (*C).type = 6;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "使用移動/攻擊技能時，可捨棄1張技能牌獲得射程+X（X為等級）";
	}
	if(CardID == 138){ //板載緩存（攻擊蛻變2）
		(*C).cardname = "板載緩存";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 6; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).value = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "行動回合時可以將一張手牌存放到此牌上（此牌只能存放至多一張）\n此牌不會被棄至棄牌堆中\n行動回合時可以將存放在此牌上的牌加入你的手牌";
	}
	
	//白雪公主_技能牌-----------------------------------------------------------------
	if(CardID == 23){ //水晶碎片
		(*C).cardname = "水晶碎片";
		(*C).cost = 0 ;
		(*C).level = 1;
		(*C).range = 1; // for attack 0 means it doesn't need range
		(*C).type = 4; // 0)attack 1)defend 2)movement 3)wild 4)skills 5)Ult 6)passive
		(*C).damage = 1;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1+O\n將對手牌庫頂1張牌棄入棄牌堆";
	}
	if(CardID == 24){ //水晶漩渦
		(*C).cardname = "水晶漩渦";
		(*C).cost = 2 ;
		(*C).level = 2;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 2;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n射程1 傷害2+O\n將對手牌庫頂2張牌棄入棄牌堆";
	}
	if(CardID == 25){ //水晶風暴
		(*C).cardname = "水晶風暴";
		(*C).cost = 4 ;
		(*C).level = 3;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 3;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n射程1 傷害3+O\n將對手牌庫頂3張牌棄入棄牌堆";
	}
	if(CardID == 26){ //玷污的恩惠
		(*C).cardname = "玷污的恩惠";
		(*C).cost = 0 ;
		(*C).level = 1;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 1;
		(*C).shield = 0;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1\n將中毒牌庫頂部至多O張牌放入對手的棄牌堆中";
	}
	if(CardID == 27){ //玷污的盛筵
		(*C).cardname = "玷污的盛筵";
		(*C).cost = 2 ;
		(*C).level = 2;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 2;
		(*C).shield = 0;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n射程1 傷害2\n將中毒牌庫頂部至多O張牌放入對手的棄牌堆中";
	}
	if(CardID == 28){ //玷污的狂歡
		(*C).cardname = "玷污的狂歡";
		(*C).cost = 4 ;
		(*C).level = 3;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 3;
		(*C).shield = 0;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n射程1 傷害3\n將中毒牌庫頂部至多O張牌放入對手的棄牌堆中";
	}
	if(CardID == 29){ //破碎的幻想
		(*C).cardname = "破碎的幻想";
		(*C).cost = 0 ;
		(*C).level = 1;
		(*C).range = 0;
		(*C).type = 4;
		(*C).damage = 1;
		(*C).shield = 0;
		(*C).require_basic_card = 2;
		(*C).cardcode = CardID;
		(*C).inf = "射程O 傷害1\n將你放置到與對手相鄰的格子";
	}
	if(CardID == 30){ //破碎的現實
		(*C).cardname = "破碎的現實";
		(*C).cost = 2 ;
		(*C).level = 2;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 2;
		(*C).shield = 0;
		(*C).require_basic_card = 2;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n射程1+O 傷害2\n將你放置到與對手相鄰的格子";
	}
	if(CardID == 31){ //破碎的命運
		(*C).cardname = "破碎的命運";
		(*C).cost = 4 ;
		(*C).level = 3;
		(*C).range = 2;
		(*C).type = 4;
		(*C).damage = 3;
		(*C).shield = 0;
		(*C).require_basic_card = 2;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n射程2+O 傷害3\n將你放置到與對手相鄰的格子";
	}
	
	//必殺技
	if(CardID == 32){ //七蛇之怒
		(*C).cardname = "七蛇之怒";
		(*C).cost = 0 ;
		(*C).level = 0;
		(*C).range = 1;
		(*C).type = 5; // ultimate
		(*C).damage = 0; // damage based on poison count
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 對手失去X點生命\nX等於他棄牌堆中中毒牌的數量";
	}
	if(CardID == 33){ //魔鏡之雨
		(*C).cardname = "魔鏡之雨";
		(*C).cost = 0 ;
		(*C).level = 0;
		(*C).range = 1;
		(*C).type = 5;
		(*C).damage = 3;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害3\n對手必須棄掉他的全部手牌之後抽取4張牌";
	}
	if(CardID == 34){ //醞釀之災
		(*C).cardname = "醞釀之災";
		(*C).cost = 0 ;
		(*C).level = 0;
		(*C).range = 3;
		(*C).type = 5;
		(*C).damage = 3;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程3 傷害3\n你可以選擇將對手棄牌堆中至多3張牌洗入他的牌庫";
	}
	
	//蛻變牌
	if(CardID == 139){ //水晶之棺
		(*C).cardname = "水晶之棺";
		(*C).cost = 0 ;
		(*C).level = 0;
		(*C).range = 0;
		(*C).type = 6; // passive
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "當你透過一個攻擊行動或是一個攻擊技能對對手造成至少兩點傷害時\n將中毒牌庫頂部1張牌放入他的棄牌堆";
	}
	if(CardID == 140 ){ //墮落之劫
		(*C).cardname = "墮落之劫";
		(*C).cost = 0 ;
		(*C).level = 0;
		(*C).range = 0;
		(*C).type = 6;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "當你要透過一個防禦技能將中毒牌放入對手的棄牌堆時\n可以選擇將其中1張中毒牌洗入他的牌庫來代替放入棄牌堆";
	}
	if(CardID == 141 ){ //劇毒之蝕
		(*C).cardname = "劇毒之蝕";
		(*C).cost = 0 ;
		(*C).level = 0;
		(*C).range = 0;
		(*C).type = 6;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "當你透過一個移動行動（並非移動技能）穿過對手時\n或是對手透過一個移動行動穿過你時\n可以將中毒牌庫頂部一張牌入他的棄牌堆";
	}
	if(CardID == 142 ){ //至純之毒
		(*C).cardname = "至純之毒";
		(*C).cost = 0 ;
		(*C).level = 0;
		(*C).range = 0;
		(*C).type = 6;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "當一張中毒牌進入對手的棄牌堆時 他額外失去1點生命\n此蛻變牌可以累積";
	}
	
	if(CardID == POISON_CARD_ID){
    (*C).cardname = "中毒";
    (*C).type = -1; // 特殊類型
    (*C).inf = "一張無用的卡牌，會稀釋你的牌庫。";
    (*C).cardcode = CardID;
}

	//睡美人_技能牌-----------------------------------------------------------------
	if(CardID == 35){
	    (*C).cardname = "心靈震顫";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 1;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 1;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程1 傷害O 你可以同時對自己造成X點傷害來獲得傷害+X，X至多為1";
	}
	if(CardID == 36){
	    (*C).cardname = "心靈之怒";
	    (*C).cost = 2;
	    (*C).level = 2;
	    (*C).range = 1;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 2;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程1 傷害2×O 你可以同時對自己造成X點傷害來獲得傷害+X，X至多為2";
	}
	if(CardID == 37){
	    (*C).cardname = "心靈狂怒";
	    (*C).cost = 4;
	    (*C).level = 3;
	    (*C).range = 1;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 3;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程1 傷害3×O 你可以同時對自己造成X點傷害來獲得傷害+X，X至多為3";
	}
	
	if(CardID == 38){
	    (*C).cardname = "爆裂之鎖";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 0;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 1;
	    (*C).cardcode = CardID;
	    (*C).inf = "直到本回合結束之前，接下來的O＋⬖次攻擊行動每一次都會獲得傷害+1，這些行動不需要連續使用";
	}
	if(CardID == 39){
	    (*C).cardname = "爆裂之骨";
	    (*C).cost = 2;
	    (*C).level = 2;
	    (*C).range = 0;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 1;
	    (*C).shield = 0;
	    (*C).require_basic_card = 1;
	    (*C).cardcode = CardID;
	    (*C).inf = "直到本回合結束之前，接下來的O＋⬖次攻擊行動每一次都會獲得傷害+2，這些行動不需要連續使用";
	}
	if(CardID == 40){
	    (*C).cardname = "爆裂之魂";
	    (*C).cost = 4;
	    (*C).level = 3;
	    (*C).range = 0;
	    (*C).type = 1;
	    (*C).power_generate = 0;
	    (*C).damage = 2;
	    (*C).shield = 0;
	    (*C).require_basic_card = 1;
	    (*C).cardcode = CardID;
	    (*C).inf = "直到本回合結束之前，接下來的O＋⬖次攻擊行動每一次都會獲得傷害+3，這些行動不需要連續使用";
	}
	
	if(CardID == 41){
	    (*C).cardname = "黑暗碰觸";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 2;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 3;
	    (*C).shield = 0;
	    (*C).require_basic_card = 1;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程2 傷害 O+⬖ 將對手向你的方向移動O格（不算對手的移動行動、不能將他穿過你）";
	}
	if(CardID == 42){
	    (*C).cardname = "黑暗糾纏";
	    (*C).cost = 2;
	    (*C).level = 2;
	    (*C).range = 3;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 1;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程3 傷害 O+⬖ 將對手向你的方向移動O格（不算對手的移動行動、不能將他穿過你）";
	}
	if(CardID == 43){
	    (*C).cardname = "黑暗絞殺";
	    (*C).cost = 4;
	    (*C).level = 3;
	    (*C).range = 4;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 1;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程4 傷害 O+⬖ 將對手向你的方向移動O格（不算對手的移動行動、不能將他穿過你）";
	}



	//必殺技
	
	if(CardID == 44){
	    (*C).cardname = "喚醒沉睡";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 5;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "無論處於哪一種狀態，立即獲得3個覺醒TOKEN（忽略上限值6），如果仍然處於沉睡狀態，你可以立即進入覺醒狀態";
	}
	if(CardID == 45){
	    (*C).cardname = "白日夢魘";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 5;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).remain = 1;
	    (*C).inf = "持續：直到下個回合開始，每當你的生命因承受傷害（非失去生命）而減少時，抽取生命減少數量相同的牌（至多六張）";
	}
	if(CardID == 46){
	    (*C).cardname = "血脈重鑄";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 5;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "無論處於哪一種狀態，花費所有的覺醒TOKEN，每花費一個覺醒TOKEN恢復1點生命";
	}

	//蛻變牌
	if(CardID == 143){
	    (*C).cardname = "放血療法";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 6;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "每回合限一次，當你需要為一個行動或技能打出一張基本牌時，你可以選擇失去2/4/6點生命，將其視作你打出一張 Lv1/Lv2/Lv3 的基本牌（不能因此獲得能量）";
	}
	if(CardID == 144){
	    (*C).cardname = "血祭之禮";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 6;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "每回合限一次，當你對對手造成至少2/4/6點傷害時，你可以將棄牌堆中一張等級不超過 Lv1/Lv2/Lv3 的攻擊牌（不能是通用牌）加入你的手牌";
	}
	if(CardID == 145){
	    (*C).cardname = "精神屏障";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 6;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "當你使用一個移動技能時，你可以同時獲得X點防禦，X等於這個技能的等級";
	}
	if(CardID == 146){
	    (*C).cardname = "強制治療";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 5;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "立即恢復5點生命，移除此牌";
	}


	//愛麗絲_技能牌-----------------------------------------------------------------
	if(CardID == 47){
	    (*C).cardname = "開啟牌局";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 1;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 1;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程1 傷害1，對手展示3張基本牌，每有一張他不能或不願意展示你獲得傷害+O，你可以選擇一張展示的牌從基礎供應牌庫獲得相同牌放入棄牌堆，之後你的身份可以變為紅心皇后";
	}
	if(CardID == 48){
	    (*C).cardname = "扭轉牌局";
	    (*C).cost = 2;
	    (*C).level = 2;
	    (*C).range = 2;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 2;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程2 傷害2，對手展示4張基本牌，每有一張他不能或不願意展示你獲得傷害+O，你可以選擇一張展示的牌從基礎供應牌庫獲得相同牌放入棄牌堆，之後你的身份可以變為紅心皇后";
	}
	if(CardID == 49){
	    (*C).cardname = "操控牌局";
	    (*C).cost = 4;
	    (*C).level = 3;
	    (*C).range = 3;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 3;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程3 傷害3，對手展示5張基本牌，每有一張他不能或不願意展示你獲得傷害+O，你可以選擇一張展示的牌從基礎供應牌庫獲得相同牌放入棄牌堆，之後你的身份可以變為紅心皇后";
	}
	if(CardID == 50){
	    (*C).cardname = "魔力技巧";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 0;
	    (*C).type = 1;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 1;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "防禦1，可以從手牌、棄牌堆移除1張基本牌，每移除1張牌，將等級不高於O的基本牌從牌庫放入棄牌堆，之後可以將身份變為瘋帽子";
	}
	if(CardID == 51){
	    (*C).cardname = "精神幻術";
	    (*C).cost = 2;
	    (*C).level = 2;
	    (*C).range = 0;
	    (*C).type = 1;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 2;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "防禦2，可以從手牌、棄牌堆移除1張基本牌，每移除1張牌，將等級不高於O的基本牌從牌庫放入棄牌堆，之後可以將身份變為瘋帽子";
	}
	if(CardID == 52){
	    (*C).cardname = "帽子戲法";
	    (*C).cost = 4;
	    (*C).level = 3;
	    (*C).range = 0;
	    (*C).type = 1;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 3;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "防禦3，可以從手牌、棄牌堆移除1張基本牌，每移除1張牌，將等級不高於O的基本牌從牌庫放入棄牌堆，之後可以將身份變為瘋帽子";
	}
	if(CardID == 53){
	    (*C).cardname = "詭異的敏捷";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 0;
	    (*C).type = 2;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "向一個方向移動至多1+O格，過程中穿過對手抽1張牌，之後可以將身份變成柴郡貓";
	}
	if(CardID == 54){
	    (*C).cardname = "詭異的隱蔽";
	    (*C).cost = 2;
	    (*C).level = 2;
	    (*C).range = 0;
	    (*C).type = 2;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "向一個方向移動至多2+O格，過程中穿過對手抽2張牌，之後可以將身份變成柴郡貓";
	}
	if(CardID == 55){
	    (*C).cardname = "詭異的詭異";
	    (*C).cost = 4;
	    (*C).level = 3;
	    (*C).range = 0;
	    (*C).type = 2;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "向一個方向移動至多3+O格，過程中穿過對手抽3張牌，之後可以將身份變成柴郡貓";
	}
	if(CardID == 56){
	    (*C).cardname = "無休止的派對";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 5;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "回合結束階段抽牌後，將手牌棄至四張，立即開始新回合，連續使用不可超過三次";
	}
	if(CardID == 57){
	    (*C).cardname = "精彩的奇妙日";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 5;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "直到本回合結束前，你的攻擊、防禦、移動牌的值+1，可與其他效果累積";
	}
	if(CardID == 58){
	    (*C).cardname = "遊戲盡在掌控";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 3;
	    (*C).type = 5;
	    (*C).power_generate = 0;
	    (*C).damage = 3;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "射程3 傷害3，將手牌和/或棄牌堆中的至多5張基本牌洗入對手牌庫";
	}
	if(CardID == 147){
	    (*C).cardname = "砍掉她的頭";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 0;
	    (*C).type = 6; // 蛻變屬性卡，為被動效果
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "蛻變1，當你的身份為紅心皇后時，每當你要通過攻擊技能將一張牌放入你的棄牌堆時，你可以將他加入手牌來代替";
	}

	if(CardID == 148){
	    (*C).cardname = "仙境降臨";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 0;
	    (*C).type = 6;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "蛻變1，當你的身份為瘋帽子時，當你將要通過一個防禦技能將牌放入你的棄牌堆時，你可以選擇將其中一張牌加入你的手牌來代替";
	}

	if(CardID == 149){
	    (*C).cardname = "我們全是瘋子";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 0;
	    (*C).type = 6;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "蛻變1，當你的身份為柴郡貓時，通過一個行動穿過對手或是對手穿過你時，可以抽1張牌";
	}

	if(CardID == 150){
	    (*C).cardname = "開始我的表演";
	    (*C).cost = 0;
	    (*C).level = 2;
	    (*C).range = 0;
	    (*C).type = 6;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "蛻變2，當你在回合結束階段抽取卡牌時，額外抽取一張牌，這張蛻變牌可以疊加";
	}


	//必殺技
	//蛻變牌
	
	//花木蘭_技能牌-----------------------------------------------------------------
	if(CardID == 59){ //不容小覷
		(*C).cardname = "不容小覷";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 1;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1+O\n你可以將對手放置到你的另一個相鄰的格子\n如果對手位於戰鬥軌道邊緣的格子\n你可以從他手牌中隨機棄掉一張牌";
	}
	if(CardID == 60){ //勢不可擋 x2
		(*C).cardname = "勢不可擋";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 2;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n射程1 傷害2+O\n你可以將對手放置到你的另一個相鄰的格子\n如果對手位於戰鬥軌道邊緣的格子\n你可以從他手牌中隨機棄掉一張牌";
	}
	if(CardID == 61){ //堅不可摧 x3
		(*C).cardname = "堅不可摧";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 3;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n射程1 傷害3+O\n你可以將對手放置到你的另一個相鄰的格子\n如果對手位於戰鬥軌道邊緣的格子\n你可以從他手牌中隨機棄掉一張牌";
	}
	if(CardID == 62){ //以靜制動
		(*C).cardname = "以靜制動";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).range = 0;
		(*C).type = 4;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "防禦O\n當你在本回合結束階段抽取卡牌時\n可以花費X點氣來額外抽取X張牌\nX至多為1";
	}
	if(CardID == 63){ //以柔克剛 x2
		(*C).cardname = "以柔克剛";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 0;
		(*C).type = 4;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n防禦O\n當你在本回合結束階段抽取卡牌時\n可以花費X點氣來額外抽取X張牌\nX至多為2";
	}
	if(CardID == 64){ //以弱勝強 x3
		(*C).cardname = "以弱勝強";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 0;
		(*C).type = 4;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n防禦O\n當你在本回合結束階段抽取卡牌時\n可以花費X點氣來額外抽取X張牌\nX至多為3";
	}
	if(CardID == 65){ //永不退縮
		(*C).cardname = "永不退縮";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 1;
		(*C).shield = 0;
		(*C).require_basic_card = 2;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1\n將對手擊退O格\n之後將你放置到一個與對手相鄰的格子\n如果對手位於戰鬥軌道的邊緣，你可以從他的手牌中隨機捨棄一張牌";
	}
	if(CardID == 66){ //毫不留情 x2
		(*C).cardname = "毫不留情";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 2;
		(*C).shield = 0;
		(*C).require_basic_card = 2;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n射程1 傷害2\n將對手擊退O格\n之後將你放置到一個與對手相鄰的格子\n如果對手位於戰鬥軌道的邊緣，你可以從他的手牌中隨機捨棄一張牌";
	}
	if(CardID == 67){ //絕不饒恕 x3
		(*C).cardname = "絕不饒恕";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 3;
		(*C).shield = 0;
		(*C).require_basic_card = 2;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n射程1 傷害3\n將對手擊退O格\n之後將你放置到一個與對手相鄰的格子\n如果對手位於戰鬥軌道的邊緣，你可以從他的手牌中隨機捨棄一張牌";
	}
	
	//必殺技
	if(CardID == 68){ //氣沖雲霄
		(*C).cardname = "氣沖雲霄";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0;
		(*C).type = 5;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "當你在本回合結束階段抽取卡牌時，額外抽取4張牌";
	}
	if(CardID == 69){ //直面混沌
		(*C).cardname = "直面混沌";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0;
		(*C).type = 5;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "將你放置到一個與對手相鄰的格子並立即獲得3點氣";
	}
	if(CardID == 70){ //雷霆一擊
		(*C).cardname = "雷霆一擊";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 1;
		(*C).type = 5;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程1\n立即花費你所有的氣來獲得傷害X\nX等於你花費的氣的量";
	}
	
	//蛻變牌
	if(CardID == 151){ //氣慣全身
		(*C).cardname = "氣慣全身";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0;
		(*C).type = 6;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "當你使用一個攻擊行動或攻擊技能時\n你可以花費X點氣來獲得傷害+X\nX至多為3";
	}
	if(CardID == 152){ //主宰命運
		(*C).cardname = "主宰命運";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0;
		(*C).type = 6;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "在你回合結束階段抽取卡牌之後\n你可以棄掉1張手牌，之後再抽取1張牌";
	}
	if(CardID == 153){ //長驅直入
		(*C).cardname = "長驅直入";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0;
		(*C).type = 6;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "當你使用一個移動行動時\n你可以花費X點氣\n向相同方向額外移動X格\nX至多為3";
	}
	if(CardID == 154){ //暴風前夕
		(*C).cardname = "暴風前夕";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0;
		(*C).type = 6;
		(*C).damage = 0;
		(*C).shield = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "在你的回合開始階段，獲得1點氣\n這張蛻變牌的效果可以累積";
	}


	//輝夜姬_技能牌-----------------------------------------------------------------
	if(CardID == 71){ //領悟的光芒
		(*C).cardname = "領悟的光芒";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 1;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1+O\n當前擁有3點防禦即獲得傷害+1";
	}
	if(CardID == 72){ //領悟的榮耀
		(*C).cardname = "領悟的榮耀";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 2;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n射程1 傷害2+O\n當前擁有3點防禦即獲得傷害+1";
	}
	if(CardID == 73){ //領悟的化身
		(*C).cardname = "領悟的化身";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 3;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n射程1 傷害3+O\n當前擁有3點防禦即獲得傷害+1";
	}

	if(CardID == 74){ //困惑的回聲
		(*C).cardname = "困惑的回聲";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).type = 4;
		(*C).shield = 1;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "防禦1+O\n展示你牌庫頂部的1張牌\n如果是一張防禦牌（不能是通用牌）則將他加入手牌\n否則，將他棄掉或是放回牌庫頂";
	}
	if(CardID == 75){ //久遠的回響
		(*C).cardname = "久遠的回響";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).type = 4;
		(*C).shield = 2;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "防禦2+O\n展示你牌庫頂部的2張牌\n如果是一張防禦牌（不能是通用牌）則將他加入手牌\n否則，將他棄掉或是以原本順序放回牌庫頂";
	}
	if(CardID == 76){ //神性的召喚
		(*C).cardname = "神性的召喚";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).type = 4;
		(*C).shield = 3;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "防禦3+O\n展示你牌庫頂部的3張牌\n如果是一張防禦牌（不能是通用牌）則將他加入手牌\n否則，將他棄掉或是以原本順序放回牌庫頂";
	}

	if(CardID == 77){ //專注的自省
		(*C).cardname = "專注的自省";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).range = 0;
		(*C).type = 4;
		(*C).damage = 1;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程O 傷害1\n你可以失去1點生命來移除你手牌或棄牌堆中的一張牌";
	}
	if(CardID == 78){ //頓悟的決心
		(*C).cardname = "頓悟的決心";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 0;
		(*C).type = 4;
		(*C).damage = 2;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n射程0 傷害2\n你可以失去1點生命來移除你手牌或棄牌堆中的一張牌\n持續：在你下個回合開始階段，如果對手超出射程4-O，對他造成4點傷害";
	}
	if(CardID == 79){ //痛徹的淨化
		(*C).cardname = "痛徹的淨化";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 0;
		(*C).type = 4;
		(*C).damage = 3;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n射程0 傷害3\n你可以失去1點生命來移除你手牌或棄牌堆中的一張牌\n持續：在你下個回合開始階段，如果對手超出射程4-O，對他造成6點傷害";
	}
	//必殺技
	if(CardID == 80){ //炙熱的竹刀
		(*C).cardname = "炙熱的竹刀";
		(*C).cost = 0;
		(*C).type = 5;
		(*C).cardcode = CardID;
		(*C).inf = "持續：直到你下個回合開始時，你不會承受傷害也不會失去生命";
	}
	if(CardID == 81){ //注定的審判
		(*C).cardname = "注定的審判";
		(*C).cost = 0;
		(*C).type = 5;
		(*C).shield = 6;
		(*C).cardcode = CardID;
		(*C).inf = "防禦6\n持續：在你下個回合的開始階段，如果對手的防禦低於你的防禦\n他失去X點生命，X等於你的防禦與他的防禦之間的差值";
	}
	if(CardID == 82){ //躁動的血性
		(*C).cardname = "躁動的血性";
		(*C).cost = 0;
		(*C).type = 5;
		(*C).damage = 3;
		(*C).cardcode = CardID;
		(*C).inf = "將對手放置到一個與你相鄰的格子並造成3點傷害\n持續：在你下個回合的開始階段，你可以將對手放置到一個與你相鄰的格子並對他造成3點傷害";
	}
	//蛻變牌
	if(CardID == 183){ //懲戒時刻
		(*C).cardname = "懲戒時刻";
		(*C).type = 6;
		(*C).cardcode = CardID;
		(*C).inf = "防禦上限+1\n每回合限一次\n在你的回合內，你可以將一張防禦牌當作一張相同等級的攻擊牌來使用";
	}
	if(CardID == 184){ //月下沉思
		(*C).cardname = "月下沉思";
		(*C).type = 6;
		(*C).cardcode = CardID;
		(*C).inf = "在你回合結束時 獲得防禦2";
	}
	if(CardID == 185){ //血色月光
		(*C).cardname = "血色月光";
		(*C).type = 6;
		(*C).cardcode = CardID;
		(*C).inf = "防禦值上限+1\n在你的回合的清理階段\n每重置3點防禦即抽取1張牌";
	}
	if(CardID == 186){ //靈性本能
		(*C).cardname = "靈性本能";
		(*C).type = 6;
		(*C).cardcode = CardID;
		(*C).inf = "防禦值上限+1\n每個自己的行動回合限一次：如果對手防禦低於你的防禦，你可已將他向任意方向移動一格";
	}

	//美人魚_技能牌-----------------------------------------------------------------
	//必殺技
	//蛻變牌

	//火柴女孩_技能牌-----------------------------------------------------------------
	//必殺技
	//蛻變牌
// 火柴牌本身
	if(CardID == MATCH_CARD_ID){
		(*C).cardname = "火柴";
		(*C).type = 3; // 視為通用牌，但有特殊規則
		(*C).level = 0; // 等級為0
		(*C).inf = "一張會觸發火柴女孩能力的特殊卡牌。";
		(*C).cardcode = CardID;
	}

	// 火柴女孩_技能牌-----------------------------------------------------------------
	if(CardID == 83){ // 虛幻的願望
		(*C).cardname = "虛幻的願望";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 1;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1+O\n你可以花費能量強化此傷害，每花費三點能量傷害+1";
	}
	if(CardID == 84){ // 隱密的期望
		(*C).cardname = "隱密的期望";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 2;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n射程1 傷害2+O\n你可以花費能量強化此傷害，每花費三點能量傷害+1";
	}
	if(CardID == 85){ // 無厭的奢望
		(*C).cardname = "無厭的奢望";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 3;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n射程1 傷害3+O\n你可以花費能量強化此傷害，每花費三點能量傷害+1";
	}
	if(CardID == 86){ // 惡魔的祭品
		(*C).cardname = "惡魔的祭品";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).range = 0;
		(*C).type = 4;
		(*C).shield = 1;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "防禦1\n可以失去X點生命來抽取X張牌，X至多為1";
	}
	if(CardID == 87){ // 惡魔的賭注
		(*C).cardname = "惡魔的賭注";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 0;
		(*C).type = 4;
		(*C).shield = 1;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n防禦1\n可以失去X點生命來抽取X張牌，X至多為2";
	}
	if(CardID == 88){ // 惡魔的契約
		(*C).cardname = "惡魔的契約";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 0;
		(*C).type = 4;
		(*C).shield = 1;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n防禦1\n可以失去X點生命來抽取X張牌，X至多為3";
	}
	if(CardID == 89){ // 失重的靈魂
		(*C).cardname = "失重的靈魂";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).range = 1;
		(*C).type = 4;
		(*C).damage = 1;
		(*C).require_basic_card = 2;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1\n你可以從對手棄牌堆中將至多O張火柴放回到火柴牌庫\n每以此放回一張，獲得1點能量";
	}
	if(CardID == 90){ // 虧欠的靈魂
		(*C).cardname = "虧欠的靈魂";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 2;
		(*C).type = 4;
		(*C).damage = 2;
		(*C).require_basic_card = 2;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 2\n射程2 傷害2\n你可以從對手棄牌堆中將至多O張火柴放回到火柴牌庫\n每以此放回一張，獲得2點能量，恢復1點生命";
	}
	if(CardID == 91){ // 殘破的靈魂
		(*C).cardname = "殘破的靈魂";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 3;
		(*C).type = 4;
		(*C).damage = 3;
		(*C).require_basic_card = 2;
		(*C).cardcode = CardID;
		(*C).inf = "購買費用 4\n射程3 傷害3\n你可以從對手棄牌堆中將至多O張火柴放回到火柴牌庫\n每以此放回一張，獲得3點能量，恢復2點生命";
	}

	// 必殺技
	if(CardID == 92){ // 地獄烈焰
		(*C).cardname = "地獄烈焰";
		(*C).type = 5;
		(*C).range = 1;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害X\nX為你當前擁有的能量數的一半（向上取整）";
	}
	if(CardID == 93){ // 厄運降臨
		(*C).cardname = "厄運降臨";
		(*C).type = 5;
		(*C).range = 3;
		(*C).cardcode = CardID;
		(*C).inf = "射程3\n棄掉對手牌庫頂部6張牌\n每有一張火柴 造成一點傷害";
	}
	if(CardID == 94){ // 貪婪詛咒
		(*C).cardname = "貪婪詛咒";
		(*C).type = 5;
		(*C).cardcode = CardID;
		(*C).inf = "將火柴牌庫至多三張火柴放至對手牌庫頂";
	}

	// 蛻變牌
	if(CardID == 155){ // 痛苦的儀式
		(*C).cardname = "痛苦的儀式";
		(*C).type = 6;
		(*C).cardcode = CardID;
		(*C).inf = "蛻變1(攻)\n當你使用攻擊行動或是攻擊技能時，\n可以從對手棄牌堆將至多一張火柴放回火柴牌庫，該次傷害+2";
	}
	if(CardID == 156){ // 火焰的捉弄
		(*C).cardname = "火焰的捉弄";
		(*C).type = 6;
		(*C).cardcode = CardID;
		(*C).inf = "蛻變2(攻)\n當對手使用一張火柴牌時 額外獲得一點能量\n火柴牌不能作為攻擊牌使用";
	}
	if(CardID == 157){ // 放縱的渴望
		(*C).cardname = "放縱的渴望";
		(*C).type = 6;
		(*C).cardcode = CardID;
		(*C).inf = "蛻變1(防)\n當你使用一個防禦技能時，\n可以從對手棄牌堆將至多1張火柴放回火柴牌庫來額外抽一張牌";
	}
	if(CardID == 158){ // 欲望的捉弄
		(*C).cardname = "欲望的捉弄";
		(*C).type = 6;
		(*C).cardcode = CardID;
		(*C).inf = "蛻變2(防)\n當對手使用一張火柴牌時 額外獲得一點能量\n火柴牌不能作為防禦牌使用";
	}
	if(CardID == 159){ // 魔鬼的凝視
		(*C).cardname = "魔鬼的凝視";
		(*C).type = 6;
		(*C).cardcode = CardID;
		(*C).inf = "蛻變1(移)\n在你的生命因承受傷害而減少後(非失去生命)\n可以從對手棄牌堆將至多1張火柴放回火柴牌庫\n向任意方向移動一格";
	}
	if(CardID == 160){ // 命運的捉弄
		(*C).cardname = "命運的捉弄";
		(*C).type = 6;
		(*C).cardcode = CardID;
		(*C).inf = "蛻變2(移)\n當對手使用一張火柴牌時 額外獲得一點能量\n火柴牌不能作為移動牌使用";
	}
	//桃樂絲_技能牌-----------------------------------------------------------------
	//必殺技
	//蛻變牌

	//山魯佐德_技能牌-----------------------------------------------------------------
	//必殺技
	//蛻變牌
	return	 0;
}
