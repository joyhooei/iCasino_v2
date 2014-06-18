//
//  LogicInChess.h
//  iCasinov2
//
//  Created by Thanhhv on 6/5/14.
//
//

#ifndef __iCasinov2__LogicInChess__
#define __iCasinov2__LogicInChess__

#include <iostream>
//#include <vector.h>
#include "SceneManager.h"
#include "mUtils.h"
using namespace std;

class ChessLogic {
public:
    ChessLogic();
    ~ChessLogic();
    
    void loadNewGame();
    string toTableString();
    string getArrayLostPieces(int side); // side=1 | side=2
    bool checkCurrTurnMoveValid(int c, int pos);
    bool colorPos(int pos);
    bool piecePos(int pos);
    void Move(int from1, int dest1);
    int countPiece(int side);
    bool isLose(int side, int reason);
    bool isLostKing(int side);
    string getArrayKing(int side);
    vector<int> getAllMovesFromPos(int pos);
    bool IsInCheck(int xside2);
    bool IsKingSafe(int xside2);
    bool Attack(int pos, int side);
    bool moveSave(int from, int dest);
    bool IsKingFace(int pos);
    
private:
    
};

#endif /* defined(__iCasinov2__LogicInChess__) */
