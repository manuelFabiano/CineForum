#!/bin/bash

gcc -g -c utenti.c
gcc -g -c recensioni.c
gcc -g -c discussioni.c
gcc -g -c generi.c
gcc -g -c menu.c
gcc -g -c main.c
gcc main.o menu.o discussioni.o recensioni.o utenti.o generi.o -o CineForum

