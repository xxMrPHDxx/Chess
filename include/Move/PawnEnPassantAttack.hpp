#ifndef PAWN_ENPASSANT_ATTACK_HPP
#define PAWN_ENPASSANT_ATTACK_HPP

#include "Move.hpp"

namespace Chess {

class PawnEnPassantAttack : public Move {
public:
    PawnEnPassantAttack() = delete;
    PawnEnPassantAttack(Board& b, Piece& p, int d, Piece& ap) : Move(b, p, d, ap) {}
    PawnEnPassantAttack(const PawnEnPassantAttack& move) : Move(move) {}
    std::shared_ptr<Board> execute() override;
    const std::string toString() override;
};

}

#endif // PAWN_ENPASSANT_ATTACK_HPP