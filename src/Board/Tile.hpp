#ifndef TILE_HPP
#define TILE_HPP

#include "../pch.hpp"

namespace Chess {

class Piece;

class Tile {
private:
    int position;
    std::shared_ptr<Piece> piece;
public:
    Tile() = delete;
    Tile(int);
    Tile(std::shared_ptr<Piece>);
    const int& getPosition() const { return this->position; }
    const bool isEmpty() const { return !this->piece; }
    const bool isOccupied() const { return !isEmpty(); }
    Piece& getPiece() const { return *this->piece; }
    friend std::ostream& operator <<(std::ostream&, const Tile&);
};

}

#endif // TILE_HPP