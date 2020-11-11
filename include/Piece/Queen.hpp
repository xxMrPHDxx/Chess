#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"

namespace Chess {

class Queen : public Piece {
private:
    static constexpr int CANDIDATE_OFFSETS[] = { -9, -8, -7, -1, 1, 7, 8, 9 };
public:
    Queen() = delete;
    Queen(Alliance a, int p, bool fm) : Piece(Type::Queen, a, p, fm) {}
    Queen(Alliance a, int p) : Queen(a, p, true) {}
    Queen(const Queen& queen) : Piece(queen) {}
    const Moves calculateLegalMoves(Board&) override;
    const bool isFirstColumnExcluded(int, int) override;
    const bool isEighthColumnExcluded(int, int) override;
    std::shared_ptr<Piece> movePiece(int destination) override {
        return std::make_shared<Queen>(ally, destination, false);
    }
};

}

#endif // QUEEN_HPP