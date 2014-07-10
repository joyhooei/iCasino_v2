//
//  LogicInChess.cpp
//  iCasinov2
//
//  Created by Thanhhv on 6/5/14.
//
//

#include "LogicInChess.h"

int BOARD_SIZE = 90;
vector<int> color;
vector<int> piece;

int DARK = 1;
int LIGHT = 2;
int PAWN = 0;
int BISHOP = 1;
int ELEPHANT = 2;
int KNIGHT = 3;
int CANNON = 4;
int ROOK = 5;
int KING = 6;
int EMPTY = 7;
int first_color[] = {DARK, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, LIGHT};
int first_piece[] = {ROOK, KNIGHT, ELEPHANT, BISHOP, KING, BISHOP, ELEPHANT, KNIGHT, ROOK, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CANNON, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CANNON, EMPTY, PAWN, EMPTY, PAWN, EMPTY, PAWN, EMPTY, PAWN, EMPTY, PAWN, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, PAWN, EMPTY, PAWN, EMPTY, PAWN, EMPTY, PAWN, EMPTY, PAWN, EMPTY, CANNON, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CANNON, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, ROOK, KNIGHT, ELEPHANT, BISHOP, KING, BISHOP, ELEPHANT, KNIGHT, ROOK};
string pieceName[] = {"pawn", "bishop", "elephan", "knight", "cannon", "rook", "king"};
string pieceColor[] = {"dark", "red"};
int offset[][8] = {{-1, 1, 13, 0, 0, 0, 0, 0},
    {-12, -14, 12, 14, 0, 0, 0, 0},
    {-28, -24, 24, 28, 0, 0, 0, 0},
    {-11, -15, -25, -27, 11, 15, 25, 27},
    {-1, 1, -13, 13, 0, 0, 0, 0},
    {-1, 1, -13, 13, 0, 0, 0, 0},
    {-1, 1, -13, 13, 0, 0, 0, 0}};
/**
 * @uml.property name;//"mailbox182" multiplicity;//"(0 -1)" dimension;//"1"
 */
int mailbox182[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, -1, -1, -1, -1, 9, 10, 11, 12, 13, 14, 15, 16, 17, -1, -1, -1, -1, 18, 19, 20, 21, 22, 23, 24, 25, 26, -1, -1, -1, -1, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, 36, 37, 38, 39, 40, 41, 42, 43, 44, -1, -1, -1, -1, 45, 46, 47, 48, 49, 50, 51, 52, 53, -1, -1, -1, -1, 54, 55, 56, 57, 58, 59, 60, 61, 62, -1, -1, -1, -1, 63, 64, 65, 66, 67, 68, 69, 70, 71, -1, -1, -1, -1, 72, 73, 74, 75, 76, 77, 78, 79, 80, -1, -1, -1, -1, 81, 82, 83, 84, 85, 86, 87, 88, 89, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
/**
 * @uml.property name;//"mailbox90" multiplicity;//"(0 -1)" dimension;//"1"
 */
int mailbox90[] = {28, 29, 30, 31, 32, 33, 34, 35, 36, 41, 42, 43, 44, 45, 46, 47, 48, 49, 54, 55, 56, 57, 58, 59, 60, 61, 62, 67, 68, 69, 70, 71, 72, 73, 74, 75, 80, 81, 82, 83, 84, 85, 86, 87, 88, 93, 94, 95, 96, 97, 98, 99, 100, 101, 106, 107, 108, 109, 110, 111, 112, 113, 114, 119, 120, 121, 122, 123, 124, 125, 126, 127, 132, 133, 134, 135, 136, 137, 138, 139, 140, 145, 146, 147, 148, 149, 150, 151, 152, 153};
/**
 * @uml.property name;//"legalposition" multiplicity;//"(0 -1)" dimension;//"1"
 */
int legalposition[]= {1, 1, 5, 3, 3, 3, 5, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 5, 1, 1, 3, 7, 3, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1, 13, 1, 9, 1, 13, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
/**
 * @uml.property name;//"maskpiece" multiplicity;//"(0 -1)" dimension;//"1"
 */
int maskpiece[] = {8, 2, 4, 1, 1, 1, 2};
/**
 * @uml.property name;//"knightcheck" multiplicity;//"(0 -1)" dimension;//"1"
 */
int knightcheck[] = {1, -1, -9, -9, -1, 1, 9, 9};
/**
 * @uml.property name;//"knightcheck2" multiplicity;//"(0 -1)" dimension;//"1"
 */
int knightcheck2[] = {-8, -10, -8, -10, 8, 10, 8, 10};
/**
 * @uml.property name;//"elephancheck" multiplicity;//"(0 -1)" dimension;//"1"
 */
int elephancheck[] = {-10, -8, 8, 10, 0, 0, 0, 0};
/**
 * @uml.property name;//"kingpalace" multiplicity;//"(0 -1)" dimension;//"2"
 */
int kingpalace[][9] = {{3, 4, 5, 12, 13, 14, 21, 22, 23}, {66, 67, 68, 75, 76, 77, 84, 85, 86}};

ChessLogic::ChessLogic(){
    
}

ChessLogic::~ChessLogic() {}


/// ----------
//// ---------


void ChessLogic::loadNewGame() {
    color.clear();
    piece.clear();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        color.push_back(first_color[i]);
        piece.push_back(first_piece[i]);
    }
};

/*
 * lấy danh sách các quân cờ trên bàn cờ theo định dạng:
 * tenquanco_mau_tenquanco_mau_ (ví dụ: 5_1_3_1____)
 */
string ChessLogic::toTableString() {
    string s = "";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (piece[i] == EMPTY) {
            s += "";
        } else {
            s += to_string(piece[i]) + "_" + to_string(color[i]);
        }
        s += "_";
    }
    
    return s;
};

