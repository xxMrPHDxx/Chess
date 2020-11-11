#ifndef CASTLING_MOVE_HPP
#define CASTLING_MOVE_HPP

#include "Move.hpp"

namespace Chess {

class CastlingMove : public Move {
private:
    Piece* king;
public:
    CastlingMove() = delete;
    CastlingMove(Board& b,Piece& rook,int d,Piece& king) : Move(b,rook,d), king(&king) {}
    Piece& getKing() const { return *this->king; }
    std::shared_ptr<Board> execute() override;
    const std::string toString() override;
};

}

#endif // CASTLING_MOVE_HPP