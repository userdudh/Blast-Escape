#include "raylib.h"

void TextoMenu(const char *opcoes[], int quantidadeOpcoes, Font fonte, int larguraTela, int alturaTela, int *selecionada) {
    Vector2 pontoMouse = GetMousePosition();

    for (int i = 0; i < quantidadeOpcoes; i++) {
        Vector2 tamanhoTexto = MeasureTextEx(fonte, opcoes[i], 40, 2);
        Vector2 posicaoTexto = (Vector2){(larguraTela - tamanhoTexto.x) / 2, 330 + i * 60};
        Rectangle areaTexto = {posicaoTexto.x, posicaoTexto.y, tamanhoTexto.x, tamanhoTexto.y};

        if (CheckCollisionPointRec(pontoMouse, areaTexto)) {
            *selecionada = i;
            Vector2 posicaoTriangulo = {posicaoTexto.x - 30, posicaoTexto.y + tamanhoTexto.y / 2};
            DrawTriangle(
                (Vector2){posicaoTriangulo.x + 10, posicaoTriangulo.y - 10},
                (Vector2){posicaoTriangulo.x + 10, posicaoTriangulo.y + 10},
                (Vector2){posicaoTriangulo.x + 20, posicaoTriangulo.y},
                WHITE
            );
        }

        DrawTextEx(fonte, opcoes[i], posicaoTexto, 40, 2, WHITE);
    }
}

void menu() {

    Texture2D robo1 = LoadTexture("./img/robo1.png");
    Texture2D robo2 = LoadTexture("./img/robo2.png");
    Texture2D robo3 = LoadTexture("./img/robo3.png");
    Texture2D fundo = LoadTexture("./img/fundo.png");
    Texture2D nuvem = LoadTexture("./img/nuvem.png");
    Texture2D titulo = LoadTexture("./img/titulo.png");

    Texture2D roboAtual = robo1;
    int roboFrame = 0;
    float frameTime = 0.5f;
    float roboTimer = 0.0f;
    float nuvemX = 0.0f, nuvemSpeed = 20.0f;

    Font fontePadrao = GetFontDefault();
    const char *opcoesMenu[] = {"New Game", "Load Game", "Options", "Exit"};
    int quantidadeOpcoes = sizeof(opcoesMenu) / sizeof(opcoesMenu[0]);
    int selecionada = -1;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        nuvemX -= nuvemSpeed * deltaTime;
        if (nuvemX <= -nuvem.width) nuvemX += nuvem.width;

        roboTimer += deltaTime;
        if (roboTimer >= frameTime) {
            roboFrame = (roboFrame + 1) % 3;
            roboAtual = (roboFrame == 0) ? robo1 : (roboFrame == 1) ? robo2 : robo3;
            roboTimer = 0.0f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(fundo, 0, 0, WHITE);
        DrawTexture(nuvem, (int)nuvemX, -15, WHITE);
        DrawTexture(nuvem, (int)(nuvemX + nuvem.width), -15, WHITE);
        DrawTexture(roboAtual, 100, 400, WHITE);
        DrawTexture(titulo, (1280 - titulo.width) / 2, 90, WHITE);

        TextoMenu(opcoesMenu, quantidadeOpcoes, fontePadrao, 1280, 620, &selecionada);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selecionada != -1) {
            if (selecionada == 0) { }
            if (selecionada == 1) { }
            if (selecionada == 2) { }
            if (selecionada == 3) {
                CloseWindow();
                return;
            }
        }

        EndDrawing();
    }

    UnloadTexture(robo1);
    UnloadTexture(robo2);
    UnloadTexture(robo3);
    UnloadTexture(fundo);
    UnloadTexture(nuvem);
    UnloadTexture(titulo);
}

int main(void) {
    InitWindow(1280, 620, "Blast Escape");
    menu();
    CloseWindow();
    return 0;
}
