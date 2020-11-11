#include "PawnMove.hpp"
#include "../Piece/Piece.hpp"
#include "../Board/Board.hpp"
#include "../BoardUtils.hpp"

namespace Chess {

    std::shared_ptr<Board> PawnMove::execute(){
        Board::Builder builder;
        for(auto& p : board->getAllActivePieces()){
            if(this->piece == p.get()) continue;
            builder.setPiece(p);
        }
        return builder
            .setPiece(piece->movePiece(destination))
            .setMoveMaker(BoardUtils::getOpponent(piece->getAlliance()))
            .build();
    }

    const std::string PawnMove::toString(){
        std::stringstream ss;
        ss << "PawnMove[";
        ss << getPosition() << "->" << destination;
        ss << "]";
        return ss.str();
    }

}