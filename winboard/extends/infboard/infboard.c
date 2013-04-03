/**
 * @author Wanderley Caloni Jr (blakhalk@ig.com.br).
 * @date 02.2004
 * 
 * Winboard Extension. Calculate the piece influences on the board.
 */

#ifndef WIN32
#define WIN32
#endif

#include "infboard.h"

#include <ctype.h>
#include <string.h>



/**
 * Empty influences on the InfluenceBoard specified.
 */
int ZeroInfluenceBoard(InfluenceBoard infBoard)
{
   memset(infBoard, 0, sizeof(InfluenceBoard));
   return 0;
}



/**
 * Write the board piece influences to infBoard.
 */
int GenInfluences(InfluenceBoard infBoard, Board board)
{
   int iRet = 0;
   ChessSquare sq;
   int iRow, iCol;
   
   ZeroInfluenceBoard(infBoard);

   for( iRow = 0; iRow < BOARD_SIZE; ++iRow )
      for( iCol = 0; iCol < BOARD_SIZE; ++iCol )
      {
         sq = board[iRow][iCol];
      
         if( WhitePiece(sq) || BlackPiece(sq) )
            iRet += GenInfluencesForPiece(infBoard, board, sq, iRow, iCol);
      }
      
   return iRet;
}



/**
 * Calculate the one piece influences located on board[iRow][iCol] 
 * and write them to infBoard.
 */
int GenInfluencesForPiece(InfluenceBoard infBoard, const Board board,
   ChessSquare piece, int iRow, int iCol)
{
   int isWhite = WhitePiece(piece);
   
   switch( piece )
   {
      case WhitePawn:
      case BlackPawn:
         return GenInfluencesForPawn(infBoard, board, iRow, iCol, isWhite);

      case WhiteKnight:
      case BlackKnight:
         return GenInfluencesForKnight(infBoard, board, iRow, iCol, isWhite);

      case WhiteBishop:
      case BlackBishop:
         return GenInfluencesForBishop(infBoard, board, iRow, iCol, isWhite);

      case WhiteRook:
      case BlackRook:
         return GenInfluencesForRook(infBoard, board, iRow, iCol, isWhite);

      case WhiteQueen:
      case BlackQueen:
         return GenInfluencesForQueen(infBoard, board, iRow, iCol, isWhite);

      case WhiteKing:
      case BlackKing:
         return GenInfluencesForKing(infBoard, board, iRow, iCol, isWhite);
         
      default:
         return 0;
   }
}



/**
 * Calculate the influences from a pawn located on board[iRow][iCol] 
 * and write them at infBoard.
 */
int GenInfluencesForPawn(InfluenceBoard infBoard, const Board board,
   int iRow, int iCol, int isWhite)
{
   int iRet = 0;
   iRow += isWhite ? 1 : -1;

   // If next file exists for the pawn.
   if( ( isWhite && iRow < BOARD_SIZE ) ||
       ( !isWhite && iRow >= 0 ) )
   {
      // Left oblique line.
      if( iCol - 1 >= 0 )
      {
         INCR_INFLUENCE(infBoard[iRow][iCol - 1], isWhite);
         ++iRet;
      }

      // Right oblique line.
      if( iCol + 1 < BOARD_SIZE )
      {
         INCR_INFLUENCE(infBoard[iRow][iCol + 1], isWhite);
         ++iRet;
      }
   }
   
   return isWhite ? iRet : -iRet;
}



/**
 * Calculate the influences from a knight located on board[iRow][iCol] 
 * and write them at infBoard.
 */
int GenInfluencesForKnight(InfluenceBoard infBoard, const Board board,
   int iRow, int iCol, int isWhite)
{
   int iRet = 0;

   if( iRow + 1 < BOARD_SIZE )
   {
      if( iCol - 2 >= 0 )
      {
         INCR_INFLUENCE(infBoard[iRow + 1][iCol - 2], isWhite);
         ++iRet;
      }
         
      if( iCol + 2 < BOARD_SIZE )
      {
         INCR_INFLUENCE(infBoard[iRow + 1][iCol + 2], isWhite);
         ++iRet;
      }
         
      if( iRow + 2 < BOARD_SIZE )
      {
         if( iCol - 1 >= 0 )
         {
            INCR_INFLUENCE(infBoard[iRow + 2][iCol - 1], isWhite);
            ++iRet;
         }
            
         if( iCol + 1 < BOARD_SIZE )
         {
            INCR_INFLUENCE(infBoard[iRow + 2][iCol + 1], isWhite);
            ++iRet;
         }
      }
   }

   if( iRow - 1 >= 0 )
   {
      if( iCol - 2 >= 0 )
      {
         INCR_INFLUENCE(infBoard[iRow - 1][iCol - 2], isWhite);
         ++iRet;
      }
         
      if( iCol + 2 < BOARD_SIZE )
      {
         INCR_INFLUENCE(infBoard[iRow - 1][iCol + 2], isWhite);
         ++iRet;
      }
         
      if( iRow - 2 >= 0 )
      {
         if( iCol - 1 >= 0 )
         {
            INCR_INFLUENCE(infBoard[iRow - 2][iCol - 1], isWhite);
            ++iRet;
         }
            
         if( iCol + 1 < BOARD_SIZE )
         {
            INCR_INFLUENCE(infBoard[iRow - 2][iCol + 1], isWhite);
            ++iRet;
         }
      }
   }
   
   return isWhite ? iRet : -iRet;
}



