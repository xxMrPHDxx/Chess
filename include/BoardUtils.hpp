#ifndef BOARD_UTILS_HPP
#define BOARD_UTILS_HPP

#include "pch.hpp"
#include "Alliance.hpp"

namespace Chess {

class Tile;
class Board;
class Move;
typedef std::vector<std::shared_ptr<Move>> Moves;

class BoardUtils {
public:
    static const int NUM_TILES = 1 << 6;
    static const int NUM_ROWS = 1 << 3;
private:
    static const int COL_MASK = NUM_ROWS - 1;
    static const bool isRow(int, int);
    static const bool isColumn(int, int);
public:
    BoardUtils() = delete;
    static const bool isValidTile(int);
    static const bool isFirstRow(int pos){ return isRow(pos, 0); }
    static const bool isSecondRow(int pos){ return isRow(pos, 1); }
    static const bool isSeventhRow(int pos){ return isRow(pos, 6); }
    static const bool isEighthRow(int pos){ return isRow(pos, 7); }
    static const bool isFirstColumn(int pos){ return isColumn(pos, 0); }
    static const bool isSecondColumn(int pos){ return isColumn(pos, 1); }
    static const bool isSeventhColumn(int pos){ return isColumn(pos, 6); }
    static const bool isEighthColumn(int pos){ return isColumn(pos, 7); }
    static const Alliance getOpponent(Alliance);
    static const int getForward(Alliance);
    static const int getBackward(Alliance ally){ return getForward(getOpponent(ally)); }
    static const Moves getLegalMovesAtTile(Board&, Tile&);
    static std::shared_ptr<Move> getMoveFromTiles(Board&, Tile&, Tile&);
};

}

#endif // BOARD_UTILS_HPP