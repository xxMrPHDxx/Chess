#include "MoveStatus.hpp"

namespace Chess {

    std::ostream& operator <<(std::ostream& out, const MoveStatus& status){
        switch(status){
            case MoveStatus::Success: return out << "Success";
            case MoveStatus::LeavesPlayerInCheck: return out << "LeavesPlayerInCheck";
            case MoveStatus::Illegal: return out << "Illegal";
            default:
                return out << "Unknown status";
        }
    }

}