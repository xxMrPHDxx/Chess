#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

namespace Chess {

class Knight : public Piece {
private:
    static constexpr int CANDIDATE_OFFSETS[] = { -17, -15, -10, -6, 6, 10, 15, 17 };
public:
    Knight() = delete;
    Knight(Alliance a, int p, bool fm) : Piece(Type::Knight, a, p, fm) {}
    Knight(Alliance a, int p) : Knight(a, p, true) {}
    Knight(const Knight& k) : Piece(k) {}
    const Moves calculateLegalMoves(Board&) override;
    const bool isFirstColumnExcluded(int, int) override;
    const bool isSecondColumnExcluded(int, int) override;
    const bool isSeventhColumnExcluded(int, int) override;
    const bool isEighthColumnExcluded(int, int) override;
    std::shared_ptr<Piece> movePiece(int destination) override {
        return std::make_shared<Knight>(ally, destination, false);
    }
};

}

#endif // KNIGHT_HPP