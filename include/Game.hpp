#ifndef GAME_HPP
#define GAME_HPP

#include "pch.hpp"
#include <SFML/Graphics.hpp>

namespace Chess {

class Tile;
class Board;

struct MoveHint {
    sf::Vector2i pos;
    sf::Sprite* spr;
};
typedef std::vector<MoveHint> MoveHints;

class Game {
private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<Board> chessBoard;
    Tile *srcTile = nullptr, *destTile = nullptr;
    sf::Texture t1, t2, t3;
    sf::Sprite sBoard, sFigures[12], sUis[6];
    sf::Event event;
    bool shouldRedraw = true;
    MoveHints moveHints;
public:
    Game();
    const bool isRunning(){ return window->isOpen(); }
    void update();
    void render();
private:
    void handleEvents();
    void onMouseEvent(sf::Event::KeyEvent&);
    void onTileLeftPressed(sf::Vector2i&, const int);
    void onTileRightPressed(sf::Vector2i&, const int);
};

}

#endif // GAME_HPP