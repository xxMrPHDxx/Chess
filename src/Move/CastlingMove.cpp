#include <Move/CastlingMove.hpp>
#include <Piece/Piece.hpp>
#include <Board/Board.hpp>
#include <BoardUtils.hpp>

namespace Chess {

    std::shared_ptr<Board> CastlingMove::execute(){
        Board::Builder builder;
        for(auto& piece : board->getAllActivePieces()){
            if(this->piece == piece.get() || this->king == piece.get())
                continue;
            builder.setPiece(piece);
        }
        const int kingPosition = destination + (piece->getPosition() < king->getPosition() ? -1 : 1);
        return builder
            .setPiece(piece->movePiece(destination))
            .setPiece(king->movePiece(kingPosition))
            .setMoveMaker(BoardUtils::getOpponent(piece->getAlliance()))
            .build();
    }

    const std::string CastlingMove::toString(){
        std::stringstream ss;
        ss << "CastlingMove[" << *piece << "<==>" << *king << "]";
        return ss.str();
    }

}