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
/// @author: kjb2503 : Kevin Becker
///
/// // // // // // // // // // // // // // // // // // // // // // // // // // // //

#define _BSD_SOURCE // required for unistd.h
#include <unistd.h> // usleep
#include "display.h" // clear, put, set_cur_pos
#include <stdio.h> // printf, scanf
#include <stdlib.h> // EXIT_SUCCESS, srand, rand
#include <time.h> // time

// a few custom MACROs
#define SLEEP_TIME 81000 // the sleep period between the display of each generation
#define ALIVE '*' // the character used if a cell is alive
#define DEAD ' ' // the character used if a cell is dead


///
/// Function: startLife
///
/// Description: Prints a basic welcome screen and gets the number of alive cells the
///              user wants when the game begins.
///
/// @return: The number of organisms a user wants to start with as a SHORT (smallest possible).
///
int startLife(int size)
{
    // storage variable for the number of organism the game should have
    int numOrgs;

    // clears our screen and sets our cursor before printing our splash
    clear();
    set_cur_pos(1,1);

    // prints our splash
    printf("\n\t..Welcome to the Game of life..\n");

    // continue to request numbers until we get one within our range
    while(1)
    {
        // prompts our user to input the number of initial organisms they want on the board
        printf("\nPlease enter the initial number of organisms (0-%d; exclusive): ", (size * size));

        // gets the number from user
        scanf("%i", &numOrgs);

        // if we get a good number, break our loop, ask again otherwise
        if(numOrgs > 0 && numOrgs < (size * size))
            break;
    }


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
void generateLifeBoard(int numOrgs, int size, char board[][size])
{
    // sets every cell to be a dead cell to begin, we'll fill in living ones later.
    // (removes the conditional required for doing this in opposite order)
    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
                board[row][col] = DEAD;

    // generates our "alive" cells randomized in location
    for (int i = 0; i < numOrgs; ++i)
    {
        // a random row and column
        int row = rand() % size;
        int col = rand() % size;

        // this conditional guarantees that the number of organisms at the start are
        // exactly as many as the user wants

        // if the spot is occupied already, we subtract from i so that it remains at the
        // same value for the next iteration
        if (board[row][col] == ALIVE)
            --i;
        else
            board[row][col] = ALIVE;
    }
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
    if (board[rowN][colW] == ALIVE) ++aliveNeighbors;
    // N
    if (board[rowN][col] == ALIVE) ++aliveNeighbors;
    // NE
    if (board[rowN][colE] == ALIVE) ++aliveNeighbors;
    // E
    if (board[row][colE] == ALIVE) ++aliveNeighbors;
    // SE
    if (board[rowS][colE] == ALIVE) ++aliveNeighbors;
    // S
    if (board[rowS][col] == ALIVE) ++aliveNeighbors;
    // SW
    if (board[rowS][colW] == ALIVE) ++aliveNeighbors;
    // W
    if (board[row][colW] == ALIVE) ++aliveNeighbors;

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
    // creates the variables we need
    char numAliveNeighbors, nextGeneration[size][size];
    int row, col;

    // goes through every cell and determines its next fate
    for (row = 0; row < size; ++row)
        for (col = 0; col < size; ++col)
        {
            numAliveNeighbors = getNumAliveNeighbors(row, col, size, curGeneration);
            switch (curGeneration[row][col])
            {
                case ALIVE:
                    //                                too many or too few live neighbors        ? die  : live
                    nextGeneration[row][col] = (numAliveNeighbors < 2 || numAliveNeighbors > 3) ? DEAD : ALIVE;
                    break;
                case DEAD:
                    //                           three live neighbors or probability fits    ? life  : dead
                    nextGeneration[row][col] = (numAliveNeighbors == 3 || rand() % 100 <= 1) ? ALIVE : DEAD;
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
/// Description: Prints our board to cursor-controlled standard out.
///
/// @param size  The size of each row in the ``board''.
/// @param board  The life board.
/// @param genNum  The current generation we are on.
///
void printBoard(int genNum, int size, char board[][size])
{
    // indexes start at 1, not 0
    for (int row = 0; row < size; ++row)
    {
        // sets our cursor to the correct row and column 1
        // only have to set it for every row (put moves cursor too)
        set_cur_pos(row + 1, 1);
        for (int col = 0; col < size; ++col)
        {
            // puts our character to the window (which conveniently moves the
            // cursor to the next position as well)
            put(board[row][col]);
        }
    }

    // sets our cursor position (just a test, prolly won't work)
    set_cur_pos(size, 1);
    // we can just print out the generation number (we don't need to ``put'' it
    // regular printf works just fine
    printf("\ngeneration: %d\n", genNum);
}


///
/// Function: main
///
/// Description: The main driver for an implementation of Conway's Game of Life.
///
/// @param argc  The number of arguments the user passed in
/// @param argv  The array of argument strings
///
/// @return: An integer; EXIT_SUCCESS for success, anything else otherwise.
///
int main(int argc, char **argv)
{
    // if someone gives too many arguments, we need to show them
    // correct usage
    if (argc > 2)
    {
        // we use %s and argv[0] so we can accurately show the usage (argv[0] is the
        // first item users entered which launched our program.
        printf("Invalid number of arguments.\nUsage: %s [board size]\n", argv[0]);
        // we failed to run so we need to return taht
        return EXIT_FAILURE;
    }

    // the size of our board (determined on the next one)
    int size;

    // gathers the size of our board based on what the program starts with
    if (argc == 2)
        size = strtol(argv[1], NULL, 10);
    else
        size = 20;

    // our generation tracker
    int gens = 0;

    // our life ``board''
    char board[size][size];

    // the number of organisms the user wants -- SHORT
    int numOrgs = startLife(size);

    // randomizes the random number seed
    srand(time(NULL));

    // generates our life board
    generateLifeBoard(numOrgs, size, board);

    // clear the screen just before we begin printing our game
    clear();

    // runs our game
    // we want to run the loop while gens is equal to 0, so...
    // do{}while() to the rescue
    // paired with pre-increment it'll go forever!
    do
    {
        // prints our new board
        printBoard(gens, size, board);

        // sleeps immediately after printing the board
        usleep(SLEEP_TIME);

        // computes our next generation in life
        computeNextGeneration(size, board);
    } while(++gens);


    return EXIT_SUCCESS;
}