/**
 * Calculate the influences from a bishop located on board[iRow][iCol] 
 * and write them at infBoard.
 */
int GenInfluencesForBishop(InfluenceBoard infBoard, const Board board,
   int iRow, int iCol, int isWhite)
{
   int iRet = 0;
   ChessSquare sq;
   int i, j;

   for( i = iRow + 1, j = iCol - 1;
      i < BOARD_SIZE && j >= 0;
      ++i, --j )
   {
      sq = board[i][j];
      INCR_INFLUENCE(infBoard[i][j], isWhite);
      ++iRet;
      
      if( IS_PAWN(board[i-1][j+1]) )
         break;
      if( isWhite && IS_PAWN(sq) && WhitePiece(sq) )
         continue;
      if( IS_BISHOP(sq) || IS_QUEEN(sq) )
         continue;
      if( !IS_EMPTY_SQUARE(sq) )
         break;
   }

   for( i = iRow + 1, j = iCol + 1;
      i < BOARD_SIZE && j < BOARD_SIZE;
      ++i, ++j )
   {
      sq = board[i][j];
      INCR_INFLUENCE(infBoard[i][j], isWhite);
      ++iRet;
      
      if( IS_PAWN(board[i-1][j-1]) )
         break;
      if( isWhite && IS_PAWN(sq) && WhitePiece(sq) )
         continue;
      if( IS_BISHOP(sq) || IS_QUEEN(sq) )
         continue;
      if( !IS_EMPTY_SQUARE(sq) )
         break;
   }

   for( i = iRow - 1, j = iCol - 1;
      i >= 0 && j >= 0;
      --i, --j )
   {
      sq = board[i][j];
      INCR_INFLUENCE(infBoard[i][j], isWhite);
      ++iRet;
      
      if( IS_PAWN(board[i+1][j+1]) )
         break;
      if( !isWhite && IS_PAWN(sq) && BlackPiece(sq) )
         continue;
      if( IS_BISHOP(sq) || IS_QUEEN(sq) )
         continue;
      if( !IS_EMPTY_SQUARE(sq) )
         break;
   }

   for( i = iRow - 1, j = iCol + 1;
      i >= 0 && j < BOARD_SIZE;
      --i, ++j )
   {
      sq = board[i][j];
      INCR_INFLUENCE(infBoard[i][j], isWhite);
      ++iRet;
      
      if( IS_PAWN(board[i+1][j-1]) )
         break;
      if( !isWhite && IS_PAWN(sq) && BlackPiece(sq) )
         continue;
      if( IS_BISHOP(sq) || IS_QUEEN(sq) )
         continue;
      if( !IS_EMPTY_SQUARE(sq) )
         break;
   }
   
   return isWhite ? iRet : -iRet;
}



/**
 * Calculate the influences from a rook located on board[iRow][iCol] 
 * and write them at infBoard.
 */
