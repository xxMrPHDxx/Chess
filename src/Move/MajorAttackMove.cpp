#include "MajorAttackMove.hpp"
#include "../Board/Board.hpp"
#include "../Piece/Piece.hpp"
#include "../BoardUtils.hpp"

namespace Chess {

    std::shared_ptr<Board> MajorAttackMove::execute(){
        Board::Builder builder;
        for(std::shared_ptr<Piece> p : board->getAllActivePieces()){
            if(this->piece == p.get() || this->attackedPiece == p.get()) continue;
            builder.setPiece(p);
        }
        return builder
            .setPiece(piece->movePiece(destination))
            .setMoveMaker(BoardUtils::getOpponent(piece->getAlliance()))
            .build();
    }

    const std::string MajorAttackMove::toString(){
        std::stringstream ss;
        ss << "MajorAttackMove[";
        ss << *piece << getPosition() << "->" << *attackedPiece << destination;
        ss << "]";
        return ss.str();
    }

}