
#include <iostream>
#include <limits>

using namespace std;

char current_marker;
int current_player;

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

void drawboard()
{
    cout << "\n";
    cout << "\t\t" << board[0][0] << " | "
         << board[0][1] << " | " << board[0][2] << "\n";
    cout << "\t\t---------\n";
    cout << "\t\t" << board[1][0] << " | "
         << board[1][1] << " | " << board[1][2] << "\n";
    cout << "\t\t---------\n";
    cout << "\t\t" << board[2][0] << " | "
         << board[2][1] << " | " << board[2][2] << "\n\n";
}

bool placemarker(int slot)
{
    if (slot < 1 || slot > 9)
    {
        cout << "Invalid slot. Choose 1-9.\n";
        return false;
    }

    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] == 'x' || board[row][col] == 'o')
    {
        cout << "That slot is already occupied!\n";
        return false;
    }

    board[row][col] = current_marker;
    return true;
}

int winner()
{
    for (int i = 0; i < 3; i++)
    {
        // Check rows
        if ((board[i][0] == 'x' || board[i][0] == 'o') &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
        {
            return current_player;
        }

        // Check columns
        if ((board[0][i] == 'x' || board[0][i] == 'o') &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
        {
            return current_player;
        }
    }

    // Check diagonal from top-left to bottom-right
    if ((board[0][0] == 'x' || board[0][0] == 'o') &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        return current_player;
    }

    // Check diagonal from top-right to bottom-left
    if ((board[0][2] == 'x' || board[0][2] == 'o') &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        return current_player;
    }

    return 0;
}

void swap()
{
    if (current_marker == 'x')
        current_marker = 'o';
    else
        current_marker = 'x';

    if (current_player == 1)
        current_player = 2;
    else
        current_player = 1;
}

void game()
{
    char marker_p1;
    int slot;
    int winning_player;

    cout << "Player 1, choose your marker (x or o): ";

    while (true)
    {
        if (!(cin >> marker_p1))
            return;

        if (marker_p1 == 'x' || marker_p1 == 'o')
            break;

        cout << "Please choose x or o: ";
    }

    current_player = 1;
    current_marker = marker_p1;

    drawboard();

    for (int turn = 0; turn < 9;)
    {
        cout << "Player " << current_player
             << " (" << current_marker << "), choose a slot (1-9): ";

        if (!(cin >> slot))
        {
            if (cin.eof())
                return;

            cout << "Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (!placemarker(slot))
            continue;

        turn++;

        drawboard();

        winning_player = winner();

        if (winning_player != 0)
        {
            cout << "Congratulations! Player "
                 << winning_player << " wins!\n";
            return;
        }

        if (turn == 9)
        {
            cout << "It's a draw!\n";
            return;
        }

        swap();
    }
}

int main()
{
    game();
    return 0;
}
