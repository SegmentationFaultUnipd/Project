# PROGETTO SCACCHIERA VIRTUALE
Sviluppato dal gruppo SEGMENTATION FAULT

Il progetto supporta diverse modalità di gioco (PvsP, PvsAI, AIvsAI) che si possono impostare all'inizio.

### Tabella dei contenuti
Il progetto è diviso in 3 cartelle:
- build: contiene i file eseguibili scacchiera e replay
- src: contiene i file sorgene e le intestazioni, al suo interno troviamo le cartelle:
    - Pieces: contiene i file sorgente e le intestazioni per i diversi pezzi
    - Players: contiene i file sorgente e le intestazioni per i diversi tipi di giocatori
- tests: contiene due log d'esempio Computer vs Computer ("Stockfish_vs_Alpha_Zero.txt"), una partita Player vs Computer ("Humans_vs_Computer.txt")
- html: contiene la documentazione del progetto realizzata con Doxygen in formato html

### Usage scacchiera
Comando: scacchiera [pp|pc|cc]
- argomento pc: inizia una partita giocatore vs computer
- argomento cc: inizia una partita computer vs computer, con massimo 500 mosse
- argomento pp: inizia una partita player vs player

### Usage replay
Comando: replay [v|f]
- argomento v [nome_file_log]: stampa a video il replay del file di log indicato
- argomento f [nome_file_log] [nome_file_output_replay]: scriver sul file il replay del file di log indicato
