#include "utenti.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//crea una lista di utenti vuota
lista_utenti crea_lista_utenti(){
    return NULL;
}


//inserisce un nuovo utente alla lista utenti in modo ordinato
//restituisce 0 se tutto va bene, 1 se la malloc non funziona, 2 se esiste gia' un utente con lo stesso nickname
int inserisci_ordinato_utente(lista_utenti* utenti, char nome[], char cognome[], char nick[], char password[], int admin){
    lista_utenti r = *utenti;
    lista_utenti q = *utenti;
    //alloco il nuovo utente
    lista_utenti nuovo_utente = (lista_utenti)malloc(sizeof(struct utente));
    if(nuovo_utente == NULL) 
        return 1;
        
    //inserisco le informazioni
    strcpy(nuovo_utente->nome, nome);
    strcpy(nuovo_utente->cognome, cognome);
    strcpy(nuovo_utente->nick, nick);
    strcpy(nuovo_utente->password, password);
    nuovo_utente->admin = admin;
    
    //cerco la posizione nella quale inserire il nuovo utente
    while ((q != NULL) && (strcmp(q->nick, nuovo_utente->nick) < 0)){
        r = q;
        q = q->next;
    }
    //se esiste gia' un utente con lo stesso nickname ritorna 2
    if((q != NULL) && (strcmp(q->nick, nuovo_utente->nick) == 0)) 
        return 2;
    
    
    if(q==*utenti){
        nuovo_utente->next = *utenti;
        *utenti=nuovo_utente;
    }
    else{
        r->next = nuovo_utente;
        nuovo_utente->next = q;
    }
    return 0;
}



//trova un utente e ne restituisce il puntatore 
//restituisce NULL se l'elemento non c'e', altrimenti il puntatore al nodo trovato
lista_utenti cerca_utente(lista_utenti utenti, char nick[]){
	while ((utenti != NULL) && (strcmp(utenti->nick, nick)!=0)){
        //scorro la lista di utenti
        utenti = utenti->next;
    }
    //restituisco NULL oppure il puntatore al nodo contenente l'utente cercato
    return utenti;
}



//funzione che cancella un utente dalla lista 
int cancella_utente(lista_utenti* utenti, char nick[]){
    lista_utenti r = *utenti; 
    lista_utenti q = *utenti; 
    while ((q != NULL) && strcmp(q->nick, nick)!=0){
    	if(strcmp(q->nick, nick) > 0)
    		return 1; //l'utente non e' nella lista
        r = q;
        q = q->next;
    }
    if (q == NULL)  
        return 1; //l'utente non e' nella lista
    if (q==*utenti)
        (*utenti) = (*utenti)->next;
    else
        r->next = q->next;
    free(q);
    return 0; 
}

int modifica_utente(lista_utenti* utenti, char nick[], char password_nuova[]){
	lista_utenti r = NULL;
	r = cerca_utente(*utenti, nick);
	if(r == NULL)
		return 1;
	else
		strcpy(r->password, password_nuova);
	return 0;
}



//funzione che permette la registrazione di un utente nella piattaforma
void sign_in (lista_utenti* utenti){
    
    char nome[31], cognome[31], nick[31], password[31];
    
    printf("Inserisci il tuo nome: ");
	fgets(nome, 31, stdin);
	nome[strcspn(nome, "\n")] = 0;
	
    
    printf("\nInserisci il tuo cognome: ");
    fgets(cognome, 31, stdin);
	cognome[strcspn(cognome, "\n")] = 0;
	
    printf("\nInserisci il tuo nickname: ");
    fgets(nick, 31, stdin);
    nick[strcspn(nick, "\n")] = 0;
    
    do{
    	printf("\nInserisci una password di minimo 4 caratteri: ");
        fgets(password, 31, stdin);
        password[strcspn(password, "\n")] = 0;
        if (strlen(password) < 4) 
        	printf(ANSI_COLOR_RED"Password troppo corta!\n"ANSI_COLOR_RESET);   
    }
    while (strlen(password) < 4);
    int r;
    r = inserisci_ordinato_utente(utenti, nome, cognome, nick, password, 0);
    while (r == 2){
        printf(ANSI_COLOR_RED"\nCi dispiace, ma esiste già un utente con lo stesso nickname\n"ANSI_COLOR_RESET);
        printf("\nScegli un altro nickname:\n");
        fgets(nick, 31, stdin);
        nick[strcspn(nick, "\n")] = 0;
        r = inserisci_ordinato_utente(utenti, nome, cognome, nick, password, 0);   
    }     
    
    if (r == 1){
        printf(ANSI_COLOR_RED"Qualcosa è andato storto!\n"ANSI_COLOR_RESET);
        exit(0);
    }
    
    else if(r ==0){
    	printf(ANSI_COLOR_YELLOW"\nRegistrazione completata con successo!\n");
    	printf("Adesso puoi effettuare in login!\n"ANSI_COLOR_RESET);
    }
}


