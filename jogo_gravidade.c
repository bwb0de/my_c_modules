#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "include/raylib.h"


const char TITULO[] = "Gravidade";
const int  FPS = 60;
const int  SCREEN_WIDTH = 800;
const int  SCREEN_HEIGHT = 800;
const Color  BACKGROUND_COLOR = BLACK;


typedef struct {
    double x;
    double y;
    double vx;
    double vy;
    double massa;
} CorpoCeleste;


double distancia_A_B(CorpoCeleste *corpo1, CorpoCeleste *corpo2) {
    double x_delta = corpo2->x - corpo1->x;
    double y_delta = corpo2->y - corpo1->y;
    //printf("Delta x para l: %f\n", x_delta);
    //printf("Delta y para l: %f\n", y_delta);
    double distancia = sqrt((x_delta * x_delta) + (y_delta * y_delta));
    return distancia;
}

double angulo_com_horizontal_A_B(CorpoCeleste *corpo1, CorpoCeleste *corpo2) {
    double tg = ((double)corpo2->y - (double)corpo1->y) / ((double)corpo2->x - (double)corpo1->x);
    double angulo_rad = atan(tg);
    double angulo_deg = (angulo_rad * 180) / PI;
    return angulo_rad;
}

void atualizar_velocidades(CorpoCeleste *c1, CorpoCeleste *c2) {
    double G = 6.67 ;//* pow(10, -3);
    double Mm = c1->massa * c2->massa;
    double ll = pow(distancia_A_B(c1, c2), 2);
    double rX = cos(angulo_com_horizontal_A_B(c1, c2));
    double rY = sin(angulo_com_horizontal_A_B(c1, c2));
    double Fx = (G*Mm*rX) / ll;
    double Fy = (G*Mm*rY) / ll;
    //F = m*a; a = F/m;
    double aXc1 = Fx/c1->massa;
    double aXc2 = Fx/c2->massa;
    double aYc1 = Fy/c1->massa;
    double aYc2 = Fy/c2->massa;

    if ( c1->x < c2->x ) {
        c1->vx += aXc1;
        c2->vx -= aXc2;
    } else {
        c1->vx -= aXc1;
        c2->vx += aXc2;
    }

    if ( c1->y < c2->y ) {
        c1->vy += aXc1;
        c2->vy -= aXc2;
    } else {
        c1->vy -= aXc1;
        c2->vy += aXc2;
    }

    //printf("Angulo: %f\n", angulo_com_horizontal_A_B(c1, c2));
    //printf("Distância: %f\n", distancia_A_B(c1, c2));
    //printf("c1: (%f, %f)\n", c1->vx, c1->vy);
    //printf("c2: (%f, %f)\n", c2->vx, c2->vy);
}


int main(void) {
    srand(time(NULL)); 

    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;
    InitWindow(screenWidth, screenHeight, TITULO);

    int step = 0;
    int step_calc = 1;

CorpoCeleste corpo1 = {
        .x = 700,
        .y = 300,
        .vx = -0.23,
        .vy = 0.45,
        .massa = 80.0,
    };

    CorpoCeleste corpo2 = {
        .x = 100,
        .y = 400,
        .vx = 0.5,
        .vy = -0.4,
        .massa = 40.0,
    };

   
    
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {

        step++;

        if (step == step_calc ) {
            step = 0;
            atualizar_velocidades(&corpo1, &corpo2);
       }


        corpo1.x += corpo1.vx; corpo1.y += corpo1.vy;
        corpo2.x += corpo2.vx; corpo2.y += corpo2.vy;

        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircle(corpo1.x, corpo1.y, corpo1.massa / 2.0, BLUE);
            DrawCircle(corpo2.x, corpo2.y, corpo2.massa / 2.0, YELLOW);

        EndDrawing();

    }
    CloseWindow();
    
    return 0;
}



