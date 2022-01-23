/**
 * @file Piece.cpp
 * @author Filippo Mazzarotto
 * @date 2022-01-23
 */

#include "Piece.h"
#include "../Board.h"

std::vector<chess::Piece*> chess::Piece::takeablePieces(Board &board) const
{
	std::vector<Coordinates> moves = legalMoves(board);
	std::vector<Piece*> takeable_pieces;

	for (Coordinates move : moves)
	{
		if (!board.isEmpty(move) && board.at(move).color() != this->color())
		{
			takeable_pieces.push_back(&board.at(move));
		}
	}
	return takeable_pieces;
}
