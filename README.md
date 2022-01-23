# Project
PROGETTO DI LABORATORIO DI PROGRAMMAZIONE sviluppato dal gruppo SEGMENTATION FAULT
SCACCHIERA VIRTUALE
Il progetto supporta diverse modalità di gioco (PvsP, PvsAI, AIvsAI) che si possono impostare all'inizio.

TABELLA DEI CONTENUTI
Il progetto è diviso in 3 cartelle:
- build: contiene i file eseguibili Scacchiera e Replay
- src: contiene i file sorgene e le intestazioni, al suo interno troviamo le cartelle:
    - Pieces: contiene i file sorgente e le intestazioni per i diversi pezzi
    - Players: contiene i file sorgente e le intestazioni per i diversi tipi di giocatori
- tests: contiene file di testo con un esempio di partita PCvsPC ("Stockfish vs Alpha Zero") e una partita generica ("general_game")
- html: contiene la documentazione del progetto realizzata con il programma "Doxygen" in formato html

INSTALLAZIONE E ESECUZIONE
Installa cmake windows installer (3.21) https://github.com/Kitware/CMake/releases/download/v3.21.4/cmake-3.21.4-windows-x86_64.msi
Durante l'installazione controlla che la voce per aggiornare la variabile d'ambiente PATH sia spuntata

Da VSCode installa le estensioni CMake e CMake Tools.

Per buildare:
posizionati in /build e esegui il comando
    cmake --build .


