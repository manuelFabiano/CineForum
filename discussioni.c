#include "discussioni.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"


//crea una lista di discussioni vuota
lista_discussioni crea_lista_discussioni(){
    return NULL;
}

int is_emptyf(lista_discussioni discussioni){
    return (discussioni == NULL? 1:0);
}


//inserisce un nuovo film alla lista film in modo ordinato
//restituisce 0 se tutto va bene, 1 se la malloc non funziona, 2 se esiste gia' un film con lo stesso nome
int inserisci_ordinato_discussione(lista_discussioni* discussioni, char titolo[], tipo t, char regia[], char attore1[], char attore2[], char attore3[], int anno_uscita, char nick_utente[], char genere[]){
    lista_discussioni r = *discussioni;
    lista_discussioni q = *discussioni;
    //alloco il nuovo nodo
    lista_discussioni nuova_discussione = (lista_discussioni)malloc(sizeof(struct discussioni));
    if(nuova_discussione == NULL) 
        return 1;
        
    nuova_discussione->recensioni = crea_lista_recensioni();    
    //inserisco le informazioni
    strcpy(nuova_discussione->titolo, titolo);
    strcpy(nuova_discussione->regia, regia);
    strcpy(nuova_discussione->attore1, attore1);
    strcpy(nuova_discussione->attore2, attore2);
    strcpy(nuova_discussione->attore3, attore3);
    strcpy(nuova_discussione->nick_utente, nick_utente);
    strcpy(nuova_discussione->genere, genere);
    nuova_discussione->t = t;
    nuova_discussione->anno_uscita = anno_uscita;
    //cerco la posizione nella quale inserire il nuovo film
    while ((q != NULL) && (strcmp(q->titolo, nuova_discussione->titolo) < 0)){
        r = q;
        q = q->next;
    }
    //se esiste gia' un film con lo stesso titolo ritorna 2
    if((q != NULL) && (strcmp(q->titolo, nuova_discussione->titolo) == 0)) 
        return 2;
    
    
    if(q==*discussioni){
        nuova_discussione->next = *discussioni;
        *discussioni=nuova_discussione;
    }
    else{
        r->next = nuova_discussione;
        nuova_discussione->next = q;
    }
    return 0;
}

//cancella una discussione dalla lista
//restituisce 0 se tutto va a buon fine, 1 in caso contrario
int cancella_discussione(lista_discussioni* discussioni, lista_generi* generi, char titolo[]){
    //due puntatori di appoggio che faccio puntare inizialmente alla testa
    lista_discussioni r = *discussioni;
    lista_discussioni q = *discussioni; 
    //cerco l'elemento (al piu' arrivo alla fine della lista)
    while ((q != NULL) && (strcmp(titolo, (*discussioni)->titolo) != 0)){
        //r raggiunge q
        r = q;
        //q va avanti di uno
        q = q->next;
    }
    //se sono arrivato alla fine della lista l'elemento non c'e'
    if (q == NULL)  
        return 1;
    //se sono ancora in testa alla lista devo spostare la testa
    if (q==*discussioni)
        (*discussioni) = (*discussioni)->next;
    //se sono in una posizione intermedia il precedente deve puntare al successivo di q
    //nota: q punta all'elemento che voglio cancellare
    else
        r->next = q->next;
        
    //cancello la lista di recensioni
    cancella_lista_recensioni((q->recensioni));    
    //cancello il puntatore nella genere
    lista_generi genere = NULL;
    genere = accesso_genere(*generi, q->genere);
    cancella_puntatore(&(genere->puntatori), q->titolo);
    
    //dealloco l'elemento
    free(q);
    //tutto e' andato a buon fine
    return 0; 
}

//accesso a una discussione indicando il titolo
lista_discussioni accesso_x(lista_discussioni discussioni, char titolo[]){
	while(discussioni != NULL){
		if (strcmp(discussioni->titolo, titolo) == 0)
			return discussioni;
		discussioni = discussioni->next;
	}
	return NULL;
}	

int modifica_n(lista_discussioni* discussione, int n){
	if (discussione == NULL)
		return 1;
	(*discussione)->n = n;
	return 0;
}


