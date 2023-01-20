// Boids.cpp
// Ethan Kerr

#include "Game.h"

int main() {

    // Window initaliztion
    Game game;

    // Game loop
    while (game.running()) {

        // Update
        game.update();

        // Render
        game.render();

    }

    return 0;
}

