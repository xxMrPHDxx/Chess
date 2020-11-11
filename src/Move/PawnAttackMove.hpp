#ifndef PAWN_ATTACK_MOVE_HPP
#define PAWN_ATTACK_MOVE_HPP

#include "Move.hpp"

namespace Chess {

class PawnAttackMove : public Move {
public:
    PawnAttackMove() = delete;
    PawnAttackMove(Board& b, Piece& p, int d, Piece& ap) : Move(b, p, d, ap) {}
    PawnAttackMove(const PawnAttackMove& move) : Move(move) {}
    std::shared_ptr<Board> execute() override;
    const std::string toString() override;
};

}

#endif // PAWN_ATTACK_MOVE_HPP