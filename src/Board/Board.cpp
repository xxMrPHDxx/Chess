#include "Board.hpp"
#include "Tile.hpp"
#include "../Move/Move.hpp"
#include "../BoardUtils.hpp"

#include "../Player/WhitePlayer.hpp"
#include "../Player/BlackPlayer.hpp"

#include "../Piece/Rook.hpp"
#include "../Piece/Knight.hpp"
#include "../Piece/Bishop.hpp"
#include "../Piece/Queen.hpp"
#include "../Piece/King.hpp"
#include "../Piece/Pawn.hpp"

namespace Chess {

    /*******************************************************************************/
    /*                              BUILDER STUFF                                  */
    /*******************************************************************************/

    Board::Builder& Board::Builder::setPiece(Piece* (&&piece)){
        if(piece && BoardUtils::isValidTile(piece->getPosition())){
            const int pos = piece->getPosition();
            this->pieces.insert({ pos, std::shared_ptr<Piece>(std::move(piece)) });
        }else if(piece){
            delete piece;
        }
        return *this;
    }

    Board::Builder& Board::Builder::setPiece(std::shared_ptr<Piece> piece){
        if(piece && BoardUtils::isValidTile(piece->getPosition())){
            const int pos = piece->getPosition();
            this->pieces.insert({ pos, piece });
        }
        return *this;
    }

    Board::Builder& Board::Builder::setMoveMaker(Alliance moveMaker){
        this->moveMaker = moveMaker;
    }

    Board::Builder& Board::Builder::setEnPassantPawn(std::shared_ptr<Piece> pawn){
        if(pawn && BoardUtils::isValidTile(pawn->getPosition())){
            this->enPassantPawn = pawn;
        }
        return *this;
    }

    std::shared_ptr<Board> Board::Builder::build(){
        return std::make_shared<Board>(*this);
    }

    /*******************************************************************************/
    /*                               BOARD STUFF                                   */
    /*******************************************************************************/

    Board::Board(const Board::Builder& builder){
        this->enPassantPawn = builder.enPassantPawn;
        // Create all the tiles
        for(int i=0; i<BoardUtils::NUM_TILES; i++){
            auto match = builder.pieces.find(i);
            if(match != builder.pieces.end()){
                auto piece = match->second;;
                this->tiles.push_back(std::make_shared<Tile>(piece));
                Pieces& pieces = piece->isWhite() ? whitePieces : blackPieces;
                pieces.push_back(piece);
                continue;
            }
            this->tiles.push_back(std::make_shared<Tile>(i));
        }
        // Calculate all legal moves
        Moves whiteLegals, blackLegals;
        for(auto& piece : whitePieces)
            for(auto& move : piece->calculateLegalMoves(*this))
                whiteLegals.push_back(move);
        for(auto& piece : blackPieces)
            for(auto& move : piece->calculateLegalMoves(*this)) 
                blackLegals.push_back(move);
        // Create the players
        this->whitePlayer = std::make_shared<WhitePlayer>(*this, whiteLegals, blackLegals);
        this->blackPlayer = std::make_shared<BlackPlayer>(*this, blackLegals, whiteLegals);
        this->currentPlayer = builder.moveMaker == Alliance::White ? whitePlayer : blackPlayer;
    }

    Tile& Board::getTile(const int idx) const {
        if(!BoardUtils::isValidTile(idx))
            throw std::invalid_argument("Invalid tile position!");
        return *this->tiles[idx];
    }

    const Pieces Board::getAllActivePieces() const {
        Pieces activePieces;
        for(auto& piece : this->whitePieces) activePieces.push_back(piece);
        for(auto& piece : this->blackPieces) activePieces.push_back(piece);
        return activePieces;
    }

    const std::shared_ptr<Player> Board::getOpponentPlayer(){
        return currentPlayer.get() == whitePlayer.get() ? blackPlayer : whitePlayer;
    }

    std::shared_ptr<Board> Board::createStandardBoard(){
        Board::Builder builder;
        for(Alliance ally : { Alliance::White, Alliance::Black }){
            for(int i=0,j=ally==Alliance::White?48:8; i<8; i++){
                builder.setPiece(new Pawn(ally, i+j));
            }
        }
        return builder
            .setPiece(new Rook  (Alliance::Black, 0))
            .setPiece(new Knight(Alliance::Black, 1))
            .setPiece(new Bishop(Alliance::Black, 2))
            .setPiece(new Queen (Alliance::Black, 3))
            .setPiece(new King  (Alliance::Black, 4))
            .setPiece(new Bishop(Alliance::Black, 5))
            .setPiece(new Knight(Alliance::Black, 6))
            .setPiece(new Rook  (Alliance::Black, 7))
            .setPiece(new Rook  (Alliance::White, 63-0))
            .setPiece(new Knight(Alliance::White, 63-1))
            .setPiece(new Bishop(Alliance::White, 63-2))
            .setPiece(new King  (Alliance::White, 63-3))
            .setPiece(new Queen (Alliance::White, 63-4))
            .setPiece(new Bishop(Alliance::White, 63-5))
            .setPiece(new Knight(Alliance::White, 63-6))
            .setPiece(new Rook  (Alliance::White, 63-7))
            .build();
    }

    std::ostream& operator <<(std::ostream& out, const Board& board){
        for(int i=0,n=0; i<BoardUtils::NUM_ROWS; i++){
            for(int j=0; j<BoardUtils::NUM_ROWS; j++, n++){
                out << *board.tiles[n];
                if(j < BoardUtils::NUM_ROWS - 1) out << ' ';
            }
            if(i < BoardUtils::NUM_ROWS - 1) out << '\n';
        }
        return out;
    }

}