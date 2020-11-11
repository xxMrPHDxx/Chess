#ifndef PAWN_JUMP_HPP
#define PAWN_JUMP_HPP

#include "Move.hpp"

namespace Chess {

class PawnJump : public Move {
public:
    PawnJump() = delete;
    PawnJump(Board& b, Piece& p, int d) : Move(b, p, d) {}
    PawnJump(const PawnJump& pj) : Move(pj) {}
    std::shared_ptr<Board> execute() override;
    const std::string toString() override;
};

}

#endif // PAWN_JUMP_HPP