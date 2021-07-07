#include "generi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"


//crea una lista di puntatori vuota
lista_puntatori crea_lista_puntatori(){
	return NULL;
}
//crea una lista di generi vuota
lista_generi crea_lista_generi(){
	return NULL;
}

//verifica se la lista di puntatori e' vuota, restituisce 1 se si
int is_emptyp(lista_puntatori puntatori){
 	return (puntatori == NULL? 1:0);
}

//verifica se la lista di generi e' vuota, restituisce 1 se si
int is_emptyg(lista_generi generi){
	 return (generi == NULL? 1:0);
}

//inserisce un puntatore alla lista in modo ordinato
int inserisci_ordinato_puntatore(lista_puntatori* puntatori, lista_discussioni discussione){
	lista_puntatori r = *puntatori;
    lista_puntatori q = *puntatori;
    //alloco il nuovo nodo
    lista_puntatori nuovo_puntatore = (lista_puntatori)malloc(sizeof(struct puntatore_discussione));
    if(nuovo_puntatore == NULL) 
        return 1;
        
    //inserisco le informazioni
    nuovo_puntatore->discussione = discussione;
    
    //cerco la posizione nella quale inserire il nuovo puntatore
    while ((q != NULL) && (strcmp(q->discussione->titolo, nuovo_puntatore->discussione->titolo) < 0)){
        r = q;
        q = q->next;
    }
    //se q e' ancora in testa  
    if(q == *puntatori){
        nuovo_puntatore->next = *puntatori;
        *puntatori = nuovo_puntatore;
    }
    else{
        r->next = nuovo_puntatore;
        nuovo_puntatore->next = q;
    }
    return 0;
}


//inserisce un genere alla lista in modo ordinato 
int inserisci_ordinato_genere(lista_generi* generi, char nome_genere[]){
	lista_generi r = *generi;
    lista_generi q = *generi;
    //alloco il nuovo nodo
    lista_generi nuovo_genere = (lista_generi)malloc(sizeof(struct genere));
    if(nuovo_genere == NULL) 
        return 1;
    
    //popolo il nodo    
    nuovo_genere->puntatori = crea_lista_puntatori();    
    strcpy(nuovo_genere->nome_genere, nome_genere); 
   
    //cerco la posizione nella quale inserire il nuovo nodo
    while ((q != NULL) && (strcmp(q->nome_genere, nuovo_genere->nome_genere) < 0)){
        r = q;
        q = q->next;
    }
    //se esiste gia' un genere con lo stesso nome ritorna 2
    if((q != NULL) && (strcmp(q->nome_genere, nuovo_genere->nome_genere) == 0)) 
        return 2;
    
    if(q==*generi){
        nuovo_genere->next = *generi;
        *generi = nuovo_genere;
    }
    else{
        r->next = nuovo_genere;
        nuovo_genere->next = q;
    }
    return 0;
}

//cancella un puntatore dalla lista
int cancella_puntatore(lista_puntatori* puntatori, char titolo[]){
    //due puntatori di appoggio che faccio puntare inizialmente alla testa
    lista_puntatori r = *puntatori;
    lista_puntatori q = *puntatori; 
    //cerco l'elemento 
    while ((q != NULL) && (strcmp(titolo, q->discussione->titolo) != 0)){
        //r raggiunge q
        r = q;
        //q va avanti di uno
        q = q->next;
    }
    //se sono arrivato alla fine della lista l'elemento non c'e'
    if (q == NULL)  
        return 1;
    //se sono ancora in testa alla lista devo spostare la testa
    if (q==*puntatori)
        (*puntatori) = (*puntatori)->next;
    //se sono in una posizione intermedia il precedente deve puntare al successivo di q
    //nota: q punta all'elemento che voglio cancellare
    else
        r->next = q->next;  
    //dealloco l'elemento
    free(q);
    //tutto e' andato a buon fine
    return 0; 
}

