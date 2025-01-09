#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <raylib.h>
//#include "include/raylib.h"


const char TITULO[] = "Snake";
const int  BLOCK_SIZE = 12;
const int  INIT_SIZE = 5;
const int  BLOCKS_HORIZONTAL = 40;
const int  BLOCKS_VERTICAL = 40;
const int  SCREEN_WIDTH = BLOCK_SIZE * BLOCKS_HORIZONTAL;
const int  SCREEN_HEIGHT = BLOCK_SIZE * BLOCKS_VERTICAL;
const int  FPS = 30;
const int  SNAKE_STEP_TIME = 6;
const Color  BACKGROUND_COLOR = BLACK;


typedef enum {
    GOING_UP,
    GOING_DOWN,
    GOING_LEFT,
    GOING_RIGHT
} Direction;

typedef struct {
     int x;
     int y;
} BodyChunk;


typedef struct {
     int x;
     int y;
     int score;
} Food;



typedef struct {
    int tamanho;
    unsigned int score;
    Direction direction;
    unsigned short velocidade;
    BodyChunk corpo[100];
} Snake;



void aumentar_corpo(Snake *snake) {
    BodyChunk novo_pedaco;
    BodyChunk rabo = snake->corpo[snake->tamanho];

    switch (snake->direction) {
        case GOING_DOWN: {
            novo_pedaco.x = rabo.x;
            novo_pedaco.y = rabo.y - BLOCK_SIZE;
            break;
        }
        case GOING_UP: {
            novo_pedaco.x = rabo.x;
            novo_pedaco.y = rabo.y + BLOCK_SIZE;
            break;
        }
        case GOING_LEFT: {
            novo_pedaco.x = rabo.x + BLOCK_SIZE;
            novo_pedaco.y = rabo.y;
            break;
        }
        case GOING_RIGHT: {
            novo_pedaco.x = rabo.x - BLOCK_SIZE;
            novo_pedaco.y = rabo.y;
            break;
        }
    }

    snake->tamanho++;
    snake->corpo[snake->tamanho] = novo_pedaco;

}


void mover_serpente(Snake *snake) {
    int tmp_x, tmp_y;
    int old_x = snake->corpo[0].x;
    int old_y = snake->corpo[0].y;

    switch (snake->direction) {
        case GOING_UP: {
            snake->corpo[0].y -= BLOCK_SIZE;
            break;
        }
        case GOING_DOWN: {
            snake->corpo[0].y += BLOCK_SIZE;
            break;
        }
        case GOING_RIGHT: {
            snake->corpo[0].x += BLOCK_SIZE;
            break;
        }
        case GOING_LEFT: {
            snake->corpo[0].x -= BLOCK_SIZE;
            break;
        }
    }

    for (int i = 1; i < snake->tamanho; i++ ) {
        tmp_x = snake->corpo[i].x;
        tmp_y = snake->corpo[i].y;
        snake->corpo[i].x = old_x;
        snake->corpo[i].y = old_y;
        old_x = tmp_x;
        old_y = tmp_y;
    }
}


void mover_comida(Food *food) {
    food->x = (rand() % BLOCKS_HORIZONTAL) * BLOCK_SIZE;
    food->y = (rand() % BLOCKS_VERTICAL) * BLOCK_SIZE;
    food->score = (rand() % 5) + 1;
}



int colisao_com_corpo(Snake *snake) {
    for (int i = 1; i < snake->tamanho; i++ ) {
        if (snake->corpo[i].x == snake->corpo[0].x && snake->corpo[i].y == snake->corpo[0].y) {
            return 1;
        }
    }
    return 0;
}


int colisao_com_limites_da_janela(Snake *snake) {
    if (snake->corpo[0].x < 0 || snake->corpo[0].x >= SCREEN_WIDTH  ) {return 1;}
    if (snake->corpo[0].y < 0 || snake->corpo[0].y >= SCREEN_HEIGHT ) {return 1;}
    return 0;
}


int colisao_com_comida(Snake *snake, Food *food) {
    if (snake->corpo[0].x == food->x && snake->corpo[0].y == food->y ) {return 1;}
    return 0;
}




Snake *criar_snake() {
    Snake *snake = (Snake *)malloc(sizeof(Snake));
    snake->tamanho = 0;
    snake->corpo[0].x = BLOCK_SIZE * 3;
    snake->corpo[0].y = BLOCK_SIZE * 3;
    snake->direction = GOING_DOWN;
    snake->score = 0;
    snake->velocidade = 0;
    for (int i = 0; i < 4; i++) {
        aumentar_corpo(snake);
    }
    return snake;
}


Food *criar_comida() {
    Food *food = (Food *)malloc(sizeof(Food));
    food->x = (rand() % BLOCKS_HORIZONTAL) * BLOCK_SIZE;
    food->y = (rand() % BLOCKS_VERTICAL) * BLOCK_SIZE;
    food->score = (rand() % 5) + 1;
    return food;
}




int main(void) {
    srand(time(NULL)); 

    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;
    InitWindow(screenWidth, screenHeight, TITULO);
    short steps = 0;

    SetTargetFPS(FPS);
    Snake *snake = criar_snake();
    Food *food = criar_comida();
    char pontos[15];
    sprintf(pontos, "Pontos: %d", 0);


    while (!WindowShouldClose()) {

        steps++;

        //Controle
        if      ( IsKeyPressed(KEY_UP)    && snake->direction != GOING_DOWN ) { snake->direction = GOING_UP;    }
        else if ( IsKeyPressed(KEY_DOWN)  && snake->direction != GOING_UP   ) { snake->direction = GOING_DOWN;  }
        else if ( IsKeyPressed(KEY_LEFT)  && snake->direction != GOING_RIGHT) { snake->direction = GOING_LEFT;  }
        else if ( IsKeyPressed(KEY_RIGHT) && snake->direction != GOING_LEFT ) { snake->direction = GOING_RIGHT; }


        //Taxa de atualização
        if ( steps == SNAKE_STEP_TIME ) {
            mover_serpente(snake);
            steps = snake->velocidade;
        }

        //Evoluindo no jogo
        if (colisao_com_comida(snake, food)) {
            snake->score += food->score;
            aumentar_corpo(snake);
            mover_comida(food);
            sprintf(pontos, "Pontos: %d", snake->score);
            if (snake->score % 3 == 0 && snake->velocidade < (SNAKE_STEP_TIME - 1)) {
                snake->velocidade++;
            }
        }

       //Fim de jogo
        if (colisao_com_corpo(snake)) { break; }
        if (colisao_com_limites_da_janela(snake)) { break; }



        BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangle(food->x, food->y, BLOCK_SIZE, BLOCK_SIZE, RED);

            for (int i = 0; i < snake->tamanho; i++) {
                DrawRectangle(snake->corpo[i].x, snake->corpo[i].y, BLOCK_SIZE, BLOCK_SIZE, RAYWHITE);
            }

            DrawText(pontos, BLOCK_SIZE, SCREEN_HEIGHT - (BLOCK_SIZE * 2), 12, YELLOW);

        EndDrawing();

    }
    free(snake);
    CloseWindow();
    return 0;
}



