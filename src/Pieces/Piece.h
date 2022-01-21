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
            virtual void move (Coordinates new_position, Board &board) {
                position_ = new_position;
            }

            //Check if the piece can move to a file and rank.
            virtual bool canMoveAt(Coordinates pos, chess::Board& board) const = 0;

            //Check if the piece has at least an avaible move
            virtual bool canMove(chess::Board& board) const = 0;

            //List all the avaible moves
            virtual std::vector<Coordinates> legalMoves(chess::Board& board) const = 0;

            //List all the moves that capture an enemy piece
            virtual std::vector<Piece*> takeablePieces(chess::Board& board) const;

            // returns the ascii character for that piece
            char virtual ascii() const = 0;

            Color color() const { return color_;}
            short file() const { return position_.file; }
            short rank() const { return position_.rank; }
            Coordinates coordinates() const { return position_; }
            Piece(const Piece &obj) : Piece{obj.position_, obj.color_} {};
            
            Piece& operator=(const Piece& obj) {
                position_ = obj.position_;
                return *this;
            }
        protected:
            Piece(Coordinates pos, Color color) {
                position_ = pos;
                color_ = color;
            };


            Coordinates position_;
            Color color_;
    };

} //namespace chess

#endif //PIECE_H