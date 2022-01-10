#include "Piece.h"
#include "../Board.h"
/**
 * @brief Metodo che ritorna i pezzi che sono catturabili da this
 * @note Sarebbe più efficiente riscrivere il metodo per ogni pezzo, così da salvarsi un "doppio controllo" sulla board. Il codice risulterebbe molto simile a 
 * legalMoves(), abbiamo deciso di sacrificare un po' di efficienza per ridurre la duplicazione del codice 
 * @param board la scacchiera
 * @return std::vector<chess::Coordinates> le coordinate dei pezzi catturabili
 */
std::vector<chess::Coordinates> chess::Piece::takeablePieces(Board& board) const {
	std::vector<Coordinates> moves = legalMoves(board);
	std::vector<Coordinates> takeable_pieces;
	for(auto coord: moves) {
		if(!board.isEmpty(coord)) {
			takeable_pieces.push_back(coord);
		}
	}
	return takeable_pieces;
}
