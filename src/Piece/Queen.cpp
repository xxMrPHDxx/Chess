#include <Piece/Queen.hpp>
#include <Board/Tile.hpp>
#include <Board/Board.hpp>
#include <BoardUtils.hpp>

#include <Move/MajorMove.hpp>
#include <Move/MajorAttackMove.hpp>

namespace Chess {

    constexpr int Queen::CANDIDATE_OFFSETS[];
    const Moves Queen::calculateLegalMoves(Board& board){
        Moves legalMoves;
        for(const int& offset : CANDIDATE_OFFSETS){
            int destination = position;
            while(BoardUtils::isValidTile(destination + offset)){
                if(hasExclusion(destination, offset)) break;
                destination += offset;
                Tile& tile = board[destination];
                if(tile.isOccupied()){
                    Piece& piece = tile.getPiece();
                    if(piece.getAlliance() != ally){
                        legalMoves.push_back(std::make_shared<MajorAttackMove>(
                            board, *this, destination, piece
                        ));
                    }
                    break;
                }else{
                    legalMoves.push_back(std::make_shared<MajorMove>(
                        board, *this, destination
                    ));
                }
            }
        }
        return legalMoves;
    }

    const bool Queen::isFirstColumnExcluded(int pos, int off){
        return BoardUtils::isFirstColumn(pos) && (off == -9 || off == -1 || off == 7);
    }

    const bool Queen::isEighthColumnExcluded(int pos, int off){
        return BoardUtils::isEighthColumn(pos) && (off == -7 || off == 1 || off == 9);
    }

}