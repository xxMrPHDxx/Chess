#ifndef PIECE_HPP
#define PIECE_HPP

#include "../pch.hpp"
#include "../Alliance.hpp"

namespace Chess {

class Move;
class Board;

typedef std::vector<std::shared_ptr<Move>> Moves;

class Piece {
public:
    enum class Type {
        Rook = 0, Knight = 1, Bishop = 2, Queen = 3, King = 4, Pawn = 5
    };
protected:
    Type type;
    Alliance ally;
    int position;
    bool firstMove;
    const bool hasExclusion(int, int);
public:
    Piece() = delete;
    Piece(Type, Alliance, int, bool);
    Piece(const Piece&);
    const Type& getType() const { return this->type; }
    const Alliance& getAlliance() const { return this->ally; }
    const int& getPosition() const { return this->position; }
    const bool& isFirstMove() const { return this->firstMove; }
    const bool isWhite() const { return this->ally == Alliance::White; }
    const bool isBlack() const { return this->ally == Alliance::Black; }
    const bool isKing() const { return this->type == Type::King; }
    const bool isPawn() const { return this->type == Type::Pawn; }
    virtual const Moves calculateLegalMoves(Board&) = 0;
    virtual const bool isFirstColumnExcluded(int, int){ return false; }
    virtual const bool isSecondColumnExcluded(int, int){ return false; }
    virtual const bool isSeventhColumnExcluded(int, int){ return false; }
    virtual const bool isEighthColumnExcluded(int, int){ return false; }
    virtual std::shared_ptr<Piece> movePiece(int) = 0;
    friend std::ostream& operator <<(std::ostream&, const Piece&);
};

}

#endif // PIECE_HPP