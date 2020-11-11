#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

namespace Chess {

class King : public Piece {
private:
    static constexpr int CANDIDATE_OFFSETS[] = { -9, -8, -7, -1, 1, 7, 8, 9 };
public:
    King() = delete;
    King(Alliance a, int p, bool fm) : Piece(Type::King, a, p, fm) {}
    King(Alliance a, int p) : King(a, p, true) {}
    King(const King& king) : Piece(king) {}
    const Moves calculateLegalMoves(Board&) override;
    const bool isFirstColumnExcluded(int, int) override;
    const bool isEighthColumnExcluded(int, int) override;
    std::shared_ptr<Piece> movePiece(int destination) override {
        return std::make_shared<King>(ally, destination, false);
    }
};

}

#endif // KING_HPP