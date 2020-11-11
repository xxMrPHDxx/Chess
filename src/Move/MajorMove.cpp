#include "MajorMove.hpp"
#include "../Board/Board.hpp"
#include "../Piece/Piece.hpp"
#include "../BoardUtils.hpp"

namespace Chess {

    std::shared_ptr<Board> MajorMove::execute(){
        Board::Builder builder;
        for(std::shared_ptr<Piece> p : board->getAllActivePieces()){
            if(this->piece == p.get()) continue;
            builder.setPiece(p);
        }
        return builder
            .setPiece(piece->movePiece(destination))
            .setMoveMaker(BoardUtils::getOpponent(piece->getAlliance()))
            .build();
    }

    const std::string MajorMove::toString(){
        std::stringstream ss;
        ss << "MajorMove[";
        ss << *piece << getPosition() << "->" << destination;
        ss << "]";
        return ss.str();
    }

}