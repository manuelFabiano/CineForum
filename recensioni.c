#include "recensioni.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//crea una lista di recensioni vuota
lista_recensioni crea_lista_recensioni(){
    lista_recensioni recensioni=(lista_recensioni)malloc(sizeof(struct lista_recensioni));
	if(recensioni == NULL)	
		return NULL;	//Errore
	else{
		recensioni->head = NULL;
		recensioni->tail = NULL;
		return recensioni;
	}
}

//verifica se la lista e' vuota
int is_emptyr(lista_recensioni recensioni){
    if(recensioni->head == NULL) return 1;
    else return 0;
}

//questa lista e' ordinata per tempo di inserimento, ovvero le recensioni inserite per prime rimangono in testa alla lista mentre le recensioni inserite per ultime vanno in coda alla lista
//inserisce un elemento in coda alla lista
//restituisce 0 se tutto va a buon fine, 1 in caso contrario
int inserisci_coda_recensione (lista_recensioni recensioni, char titolo[], int voto, char nick_utente[], char contenuto_recensione[]){
    struct recensione* nuova_recensione = (struct recensione*)malloc(sizeof(struct recensione));
    if(nuova_recensione == NULL)
    	return 1;
   //popolo il nuovo nodo con i dati
    strcpy(nuova_recensione->titolo, titolo);
    nuova_recensione->voto = voto;
	strcpy(nuova_recensione->nick_utente, nick_utente);
    strcpy(nuova_recensione->contenuto_recensione, contenuto_recensione);
	nuova_recensione->next = NULL;
	
	if(is_emptyr(recensioni) == 1)
		recensioni->head = nuova_recensione;
	else
		recensioni->tail->next = nuova_recensione;
	
	recensioni->tail = nuova_recensione;
	
	return 0;
}  

//funzione che cancella l'intera lista di recensioni in una discussione
void cancella_lista_recensioni(lista_recensioni recensioni){
	struct recensione* r = recensioni->head; //head
	struct recensione* q = NULL;        //next
	
	while(r != NULL){
		q = r->next;
		free(r);
		r = q;
	}
	recensioni->head = NULL;
	recensioni->tail = NULL;
	free(recensioni);
}

//cancella una recensione dalla lista
//restituisce 0 se tutto va a buon fine, 1 in caso contrario
int cancella_recensione(lista_recensioni recensioni, char nick[]){
    if(is_emptyr(recensioni)==1)	
    	return 1;
    //due puntatori di appoggio che faccio puntare inizialmente alla testa
    struct recensione* r = recensioni->head;
    struct recensione* q = recensioni->head; 
    //cerco l'elemento (al piu' arrivo alla fine della lista)
    while ((q != NULL) && (strcmp (nick, q->nick_utente) != 0)){
    	r = q;
    	q = q->next;
    }
    if(q == NULL)
    	return 1; //elemento non trovato
    if(strcmp (nick, q->nick_utente) == 0){
    	//se e' il primo
    	if(q == recensioni->head)
    		recensioni->head = q->next;
    	//se e' l'ultimo
    	if(q->next == NULL)
    		recensioni->tail = r;
    	r->next = q->next;
    	free(q);
    	return 0;
    }
}

//modifica il titolo di una recensione
int modifica_titolo(struct recensione* recensione, char titolo_nuovo[]){
	if (recensione == NULL)
		return 1;
	
	strcpy(recensione->titolo, titolo_nuovo);
	return 0;
}

//modifica il contenuto di una recensione
int modifica_contenuto(struct recensione* recensione, char contenuto_nuovo[]){
	if (recensione == NULL)
		return 1;
	
	strcpy(recensione->contenuto_recensione, contenuto_nuovo);
	return 0;
}

//modifica il voto di una recensione
int modifica_voto(struct recensione* recensione, int voto_nuovo){
	if (recensione == NULL)
		return 1;
	
	recensione->voto = voto_nuovo;
	return 0;
}

