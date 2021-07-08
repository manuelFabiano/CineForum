#include "utenti.h"
#include "recensioni.h"
#include "discussioni.h"
#include "generi.h"
#include "menu.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

              
int main(){
    lista_utenti utenti= crea_lista_utenti();
	lista_discussioni discussioni= crea_lista_discussioni();
	lista_generi generi= crea_lista_generi();
    
    //per caricare
    int r;
    r = carica_utenti(&utenti);
    if (r == 1)
    	printf(ANSI_COLOR_RED"\nQualcosa è andato storto durante il caricamento degli utenti\n"ANSI_COLOR_RESET);
    r = carica_generi(&generi);
    if (r == 1)	
    	printf(ANSI_COLOR_RED"\nQualcosa è andato storto durante il caricamento dei generi\n"ANSI_COLOR_RESET);
    r = carica_discussioni(&discussioni, &generi);
    if (r == 1)	
    	printf(ANSI_COLOR_RED"\nQualcosa è andato storto durante il caricamento delle discussioni\n"ANSI_COLOR_RESET);
    
    inserisci_ordinato_utente(&utenti, "admin", "admin", "admin" , "admin" , 1);
    
    //menu principale
    menu(&utenti, &discussioni, &generi);
    
    //per salvare
    r = salva_utenti(utenti);
     if (r == 1)
    	printf(ANSI_COLOR_RED"\nQualcosa è andato storto durante il salvataggio degli utenti\n"ANSI_COLOR_RESET);
    r = salva_generi(generi);
     if (r == 1)
    	printf(ANSI_COLOR_RED"\nQualcosa è andato storto durante il salvataggio dei generi\n"ANSI_COLOR_RESET);
    r = salva_discussioni(discussioni);
     if (r == 1)
    	printf(ANSI_COLOR_RED"\nQualcosa è andato storto durante il salvataggio delle discussioni\n"ANSI_COLOR_RESET);
   
    //per svuotare la memoria
  	cancella_utenti(&utenti);
  	cancella_discussioni(&discussioni, &generi);
  	cancella_generi(&generi);
}

