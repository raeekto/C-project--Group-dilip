// TIC-TAC-TOE (friend VS friend)
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char positions[9];
bool gamePause = false;

// Reset board
static void reset_board(void)
{
    int i;
    for (i = 0; i < 9; i++)
    {
        positions[i] = ' ';
    }
    gamePause = false;
}

// Clear previous output
static void clear_screen(void)
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    printf("\033[H\033[J"); // ANSI escape codes for Linux/macOS
#endif
}

// Check if a player has won
static bool check_winner(char person)
{
    int wins[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8}, // columns
        {0, 4, 8},
        {2, 4, 6} // diagonals
    };
    int w;
    for (w = 0; w < 8; w++)
    {
        int a = wins[w][0], b = wins[w][1], c = wins[w][2];
        if (positions[a] == person && positions[b] == person && positions[c] == person)
        {
            return true;
        }
    }
    return false;
}

// Render the board
static void render_board(void)
{
    printf("\n=========================================\n");
    int i;
    for (i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            printf("\n\n");
        printf("%c\t", positions[i]);
    }
    printf("\n\n=========================================\n");
}

// Check if the board is full (draw)
static bool is_draw(void)
{
    int i;
    for (i = 0; i < 9; i++)
    {
        if (positions[i] == ' ')
            return false;
    }
    return true;
}

// Apply move and check game state
bool table(int position, char person)
{
    if (position < 1 || position > 9)
    {
        printf("\nInvalid position. Choose 1-9.\n");
        return false;
    }
    if (positions[position - 1] != ' ')
    {
        printf("\nPosition already taken. Choose another.\n");
        return false;
    }

    positions[position - 1] = person;

    clear_screen();
    render_board();

    if (check_winner(person))
    {
        printf("\nWinner is person %c\n", person);
        gamePause = true;
        return true;
    }

    if (is_draw())
    {
        printf("\nGame is a draw.\n");
        return true;
    }

    return false;
}

int main()
{
    char choice[10];
    bool userChoice;

    do
    {
        reset_board(); // reset board for new match
        bool turnA = true;
        char personA = 'A', personB = 'B';
        int position;
        bool gameOver = false;

        clear_screen();
        render_board();

        while (!gameOver)
        {
            if (turnA)
            {
                printf("\nTurn of person A\nChoose position: ");
                if (scanf("%d", &position) != 1)
                {
                    printf("\nInvalid input. Exiting.\n");
                    return 0;
                }
                gameOver = table(position, personA);
                turnA = false;
            }
            else
            {
                printf("\nTurn of person B\nChoose position: ");
                if (scanf("%d", &position) != 1)
                {
                    printf("\nInvalid input. Exiting.\n");
                    return 0;
                }
                gameOver = table(position, personB);
                turnA = true;
            }
        }

        // Ask to play again
        printf("\nDo you want to play another match? (y/yes to continue): ");
        scanf("%s", choice);
        if (strcmp(choice, "y") == 0 || strcmp(choice, "yes") == 0)
        {
            userChoice = true;
        }
        else
        {
            userChoice = false;
        }

    } while (userChoice);

    return 0;
}