//funzione per il login dell'utente
int login (lista_utenti utenti, struct utente** utente){
    char nick[31], password[31];
    int i;
    
    printf("Inserisci il tuo nickname: ");
    fgets(nick, 31, stdin);
    nick[strcspn(nick, "\n")] = 0;
    
    printf("\nInserisci la tua password: ");
    fgets(password, 31, stdin);
    password[strcspn(password, "\n")] = 0;
    
    while(utenti != NULL){
    
    if ((strcmp(utenti->nick, nick) == 0) && (strcmp(utenti->password, password) == 0)) {
        *utente = utenti;	
        return 0;
    }
    utenti=utenti->next;
    }    

    //se l'utente non e' stato trovato ritorna 1
    return 1;
    	
}

//stampa la lista di utenti
void stampa_lista_utenti(lista_utenti utenti){    
    printf(ANSI_COLOR_YELLOW"\nEcco la lista di utenti registrati:\n"ANSI_COLOR_RESET);
   if(utenti == NULL){
       printf("\nNessun utente si è ancora registrato.\n");
       return;
   }
   
    while ((utenti != NULL)){
    	if (utenti->admin == 0)
        	printf("\n%s - %s %s", utenti->nick, utenti->nome, utenti->cognome);
        utenti = utenti->next;
    }
}


void cancella_utenti(lista_utenti* utenti){
	lista_utenti r = *utenti; //head
	lista_utenti q = NULL;        //next
	
	while(r != NULL){
		q = r->next;
		free(r);
		r = q;
	}
	utenti = NULL;

}

int salva_utenti(lista_utenti utenti){
	FILE* f = fopen("Utenti", "w");
	if(f == NULL)
		return 1;
	
	while(utenti != NULL){
		fprintf(f, "%s\n", utenti->nome);
		fprintf(f, "%s\n", utenti->cognome);
		fprintf(f, "%s\n", utenti->nick);
		fprintf(f, "%s\n", utenti->password);
		fprintf(f, "%d\n", utenti->admin);
		utenti = utenti->next;
	}
	fclose(f);	
	return 0;
}

int carica_utenti(lista_utenti* utenti){
	FILE* f = fopen("Utenti", "r");
	if(f == NULL)
		return 1;
	char nome[31], cognome[31], nick[31], password[31];
	int admin, risultato;
	while(!feof(f)){
		fgets(nome, 31, f);
		nome[strcspn(nome, "\n")] = 0;
		fgets(cognome,31, f);
		cognome[strcspn(cognome, "\n")] = 0;
		fgets(nick, 31, f);
		nick[strcspn(nick, "\n")] = 0;
		fgets(password, 31, f);
		password[strcspn(password, "\n")] = 0;
		fscanf(f, "%d\n", &admin);
	
		risultato = inserisci_ordinato_utente(utenti, nome, cognome, nick, password, admin);
		if(risultato == 1){
			printf(ANSI_COLOR_RED"\nQualcosa è andato storto\n"ANSI_COLOR_RESET);
			exit(0);		
		}		
	}
	fclose(f);
	return 0;
}

