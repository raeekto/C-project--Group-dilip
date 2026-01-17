// TIC-TAC-TOE(player VS computer or friend VS friend)

// Headers declaration
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// Functions declaration
static void r1ender_board(void);           // to render
static bool check_winner(char person);     // to check winner
static bool is_draw(void);                 // to check draw
bool make_move(int position, char person); // to moves
void play_computer(void);                  // to play with computer
void play_friend(void);                    // to play with friend

// Table struct to hold board positions
typedef struct
{
    char cells[9];
} Table;

Table board;

// Reset board
static void reset_board(void)
{
    for (int i = 0; i < 9; i++)
    {
        board.cells[i] = ' ';
    }
}

// Clear screen
static void clear_screen(void)
{
#ifdef _WIN32
    system("cls");
#endif
}

// for loading style (At starting and ending)
void loadingStyle(int miliSec, char heading[])
{
    printf("\n");
    for (int i = 0; i < strlen(heading); i++)
    {
        printf("%c", heading[i]);
        Beep(1000, 00);
        Sleep(miliSec);
    }
    for (int i = 0; i < 7; i++)
    {
        printf(".");
        Beep(1000, 500);
        Sleep(miliSec);
    }
    printf("\n\n");
}
// main body part
int main()
{
    srand(time(NULL));
    int mode;
    char choice[10];
    bool userChoice;

    do
    {
        printf("\n\t\tWELCOME\n\t\tLoading.");
        loadingStyle(30, "Enjoy With Tic-Tac-Toe");
        printf("\n\n");
        printf("\nChoose mode:\n1. Play with Friend\n2. Play with Computer\nEnter choice: ");
        scanf("%d", &mode);

        if (mode == 1)
        {
            play_friend();
        }
        else if (mode == 2)
        {
            play_computer();
        }
        else
        {
            printf("\nInvalid choice.\n");
            continue;
        }

        printf("\nDo you want to play another match? (y/yes to continue): ");
        scanf("%s", choice);

        userChoice = (strcmp(choice, "y") == 0 || strcmp(choice, "yes") == 0);

        if (!userChoice)
        {
            // printf("\n\n\t\tEnding game ");
            loadingStyle(100, "Ending game");
        }
        else
        {
            // printf("\n\n\t\tstarting new game ");
            loadingStyle(100, "Starting new game");
        }

    } while (userChoice);

    return 0;
}

// Rendering board
static void render_board(void)
{
    printf("\n=========== TIC TAC TOE ===========\n\n");
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i % 2 == 0 && j == 0)
            {
                printf("\t-------------------");
            }
            else
            {
                if (i % 2 != 0)
                {
                    int cellIndex = (i / 2) * 3 + j;
                    char symbol = board.cells[cellIndex] == ' ' ? '1' + cellIndex : board.cells[cellIndex];
                    if (j == 0)
                        (j == 2) ? printf("\t|  %c  |", symbol) : printf("\t|  %c  ", symbol);
                    else
                        (j == 2) ? printf("|  %c  |", symbol) : printf("|  %c  ", symbol);
                }
            }
        }
        printf("\n");
    }
    printf("\n===================================\n");
}

// Check winner
static bool check_winner(char person)
{
    int wins[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}, // rows
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8}, // cols
        {0, 4, 8},
        {2, 4, 6} // diagonals
    };
    for (int w = 0; w < 8; w++)
    {
        int a = wins[w][0], b = wins[w][1], c = wins[w][2];
        if (board.cells[a] == person && board.cells[b] == person && board.cells[c] == person)
        {
            return true;
        }
    }
    return false;
}

// Check draw
static bool is_draw(void)
{
    for (int i = 0; i < 9; i++)
    {
        if (board.cells[i] == ' ')
            return false;
    }
    return true;
}

// Apply move
bool make_move(int position, char person)
{
    if (position < 1 || position > 9)
    {
        Beep(2000, 600);
        printf("\nInvalid position. Choose 1-9.\n");
        return false;
    }
    if (board.cells[position - 1] != ' ')
    {
        Beep(2000, 600);
        printf("\nPosition already taken. Choose another.\n");
        return false;
    }

    board.cells[position - 1] = person;

    clear_screen(); // clearing previous output
    render_board(); // rendering again

    if (check_winner(person))
    {
        printf("\n\t Player %c!  ", person);
        loadingStyle(100, "Wins this game");
        return true;
    }
    if (is_draw())
    {
        loadingStyle(100, "Game is draw");
        return true;
    }
    return false;
}

// Friend vs Friend mode
void play_friend(void)
{
    reset_board();
    bool turnX = true;
    char player1 = 'X', player2 = 'O';
    int position;
    bool gameOver = false;

    clear_screen();
    render_board();

    while (!gameOver)
    {
        printf("\tPlay with friend\n");
        if (turnX)
        {
            do
            {
                printf("\nTurn of Player 1 (X)\nChoose position (1-9): ");
                scanf("%d", &position);
                Beep(1000, 100);
            } while (!make_move(position, player1) && board.cells[position - 1] != player1);
            gameOver = check_winner(player1) || is_draw();
            turnX = false;
        }
        else
        {
            do
            {
                printf("\nTurn of Player 2 (O)\nChoose position (1-9): ");
                scanf("%d", &position);
                Beep(1000, 100);
            } while (!make_move(position, player2) && board.cells[position - 1] != player2);
            gameOver = check_winner(player2) || is_draw();
            turnX = true;
        }
    }
}

// Computer move (random valid)
int computer_move(void)
{
    int pos;
    do
    {
        pos = rand() % 9 + 1;
    } while (board.cells[pos - 1] != ' ');
    return pos;
}

// Player vs Computer mode
void play_computer(void)
{
    reset_board();
    bool playerTurn = true;
    char player = 'X', computer = 'O';
    int position;
    bool gameOver = false;

    clear_screen(); // clearing previous screen
    render_board(); // rendering

    while (!gameOver)
    {
        printf("\tPlay with computer\n");
        if (playerTurn)
        {
            do
            {
                printf("\nYour turn (X)\nChoose position (1-9): ");
                scanf("%d", &position);
                Beep(1000, 100);
            } while (!make_move(position, player) && board.cells[position - 1] != player);
            gameOver = check_winner(player) || is_draw();
            playerTurn = false;
        }
        else
        {
            printf("\nComputer's turn (O)...\n");
            Sleep(1500);
            do
            {
                position = computer_move();
            } while (!make_move(position, computer) && board.cells[position - 1] != computer);
            gameOver = check_winner(computer) || is_draw();
            playerTurn = true;
        }
    }
}
