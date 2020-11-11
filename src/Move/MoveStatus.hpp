#ifndef MOVE_STATUS_HPP
#define MOVE_STATUS_HPP

#include "../pch.hpp"

namespace Chess {

enum class MoveStatus {
    Success, LeavesPlayerInCheck, Illegal
};

std::ostream& operator <<(std::ostream&, const MoveStatus&);

}

#endif // MOVE_STATUS_HPP