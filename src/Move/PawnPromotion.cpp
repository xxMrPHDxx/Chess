#include "PawnPromotion.hpp"
#include "../Board/Board.hpp"
#include "../BoardUtils.hpp"

#include "../Piece/Queen.hpp"

namespace Chess {

    PawnPromotion::PawnPromotion(std::shared_ptr<Move> move) :
        move(move),
        Move(move->getBoard(), move->getPiece(), move->getDestination()) {
            this->attackedPiece = move->isAttackMove() ? &move->getAttackedPiece() : nullptr;
        }

    PawnPromotion::PawnPromotion(Move* (&&move)) :
        PawnPromotion(std::shared_ptr<Move>(std::move(move))) {}
    
    std::shared_ptr<Board> PawnPromotion::execute(){
        Board::Builder builder;
        for(auto& p : board->getAllActivePieces()){
            if(this->piece == p.get() || this->attackedPiece == p.get()) continue;
            builder.setPiece(p);
        }
        return builder
            .setPiece(std::make_shared<Queen>(piece->getAlliance(), destination, false))
            .setMoveMaker(BoardUtils::getOpponent(piece->getAlliance()))
            .build();
    }

    const std::string PawnPromotion::toString(){
        std::stringstream ss;
        ss << "PawnPromotion[" << move->toString() << "]";
        return ss.str();
    }

}