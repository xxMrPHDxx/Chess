#ifndef MAJOR_ATTACK_MOVE_HPP
#define MAJOR_ATTACK_MOVE_HPP

#include "Move.hpp"

namespace Chess {

class MajorAttackMove : public Move {
public:
    MajorAttackMove() = delete;
    MajorAttackMove(Board& b, Piece& p, int d, Piece& ap) : Move(b, p, d, ap) {}
    std::shared_ptr<Board> execute() override;
    const std::string toString() override;
};

}

#endif // MAJOR_ATTACK_MOVE_HPP