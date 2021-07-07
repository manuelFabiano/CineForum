#ifndef GENERI_H
#define GENERI_H

#include "discussioni.h"

typedef struct discussioni* lista_discussioni;

struct puntatore_discussione{
	lista_discussioni discussione; //puntatore alla discussione
	struct puntatore_discussione* next;
};

typedef struct puntatore_discussione* lista_puntatori;

struct genere{
	char nome_genere[31];
	lista_puntatori puntatori;
	struct genere* next;
};

typedef struct genere* lista_generi;

//crea una lista di puntatori vuota
lista_puntatori crea_lista_puntatori();

//crea una lista di generi vuota
lista_generi crea_lista_generi();

//verifica se la lista di puntatori e' vuota
int is_emptyp(lista_puntatori puntatori);

//verifica se la lista di generi e' vuota
int is_emptyg(lista_generi generi);

//inserisce un puntatore alla lista in modo ordinato
int inserisci_ordinato_puntatore(lista_puntatori* puntatori, lista_discussioni discussione);

//inserisce un genere alla lista in modo ordinato 
int inserisci_ordinato_genere(lista_generi* generi, char nome_genere[]);

//cancella un puntatore dalla lista
int cancella_puntatore(lista_puntatori* puntatori, char titolo[]);

//cancella un genere dalla lista
int cancella_genere(lista_generi* generi, char nome_genere[]);

//ricerca un puntatore dalla lista in base al titolo 
lista_puntatori accesso_puntatore(lista_puntatori puntatori, char titolo[]);

//ricerca un genere dalla lista
lista_generi accesso_genere(lista_generi generi, char nome_genere[]);

//sposta un puntatore da un genere a un altr
void sposta_puntatore(lista_puntatori* puntatore, lista_generi genere);

//permette all'admin di rimuovere un genere dalla lista, spostando tutti i puntatori in altri generi
int rimuovi_genere(lista_generi* generi);

//filtra le discussioni per genere
int stampa_filtro(lista_generi generi, char nome_genere[]);

int filtra(lista_generi generi);

void stampa_puntatori(lista_puntatori puntatori);

void stampa_generi(lista_generi generi);

void cancella_generi(lista_generi* generi);

int salva_generi(lista_generi generi);

int carica_generi(lista_generi* generi);

#endif
