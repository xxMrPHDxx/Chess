#include "King.hpp"
#include "../Board/Tile.hpp"
#include "../Board/Board.hpp"
#include "../BoardUtils.hpp"

#include "../Move/MajorMove.hpp"
#include "../Move/MajorAttackMove.hpp"

namespace Chess {

    constexpr int King::CANDIDATE_OFFSETS[];
    const Moves King::calculateLegalMoves(Board& board){
        Moves legalMoves;
        for(const int& offset : CANDIDATE_OFFSETS){
            const int destination = position + offset;
            if(!BoardUtils::isValidTile(destination) || hasExclusion(position, offset))
                continue;
            Tile& tile = board[destination];
            if(tile.isOccupied()){
                Piece& piece = tile.getPiece();
                if(piece.getAlliance() != ally){
                    legalMoves.push_back(std::make_shared<MajorAttackMove>(
                        board, *this, destination, piece
                    ));
                }
            }else{
                legalMoves.push_back(std::make_shared<MajorMove>(
                    board, *this, destination
                ));
            }
        }
        return legalMoves;
    }

    const bool King::isFirstColumnExcluded(int pos, int off){
        return BoardUtils::isFirstColumn(pos) && (off == -9 || off == -1 || off == 7);
    }

    const bool King::isEighthColumnExcluded(int pos, int off){
        return BoardUtils::isEighthColumn(pos) && (off == -7 || off == 1 || off == 9);
    }

}