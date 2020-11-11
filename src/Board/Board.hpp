#ifndef BOARD_HPP
#define BOARD_HPP

#include "../pch.hpp"
#include "../Alliance.hpp"

namespace Chess {

class Piece;
class Tile;
class Move;
class Board;
class Player;

typedef std::map<int, std::shared_ptr<Piece>> PieceConfig;
typedef std::vector<std::shared_ptr<Piece>> Pieces;
typedef std::vector<std::shared_ptr<Tile>> Tiles;
typedef std::vector<std::shared_ptr<Move>> Moves;

class Board {
public:
    class Builder {
    public:
        PieceConfig pieces;
        Alliance moveMaker;
        std::shared_ptr<Piece> enPassantPawn;
        Builder(Alliance moveMaker) : moveMaker(moveMaker), enPassantPawn(nullptr) {}
        Builder() : Builder(Alliance::White) {}
        Builder& setPiece(Piece* (&&));
        Builder& setPiece(std::shared_ptr<Piece>);
        Builder& setMoveMaker(Alliance moveMaker);
        Builder& setEnPassantPawn(std::shared_ptr<Piece>);
        std::shared_ptr<Board> build();
    };
private:
    Tiles tiles;
    Pieces whitePieces, blackPieces;
    std::shared_ptr<Player> whitePlayer, blackPlayer, currentPlayer;
    std::shared_ptr<Piece> enPassantPawn;
public:
    Board() = delete;
    Board(const Builder&);
    Tile& getTile(const int) const;
    Tile& operator [](const int idx){ return getTile(idx); }
    const Pieces& getWhitePieces() const { return this->whitePieces; }
    const Pieces& getBlackPieces() const { return this->blackPieces; }
    const Pieces getAllActivePieces() const;
    const std::shared_ptr<Player> getWhitePlayer() const { return this->whitePlayer; }
    const std::shared_ptr<Player> getBlackPlayer() const { return this->blackPlayer; }
    const std::shared_ptr<Player> getCurrentPlayer() const { return this->currentPlayer; }
    const std::shared_ptr<Player> getOpponentPlayer();
    const bool hasEnPassantPawn() const { return (bool)this->enPassantPawn; }
    Piece& getEnPassantPawn() const { return *this->enPassantPawn; }
    static std::shared_ptr<Board> createStandardBoard();
    friend std::ostream& operator <<(std::ostream&, const Board&);
};

}

#endif // BOARD_HPP