/*
 * Đếm số quân đã mất:
 * return: xe_phao_ma_tuongj_si_tot (vd: 1_0_1_0_0_3)
 */
string ChessLogic::getArrayLostPieces(int side) {
    string str = "";
    // Sỹ 2; Tuợng 2; Mã 2; Xe 2; Pháo 2; tốt 5
    int countPawn = 0, countBishop = 0, countElephant = 0, countKnight = 0, countCannon = 0, countRook = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (color[i] == side) {
            if (piece[i] == PAWN)
                    countPawn++;
            else if (piece[i] == BISHOP)
                    countBishop++;
            else if (piece[i] == ELEPHANT)
                    countElephant++;
            else if (piece[i] == KNIGHT)
                    countKnight++;
            else if (piece[i] == CANNON)
                    countCannon++;
            else if (piece[i] == ROOK)
                    countRook++;
            }
        }
    // To string
    // str = PAWN + "_" + (5 - countPawn) + "-";
    // str = BISHOP + "_" + (2 - countBishop) + "-";
    // str = ELEPHANT + "_" + (2 - countElephant) + "-";
    // str = KNIGHT + "_" + (2 - countKnight) + "-";
    // str = CANNON + "_" + (2 - countCannon) + "-";
    // str = ROOK + "_" + (2 - countRook);
    
	ostringstream osRook, osCannon, osKnight, osElephant, osBishop, osPawn;
	osRook<<(countRook);
	osCannon<<(countCannon);
	osKnight<<(countKnight);
	osElephant<<(countElephant);
	osBishop<<(countBishop);
	osPawn<<(countPawn);
	
	str = "x" + osRook.str() + "_" + "x" + osCannon.str() + "_" + "x" + osKnight.str() + "_" + "x" + osElephant.str() + "_" + "x" + osBishop.str() + "_" + "x" + osPawn.str();
	//str = countRook + "_" + countCannon + '_' + countKnight + '_' + countElephant + '_' + countBishop + '_' + countPawn;
    
    return str;
};

/*
 * Kiểm tra xem quân di chuyển có đúng màu của nguời chơi hiện taị hay không
 * c: màu (DARK | LIGHT)
 * pos: vị trí quân trên bàn(0 -> 89)
 */
bool ChessLogic::checkCurrTurnMoveValid(int c, int pos) {
    return (color[pos] == c);
};

bool ChessLogic::colorPos(int pos) {
    return color[pos];
};

bool ChessLogic::piecePos(int pos) {
    return piece[pos];
};

/*
 * move a piece,
 * chỉ được gọi đến khi đã kiểm tra nước đi hợp lệ
 */
