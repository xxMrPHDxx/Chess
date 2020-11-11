#include <Piece/Piece.hpp>

namespace Chess {

    Piece::Piece(Type type, Alliance ally, int position, bool firstMove) :
        type(type),
        ally(ally),
        position(position),
        firstMove(firstMove) {}

    Piece::Piece(const Piece& p) :
        type(p.type),
        ally(p.ally),
        position(p.position),
        firstMove(p.firstMove) {}

    const bool Piece::hasExclusion(int pos, int off){
        return isFirstColumnExcluded(pos, off) ||
            isSecondColumnExcluded(pos, off) ||
            isSeventhColumnExcluded(pos, off) ||
            isEighthColumnExcluded(pos, off);
    }

    std::ostream& operator <<(std::ostream& out, const Piece& piece){
        char c;
        switch(piece.type){
            case Piece::Type::Rook  : c = 'R'; break;
            case Piece::Type::Knight: c = 'N'; break;
            case Piece::Type::Bishop: c = 'B'; break;
            case Piece::Type::Queen : c = 'Q'; break;
            case Piece::Type::King  : c = 'K'; break;
            case Piece::Type::Pawn  : c = 'P'; break;
            default:
                throw std::invalid_argument("Invalid piece type!");
        }
        switch(piece.ally){
            case Alliance::White: c += 32;
            case Alliance::Black: break;
            default:
                throw std::invalid_argument("Invalid piece alliance!");
        }
        return out << c;
    }
    
}