#include <Move/PawnAttackMove.hpp>
#include <Piece/Piece.hpp>
#include <Board/Board.hpp>
#include <BoardUtils.hpp>

namespace Chess {

    std::shared_ptr<Board> PawnAttackMove::execute(){
        Board::Builder builder;
        for(auto& p : board->getAllActivePieces()){
            if(this->piece == p.get() || this->attackedPiece == p.get()) continue;
            builder.setPiece(p);
        }
        return builder
            .setPiece(piece->movePiece(destination))
            .setMoveMaker(BoardUtils::getOpponent(piece->getAlliance()))
            .build();
    }

    const std::string PawnAttackMove::toString(){
        std::stringstream ss;
        ss << "PawnAttackMove[";
        ss << getPosition() << "=>" << *attackedPiece << destination;
        ss << "]";
        return ss.str();
    }

}