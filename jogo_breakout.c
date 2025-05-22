#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <raylib.h>

#define N_BLOCOS 40


const char TITULO[] = "Breakout";
const int  BLOCK_SIZE = 12;
const int  INIT_SIZE = 5;
const int  BLOCKS_HORIZONTAL = 39;
const int  BLOCKS_VERTICAL = 39;
const int  SCREEN_WIDTH = BLOCK_SIZE * BLOCKS_HORIZONTAL;
const int  SCREEN_HEIGHT = BLOCK_SIZE * BLOCKS_VERTICAL;
const int  FPS = 60;
Color  BACKGROUND_COLOR = BLACK;


typedef struct Base {
    Color cor;
    Rectangle rect;
    int meio;
} base_t;


typedef struct Bloco {
    Color cor;
    Rectangle rect;
    uint8_t vitalidade;
} bloco_t;


typedef struct Bola {
    Vector2 pos;
    Vector2 mov;
    Color cor;
    uint8_t raio;
    uint8_t poder;
} bola_t;


int main(void) {
    srand(time(NULL)); 

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITULO);
    SetTargetFPS(FPS);
    HideCursor();

    int steps = 0;
    char pontos[15];

    //Criando Base
    base_t base_jogador = {
        .cor = WHITE, 
        .rect = {
            .x = SCREEN_WIDTH / 2, 
            .y = (SCREEN_HEIGHT / 40) * 38,
            .width = BLOCK_SIZE * 5,
            .height = BLOCK_SIZE / 2
        },
    };


    //Criando blocos
    bloco_t blocos[N_BLOCOS] = {};
    int line = 0;
    int row = 0;
    uint8_t first_pass = 1;

    for (int i = 0; i < N_BLOCOS; i++) {
        blocos[i].rect.x = row  * (BLOCK_SIZE * 3);
        row++;
        blocos[i].rect.y = (line * BLOCK_SIZE) + (BLOCK_SIZE / 2);
        blocos[i].rect.width = BLOCK_SIZE * 3;
        blocos[i].rect.height = BLOCK_SIZE;
        blocos[i].vitalidade = 1;
        if (!(i % 3)) { blocos[i].cor = BLUE; }
        else if (!(i % 2)) {blocos[i].cor = RED; }
        else {blocos[i].cor = GREEN;}
        if (!(i % 13 * BLOCK_SIZE)) {
            if (!(first_pass)) {line++;}
            row = 0;
        }
        first_pass = 0;
    }

    //Criando bola
    bola_t bola = {
        .pos = {.x = SCREEN_WIDTH / 2, .y = (SCREEN_HEIGHT / 39) * 30}, 
        .mov = {.x = -1, .y = -2 }, 
        .raio = 7,
        .cor = GRAY,
    };
    
    sprintf(pontos, "Pontos: %d", 0);

    while (!WindowShouldClose()) {

        steps++;
        base_jogador.rect.x = GetMouseX();
        base_jogador.meio = (base_jogador.rect.x + base_jogador.rect.width) / 2;
        bola.pos.x += bola.mov.x;
        bola.pos.y += bola.mov.y;


        //Mantendo bola na tela
        if (bola.pos.x - bola.raio < 0 || bola.pos.x + bola.raio > SCREEN_WIDTH) {
            bola.mov.x *= -1;
        } else if (bola.pos.y + bola.raio > SCREEN_HEIGHT || bola.pos.y - bola.pos.y < 0) {
            bola.mov.y *= -1;
        }

        if (CheckCollisionCircleRec(bola.pos, bola.raio, base_jogador.rect)) {
            if (bola.pos.y < base_jogador.rect.y) {
                bola.mov.y = abs(bola.mov.y) * -1.05;
            } else {
                bola.mov.y = abs(bola.mov.y) * 1.05;
            }

            if (bola.pos.x < base_jogador.meio) {
                bola.mov.x = abs( 2 * base_jogador.meio / (base_jogador.meio - bola.pos.x)) * -1;
            } else {
                bola.mov.x = abs( 2 * base_jogador.meio / ( bola.pos.x - base_jogador.meio)) * 1;
            }
        }


        for (int i = 0; i < N_BLOCOS; i++) {
            if (CheckCollisionCircleRec(bola.pos, bola.raio, blocos[i].rect)) {
                bola.mov.y *= -1;
            }
        }

        /*
        if (IsKeyPressed(KEY_A)) {
            base_jogador.largura += BLOCK_SIZE;
        } else if ( IsKeyPressed(KEY_D)) {
            base_jogador.largura -= BLOCK_SIZE;
        }
        */


        if (base_jogador.rect.x < 0) {
            base_jogador.rect.x = 0;
        } else if (base_jogador.rect.x + base_jogador.rect.width > SCREEN_WIDTH) {
            base_jogador.rect.x = SCREEN_WIDTH - base_jogador.rect.width;
        }

        BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangleRec(base_jogador.rect, base_jogador.cor);
            DrawText(pontos, BLOCK_SIZE, SCREEN_HEIGHT - (BLOCK_SIZE * 2), 12, YELLOW);
            for (int i = 0; i < N_BLOCOS; i++) {
                DrawRectangleRec(blocos[i].rect, blocos[i].cor);
            }
            DrawCircle(bola.pos.x, bola.pos.y, bola.raio, bola.cor);

        EndDrawing();

    }
    CloseWindow();
    return 0;
}


