#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const int screenWidth = 400;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Jogo Da Velha");
    SetTargetFPS(60);

    Rectangle recs[3][3];
    Rectangle btn = {screenWidth / 2 - 70, screenHeight / 2 - 20, 140, 40};
    Color color = ColorAlpha(WHITE, 0.f); // Cor de cada "casa" no jogo, alfa deve ser 0.f para ser transparente

    // Array do grid
    int pos[3][3];

    int player = 1;
    int winner = 0;
    int gameOver = 0;

    // Preenche o vetor pos com 0
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            recs[i][j] = (Rectangle){100 * i + 50.f, 100 * j + 50.f, 100.f, 100.f};
            pos[i][j] = 0;
        }
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Linhas Horizontais
        DrawLine(50, 150, 350, 150, BLACK);
        DrawLine(50, 250, 350, 250, BLACK);

        // Linhas Verticais
        DrawLine(150, 50, 150, 350, BLACK);
        DrawLine(250, 50, 250, 350, BLACK);

        int spacesLeft = 9;

        // Qyal jogador está na vez
        if (!gameOver)
            DrawText(player == 1 ? "JOGADOR X" : "JOGADOR O", screenWidth / 2 - 50, 0, 20, BLACK);

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Desenha um retângulo invisível onde será a área clicavel
                DrawRectangleRec(recs[i][j], color);

                // Desenha as posições com X e O
                if (pos[i][j] != 0)
                    DrawText(pos[i][j] == 1 ? "X" : "O", recs[i][j].x + 10, recs[i][j].y + 10, 80, BLACK);

                // Verifica se tem um vencedor
                if ((pos[i][0] != 0) || (pos[0][j] != 0))
                {
                    if ((pos[i][0] == pos[i][1]) && (pos[i][1] == pos[i][2]))
                        winner = pos[i][0];

                    if ((pos[0][j] == pos[1][j]) && (pos[1][j] == pos[2][j]))
                        winner = pos[0][j];

                    if ((pos[0][0] == pos[1][1]) && (pos[0][0] == pos[2][2]))
                        winner = pos[0][0];

                    if ((pos[0][2] == pos[1][1]) && (pos[0][2] == pos[2][0]))
                        winner = pos[0][2];
                }

                // Mostra o vencedor
                if (winner != 0)
                {
                    DrawText(winner == 1 ? "X VENCEU" : "O VENCEU", screenWidth / 2 - 50, 0, 20, BLACK);
                    gameOver = 1;
                }

                // Se a posição for diferente de 0 então ela não está vazia
                if (pos[i][j] != 0)
                    spacesLeft--;

                // Se todos os espaços estiverem preenchidos e não tiver um vencedor, o jogo empatou
                if (spacesLeft == 0 && winner == 0)
                {
                    DrawText("EMPATE", screenWidth / 2 - 50, 0, 20, BLACK);
                    gameOver = 1;
                }

                // Marca a posição no array com 1 ou 2 dependendo do jogador que está na vez
                if (CheckCollisionPointRec(GetMousePosition(), recs[i][j]))
                {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && pos[i][j] == 0 && !gameOver)
                    {
                        pos[i][j] = player;
                        player = player != 1 ? 1 : 2;
                    }
                }

                // Fim do jogo, reinicia as variáveis
                if (gameOver)
                {
                    DrawRectangleRec(btn, BLACK);
                    DrawText("RESTART", btn.x + 10, btn.y + 10, 25, WHITE);

                    if (CheckCollisionPointRec(GetMousePosition(), btn))
                    {
                        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                        {
                            for (int i = 0; i < 3; i++)
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    pos[i][j] = 0;
                                }
                            }

                            player = 1;
                            winner = 0;
                            gameOver = 0;
                        }
                    }
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}