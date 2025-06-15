#include "TwistedFables.h"


int8_t add_card_to_starting(player *P,int16_t card_id  ,int16_t combo_cardid ,int16_t lv){
	P->starting[P->starting_size] = card_id;
	P->combo_basic[P->starting_size] = combo_cardid;
	P->starting_lv[P->starting_size] = lv;
	P->clone[P->starting_size]=0;
	P->starting_size++;

	return 0;
}

bool is_kaguya_defense_card(int id){
    return id == 74 || id == 75 || id == 76;
}

void remove_card_interactively(player* p) {
    if (p->hands <= 0) return;

    printf("請選擇要移除的手牌（0 ~ %d）：\n", p->hands - 1);
    for (int i = 0; i < p->hands; i++) {
        printf("[%d] 卡片名稱: %s (ID: %d)\n", i, p->hands_card[i].cardname, p->hands_card[i].cardcode);
    }

    int select = 0;
    scanf("%d", &select);
    if (select < 0 || select >= p->hands) {
        printf("選擇錯誤，取消移除。\n");
        return;
    }

    int removed_id = p->hands_card[select].cardcode;
    remove_card_from_hand(p, select);
    printf("你移除了卡片 ID %d。\n", removed_id);
}

void remove_card_from_deck_index(player* p, int index) {
    if (index < 0 || index >= p->deck.SIZE) return;
    for (int i = index; i < p->deck.SIZE - 1; i++) {
        p->deck.array[i] = p->deck.array[i + 1];
    }
    p->deck.SIZE--;
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
	else if(card_id == 78){
	    if(range_counter(you, P, 4) == 0){
		deal_damage(you, P, 4);
	    }
	}
	else if(card_id == 79){
	    if(range_counter(you, P, 4) == 0){
		deal_damage(you, P, 6);
	    }
	}
	else if(card_id == 82){
	    move_adjacent_to_player(P, you);
	    deal_damage(you, P, 3);
	}else if(card_id == 154){ // 暴風前夕
        if(you->qi < 12) { // 假設氣的上限是12
            you->qi++;
            printf("暴風前夕觸發，%s 獲得1點氣，目前：%d\n", you->charname, you->qi);
        }
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
								if(skillBuyDeck[you->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp3);
								if(cardtemp3.cost == 0){
									you->passive[you->passive_n] = skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][0].SIZE-1];
									skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1] = 0;
									skillBuyDeck[you->num][2].SIZE--;
									you->passive_n++;
									if(skillBuyDeck[you->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp2);
								}
							}
							if(skillBuyDeck[you->num][2].SIZE != 0){
								if(skillBuyDeck[you->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp3);
								pushbackVector(&you->discard, skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1]);
								skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1] = 0;
								skillBuyDeck[you->num][2].SIZE--;
							}
							
							if(skillBuyDeck[you->num][2].SIZE != 0){
								if(skillBuyDeck[you->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp3);
								if(cardtemp3.cost == 0){
									you->passive[you->passive_n] = skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][0].SIZE-1];
									skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1] = 0;
									skillBuyDeck[you->num][2].SIZE--;
									you->passive_n++;
									if(skillBuyDeck[you->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp2);
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
		int8_t a , b =-100;
			use_skill(you,P,you->RedUlt.cardid , &a ,& b, you->RedUlt.spel_buy ,you->RedUlt.bas_buy ,  mode,BotOn);
			you->clone[you->starting_size-1]=1;
			*damage_output = you->RedUlt.atk;
			*armor_output = you->RedUlt.def;
		}else if(you->RedUlt.action == 2){
			if(you->Redhoodsave[0]==-2 ||you->Redhoodsave[1]==-2  ||you->Redhoodsave[2]==-2 ){
				Redhoodsavefile(you,BotOn);
			}
		}else if(you->RedUlt.action == 4){
			card cardtemp1;
			if(skillBuyDeck[you->num][0].SIZE >0)Card_Define(skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1], &cardtemp1);
			card cardtemp2;
			if(skillBuyDeck[you->num][1].SIZE >0)Card_Define(skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1], &cardtemp2);
			card cardtemp3;
			if(skillBuyDeck[you->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp3);
			
			int8_t cc = you->RedUlt.spel_buy;
			
			switch(cc){
				case 1: // 攻擊
					if(skillBuyDeck[you->num][0].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1]);
						skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1] = 0;
						skillBuyDeck[you->num][0].SIZE--;
						
						Card_Define(skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1], &cardtemp1);
						if(cardtemp1.cost == 0){
							you->passive[you->passive_n] = skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1];
							skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1] = 0;
							skillBuyDeck[you->num][0].SIZE--;
							if(skillBuyDeck[you->num][0].SIZE <=0) skillBuyDeck[you->num][0].SIZE = 0;
							you->passive_n++;
							if(skillBuyDeck[you->num][0].SIZE >0)Card_Define(skillBuyDeck[you->num][0].array[skillBuyDeck[you->num][0].SIZE-1], &cardtemp1);
						}
						printf_skill_shop(you->num);
					}
					
				break;
				
				case 2: // 防禦
					if(skillBuyDeck[you->num][1].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1]);
						skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1] = 0;
						skillBuyDeck[you->num][1].SIZE--;
						
						Card_Define(skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1], &cardtemp2);
						if(cardtemp2.cost == 0){
							you->passive[you->passive_n] = skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1];
							skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1] = 0;
							skillBuyDeck[you->num][1].SIZE--;
							if(skillBuyDeck[you->num][1].SIZE <=0) skillBuyDeck[you->num][1].SIZE = 0;
							you->passive_n++;
							if(skillBuyDeck[you->num][1].SIZE >0)Card_Define(skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][1].SIZE-1], &cardtemp2);
						}
						printf_skill_shop(you->num);
					}
					
				break;
				
				case 3: // 移動
					if(skillBuyDeck[you->num][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1]);
						skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1] = 0;
						skillBuyDeck[you->num][2].SIZE--;
						
						Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp3);
						if(cardtemp3.cost == 0){
							you->passive[you->passive_n] = skillBuyDeck[you->num][1].array[skillBuyDeck[you->num][2].SIZE-1];
							skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1] = 0;
							skillBuyDeck[you->num][2].SIZE--;
							if(skillBuyDeck[you->num][2].SIZE <=0) skillBuyDeck[you->num][2].SIZE = 0;
							you->passive_n++;
							if(skillBuyDeck[you->num][2].SIZE >0)Card_Define(skillBuyDeck[you->num][2].array[skillBuyDeck[you->num][2].SIZE-1], &cardtemp2);
						}
						
					}
					
				break;
				
				
				default:
					printf("不存在此選項\n");
				break;
			}
		}else if(you->RedUlt.action == 3){
			int cc = you->RedUlt.bas_buy;
			switch(cc){
				case 1: // 攻擊卡 1
					if(basicBuyDeck[0][0].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, basicBuyDeck[0][0].array[basicBuyDeck[0][0].SIZE-1]);
						basicBuyDeck[0][0].array[basicBuyDeck[0][0].SIZE-1] = 0;
						basicBuyDeck[0][0].SIZE--;
						
						//printf_basic_shop();
					}
				
				break;
				
				case 2: // 攻擊卡 2
					if(basicBuyDeck[0][1].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, basicBuyDeck[0][1].array[basicBuyDeck[0][1].SIZE-1]);
						basicBuyDeck[0][1].array[basicBuyDeck[0][1].SIZE-1] = 0;
						basicBuyDeck[0][1].SIZE--;
						
						//printf_basic_shop();
					}
				
				break;
				
				case 3: // 攻擊卡 3
					if(basicBuyDeck[0][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, basicBuyDeck[0][2].array[basicBuyDeck[0][2].SIZE-1]);
						basicBuyDeck[0][2].array[basicBuyDeck[0][2].SIZE-1] = 0;
						basicBuyDeck[0][2].SIZE--;
						
						//printf_basic_shop();
					}
				
				break;
				
				case 4: // 防禦卡 1
					if(basicBuyDeck[1][0].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, basicBuyDeck[1][0].array[basicBuyDeck[1][0].SIZE-1]);
						basicBuyDeck[1][0].array[basicBuyDeck[1][0].SIZE-1] = 0;
						basicBuyDeck[1][0].SIZE--;
						
						//printf_basic_shop();
					}
				
				break;
				
				case 5: // 防禦卡 2
					if(basicBuyDeck[1][1].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, basicBuyDeck[1][1].array[basicBuyDeck[1][1].SIZE-1]);
						basicBuyDeck[1][1].array[basicBuyDeck[1][1].SIZE-1] = 0;
						basicBuyDeck[1][1].SIZE--;
						
						//printf_basic_shop();
					}
				
				break;
				
				case 6: // 防禦卡 3
					if(basicBuyDeck[1][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, basicBuyDeck[1][2].array[basicBuyDeck[1][2].SIZE-1]);
						basicBuyDeck[1][2].array[basicBuyDeck[1][2].SIZE-1] = 0;
						basicBuyDeck[1][2].SIZE--;
					
						//printf_basic_shop();
					}
				
				break;
				
				case 7: // 移動卡 1
					if(basicBuyDeck[2][0].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, basicBuyDeck[2][0].array[basicBuyDeck[2][0].SIZE-1]);
						basicBuyDeck[2][0].array[basicBuyDeck[2][0].SIZE-1] = 0;
						basicBuyDeck[2][0].SIZE--;
						
						//printf_basic_shop();
					}
				
				break;
				
				case 8: // 移動卡 2
					if(basicBuyDeck[2][1].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, basicBuyDeck[2][1].array[basicBuyDeck[2][1].SIZE-1]);
						basicBuyDeck[2][1].array[basicBuyDeck[2][1].SIZE-1] = 0;
						basicBuyDeck[2][1].SIZE--;
						
						//printf_basic_shop();
					}
				
				break;
				
				case 9: // 移動卡 3
					if(basicBuyDeck[2][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, basicBuyDeck[2][2].array[basicBuyDeck[2][2].SIZE-1]);
						basicBuyDeck[2][2].array[basicBuyDeck[2][2].SIZE-1] = 0;
						basicBuyDeck[2][2].SIZE--;
						
						//printf_basic_shop();
					}
				
				break;
				
				case 10: // 通用卡 
					if(basicBuyDeck[2][2].SIZE == 0){
						printf("此卡已經賣光了\n") ;
						
					}else{
						pushbackVector(&you->discard, basicBuyDeck[3][0].array[basicBuyDeck[3][0].SIZE-1]);
						basicBuyDeck[3][0].array[basicBuyDeck[3][0].SIZE-1] = 0;
						basicBuyDeck[3][0].SIZE--;
						
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
        printf("發動了醞釀之災！\n");
    }
	else if(card_id == 80){ // 炙熱的竹刀
	    you->immune = 1;
	}
	else if(card_id == 81){ // 注定的審判
	    *armor_output = 6;
	    int diff = you->armor - P->armor;
	    if(diff > 0){
		*damage_output = diff;
	    } else {
		*damage_output = 0;
	    }
	}
	else if(card_id == 82){ // 躁動的血性
	    move_adjacent_to_player(P, you); // 把對手移到你旁邊
	    *damage_output = 3;
	    add_card_to_starting(you, card_id, 0, 0); // 下一回合再次觸發
	}    
	// --- 加入花木蘭必殺技 ---
    if(card_id == 68) { // 氣沖雲霄
        you->mulan_draw_buff += 4;
        printf("%s 發動了氣沖雲霄，準備在本回合結束時額外抽 4 張牌！\n", you->charname);
    }
    else if(card_id == 69) { // 直面混沌
        move_adjacent_to_player(you, P);
        you->qi += 3;
        if (you->qi > 12) you->qi = 12; // 假設氣的上限是12
        printf("%s 發動了直面混沌，移動到對手身邊並獲得 3 點氣，目前氣: %d\n", you->charname, you->qi);
    }
    else if(card_id == 70) { // 雷霆一擊
        *damage_output = you->qi;
        printf("%s 發動了雷霆一擊，花費了 %d 點氣，造成 %d 點傷害！\n", you->charname, you->qi, *damage_output);
        you->qi = 0;
    }
	 // --- 火柴女孩必殺技 ---
    if (card_id == 92) { // 地獄烈焰
        *damage_output = (int)ceil(you->power / 2.0);
		printf("%s 召喚地獄烈焰，造成 %d 點傷害！\n", you->charname, *damage_output);
    }
    else if (card_id == 93) { // 厄運降臨
        int match_count = 0;
        printf("%s 翻開了對手的牌庫...\n", you->charname);
        for(int i=0; i<6; ++i) {
            if (P->deck.SIZE > 0) {
                int16_t milled_card = BottomVector(&P->deck);
                card C_temp;
                Card_Define(milled_card, &C_temp);
                printf("棄掉了 %s\n", C_temp.cardname);
                if (milled_card == MATCH_CARD_ID) {
                    match_count++;
                }
                discard_from_top_of_deck(P, 1);
            } else {
                break;
            }
        }
        *damage_output = match_count;
		printf("共翻到 %d 根火柴，造成 %d 點傷害。\n", match_count, *damage_output);
    }
    else if (card_id == 94) { // 貪婪詛咒
        printf("你要將幾根火柴放到對手牌庫頂？(0-3)\n");
        int8_t amount = 0;
        // ... (加入 bot 或玩家輸入邏輯)
        scanf("%hhd", &amount); getchar();
        if (amount < 0) amount = 0;
        if (amount > 3) amount = 3;
        if (amount > you->matches) amount = you->matches;
        
        for(int i=0; i<amount; ++i) {
            add_card_to_deck_top(P, MATCH_CARD_ID);
        }
        you->matches -= amount;
        printf("你將 %d 根火柴放到了 %s 的牌庫頂。\n", amount, P->charname);
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
	// === 輝夜姬：攻擊技能 ===
	else if(card_id == 71 || card_id == 72 || card_id == 73){
	    *armor_output = 0;
	    *damage_output = lv;
	    if(you->armor >= 3){
		*damage_output += 1;
	    }
	}

	// === 輝夜姬：防禦技能 ===
	else if(card_id == 74 || card_id == 75 || card_id == 76){
	    *armor_output = lv;
	    *damage_output = 0;

	    int peek = lv; // 看幾張
	    for(int i = 0; i < peek && i < you->deck.SIZE; i++){
		int top = you->deck.array[you->deck.SIZE - 1 - i];
		if(is_kaguya_defense_card(top)){
		    pushbackVector(&you->hands, top);
		    remove_card_from_deck_index(you, you->deck.SIZE - 1 - i);
		    break;
		}
	    }
	}

	// === 輝夜姬：移動技能 ===
	else if(card_id == 77 || card_id == 78 || card_id == 79){
	    *armor_output = 0;
	    *damage_output = lv;
	    if(you->hp > 1){
		you->hp -= 1;
		remove_card_interactively(you); // 讓玩家選擇移除卡
	    }
	    add_card_to_starting(you, card_id, 0, lv); // 持續效果
	}

	//花木蘭
	// 攻擊技能鏈 (不容小覷, 勢不可擋, 堅不可摧)
    if(card_id >= 59 && card_id <= 61) {
        card C;
        Card_Define(card_id, &C);
        *damage_output = C.damage + lv;

        // 將對手放置到另一個相鄰格子
        int8_t current_pos = P->coordinate;
        int8_t your_pos = you->coordinate;
        int8_t other_adjacent_pos = (current_pos == your_pos + 1) ? your_pos - 1 : your_pos + 1;
        
        int8_t Right_MAX = (mode == 1) ? 9 : 11;
        if (other_adjacent_pos >= 1 && other_adjacent_pos <= Right_MAX) {
            P->coordinate = other_adjacent_pos;
            printf("%s 被移動到格子 %d\n", P->charname, P->coordinate);
        }

        // 檢查邊緣棄牌效果
        if (P->coordinate == 1 || P->coordinate == Right_MAX) {
            if (P->hands > 0) {
                int rand_card_idx = rand() % P->hands;
                printf("%s 位於戰鬥軌道邊緣，隨機棄掉一張手牌！\n", P->charname);
                discard_card_from_hand(P, rand_card_idx);
            }
        }
    }
    // 防禦技能鏈 (以靜制動, 以柔克剛, 以弱勝強)
    else if(card_id >= 62 && card_id <= 64) {
        card C;
        Card_Define(card_id, &C);
        *armor_output = lv; // 防禦O
        you->mulan_draw_buff += C.level; // 設置結束階段抽牌buff
        printf("%s 準備在本回合結束時，花費氣額外抽牌 (至多 %d 張)\n", you->charname, you->mulan_draw_buff);
    }
    // 移動技能鏈 (永不退縮, 毫不留情, 絕不饒恕)
    else if(card_id >= 65 && card_id <= 67) {
        card C;
        Card_Define(card_id, &C);
        *damage_output = C.damage;

        // 擊退對手
        int8_t knockback = lv;
        int8_t direction = (P->coordinate > you->coordinate) ? 1 : -1;
        int8_t Right_MAX = (mode == 1) ? 9 : 11;

        for (int i = 0; i < knockback; ++i) {
            int8_t next_pos = P->coordinate + direction;
            if (next_pos >= 1 && next_pos <= Right_MAX) {
                P->coordinate = next_pos;
            } else {
                break; // 到達邊界
            }
        }
        printf("%s 被擊退到格子 %d\n", P->charname, P->coordinate);

        // 將自己放置到相鄰格子
        move_adjacent_to_player(you, P);
        printf("%s 移動到 %s 的相鄰格子 %d\n", you->charname, P->charname, you->coordinate);

        // 檢查邊緣棄牌效果
        if (P->coordinate == 1 || P->coordinate == Right_MAX) {
            if (P->hands > 0) {
                int rand_card_idx = rand() % P->hands;
                printf("%s 位於戰鬥軌道邊緣，隨機棄掉一張手牌！\n", P->charname);
                discard_card_from_hand(P, rand_card_idx);
            }
        }
    }
	// --- 火柴女孩技能 ---
	if (card_id >= 83 && card_id <= 85) { // 攻擊技能鏈
		card C;
        Card_Define(card_id, &C);
        *damage_output = C.damage + lv;
		
		if (check_passive(you, 155) > 0) { // 蛻變1: 痛苦的儀式
			printf("你擁有'痛苦的儀式'，是否要從對手棄牌堆回收1根火柴使本次傷害+2？(1:是, 0:否)\n");
			int8_t choice = 0;
			//... (加入 bot 或玩家輸入邏輯)
			scanf("%hhd", &choice); getchar();
			if (choice == 1 && reclaim_matches_from_discard(you, P, 1) > 0) {
				*damage_output += 2;
			}
		}

		while (you->power >= 3) {
			printf("你可以花費3點能量使傷害+1，是否花費？(剩餘能量:%d) (1:是, 0:否)\n", you->power);
			int8_t choice = 0;
			//... (加入 bot 或玩家輸入邏輯)
			scanf("%hhd", &choice); getchar();
			if (choice == 1) {
				you->power -= 3;
				(*damage_output)++;
			} else {
				break;
			}
		}
	}
	else if (card_id >= 86 && card_id <= 88) { // 防禦技能鏈
		*armor_output = 1;
		int max_draw = 0;
		if (card_id == 86) max_draw = 1;
		if (card_id == 87) max_draw = 2;
		if (card_id == 88) max_draw = 3;

		printf("你可以失去X點生命來抽X張牌 (X至多為%d)，要失去多少生命？(0-%d)\n", max_draw, max_draw);
		int8_t cost_hp = 0;
		//... (加入 bot 或玩家輸入邏輯)
		scanf("%hhd", &cost_hp); getchar();
		if (cost_hp > 0 && cost_hp <= max_draw && you->hp > cost_hp) {
			you->hp -= cost_hp;
			draw_card(cost_hp, you);
		}
		
		if (check_passive(you, 157) > 0) { // 蛻變1: 放縱的渴望
			printf("你擁有'放縱的渴望'，是否從對手棄牌堆回收1根火柴來額外抽1張牌？(1:是, 0:否)\n");
			int8_t choice = 0;
			//... (加入 bot 或玩家輸入邏輯)
			scanf("%hhd", &choice); getchar();
			if (choice == 1 && reclaim_matches_from_discard(you, P, 1) > 0) {
				draw_card(1, you);
			}
		}
	}
	else if (card_id >= 89 && card_id <= 91) { // 移動技能鏈
		card C;
        Card_Define(card_id, &C);
        *damage_output = C.damage;

		int reclaimed = reclaim_matches_from_discard(you, P, lv);
		if (card_id == 89) you->power += reclaimed * 1;
		if (card_id == 90) { you->power += reclaimed * 2; regenerate_hp(you, reclaimed * 1); }
		if (card_id == 91) { you->power += reclaimed * 3; regenerate_hp(you, reclaimed * 2); }
	}
	return 0;
}
