/*
 * Programmeringsteknik med C och Matlab
 * Fall 21
 * Assignment 3

 * File:         ou3.c
 * Description:  A simple implementation of Conway's Game of Life. Lets the user
 *               choose initial configuration. Then let them step or exit.
 *               Prints the game field in each step.
 * Author:       Gabriel Morberg
 * CS username:  c21gmg@cs.umu.se
 * Date:         2021-10-19
 * Limitations:  No validation of input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'

/* Declaration of data structure */
typedef struct{
    char current;
    char next;
} cell;

/* Declaration of functions */
char userChoices(void);
void initField(const int rows, const int cols, cell field[rows][cols]);
void printCellField(const int rows, const int cols, cell field[rows][cols]);
void cellSurviveCheck (const int rows, const int cols, cell field[rows][cols]);
int findAdjacentAliveCells(const int rows, const int cols,
                           cell field[rows][cols], int rowPos, int colPos);
void updateField (const int rows, const int cols, cell field[rows][cols]);
void clearField(const int rows, const int cols, cell field[rows][cols]);
void loadGlider(const int rows, const int cols, cell field[rows][cols]);
void loadSemaphore(const int rows, const int cols, cell field[rows][cols]);
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
void loadCustom(const int rows, const int cols, cell field[rows][cols]);
char getStartStateChoice(void);


/* Function:    main
 * Description: Start and run simulations, interact with the user.
 *              Lets the user choose initial structure and whether to step
 *              or exit. Writes information to the user, and the game field
 *              in each step.
 */

int main(void) {


    const int cols = 20;
    const int rows = 20;
    cell field[rows][cols];

    srand(time (NULL));
    initField(rows,cols,field);

    do {

        printCellField(rows,cols,field);
        cellSurviveCheck(rows,cols,field);
        updateField(rows,cols,field);

    } while (userChoices() == '\n');

    return 0;
}




/* Function:    initField
 * Description: Loads a structure that the user selects
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void initField(const int rows, const int cols, cell field[rows][cols]) {
    char choice;

    clearField(rows,cols,field);

    choice=getStartStateChoice();

    switch (choice) {
        case 'g':
        case 'G':
            loadGlider(rows, cols, field);
            break;
        case 's':
        case 'S':
            loadSemaphore(rows, cols, field);
            break;
        case 'r':
        case 'R':
            loadRandom(rows, cols, field);
            break;
        case 'c':
        case 'C':
        default:
            loadCustom(rows, cols, field);
            break;
    }
}

/* Function:    getStartStateChoice
 * Description: Lets the user choose starting state
 * Input:
 * Output:      The users choice. Should be one of the letters G,S,R or C.
 */
char getStartStateChoice(void) {
    int ch;

    printf("Select field spec to load ([G]lider, [S]emaphore, [R]andom ");
    printf("or [C]ustom): ");

    ch = getchar();

    /* Ignore following newline */
    if (ch != '\n') {
        getchar();
    }
    return ch;
}

/* Function:    clearField
 * Description: Initialize all the cells in the field to dead
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */
void clearField(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].current = DEAD;
        }
    }
}

/* Function:    loadGlider
 * Description: Inserts a glider into the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void loadGlider(const int rows, const int cols, cell field[rows][cols]) {

    field[0][1].current = ALIVE;
    field[1][2].current = ALIVE;
    field[2][0].current = ALIVE;
    field[2][1].current = ALIVE;
    field[2][2].current = ALIVE;
}


/* Function:    loadSemaphore
 * Description: Inserts a semaphore into the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */

void loadSemaphore(const int rows, const int cols, cell field[rows][cols]) {

    field[8][1].current = ALIVE;
    field[8][2].current = ALIVE;
    field[8][3].current = ALIVE;
}


/* Function:    loadRandom
 * Description: Inserts a random structure into the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated. There is a 50 % chance that a cell
 *              is alive.
 */

void loadRandom(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {

            if ((rand() % 2) == 1) {
                field[r][c].current = ALIVE;
            }
            else {
                field[r][c].current = DEAD;
            }
        }
    }
}


/* Function:    loadCustom
 * Description: Lets the user specify a structure that then is inserted into
 *              the field.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      The field array is updated.
 */
void loadCustom(const int rows, const int cols, cell field[rows][cols]) {
    int r, c;

    printf("Give custom format string: ");
    do {
        scanf("%d,%d", &r, &c);
        field[r][c].current = ALIVE;
    } while (getchar() != '\n');
}


/* Function:    userChoice
 * Description: Presents the user choices and let them choose
 * Output:      a char representing choice.
 */
char userChoices(void) {

    printf("\nSelect one of the following options: \n");
    printf("        (enter) Step\n");
    printf("        (any)   Exit\n");

    return getchar();

}

/* Function:    printCellField
 * Description: Function is used for the visual representation of the field
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      Prints the current cells state in the field
 */
void printCellField(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        /* This if statement will line the rows up correctly */
        if (r>=1) {
            printf("\n");
        }
        for (int c = 0 ; c < cols ; c++) {
            printf("%c ",field[r][c].current);
        }
    }
}
/* Function:    cellSurviveCheck
 * Description: Goes through all cells and checks the conditions
 *              whether the  cell should survive or die in the next step
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 * Output:      sets the current cell either dead or alive for next step.
 */
void cellSurviveCheck (const int rows, const int cols, cell field[rows][cols]) {

    int adjAliveCells = 0;

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {

            adjAliveCells = findAdjacentAliveCells(rows,cols,field,r,c);

            if (field[r][c].current == DEAD && adjAliveCells == 3) {

                field[r][c].next = ALIVE;
            }
            else if (field[r][c].current == ALIVE &&
                    (adjAliveCells < 2 || adjAliveCells > 3)){

                field[r][c].next = DEAD;
            }
            else {
                field[r][c].next = field[r][c].current;
            }
      }
    }
}


/* Function:    findAdjacentAliveCells
 * Description: Checks every cell around the cell being checked, if they're alive.
 * Input:       rows - the number of rows in the field
 *              cols - the number of columns in the field
 *              field - the field array
 *              rowPos - the row index of the cell that is being checked
 *              colPos - the column index of the cell that is being checked
 * Output:      An integer containing amount of alive cells
 */
int findAdjacentAliveCells (const int rows, const int cols, cell field[rows][cols],
                            int rowPos, int colPos) {

   int adjAliveCells = 0;

    for (int i = rowPos - 1; i <= rowPos + 1; i++) {
        for (int j = colPos - 1; j <= colPos + 1; j++) {

            /*This if statement will catch all the positions outside the field
             *  Which SHOULD not be checked since they're not defined.
             */
            if ( i == 20 || i == -1 || j == 20 || j == -1) {

            }
            /* rowPos != r || colPos !=c makes sure it doesnt count itself */
            else if (field[i][j].current == ALIVE && (rowPos != i || colPos !=j)) {
                adjAliveCells++;
            }
        }
    }
    return adjAliveCells;
 }




 /* Function:    updateField
  * Description: this will update the previous step to the next step
  * Input:       rows - the number of rows in the field
  *              cols - the number of columns in the field
  *              field - the field array
  * Output:      sets field.current to field.next
  */
void updateField (const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].current = field[r][c].next;
        }
    }
}
