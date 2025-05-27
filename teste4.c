#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "geometria.h"
#include "gamming.h"


#define TITULO " "
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define FPS 60
#define BACKGROUND_COLOR BLACK



#define TOTAL_ELEMENTOS_PILHA 30


typedef struct PilhaIndices {
    uint8_t array_idx[TOTAL_ELEMENTOS_PILHA];
    uint8_t numero_elementos;
} pilha_in_stack_t;



void inserir_na_pilha(pilha_in_stack_t *p, uint8_t idx) {
    if (p->numero_elementos < TOTAL_ELEMENTOS_PILHA) {
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


typedef struct Projetil {
    Vector2 pos;
    Vector2 v_mov;
    uint8_t raio;
    uint8_t dano;
    Color cor;
} projetil_t;


uint8_t mover_projeteis(uint8_t numero_projeteis_ativos, projetil_t *projeteis_ativos) {
    pilha_in_stack_t p = {};

    for (uint8_t i = 0; i < numero_projeteis_ativos; i++) {
        projeteis_ativos[i].pos.x += projeteis_ativos[i].v_mov.x;
        projeteis_ativos[i].pos.y += projeteis_ativos[i].v_mov.y;
        if (projeteis_ativos[i].pos.x > SCREEN_WIDTH || projeteis_ativos[i].pos.x < 0 || projeteis_ativos[i].pos.y > SCREEN_HEIGHT || projeteis_ativos[i].pos.y < 0) {
            inserir_na_pilha(&p, i);
        }
    }

    int8_t idx_retirado = 0;
    uint8_t decrementar_balas_ativas = 0;

    if (p.numero_elementos) {
        idx_retirado = retirar_da_pilha(&p);
        decrementar_balas_ativas++;
        if (idx_retirado < numero_projeteis_ativos) {
            for (uint8_t i = idx_retirado; i < numero_projeteis_ativos; i++) {
                projeteis_ativos[i] = projeteis_ativos[i+1];
            }
        }
    }

    numero_projeteis_ativos -= decrementar_balas_ativas;

    return numero_projeteis_ativos;
}



int main() {
    game_status_t g = {
        .vidas=3, 
        .vitalidade_maxima=100, 
        .vitalidade=100, 
        .cor_fundo=BACKGROUND_COLOR
    };

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITULO);
    SetTargetFPS(FPS);

    projetil_t projetis[20] = {};
    projetis[0].pos.x = SCREEN_WIDTH / 2;
    projetis[0].pos.y = SCREEN_HEIGHT / 2;
    projetis[0].v_mov.x = 1;

    while (!WindowShouldClose()) {
        if (fim_de_jogo(&g)) {break;}
        //Lógica do jogo

        mover_projeteis(1, projetis);

        BeginDrawing();
            ClearBackground(g.cor_fundo);
            
            for (uint8_t i = 0; i < 20; i++) {
                DrawCircle(projetis[i].pos.x, projetis[i].pos.y, 3, RED);
            }


        EndDrawing();

    }
    CloseWindow();
    return 0;
}