void ChessLogic::Move(int from1, int dest1) {
    if (from1 < 0 || from1 > 89 || dest1 < 0 || dest1 > 89)
        return;
    piece[dest1] = piece[from1];
    color[dest1] = color[from1];
    piece[from1] = EMPTY;
    color[from1] = 0;
};

// số quân cờ còn lại trên bàn của bên side (DARK or LIGHT)
int ChessLogic::countPiece(int side) {
    int count = 0;
    
    for (int  i = 0; i < BOARD_SIZE; ++i) {
        if (color[i] == side && piece[i] != EMPTY) {
            count++;
        }
    }
    
    return count;
};

/*
 * kiem tra xem con nuoc di nao khong neu het thi thua
 */
bool ChessLogic::isLose(int side, int reason) {
    reason = 0;
    bool check = false;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (color[i] == side) {
            vector<int> arr = getAllMovesFromPos(i);
            if (arr.size() > 0) {
                // return false;
                check = true;
                break;
            }
        }
    }
    if (!check) {
        reason = 1;
        return true;
    }// Không còn nước đi
    // Kiem tra tuong
    check = false;
    for (int i = 0; i < 9; i++) {
        int pos = kingpalace[side - 1][i];
        if (piece[pos] == KING) {
            check = true;
            break;
        }
    }
    if (!check) {
        reason = 2;
        return true;
        // Mất tướng
    }
    return false;
};

bool ChessLogic::isLostKing(int side) {
    // Kiem tra tuong
    bool check = false;
    for (int i = 0; i < 9; i++) {
        int pos = kingpalace[side - 1][i];
        if (piece[pos] == KING) {
            check = true;
            break;
        }
    }
    if (!check) {
        return true;
        // Mất tướng
    }
    return false;
}

// trả về các vị trí tướng có thể đi
string ChessLogic::getArrayKing(int side) {
    int i = 0, pos = -1;
    string s = "";
    for ( i = 0; i < 9; i++) {
        pos = kingpalace[side - 1][i];
        s += to_string(piece[pos]) + "_";
    }
    return s;
};

/*
 * get all move from pos
 */
vector<int> ChessLogic::getAllMovesFromPos(int pos) {
    vector<int> move(20);
    // tối đa chỉ 20 nước đi
    
    // màu
    int side = color[pos];
    
    // vị trí
    int p = piece[pos];
    
    if (p == EMPTY)
        return move;
    
    int xside = (3 - side);
    int n, x, y, fcannon, t, dem = 0;
    // so huong di toi da la 8
    for (int j = 0; j < 8; ++j) {
        if (offset[p][j] == 0) {
            break;
        }
        x = mailbox90[pos];
        fcannon = 0;
        if (p == ROOK || p == CANNON) {
            n = 9;
        } else {
            n = 1;
        }
        for (int k = 0; k < n; k++) {
            if (p == PAWN && side == LIGHT) {
                x -= offset[p][j];
            } else {
                x += offset[p][j];
            }
            
            y = mailbox182[x];
            if (side == DARK) {
                t = y;
            } else {
                t = 89 - y;
            }
            if (y == -1 || (legalposition[t] & maskpiece[p]) == 0) {
                break;
            }
            if (fcannon == 0) {
                if (color[y] != side) {
                    if (p == KNIGHT) {
                            // System.out.println("night");
                            if (color[pos + knightcheck[j]] == 0 && moveSave(pos, y))// Gen_push(i, y);
                            {
                                move[dem++] = y;
                                // System.out.println("move "+y);
                            }
                    }
                    else if (p == ELEPHANT) {
                            if (color[pos + elephancheck[j]] == 0 && moveSave(pos, y))// Gen_push(i, y);
                            {
                                move[dem++] = y;
                            }
                    }
                    else if (p == CANNON) {
                            if (color[y] == 0 && moveSave(pos, y))// Gen_push(i,
								// y);
                            {
                                move[dem++] = y;
                                // System.out.println("move "+y);
                            }
                    }
                    else {
                            // Gen_push(i, y);
                            if (moveSave(pos, y)) {
                                move[dem++] = y;
                            }
							// System.out.println("move "+y);
                    }
                }
                if (color[y] != 0) {
                    if (p == CANNON) {
                        fcannon++;
                    } else {
                        break;
                    }
                }
            }/*
              * if fcannon == 0
              */
            else {/*
                   * CANNON switch
                   */
                if (color[y] != 0) {
                    if (color[y] == xside && moveSave(pos, y))// Gen_push(i,
						// y);
                    {
                        move[dem++] = y;
                        // System.out.println("move "+y);
                    }
                    break;
                }
            }/*
              * else fcannon
              */
        } /*
           * for k
           */
    }/*
      * for i
      */
    move[dem] = -1;
    // System.out.println("dem: "+dem);
    return move;
};

