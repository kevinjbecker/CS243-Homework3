/// http://www.dreamincode.net/forums/topic/55572-conways-game-of-life/
/// downloaded by copy-paste on 8/19/2015 and modified to use an infinite loop.
///
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; e.g. mix of TAB and spaces indentation
/// </li>
/// <li>  documentation: documentation is non-existent except for this block.
/// </li>
/// </ol>
///
/// Author: kjb2503 | Kevin Becker
///
/// // // // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h> // printf, scanf
#include <stdlib.h> // EXIT_SUCCESS, srand, rand
#define TOT_GENS 100
#define GRID_SIZE 20

///
/// Function: startLife
///
/// Description: Prints a basic welcome screen and gets the number of alive cells the
///              user wants when the game begins.
///
/// @return: The number of organisms a user wants to start with as a SHORT (smallest possible).
///
short startLife(void)
{
    // storage variable for the number of organism the game should have
    int numOrgs;
    // prints our splash
    printf("\n\t..Welcome to the Game of life..\n");

    // prompts our user to input the number of initial organisms they want on the board
    printf("\nPlease enter the initial number of organisms (0-400; exclusive): ");

    // gets the number from user
    scanf("%i", &numOrgs);

    // returns the number the user enters
    return numOrgs;
}


///
/// Function: generateLifeBoard
///
/// Description: Generates a starting life board with the number of organisms requested by the user.
///
/// @param numOrgs  The number of ``organisms'' to put in our board.
/// @param size  The size of each row in the ``board''.
/// @param board  The life board.
///
void generateLifeBoard(short numOrgs, int size, char board[][size])
{
    // starts a random generator (31 is a magic number because it's just a seed for rand)
    // NOTE: Because the seed is 31 (and always 31) the board will always generate the same
    srand(31);

    // sets every cell to be a dead cell to begin, we'll fill in living ones later
    // (removes the conditional required for doing this in opposite order)
    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
                board[row][col] = ' ';

    // generates our "alive" cells randomized in location
    for (int i = 0; i < numOrgs; ++i)
        board[rand() % size][rand() % size] = '*';
}



///
/// Function: getNumAliveNeighbors
///
/// Description: Gets the number of alive neighbors for a given cell.
///
/// @param row  The row we want to compute.
/// @param col  The col we want to compute.
/// @param size  The size of each row in the ``board''.
/// @param board  The life board.
///
/// @return The number of living neighbors the cell at (row, col) has.
///         (NOTE: char return type because we only have 8 neighbors, so
///          we don't need any more than what a char holds)
///
char getNumAliveNeighbors(int row, int col, int size, char board[][size])
{
    // the total number of neighbors
    int aliveNeighbors = 0;

    // the row index of the row above (including wrap around)
    int rowN = (row == 0 ? (size - 1) : (row - 1));
    // the row index of the row below (including wrap around)
    int rowS = (row == (size - 1) ? 0 : (row + 1));
    // the column index of the column to the left (including wrap-around)
    int colW = (col == 0 ? (size - 1) : (col - 1));
    // the column index of the column to the right (including wrap-around)
    int colE = (col == (size - 1) ? 0 : (col + 1));

    //calculate total alive neighbors (based on cardinal direction)
    // NW
    if (board[rowN][colW] == '*') ++aliveNeighbors;
    // N
    if (board[rowN][col] == '*') ++aliveNeighbors;
    // NE
    if (board[rowN][colE] == '*') ++aliveNeighbors;
    // E
    if (board[row][colE]  == '*') ++aliveNeighbors;
    // SE
    if (board[rowS][colE] == '*') ++aliveNeighbors;
    // S
    if (board[rowS][col] == '*') ++aliveNeighbors;
    // SW
    if (board[rowS][colW] == '*') ++aliveNeighbors;
    // W
    if (board[row][colW] == '*') ++aliveNeighbors;

    // return the number of alive neighbors
    return aliveNeighbors;
}


///
/// Function: computerNextGeneration
///
/// Description: Computes the next generation in our game of life based off the board passed in.
///
/// @param size  The size of each row in the ``board''.
/// @param board  The life board.
///
void computeNextGeneration(int size, char curGeneration[][size])
{
    char numAliveNeighbors, nextGeneration[size][size];
    int row, col;

    for (row = 0; row < size; ++row)
        for (col = 0; col < size; ++col)
        {
            numAliveNeighbors = getNumAliveNeighbors(row, col, size, curGeneration);
            switch (curGeneration[row][col])
            {
                case '*':
                    //                                too many or too few live neighbors        ? die : live
                    nextGeneration[row][col] = (numAliveNeighbors < 2 || numAliveNeighbors > 3) ? ' ' : '*';
                    break;
                case ' ':
                    //                           three live neighbors   ? life: dead
                    nextGeneration[row][col] = (numAliveNeighbors == 3) ? '*' : ' ';
                    break;
            }
        }

    //copy over new generation to old
    for (row = 0; row < size; ++row)
        for (col = 0; col < size; ++col)
            curGeneration[row][col] = nextGeneration[row][col];
}


///
/// Function: printBoard
///
/// Description: Prints our board to standard out.
///
/// @param size  The size of each row in the ``board''.
/// @param board  The life board.
/// @param genNum  The current generation we are on.
///
void printBoard(int genNum, int size, char board[][size])
{
    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col)
        {
            printf("%c", board[row][col]);
        }
        puts(" ");
    }
    // tells the user what generation we're on
    printf("\ngeneration: %d\n", genNum);
}


///
/// Function: main
///
/// Description: The main driver for an implementation of Conway's Game of Life.
///
/// @return: An integer; EXIT_SUCCESS for success, anything else otherwise.
///
int main(void)
{
    // the size of our board (20x20)
    int size = GRID_SIZE;

    // our life ``board''
    char board[size][size];

    // the number of organisms the user wants -- SHORT
    short numOrgs = startLife();

    // generates our life board
    generateLifeBoard(numOrgs, size, board);

    // runs our game for TOT_GENS (the total number of generations)
    for(int gens = 0; gens < TOT_GENS; ++gens)
    {
        // prints our new board
        printBoard(gens, size, board);
        // computes our next generation in life
        computeNextGeneration(size, board);
    }

    return EXIT_SUCCESS;
}

