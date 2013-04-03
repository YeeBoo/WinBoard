/**
 * @author Wanderley Caloni Jr (blakhalk@ig.com.br).
 * @date 02.2004
 * 
 * Winboard Extension. Calculate the piece influences on the board.
 * Test Application.
 */

#include "infboard.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int printHelp()
{
  printf("Modo de usar (ex): InfluenceBoard 3p4.8.8.4DR2.8.7b.R6p.5C2\n");
  return 0;
}



int main(int argc, char *argv[])
{
  if( argc == 2 )
    return GenInfluencesFromPos(argv[1]);
  else
    return printHelp();
}
