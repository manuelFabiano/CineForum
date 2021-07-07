#ifndef MENU_H
#define MENU_H

#include "utenti.h"
#include "recensioni.h"
#include "discussioni.h"
#include "generi.h"


void menu_visualizza_discussioni(lista_discussioni* discussioni, lista_generi* generi, struct utente* utente);

//menu' principale discussioni
void menu_discussioni(lista_discussioni* discussioni, lista_generi* generi, struct utente* utente);

//menu' degli utenti/admin
void menu_utente(lista_utenti* utenti, lista_discussioni* discussioni, lista_generi* generi, struct utente* utente);

//menu' principale
void menu(lista_utenti* utenti, lista_discussioni* discussioni, lista_generi* generi);



#endif
