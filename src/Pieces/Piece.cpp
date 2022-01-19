#include "Piece.h"
#include "../Board.h"
/**
 * @brief Metodo che ritorna i pezzi che sono catturabili da this
 * @note Sarebbe più efficiente riscrivere il metodo per ogni pezzo, così da salvarsi un "doppio controllo" sulla board. Il codice risulterebbe molto simile a
 * legalMoves(), abbiamo deciso di sacrificare un po' di efficienza per ridurre la duplicazione del codice
 * @param board la scacchiera
 * @return std::vector<chess::Coordinates> le coordinate dei pezzi catturabili
 */
std::vector<chess::Piece*> chess::Piece::takeablePieces(Board &board) const
{
	std::cout << "Taking pieces: ";

	std::vector<Coordinates> moves = legalMoves(board);
	std::vector<Piece*> takeable_pieces;

	for (Coordinates move : moves)
	{
		std::cout << move << " ";
		if (!board.isEmpty(move) && board.at(move).color() != this->color())
		{
			takeable_pieces.push_back(&board.at(move));
		}
	}
	return takeable_pieces;
}
