#ifndef PAWN_MOVE_HPP
#define PAWN_MOVE_HPP

#include "Move.hpp"

namespace Chess {

class PawnMove : public Move {
public:
    PawnMove() = delete;
    PawnMove(Board& b, Piece& p, int d) : Move(b, p, d) {}
    std::shared_ptr<Board> execute() override;
    const std::string toString() override;
};

}

#endif // PAWN_MOVE_HPP