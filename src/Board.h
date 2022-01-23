//AUTORE: Filippo Mazzarotto
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <list>
#include <memory>
#include <assert.h>

#include "Pieces/Piece.h"
#include "Pieces/Knight.h"
#include "Pieces/King.h"
#include "Pieces/Rook.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/Bishop.h"

#include "Color.h"
#include "Coordinates.h"

namespace chess {
    /**
     * @brief Classe che rappresenta la scacchiera
     * 
     */
    class Board {
        public:
            Board();
            Board(const Board& to_copy);

            bool isEmpty(Coordinates coords) const;
            const Piece& at(Coordinates coords) const;
            Piece& at(Coordinates coords);
            Piece& getKing(Color king_color);

            /**
             * @brief Ritorna la lista delle coordinate dei pezzi del colore specificato
             * 
             * @param color
             * @return Reference alla std::list<Coordinates> dei pezzi di color
             */
            std::list<Coordinates>& getPiecesCoords(Color color);

            /**
             * @brief Prova ad eseguire la mossa from-to.
             * 
             * @note Assume che in from ci sia
             * 
             * @param from coordinate di inizio
             * @param to coordinate di spostamento
             * @return true se la mossa è stata eseguita
             * @return false se la mossa è illegale
             */
            bool move(Coordinates from, Coordinates to);

            /**
             * @brief Verifica che dopo la mossa from-to il re del giocatore che ha mosso
             * non sia in scacco. Sarebbe una mossa illegale
             * @note Non effettua modifica alla board.
             * 
             * @param from coordinate di inizio
             * @param to coordinate di spostamento
             */
            bool isKingInCheckAfterMove(Coordinates from, Coordinates to);

            /**
             * @brief Verifica se le coordinate specificate sono minacciate da pezzi avversari.
             * 
             * @param piece_coords coordinate della casa da controllare.
             * @param piece_color colore del pezzo (reale o no) della casa. I pezzi avversari
             * sono del colore opposto.
             */
            bool isThreatened(Coordinates piece_coords, Color piece_color);

            bool isKingInCheck(Color king_color);

            bool isEmptyOrOppositeColor(Coordinates landing_square, Color piece_color) const;
            bool isOppositeColor(Coordinates landing_square, Color piece_color) const;

            /**
             * @brief Aggiunge la mossa from-to alla lista delle possibili mosse en-passants
             * 
             * @param from la casa del pezzo che può effettuare la mossa.
             * @param to la casa in cui si posiziona il pezzo dopo aver effettuato la mossa.
             */
            void addAvailableEnPassant(Coordinates from, Coordinates to);
            
            /**
             * @brief Rimuovi il pedone delle coordinate specificati e crea al suo posto un
             * nuovo pezzo di tipo definito da piece.
             * 
             * @param pawn coordinate del pedone da promuovere
             * @param piece il carattere ascii maiuscolo del tipo del pezzo.
             */
			void promote(Coordinates pawn, char piece);

            bool isCastlingMove(Coordinates from, Coordinates to);
            void doCastlingMove(Coordinates from, Coordinates to);

            bool isEnPassantMove(Coordinates from, Coordinates to);
            void doEnPassantMove(Coordinates from, Coordinates to);

        private:
            /**
             * @brief Esegui la mossa specificata, comprende i comportamenti delle mosse
             * di arrocco e di en passant
             */
            void handleMoveType_(Coordinates from, Coordinates to);

            /**
             * @brief Crea un nuovo pezzo con le caratteristiche specificate
             * 
             * @param piece_ascii carattere ascii maiuscolo del tipo del pezzo
             * @param coords coordinate del pezzo
             * @param color colore del pezzo
             */
            void addPiece_(char piece_ascii, Coordinates coords, Color color);
            void addPieceToMatrix_(std::unique_ptr<Piece>& attacking_piece_color, Coordinates coords);
            void addPieceCoords_(Coordinates coords);

            /**
             * @brief rimuove tutti gli en passants possibili del colore specificato.
             */
            void clearEnPassants_(Color piece_color);

            /**
             * @brief rimuove il pezzo delle coordinate specificate
             */
            void removePiece_(Coordinates coords);

            /**
             * @brief Factory: crea uno unique pointer al pezzo con le caratteristiche specificate.
             * 
             * @param c carattere ascii maiuscolo del tipo del pezzo
             * @param coords coordinate del pezzo
             * @param color colore del pezzo
             * @return std::unique_ptr<Piece> 
             */
            std::unique_ptr<Piece> makePiece_(char c, Coordinates coords, Color color) const;

            /**
             * @brief Factory: crea uno unique pointer che punta a un clone del pezzo specificato.
             * 
             * @note Il clone si trova in una differente area di memoria.
             * 
             * @param p reference const pezzo da clonare
             * @return std::unique_ptr<Piece> 
             */
            std::unique_ptr<Piece> clonePiece_(const Piece& p) const;

            /**
             * @brief Aggiorna la posizione nei membri del pezzo, nella matrice e nelle liste dei pezzi,
             * da from a to.
             * 
             * @note Non gestisce situazione di arrocco ed en passant
             */
            void updatePosition_(Coordinates from, Coordinates to);

            /**
             * @brief lista delle coordinate di tutti i pezzi bianchi.
             */
            std::list<Coordinates> white_coords_;

            /**
             * @brief lista delle coordinate di tutti i pezzi bianchi.
             */
            std::list<Coordinates> black_coords_;

            /**
             * @brief lista delle mosse en passant possibili, attraverso std::pair di coordinate.
             */
            std::list<std::pair<Coordinates, Coordinates>> available_en_passants_;

            /**
             * @brief Matrice 8x8 di puntatori ai pezzi. Le case vuote sono indicate da nullptr.
             */
            std::unique_ptr<Piece> board_[8][8];
    };

    std::ostream& operator<<(std::ostream& os, const Board& board);

} //namespace chess

#endif //BOARD_H