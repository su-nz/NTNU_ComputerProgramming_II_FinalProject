#include "TwistedFables.h"


int8_t add_card_to_starting(player *P,int16_t card_id  ,int16_t combo_cardid ){
	P->starting[P->starting_size] = card_id;
	P->combo_basic[P->starting_size];
	P->starting_size++;
}

int8_t startingskill(player *P,int16_t card_id,int16_t lv ){
	if(card_id == 11){
	
	}
}


int8_t use_skill(player* you,player *P,int16_t card_id , int8_t *damage_output , int8_t *armor_output, int8_t lv , int8_t combo_cardid , int8_t mode){
	int8_t Right_MAX;
	if(mode ==1){
		Right_MAX = 9;
	}else{
		Right_MAX = 11;
	}
	
	int8_t way = 0;
	if(you->coordinate - P->coordinate < 0){
		way = 1;//右	
	}else{
		way = -1;//左	
	}
	
	//小紅帽
	
	if(card_id == 11){
		*damage_output = 1+lv;
		*armor_output = 0;
	}else if(card_id == 12){
		*damage_output = 2+lv;
		*armor_output = 0;
	}else if(card_id == 13){
		*damage_output = 3+lv;
		*armor_output = 0;
	}else if(card_id == 14){
		*damage_output = 1;
		*armor_output = lv;
		add_card_to_starting(P,14,combo_cardid);
	}else if(card_id == 15){
		*damage_output = 2;
		*armor_output = lv;
		add_card_to_starting(P,15,combo_cardid);
	}else if(card_id == 16){
		*damage_output = 3;
		*armor_output = lv;
		add_card_to_starting(P,16,combo_cardid);
	}else if(card_id == 17){
		*damage_output = 1;
		for(int i = 0 ; i < lv ; i++){
			if(P->coordinate + way <= Right_MAX && P->coordinate + way > 0){
				P->coordinate += way;
			}
		}
		
	}else if(card_id == 18){
		*damage_output = 2;
		for(int i = 0 ; i < lv ; i++){
			if(P->coordinate + way <= Right_MAX  && P->coordinate + way > 0){
				P->coordinate += way;
			}
		}
		
	}else if(card_id == 19){
		*damage_output = 3;
		for(int i = 0 ; i < lv ; i++){
			if(P->coordinate + way <= Right_MAX  && P->coordinate + way > 0){
				P->coordinate += way;
			}
		}
		
	}
	return 0;
}
