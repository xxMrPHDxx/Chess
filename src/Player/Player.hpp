#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../pch.hpp"
#include "../Alliance.hpp"

namespace Chess {

class Board;
class Piece;
class Move;
class MoveTransition;

typedef std::vector<std::shared_ptr<Piece>> Pieces;
typedef std::vector<std::shared_ptr<Move>> Moves;

class Player {
protected:
    Alliance ally;
    Pieces activePieces;
    Moves legalMoves;
    std::shared_ptr<Piece> king;
    bool inCheck;
public:
    Player() = delete;
    Player(Alliance, Board&, Moves&, Moves&);
    const Alliance& getAlliance() const { return this->ally; }
    const Pieces& getPieces() const { return this->activePieces; }
    const Moves& getLegalMoves() const { return this->legalMoves; }
    Piece& getKing() const { return *this->king; }
    const bool& isInCheck() const { return this->inCheck; }
    const bool isInCheckMate();
    const bool isInStaleMate();
    const bool isWhite() const { return this->ally == Alliance::White; }
    const bool isBlack() const { return this->ally == Alliance::Black; }
    MoveTransition makeMove(std::shared_ptr<Board>, std::shared_ptr<Move>);
    static const Moves calculateAttacksOnTile(Moves&, const int);
    static const bool hasEscapeMoves(Player&);
    friend std::ostream& operator <<(std::ostream&, const Player&);
};

}

#endif // PLAYER_HPP