#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include <pch.hpp>
#include <Alliance.hpp>

namespace Chess {

class Board;
class Move;

class MiniMax {
private:
    int maxDepth;
public:
    MiniMax(int maxDepth) : maxDepth(maxDepth) {}
    MiniMax() : MiniMax(3) {}
    ~MiniMax() = default;
    std::shared_ptr<Move> evaluate(std::shared_ptr<Board>);
private:
    int min(std::shared_ptr<Board>, int);
    int max(std::shared_ptr<Board>, int);
    static bool isEndScenario(std::shared_ptr<Board>);
};

}

#endif // MINIMAX_HPP