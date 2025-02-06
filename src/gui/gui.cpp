#include "gui.h"

void Gui::drawGameOver()
{
    DrawRectangle(settings.screenWidth / 2 - (gameOverWidth / 2),
                  settings.screenHeight / 2 - (gameOverHeight / 2),
                       gameOverWidth, gameOverHeight, gameOverBackgroundColor);
    std::string text = "GAME OVER";
    int textLen = MeasureText(text.c_str(), gameOverFontSize);
    DrawText("GAME OVER",
         settings.screenWidth / 2 - textLen / 2,
         settings.screenHeight / 2 - gameOverFontSize / 2,
              gameOverFontSize, gameOverTextColor);
}

void Gui::drawScore(int score)
{
    std::string text = "SCORE: ";
    text += std::to_string(score);
    int textWidth = MeasureText(text.c_str(), 50);
    DrawText(text.c_str(), settings.screenWidth / 2 - textWidth / 2,10,50,RED);
}
