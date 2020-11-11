#include <BoardUtils.hpp>
#include <Board/Tile.hpp>
#include <Board/Board.hpp>
#include <Move/Move.hpp>
#include <Player/Player.hpp>

namespace Chess {

    const bool BoardUtils::isRow(int pos, int row){
        return pos >> 3 == row;
    }

    const bool BoardUtils::isColumn(int pos, int col){
        return (pos & COL_MASK) == col;
    }

    const bool BoardUtils::isValidTile(int pos){
        return pos >= 0 && pos < NUM_TILES;
    }

    const Alliance BoardUtils::getOpponent(Alliance ally) {
        switch(ally){
            case Alliance::White: return Alliance::Black;
            case Alliance::Black: return Alliance::White;
            default:
                throw std::invalid_argument("Invalid alliance! Cannot find opponent alliance.");
        }
    }

    const int BoardUtils::getForward(Alliance ally){
        switch(ally){
            case Alliance::White: return -1;
            case Alliance::Black: return  1;
        }
        return 0;
    }

    const Moves BoardUtils::getLegalMovesAtTile(Board& board, Tile& tile){
        Moves moves;
        for(auto& move : board.getCurrentPlayer()->getLegalMoves()){
            if(move->getPosition() == tile.getPosition())
                moves.push_back(move);
        }
        return moves;
    }

    std::shared_ptr<Move> BoardUtils::getMoveFromTiles(Board& board, Tile& src, Tile& dest){
        for(auto& move : board.getCurrentPlayer()->getLegalMoves()){
            if(move->getPosition() == src.getPosition() && move->getDestination() == dest.getPosition())
                return move;
        }
        return std::shared_ptr<Move>(nullptr);
    }

}