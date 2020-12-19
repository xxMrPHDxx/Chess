#include <Game.hpp>
#include <Piece/Piece.hpp>
#include <Board/Tile.hpp>
#include <Board/Board.hpp>
#include <Move/Move.hpp>
#include <Player/Player.hpp>
#include <BoardUtils.hpp>

#include <Move/CastlingMove.hpp>
#include <Move/MoveTransition.hpp>

#include <Piece/Rook.hpp>
#include <Piece/King.hpp>
#include <Piece/Pawn.hpp>

namespace Chess {

    Game::Game(){
        // window = std::make_shared<sf::RenderWindow>(
        //     sf::VideoMode(504, 504), "Chess", sf::Style::Titlebar | sf::Style::Close
        // );
        // window->setFramerateLimit(30);
        chessBoard = Board::createStandardBoard();

        if(!t1.loadFromFile("img/board.png"))
            std::cout << "Failed to load 'img/board.png'!\n";
        if(!t2.loadFromFile("img/figures.png"))
            std::cout << "Failed to load 'img/figures.png'!\n";
        if(!t3.loadFromFile("img/ui.png"))
            std::cout << "Failed to load 'img/ui.png'!\n";

        sBoard.setTexture(t1);
        for(int i,n1,n2=n1=i=0; i<2; i++){
            for(int j=0; j<6; j++){
                sf::Sprite& s = sFigures[n1++];
                s.setTexture(t2);
                s.setTextureRect(sf::IntRect(j*56, i*56, 56, 56));
            }
            for(int j=0; j<3; j++){
                sf::Sprite& s = sUis[n2++];
                s.setTexture(t3);
                s.setTextureRect(sf::IntRect(j*56, i*56, 56, 56));
            }
        }
    }

    /*
    void Game::update(){
        handleEvents();
    }
    */

    void Game::render(sf::RenderWindow& window){
        // if(!shouldRedraw || aiThinking) return;
        window.draw(sBoard);
        // Draw the player in checkmate and stalemate hint
        if(chessBoard->getCurrentPlayer()->isInCheckMate() || chessBoard->getCurrentPlayer()->isInStaleMate()){
            sf::Sprite& s = sUis[chessBoard->getCurrentPlayer()->isInCheckMate() ? 4 : 5];
            const int pos = chessBoard->getCurrentPlayer()->getKing().getPosition();
            const int r = pos >> 3, c = pos & 7;
            s.setPosition(28+c*56, 28+r*56);
            window.draw(s);
        }
        // Draw the player in check hint
        else if(chessBoard->getCurrentPlayer()->isInCheck()){
            const int pos = chessBoard->getCurrentPlayer()->getKing().getPosition();
            const int r = pos >> 3, c = pos & 7;
            sf::Sprite& s = sUis[3];
            s.setPosition(28+c*56, 28+r*56);
            window.draw(s);
        }
        // Draw the pieces
        for(auto& piece : chessBoard->getAllActivePieces()){
            const int idx = (int)piece->getType() + (int)piece->getAlliance() * 6;
            sf::Sprite& s = sFigures[idx];
            const int pos = piece->getPosition();
            const int r = pos >> 3, c = pos & 7;
            s.setPosition(sf::Vector2f(28+c*56, 28+r*56));
            window.draw(s);
        }
        // Drawing the move hints
        for(auto& hint : moveHints){
            sf::Sprite& s = *hint.spr;
            s.setPosition(hint.pos.x, hint.pos.y);
            window.draw(s);
        }
        moveHints.clear();
        window.display();
        shouldRedraw = false;
    }

    void Game::executeComputerMove(std::shared_ptr<Move> move){
        chessBoard = move->execute();
    }

    void Game::handleEvents(sf::RenderWindow& window, sf::Event& event){
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed: window.close(); break;
                case sf::Event::MouseButtonPressed: onMouseEvent(event.key); break;
            }
        }
    }

    void Game::onMouseEvent(sf::Event::KeyEvent& key){
        /*
        sf::Vector2i mouse = sf::Mouse::getPosition(*window);
        const int row = (mouse.y - 28) / 56, col = (mouse.x - 28) / 56;
        const int idx = (row << 3) | col;
        if(!BoardUtils::isValidTile(idx)) return;
        sf::Vector2i pos(row, col);
        switch(key.code){
            case sf::Mouse::Button::Left: onTileLeftPressed(pos, idx); break;
            case sf::Mouse::Button::Right: onTileRightPressed(pos, idx); break;
        }
        */
    }

    void Game::onTileLeftPressed(sf::Vector2i& pos, const int idx){
        /*
        if(srcTile == nullptr){ // First click (Select source tile)
            srcTile = &chessBoard->getTile(idx);
            if(srcTile->isOccupied()){
                // Draw the move hints
                Moves moves = BoardUtils::getLegalMovesAtTile(*chessBoard, *srcTile);
                for(auto& move : moves){
                    bool isCastling = dynamic_cast<const CastlingMove*>(move.get()) != nullptr;
                    sf::Sprite& s = sUis[move->isAttackMove()|(isCastling?2:0)];
                    const int pos = move->getDestination();
                    const int r = pos >> 3, c = pos & 7;
                    moveHints.push_back({sf::Vector2i(28+c*56, 28+r*56), &s});
                }
                if(moves.size() > 0) { shouldRedraw = true; return; }
            }
            srcTile = destTile = nullptr;
        }else if(destTile == nullptr){ // Second click (Select destination tile)
            destTile = &chessBoard->getTile(idx);
            if(srcTile != destTile){
                // Execute the move
                auto move = BoardUtils::getMoveFromTiles(*chessBoard, *srcTile, *destTile);
                MoveTransition transition = chessBoard->getCurrentPlayer()->makeMove(chessBoard, move);
                if(transition.isSuccess())
                    chessBoard = transition.getBoard();
                else
                    std::cout << "Cannot execute the move [" << transition.getStatus() << "]\n";
            }
            srcTile = destTile = nullptr;
            shouldRedraw = true;
        }
        */
    }

    void Game::onTileRightPressed(sf::Vector2i& pos, const int idx){
        if(srcTile != nullptr) shouldRedraw = true;
        srcTile = destTile = nullptr;
    }

}