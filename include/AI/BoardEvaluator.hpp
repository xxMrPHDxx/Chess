#ifndef BOARD_EVALUATOR_HPP
#define BOARD_EVALUATOR_HPP

#include "../pch.hpp"

namespace Chess {

class Board;
class Player;
class Piece;

typedef std::vector<std::shared_ptr<Piece>> Pieces;

class BoardEvaluator {
private:
    static const long ROOK_SCORE   =   500;
    static const long KNIGHT_SCORE =   300;
    static const long BISHOP_SCORE =   300;
    static const long QUEEN_SCORE  =   800;
    static const long KING_SCORE   = 10000;
    static const long PAWN_SCORE   =   100;

    static const long CHECK_SCORE       =    500;
    static const long CHECK_MATE_SCORE  = 100000;
    static const long STALE_MATE_SCORE  =  -5000;
public:
    static long evaluate(std::shared_ptr<Board>);
    static long evaluate(Pieces);
    static long evaluate(std::shared_ptr<Player>);
};

}

#endif // BOARD_EVALUATOR_HPP