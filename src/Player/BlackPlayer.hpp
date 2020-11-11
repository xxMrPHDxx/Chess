#ifndef BLACK_PLAYER_HPP
#define BLACK_PLAYER_HPP

#include "Player.hpp"

namespace Chess {

class BlackPlayer : public Player {
public:
    BlackPlayer() = delete;
    BlackPlayer(Board& b, Moves& lm, Moves& olm) : Player(Alliance::Black, b, lm, olm) {}
    BlackPlayer(const BlackPlayer& player) : Player(player) {}
};

}

#endif // BLACK_PLAYER_HPP