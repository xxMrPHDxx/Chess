#include <Move/PawnJump.hpp>
#include <Piece/Piece.hpp>
#include <Board/Board.hpp>
#include <BoardUtils.hpp>

namespace Chess {

    std::shared_ptr<Board> PawnJump::execute(){
        Board::Builder builder;
        for(auto& p : board->getAllActivePieces()){
            if(this->piece == p.get()) continue;
            builder.setPiece(p);
        }
        std::shared_ptr<Piece> pawn = piece->movePiece(destination);
        return builder
            .setPiece(pawn)
            .setMoveMaker(BoardUtils::getOpponent(piece->getAlliance()))
            .setEnPassantPawn(pawn)
            .build();
    }

    const std::string PawnJump::toString(){
        std::stringstream ss;
        ss << "PawnJump[";
        ss << getPosition() << "-->" << destination;
        ss << "]";
        return ss.str();
    }

}