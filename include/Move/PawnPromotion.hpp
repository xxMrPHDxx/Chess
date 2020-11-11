#ifndef PAWN_PROMOTION_HPP
#define PAWN_PROMOTION_HPP

#include "Move.hpp"

namespace Chess {

class PawnPromotion : public Move {
private:
    std::shared_ptr<Move> move;
public:
    PawnPromotion() = delete;
    PawnPromotion(Move* (&&));
    PawnPromotion(std::shared_ptr<Move>);
    std::shared_ptr<Board> execute() override;
    const std::string toString() override;
};

}

#endif // PAWN_PROMOTION_HPP