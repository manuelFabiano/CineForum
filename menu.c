#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void menu_visualizza_discussioni(lista_discussioni* discussioni, lista_generi* generi, struct utente* utente) {
	char scelta, scelta2, scelta3, scelta4;
	int c, r;
	char nick[31];
	lista_discussioni discussione = NULL ;
	struct recensione* recensione = NULL;
		
	do{	
		system("clear");
		printf("\nCosa vuoi visualizzare?\n\n");
		printf("1) Film e Serie tv\n");
		printf("2) Solo film\n");
		printf("3) Solo serie tv\n");
		printf("0) Ritorna al menù precedente\n\n");
		scanf("%c" ,&scelta);
		system("clear");
    	while ((c = getchar()) != '\n' && c != EOF);
    	if(scelta == '1' || scelta == '2' || scelta == '3'){
    	do{
			if(scelta == '1')
				r = stampa_discussioni(*discussioni);
			if(scelta == '2')
				r = stampa_discussioni_film(*discussioni);
			if(scelta == '3')
				r = stampa_discussioni_serie(*discussioni);
						
			//Se non e' ancora presente nessuna discussione
			if (r == 1){
						
				
					printf("\nCosa vuoi fare?\n\n");
					printf("1) Inizia una nuova discussione\n");
    				printf("0) Ritorna al menù delle discussioni\n\n");
					scanf("%c", &scelta2);
    			
    				while ((c = getchar()) != '\n' && c != EOF);
    					
    				switch(scelta2){
    			
    					case '0': return; break;
    				
    					case '1': 
    						system("clear");
    						discussione = inizia_discussione(discussioni, generi, utente);
    						if(discussione == NULL){
		    					printf("\n\nPremi invio per continuare\n");
		            			while( getchar() != '\n' );
		           				 system("clear");
		            			break;
                				}
                			printf("\nPremi invio per continuare\n");
               				while( getchar() != '\n' );
                			system("clear");
        		
							do{
								system("clear");
								stampa_scheda(discussione);
								stampa_recensioni(discussione->recensioni);
								printf("Cosa vuoi fare?\n\n");
								printf("1) Scrivi una recensione\n");
								//se l'utente ha gia' inserito una recensione puo' modificarla o cancellarla
								recensione = cerca_recensione(discussione->recensioni, utente);
								//Se l'utente e' un admin
								if(utente->admin == 1){
									if(recensione != NULL){
										printf("2) Modifica la tua recensione\n");
										printf("3) Rimuovi la tua recensione\n");
									}
									printf("4) Rimuovi la recensione di un utente\n");
									printf("5) Cancella questa discussione\n");
								}else{
									//se l'utente non e' un admin
									if(recensione != NULL){
										printf("2) Modifica la tua recensione\n");
										printf("3) Rimuovi la tua recensione\n");
									}
								}
								printf("0) Ritorna al menù precedente\n\n");
								scanf("%c", &scelta3);
							
								while ((c = getchar()) != '\n' && c != EOF);
											
								switch(scelta3){
											
									case '0': return;
												
									case '1': 
										//AGGIUNGI RECENSIONE
										//se l'utente ha gia' inserito una recensione non puo' aggiungerne un altra
										recensione = cerca_recensione(discussione->recensioni, utente);
										if(recensione != NULL){
											printf(ANSI_COLOR_RED"\nHai già inserito una recensione!\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
							    			while( getchar() != '\n' );
							    			system("clear") ;
											break;
										}
						        		system("clear");
										r = aggiungi_recensione(discussione->recensioni, utente);
										if (r == 1){
											printf(ANSI_COLOR_RED"Qualcosa è andato storto!\n"ANSI_COLOR_RESET);
											exit(0);
										}
										printf("\nPremi invio per continuare\n");
						        		while( getchar() != '\n' );
						        		system("clear") ;
										break;
													
									case '2': 
										//MODIFICA RECENSIONE
										//se l'utente non ha ancora inserito una recensione, non può farlo
										if (recensione !=NULL){
											r = modifica_recensione(discussione->recensioni, utente->nick);
											if(r == 1){
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
								    			while( getchar() != '\n' );
								    			system("clear") ;
						        			}
						        			else{
						        				printf(ANSI_COLOR_YELLOW"\nRecensione modificata con successo!\n"ANSI_COLOR_RESET);
						        				printf("\nPremi invio per continuare\n");
						        				while( getchar() != '\n' );
						        				system("clear") ; 
						        			}
										}else{
											printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
						        			while( getchar() != '\n' );
						        			system("clear") ; 
										}
										break;
												
									case '3':
										//RIMUOVI RECENSIONE				
										if(recensione != NULL){
											printf(ANSI_COLOR_RED"Sei sicuro di voler rimuovere definitivamente la tua recensione?\n"ANSI_COLOR_RESET);
											printf("1)Si   2)No\n");
											scanf("%c", &scelta4);
											while ((c = getchar()) != '\n' && c != EOF);
											if(scelta4 != '1' && scelta4 != '2'){
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
				    							while( getchar() != '\n' );
				  								system("clear") ;
												break;
											}
											if(scelta4 == '1'){					
												cancella_recensione(discussione->recensioni, utente->nick);
												printf(ANSI_COLOR_YELLOW"Recensione rimossa con successo!\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
						        				while( getchar() != '\n' );
						        				system("clear") ; 
												}
										}else{
											printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
						        			while( getchar() != '\n' );
						        			system("clear") ;
						        		} 
										break;
									
									case '4':
										//RIMUOVI RECENSIONE ADMIN
										if(utente->admin == 1){
										printf("Inserisci il nickname dell'utente del quale vuoi rimuovere la recensione: ");
										fgets(nick, 31, stdin);
										nick[strcspn(nick, "\n")] = 0;
										r = cancella_recensione(discussione->recensioni, nick);
										if(r == 1){
											printf(ANSI_COLOR_RED"\nNon è presente alcuna recensione scritta dall'utente inserito!\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
							    			while( getchar() != '\n' );
							    			system("clear") ; 
											break;
										}
										printf(ANSI_COLOR_YELLOW"\nRecensione rimossa con successo!\n"ANSI_COLOR_RESET);
										printf("\nPremi invio per continuare\n");
							    		while( getchar() != '\n' );
							    		system("clear") ; 
										break;
										}else{
											printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
						        			while( getchar() != '\n' );
						        			system("clear") ; 
											break;
										}
										
									case '5':
										if(utente->admin == 1){
											printf(ANSI_COLOR_RED"Sei sicuro di voler rimuovere definitivamente questa discussione?\n"ANSI_COLOR_RESET);
											printf("1)Si   2)No\n");
											scanf("%c", &scelta3);
											while ((c = getchar()) != '\n' && c != EOF);
											if(scelta3 != '1' && scelta3 != '2'){
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
												while( getchar() != '\n' );
							  					system("clear") ;
												break;
											}
											if(scelta3 == '1'){					
												cancella_discussione(discussioni, generi, discussione->titolo);
												printf(ANSI_COLOR_YELLOW"\nDiscussione rimossa con successo!\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
						        				while( getchar() != '\n' );
						        				system("clear") ; 
												return;											
											}
										}else{
											printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
						        			while( getchar() != '\n' );
						        			system("clear");
										}
										break;
									
									default:
										printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
										printf("\nPremi invio per continuare\n");
						        		while( getchar() != '\n' );
						        		system("clear") ; 
										break;
								}
								
							}while(scelta3 != '0' && scelta3 != '5');
							return;	
    						
    				
    					default: 
    						printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET); 
    						printf("\nPremi invio per continuare\n");
				    		while( getchar() != '\n' );
				  			system("clear") ;
    						break;
    					}
    				return;	
   				}else{
	   				
						//Se sono già presenti discussioni
						printf("\nCosa vuoi fare?\n\n");
						printf("1) Visualizza una discussione\n");
		   				printf("2) Inizia una nuova discussione\n");
		   				printf("0) Ritorna al menù delle discussioni\n\n");
		   				scanf("%c", &scelta2);
		   				while ((c = getchar()) != '\n' && c != EOF);
						
						switch(scelta2){
						
							case '0':
								return;
							
							case '1':	
								
									if(scelta == '1')
										discussione = apri_discussione(*discussioni, utente, 1);
									if(scelta == '2')
										discussione = apri_discussione(*discussioni, utente, 2);
									if(scelta == '3')
										discussione = apri_discussione(*discussioni, utente, 3);
									if(discussione == NULL){
										printf(ANSI_COLOR_RED"\nNon è stata trovata nessuna discussione corrispondente a quel numero\n\n"ANSI_COLOR_RESET);
										printf("\nPremi invio per continuare\n");
										while( getchar() != '\n' );
										system("clear") ;
										break;
									}
		   						do{	
		   							system("clear") ;
		   							stampa_scheda(discussione);
									stampa_recensioni(discussione->recensioni);
		   							printf("Cosa vuoi fare?\n\n");
									printf("1) Scrivi una recensione\n");
									//se l'utente ha gia' inserito una recensione puo' modificarla o cancellarla
									recensione = cerca_recensione(discussione->recensioni, utente);
									//Se l'utente e' un admin
									if(utente->admin == 1){
										if(recensione != NULL){
											printf("2) Modifica la tua recensione\n");
											printf("3) Rimuovi la tua recensione\n");
										}
										printf("4) Rimuovi la recensione di un utente\n");
										printf("5) Cancella questa discussione\n");
									}else{
										//se l'utente non e' un admin
										if(recensione != NULL){
											printf("2) Modifica la tua recensione\n");
											printf("3) Rimuovi la tua recensione\n");
										}
									}
									printf("0) Ritorna al menù precedente\n\n");
									scanf("%c", &scelta3);
									
									while ((c = getchar()) != '\n' && c != EOF);
													
									switch(scelta3){
													
										case '0': return;
														
										case '1': 
											//AGGIUNGI RECENSIONE
											//se l'utente ha gia' inserito una recensione non puo' aggiungerne un altra
											recensione = cerca_recensione(discussione->recensioni, utente);
											if(recensione != NULL){
												printf(ANSI_COLOR_RED"\nHai già inserito una recensione!\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
												while( getchar() != '\n' );
												system("clear") ;
												break;
											}
											system("clear");
											r = aggiungi_recensione(discussione->recensioni, utente);
											if (r == 1){
												printf(ANSI_COLOR_RED"Qualcosa è andato storto!\n"ANSI_COLOR_RESET);
												exit(0);
											}
											printf("\nPremi invio per continuare\n");
											while( getchar() != '\n' );
											system("clear") ;
											break;
														
										case '2': 
											//MODIFICA RECENSIONE
											//se l'utente non ha ancora inserito una recensione, non può farlo
											if (recensione !=NULL){
												r = modifica_recensione(discussione->recensioni, utente->nick);
												if(r == 1){
													printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
													printf("\nPremi invio per continuare\n");
													while( getchar() != '\n' );
													system("clear") ;
												}
												else{
									   				printf(ANSI_COLOR_YELLOW"\nRecensione modificata con successo!\n"ANSI_COLOR_RESET);
									   				printf("\nPremi invio per continuare\n");
													while( getchar() != '\n' );
													system("clear") ; 
												}
											}else{
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
												while( getchar() != '\n' );
									   			system("clear") ; 
											}
											break;
													
										case '3':
											//RIMUOVI RECENSIONE				
											if(recensione != NULL){
												printf(ANSI_COLOR_RED"Sei sicuro di voler rimuovere definitivamente la tua recensione?\n"ANSI_COLOR_RESET);
												printf("1)Si   2)No\n");
												scanf("%c", &scelta4);
												while ((c = getchar()) != '\n' && c != EOF);
												if(scelta4 != '1' && scelta4 != '2'){
													printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
													break;
												}
												if(scelta4 == '1'){					
													cancella_recensione(discussione->recensioni, utente->nick);
													printf(ANSI_COLOR_YELLOW"Recensione rimossa con successo!\n"ANSI_COLOR_RESET);
													printf("\nPremi invio per continuare\n");
									   				while( getchar() != '\n' );
									   				system("clear") ; 
													}
											}else{
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
												while( getchar() != '\n' );
												system("clear") ;
											} 
											break;
											
										case '4':
											//RIMUOVI RECENSIONE ADMIN
											if(utente->admin == 1){
											printf("Inserisci il nickname dell'utente del quale vuoi rimuovere la recensione: ");
											fgets(nick, 31, stdin);
											nick[strcspn(nick, "\n")] = 0;
											r = cancella_recensione(discussione->recensioni, nick);
											if(r == 1){
												printf(ANSI_COLOR_RED"\nNon è presente alcuna recensione scritta dall'utente inserito!\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
							    				while( getchar() != '\n' );
							    				system("clear") ; 
												break;
											}
											printf(ANSI_COLOR_YELLOW"\nRecensione rimossa con successo!\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
							    			while( getchar() != '\n' );
							    			system("clear") ; 
											break;
											}else{
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
												while( getchar() != '\n' );
												system("clear") ; 
												break;
											}
											
										case '5':
											if(utente->admin == 1){
												printf(ANSI_COLOR_RED"Sei sicuro di voler rimuovere definitivamente questa discussione?\n"ANSI_COLOR_RESET);
												printf("1)Si   2)No\n");
												scanf("%c", &scelta3);
												while ((c = getchar()) != '\n' && c != EOF);
												if(scelta3 != '1' && scelta3 != '2'){
													printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
													printf("\nPremi invio per continuare\n");
													while( getchar() != '\n' );
								  					system("clear") ;
													break;
												}
												if(scelta3 == '1'){					
													cancella_discussione(discussioni, generi, discussione->titolo);
													printf(ANSI_COLOR_YELLOW"\nDiscussione rimossa con successo!\n"ANSI_COLOR_RESET);
													printf("\nPremi invio per continuare\n");
								    				while( getchar() != '\n' );
								    				system("clear") ; 
													return;
												}
											}else{
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
								    			while( getchar() != '\n' );
								    			system("clear");
											}
											break;
									
										default:
											printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
											while( getchar() != '\n' );
											system("clear") ; 
											break;
									}
								 }while(scelta3 != '0' && scelta3 != '5');
									 
								break;
							
							case '2': 
								system("clear") ; 
								discussione = inizia_discussione(discussioni, generi, utente);
								if(discussione == NULL){
									printf("\n\nPremi invio per continuare\n");
									while( getchar() != '\n' );
									system("clear");
									break;
								}
								printf("\nPremi invio per continuare\n");
								while( getchar() != '\n' );
								system("clear");
						
								do{
									system("clear");
									stampa_scheda(discussione);
									stampa_recensioni(discussione->recensioni);
									printf("Cosa vuoi fare?\n\n");
									printf("1) Scrivi una recensione\n");
									//se l'utente ha gia' inserito una recensione puo' modificarla o cancellarla
									recensione = cerca_recensione(discussione->recensioni, utente);
									//Se l'utente e' un admin
									if(utente->admin == 1){
										if(recensione != NULL){
											printf("2) Modifica la tua recensione\n");
											printf("3) Rimuovi la tua recensione\n");
										}
										printf("4) Rimuovi la recensione di un utente\n");
										printf("5) Cancella questa discussione\n");
									}else{
										//se l'utente non e' un admin
										if(recensione != NULL){
											printf("2) Modifica la tua recensione\n");
											printf("3) Rimuovi la tua recensione\n");
										}
									}
									printf("0) Ritorna al menù precedente\n\n");
									scanf("%c", &scelta3);
								
									while ((c = getchar()) != '\n' && c != EOF);
												
									switch(scelta3){
												
										case '0': break;
													
										case '1': 
											//AGGIUNGI RECENSIONE
											//se l'utente ha gia' inserito una recensione non puo' aggiungerne un altra
											recensione = cerca_recensione(discussione->recensioni, utente);
											if(recensione != NULL){
												printf(ANSI_COLOR_RED"\nHai già inserito una recensione!\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
												while( getchar() != '\n' );
												system("clear") ;
												break;
											}
								    		system("clear");
											r = aggiungi_recensione(discussione->recensioni, utente);
											if (r == 1){
												printf(ANSI_COLOR_RED"Qualcosa è andato storto!\n"ANSI_COLOR_RESET);
												exit(0);
											}
											printf("\nPremi invio per continuare\n");
								    		while( getchar() != '\n' );
								    		system("clear") ;
											break;
														
										case '2': 
											//MODIFICA RECENSIONE
											//se l'utente non ha ancora inserito una recensione, non può farlo
											if (recensione !=NULL){
												r = modifica_recensione(discussione->recensioni, utente->nick);
												if(r == 1){
													printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
													printf("\nPremi invio per continuare\n");
													while( getchar() != '\n' );
													system("clear") ;
								    			}
								    			else{
								    				printf(ANSI_COLOR_YELLOW"\nRecensione modificata con successo!\n"ANSI_COLOR_RESET);
								    				printf("\nPremi invio per continuare\n");
								    				while( getchar() != '\n' );
								    				system("clear") ; 
								    			}
											}else{
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
								    			while( getchar() != '\n' );
								    			system("clear") ; 
											}
											break;
													
										case '3':
											//RIMUOVI RECENSIONE				
											if(recensione != NULL){
												printf(ANSI_COLOR_RED"Sei sicuro di voler rimuovere definitivamente la tua recensione?\n"ANSI_COLOR_RESET);
												printf("1)Si   2)No\n");
												scanf("%c", &scelta3);
												while ((c = getchar()) != '\n' && c != EOF);
												if(scelta3 != '1' && scelta3 != '2'){
													printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
													printf("\nPremi invio per continuare\n");
													while( getchar() != '\n' );
						  							system("clear") ;
													break;
												}
												if(scelta3 == '1'){					
													cancella_recensione(discussione->recensioni, utente->nick);
													printf(ANSI_COLOR_YELLOW"Recensione rimossa con successo!\n"ANSI_COLOR_RESET);
													printf("\nPremi invio per continuare\n");
								    				while( getchar() != '\n' );
								    				system("clear") ; 
													}
											}else{
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
								    			while( getchar() != '\n' );
								    			system("clear") ;
								    		} 
											break;
										
										case '4':
											//RIMUOVI RECENSIONE ADMIN
											if(utente->admin == 1){
												printf("Inserisci il nickname dell'utente del quale vuoi rimuovere la recensione: ");
												fgets(nick, 31, stdin);
												nick[strcspn(nick, "\n")] = 0;
												r = cancella_recensione(discussione->recensioni, nick);
												if(r == 1){
												printf(ANSI_COLOR_RED"\nNon è presente alcuna recensione scritta dall'utente inserito!\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
							    				while( getchar() != '\n' );
							    				system("clear") ; 
												break;
												}
												printf(ANSI_COLOR_YELLOW"\nRecensione rimossa con successo!\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
							    				while( getchar() != '\n' );
							    				system("clear") ; 
											}else{
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
								    			while( getchar() != '\n' );
								    			system("clear") ;
								    		} 
											break;
											
										case '5':
											if(utente->admin == 1){
												printf("Sei sicuro di voler rimuovere definitivamente questa discussione?\n");
												printf("1)Si   2)No\n");
												scanf("%c", &scelta3);
												while ((c = getchar()) != '\n' && c != EOF);
												if(scelta3 != '1' && scelta3 != '2'){
													printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
													printf("\nPremi invio per continuare\n");
													while( getchar() != '\n' );
								  					system("clear") ;
													break;
												}
												if(scelta3 == '1'){					
													cancella_discussione(discussioni, generi, discussione->titolo);
													printf(ANSI_COLOR_YELLOW"\nDiscussione rimossa con successo!\n"ANSI_COLOR_RESET);
													printf("\nPremi invio per continuare\n");
								    				while( getchar() != '\n' );
								    				system("clear") ; 
													return;
												}
											}else{
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
								    			while( getchar() != '\n' );
								    			system("clear");
											}
											break;
											
																				
										default:
											printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
								    		while( getchar() != '\n' );
								    		system("clear") ; 
											break;
									}
								} 
								while(scelta3 != '0' && scelta3 != '5');						
								system("clear");
								break; 
							
							
							default: 
								printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET); 
								printf("\nPremi invio per continuare\n");
								while( getchar() != '\n' );
						  		system("clear") ;
								break;
							}
    				
    			}
    		}while(scelta2 != '0');	
    	}		
    	if(scelta !='0'){
    		printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
    		printf("\nPremi invio per continuare\n");
			while( getchar() != '\n' );
		  	system("clear") ;
   		}
	
}while(scelta != '0');
}

 	
//menù per gestire le discussioni
void menu_discussioni(lista_discussioni* discussioni, lista_generi* generi, struct utente* utente){
	char scelta, scelta2, scelta3, scelta4;
	char nome_genere[31], nick[31];
	int r;
	lista_discussioni discussione = NULL;
	struct recensione* recensione = NULL;
	
	do{
		system("clear");
		printf(ANSI_COLOR_YELLOW"\nScegli una delle opzioni disponibili\n\n"ANSI_COLOR_RESET);
		printf("1) Visualizza l'elenco di discussioni\n");
		printf("2) Filtra per genere\n");
		if(utente->admin ==1){
			printf("3) Aggiungi un genere\n");
			printf("4) Rimuovi un genere\n");
		}
		printf("0) Ritorna al menù precedente\n\n");
		scanf("%c" ,&scelta);
		int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        switch(scelta){
        	case '0': break;
        	
        	case '1': 	
        		menu_visualizza_discussioni(discussioni, generi, utente);
        	    break;
        	
        	case '2': 
        		system("clear");
        		do{
		    		resetta_n(discussioni);
		    		r = filtra(*generi);
		    		if(r == 1){ 
		    			printf("\nPremi invio per continuare\n");
		             	while( getchar() != '\n' );
		             	system("clear");
		            	break;
		            } 
        		
		    		printf("\nCosa vuoi fare?\n\n");
					printf("1) Visualizza una discussione\n");
	   				printf("0) Ritorna al menù delle discussioni\n\n");
	   				scanf("%c", &scelta2);
					
	   				while ((c = getchar()) != '\n' && c != EOF);
					
					switch(scelta2){
					
						case '0':
							break;
						
						case '1':	
							
							discussione = apri_discussione(*discussioni, utente, 1);
							if(discussione == NULL){
								printf(ANSI_COLOR_RED"\nNon è stata trovata nessuna discussione corrispondente a quel numero\n\n"ANSI_COLOR_RESET);
								printf("\nPremi invio per continuare\n");
							    while( getchar() != '\n' );
							    system("clear");
								break;
							}
	   						do{
	   							system("clear");
	   							stampa_scheda(discussione);
								stampa_recensioni(discussione->recensioni);
	   							printf("Cosa vuoi fare?\n\n");
								printf("1) Scrivi una recensione\n");
								//se l'utente ha gia' inserito una recensione puo' modificarla o cancellarla
								recensione = cerca_recensione(discussione->recensioni, utente);
								//Se l'utente e' un admin
								if(utente->admin == 1){
									if(recensione != NULL){
										printf("2) Modifica la tua recensione\n");
										printf("3) Rimuovi la tua recensione\n");
									}
									printf("4) Rimuovi la recensione di un utente\n");
									printf("5) Cancella questa discussione\n");
								}else{
									//se l'utente non e' un admin
									if(recensione != NULL){
										printf("2) Modifica la tua recensione\n");
										printf("3) Rimuovi la tua recensione\n");
									}
								}
								printf("0) Ritorna al menù principale\n\n");
								scanf("%c", &scelta3);
								
								while ((c = getchar()) != '\n' && c != EOF);
												
								switch(scelta3){
												
									case '0': return;
													
									case '1': 
										//AGGIUNGI RECENSIONE
										//se l'utente ha gia' inserito una recensione non puo' aggiungerne un altra
										recensione = cerca_recensione(discussione->recensioni, utente);
										if(recensione != NULL){
											printf(ANSI_COLOR_RED"\nHai già inserito una recensione!\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
							    			while( getchar() != '\n' );
							    			system("clear") ;
											break;
										}
							    		system("clear");
										r = aggiungi_recensione(discussione->recensioni, utente);
										if (r == 1){
											printf(ANSI_COLOR_RED"Qualcosa è andato storto!\n"ANSI_COLOR_RESET);
											exit(0);
										}
										printf("\nPremi invio per continuare\n");
							    		while( getchar() != '\n' );
							    		system("clear") ;
										break;
													
									case '2': 
										//MODIFICA RECENSIONE
										//se l'utente non ha ancora inserito una recensione, non può farlo
										if (recensione !=NULL){
											r = modifica_recensione(discussione->recensioni, utente->nick);
											if(r == 1){
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
												while( getchar() != '\n' );
												system("clear") ;
							    			}
							    			else{
								   				printf(ANSI_COLOR_YELLOW"\nRecensione modificata con successo!\n"ANSI_COLOR_RESET);
								   				printf("\nPremi invio per continuare\n");
							    				while( getchar() != '\n' );
							    				system("clear") ; 
							    			}
										}else{
											printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
								    		while( getchar() != '\n' );
								   			system("clear") ; 
										}
										break;
												
									case '3':
										//RIMUOVI RECENSIONE				
										if(recensione != NULL){
											printf(ANSI_COLOR_RED"Sei sicuro di voler rimuovere definitivamente la tua recensione?\n"ANSI_COLOR_RESET);
											printf("1)Si   2)No\n");
											scanf("%c", &scelta4);
											while ((c = getchar()) != '\n' && c != EOF);
											if(scelta4 != '1' && scelta4 != '2'){
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
				    							while( getchar() != '\n' );
				  								system("clear") ;
												break;
											}
											if(scelta4 == '1'){					
												cancella_recensione(discussione->recensioni, utente->nick);
												printf(ANSI_COLOR_YELLOW"Recensione rimossa con successo!\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
								   				while( getchar() != '\n' );
								   				system("clear") ; 
												}
										}else{
											printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
							    			while( getchar() != '\n' );
							    			system("clear") ;
							    		} 
										break;
										
									case '4':
										//RIMUOVI RECENSIONE ADMIN
										if(utente->admin == 1){
										printf("Inserisci il nickname dell'utente del quale vuoi rimuovere la recensione: ");
										fgets(nick, 31, stdin);
										nick[strcspn(nick, "\n")] = 0;
										r = cancella_recensione(discussione->recensioni, nick);
										if(r == 1){
											printf(ANSI_COLOR_RED"\nNon è presente alcuna recensione scritta dall'utente inserito!\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
							    			while( getchar() != '\n' );
							    			system("clear") ; 
											break;
										}
										printf(ANSI_COLOR_YELLOW"\nRecensione rimossa con successo!\n"ANSI_COLOR_RESET);
										printf("\nPremi invio per continuare\n");
							    		while( getchar() != '\n' );
							    		system("clear") ; 
										break;
										}else{
											printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
							    			while( getchar() != '\n' );
							    			system("clear") ; 
											break;
										}
										
									case '5':
										if(utente->admin == 1){
											printf(ANSI_COLOR_RED"Sei sicuro di voler rimuovere definitivamente questa discussione?\n"ANSI_COLOR_RESET);
											printf("1)Si   2)No\n");
											scanf("%c", &scelta3);
											while ((c = getchar()) != '\n' && c != EOF);
											if(scelta3 != '1' && scelta3 != '2'){
												printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
												while( getchar() != '\n' );
							  					system("clear") ;
												break;
											}
											if(scelta3 == '1'){					
												cancella_discussione(discussioni, generi, discussione->titolo);
												printf(ANSI_COLOR_YELLOW"\nDiscussione rimossa con successo!\n"ANSI_COLOR_RESET);
												printf("\nPremi invio per continuare\n");
						        				while( getchar() != '\n' );
						        				system("clear") ; 
											}
										}else{
											printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
											printf("\nPremi invio per continuare\n");
						        			while( getchar() != '\n' );
						        			system("clear");
										}
										break;
								
								default:
									printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
									printf("\nPremi invio per continuare\n");
							    	while( getchar() != '\n' );
							    	system("clear") ; 
									break;
								}
							 }while(scelta3 != '0' && scelta3 != '5');
								 
							break;
																
						default:
							printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
							printf("\nPremi invio per continuare\n");
				        	while( getchar() != '\n' );
				        	system("clear") ; 
							break;
					}
				}while(scelta2 != '0');
				break;
        			
        	case '3':
        		if(utente->admin != 1){
        			printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
					printf("\nPremi invio per continuare\n");
				    while( getchar() != '\n' );
				  	system("clear") ;        		
        		}else{
        			system("clear");
        			printf(ANSI_COLOR_YELLOW"\nEcco la lista dei generi già presenti:\n\n"ANSI_COLOR_RESET);
        			stampa_generi(*generi);		
        			printf("\nInserisci il genere che vuoi aggiungere: ");
        			fgets(nome_genere, 31, stdin);
					nome_genere[strcspn(nome_genere, "\n")] = 0;
					r = inserisci_ordinato_genere(generi, nome_genere);
					if(r == 1)
						exit(0);
					if(r == 2)
						printf(ANSI_COLOR_RED"\nQuesto genere è gia stato inserito!\n"ANSI_COLOR_RESET);
					if(r == 0)
						printf(ANSI_COLOR_YELLOW"\nNuovo genere aggiunto con successo!\n"ANSI_COLOR_RESET);
					printf("\nPremi invio per continuare\n");
				    while( getchar() != '\n' );
				  	system("clear") ; 				
				}		
				break;
						
        	case '4':
        		//RIMUOVI GENERE
        		if(utente->admin != 1){
        			printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
        			printf("\nPremi invio per continuare\n");
				    while( getchar() != '\n' );
				  	system("clear") ;
				  	
        		}else{
        			system("clear");
        			r = rimuovi_genere(generi);
        			if(r == 1)
        				printf(ANSI_COLOR_RED"\nIl genere inserito non è stato trovato!\n"ANSI_COLOR_RESET);
        			else
        				printf(ANSI_COLOR_YELLOW"\nGenere rimosso con successo!\n"ANSI_COLOR_RESET);
					printf("\nPremi invio per continuare\n");
				    while( getchar() != '\n' );
				  	system("clear") ;        		
        		}
        		break;
        			
        	default: 
        			printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
        			printf("\nPremi invio per continuare\n");
				    while( getchar() != '\n' );
				  	system("clear") ;
    				break;
    	}
	}while (scelta != '0');
}




//menù degli utenti
void menu_utente(lista_utenti* utenti, lista_discussioni* discussioni, lista_generi* generi, struct utente* utente){
	char scelta, scelta2, scelta3;
	lista_discussioni discussione = NULL;
	struct recensione* recensione = NULL;

	
	int r;
	char nick[31], password[31], password_nuova[31];


	do{
		system("clear");
		//MENU PRINCIPALE
		printf(ANSI_COLOR_YELLOW"\nCiao, %s, cosa vuoi fare?\n\n"ANSI_COLOR_RESET, utente->nick);
		printf("1) Inizia una discussione su un film o una serie tv\n");
		printf("2) Apri il menù delle discussioni\n");
		if(utente->admin == 1)
			printf("3) Lista utenti\n");
		else
			printf("3) Impostazioni profilo\n");
		printf("0) Logout\n\n");
		scanf("%c" ,&scelta);
		int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        switch(scelta){
        	case '0': break;
        	
        	case '1': 
     			//INIZIA UNA DISCUSSIONE
     			system("clear");
        		discussione = inizia_discussione(discussioni, generi, utente);
        		if(discussione == NULL){
		    		printf("\n\nPremi invio per continuare\n");
		            while( getchar() != '\n' );
		            system("clear");
		            break;
                }
                printf("\nPremi invio per continuare\n");
                while( getchar() != '\n' );
                system("clear");
        		
        		//Dopo aver iniziato la discussione, quest'ultima viene visualizzata
        		do{
        			stampa_scheda(discussione);
					stampa_recensioni(discussione->recensioni);
					printf("Cosa vuoi fare?\n\n");
    				printf("1) Scrivi una recensione\n");
    				//se l'utente ha gia' inserito una recensione puo' modificarla o cancellarla
    				recensione = cerca_recensione(discussione->recensioni, utente);
    				//Se l'utente e' un admin
    				if(utente->admin == 1){
    					if(recensione != NULL){
    						printf("2) Modifica la tua recensione\n");
    						printf("3) Rimuovi la tua recensione\n");
    					}
    					printf("4) Rimuovi la recensione di un utente\n");
    					printf("5) Cancella questa discussione\n");
    				}else{
    					//se l'utente non e' un admin
    					if(recensione != NULL){
    						printf("2) Modifica la tua recensione\n");
    						printf("3) Rimuovi la tua recensione\n");
    					}
    				}
    				printf("0) Ritorna al menù precedente\n\n");
    				scanf("%c", &scelta2);
    			
    				while ((c = getchar()) != '\n' && c != EOF);
    							
    				switch(scelta2){
    							
    					case '0': break;
    								
    					case '1': 
    						//AGGIUNGI RECENSIONE
    						//se l'utente ha gia' inserito una recensione non puo' aggiungerne un altra
    						recensione = cerca_recensione(discussione->recensioni, utente);
    						if(recensione != NULL){
    							printf(ANSI_COLOR_RED"\nHai già inserito una recensione!\n"ANSI_COLOR_RESET);
    							printf("\nPremi invio per continuare\n");
							    while( getchar() != '\n' );
							    system("clear") ;
    							break;
    						}
                    		system("clear");
    						r = aggiungi_recensione(discussione->recensioni, utente);
    						if (r == 1){
    							printf(ANSI_COLOR_RED"Qualcosa è andato storto!\n"ANSI_COLOR_RESET);
    							exit(0);
    						}
    						printf("\nPremi invio per continuare\n");
                    		while( getchar() != '\n' );
                    		system("clear") ;
    						break;
    									
    					case '2': 
    						//MODIFICA RECENSIONE
    						//se l'utente non ha ancora inserito una recensione, non può farlo
    						if (recensione !=NULL){
    							r = modifica_recensione(discussione->recensioni, utente->nick);
    							if(r == 1){
									printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
									printf("\nPremi invio per continuare\n");
		                			while( getchar() != '\n' );
		                			system("clear") ;
                    			}
                    			else{
                    				printf(ANSI_COLOR_YELLOW"\nRecensione modificata con successo!\n"ANSI_COLOR_RESET);
                    				printf("\nPremi invio per continuare\n");
                    				while( getchar() != '\n' );
                    				system("clear") ; 
                    			}
    						}else{
								printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
								printf("\nPremi invio per continuare\n");
                    			while( getchar() != '\n' );
                    			system("clear") ; 
    						}
    						break;
    								
    					case '3':
    						//RIMUOVI RECENSIONE				
    						if(recensione != NULL){
								printf(ANSI_COLOR_RED"Sei sicuro di voler rimuovere definitivamente la tua recensione?\n"ANSI_COLOR_RESET);
								printf("1)Si   2)No\n");
								scanf("%c", &scelta3);
								while ((c = getchar()) != '\n' && c != EOF);
								if(scelta3 != '1' && scelta3 != '2'){
									printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
									printf("\nPremi invio per continuare\n");
				    				while( getchar() != '\n' );
				  					system("clear") ;
									break;
								}
								if(scelta3 == '1'){					
									cancella_recensione(discussione->recensioni, utente->nick);
									printf(ANSI_COLOR_YELLOW"Recensione rimossa con successo!\n"ANSI_COLOR_RESET);
									printf("\nPremi invio per continuare\n");
                    				while( getchar() != '\n' );
                    				system("clear") ; 
									}
								system("clear") ;	
							}else{
								printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
								printf("\nPremi invio per continuare\n");
                    			while( getchar() != '\n' );
                    			system("clear") ;
                    		} 
    						break;
    					
    					case '4':
    						//RIMUOVI RECENSIONE ADMIN
    						if(utente->admin == 1){
								printf("Inserisci il nickname dell'utente del quale vuoi rimuovere la recensione: ");
								fgets(nick, 31, stdin);
								nick[strcspn(nick, "\n")] = 0;
								r = cancella_recensione(discussione->recensioni, nick);
								if(r == 1){
									printf(ANSI_COLOR_RED"\nNon è presente alcuna recensione scritta dall'utente inserito!\n"ANSI_COLOR_RESET);
									printf("\nPremi invio per continuare\n");
							    	while( getchar() != '\n' );
							    	system("clear") ; 
									break;
								}
								printf(ANSI_COLOR_RED"\nRecensione rimossa con successo!\n"ANSI_COLOR_YELLOW);
								printf("\nPremi invio per continuare\n");
							    while( getchar() != '\n' );
							 	system("clear") ; 
    						}else{
    							printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
    							printf("\nPremi invio per continuare\n");
                    			while( getchar() != '\n' );
                    			system("clear");
                    		} 
    						break;
    					
    					case '5':
    						if(utente->admin == 1){
								printf(ANSI_COLOR_RED"Sei sicuro di voler rimuovere definitivamente questa discussione?\n"ANSI_COLOR_RESET);
								printf("1)Si   2)No\n");
								scanf("%c", &scelta3);
								while ((c = getchar()) != '\n' && c != EOF);
								if(scelta3 != '1' && scelta3 != '2'){
									printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
									printf("\nPremi invio per continuare\n");
				    				while( getchar() != '\n' );
				  					system("clear") ;
									break;
								}
								if(scelta3 == '1'){					
									cancella_discussione(discussioni, generi, discussione->titolo);
									printf(ANSI_COLOR_YELLOW"\nDiscussione rimossa con successo!\n"ANSI_COLOR_RESET);
									printf("\nPremi invio per continuare\n");
                    				while( getchar() != '\n' );
                    				system("clear") ; 
									
								}
    						}else{
    							printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
    							printf("\nPremi invio per continuare\n");
                    			while( getchar() != '\n' );
                    			system("clear");
    						}
    						break;
    						
    						
    					default:
    						printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
    						printf("\nPremi invio per continuare\n");
                    		while( getchar() != '\n' );
                    		system("clear") ; 
    						break;
    				}
    			}while(scelta2 != '0' && scelta2 != '5');				
				
        		break;
        	
        	case '2': menu_discussioni(discussioni, generi, utente); break;
        	
        	case '3':
				system("clear");        		
        		//Se l'utente e' un admin, puo' bannare un utente
        		if(utente->admin == 1){
					do{
						stampa_lista_utenti(*utenti);
						
						printf("\n\nCosa vuoi fare?\n\n");
		    			printf("1) Banna un utente\n");
		    			printf("0) Ritorna al menù principale\n");
		    			scanf("%c" ,&scelta2);
		    			while ((c = getchar()) != '\n' && c != EOF);
		    			
		    			switch(scelta2){
		    			
		    			case '0': 
		    				break;
		    			
		    			case '1': 	
		    				printf("Inserisci il nickname dell'utente da bannare: ");
		    				fgets(nick, 31, stdin);
		    				nick[strcspn(nick, "\n")] = 0;
		    				r = cancella_utente(utenti, nick);
		    				if(r == 0)
		    					printf(ANSI_COLOR_YELLOW"\nUtente bannato con successo!"ANSI_COLOR_RESET);
		    				else
		    					printf(ANSI_COLOR_RED"\nUtente non trovato!\n"ANSI_COLOR_RESET);
		    				printf("\nPremi invio per continuare\n");
		                	while( getchar() != '\n' );
		                	system("clear") ; 
							break;
		    				
		    			
		    			default:
		    				printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
							printf("\nPremi invio per continuare\n");
		                	while( getchar() != '\n' );
		                	system("clear") ; 
							break;
		   				}		
					}while(scelta2 != '0');	
				}
        		else{      		
        		//Un utente normale invece puo' modificare la password o cancellare il proprio profilo
		    		do{
		    			printf(ANSI_COLOR_YELLOW"Impostazioni profilo\n"ANSI_COLOR_RESET);
		    			printf("\nCosa vuoi fare?\n");
		    			printf("1) Modifica password\n");
		    			printf("2) Elimina account\n");
		    			printf("0) Ritorna al menù principale\n");
		    			scanf("%c" ,&scelta2);
		    			while ((c = getchar()) != '\n' && c != EOF);
		    			
		    			switch(scelta2){
		    			
		    			case '0': break;
		    			
		    			case '1':	
		    				system("clear");
		    				printf("\nInserisci la tua vecchia password: ");
							fgets(password, 31, stdin);
							password[strcspn(password, "\n")] = 0;
							if(strcmp(utente->password, password) == 0){
								printf("\nInserisci la tua nuova password: ");
								fgets(password_nuova, 31, stdin);
								password_nuova[strcspn(password_nuova, "\n")] = 0;
								if(strcmp(password, password_nuova) == 0){
									printf(ANSI_COLOR_RED"Non puoi inserire di nuovo la stessa password!\n"ANSI_COLOR_RESET);
									printf("\nPremi invio per continuare\n");
		                			while( getchar() != '\n' );
		                			system("clear") ;
									break;
								}
								r = modifica_utente(utenti, utente->nick, password_nuova);
		    					if (r == 0){
		    						printf(ANSI_COLOR_YELLOW"\nPassword modificata con successo!\n"ANSI_COLOR_RESET);
		    						printf("\nPremi invio per continuare\n");
		                			while( getchar() != '\n' );
		                			system("clear") ;
		                		}
		                	}else {
		                		printf(ANSI_COLOR_RED"\nPassword non corretta\n"ANSI_COLOR_RESET);
		                		printf("\nPremi invio per continuare\n");
		                		while( getchar() != '\n' );
		                		system("clear") ;
		                	}		 
		    				break;
		    			
		    			case '2': 
		    				system("clear");   
		    				printf(ANSI_COLOR_RED"\nSei sicuro di voler eliminare definitivamente il tuo account?\n");
		    				printf("Ricorda! Anche dopo aver eliminato il tuo account, tutte le recensioni scritte da te rimarranno, a meno che non vengano rimosse da un admin!\n"ANSI_COLOR_RESET);
							printf("1)Si   2)No\n");
							scanf("%c", &scelta3);
							while ((c = getchar()) != '\n' && c != EOF);
							if(scelta3 != '1' && scelta3 != '2'){
								printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
								printf("\nPremi invio per continuare\n");
				    			while( getchar() != '\n' );
				  				system("clear") ;
								break;
							}
							if(scelta3 == '1'){				
								cancella_utente(utenti, utente->nick);
								printf(ANSI_COLOR_YELLOW"Account eliminato con successo!\n"ANSI_COLOR_RESET);
								printf("\nPremi invio per continuare\n");
		           				while( getchar() != '\n' );
		           				system("clear") ; 
		           				return;
							}
		    				break;
		    			
		   				default:
		   					printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
							printf("\nPremi invio per continuare\n");
		                	while( getchar() != '\n' );
		                	system("clear") ; 
							break;
		    		    }
		    		}while(scelta2 != '0');	
        		}
        		break;
        	
        	default: 
        			printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
        			printf("\nPremi invio per continuare\n");
		            while( getchar() != '\n' );
		           	system("clear") ; 
    				break;
    		}
    	}while (scelta != '0');
	}






//menù principale
void menu(lista_utenti* utenti, lista_discussioni* discussioni, lista_generi* generi){
    char scelta; 
    int r = 0; //risultato della funzione login
    struct utente* utente;   
    utente = NULL;
    system("clear");
    printf(ANSI_COLOR_YELLOW"Benvenuto nel\n\n");
    printf("  ______  __  .__   __.  _______  _______   ______   .______       __    __  .___  ___. \n");
    printf(" /      ||  | |  \\ |  | |   ____||   ____| /  __  \\  |   _  \\     |  |  |  | |   \\/   |\n" );
    printf("|  ,----'|  | |   \\|  | |  |__   |  |__   |  |  |  | |  |_)  |    |  |  |  | |  \\  /  | \n");
    printf("|  |     |  | |  . `  | |   __|  |   __|  |  |  |  | |      /     |  |  |  | |  |\\/|  | \n");
    printf("|  `----.|  | |  |\\   | |  |____ |  |     |  `--'  | |  |\\  \\----.|  `--'  | |  |  |  | \n");
    printf(" \\______||__| |__| \\__| |_______||__|      \\______/  | _| `._____| \\______/  |__|  |__| \n"ANSI_COLOR_RESET);
    printf("\n\n");
   	printf("\nPremi invio per continuare\n");
    while( getchar() != '\n' );
    
    do{
        //MENU INIZIALE
        system("clear");
        printf(ANSI_COLOR_YELLOW"\nMenù iniziale\n\n"ANSI_COLOR_RESET);
        printf("Scegli l'operazione desiderata: \n");
        printf("1) Accedi\n");
        printf("2) Registati\n");
        printf("3) Informazioni\n");
        printf("0) Esci\n\n");
        scanf("%c",&scelta);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        switch(scelta){
            case '0':
            		//ESCI 
            		printf("Arrivederci!\n"); 
            		break;
            
            case '1': 
            		//LOGIN
            		system("clear") ;
            		printf(ANSI_COLOR_YELLOW"\nInzio processo di login...\n\n"ANSI_COLOR_RESET);
            		r = login (*utenti , &utente);
            		if(r == 0){
            			//LOGIN EFFETTUATO
            			printf(ANSI_COLOR_YELLOW"\nLogin effettuato con successo!\n"ANSI_COLOR_RESET);
            			printf("\nPremi invio per continuare\n");
                    	while( getchar() != '\n' );
                    	system("clear") ;
                    	//SI PASSA AL MENU SUCCESSIVO
            			menu_utente(utenti, discussioni, generi, utente);
            		}
            		else{ 
            			//LOGIN FALLITO
            			printf(ANSI_COLOR_RED"\nCi dispiace, ma non e' stato trovato nessun utente con questa combinazione nickname e password!\n"ANSI_COLOR_RESET);
            			printf("\nPremi invio per continuare\n");
                    	while( getchar() != '\n' );
                    	system("clear") ;
            		}	
            		break;
            			
            case '2': 
					//SIGN IN
					system("clear") ;
					printf(ANSI_COLOR_YELLOW"\nInizio processo di registrazione...\n\n"ANSI_COLOR_RESET);
                    sign_in(utenti); 
                    printf("\nPremi invio per continuare\n");
                    while( getchar() != '\n' );
                    system("clear") ;
                    break;
    		
    		case '3':
    				//INFORMAZIONI
    				system("clear") ;
    				printf(ANSI_COLOR_YELLOW"Benvenuto nel forum, se sei un appassionato di film e serie tv, sei nel posto giusto!\n");
    				printf("Qui potrai condividere le tue opinioni sulle opere che guardi, aprendo una discussione\n"); 
    				printf("su un film o una serie, oppure ricercandone una nella lista di quelle già presenti.\n");
    				printf("All'interno di ogni discussione, ogni utente ha la possibilità di recensire l'opera\n");
    				printf("in questione, dandole anche un voto.\n");
    				printf("Per entrare basta registrarsi al forum attraverso la sezione Registrati nel menu principale!\n"ANSI_COLOR_RESET);
    				printf("\nPremi invio per continuare\n");
                    while( getchar() != '\n' );
                    system("clear") ;
                    break;
    		
    		default:
    				printf(ANSI_COLOR_RED"Scelta non valida\n"ANSI_COLOR_RESET);
    				printf("\nPremi invio per continuare\n");
                    while( getchar() != '\n' );
                    system("clear") ;
    				break;
       }
      }while (scelta != '0');
       
}
              
         	
