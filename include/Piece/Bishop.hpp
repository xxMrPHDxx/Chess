#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"

namespace Chess {

class Bishop : public Piece {
private:
    static constexpr int CANDIDATE_OFFSETS[] = { -9, -7, 7, 9 };
public:
    Bishop() = delete;
    Bishop(Alliance a, int p, bool fm) : Piece(Type::Bishop, a, p, fm) {}
    Bishop(Alliance a, int p) : Bishop(a, p, true) {}
    Bishop(const Bishop& bishop) : Piece(bishop) {}
    const Moves calculateLegalMoves(Board&) override;
    const bool isFirstColumnExcluded(int, int) override;
    const bool isEighthColumnExcluded(int, int) override;
    std::shared_ptr<Piece> movePiece(int destination) override {
        return std::make_shared<Bishop>(ally, destination, false);
    }
};

}

#endif // BISHOP_HPP