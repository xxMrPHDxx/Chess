#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

namespace Chess {

class Rook : public Piece {
private:
    static constexpr int CANDIDATE_OFFSETS[] = { -8, -1, 1, 8 };
public:
    Rook() = delete;
    Rook(Alliance a, int p, bool fm) : Piece(Type::Rook, a, p, fm) {}
    Rook(Alliance a, int p) : Rook(a, p, true) {}
    Rook(const Rook& rook) : Piece(rook) {}
    const Moves calculateLegalMoves(Board&) override;
    const bool isFirstColumnExcluded(int, int) override;
    const bool isEighthColumnExcluded(int, int) override;
    std::shared_ptr<Piece> movePiece(int destination) override {
        return std::make_shared<Rook>(ally, destination, false);
    }
};

}

#endif // ROOK_HPP