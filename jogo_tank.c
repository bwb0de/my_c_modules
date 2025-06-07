#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "geometria.h"
#include "gamming.h"


#define TITULO "Tank"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define FPS 60
#define BACKGROUND_COLOR BLACK
#define TOTAL_BALAS 10
#define VELOCIDADE_BALAS 5

typedef struct Bala {
    Vector2 pos;
    Vector2 v_mov;
    uint8_t raio;
    uint8_t dano;
    Color cor;
} bala_t;

typedef struct Tanque {
    int16_t direcao;
    uint8_t v_rotacao;
    uint8_t v_mov;
    Rectangle corpo;
    Vector2 origem;
    bala_t balas[TOTAL_BALAS];
    uint8_t balas_ativas;
} tanque_t;

typedef struct PilhaIndices {
    uint8_t array_idx[30];
    uint8_t numero_elementos;
} pilha_in_stack_t;


void inserir_na_pilha(pilha_in_stack_t *p, uint8_t idx) {
    if (p->numero_elementos < 30) {
        uint8_t i = p->numero_elementos;
        p->array_idx[i] = idx;
        p->numero_elementos++;
    }
}

int8_t retirar_da_pilha(pilha_in_stack_t *p) {
    if (p->numero_elementos == 0) {
        return -1;
    }
    int8_t elemento = p->array_idx[p->numero_elementos];
    p->numero_elementos--;
    return elemento;

}

void mover_tanque(game_status_t *g, tanque_t *t) {
    if (IsKeyDown(KEY_RIGHT)) {
        t->direcao += 2;
        if (t->direcao > 359) {t->direcao = 0;}
        zerar_steps(g);
    }
    else if (IsKeyDown(KEY_LEFT)) {
        t->direcao -= 2;
        if (t->direcao < 0) {t->direcao = 359;}
        zerar_steps(g);
    }

    if (IsKeyDown(KEY_UP)) {
        t->corpo.x += cosf(t->direcao*DEG2RAD) * t->v_mov;
        t->corpo.y += sinf(t->direcao*DEG2RAD) * t->v_mov;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        t->corpo.x -= (cosf(t->direcao*DEG2RAD) / 2) * t->v_mov;
        t->corpo.y -= (sinf(t->direcao*DEG2RAD) / 2) * t->v_mov;
    }

    if (IsKeyPressed(KEY_SPACE)) {
        if (t->balas_ativas < TOTAL_BALAS) {
            uint8_t i = t->balas_ativas;
            t->balas[i].pos.x = t->corpo.x;
            t->balas[i].pos.y = t->corpo.y;
            t->balas[i].v_mov.x = cosf(t->direcao*DEG2RAD) * VELOCIDADE_BALAS;
            t->balas[i].v_mov.y = sinf(t->direcao*DEG2RAD) * VELOCIDADE_BALAS;
            t->balas_ativas++;
        }
    }

    t->origem.x = t->corpo.width / 2;
    t->origem.y = t->corpo.height / 2;
}


void mover_balas_tanque(tanque_t *t) {

    pilha_in_stack_t p = {};

    for (uint8_t i = 0; i < t->balas_ativas; i++) {
        t->balas[i].pos.x += t->balas[i].v_mov.x;
        t->balas[i].pos.y += t->balas[i].v_mov.y;
        if (t->balas[i].pos.x > SCREEN_WIDTH || t->balas[i].pos.x < 0 || t->balas[i].pos.y > SCREEN_HEIGHT || t->balas[i].pos.y < 0) {
            inserir_na_pilha(&p, i);
        }
    }

    int8_t idx_retirado = 0;
    uint8_t decrementar_balas_ativas = 0;

    if (p.numero_elementos) {
        idx_retirado = retirar_da_pilha(&p);
        decrementar_balas_ativas++;
        if (idx_retirado < t->balas_ativas) {
            for (uint8_t i = idx_retirado; i < t->balas_ativas; i++) {
                t->balas[i] = t->balas[i+1];
            }
        }
    }

    t->balas_ativas -= decrementar_balas_ativas;
}



int main() {
    game_status_t g = {.vidas=3, .vitalidade_maxima=100, .vitalidade=100};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITULO);
    SetTargetFPS(FPS);

    tanque_t tank = {
        .direcao = 0,
        .corpo = {30, 30, 60, 30},
        .v_rotacao = 2,
        .v_mov = 1,
    };


    while (!WindowShouldClose()) {
        if (fim_de_jogo(&g)) {break;}
        incrementar_steps(&g);

        //Lógica do jogo
        mover_tanque(&g, &tank);
        mover_balas_tanque(&tank);


        BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);
            //DrawRectangleRec(tank.corpo, WHITE);
            DrawRectanglePro(tank.corpo, tank.origem, (float)tank.direcao, WHITE);

            for (uint8_t i = 0; i < tank.balas_ativas; i++) {
                DrawCircle(tank.balas[i].pos.x, tank.balas[i].pos.y, 3, RED);
            }

        EndDrawing();

    }
    CloseWindow();
    return 0;
}
