/**
 * @file Piece.h
 * @author Filippo Mazzarotto
 * @date 2022-01-23
 */

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>

#include "../Color.h"
#include "../Coordinates.h"

namespace chess {
	class Board;
    /**
     * @brief Rappresenta un pezzo generico
     * 
     */
    class Piece {
        public:
            /**
             * @brief Aggiorna i membri privati.
             * 
             * @param new_position Le nuove coordinate.
             * @param board La scacchiera in cui si muove. Utile per aggiungere
             * possibilità di en passant.
             */
            virtual void move (Coordinates new_position, Board &board) {
                position_ = new_position;
            }
            
            /**
             * @brief Verifica se può muoversi nella posizione specificata.
             * @param coords Le coordinate per cui verificare.
             * @param board La scacchiera in cui si muove.
             * @return true, se la mossa è valida.
             * @return false, se è una mossa illegale.
             * 
             * @note Non viene controllato che dopo la mossa il proprio re non sia in scacco.
             * Questo controllo viene gestito dalla scacchiera.
             */
            virtual bool canMoveAt(Coordinates coords, chess::Board& board) const = 0;
            
            /**
             * @brief Verifica se ha almeno una mossa disponibile.
             * 
             * @note Questo metodo potrebbe essere sostituito da una verifica sulla
             * grandezza del vettore ritornato da legalMoves ma sarebbe meno efficiente.
             * 
             * @param board La scacchiera in cui si muove.
             * @return true, se ha almeno una mossa disponibile.
             * @return false, altrimenti.
             */
            virtual bool canMove(chess::Board& board) const = 0;

            /**
             * @brief Ritorna tutte le coordinate in cui il pezzo può muovere.
             * 
             * @note Non viene controllato che dopo la mossa il proprio re non sia in scacco.
             * Questo controllo viene gestito dalla scacchiera.
             * 
             * @param board La scacchiera in cui si muove.
             * @return std::vector<Coordinates> contenente le coordinate di arrivo
             * delle mosse disponibili.
             */
            virtual std::vector<Coordinates> legalMoves(chess::Board& board) const = 0;
            
            /**
             * @brief Ritorna i puntatori catturabili da this sulla scacchiera board.
             * 
             * @note Le mosse ritornate potrebbero causare scacco.
             * 
             * @note I puntatori puntano a un'area posseduta da uno unique_ptr. L'uso di questo
             * metodo deve essere usato raramente e in scope limitati.
             * 
             * @param board La scacchiera in cui si muove.
             * @return std::vector<Piece*> contenente tutti i puntatori ai pezzi catturabili.
             */
            virtual std::vector<Piece*> takeablePieces(chess::Board& board) const;

            /**
             * @brief Ritorna il carattere maiuscolo ascii associato a questo pezzo.
             * @note Associazioni:
             * Re = R
             * Regina = D
             * Alfiere = A
             * Cavallo = C
             * Torre = T
             * Pedone = P
             * @return Il carattere che individua lo specifico pezzo.
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

            Piece(const Piece &obj) : Piece{obj.position_, obj.color_} {
            };

            Coordinates position_;
            Color color_;
    };

} //namespace chess

#endif //PIECE_H