int8_t play_a_card(player *P){
	system("clear");
	print_game_broad_9();
	print_hands(P);
	printf("你要打哪一張牌？（輸入0返回）\n");
	while(1){
		int8_t select=-1;
		if((*P).hands == 0){
			if(mode == 1){
				print_game_broad_9();
						
				}else{			
			}
			printf("你沒有手牌了！\n");
			action_command(P);
		}
		
			printf("請問你要打哪一張牌？\n");
			printf(">");
			scanf("%hhd",&select);
			if(select == 0){
				if(mode == 1){
					print_game_broad_9();
					return 0;
				}else{
					
				}
				action_command(P);
				return 0;
			}
		
			if(select > P->hands || select < 0 ){
					printf("沒有這張卡！%d\n",target(P));
			}else{
				printf("%d\n",P->hands_card[select-1].type);
				switch (P->hands_card[select-1].type){
					case 0://攻擊卡
						if(range_counter(P,&Player[target(P)],P->hands_card[select-1].range) == 1){
							deal_damage(&Player[target(P)] , P->hands_card[select-1].value + P->atk_buff);
							P->power += P->hands_card[select-1].power_generate;
							discard_card_from_hand(P,select-1);
							int inf_atk = (P->hands_card[select-1].value + P->atk_buff );
							print_game_broad_9();
							printf("你對對手造成了\033[1;31m%hhd\033[0m點傷害",inf_atk );
							action_command(P);
							
							
							
						}else{
							print_game_broad_9();
							printf("對手不在你的攻擊範圍！\n");
							action_command(P);
						}
					break;
					
					case 1://防禦卡
						P->armor += P->hands_card[select-1].value + P->defend_buff;
						P->power  += P->hands_card[select-1].power_generate;
						int ar_in = P->hands_card[select-1].value + P->defend_buff ;
						discard_card_from_hand(P,select-1);
						print_game_broad_9();
						printf("你獲得了\033[1;31m%hhd\033[0m個盾",ar_in );
						action_command(P);
					break;
					
					case 2://移動卡
						int8_t way = 0;
						printf("你要向左還是向右？1.)向左 2.)向右 ：");
						scanf("%hhd",&way);
						int move = P->hands_card[select-1].value + P->speed_buff ;
						for(int i = 0 ; i < move ; i++){
							
							if(way == 1){ //左
							
								if(P->coordinate -1 != 0){
									if(P->coordinate -1 == Player[target(P)].coordinate && P->coordinate - 2 != 0 && move >= 2 ){
											P->coordinate-=2 ;
											move -=2 ;
									}else{
										if(P->coordinate -1 !=Player[target(P)].coordinate)P->coordinate-- ;
											move --;
									}
								}
								
							}else{
								if(P->coordinate +1 != Right_MAX){
									if(P->coordinate +1 == Player[target(P)].coordinate && P->coordinate + 2 != Right_MAX && move >= 2 ){
											P->coordinate+=2 ;
											move -=2 ;
									}else{
											if(P->coordinate +1 !=Player[target(P)].coordinate)P->coordinate++ ;
											move --;
									}
								}
							}
								
						}
						P->power  += P->hands_card[select-1].power_generate;
						discard_card_from_hand(P,select-1);
						print_game_broad_9();
						action_command(P);
					break;
					
					case 3://技能卡
						int8_t combo_card =-1;
						int8_t damage_deal=0;
						int8_t armor_get=0;
						int8_t levels = -1;
						
						if(P->hands_card[select-1].require_basic_card == 0){
							printf("你要搭配哪一張基礎攻擊卡？\n>");
						}else if(P->hands_card[select-1].require_basic_card == 1){
							printf("你要搭配哪一張基礎防禦卡？\n>");
						}else if(P->hands_card[select-1].require_basic_card == 2){
							printf("你要搭配哪一張基礎移動卡？\n>");
						}
						while(scanf("%hhd",&combo_card)!=1){
							getchar();
							printf("invalid input");
						}
						if(P->hands_card[combo_card-1].type == P->hands_card[select-1].require_basic_card ){
							if(range_counter(P,&Player[target(P)],P->hands_card[select-1].range) == 1 || P->hands_card[select-1].range == 0){
								use_skill(P,&Player[target(P)], P->hands_card[combo_card-1].cardcode , &damage_deal , &armor_get , levels , P->hands_card[combo_card-1].cardcode , mode);
							}else{
								printf("對手不在你的攻擊範圍！\n");
							}
						
						}else{
							printf("你所選擇的卡片並不能搭配這張卡！\n");
						}
					
					break;
					
					case 5://大招卡
					
					break;
					
						
				}
				return -1;
			}
		
				
	}
}




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
		int tt = 2;
		printf_skill_shop(P->num);
		card cardtemp1;
		Card_Define(skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1], &cardtemp1);
		card cardtemp2;
		Card_Define(skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1], &cardtemp2);
		card cardtemp3;
		Card_Define(skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1], &cardtemp3);
		
		printf_skill_shop(P->num);
		while(tt!=0){
				if(skillBuyDeck[P->num][0].SIZE == 0 && skillBuyDeck[P->num][1].SIZE == 0  && skillBuyDeck[P->num][2].SIZE == 0 ){
					break;
				}
				int8_t cc =-1;
				printf("請輸入你要升級的技能：") ;
				scanf("%hhd",&cc);
				switch(cc){
					case 1: // 攻擊
						if(skillBuyDeck[P->num][0].SIZE == 0){
							printf("此卡已經賣光了\n") ;
							
						}else{
							pushbackVector(&P->discard, skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1]);
							skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1] = 0;
							skillBuyDeck[P->num][0].SIZE--;
							P->power -=cardtemp1.cost;
							Card_Define(skillBuyDeck[P->num][0].array[skillBuyDeck[P->num][0].SIZE-1], &cardtemp1);
							printf_skill_shop(P->num);
						}
						tt--;
					break;
					
					case 2: // 防禦
						if(skillBuyDeck[P->num][1].SIZE == 0){
							printf("此卡已經賣光了\n") ;
							
						}else{
							pushbackVector(&P->discard, skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1]);
							skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1] = 0;
							skillBuyDeck[P->num][1].SIZE--;
							P->power -=cardtemp2.cost;
							Card_Define(skillBuyDeck[P->num][1].array[skillBuyDeck[P->num][1].SIZE-1], &cardtemp2);
							printf_skill_shop(P->num);
						}
						tt--;
					break;
					
					case 3: // 移動
						if(skillBuyDeck[P->num][2].SIZE == 0){
							printf("此卡已經賣光了\n") ;
							
						}else{
							pushbackVector(&P->discard, skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1]);
							skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1] = 0;
							skillBuyDeck[P->num][2].SIZE--;
							P->power -=cardtemp3.cost;
							Card_Define(skillBuyDeck[P->num][2].array[skillBuyDeck[P->num][2].SIZE-1], &cardtemp3);
							printf_skill_shop(P->num);
						}
						tt--;
					break;
				
					
					default:
						printf("不存在此選項\n");
					break;
					
					
				}
				
			
		}
		return 0;
	}else if(card_id == 21){
	
	}else if(card_id == 22){
		
	}
	
}
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
		int tt = 2;
		printf_skill_shop(P->num);
		card cardtemp1;
		Card_Define(skillBuyDeck[P->num][0]->array[skillBuyDeck[P->num][0]->SIZE-1], &cardtemp1);
		card cardtemp2;
		Card_Define(skillBuyDeck[P->num][1]->array[skillBuyDeck[P->num][1]->SIZE-1], &cardtemp2);
		card cardtemp3;
		Card_Define(skillBuyDeck[P->num][2]->array[skillBuyDeck[P->num][2]->SIZE-1], &cardtemp3);
		
		printf_skill_shop(P->num);
		while(tt!=0){
				if(skillBuyDeck[P->num][0]->SIZE == 0 && skillBuyDeck[P->num][1]->SIZE == 0  && skillBuyDeck[P->num][2]->SIZE == 0 ){
					break;
				}
				int8_t cc =-1;
				printf("請輸入你要升級的技能：") ;
				scanf("%hhd",&cc);
				switch(cc){
					case 1: // 攻擊
						if(skillBuyDeck[P->num][0]->SIZE == 0){
							printf("此卡已經賣光了\n") ;
							
						}else{
							pushbackVector(&P->discard, skillBuyDeck[P->num][0]->array[skillBuyDeck[P->num][0]->SIZE-1]);
							skillBuyDeck[P->num][0]->array[skillBuyDeck[P->num][0]->SIZE-1] = 0;
							skillBuyDeck[P->num][0]->SIZE--;
							P->power -=cardtemp1.cost;
							Card_Define(skillBuyDeck[P->num][0]->array[skillBuyDeck[P->num][0]->SIZE-1], &cardtemp1);
							printf_skill_shop(P->num);
						}
						tt--;
					break;
					
					case 2: // 防禦
						if(skillBuyDeck[P->num][1]->SIZE == 0){
							printf("此卡已經賣光了\n") ;
							
						}else{
							pushbackVector(&P->discard, skillBuyDeck[P->num][1]->array[skillBuyDeck[P->num][1]->SIZE-1]);
							skillBuyDeck[P->num][1]->array[skillBuyDeck[P->num][1]->SIZE-1] = 0;
							skillBuyDeck[P->num][1]->SIZE--;
							P->power -=cardtemp2.cost;
							Card_Define(skillBuyDeck[P->num][1]->array[skillBuyDeck[P->num][1]->SIZE-1], &cardtemp2);
							printf_skill_shop(P->num);
						}
						tt--;
					break;
					
					case 3: // 移動
						if(skillBuyDeck[P->num][2]->SIZE == 0){
							printf("此卡已經賣光了\n") ;
							
						}else{
							pushbackVector(&P->discard, skillBuyDeck[P->num][2]->array[skillBuyDeck[P->num][2]->SIZE-1]);
							skillBuyDeck[P->num][2]->array[skillBuyDeck[P->num][2]->SIZE-1] = 0;
							skillBuyDeck[P->num][2]->SIZE--;
							P->power -=cardtemp3.cost;
							Card_Define(skillBuyDeck[P->num][2]->array[skillBuyDeck[P->num][2]->SIZE-1], &cardtemp3);
							printf_skill_shop(P->num);
						}
						tt--;
					break;
				
					
					default:
						printf("不存在此選項\n");
					break;
					
					
				}
				
			
		}
		return 0;
	}else if(card_id == 21){
	
	}else if(card_id == 22){
		
	}
	
	
	
