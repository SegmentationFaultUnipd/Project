# Project
PROGETTO DI LABORATORIO DI PROGRAMMAZIONE sviluppato dal gruppo SEGMENTATION FAULT
SCACCHIERA VIRTUALE
Il progetto supporta diverse modalità di gioco (PvsP, PvsAI, AIvsAI) che si possono impostare all'inizio.

TABELLA DEI CONTENUTI
Il progetto è diviso in 3 cartelle:
- build: contiene i file eseguibili scacchiera e replay
- src: contiene i file sorgene e le intestazioni, al suo interno troviamo le cartelle:
    - Pieces: contiene i file sorgente e le intestazioni per i diversi pezzi
    - Players: contiene i file sorgente e le intestazioni per i diversi tipi di giocatori
- tests: contiene due log d'esempio Computer vs Computer ("Stockfish_vs_Alpha_Zero.txt"), una partita Player vs Computer ("Humans_vs_Computer.txt")
- html: contiene la documentazione del progetto realizzata con Doxygen in formato html

USAGE scacchiera
Uso corretto: scacchiera [pp|pc|cc]
- argomento pc: inizia una partita giocatore vs computer
- argomento cc: inizia una partita computer vs computer, con massimo 500 mosse
- argomento pp: inizia una partita player vs player
