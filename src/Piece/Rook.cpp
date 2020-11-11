#include <Piece/Rook.hpp>
#include <Board/Tile.hpp>
#include <Board/Board.hpp>
#include <BoardUtils.hpp>

#include <Move/MajorMove.hpp>
#include <Move/MajorAttackMove.hpp>
#include <Move/CastlingMove.hpp>

namespace Chess {

    constexpr int Rook::CANDIDATE_OFFSETS[];
    const Moves Rook::calculateLegalMoves(Board& board){
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
                    }else if(firstMove && piece.isKing() && piece.isFirstMove()){
                        legalMoves.push_back(std::make_shared<CastlingMove>(
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

    const bool Rook::isFirstColumnExcluded(int pos, int off){
        return BoardUtils::isFirstColumn(pos) && off == -1;
    }

    const bool Rook::isEighthColumnExcluded(int pos, int off){
        return BoardUtils::isEighthColumn(pos) && off == 1;
    }

}