/**
 * @author Wanderley Caloni Jr (blakhalk@ig.com.br).
 * @date 02.2004
 * 
 * Winboard Extension. Calculate the piece influences on the board.
 */

/** WinBoard. */
#include <common.h>
#include <moves.h>



/** Defines. */
#define IS_PAWN(piece) (piece==WhitePawn || piece==BlackPawn)
#define IS_KNIGHT(piece) (piece==WhiteKnight || piece==BlackKnight)
#define IS_BISHOP(piece) (piece==WhiteBishop || piece==BlackBishop)
#define IS_ROOK(piece) (piece==WhiteRook || piece==BlackRook)
#define IS_QUEEN(piece) (piece==WhiteQueen || piece==BlackQueen)
#define IS_KING(piece) (piece==WhiteKing || piece==BlackKing)
#define IS_EMPTY_SQUARE(piece) (piece==EmptySquare)

#define INCR_INFLUENCE(var,iswhite) (iswhite ? ++var.white : ++var.black)



/** Store the influences from the pieces over it. */
typedef struct
{
  char white;
  char black;
}
InfluenceSquare;


/** Piece Influences Chessboard. */
typedef InfluenceSquare InfluenceBoard[BOARD_SIZE][BOARD_SIZE];



/** Prototypes. */

/** From moves.c */
extern int WhitePiece(ChessSquare piece);
extern int BlackPiece(ChessSquare piece);

extern int ZeroInfluenceBoard(InfluenceBoard infBoard);

extern int GenInfluences(InfluenceBoard infBoard, Board board);

extern int GenInfluencesForPiece(InfluenceBoard infBoard, 
   const Board board, ChessSquare piece, int iRow, int iCol);

extern int GenInfluencesForPawn(InfluenceBoard infBoard, 
   const Board board, int iRow, int iCol, int isWhite);
   
extern int GenInfluencesForKnight(InfluenceBoard infBoard, 
   const Board board, int iRow, int iCol, int isWhite);

extern int GenInfluencesForBishop(InfluenceBoard infBoard, 
   const Board board, int iRow, int iCol, int isWhite);

extern int GenInfluencesForRook(InfluenceBoard infBoard, 
   const Board board, int iRow, int iCol, int isWhite);

extern int GenInfluencesForQueen(InfluenceBoard infBoard, 
   const Board board, int iRow, int iCol, int isWhite);

extern int GenInfluencesForKing(InfluenceBoard infBoard, 
   const Board board, int iRow, int iCol, int isWhite);

extern int GenInfluencesFromPos(char *pszPos);
