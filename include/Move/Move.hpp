#ifndef MOVE_HPP
#define MOVE_HPP

#include "../pch.hpp"

namespace Chess {

class Board;
class Piece;

class Move {
protected:
    Board* board;
    Piece* piece;
    int destination;
    Piece* attackedPiece;
public:
    Move() = delete;
    Move(Board&, Piece&, int, Piece&);
    Move(Board& b, Piece& p, int d);
    Board& getBoard() const { return *this->board; }
    Piece& getPiece() const { return *this->piece; }
    const int& getPosition() const;
    const int& getDestination() const { return this->destination; }
    const bool isAttackMove() const { return this->attackedPiece != nullptr; }
    Piece& getAttackedPiece() const { return *this->attackedPiece; }
    virtual std::shared_ptr<Board> execute() = 0;
    virtual const std::string toString() = 0;
    friend std::ostream& operator <<(std::ostream& out, Move& move){
        return out << (&move)->toString();
    }
};

}

#endif // MOVE_HPP