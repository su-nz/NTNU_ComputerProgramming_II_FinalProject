#include "TwistedFables.h"


int8_t add_card_to_starting(player *P,int16_t card_id  ,int16_t combo_cardid ,int16_t lv){
	P->starting[P->starting_size] = card_id;
	P->combo_basic[P->starting_size] = combo_cardid;
	P->starting_lv[P->starting_size] = lv;
	P->starting_size++;

	return 0;
}


int8_t startingskill(player* you ,player *P,int16_t card_id,int16_t lv ){
	if(card_id == 14){
		if(you->armor !=0 ){
			if(range_counter(you,P,1) == 1){
				deal_damage(you, P, 2);
			}
		}
	}else if(card_id == 15){
		if(you->armor !=0 ){
			if(range_counter(you,P,2) == 1){
				deal_damage(you, P, 4);
			}
		}
	}else if(card_id == 16){
		if(you->armor !=0 ){
			if(range_counter(you,P,3) == 1){
				deal_damage(you, P, 6);
			}
		}
	}else if(card_id == 45){
		draw_card( 6-you->sleep_hp, you);
		you->sleep_hp = -2;
	}
	return 0;
}


int8_t use_Ult(player* you,player *P,int16_t card_id , int8_t *damage_output , int8_t *armor_output, int8_t mode ,vector (*skillBuyDeck)[3],vector (*basicBuyDeck)[3],int8_t BotOn){
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
				if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							cc = botChoice(0,1,3,0);
						}else{
							scanf("%hhd",&cc);
				}
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
		
		if(you->RedUlt.action == 0){
			*damage_output = you->RedUlt.atk;
			*armor_output = you->RedUlt.def;
		}else if(you->RedUlt.action == 1){
			use_skill(you,P,you->RedUlt.cardid , damage_output , armor_output, you->RedUlt.spel_buy ,you->RedUlt.bas_buy ,  mode,BotOn);
		}else if(you->RedUlt.action == 2){
			if(you->Redhoodsave[0]==-2 ||you->Redhoodsave[1]==-2  ||you->Redhoodsave[2]==-2 ){
				Redhoodsavefile(you,BotOn);
			}
		}else if(you->RedUlt.action == 3){
			card cardtemp1;
			if(skillBuyDeck[P->num][0].SIZE >0)Card_Define(skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1], &cardtemp1);
			card cardtemp2;
			if(skillBuyDeck[P->num][1].SIZE >0)Card_Define(skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1], &cardtemp2);
			card cardtemp3;
			if(skillBuyDeck[P->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp3);
			int cc = P->RedUlt.spel_buy;
			
			switch(cc){
				case 1: // 攻擊
					if(P->power < cardtemp1.cost){
						printf("你的能量不夠\n") ;
						
					}else if(skillBuyDeck[P->num][0].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1]);
						skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1] = 0;
						skillBuyDeck[P->num][0].SIZE--;
						P->power -=cardtemp1.cost;
						Card_Define(skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1], &cardtemp1);
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
						printf("你的能量不夠\n") ;
						
					}else if(skillBuyDeck[P->num][1].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
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
					
				break;
				
				case 3: // 移動
					if(P->power < cardtemp3.cost){
						printf("你的能量不夠\n") ;
						
					}else if(skillBuyDeck[P->num][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&P->discard, skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1]);
						skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1] = 0;
						skillBuyDeck[P->num][2].SIZE--;
						P->power -=cardtemp3.cost;
						Card_Define(skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1], &cardtemp3);
						if(cardtemp3.cost == 0){
							P->passive[P->passive_n] = skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][2].SIZE-1];
							skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1] = 0;
							skillBuyDeck[P->num][2].SIZE--;
							if(skillBuyDeck[P->num][2].SIZE <=0) skillBuyDeck[P->num][2].SIZE = 0;
							P->passive_n++;
							if(skillBuyDeck[P->num][2].SIZE >0)Card_Define(skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1], &cardtemp2);
						}
						printf_skill_shop(P->num);
					}
					
				break;
				
				
				default:
					printf("不存在此選項\n");
				break;
			}
		}else if(you->RedUlt.action == 4){
			int cc = P->RedUlt.bas_buy;
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
						//printf_basic_shop();
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
						//printf_basic_shop();
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
						//printf_basic_shop();
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
						//printf_basic_shop();
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
						//printf_basic_shop();
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
						//printf_basic_shop();
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
						//printf_basic_shop();
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
						//printf_basic_shop();
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
						//printf_basic_shop();
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
						//printf_basic_shop();
					}
				
				break;
				
				default:
					printf("不存在此選項\n");
				break;
			}
			
		}else{
			printf("無複製對象\n");
		}
	
	
	
	
	}else if(card_id == 22){
		int times=0;
		while(1){
			printf("\n請輸入你要擊退的距離(0-3)\n>");
			
			if(BotOn == 1 && (you->num == 1 || you->num == 3) ){
							times = botChoice(0,0,3,0);
						}else{
							scanf("%d",&times);
							getchar();
				}
			
			if(times >= 0  && times <= 3){
				break;
			}else{
				printf("你的範圍錯誤\n");
			}
		}
		*damage_output = 3;
		for(int i = 0 ; i < times ; i++){
			if(P->coordinate + way <= Right_MAX  && P->coordinate + way > 0 ){
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
				
				if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							select = botChoice(0,1,P->hands ,0);
						}else{
							scanf("%hhd",&select);
				}
				if(select > P->hands || select <= 0 ){
					printf("沒有這張卡！\n");
				}else{
					discard_card_from_hand(P,select-1);
					break;
				}
			}
			left--;
			
		}
		
	}else if(card_id == 44){
		you->sleep =0;
		you->sleep_token+=3;
	}else if(card_id == 45){
		you->sleep_hp = 6;
		add_card_to_starting(you,45,0,0);
	}else if(card_id == 46){
		you->sleep =1;
		regenerate_hp(you,you->sleep_token);
		remove_sleeptoken(you,you->sleep_token);
	}

	if (card_id == 32) { // 七蛇之怒
        int8_t poison_count = 0;
        printf("對手的棄牌堆中有：\n");
        for (int i = 0; i < P->discard.SIZE; i++) {
            if (P->discard.array[i] == POISON_CARD_ID) {
                poison_count++;
            }
        }
        printf("%d 張中毒牌。\n", poison_count);
        *damage_output = poison_count;
    } 
    else if (card_id == 33) { // 魔鏡之雨
        *damage_output = 3;
        printf("對手棄掉了所有手牌，並重新抽取 4 張。\n");
        discard_all_hands(P);
        draw_card(4, P);
    }
    else if (card_id == 34) { // 醞釀之災
        *damage_output = 3;
        // 這個效果比較複雜，需要額外的UI互動讓玩家選擇。
        // 作為初步實作，我們先印出提示訊息
		//(選擇棄牌堆卡牌洗回牌庫的功能待實作)。
        printf("發動了醞釀之災！\n");
        // 可以在此處呼叫一個未來的函式，如: discard_to_deck_interactive(you, P, 3);
    }
	

	return 0;
}


