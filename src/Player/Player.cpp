#include "Player.hpp"
#include "../Piece/Piece.hpp"
#include "../Board/Board.hpp"
#include "../Move/Move.hpp"
#include "../Move/MoveTransition.hpp"

namespace Chess {

    Player::Player(Alliance ally, Board& board, Moves& legalMoves, Moves& opponentLegals) :
        ally(ally),
        legalMoves(legalMoves),
        king(nullptr) {
        this->activePieces = ally == Alliance::White ? board.getWhitePieces() : board.getBlackPieces();
        for(auto& piece : this->activePieces){
            if(!piece->isKing()) continue;
            if(this->king)
                throw std::invalid_argument("There's more than 1 King found!");
            this->king = std::shared_ptr<Piece>(piece);
        }
        if(!this->king)
            throw std::invalid_argument("No king found!");
        this->inCheck = calculateAttacksOnTile(opponentLegals, this->king->getPosition()).size() > 0;
    }

    const bool Player::isInCheckMate(){
        return this->inCheck && !hasEscapeMoves(*this);
    }

    const bool Player::isInStaleMate(){
        return !this->inCheck && !hasEscapeMoves(*this);
    }

    const Moves Player::calculateAttacksOnTile(Moves& opponentLegals, const int pos){
        Moves attackMoves;
        for(auto& move : opponentLegals){
            if(move->isAttackMove() && move->getDestination() == pos){
                attackMoves.push_back(move);
            }
        }
        return attackMoves;
    }

    MoveTransition Player::makeMove(std::shared_ptr<Board> current, std::shared_ptr<Move> move){
        MoveTransition ILLEGAL(current, move, MoveStatus::Illegal);
        if(!move) return ILLEGAL;
        auto next = move->execute();
        auto opponent = next->getOpponentPlayer();
        if((current->getCurrentPlayer()->isInCheck() && opponent->isInCheck()) || opponent->isInCheck())
            return MoveTransition(current, move, MoveStatus::LeavesPlayerInCheck);
        else if(!(opponent->isInCheck() || opponent->isInCheckMate() || opponent->isInStaleMate())){
            return MoveTransition(next, move, MoveStatus::Success);
        }
        return ILLEGAL;
    }

    const bool Player::hasEscapeMoves(Player& player){
        for(auto& move : player.getLegalMoves()){
            auto board = move->execute();
            if(!board->getOpponentPlayer()->isInCheck())
                return true;
        }
        return false;
    }

    std::ostream& operator <<(std::ostream& out, const Player& player){
        out << (player.isWhite() ? "White" : "Black");
        out << "Player[";
        out << "Pieces=" << player.activePieces.size() << ",";
        out << "Moves=" << player.legalMoves.size();
        out << "]";
        return out;
    }

}