//cancella un genere dalla lista
int cancella_genere(lista_generi* generi, char nome_genere[]){
 //due puntatori di appoggio che faccio puntare inizialmente alla testa
    lista_generi r = *generi;
    lista_generi q = *generi; 
    //cerco l'elemento 
    while ((q != NULL) && (strcmp(nome_genere, q->nome_genere) != 0)){
        //r raggiunge q
        r = q;
        //q va avanti di uno
        q = q->next;
    }
    //se sono arrivato alla fine della lista l'elemento non c'e'
    if (q == NULL)  
        return 1;
    //se sono ancora in testa alla lista devo spostare la testa
    if (q==*generi)
        (*generi) = (*generi)->next;
    //se sono in una posizione intermedia il precedente deve puntare al successivo di q
    //nota: q punta all'elemento che voglio cancellare
    else
        r->next = q->next;  
    //dealloco l'elemento
    free(q);
    //tutto e' andato a buon fine
    return 0; 
}

//ricerca un puntatore dalla lista in base al titolo 
lista_puntatori accesso_puntatore(lista_puntatori puntatori, char titolo[]){
	while(puntatori != NULL){
		if (strcmp(puntatori->discussione->titolo, titolo) == 0)
			return puntatori;
		puntatori = puntatori->next;
	}
	return NULL;
}

//ricerca un genere dalla lista
lista_generi accesso_genere(lista_generi generi, char nome_genere[]){
	while(generi != NULL){
		if (strcmp(generi->nome_genere, nome_genere) == 0)
			return generi;
		generi = generi->next;
	}
	return NULL;
}

//sposta un puntatore da un genere a un altr
void sposta_puntatore(lista_puntatori* puntatore, lista_generi genere){
	lista_puntatori r = genere->puntatori;
	lista_puntatori q = genere->puntatori;
	
	//cerco la posizione	
	while ((q != NULL) && (strcmp(q->discussione->titolo, (*puntatore)->discussione->titolo) < 0)){
        r = q;
        q = q->next;
    }
    //se q e' ancora in testa  
    if(q == genere->puntatori){
        (*puntatore)->next = genere->puntatori;
        genere->puntatori = *puntatore;
    }
    else{
        r->next = *puntatore;
        (*puntatore)->next = q;
    }
    strcpy((*puntatore)->discussione->genere, genere->nome_genere);
}	
//permette all'admin di rimuovere un genere dalla lista, spostando tutti i puntatori in altri generi
int rimuovi_genere(lista_generi* generi){
	lista_generi genere = NULL, genere2 = NULL;
	char nome_genere[31], nome_genere2[31];
	
	printf("\nEcco la lista dei generi:\n\n");
    stampa_generi(*generi);	
    printf("\nInserisci il genere da rimuovere: ");
    fgets(nome_genere, 31, stdin);
	nome_genere[strcspn(nome_genere, "\n")] = 0;
	
	genere = accesso_genere(*generi, nome_genere);
	if(genere == NULL)
		return 1;	//Genere non trovato
	
	//scorro i puntatori presenti nel genere	
	lista_puntatori r = genere->puntatori; 	//head
	lista_puntatori q = NULL;        		//next
	
	if(is_emptyp(genere->puntatori) == 0){
		 
		while(r != NULL){
			system("clear") ;
			q = r->next;
			do{
			system("clear") ;
			if(r->discussione->t == 0)
				printf("\nNel genere che si vuole rimuovere è presente una discussione sul film %s, seleziona un altro genere in cui spostarla:\n", r->discussione->titolo);
			else	
				printf("\nNel genere che si vuole rimuovere è presente una discussione sulla serie %s, seleziona un altro genere in cui spostarla:\n", r->discussione->titolo);
			
			
				stampa_generi(*generi);
				printf("\nInserisci il genere in cui spostare la discussione: ");
				fgets(nome_genere2, 31, stdin);
				nome_genere2[strcspn(nome_genere2, "\n")] = 0;
				if(strcmp(nome_genere, nome_genere2) == 0 ){
					printf(ANSI_COLOR_RED"\nImpossibile spostare la discussione nel genere che si vuole rimuovere!\n"ANSI_COLOR_RESET);
					printf("\nPremi invio per continuare\n");
		 			while( getchar() != '\n' );
		 			system("clear");
		 		}	
				else{	
					genere2 = accesso_genere(*generi, nome_genere2);
					if(genere2 == NULL){
						printf(ANSI_COLOR_RED"\nIl genere inserito non è valido!"ANSI_COLOR_RESET);
						printf("\nPremi invio per continuare\n");
			 			while( getchar() != '\n' );
			 			system("clear");
			 		}
				}	
			}while((strcmp(nome_genere, nome_genere2) == 0) || (genere2 == NULL));	
			
			sposta_puntatore(&r, genere2);
			printf(ANSI_COLOR_YELLOW"\nDiscussione spostata con successo nel genere %s\n"ANSI_COLOR_RESET, genere2->nome_genere);
			printf("\nPremi invio per continuare\n");
		 	while( getchar() != '\n' );
			
			r = q;
		}
		genere->puntatori = NULL;
		
		printf(ANSI_COLOR_YELLOW"\nTutte le discussioni all'interno del genere sono state spostate\n"ANSI_COLOR_RESET);
	}
	cancella_genere(generi, nome_genere);
	return 0;
}	
	

