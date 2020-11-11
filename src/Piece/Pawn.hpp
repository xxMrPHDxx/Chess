#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

namespace Chess {

class Pawn : public Piece {
private:
    static constexpr int CANDIDATE_OFFSETS[] = { 7, 8, 9, 16 };
public:
    Pawn() = delete;
    Pawn(Alliance a, int p, bool fm) : Piece(Type::Pawn, a, p, fm) {}
    Pawn(Alliance a, int p) : Pawn(a, p, true) {}
    Pawn(const Pawn& pawn) : Piece(pawn) {}
    const Moves calculateLegalMoves(Board& board) override;
    const bool isFirstColumnExcluded(int pos, int off) override;
    const bool isEighthColumnExcluded(int pos, int off) override;
    std::shared_ptr<Piece> movePiece(int destination) override {
        return std::make_shared<Pawn>(ally, destination, false);
    }
};

}

#endif // PAWN_HPP