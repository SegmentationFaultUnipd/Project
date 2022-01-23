//AUTORE: Filippo Mazzarotto
#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>

#include "../Color.h"
#include "../Coordinates.h"

namespace chess {
	class Board;

    class Piece {
        public:
            /**
             * @brief Aggiorna le coordinate di this
             * 
             * @param new_position le coordinate della nuova posizione
             * @param board la schacchiera
             */
            virtual void move (Coordinates new_position, Board &board) {
                position_ = new_position;
            }
            
            /**
             * @brief Verifica se this può muoversi nella posizione
             * pos usando la schacchiera board
             * @param pos le coordinate di arrivo da verificare
             * @param board la schacchiera
             * @return true se this può eseguire la mossa
             * @return false altrimenti
             */
            virtual bool canMoveAt(Coordinates pos, chess::Board& board) const = 0;
            
            /**
             * @brief Verifica se this ha almeno una mossa disponibile sulla 
             * scacchiera board
             * @note Questo metodo potrebbe essere sostituito da una verifica sulla
             * grandezza del vettore ritornato da legalMoves ma sarebbe meno efficiente
             * @param board la schacchiera
             * @return true se this ha almeno una mossa disponibile
             * @return false altrimenti
             */
            virtual bool canMove(chess::Board& board) const = 0;

            /**
             * @brief Ritorna tutte le mosse che this può fare sulla schacchiera
             * board
             * @note Le mosse ritornate potrebbero causare scacco
             * @param board la schacchiera
             * @return std::vector<Coordinates> contenente del coordinate di arrivo
             * delle mosse disponibili 
             */
            virtual std::vector<Coordinates> legalMoves(chess::Board& board) const = 0;

            /**
             * @brief Ritorna tutti i pezzi catturabili da this sulla schacchiera
             * board
             * @note Le mosse ritornate potrebbero causare scacco
             * @param board la schacchiera
             * @return std::vector<Piece*> contenente tutti i puntatori ai pezzi catturabili 
             */
            virtual std::vector<Piece*> takeablePieces(chess::Board& board) const;

            /**
             * @brief Ritorna il carattere ascii associato a this 
             * @note Associazioni:
             * Re = r
             * Regina = d
             * Alfiere = a
             * Cavallo = c
             * Torre = t
             * Pedone = p
             * @return char carattere che individua uno specifico pezzo
             */
            char virtual ascii() const = 0;

            Color color() const { return color_;}
            short file() const { return position_.file; }
            short rank() const { return position_.rank; }
            Coordinates coordinates() const { return position_; }
            
            Piece& operator=(const Piece& obj) {
                position_ = obj.position_;
                return *this;
            }
        protected:
            Piece(Coordinates pos, Color color) {
                position_ = pos;
                color_ = color;
            };
            Piece(const Piece &obj) : Piece{obj.position_, obj.color_} {};


            Coordinates position_;
            Color color_;
    };

} //namespace chess

#endif //PIECE_H