//filtra le discussioni per genere
int stampa_filtro(lista_generi generi, char nome_genere[]){
	lista_generi genere = NULL;
	int n = 0;

	genere = accesso_genere(generi, nome_genere);
	if(genere == NULL)
		return 1; //genere non trovato

	if(is_emptyp(genere->puntatori) == 1)
		return 2;
	
	system("clear");	
	printf(ANSI_COLOR_YELLOW"\nEcco l'elenco di tutte le discussioni aperte sui film e le serie tv sul genere %s:\n\n"ANSI_COLOR_RESET, nome_genere);
	lista_puntatori p = genere->puntatori;
	while (p != NULL){
		n++;
		modifica_n(&p->discussione, n);
        printf("\n%d) %s  ", p->discussione->n, p->discussione->titolo);
        if(p->discussione->t == film)
        	printf("(Film)");
        else
        	printf("(Serie TV)");
        printf("\n   Discussione iniziata da: %s\n", p->discussione->nick_utente);                                     
        p = p->next;
    }
	return 0;
}

int filtra(lista_generi generi){
	int r;
	char nome_genere[31];
			
	printf("\nEcco la lista dei generi:\n\n");
    stampa_generi(generi);		
    printf("\nInserisci il genere di cui vuoi visualizzare le discussioni: ");
    fgets(nome_genere, 31, stdin);
	nome_genere[strcspn(nome_genere, "\n")] = 0;

	r = stampa_filtro(generi, nome_genere);
	
	if(r == 1){
		printf(ANSI_COLOR_RED"\nIl genere inserito non è valido!"ANSI_COLOR_RESET);
		return 1;
	}	
	if(r == 2){
		printf(ANSI_COLOR_RED"\nNon sono ancora state aperte discussioni su film e serie tv sul genere %s\n"ANSI_COLOR_RESET, nome_genere);
		return 1;
	}
	if(r == 0)
		return 0;
	
}

void stampa_generi(lista_generi generi){
	
	if(is_emptyg(generi) == 1){
		printf("Non è ancora stato inserito nessun genere!\n");
		return;
	}
	while(generi != NULL){
		printf("    %s\n\n", generi->nome_genere);
		generi = generi->next;
	}
}	

void cancella_generi(lista_generi* generi){
	lista_generi r = *generi; //head
	lista_generi q = NULL;        //next
	
	while(r != NULL){
		q = r->next;
		r->puntatori = NULL;
		free(r);
		r = q;
	}
	generi = NULL;
}

int salva_generi(lista_generi generi){
	FILE* f = fopen("Generi", "w");
	if(f == NULL)
		return 1;
	
	while(generi != NULL){
		fprintf(f, "%s\n", generi->nome_genere);
		generi = generi->next;
	}
	fclose(f);	
	return 0;
}

int carica_generi(lista_generi* generi){
	FILE* f = fopen("Generi", "r");
	if(f == NULL)
		return 1;
	char nome_genere[31];
	int risultato;
	while(!feof(f)){
		fgets(nome_genere, 31, f);
		nome_genere[strcspn(nome_genere, "\n")] = 0;	
		risultato = inserisci_ordinato_genere(generi, nome_genere);
		if(risultato == 1){
			printf(ANSI_COLOR_RED"\nQualcosa è andato storto\n"ANSI_COLOR_RESET);
			exit(0);		
		}		
	}
	fclose(f);
	return 0;
}