//funzione che permette all'utente di iniziare una discussione su un film/serie tv, aggiungendolo alla lista
lista_discussioni inizia_discussione(lista_discussioni* discussioni, lista_generi* generi, struct utente* utente){
	char titolo[51], regia[51], sceneggiatura[51], attore1[31], attore2[31], attore3[31], nome_genere[31];
	int anno_uscita;
	tipo t;
	char temp;
	lista_generi genere = NULL;
	if(is_emptyg(*generi) == 1){
		printf(ANSI_COLOR_RED"\nNon è possibile iniziare una discussione perchè non è ancora stata aggiunto nessun genere."ANSI_COLOR_RESET);
		return NULL;
	}
	
	do{
		printf("\nEcco la lista di generi:\n\n");
		stampa_generi(*generi);	
		printf("Seleziona il genere: ");
		fgets(nome_genere, 31, stdin);
		nome_genere[strcspn(nome_genere, "\n")] = 0;
		genere = accesso_genere(*generi, nome_genere);
		if(genere == NULL)
			printf(ANSI_COLOR_RED"\nIl genere inserito non è valido!\n"ANSI_COLOR_RESET);	            //Genere non trovato
	}while(genere == NULL);
	
	
	do{
		printf("\nSeleziona il tipo:\n");	
		printf("1)Film    2)Serie tv\n");
		scanf("%c", &temp);
		if(temp != '1' && temp != '2'){
			printf(ANSI_COLOR_RED"\nScelta non valida\n"ANSI_COLOR_RESET);
			int c;
        	while ((c = getchar()) != '\n' && c != EOF);
        }	
	} while (temp != '1' && temp != '2');
	
	if (temp == '1')
		t = film;
	if(temp == '2')
		t = serie_tv;
	
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	
	printf("\nInserisci il titolo: ");  
	fgets(titolo, 51, stdin);
	titolo[strcspn(titolo, "\n")] = 0;
	
	printf("\nInserisci il nome del regista: ");               //nome o nomi dei o del regista/i
	fgets(regia, 51, stdin);
	regia[strcspn(regia, "\n")] = 0;
 	printf("\nInserisci i nomi di 3 attori\n");    
	printf("\nPrimo attore: ");
	fgets(attore1, 31, stdin);
	attore1[strcspn(attore1, "\n")] = 0;
	printf("\nSecondo attore: ");
	fgets(attore2, 31, stdin);
	attore2[strcspn(attore2, "\n")] = 0;
	printf("\nTerzo attore: ");
	fgets(attore3, 31, stdin);
	attore3[strcspn(attore3, "\n")] = 0;    
	
	
	printf("\nAnno di uscita: ");
	scanf("%d", &anno_uscita);
	while ((c = getchar()) != '\n' && c != EOF);
	if( anno_uscita > 2021 || anno_uscita < 1895 ){
	    printf(ANSI_COLOR_RED"\nErrore! Anno di uscita non valido\n"ANSI_COLOR_RESET);
		return NULL;
	}
	int r;
	r = inserisci_ordinato_discussione(discussioni, titolo, t, regia, attore1, attore2, attore3, anno_uscita, utente->nick, genere->nome_genere);
	
	if(r == 2){
        printf(ANSI_COLOR_RED"Errore! Esiste gia' una discussione su questo film!\n"ANSI_COLOR_RESET);
   		return NULL;
    }     
    
    if (r == 1){
        printf(ANSI_COLOR_RED"Qualcosa e' andato storto!\n"ANSI_COLOR_RESET);
        exit(0);
    }
    
    printf(ANSI_COLOR_YELLOW"\nDiscussione iniziata con successo!\n"ANSI_COLOR_RESET);
    
    lista_discussioni discussione = NULL;
    discussione = accesso_x(*discussioni, titolo);
    
    inserisci_ordinato_puntatore(&(genere->puntatori), discussione);
        
    return discussione;
}



//restituisce il puntatore alla discussione ricercata (sia film sia serie)
//restituisce NULL se la discussione non viene trovata
lista_discussioni ricerca_discussione_n(lista_discussioni discussioni, int n){
	//se l'indice non e' valido
	if(n<1){
		return NULL;
	}
	while(discussioni!=NULL){
		if (discussioni->n == n)
			return discussioni;
		discussioni = discussioni->next;
	}
	return NULL;
}

//restituisce il puntatore alla discussione ricercata (solo film)
//restituisce NULL se la discussione non viene trovata
lista_discussioni ricerca_discussione_nfilm(lista_discussioni discussioni, int n){
	//se l'indice non e' valido
	if(n<1){
		return NULL;
	}
	while(discussioni!=NULL){
		if ((discussioni->t == film) && (discussioni->n == n))
			return discussioni;
		discussioni = discussioni->next;
	}
	return NULL;
}

