#ifndef DISCUSSIONI_H
#define DISCUSSIONI_H

#include "utenti.h"
#include "recensioni.h"
#include "generi.h"


typedef enum {
	film, serie_tv}tipo;


struct discussioni{
	char titolo[51];
	tipo t;
	char regia[51];
	char attore1[31];
	char attore2[31];
	char attore3[31];
	char genere[31];
	int anno_uscita;
	int n; //questa variabile serve per numerare le discussioni
	char nick_utente[31];
	lista_recensioni recensioni;
	struct discussioni* next;                 
};

typedef struct discussioni* lista_discussioni;

typedef struct genere* lista_generi;

//crea una lista di discussioni vuota
lista_discussioni crea_lista_discussioni();

//verifica se la lista e' vuota
int is_emptyf(lista_discussioni discussioni);

//inserisce una nuova discussione alla lista in modo ordinato
int inserisci_ordinato_discussione(lista_discussioni* discussioni, char titolo[], tipo t, char regia[], char attore1[], char attore2[], char attore3[], int anno_uscita, char nick_utente[], char genere[]);

//cancella una discussione
int cancella_discussione(lista_discussioni* discussioni, lista_generi* generi, char titolo[]);

//accede a una discussione indicandone il titolo
lista_discussioni accesso_x(lista_discussioni discussioni, char titolo[]);

//modifica il genere di una discussione
int modifica_genere(lista_discussioni* discussione, char genere_nuovo[]);

//modifica la variabile n
int modifica_n(lista_discussioni* discussione, int n);

//funzione che permette all'utente di iniziare una discussione su un film/serie tv, aggiungendolo alla lista
lista_discussioni inizia_discussione(lista_discussioni* discussioni, lista_generi* generi, struct utente* utente);

//restituisce il puntatore alla discussione ricercata (sia film sia serie)
lista_discussioni ricerca_discussione_n(lista_discussioni discussioni, int n);

//restituisce il puntatore alla discussione ricercata (solo film)
lista_discussioni ricerca_discussione_nfilm(lista_discussioni discussioni, int n);

//restituisce il puntatore alla discussione ricercata (solo serie)
lista_discussioni ricerca_discussione_nserie(lista_discussioni discussioni, int n);

//resetta la variabile n di ogni descussione
void resetta_n(lista_discussioni* discussioni);

//stampa la scheda di un film/serie
void stampa_scheda(lista_discussioni discussioni);

//stampa l'elenco di discussioni aperte (sia film sia serie tv)
int stampa_discussioni(lista_discussioni discussioni);

//stampa l'elenco di discussioni aperte (film)
int stampa_discussioni_film(lista_discussioni discussioni);

//stampa l'elenco di discussioni aperte (serie tv)
int stampa_discussioni_serie(lista_discussioni discussioni);

//stampa la scheda del film e le sue recensioni e restituisce l'indirizzo della discussione visualizzata
lista_discussioni apri_discussione(lista_discussioni discussioni, struct utente* utente, int tipo);

void cancella_discussioni(lista_discussioni* discussioni, lista_generi* generi);

int salva_discussioni(lista_discussioni discussioni);

int carica_discussioni(lista_discussioni* discussioni, lista_generi* generi);
#endif
















