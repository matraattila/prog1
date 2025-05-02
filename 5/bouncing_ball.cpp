#include <cstdlib> // For rand and srand
#include <cstring> // For memset
#include <ctime>   // For time
#include <iostream>
#include <unistd.h> // For usleep

#define SCREEN_WIDTH 45
#define SCREEN_HEIGHT 20

using namespace std;

// Ball structure to represent the ball's position and velocity
struct Ball {
  float x, y;   // Position
  float vx, vy; // Velocity

  Ball(float x, float y, float vx, float vy) : x(x), y(y), vx(vx), vy(vy) {}
};

// Global variables
char screen[SCREEN_HEIGHT][SCREEN_WIDTH];

// Clears the screen buffer
void clearScreen() {
  for (int row = 0; row < SCREEN_HEIGHT; row++) {
    memset(screen[row], ' ', SCREEN_WIDTH);
  }
}

// Draws the ball on the screen
void drawBall(const Ball &ball) {
  int ballX = ball.x;
  int ballY = ball.y;

  if (ballX >= 0 && ballX < SCREEN_HEIGHT && ballY >= 0 &&
      ballY < SCREEN_WIDTH) {
    screen[ballX][ballY] = 'O';
  }
}

// Prints the screen buffer to the console
void renderScreen() {
  // Clear the terminal screen
  cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen

  for (int row = 0; row < SCREEN_HEIGHT; row++) {
    for (int col = 0; col < SCREEN_WIDTH; col++) {
      cout << screen[row][col];
    }
    cout << endl;
  }
}

// Updates the ball's position and handles collisions
void updateBall(Ball &ball) {
  ball.x += ball.vx;
  ball.y += ball.vy;

  // Handle wall collisions
  if (ball.y <= 0 || ball.y >= SCREEN_WIDTH - 1) {
    ball.vy = -ball.vy;
  }
  if (ball.x <= 0 || ball.x >= SCREEN_HEIGHT - 1) {
    ball.vx = -ball.vx;
  }
}

int main() {
  srand(static_cast<unsigned int>(time(0)));

  // Initialize the ball
  Ball ball(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, -0.2f, 0.2f);

  while (true) {
    clearScreen();
    updateBall(ball);
    drawBall(ball);
    renderScreen();
    usleep(10000); // Control game speed (70ms)
  }

  return 0;
}
