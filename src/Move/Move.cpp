#include "Move.hpp"
#include "../Piece/Piece.hpp"

namespace Chess {

    Move::Move(Board& b, Piece& p, int d, Piece& ap) :
        board(&b),
        piece(&p),
        destination(d),
        attackedPiece(&ap) {}
    
    Move::Move(Board& b, Piece& p, int d) :
        board(&b),
        piece(&p),
        destination(d),
        attackedPiece(nullptr) {}
    
    const int& Move::getPosition() const {
        return this->piece->getPosition();
    }

}