#include "PawnEnPassantAttack.hpp"
#include "../Piece/Piece.hpp"
#include "../Board/Board.hpp"
#include "../BoardUtils.hpp"

namespace Chess {

    std::shared_ptr<Board> PawnEnPassantAttack::execute(){
        Board::Builder builder;
        for(auto& piece : board->getAllActivePieces()){
            if(this->piece == piece.get() || this->attackedPiece == piece.get())
                continue;
            builder.setPiece(piece);
        }
        return builder
            .setPiece(this->piece->movePiece(destination))
            .setMoveMaker(BoardUtils::getOpponent(this->piece->getAlliance()))
            .build();
    }

    const std::string PawnEnPassantAttack::toString(){
        std::stringstream ss;
        ss << "PawnEnPassantAttack[" << getPosition() << "-->" << destination << "]";
        return ss.str();
    }

}