//ritorna 0 se tutto va bene, 1 in caso di errore  
int modifica_recensione(lista_recensioni recensioni, char nick[]){
	char titolo[51], contenuto_recensione[1001];
	int voto;
	char scelta;
	
	printf("\nCosa vuoi modificare?\n\n");
	printf("1) Titolo   2) Contenuto   3)Voto\n\n");
	scanf("%c", &scelta);
	if (scelta != '1' && scelta != '2' && scelta != '3')
		return 1;
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	
	if(scelta == '1'){
		printf("\nInserisci il nuovo titolo: ");
		fgets(titolo, 51, stdin);
		titolo[strcspn(titolo, "\n")] = 0;
		while ((c = getchar()) != '\n' && c != EOF);
	} 
	
	if(scelta == '2'){
		printf("\nInserisci il nuovo contenuto della recensione: ");
		fgets(contenuto_recensione, 1000, stdin);
		contenuto_recensione[strcspn(contenuto_recensione, "\n")] = 0;
		while ((c = getchar()) != '\n' && c != EOF);
	}
	
	if(scelta == '3'){
		do{
			printf("\nInserisci il nuovo voto: ");
			scanf("%d", &voto);
			while ((c = getchar()) != '\n' && c != EOF);
			if(voto < 0 || voto > 10)
    			printf(ANSI_COLOR_RED"\nIl voto deve essere compreso fra 0 e 10\n"ANSI_COLOR_RESET);
		}while(voto < 0 || voto > 10);
	}  
	
	//ricerco la recensione
	struct recensione* p = recensioni->head;
	while(p != NULL){
		if(strcmp(nick, p->nick_utente) == 0){
			if(scelta == '1')
				 modifica_titolo(p, titolo);
			if(scelta == '2')
				 modifica_contenuto(p, contenuto_recensione);
			if(scelta == '3')
				 modifica_voto(p, voto);
			return 0;
		}		
		p = p->next;
	}
}

    
//funzione che permette di inserire una recensione su un film
int aggiungi_recensione(lista_recensioni recensioni, struct utente* utente){
	char titolo[51];
	
	printf("\nInserisci il titolo della recensione: ");
	fgets(titolo, 51, stdin);
	titolo[strcspn(titolo, "\n")] = 0;
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	printf("\nScrivi la tua recensionec (max. 1000 caratteri):\n");
	
	char contenuto_recensione[1001];
	
    fgets(contenuto_recensione, 1001, stdin);
    contenuto_recensione[strcspn(contenuto_recensione, "\n")] = 0;
    while ((c = getchar()) != '\n' && c != EOF);
    
    int voto;
    do{
    	printf("\nDai un voto da 1 a 10 al film: ");
    	scanf("%d", &voto);
    	if(voto < 0 || voto > 10)
    		printf(ANSI_COLOR_RED"\nIl voto deve essere compreso fra 0 e 10\n"ANSI_COLOR_RESET);
  	}while(voto < 0 || voto > 10);
    
    while ((c = getchar()) != '\n' && c != EOF);
    
    
    int r;
    r = inserisci_coda_recensione(recensioni, titolo, voto, utente->nick, contenuto_recensione);
    
    if (r == 1){
    	printf(ANSI_COLOR_RED"Qualcosa e' andato storto!\n"ANSI_COLOR_RESET);
    	exit(0);
    }	
    
    if (r == 0)
    printf(ANSI_COLOR_YELLOW"\nRecensione aggiunta con successo!\n\n"ANSI_COLOR_RESET);
    
    return 0;

}

//funzione che conta il numero di recensioni presenti in una discussione
int conta_recensioni(lista_recensioni recensioni){
	int N = 0;
	struct recensione* p = recensioni->head;
	
	while(p != NULL){
		N++;
		p = p->next;
	}
	return N;
}

void stampa_recensioni(lista_recensioni recensioni){
	if (is_emptyr(recensioni) == 1)
		printf(ANSI_COLOR_YELLOW"Non sono ancora state scritte recensioni.\n\n"ANSI_COLOR_RESET);
	else if (conta_recensioni(recensioni) == 1)
			printf(ANSI_COLOR_YELLOW"In questa discussione è presente 1 recensione:\n\n\n"ANSI_COLOR_RESET);
	else 
		printf(ANSI_COLOR_YELLOW"In questa discussione sono presenti %d recensioni:\n\n\n"ANSI_COLOR_RESET, conta_recensioni(recensioni));
	
	struct recensione* p = recensioni->head;
	while(p != NULL){
		printf(ANSI_COLOR_YELLOW"Recensione di %s: "ANSI_COLOR_RESET, p->nick_utente);
		printf("%s\n\n", p->titolo);
		printf("%s\n", p->contenuto_recensione);
		printf("\nVoto: %d\n\n\n", p->voto);
		
		p = p->next;
	}
}

//funzione che scorre tutta la lista di recensioni e verifica se l'utente inserito come parametro ha gia' inserito una recensione e la restituisce, altrimenti restituisce NULL 
struct recensione* cerca_recensione(lista_recensioni recensioni, struct utente* utente){
	struct recensione* p = recensioni->head;
	while(p != NULL){
		if(strcmp(utente->nick, p->nick_utente) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}


//calcola la media dei voti inseriti nelle recensioni da ogni utente
float calcola_media(lista_recensioni recensioni){
	float media=0;
	int N = conta_recensioni(recensioni);
	
	struct recensione* p = recensioni->head;
	while(p != NULL){
	media += p->voto;
	p = p->next;
	}
	media = media / N;
	return media;
}


    
    
    
    
