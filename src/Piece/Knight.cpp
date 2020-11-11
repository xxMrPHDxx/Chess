#include <Piece/Knight.hpp>
#include <Board/Tile.hpp>
#include <Board/Board.hpp>
#include <BoardUtils.hpp>

#include <Move/MajorMove.hpp>
#include <Move/MajorAttackMove.hpp>

using namespace Chess;

constexpr int Knight::CANDIDATE_OFFSETS[];
const Moves Knight::calculateLegalMoves(Board& board){
    Moves legalMoves;
    for(const int& offset : CANDIDATE_OFFSETS){
        const int destination = position + offset;
        if(!BoardUtils::isValidTile(destination) || hasExclusion(position, offset))
            continue;
        Tile& tile = board[destination];
        if(tile.isOccupied()){
            Piece& piece = tile.getPiece();
            if(piece.getAlliance() != ally){
                legalMoves.push_back(std::make_shared<MajorAttackMove>(
                    board, *this, destination, piece
                ));
            }
        }else{
            legalMoves.push_back(std::make_shared<MajorMove>(
                board, *this, destination
            ));
        }
    }
    return legalMoves;
}

const bool Knight::isFirstColumnExcluded(int pos, int off){
    return BoardUtils::isFirstColumn(pos) && (off == -17 || off == -10 || off == 6 || off == 15);
}

const bool Knight::isSecondColumnExcluded(int pos, int off){
    return BoardUtils::isSecondColumn(pos) && (off == -10 || off == 6);
}

const bool Knight::isSeventhColumnExcluded(int pos, int off){
    return BoardUtils::isSeventhColumn(pos) && (off == -6 || off == 10);
}

const bool Knight::isEighthColumnExcluded(int pos, int off){
    return BoardUtils::isEighthColumn(pos) && (off == -15 || off == -6 || off == 10 || off == 17);
}