int8_t use_skill(player* you,player *P,int16_t card_id , int8_t *damage_output , int8_t *armor_output, int8_t lv , int8_t combo_cardid , int8_t mode,int8_t BotOn){
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
			if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							times = botChoice(0,0,lv,0);
						}else{
							scanf("%d",&times);
							getchar();
				}
			
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
			if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							times = botChoice(0,0,lv,0);
						}else{
							scanf("%d",&times);
							getchar();
				}
			
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
			if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							times = botChoice(0,0,lv,0);
						}else{
							scanf("%d",&times);
							getchar();
				}
			
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
		
	}else if(card_id == 35){
		int dama=0;
		while(1){
			printf("\n請輸入獻祭的血量(0-1)\n>");
			
			if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							dama = botChoice(0,0,1,0);
						}else{
							scanf("%d",&dama);
							getchar();
				}
			
			if(dama >= 0  && dama <= 1){
				break;
			}else{
				printf("你的範圍錯誤\n");
			}
		}
		*damage_output = dama+lv*1;
		
	}else if(card_id == 36){
		int dama=0;
		while(1){
			printf("\n請輸入獻祭的血量(0-2)\n>");
			if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							dama = botChoice(0,0,2,0);
						}else{
							scanf("%d",&dama);
							getchar();
				}
			
			if(dama >= 0  && dama <= 2){
				break;
			}else{
				printf("你的範圍錯誤\n");
			}
		}
		*damage_output = dama+lv*2;
		
	}else if(card_id == 37){
		int dama=0;
		while(1){
			printf("\n請輸入獻祭的血量(0-3)\n>");
			if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							dama = botChoice(0,0,3,0);
						}else{
							scanf("%d",&dama);
							getchar();
				}
			
			if(dama >= 0  && dama <= 3){
				break;
			}else{
				printf("你的範圍錯誤\n");
			}
		}
		*damage_output = dama+lv*3;
		
	}else if(card_id == 38){
		you-> atk_bb1 += lv;
		int dama=0;
		if(you->sleep == 0){
			while(1){
				printf("\n請輸入要使用的沉睡Token數量(0-3)\n>");
				if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							dama = botChoice(0,0,3,0);
						}else{
							scanf("%d",&dama);
							getchar();
				}
				
				if(dama >= 0  && dama <= 3 && you->sleep_token >= dama){
					remove_sleeptoken(you,dama);
					you-> atk_bb1 += dama;
					break;
				}else if(you->sleep_token < dama){
					printf("你沒有足夠的Token\n");
				}else {
					printf("你的範圍錯誤\n");
				}
			}
		}
		
		
		
	}else if(card_id == 39){
		you-> atk_bb2 += lv;
		int dama=0;
		if(you->sleep == 0){
			while(1){
				printf("\n請輸入要使用的沉睡Token數量(0-3)\n>");
				if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							dama = botChoice(0,0,3,0);
						}else{
							scanf("%d",&dama);
							getchar();
				}
				
				if(dama >= 0  && dama <= 3 && you->sleep_token >= dama){
					remove_sleeptoken(you,dama);
					you-> atk_bb2 += dama;
					break;
				}else if(you->sleep_token < dama){
					printf("你沒有足夠的Token\n");
				}else {
					printf("你的範圍錯誤\n");
				}
			}
		}
	}else if(card_id == 40){
		you-> atk_bb3 += lv;
		int dama=0;
		if(you->sleep == 0){
			while(1){
				printf("\n請輸入要使用的沉睡Token數量(0-3)\n>");
				if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							dama = botChoice(0,0,3,0);
						}else{
							scanf("%d",&dama);
							getchar();
				}
				
				if(dama >= 0  && dama <= 3 && you->sleep_token >= dama){
					remove_sleeptoken(you,dama);
					you-> atk_bb3 += dama;
					break;
				}else if(you->sleep_token < dama){
					printf("你沒有足夠的Token\n");
				}else {
					printf("你的範圍錯誤\n");
				}
			}
		}
	}else if(card_id == 41 || card_id == 42 || card_id == 43 ){
		int dama=0;
		if(you->sleep == 0){
			while(1){
				printf("\n請輸入要使用的沉睡Token數量(0-3)\n>");
				if(BotOn == 1 && (P->num == 1 || P->num == 3) ){
							dama = botChoice(0,0,3,0);
						}else{
							scanf("%d",&dama);
							getchar();
				}
				
				if(dama >= 0  && dama <= 3 && you->sleep_token >= dama){
					remove_sleeptoken(you,dama);
					you-> atk_bb3 += dama;
					break;
				}else if(you->sleep_token < dama){
					printf("你沒有足夠的Token\n");
				}else {
					printf("你的範圍錯誤\n");
				}
			}
		}
		*damage_output = lv + dama;
		for(int i = 0 ; i < lv ; i++){
			if(P->coordinate - way <= Right_MAX  && P->coordinate - way > 0 && P->coordinate - way != you->coordinate - way){
				P->coordinate -= way;
			}
		}
	}
	
	if(card_id >= 23 && card_id <= 31) { // 白雪公主的技能牌
        *damage_output = lv; // 大部分技能的傷害都等於搭配的基礎牌等級

        switch(card_id) {
            case 23: // 水晶碎片
            case 24: // 水晶漩渦
            case 25: // 水晶風暴
                discard_from_top_of_deck(P, lv);
                break;

            case 26: // 玷污的恩惠
            case 27: // 玷污的盛筵
            case 28: // 玷污的狂歡
                add_poison_to_discard(you, P, lv);
                break;

            case 29: // 破碎的幻想
            case 30: // 破碎的現實
            case 31: // 破碎的命運
                move_adjacent_to_player(you, P);
                break;
        }
    }
	return 0;
}
