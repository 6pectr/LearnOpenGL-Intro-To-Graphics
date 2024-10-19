#include <iostream>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>  // for read()

using namespace std::chrono;

// Non-blocking keypress function
char getNonBlockingKeyPress() {
    struct termios oldt, newt;
    char ch;
    int oldf;

    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set non-blocking mode for input
    ch = getchar();

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

int main() {
    // player
    class Player {
    public:
        int player_x = 1;
        int player_y = 1;
    };

    int speed = 1;
    Player character;

    char grid[3][3] = {
        {'#', '#', '#'},
        {'#', '#', '#'},
        {'#', '#', '#'}
    };

    auto start = steady_clock::now();

    while (true) {
        auto end = steady_clock::now();
        auto elapsed = duration_cast<milliseconds>(end - start);

        // Reset previous position
        grid[character.player_y][character.player_x] = '#';

        // Capture non-blocking key press
        if (read(STDIN_FILENO, &character, sizeof(character)) == 1) {
            char key = getNonBlockingKeyPress();

            // Move player based on key press
            if (key == 'W' || key == 'w') {
                if (character.player_y > 0) character.player_y -= speed;
            }
            else if (key == 'S' || key == 's') {
                if (character.player_y < 2) character.player_y += speed;
            }
            else if (key == 'A' || key == 'a') {
                if (character.player_x > 0) character.player_x -= speed;
            }
            else if (key == 'D' || key == 'd') {
                if (character.player_x < 2) character.player_x += speed;
            }
        }

        // Update player position
        grid[character.player_y][character.player_x] = '0';

        // Print the grid
        system("clear"); // Clears the screen for continuous rendering (for Linux/macOS)
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << grid[i][j];
            }
            std::cout << std::endl;
        }

        // Sleep to control rendering speed
        std::this_thread::sleep_for(milliseconds(100));
    }

    return 0;
}
