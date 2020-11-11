#include "MoveTransition.hpp"

namespace Chess {

    MoveTransition::MoveTransition(std::shared_ptr<Board> board, std::shared_ptr<Move> move, MoveStatus status) :
        board(board),
        move(move),
        status(status) {}

    std::ostream& operator <<(std::ostream& out, const MoveTransition& mt){
        return out << "MoveTransition[status=" << mt.getStatus() << "]";
    }

}