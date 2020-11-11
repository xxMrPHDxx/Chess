#include "Tile.hpp"
#include "../Piece/Piece.hpp"
#include "../BoardUtils.hpp"

namespace Chess {

    Tile::Tile(int position) :
        position(position),
        piece(nullptr) {}
    
    Tile::Tile(std::shared_ptr<Piece> piece) :
        piece(piece) {
        if(!piece || !BoardUtils::isValidTile(piece->getPosition())){
            throw std::invalid_argument("Invalid piece position!");
        }
        this->position = piece->getPosition();
    }

    std::ostream& operator <<(std::ostream& out, const Tile& tile){
        if(tile.isEmpty()) return out << '-';
        return out << tile.getPiece();
    }

}