// kiểm tra xem tướng đang ở vị trí nào sau đó kiểm tra xem tướng có dang bị
// chiếu ko

bool ChessLogic::IsInCheck(int xside2) {
    int i = 0, pos;
    do {
        // System.out.println("side "+xside+ " i"+ i);
        pos = kingpalace[xside2 - 1][i];
        
        i++;
    } while (piece[pos] != KING);
    // System.out.println("pos king"+pos);
    return Attack(pos, xside2);
};

bool ChessLogic::IsKingSafe(int xside2) {
    int i = 0, pos;
    do {
        // System.out.println("side "+xside+ " i"+ i);
        pos = kingpalace[xside2 - 1][i];
		//CCLog("ChessLogic::IsKingSafe pos=%d", pos);
        i++;
		if (pos < 0 || pos >= 90) return true;
    } while (piece[pos] != KING);
    if (Attack(pos, xside2)) {
        // System.out.println("chieu");
    }
    return !(Attack(pos, xside2) || IsKingFace(pos));
};

/*
 *
 */

bool ChessLogic::Attack(int pos, int side) {
    
    int j, k, x, y, fcannon, sd, xsd;
    
    sd = side;
    xsd = 3 - sd;
    
    for ( j = 0; j < 4; j++) {// ROOK, CANNON, PAWN, KING
        x = mailbox90[pos];
        fcannon = 0;
        for ( k = 0; k < 9; k++) {
            x = x + offset[ROOK][j];
            y = mailbox182[x];
            if (y == -1) {
                break;
            }
            if (fcannon == 0) {
                if (color[y] == xsd) {
                    if (piece[y] == ROOK) {
                            return true;
							// if(sd==LIGHT) {
							// if(y!=32&&y!=33&&y!=34) return true;
							// }
                    }
                    else if (piece[y] == KING){
                            if (piece[pos] == KING) {
                                return true;
                            }
                    }
                    else if (piece[y] == PAWN){
                            if (k == 0 && ((sd == DARK && j != 2) || (sd == LIGHT && j != 3))) {
                                return true;
                            }
                    }
                }
                if (piece[y] != EMPTY) {
                    fcannon = 1;
                }
            } else// CANNON case
				if (piece[y] != EMPTY) {
					if (color[y] == xsd && piece[y] == CANNON) {
						return true;
					}
					break;
				}
        } // for k
    }// for j
    
    for ( j = 0; j < 8; j++) {// Knight Check
        y = mailbox182[mailbox90[pos] + offset[KNIGHT][j]];
        if (y == -1) {
            continue;
        }
        if (color[y] == xsd && piece[y] == KNIGHT && piece[pos + knightcheck2[j]] == EMPTY) {
            return true;
        }
    }
    return false;
};

/*
 * kiem tra nuoc di co an toan ko?
 */
bool ChessLogic::moveSave(int from, int dest) {
    if (true)
        return true;
    
    int pFrom = piece[from];
    int cFrom = color[from];
    int pDest = piece[dest];
    int cDest = color[dest];
    Move(from, dest);
    bool k = IsKingSafe(color[dest]);
    
    piece[from] = pFrom;
    color[from] = cFrom;
    piece[dest] = pDest;
    color[dest] = cDest;
    return k;
};

bool ChessLogic::IsKingFace(int pos) {
    int k, p = pos;
    if (color[pos] == DARK) {
        k = 9;
    } else {
        k = -9;
    }
    for (int i = 0; i < 10; ++i) {
        p += k;
        if (p < 0 || p > 89) {
            break;
        }
        // System.out.println("p "+p);
        if (piece[p] != EMPTY && piece[p] != KING) {
            return false;
        } else if (piece[p] == KING) {
            return true;
        }
    }
    return false;
};

void ChessLogic::setChessIDBySide( int idChess, int side, int pos )
{
	color[pos] = side;
	piece[pos] = idChess;
}