//restituisce il puntatore alla discussione ricercata (solo serie)
//restituisce NULL se la discussione non viene trovata
lista_discussioni ricerca_discussione_nserie(lista_discussioni discussioni, int n){
	//se l'indice non e' valido
	if(n<1){
		return NULL;
	}
	while(discussioni!=NULL){
		if ((discussioni->t == serie_tv) && (discussioni->n == n))
			return discussioni;
		discussioni = discussioni->next;
	}
	return NULL;
}


		
void resetta_n(lista_discussioni* discussioni){
	lista_discussioni p = *discussioni;
	
	while(p != NULL){
	modifica_n(&p, 0);
	p = p->next;
	}
}	
	
		
		
		
//stampa la scheda di una discussione
void stampa_scheda(lista_discussioni discussione){
	printf(ANSI_COLOR_YELLOW"\n ______________________________________________________");
	if (discussione->t == 0)
		printf("\n|Scheda del film:\n|");
	else
		printf("\n|Scheda della serie:\n|");
	
	printf("\n|Titolo: %s\n|", discussione->titolo);
	printf("\n|Genere: %s\n|", discussione->genere);
	printf("\n|Regia di: %s\n|", discussione->regia);
	printf("\n|Cast: %s, %s, %s \n|", discussione->attore1, discussione->attore2, discussione->attore3);
	printf("\n|Anno di uscita : %d\n|", discussione->anno_uscita);
	if(conta_recensioni(discussione->recensioni) == 0)
		printf("\n|Media voti: N/A\n|");
	else
		printf("\n|Media voti: %.1f\n|"ANSI_COLOR_RESET, calcola_media(discussione->recensioni));
	printf("\n\n\n---------------------------------------------------------\n\n\n");
}


//stampa l'elenco di discussioni aperte (sia film sia serie tv)
//ritorna 1 se la lista e' vuota
int stampa_discussioni(lista_discussioni discussioni){
	int n = 0;
	resetta_n(&discussioni);
	printf(ANSI_COLOR_YELLOW"\nEcco l'elenco di tutte le discussioni aperte sui film e le serie tv:\n\n"ANSI_COLOR_RESET);
	if(is_emptyf(discussioni) == 1){
		printf("\nNon sono ancora state aperte discussioni su film e serie tv.\n");
		return 1;
	}
	while ((discussioni != NULL)){
		n++;
		modifica_n(&discussioni, n);
        printf("\n%d) %s  ", discussioni->n, discussioni->titolo);
        if(discussioni->t == film)
        	printf("(Film)");
        else
        	printf("(Serie TV)");
        printf("\n   Discussione iniziata da: %s\n", discussioni->nick_utente);                                     
        discussioni = discussioni->next;
    }
	return 0;
}


//stampa l'elenco di discussioni aperte (film)
int stampa_discussioni_film(lista_discussioni discussioni){
	int n = 0;
	resetta_n(&discussioni);
	printf(ANSI_COLOR_YELLOW"\nEcco l'elenco di tutte le discussioni aperte sui film:\n\n"ANSI_COLOR_RESET);
	while ((discussioni != NULL)){
        if(discussioni->t == film){
        	n++;
        	modifica_n(&discussioni, n);
        	printf("\n%d) %s\n", discussioni->n, discussioni->titolo);  
        	printf("   Discussione iniziata da: %s\n", discussioni->nick_utente);
        	}                                              
        discussioni = discussioni->next;
    }
	if(n == 0){
		printf("\nNon sono ancora state aperte discussioni sui film\n");
		return 1;
	}
	else return 0;
}


//stampa l'elenco di discussioni aperte (serie tv)
int stampa_discussioni_serie(lista_discussioni discussioni){
	int n = 0;
	resetta_n(&discussioni);
	printf(ANSI_COLOR_YELLOW"\nEcco l'elenco di tutte le discussioni aperte sulle serie tv:\n\n"ANSI_COLOR_RESET);
	while ((discussioni != NULL)){
		if(discussioni->t == serie_tv){
			n++;
			modifica_n(&discussioni, n);
        	printf("\n%d) %s\n", discussioni->n, discussioni->titolo);  
        	printf("   Discussione iniziata da: %s\n", discussioni->nick_utente);  
        }                                            
        discussioni = discussioni->next;
    }
	if(n == 0){
		printf("\nNon sono ancora state aperte discussioni sulle serie tv.\n");
		return 1;
	}
	else return 0;
}

//ritorna NULL se la discussione non e' stata trovata, altrimenti restituisce l'indirizzo della discussione ricercata
lista_discussioni apri_discussione(lista_discussioni discussioni, struct utente* utente, int tipo){
	if(is_emptyf(discussioni) == 1)
		return NULL;
	
	int n, scelta;
	lista_discussioni discussione = NULL;
	
	printf("\n\nInserisci il numero della discussione da visualizzare: ");
	scanf("%d", &n);
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
				
	if(tipo == 1) //sia film sia serie
		discussione = ricerca_discussione_n(discussioni, n);
	
	if(tipo == 2) //solo film
		discussione = ricerca_discussione_nfilm(discussioni, n);
	
	if(tipo == 3) //solo serie
		discussione = ricerca_discussione_nserie(discussioni, n);
	
	if(discussione == NULL)
		return NULL;
	
	return discussione;
}


