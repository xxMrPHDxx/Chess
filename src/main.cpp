#include <pch.hpp>
#include <chrono>
#include <Board/Board.hpp>
#include <Player/Player.hpp>
#include <Move/Move.hpp>
#include <Move/MoveTransition.hpp>

#include <Game.hpp>
#include <AI/MiniMax.hpp>

int main(){
    using namespace Chess;

    sf::RenderWindow window(sf::VideoMode(504, 504), "Chess", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(30);

    sf::Event event;

    Game game;
    MiniMax ai;
    
    std::thread ai_thread([&window, &ai, &game](){
        // TODO: Only move when current player isn't human and game hasn't ended
        while(window.isOpen()){
            std::printf("AI is thinking...\n");
            game.aiThinking = true;
            std::shared_ptr<Move> move;
            move = ai.evaluate(game.getChessBoard());
            std::cout << "AI got move: " << move->toString() << "\n";
            game.executeComputerMove(move);
            game.aiThinking = false;
        }
    });

    long frames = 0, ticks = 0, sleep_time;
    const double FPS = 30.0, microPerTick = 1000000.0 / FPS;
    bool should_render;
    sf::Clock clock, fps_timer;
    double elapsed = 0;
    while(window.isOpen()){
        should_render = 0;
        if(clock.getElapsedTime().asMicroseconds() >= microPerTick){
            game.handleEvents(window, event);
            should_render = 1;
            clock.restart();
            ticks++;
        }else{
            sleep_time = (microPerTick - clock.getElapsedTime().asMicroseconds())/1000;
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        }
        if(should_render){ game.render(window); frames++; }
        if(fps_timer.getElapsedTime().asMilliseconds() >= 1000){
            std::printf("FPS: %i, ticks: %i\n", frames, ticks);
            frames = ticks = 0;
            fps_timer.restart();
        }
    }
    // Stops the ai thread safely
    ai_thread.detach();
    return 0;
}