int GenInfluencesForRook(InfluenceBoard infBoard, const Board board,
   int iRow, int iCol, int isWhite)
{
   int iRet = 0;
   ChessSquare sq;
   int i;
   
   for( i = iRow + 1; i < BOARD_SIZE; ++i )
   {
      sq = board[i][iCol];
      INCR_INFLUENCE(infBoard[i][iCol], isWhite);
      ++iRet;
      
      if( isWhite == WhitePiece(sq) && (IS_ROOK(sq) || IS_QUEEN(sq)) )
         continue;
      if( !IS_EMPTY_SQUARE(sq) )
         break;
   }
   
   
   for( i = iCol - 1; i >= 0; --i )
   {
      sq = board[iRow][i];
      INCR_INFLUENCE(infBoard[iRow][i], isWhite);
      ++iRet;
      
      if( isWhite == WhitePiece(sq) && (IS_ROOK(sq) || IS_QUEEN(sq)) )
         continue;
      if( !IS_EMPTY_SQUARE(sq) )
         break;
   }
   
   for( i = iCol + 1; i < BOARD_SIZE; ++i )
   {
      sq = board[iRow][i];
      INCR_INFLUENCE(infBoard[iRow][i], isWhite);
      ++iRet;
      
      if( isWhite == WhitePiece(sq) && (IS_ROOK(sq) || IS_QUEEN(sq)) )
         continue;
      if( !IS_EMPTY_SQUARE(sq) )
         break;
   }
   
   for( i = iRow - 1; i >= 0; --i )
   {
      sq = board[i][iCol];
      INCR_INFLUENCE(infBoard[i][iCol], isWhite);
      ++iRet;
      
      if( isWhite == WhitePiece(sq) && (IS_ROOK(sq) || IS_QUEEN(sq)) )
         continue;
      if( !IS_EMPTY_SQUARE(sq) )
         break;
   }

   return isWhite ? iRet : -iRet;
}



/**
 * Calculate the influences from a queen located on board[iRow][iCol] 
 * and write them at infBoard.
 */
int GenInfluencesForQueen(InfluenceBoard infBoard, const Board board,
   int iRow, int iCol, int isWhite)
{
   int iRet;
   
   iRet = GenInfluencesForBishop(infBoard, board, iRow, iCol, isWhite);
   iRet += GenInfluencesForRook(infBoard, board, iRow, iCol, isWhite);
   
   return iRet;
}



/**
 * Calculate the influences from a king located on board[iRow][iCol] 
 * and write them at infBoard.
 */
int GenInfluencesForKing(InfluenceBoard infBoard, const Board board,
   int iRow, int iCol, int isWhite)
{
   int iRet = 0;
   
   if( iRow + 1 < BOARD_SIZE )
   {
      INCR_INFLUENCE(infBoard[iRow + 1][iCol], isWhite);
      ++iRet;
      
      if( iCol - 1 >= 0 )
      {
         INCR_INFLUENCE(infBoard[iRow + 1][iCol - 1], isWhite);
         ++iRet;
      }

      if( iCol + 1 < BOARD_SIZE )
      {
         INCR_INFLUENCE(infBoard[iRow + 1][iCol + 1], isWhite);
         ++iRet;
      }
   }
   
   if( iCol - 1 >= 0 )
   {
      INCR_INFLUENCE(infBoard[iRow][iCol - 1], isWhite);
      ++iRet;
   }

   if( iCol + 1 < BOARD_SIZE )
   {
      INCR_INFLUENCE(infBoard[iRow][iCol + 1], isWhite);
      ++iRet;
   }

   if( iRow - 1 >= 0 )
   {
      INCR_INFLUENCE(infBoard[iRow - 1][iCol], isWhite);
      ++iRet;
      
      if( iCol - 1 >= 0 )
      {
         INCR_INFLUENCE(infBoard[iRow - 1][iCol - 1], isWhite);
         ++iRet;
      }

      if( iCol + 1 < BOARD_SIZE )
      {
         INCR_INFLUENCE(infBoard[iRow - 1][iCol + 1], isWhite);
         ++iRet;
      }
   }

   return isWhite ? iRet : -iRet;
}



/**
 * Calculate the influences from a specified position on the sbrubles format.
 */
int GenInfluencesFromPos(char *pszPos)
{
   static const char c_szTokens[] = "PCBTDRpcbtdr";
   Board board;
   InfluenceBoard inflBoard;
   int iRow, iCol;
   char *pszTok;

   for( iRow = 0; iRow < BOARD_SIZE; ++iRow )
      for( iCol = 0; iCol < BOARD_SIZE; ++iCol )
         board[iRow][iCol] = EmptySquare;

   ZeroInfluenceBoard(inflBoard);

   for( iRow = 7; iRow >= 0; --iRow, ++pszPos )
      for( iCol = 0; iCol < BOARD_SIZE; ++iCol, ++pszPos )
      {
         if( *pszPos == '.' )
            break;
         else
            if( isdigit(*pszPos) )
               iCol += (*pszPos - '0') - 1;
            else
               if( pszTok = strchr(c_szTokens, *pszPos) )
                  board[iRow][iCol] = (ChessSquare)(pszTok - c_szTokens);
      }

      return GenInfluences(inflBoard, board);
}