void cancella_discussioni(lista_discussioni* discussioni, lista_generi* generi){
	lista_discussioni r = *discussioni; //head
	lista_discussioni q = NULL;        //next
	
	while(r != NULL){
		q = r->next;
		cancella_lista_recensioni((r->recensioni));    
    	//cancello il puntatore nella genere
   	 	lista_generi genere = NULL;
   		genere = accesso_genere(*generi, r->genere);
    	cancella_puntatore(&(genere->puntatori), r->titolo);
		free(r);
		r = q;
	}
	discussioni = NULL;
}


int salva_discussioni(lista_discussioni discussioni){
	FILE* f = fopen("Discussioni", "w");
	if(f == NULL)
		return 1;
	struct recensione* p = NULL;
	while(discussioni != NULL){
		fprintf(f, "%s\n", discussioni->genere);
		//se è un film
		if(discussioni->t == 0)
			fprintf(f, "0\n");
		//se è una serie tv
		if(discussioni->t == 1)
			fprintf(f, "1\n");	
		fprintf(f, "%s\n", discussioni->titolo);
		fprintf(f, "%s\n", discussioni->regia);
		fprintf(f, "%s\n", discussioni->attore1);
		fprintf(f, "%s\n", discussioni->attore2);
		fprintf(f, "%s\n", discussioni->attore3);
		fprintf(f, "%d\n", discussioni->anno_uscita);
		fprintf(f, "%s\n", discussioni->nick_utente);
		
		//salvo le recensioni
		p = discussioni->recensioni->head;
		while(p != NULL){
			fprintf(f, "%s\n", p->titolo);
			fprintf(f, "%s\n", p->contenuto_recensione);
			fprintf(f, "%s\n", p->nick_utente);
			fprintf(f, "%d\n", p->voto);
			p = p->next;		
		}
		fprintf(f, "FINE_RECENSIONI\n");
		discussioni = discussioni->next;
	}
	fprintf(f, "FINE_DISCUSSIONI\n");
	fclose(f);	
	return 0;
}


int carica_discussioni(lista_discussioni* discussioni, lista_generi* generi){
	FILE* f = fopen("Discussioni", "r");
	if(f == NULL)
		return 1;
	char genere[31], titolo[51], regia[51], attore1[31], attore2[31], attore3[31], nick_utente[31], titolo_recensione[51], contenuto_recensione[1001], nick_utente_recensione[31];
	int anno_uscita, temp, voto, risultato;
	tipo t;
	lista_discussioni discussione = NULL;
	lista_generi genere1 = NULL;
	
	while(fgets(genere, 31, f)){
		if(strcmp(genere, "FINE_DISCUSSIONI\n") == 0){
				break;
		}	
		genere[strcspn(genere, "\n")] = 0;
		fscanf(f, "%d\n", &temp);
		if(temp == 0)
			t = film;
		if(temp == 1)
			t = serie_tv;
		fgets(titolo, 51, f);
		titolo[strcspn(titolo, "\n")] = 0;			
		fgets(regia, 51, f);
		regia[strcspn(regia, "\n")] = 0;
		fgets(attore1, 31, f);
		attore1[strcspn(attore1, "\n")] = 0;
		fgets(attore2, 31, f);
		attore2[strcspn(attore2, "\n")] = 0;
		fgets(attore3, 31, f);
		attore3[strcspn(attore3, "\n")] = 0;
		fscanf(f, "%d\n", &anno_uscita);
		fgets(nick_utente, 31, f);
		nick_utente[strcspn(nick_utente, "\n")] = 0;
		
		risultato = inserisci_ordinato_discussione(discussioni, titolo, t, regia, attore1, attore2, attore3, anno_uscita, nick_utente, genere);
		if(risultato == 1){
			printf(ANSI_COLOR_RED"\nQualcosa è andato storto\n"ANSI_COLOR_RESET);
			exit(0);		
		}		
		genere1 = accesso_genere(*generi, genere);
		discussione = accesso_x(*discussioni, titolo);
		inserisci_ordinato_puntatore(&(genere1->puntatori), discussione);
		
		
		while(fgets(titolo_recensione, 51, f)){
			if(strcmp(titolo_recensione, "FINE_RECENSIONI\n") == 0){
				break;
			}
			titolo_recensione[strcspn(titolo_recensione, "\n")] = 0;
			fgets(contenuto_recensione, 1001, f);
			contenuto_recensione[strcspn(contenuto_recensione, "\n")] = 0;				
			fgets(nick_utente_recensione, 31,f);
			nick_utente_recensione[strcspn(nick_utente_recensione, "\n")] = 0;		
			fscanf(f, "%d\n", &voto);
				
			risultato = inserisci_coda_recensione(discussione->recensioni, titolo_recensione, voto, nick_utente_recensione, contenuto_recensione);
			if(risultato == 1){
				printf(ANSI_COLOR_RED"\nQualcosa è andato storto\n"ANSI_COLOR_RESET);
				exit(0);		
			}		
		}
	}
	fclose(f);
	return 0;
}

