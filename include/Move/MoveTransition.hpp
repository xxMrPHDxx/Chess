#ifndef MOVE_TRANSITION_HPP
#define MOVE_TRANSITION_HPP

#include "../pch.hpp"
#include "MoveStatus.hpp"

namespace Chess {

class Board;
class Move;

class MoveTransition {
private:
    std::shared_ptr<Board> board;
    std::shared_ptr<Move> move;
    MoveStatus status;
public:
    MoveTransition() = delete;
    MoveTransition(std::shared_ptr<Board>, std::shared_ptr<Move>, MoveStatus);
    std::shared_ptr<Board> getBoard() const { return this->board; }
    std::shared_ptr<Move> getMove() const { return this->move; }
    const MoveStatus& getStatus() const { return this->status; }
    const bool isSuccess() const { return this->status == MoveStatus::Success; }
    friend std::ostream& operator <<(std::ostream&, const MoveTransition&);
};

}

#endif // MOVE_TRANSITION_HPP