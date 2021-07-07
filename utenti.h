#ifndef UTENTI_H
#define UTENTI_H


//struttura utente
struct utente{
    char nome[31];
    char cognome[31];
    char nick[31];
    char password[31];
    int admin;   //se e' 1 l'utente e' un admin, altrimenti 0
    struct utente* next;
} utente;

typedef struct utente* lista_utenti;

//crea una lista di utenti vuota
lista_utenti crea_lista_utenti();

//inserisce ordinatamente per nick
int inserisci_ordinato_utente(lista_utenti* utenti, char nome[], char cognome[], char nick[], char password[], int admin);

//cerca un utente e ne restituisce il puntatore 
lista_utenti cerca_utente(lista_utenti utenti, char nick[]);

//cancella un utente dalla lista
int cancella_utente(lista_utenti* utenti, char nick[]);

//modifica la password dell'utente
int modifica_utente(lista_utenti* utenti, char nick[], char password_nuova[]);

//registra un utente nella piattaforma
void sign_in(lista_utenti* utenti);

//login dell'utente
int login (lista_utenti utenti, struct utente** utente);

//stampa la lista di utenti
void stampa_lista_utenti(lista_utenti utenti);

void cancella_utenti(lista_utenti* utenti);

int salva_utenti(lista_utenti utenti);

int carica_utenti(lista_utenti* utenti);
#endif

