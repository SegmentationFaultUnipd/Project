/**
 * @file Board.h
 * @author Filippo Mazzarotto
 * @date 2022-01-23
 */
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
             * @brief Ritorna la lista delle coordinate dei pezzi del colore specificato.
             * 
             * @param color Colore dei pezzi da ottenere.
             * @return Reference alla std::list<Coordinates>
             */
            std::list<Coordinates>& getPiecesCoords(Color color);

            /**
             * @brief Prova ad eseguire la mossa specificata.
             * 
             * @note Assume che in from ci sia un pezzo.
             * 
             * @param from Coordinate di inizio.
             * @param to Coordinate di fine.
             * 
             * @return true, se la mossa è stata eseguita,
             * @return false, se la mossa è illegale,
             */
            bool move(Coordinates from, Coordinates to);

            /**
             * @brief Verifica se dopo la mossa specificata il re del giocatore che ha mosso
             * è in scacco.
             * @note Non effettua modifica alla board.
             * 
             * @param from Coordinate di inizio.
             * @param to Coordinate di fine.
             */
            bool isKingInCheckAfterMove(Coordinates from, Coordinates to);

            /**
             * @brief Verifica se le coordinate specificate sono minacciate da pezzi avversari.
             * 
             * @note Le coordinate possono puntare a una casa vuota.
             * 
             * @param piece_coords Coordinate della casa da controllare.
             * @param piece_color Colore del pezzo presente nella casa. I pezzi avversari
             * sono del colore opposto.
             */
            bool isThreatened(Coordinates piece_coords, Color piece_color);

            bool isKingInCheck(Color king_color);

            bool isEmptyOrOppositeColor(Coordinates landing_square, Color piece_color) const;
            bool isOppositeColor(Coordinates landing_square, Color piece_color) const;

            /**
             * @brief Aggiunge la mossa specificata alla lista delle possibili mosse en passant.
             * 
             * @param from La casa del pezzo che può effettuare la mossa.
             * @param to La casa in cui si posiziona il pezzo dopo aver preso en passant.
             */
            void addAvailableEnPassant(Coordinates from, Coordinates to);
            
            /**
             * @brief Rimuove il pedone dalle coordinate specificate e crea al suo posto un
             * nuovo pezzo del tipo specificato.
             * 
             * @param pawn_coords coordinate del pedone da promuovere
             * @param piece_ascii il carattere ascii maiuscolo del tipo del pezzo in cui promuovere.
             */
			void promote(Coordinates pawn_coords, char piece_ascii);

            bool isCastlingMove(Coordinates from, Coordinates to);
            void doCastlingMove(Coordinates from, Coordinates to);

            bool isEnPassantMove(Coordinates from, Coordinates to);
            void doEnPassantMove(Coordinates from, Coordinates to);

        private:
            /**
             * @brief Esegui la mossa specificata. Comprende i comportamenti delle mosse
             * di arrocco e di en passant.
             */
            void handleMoveType_(Coordinates from, Coordinates to);

            /**
             * @brief Aggiunge alla scacchiera un nuovo pezzo con le caratteristiche specificate.
             * 
             * @param piece_ascii Carattere ascii maiuscolo del tipo del pezzo.
             * @param coords Coordinate del pezzo.
             * @param color Colore del pezzo.
             */
            void addPiece_(char piece_ascii, Coordinates coords, Color color);
            void addPieceToMatrix_(std::unique_ptr<Piece>& attacking_piece_color, Coordinates coords);
            void addPieceCoords_(Coordinates coords);

            /**
             * @brief Rimuove tutti gli en passants disponibili al colore specificato.
             */
            void clearEnPassants_(Color piece_color);

            /**
             * @brief Rimuobe il pezzo delle coordinate specificate.
             */
            void removePiece_(Coordinates coords);

            /**
             * @brief Factory: crea uno unique pointer al pezzo con le caratteristiche specificate.
             * 
             * @param c Carattere ascii maiuscolo del tipo del pezzo
             * @param coords Coordinate del pezzo
             * @param color Colore del pezzo
             * @return std::unique_ptr<Piece> 
             */
            std::unique_ptr<Piece> makePiece_(char c, Coordinates coords, Color color) const;

            /**
             * @brief Factory: crea uno unique pointer che punta a un clone del pezzo specificato.
             * 
             * @note Il clone si trova in una differente area di memoria.
             * 
             * @param to_clone Reference const pezzo da clonare
             * @return std::unique_ptr<Piece> 
             */
            std::unique_ptr<Piece> clonePiece_(const Piece& to_clone) const;

            /**
             * @brief Aggiorna la posizione del pezzo nei suoi membri privati, nella matrice e nelle liste dei pezzi.
             * 
             * @param from Coordinate del pezzo da aggiornare.
             * @param to Coordinate in cui aggiornare.
             * 
             * @note Non gestisce situazione di arrocco ed en passant.
             */
            void updatePosition_(Coordinates from, Coordinates to);

            /**
             * @brief Lista delle coordinate di tutti i pezzi bianchi.
             */
            std::list<Coordinates> white_coords_;

            /**
             * @brief Lista delle coordinate di tutti i pezzi bianchi.
             */
            std::list<Coordinates> black_coords_;

            /**
             * @brief Lista delle mosse en passant possibili, attraverso std::pair di coordinate.
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