#include "TwistedFables.h"
#include "Card.h"

int16_t Card_Define(int16_t CardID , card *C){// 
	//初始化
	
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
	
	//初始化完成
	
	
	if(CardID >= 1 && CardID <=12){ //基礎 攻擊牌 等級一
		(*C).cardname = "攻擊牌 等級一";
		(*C).cost = 1 ;
		(*C).level = 1;
		(*C).range = 1; //for attack 0 means its doesn't need range
		(*C).type = 0; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
		(*C).power_generate = 1;
		(*C).value = 1; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "射程1、傷害1 的攻擊，獲得1點能量";
	}
	
	if(CardID >= 13 && CardID <=24){ //基礎 攻擊牌 等級二
		(*C).cardname = "攻擊牌 等級二";
		(*C).cost = 3 ;
		(*C).level = 2;
		(*C).range = 1; //for attack 0 means its doesn't need range
		(*C).type = 0; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
		(*C).power_generate = 2;
		(*C).value = 2; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "射程1、傷害2 的攻擊，獲得2點能量";
	}
	
	if(CardID >= 25 && CardID <=36){ //基礎 攻擊牌 等級三
		(*C).cardname = "攻擊牌 等級三";
		(*C).cost = 6 ;
		(*C).level = 3;
		(*C).range = 1; //for attack 0 means its doesn't need range
		(*C).type = 0; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
		(*C).power_generate = 3;
		(*C).value = 3; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "射程1、傷害3 的攻擊，獲得3點能量";
	}
	
	if(CardID >= 37 && CardID <=48){ //基礎 防禦牌 等級一
		(*C).cardname = " 防禦牌 等級一";
		(*C).cost = 1 ;
		(*C).level = 1;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 1; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
		(*C).power_generate = 1;
		(*C).value = 1; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "獲得1點防禦，獲得1點能量";
	}
	
	if(CardID >= 49 && CardID <=60){ //基礎 防禦牌 等級二
		(*C).cardname = "防禦牌 等級二";
		(*C).cost = 3 ;
		(*C).level = 2;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 1; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
		(*C).power_generate = 2;
		(*C).value = 2; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "獲得2點防禦，獲得2點能量";
	}
	
	if(CardID >= 61 && CardID <=72){ //基礎 防禦牌 等級三
		(*C).cardname = "防禦牌 等級三";
		(*C).cost = 6 ;
		(*C).level = 3;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 1; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
		(*C).power_generate = 3;
		(*C).value = 3; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "獲得3點防禦，獲得3點能量";
	}
	
	if(CardID >= 73 && CardID <=84){ //基礎 移動牌 等級一
		(*C).cardname = "移動牌 等級一";
		(*C).cost = 1 ;
		(*C).level = 1;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 2; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
		(*C).power_generate = 1;
		(*C).value = 1; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "向任意方向移動1格（如果可能的話），獲得1點能量";
	}
	
	if(CardID >= 85 && CardID <=96){ //基礎 移動牌 等級二
		(*C).cardname = "移動牌 等級二";
		(*C).cost = 3 ;
		(*C).level = 2;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 2; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
		(*C).power_generate = 2;
		(*C).value = 2; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "向任意方向移動2格（如果可能的話），獲得2點能量";
	}
	
	if(CardID >= 97 && CardID <=108){ //基礎 移動牌 等級三
		(*C).cardname = "移動牌 等級三";
		(*C).cost = 6 ;
		(*C).level = 3;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 2; // 0)attack 1)defend 2)movement 3)skills 4)Ult 5)passive
		(*C).power_generate = 3;
		(*C).value = 3; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "向任意方向移動3格（如果可能的話），獲得3點能量";
	}
	
	if(CardID >= 108 && CardID <=120){ //基礎 通用牌 等級一
		(*C).cardname = "通用牌 等級一";
		(*C).cost = 1 ;
		(*C).level = 1;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 3; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 1;
		(*C).value = 1; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 0; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "可以當作 攻擊、防禦、移動的等級一";
	}
	
	if(CardID == 121){ //快速射擊
		(*C).cardname = "快速射擊";
		(*C).cost = 0 ;
		(*C).level = 1;
		(*C).range = 1; //for attack 0 means its doesn't need range
		(*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).damage = 1; // for example value = 1 on attack => deal 1 damage
		(*C).require_basic_card = 1; // 0 means do not requires
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1+O";
	}
	
	if(CardID >= 122 && CardID <= 123){ //精準射擊 x2
		(*C).cardname = "精準射擊";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 2;//for attack 0 means its doesn't need range
		(*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).damage = 2;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "射程2 傷害2+O";
	}
	if(CardID == 124){ //過載燃燒
		(*C).cardname = "過載燃燒";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0;//for attack 0 means its doesn't need range
		(*C).type = 6; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).value = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "當你使用一個移動技能或是攻擊技能時\n可以捨棄至多一張技能牌來獲得傷害X\nX為你捨棄的技能牌等級";
	}
	if(CardID >= 125 && CardID <= 127){ //致命狙擊 x3
		(*C).cardname = "致命狙擊";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 3; //for attack 0 means its doesn't need range
		(*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).damage = 3;
		(*C).require_basic_card = 1;
		(*C).cardcode = CardID;
		(*C).inf = "射程3 傷害3+O";
	}
	if(CardID == 128){ //板載緩存（攻擊蛻變2）
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
	if(CardID == 129){ //能量護盾
		(*C).cardname = "能量護盾";
		(*C).cost = 0;
		(*C).level = 1;
		(*C).range = 1; //for attack 0 means its doesn't need range
		(*C).type = 1; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).shield = 1;
		(*C).damage = 1;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程1 傷害1 防禦1\n持續：在你下個回合的開始階段 如果防禦不為0\n對射程1內的對手造成 2點傷害";
	}
	if(CardID >= 130 && CardID <= 131){ //電流護盾 x2
		(*C).cardname = "電流護盾";
		(*C).cost = 2;
		(*C).level = 2;
		(*C).range = 2; //for attack 0 means its doesn't need range
		(*C).type = 1; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).shield = 1;
		(*C).damage = 2;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程2 傷害2 防禦1\n持續：在你下個回合的開始階段 如果防禦不為0\n對射程2內的對手造成 4點傷害";
	}
	if(CardID == 132){ //兜帽系統
		(*C).cardname = "兜帽系統";
		(*C).cost = 0;
		(*C).level = 0;
		(*C).range = 0; //for attack 0 means its doesn't need range
		(*C).type = 6; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).value = 0;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "每當對手對你造成傷害時\n可以捨棄至多一張技能牌來將傷害減少X\nX為你捨棄的技能牌等級";
	}
	if(CardID >= 133 && CardID <= 135){ //終極護盾 x3
		(*C).cardname = "終極護盾";
		(*C).cost = 4;
		(*C).level = 3;
		(*C).range = 3; //for attack 0 means its doesn't need range
		(*C).type = 1; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
		(*C).power_generate = 0;
		(*C).shield = 1;
		(*C).damage = 3;
		(*C).require_basic_card = 0;
		(*C).cardcode = CardID;
		(*C).inf = "射程3 傷害3 防禦1\n持續：在你下個回合的開始階段 如果防禦不為0\n對射程3內的對手造成 6點傷害";
	}
	if(CardID == 136){ //板載緩存（防禦蛻變2）
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
	if(CardID == 137){ //彈道噴射
	    (*C).cardname = "彈道噴射";
	    (*C).cost = 0;
	    (*C).level = 1;
	    (*C).range = 1; //for attack 0 means its doesn't need range
	    (*C).type = 4; // 0)attack 1)defend 2)movement 3) wild 4)skills 5)Ult 6)passive
	    (*C).power_generate = 0;
	    (*C).damage = 1;
	    (*C).shield = 0;
	    (*C).require_basic_card = 1;
	    (*C).cardcode = CardID;
	    (*C).inf = "將對手擊退至多O格";
	}
	if(CardID >= 138 && CardID <= 139){ //火力噴射 x2
	    (*C).cardname = "火力噴射";
	    (*C).cost = 2;
	    (*C).level = 2;
	    (*C).range = 2;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 2;
	    (*C).shield = 0;
	    (*C).require_basic_card = 1;
	    (*C).cardcode = CardID;
	    (*C).inf = "將對手擊退至多O格";
	}
	if(CardID == 140){ //變異感應
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
	if(CardID >= 141 && CardID <= 143){ //暴怒噴射 x3
	    (*C).cardname = "暴怒噴射";
	    (*C).cost = 4;
	    (*C).level = 3;
	    (*C).range = 3;
	    (*C).type = 4;
	    (*C).power_generate = 0;
	    (*C).damage = 3;
	    (*C).shield = 0;
	    (*C).require_basic_card = 1;
	    (*C).cardcode = CardID;
	    (*C).inf = "將對手擊退至多O格";
	}
	if(CardID == 144){ //板載緩存（移動）
	    (*C).cardname = "板載緩存";
	    (*C).cost = 0;
	    (*C).level = 0;
	    (*C).range = 0;
	    (*C).type = 6;
	    (*C).power_generate = 0;
	    (*C).damage = 0;
	    (*C).shield = 0;
	    (*C).require_basic_card = 0;
	    (*C).cardcode = CardID;
	    (*C).inf = "行動回合可存放一張手牌（最多一張），不進棄牌堆，可取回";
	}

	// 必殺技
	if(CardID == 145){ //餓狼吞噬
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
	if(CardID == 146){ //系統入侵
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
	if(CardID == 147){ //復仇之雨
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

}
