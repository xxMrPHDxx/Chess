#ifndef MAJOR_MOVE_HPP
#define MAJOR_MOVE_HPP

#include "Move.hpp"

namespace Chess {

class MajorMove : public Move {
public:
    MajorMove() = delete;
    MajorMove(Board& b, Piece& p, int d) : Move(b, p, d) {}
    std::shared_ptr<Board> execute() override;
    const std::string toString() override;
};

}

#endif // MAJOR_MOVE_HPP