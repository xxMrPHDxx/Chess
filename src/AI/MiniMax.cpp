#include <AI/MiniMax.hpp>
#include <AI/BoardEvaluator.hpp>
#include <Board/Board.hpp>
#include <Move/Move.hpp>
#include <Move/MoveTransition.hpp>
#include <Player/Player.hpp>

namespace Chess {

    std::shared_ptr<Move> MiniMax::evaluate(std::shared_ptr<Board> board){
        std::shared_ptr<Move> bestMove(nullptr);
        int minValue = INT_MAX, maxValue = INT_MIN, value;
        for(auto& move : board->getCurrentPlayer()->getLegalMoves()){
            value = board->getCurrentPlayer()->isWhite() ?
                min(board, this->maxDepth) : max(board, this->maxDepth);
            if(board->getCurrentPlayer()->isWhite() && value >= maxValue){
                maxValue = value;
                bestMove = move;
            }else if(board->getCurrentPlayer()->isBlack() && value <= minValue){
                minValue = value;
                bestMove = move;
            }
        }
        return bestMove;
    }

    int MiniMax::min(std::shared_ptr<Board> board, int depth){
        if(depth <= 0 || isEndScenario(board))
            return BoardEvaluator::evaluate(board);
        int value = INT_MAX;
        for(auto& move : board->getCurrentPlayer()->getLegalMoves()){
            MoveTransition transition = board->getCurrentPlayer()->makeMove(board, move);
            if(!transition.isSuccess()) continue;
            int max_ = max(transition.getBoard(), depth-1);
            if(max_ <= value) value = max_;
        }
        return value;
    }

    int MiniMax::max(std::shared_ptr<Board> board, int depth){
        if(depth <= 0 || isEndScenario(board))
            return BoardEvaluator::evaluate(board);
        int value = INT_MIN;
        for(auto& move : board->getCurrentPlayer()->getLegalMoves()){
            MoveTransition transition = board->getCurrentPlayer()->makeMove(board, move);
            if(!transition.isSuccess()) continue;
            int min_ = min(transition.getBoard(), depth-1);
            if(min_ <= value) value = min_;
        }
        return value;
    }

    bool MiniMax::isEndScenario(std::shared_ptr<Board> board){
        return board->getCurrentPlayer()->isInCheckMate() ||
            board->getCurrentPlayer()->isInStaleMate() ||
            board->getOpponentPlayer()->isInCheckMate() ||
            board->getOpponentPlayer()->isInStaleMate();
    }

}