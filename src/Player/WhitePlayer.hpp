#ifndef WHITE_PLAYER_HPP
#define WHITE_PLAYER_HPP

#include "Player.hpp"

namespace Chess {

class WhitePlayer : public Player {
public:
    WhitePlayer() = delete;
    WhitePlayer(Board& b, Moves& lm, Moves& olm) : Player(Alliance::White, b, lm, olm) {}
    WhitePlayer(const WhitePlayer& player) : Player(player) {}
};

}

#endif // WHITE_PLAYER_HPP