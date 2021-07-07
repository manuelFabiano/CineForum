#ifndef RECENSIONI_H
#define RECENSIONI_H
#include "utenti.h"

struct recensione{
	char titolo[51];   //titolo della recensione
	int voto;
	char nick_utente[31];   //nick dell'utente che ha scritto la recensione
	char contenuto_recensione[1001]; //le recensioni potranno contenere max 1000 caratteri
	struct recensione* next;
};

struct lista_recensioni{
	struct recensione* head;
	struct recensione* tail;
};

typedef struct lista_recensioni* lista_recensioni;


//crea una lista di recensioni vuota
lista_recensioni crea_lista_recensioni();

//verifica se la lista e' vuota
int is_emptyr(lista_recensioni recensioni);

//questa lista e' ordinata per tempo di inserimento, ovvero le recensioni inserite per prime rimangono in testa alla lista mentre le recensioni inserite per ultime vanno in coda alla lista
//inserisce un elemento in coda alla lista
int inserisci_coda_recensione (lista_recensioni recensioni, char titolo[], int voto, char nick_utente[], char contenuto_recensione[]);

//cancella l'intera lista di recensioni in una discussione
void cancella_lista_recensioni(lista_recensioni recensioni);

//cancella una recensione passando per parametro il nick dell'utente che l'ha inserita
int cancella_recensione(lista_recensioni recensioni, char nick[]);

//modifica il titolo di una recensione
int modifica_titolo(struct recensione* recensione, char titolo_nuovo[]);

//modifica il contenuto di una recensione
int modifica_contenuto(struct recensione* recensione, char contenuto_nuovo[]);

//modifica il voto di una recensione
int modifica_voto(struct recensione* recensione, int voto_nuovo);

//permette all'utente di modificare una recensione
int modifica_recensione(lista_recensioni recensioni, char nick[]);

//funzione per inserire una recensione su un film
int aggiungi_recensione(lista_recensioni recensioni, struct utente* utente);

//conta il numero di recensioni presenti in una discussione
int conta_recensioni(lista_recensioni recensioni);

//stampa tutte le recensioni in una discussione
void stampa_recensioni(lista_recensioni recensioni);

//funzione che scorre tutta la lista di recensioni e verifica se l'utente inserito come parametro ha gia' inserito una recensione e la restituisce, altrimenti restituisce NULL 
struct recensione* cerca_recensione(lista_recensioni recensioni, struct utente* utente);

//calcola la media dei voti inseriti nelle recensioni da ogni utente
float calcola_media(lista_recensioni recensioni);


#endif
