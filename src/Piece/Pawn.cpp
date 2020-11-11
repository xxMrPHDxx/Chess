#include "Pawn.hpp"
#include "../Board/Tile.hpp"
#include "../Board/Board.hpp"
#include "../BoardUtils.hpp"

#include "../Move/PawnJump.hpp"
#include "../Move/PawnMove.hpp"
#include "../Move/PawnAttackMove.hpp"
#include "../Move/PawnPromotion.hpp"
#include "../Move/PawnEnPassantAttack.hpp"

namespace Chess {

    constexpr int Pawn::CANDIDATE_OFFSETS[];
    const Moves Pawn::calculateLegalMoves(Board& board){
        Moves legalMoves;
        for(const int offset : CANDIDATE_OFFSETS){
            const int forward = offset * BoardUtils::getForward(ally);
            const int destination = position + forward;
            if(!BoardUtils::isValidTile(destination) || hasExclusion(position, forward))
                continue;
            Tile& tile = board[destination];
            switch(offset){
                case 16: { // PawnJump
                    Tile& behind = board[destination + 8 * BoardUtils::getBackward(ally)];
                    if(tile.isEmpty() && behind.isEmpty() && firstMove){
                        legalMoves.push_back(std::make_shared<PawnJump>(
                            board, *this, destination
                        ));
                    }
                } break;
                case 8: { // PawnMove
                    if(tile.isEmpty()){
                        std::shared_ptr<Move> move = std::make_shared<PawnMove>(
                            board, *this, destination
                        );
                        if(BoardUtils::isFirstRow(destination)){
                            legalMoves.push_back(std::make_shared<PawnPromotion>(move));
                        }else{
                            legalMoves.push_back(move);
                        }
                    }
                } break;
                case 7: case 9: { // PawnAttackMove
                    if(tile.isEmpty() && board.hasEnPassantPawn()){
                        Piece& pawn = board.getEnPassantPawn();
                        Tile& pawnTile = board[destination - 8 * BoardUtils::getBackward(pawn.getAlliance())];
                        if(pawnTile.isOccupied() && pawnTile.getPiece().isPawn()){
                            Piece& pawn = pawnTile.getPiece();
                            legalMoves.push_back(std::make_shared<PawnEnPassantAttack>(
                                board, *this, destination, pawn
                            ));
                        }
                    }else if(tile.isOccupied() && tile.getPiece().getAlliance() != ally){
                        std::shared_ptr<Move> move = std::make_shared<PawnAttackMove>(
                            board, *this, destination, tile.getPiece()
                        );
                        if(BoardUtils::isFirstRow(destination)){
                            legalMoves.push_back(std::make_shared<PawnPromotion>(move));
                        }else{
                            legalMoves.push_back(move);
                        }
                    }
                } break;
            }
        }
        return legalMoves;
    }

    const bool Pawn::isFirstColumnExcluded(int pos, int off){
        return BoardUtils::isFirstColumn(pos) && (off == -9 || off == 7);
    }

    const bool Pawn::isEighthColumnExcluded(int pos, int off){
        return BoardUtils::isEighthColumn(pos) && (off == -7 || off == 9);
    }

}