#include <AI/BoardEvaluator.hpp>
#include <Board/Board.hpp>
#include <Piece/Piece.hpp>
#include <Player/Player.hpp>

namespace Chess {

    long BoardEvaluator::evaluate(std::shared_ptr<Board> board){
        return (evaluate(board->getWhitePieces()) - evaluate(board->getBlackPieces())) + 
            (evaluate(board->getWhitePlayer()) - evaluate(board->getBlackPlayer()));
    }

    long BoardEvaluator::evaluate(Pieces pieces){
        long score = 0;
        for(auto& piece : pieces){
            switch(piece->getType()){
                case Piece::Type::Rook  : score += ROOK_SCORE; break;
                case Piece::Type::Knight: score += KNIGHT_SCORE; break;
                case Piece::Type::Bishop: score += BISHOP_SCORE; break;
                case Piece::Type::Queen : score += QUEEN_SCORE; break;
                case Piece::Type::King  : score += KING_SCORE; break;
                case Piece::Type::Pawn  : score += PAWN_SCORE; break;
                default: continue;
            }
        }
        return score;
    }

    long BoardEvaluator::evaluate(std::shared_ptr<Player> player){
        return player->isInCheckMate() ? 
            CHECK_MATE_SCORE : 
            (player->isInCheck() ? 
                CHECK_SCORE : 
                (player->isInStaleMate() ? STALE_MATE_SCORE : 0)
            );
    }

}