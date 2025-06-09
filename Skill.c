#include "TwistedFables.h"


int8_t add_card_to_starting(player *P,int16_t card_id  ,int16_t combo_cardid ,int16_t lv){
	P->starting[P->starting_size] = card_id;
	P->combo_basic[P->starting_size] = combo_cardid;
	P->starting_lv[P->starting_size] = lv;
	P->starting_size++;
}


int8_t startingskill(player* you ,player *P,int16_t card_id,int16_t lv ){
	if(card_id == 14){
		if(you->armor !=0 ){
			if(range_counter(you,P,1) == 1){
				deal_damage(P,2);
			}
		}
	}else if(card_id == 15){
		if(you->armor !=0 ){
			if(range_counter(you,P,2) == 1){
				deal_damage(P,4);
			}
		}
	}else if(card_id == 16){
		if(you->armor !=0 ){
			if(range_counter(you,P,3) == 1){
				deal_damage(P,6);
			}
		}
	}
}


int8_t use_Ult(player* you,player *P,int16_t card_id , int8_t *damage_output , int8_t *armor_output, int8_t mode ,vector (*skillBuyDeck)[3]){
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
	
	if(card_id == 20){
		system("clear");
		
		card cardtemp1;
		if(skillBuyDeck[P->num][0].SIZE >0)Card_Define(skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1], &cardtemp1);
		card cardtemp2;
		if(skillBuyDeck[P->num][1].SIZE >0)Card_Define(skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1], &cardtemp2);
		card cardtemp3;
		if(skillBuyDeck[P->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp3);
		
		printf_skill_shop(you->num);
		
				if(skillBuyDeck[you->num][0].SIZE == 0 && skillBuyDeck[you->num][1].SIZE == 0  && skillBuyDeck[you->num][2].SIZE == 0 ){
					return 0;
				}
				int8_t cc =-1;
				printf("請輸入你要升級的技能：") ;
				scanf("%hhd",&cc);
				switch(cc){
					case 1: // 攻擊
						if(skillBuyDeck[you->num][0].SIZE == 0){
							printf("此卡已經賣光了\n") ;
							
						}else{
							pushbackVector(&you->discard, skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1]);
							skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1] = 0;
							skillBuyDeck[you->num][0].SIZE--;
							if(skillBuyDeck[you->num][0].SIZE != 0){
									if(skillBuyDeck[P->num][0].SIZE >0)Card_Define(skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1], &cardtemp1);
								
								if(cardtemp1.cost == 0){
									you->passive[you->passive_n] = skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1];
									skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1] = 0;
									skillBuyDeck[you->num][0].SIZE--;
									you->passive_n++;
									if(skillBuyDeck[P->num][0].SIZE >0)Card_Define(skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1], &cardtemp1);
								}
							}
							if(skillBuyDeck[you->num][0].SIZE != 0){
								if(skillBuyDeck[P->num][0].SIZE >0)Card_Define(skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1], &cardtemp1);
								pushbackVector(&you->discard, skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1]);
								skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1] = 0;
								skillBuyDeck[you->num][0].SIZE--;
							}
							
							if(skillBuyDeck[you->num][0].SIZE != 0){
									if(skillBuyDeck[P->num][0].SIZE >0)Card_Define(skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1], &cardtemp1);
								
								if(cardtemp1.cost == 0){
									you->passive[you->passive_n] = skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1];
									skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1] = 0;
									skillBuyDeck[you->num][0].SIZE--;
									you->passive_n++;
									if(skillBuyDeck[P->num][0].SIZE >0)Card_Define(skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1], &cardtemp1);
								}
							}
						}
						
					break;
					
					case 2: // 防禦
						if(skillBuyDeck[you->num][1].SIZE == 0){
							printf("此卡已經賣光了\n") ;
							
						}else{
							pushbackVector(&you->discard, skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1]);
							skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1] = 0;
							skillBuyDeck[you->num][1].SIZE--;
							if(skillBuyDeck[you->num][1].SIZE != 0){
								if(skillBuyDeck[P->num][1].SIZE >0)Card_Define(skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1], &cardtemp2);
								if(cardtemp2.cost == 0){
									you->passive[you->passive_n] = skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][0].SIZE-1];
									skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1] = 0;
									skillBuyDeck[you->num][1].SIZE--;
									you->passive_n++;
									if(skillBuyDeck[P->num][1].SIZE >0)Card_Define(skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1], &cardtemp2);
								}
							}
							if(skillBuyDeck[you->num][1].SIZE != 0){
								if(skillBuyDeck[P->num][1].SIZE >0)Card_Define(skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1], &cardtemp2);
								pushbackVector(&you->discard, skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1]);
								skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1] = 0;
								skillBuyDeck[you->num][1].SIZE--;
							}
							
							if(skillBuyDeck[you->num][1].SIZE != 0){
								if(skillBuyDeck[P->num][1].SIZE >0)Card_Define(skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1], &cardtemp2);
								if(cardtemp2.cost == 0){
									you->passive[you->passive_n] = skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][0].SIZE-1];
									skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1] = 0;
									skillBuyDeck[you->num][1].SIZE--;
									you->passive_n++;
									if(skillBuyDeck[P->num][1].SIZE >0)Card_Define(skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1], &cardtemp2);
								}
							}
						}
						
					break;
					
					case 3: // 移動
						if(skillBuyDeck[you->num][2].SIZE == 0){
							printf("此卡已經賣光了\n") ;
							
						}else{
							pushbackVector(&you->discard, skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1]);
							skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1] = 0;
							skillBuyDeck[you->num][2].SIZE--;
							if(skillBuyDeck[you->num][2].SIZE != 0){
								if(skillBuyDeck[P->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp3);
								if(cardtemp3.cost == 0){
									you->passive[you->passive_n] = skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][0].SIZE-1];
									skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1] = 0;
									skillBuyDeck[you->num][2].SIZE--;
									you->passive_n++;
									if(skillBuyDeck[P->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp2);
								}
							}
							if(skillBuyDeck[you->num][2].SIZE != 0){
								if(skillBuyDeck[P->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp3);
								pushbackVector(&you->discard, skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1]);
								skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1] = 0;
								skillBuyDeck[you->num][2].SIZE--;
							}
							
							if(skillBuyDeck[you->num][2].SIZE != 0){
								if(skillBuyDeck[P->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp3);
								if(cardtemp3.cost == 0){
									you->passive[you->passive_n] = skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][0].SIZE-1];
									skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1] = 0;
									skillBuyDeck[you->num][2].SIZE--;
									you->passive_n++;
									if(skillBuyDeck[P->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp2);
								}
							}
						}
						
					break;
				
					
					default:
						printf("不存在此選項\n");
					break;
					
				}
				
			
		
		
		return 0;
	}else if(card_id == 21){
	
	}else if(card_id == 22){
		int times=0;
		while(1){
			printf("\n請輸入你要擊退的距離(0-3)\n>");
			scanf("%d",&times);
			getchar();
			if(times >= 0  && times <= 3){
				break;
			}else{
				printf("你的範圍錯誤\n");
			}
		}
		*damage_output = 3;
		for(int i = 0 ; i < times ; i++){
			if(P->coordinate + way <= Right_MAX  && P->coordinate + way > 0){
				P->coordinate += way;
			}
		}
		
		int left = 3;
		for(int i = 0 ; i < 3 ; i++){
			if(P->hands == 0) break;
			
			while(1){
				int8_t select=0;
				system("clear");
				printf("%s請你棄置3張牌，還剩下%d張牌要棄置\n",P->charname,left);
				print_hands(P);
				printf("請輸入你要棄置的牌\n>");
				printf("輸入數字：");
				scanf("%hhd",&select);
				if(select > P->hands || select <= 0 ){
					printf("沒有這張卡！\n");
				}else{
					discard_card_from_hand(P,select-1);
					break;
				}
			}
			left--;
			
		}
		
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
		add_card_to_starting(you,14,combo_cardid,lv);
	}else if(card_id == 15){
		*damage_output = 2;
		*armor_output = lv;
		add_card_to_starting(you,15,combo_cardid,lv);
	}else if(card_id == 16){
		*damage_output = 3;
		*armor_output = lv;
		add_card_to_starting(you,16,combo_cardid,lv);
	}else if(card_id == 17){
		int times=0;
		while(1){
			printf("\n請輸入你要擊退的距離(0-%d)\n>",lv);
			scanf("%d",&times);
			getchar();
			if(times >= 0  && times <= lv){
				break;
			}else{
				printf("你的範圍錯誤\n");
			}
		}
		*damage_output = 1;
		for(int i = 0 ; i < times ; i++){
			if(P->coordinate + way <= Right_MAX  && P->coordinate + way > 0){
				P->coordinate += way;
			}
		}
		
	}else if(card_id == 18){
		int times=0;
		while(1){
			printf("\n請輸入你要擊退的距離(0-%d)\n>",lv);
			scanf("%d",&times);
			getchar();
			if(times >= 0  && times <= lv){
				break;
			}else{
				printf("你的範圍錯誤\n");
			}
		}
		*damage_output = 2;
		for(int i = 0 ; i < times ; i++){
			if(P->coordinate + way <= Right_MAX  && P->coordinate + way > 0){
				P->coordinate += way;
			}
		}
		
	}else if(card_id == 19){
		int times=0;
		while(1){
			printf("\n請輸入你要擊退的距離(0-%d)\n>",lv);
			scanf("%d",&times);
			getchar();
			if(times >= 0  && times <= lv){
				break;
			}else{
				printf("你的範圍錯誤\n");
			}
		}
		*damage_output = 3;
		for(int i = 0 ; i < times ; i++){
			if(P->coordinate + way <= Right_MAX  && P->coordinate + way > 0){
				P->coordinate += way;
			}
		}
		
	}
	return 0;
}
