#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <raylib.h>
//#include "include/raylib.h"

#define RAIO_PECA 20
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900
#define FPS 60
#define TITULO "SiUR Table"
#define INFO_STATUS_SIZE 20

//const char     TITULO[] = "SiUR Table";
//const int      FPS = 60;
const Vector2  SCREEN_CENTER = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
const Vector2  SCREEN_TOP_LEFT = {0.0, 0.0};
const Color    BACKGROUND_COLOR = BLACK;


typedef struct Piece {
    Vector2 pos;
    Vector2 mov_speed;
    double raio;
    Color cor;
    uint8_t cor_idx;
    uint8_t piked;
} peca_t;


typedef struct Line {
    Vector2 origin;
    Vector2 destination;
} line_t;


double distancia(Vector2 p1, Vector2 p2) {
    double cX = p2.x - p1.x;
    double cY = p2.y - p1.y;
    return sqrt(pow(cX, 2) + pow(cY, 2));
}


int main(void) {
    srand(time(NULL)); 
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITULO);

    peca_t cursor = { .cor = BLUE };
    peca_t *selecionada;
    peca_t move_point = {};

    peca_t todas_pecas[10] = {};

    for (int i = 0; i < 10; i++) {
        todas_pecas[i].raio = RAIO_PECA;
        todas_pecas[i].pos.x = 750.0f;
        todas_pecas[i].pos.y = ((i+1) * 50.0) - 30.0;
        todas_pecas[i].cor = YELLOW;
    }

    line_t linha_distancia = {};
    line_t linha_caminho = {};

    char info[20];
    char dist[10];

    double dist_v = 0.0;

    Vector2 line_dist = {};
    int escolher_destino = 0;
    int draw_move_point = 0;
    int gatilho_movimento = 0;
    uint8_t selecao_ativa = 0;
    uint8_t move_step = 0;
    uint8_t piece_take = 0;

    float zoom_factor = 1.0;
    uint8_t zoom_change = 0;
    int8_t zoom_direction = 0;

    int count = 0;
    int count_changes = 0;
    
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {

        count++;

        cursor.pos = GetMousePosition();

        line_dist.x = ((cursor.pos.x - selecionada->pos.x) / 2) + selecionada->pos.x;
        line_dist.y = ((cursor.pos.y - selecionada->pos.y) / 2) + selecionada->pos.y;

        count_changes = 0;
  
        for (int i = 0; i < 10; i++) {
            count_changes++;

            if (CheckCollisionCircles(cursor.pos, cursor.raio, todas_pecas[i].pos, todas_pecas[i].raio)) {
                //sprintf_s(info, 20, "%s", "Colisão com J2");
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    move_point.pos.x = -20.0;
                    move_point.pos.y = -20.0;
                    selecionada = &todas_pecas[i];
                    escolher_destino = 1;
                    linha_caminho.origin = move_point.pos;
                    linha_caminho.destination = move_point.pos;
                    selecao_ativa = 1;
                }

                if (IsKeyDown(KEY_P) && todas_pecas[i].piked == 0 && count > 20) {
                    todas_pecas[i].piked = 1;
                    sprintf_s(info, 20, "%s", "Peça capturada...");
                    count = 0;
                } else if (IsKeyDown(KEY_P) && todas_pecas[i].piked != 0 && count > 20) {
                    todas_pecas[i].piked = 0;
                    sprintf_s(info, 20, "%s", "Peça liberada...");
                    count = 0;
                } else if (IsKeyDown(KEY_E) && todas_pecas[i].piked == 0 && count > 20) {
                    sprintf_s(info, 20, "%s", "Peça excluída...");
                    todas_pecas[i].pos.x = -2000.0f;
                    todas_pecas[i].pos.y = -2000.0f;
                    count = 0;
                } else if (IsKeyDown(KEY_C) && todas_pecas[i].piked == 0 && count > 20) {
                    switch (todas_pecas[i].cor_idx) {
                        case 0: {
                            todas_pecas[i].cor_idx += 1;
                            todas_pecas[i].cor = BLUE;
                            break;
                        }

                        case 1: {
                            todas_pecas[i].cor_idx = 0;
                            todas_pecas[i].cor = YELLOW;
                            break;
                        }
                    }
                    count = 0;
                }
            }

            if (todas_pecas[i].piked == 1) {
                todas_pecas[i].pos = GetMousePosition();
            }

            if (IsKeyDown(KEY_LEFT)) {
                todas_pecas[i].pos.x -= 2;
            } else if (IsKeyDown(KEY_RIGHT)) {
                todas_pecas[i].pos.x += 2;
            } else if (IsKeyDown(KEY_DOWN)) {
                todas_pecas[i].pos.y += 2;
            } else if (IsKeyDown(KEY_UP)) {
                todas_pecas[i].pos.y -= 2;
            } 

            if ( count > 10 ) {
                if (IsKeyDown(KEY_A)) {
                    count = 0;
                    zoom_factor += 0.1;
                    zoom_direction = 1;
                    zoom_change = 1;
                } else if (IsKeyDown(KEY_D)) {
                    count = 0;
                    if (zoom_factor >= 0.3) {
                        zoom_factor -= 0.1;
                        zoom_direction = -1;
                        zoom_change = 1;
                    }
                }
            }
        }


        if (zoom_change) {
            while (count_changes) {
                int i = count_changes-1;
                todas_pecas[i].raio = RAIO_PECA * zoom_factor;

                //double distancia_antes = distancia(todas_pecas[i].pos, SCREEN_TOP_LEFT);
                //double distancia_depois = distancia_antes * zoom_factor;

                //todas_pecas[i].pos.x = (distancia_depois * todas_pecas[i].pos.x) / distancia_antes;
                //todas_pecas[i].pos.y = (distancia_depois * todas_pecas[i].pos.y) / distancia_antes;


                /*
                
                x1 --- h1;
                x2 --- h2 = h1 * factor;

                */
                
                count_changes--;
            }

            zoom_change = 0;
        }

        dist_v = sqrt( pow(cursor.pos.x - selecionada->pos.x, 2) + pow(cursor.pos.y - selecionada->pos.y, 2) );
        dist_v = trunc(dist_v / (RAIO_PECA*zoom_factor));

        sprintf_s(dist, 10, "%d", (int)dist_v);

        if ( escolher_destino && dist_v <= 7 ) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                move_point.pos = GetMousePosition();
                linha_caminho.origin = selecionada->pos;
                linha_caminho.destination = move_point.pos;
                gatilho_movimento = 1;
            }
        }


        if (gatilho_movimento) {
            if (IsKeyDown(KEY_M)) {
                gatilho_movimento = 0;
                move_step = 30;
                selecionada->mov_speed.x = (selecionada->pos.x - move_point.pos.x) / 30.0;
                selecionada->mov_speed.y = (selecionada->pos.y - move_point.pos.y) / 30.0;
                move_point.pos.x = -20.0;
                move_point.pos.y = -20.0;
                linha_caminho.origin = move_point.pos;
                linha_caminho.destination = move_point.pos;
                selecao_ativa = 0;
               
            }
        }

        if (move_step) {
            selecionada->pos.x -= selecionada->mov_speed.x;
            selecionada->pos.y -= selecionada->mov_speed.y;
            move_step--;
        }

        linha_distancia.origin = selecionada->pos;
        linha_distancia.destination = cursor.pos;

        if (selecao_ativa) {
            cursor.raio = RAIO_PECA * zoom_factor;
        } else {
            cursor.raio = 0;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(info,10,SCREEN_HEIGHT-30, INFO_STATUS_SIZE, RED);
            if (selecao_ativa) {
                if ( dist_v > 7 ) {
                   DrawLine(linha_distancia.origin.x, linha_distancia.origin.y, linha_distancia.destination.x, linha_distancia.destination.y,RED);
                   DrawText(dist, line_dist.x, line_dist.y, 16, RED);
                } else {
                   DrawLine(linha_distancia.origin.x, linha_distancia.origin.y, linha_distancia.destination.x, linha_distancia.destination.y,GREEN);
                   DrawText(dist, line_dist.x, line_dist.y, 16, GREEN);
                }
            }

            DrawCircle(move_point.pos.x, move_point.pos.y, 5, GRAY);
            DrawLine(linha_caminho.origin.x, linha_caminho.origin.y, linha_caminho.destination.x, linha_caminho.destination.y,GRAY);
            DrawCircle(cursor.pos.x, cursor.pos.y, cursor.raio, cursor.cor);
            DrawCircle(SCREEN_CENTER.x, SCREEN_CENTER.y, 2, RED);

            for (int i = 0; i < 10; i++) {
                DrawCircle(todas_pecas[i].pos.x, todas_pecas[i].pos.y, todas_pecas[i].raio, todas_pecas[i].cor);
            }
       

        EndDrawing();

    }
    CloseWindow();
    
    return 0;
}



