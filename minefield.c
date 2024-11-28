#include <raylib.h>

void ExibirMenu(const char *opcoes[], int quantidadeOpcoes, Font fonte, int larguraTela, int alturaTela) {
    Vector2 pontoMouse;
    int selecionada = -1;

    while (!WindowShouldClose()) {
        pontoMouse = GetMousePosition();
        selecionada = -1;

        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        // Desenhar as opções do menu
        for (int i = 0; i < quantidadeOpcoes; i++) {
            Vector2 tamanhoTexto = MeasureTextEx(fonte, opcoes[i], 40, 2);
            Vector2 posicaoTexto = (Vector2){(larguraTela - tamanhoTexto.x) / 2, 300 + i * 60};
            Rectangle areaTexto = {posicaoTexto.x, posicaoTexto.y, tamanhoTexto.x, tamanhoTexto.y};

            // Detectar hover
            if (CheckCollisionPointRec(pontoMouse, areaTexto)) {
                selecionada = i;

                // Desenhar o triângulo ao lado do botão
                Vector2 posicaoTriangulo = {posicaoTexto.x + tamanhoTexto.x + 10, posicaoTexto.y + tamanhoTexto.y / 2};
                DrawTriangle(
                    (Vector2){posicaoTriangulo.x, posicaoTriangulo.y - 10}, // Ponto superior
                    (Vector2){posicaoTriangulo.x + 10, posicaoTriangulo.y}, // Ponto direito
                    (Vector2){posicaoTriangulo.x, posicaoTriangulo.y + 10}, // Ponto inferior
                    BLACK // Triângulo preto
                );
            }

            // Desenhar texto
            DrawTextEx(fonte, opcoes[i], posicaoTexto, 40, 2, BLACK);
        }

        // Seleção ao clicar
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selecionada != -1) {
            switch (selecionada) {
                case 0:
                    // Iniciar jogo
                    return;
                case 1:
                    // Opções
                    break;
                case 2:
                    // Sair
                    CloseWindow();
                    return;
            }
        }

        EndDrawing();
    }
}

void menu() {
    // Carregar texturas
    Texture2D robo1 = LoadTexture("./img/robo1.png");
    Texture2D robo2 = LoadTexture("./img/robo2.png");
    Texture2D robo3 = LoadTexture("./img/robo3.png");
    Texture2D fundo = LoadTexture("./img/fundo.png");
    Texture2D nuvem = LoadTexture("./img/nuvem.png");
    Texture2D titulo = LoadTexture("./img/titulo.png");

    // Variáveis de animação do robô
    Texture2D roboAtual = robo1; // Começa com a primeira textura do robô
    int roboFrame = 0;           // Índice do frame do robô
    float frameTime = 0.5f;      // Tempo entre as trocas de frames
    float roboTimer = 0.0f;      // Temporizador para o ciclo de animação do robô

    // Variáveis para a nuvem
    float nuvemX = 0.0f;         // Posição inicial da nuvem
    float nuvemSpeed = 20.0f;   // Velocidade da nuvem (pixels por segundo)

    Font fontePadrao = GetFontDefault();

    const char *opcoesMenu[] = {"Iniciar", "Opções", "Sair"};
    int quantidadeOpcoes = sizeof(opcoesMenu) / sizeof(opcoesMenu[0]);

    // Loop do menu
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime(); // Tempo decorrido por quadro

        // Atualização da posição das nuvens
        nuvemX -= nuvemSpeed * deltaTime;
        if (nuvemX <= -nuvem.width) {
            nuvemX += nuvem.width; // Reposiciona as nuvens para criar o efeito contínuo
        }

        // Atualização da animação do robô
        roboTimer += deltaTime;
        if (roboTimer >= frameTime) {
            roboFrame = (roboFrame + 1) % 3; // Alterna entre 0, 1 e 2
            if (roboFrame == 0) roboAtual = robo1;
            else if (roboFrame == 1) roboAtual = robo2;
            else roboAtual = robo3;

            roboTimer = 0.0f; // Reinicia o temporizador
        }

        // Desenho
        BeginDrawing();
        ClearBackground(WHITE);

        // Ordem de desenho: fundo -> nuvens -> robô -> texto
        DrawTexture(fundo, 0, 0, WHITE);                      // Fundo fixo
        DrawTexture(nuvem, (int)nuvemX, -15, WHITE);
        DrawTexture(nuvem, (int)(nuvemX + nuvem.width), -15, WHITE);
        DrawTexture(roboAtual, 100, 400, WHITE);
        DrawTexture(titulo, ((1280 - titulo.width)/2),90, WHITE);

        // Chamar a função do menu
        ExibirMenu(opcoesMenu, quantidadeOpcoes, fontePadrao, 1280, 620);

        EndDrawing();
    }

    // Descarregar texturas
    UnloadTexture(robo1);
    UnloadTexture(robo2);
    UnloadTexture(robo3);
    UnloadTexture(fundo);
    UnloadTexture(nuvem);
    UnloadTexture(titulo);
}

int main(void) {
    // Inicializar janela
    InitWindow(1280, 620, "Joguinho");

    // Chamar o menu
    menu();

    // Fechar janela
    CloseWindow();
    return 0;
}
