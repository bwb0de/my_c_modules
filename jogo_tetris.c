#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "include/raylib.h"


const char TITULO[] = "Tetris";
const int  BLOCK_SIZE = 21;
const int  BLOCKS_HORIZONTAL = 15;
const int  BLOCKS_VERTICAL = 30;
const int  SCREEN_WIDTH = BLOCK_SIZE * BLOCKS_HORIZONTAL;
const int  SCREEN_HEIGHT = BLOCK_SIZE * BLOCKS_VERTICAL;
const int  FPS = 60;
const int  FALL_STEP_TIME = 24;
const Color  BACKGROUND_COLOR = BLACK;


typedef enum {
    ROTATE,
    DROP,
    DOWN,
    LEFT,
    RIGHT
} Moves;


typedef struct {
    char a[4];
    char b[4];
    char c[4];
    char d[4];
   Color cor;
} PieceView4x4; 


typedef struct {
    char a[3];
    char b[3];
    char c[3];
    Color cor;
} PieceView3x3; 


typedef struct {
    char a[2];
    char b[2];
    Color cor;
} PieceView2x2; 




typedef struct {
    int x;
    int y;
    short right_edge;
    void *sprite;
    char piece_shape;
} PieceInstance; 


void mostrar_peca_3x3(PieceInstance *piece) {
    for (int i = 0; i < 3; i++) {
        if (piece->sprite->a[i] == 'x') {
            DrawRectangle(piece->x + (i * BLOCK_SIZE), piece->y, BLOCK_SIZE, BLOCK_SIZE, RED);
        }
        if (piece->sprite->b[i] == 'x') {
            DrawRectangle(piece->x + (i * BLOCK_SIZE), piece->y+(BLOCK_SIZE*1), BLOCK_SIZE, BLOCK_SIZE, RED);
        }
        if (piece->sprite->c[i] == 'x') {
            DrawRectangle(piece->x + (i * BLOCK_SIZE), piece->y+(BLOCK_SIZE*2), BLOCK_SIZE, BLOCK_SIZE, RED);
        }
   }
}




void mostrar_peca(PieceInstance *piece) {
    for (int i = 0; i < 4; i++) {
        if (piece->sprite->a[i] == 'x') {
            DrawRectangle(piece->x + (i * BLOCK_SIZE), piece->y, BLOCK_SIZE, BLOCK_SIZE, RED);
        }
        if (piece->sprite->b[i] == 'x') {
            DrawRectangle(piece->x + (i * BLOCK_SIZE), piece->y+(BLOCK_SIZE*1), BLOCK_SIZE, BLOCK_SIZE, RED);
        }
        if (piece->sprite->c[i] == 'x') {
            DrawRectangle(piece->x + (i * BLOCK_SIZE), piece->y+(BLOCK_SIZE*2), BLOCK_SIZE, BLOCK_SIZE, RED);
        }
        if (piece->sprite->d[i] == 'x') {
            DrawRectangle(piece->x + (i * BLOCK_SIZE), piece->y+(BLOCK_SIZE*3), BLOCK_SIZE, BLOCK_SIZE, RED);
        }
    }
}


void limites_laterais(PieceInstance *piece) {
    if ( piece->x < 0 ) {
        piece->x = 0; 
    }
    if ( piece->x > (SCREEN_WIDTH - (BLOCK_SIZE * (piece->right_edge+2)))) {
        piece->x = SCREEN_WIDTH - (BLOCK_SIZE * (piece->right_edge+2)); 
    }
}


int main(void) {
    srand(time(NULL)); 

    PieceView3x3 piece0 = {
        .a = {'x', ' ', ' '},
        .b = {'x', ' ', ' '},
        .c = {'x', 'x', ' '},
        .cor = BLUE,
    };

    PieceView3x3 piece1 = {
        .a = {' ', ' ', 'x'},
        .b = {'x', 'x', 'x'},
        .c = {' ', ' ', ' '},
        .cor = BLUE,
    };

    PieceView3x3 piece2 = {
        .a = {'x', 'x', ' '},
        .b = {' ', 'x', ' '},
        .c = {' ', 'x', ' '},
        .cor = BLUE,
    };

    PieceView3x3 piece3 = {
        .a = {'x', 'x', 'x'},
        .b = {'x', ' ', ' '},
        .c = {' ', ' ', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceP0 = {
        .a = {'x', 'x', ' '},
        .b = {'x', ' ', ' '},
        .c = {'x', ' ', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceP1 = {
        .a = {'x', ' ', ' '},
        .b = {'x', 'x', 'x'},
        .c = {' ', ' ', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceP2 = {
        .a = {' ', 'x', ' '},
        .b = {' ', 'x', ' '},
        .c = {'x', 'x', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceP3 = {
        .a = {'x', 'x', 'x'},
        .b = {' ', ' ', 'x'},
        .c = {' ', ' ', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceT0 = {
        .a = {'x', 'x', 'x'},
        .b = {' ', 'x', ' '},
        .c = {' ', ' ', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceT1 = {
        .a = {'x', ' ', ' '},
        .b = {'x', 'x', ' '},
        .c = {'x', ' ', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceT2 = {
        .a = {' ', 'x', ' '},
        .b = {'x', 'x', 'x'},
        .c = {' ', ' ', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceT3 = {
        .a = {' ', 'x', ' '},
        .b = {'x', 'x', ' '},
        .c = {' ', 'x', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceS0 = {
        .a = {' ', 'x', 'x'},
        .b = {'x', 'x', ' '},
        .c = {' ', ' ', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceS1 = {
        .a = {'x', ' ', ' '},
        .b = {'x', 'x', ' '},
        .c = {' ', 'x', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceZ0 = {
        .a = {'x', 'x', ' '},
        .b = {' ', 'x', 'x'},
        .c = {' ', ' ', ' '},
        .cor = BLUE,
    };

    PieceView3x3 pieceZ1 = {
        .a = {' ', 'x', ' '},
        .b = {'x', 'x', ' '},
        .c = {'x', ' ', ' '},
        .cor = BLUE,
    };

    PieceView2x2 pieceO1 = {
        .a = {'x', 'x'},
        .b = {'x', 'x'},
        .cor = BLUE,
    };

    
    PieceView4x4 pieceI0 = {
        .a = {' ', 'x', ' ', ' '},
        .b = {' ', 'x', ' ', ' '},
        .c = {' ', 'x', ' ', ' '},
        .d = {' ', 'x', ' ', ' '},       
        .cor = BLUE,
    };

    PieceView4x4 pieceI1 = {
        .a = {' ', ' ', ' ', ' '},
        .b = {'x', 'x', 'x', 'x'},
        .c = {' ', ' ', ' ', ' '},
        .d = {' ', ' ', ' ', ' '},       
        .cor = BLUE,
    };



    PieceInstance current_piece = {
        .x = BLOCK_SIZE * (BLOCKS_HORIZONTAL / 2),
        .y = 0,
        .sprite = &piece0,
    };




    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;
    InitWindow(screenWidth, screenHeight, TITULO);
    short steps = 0;

    char pontos[15];
    sprintf(pontos, "Pontos: %d", 0);


    SetTargetFPS(FPS);


    while (!WindowShouldClose()) {

        steps++;

        //Controle
        if ( IsKeyPressed(KEY_UP)) {

            if (current_piece.sprite == &piece0 ) {
                current_piece.sprite = &piece1;
                current_piece.right_edge = 1;
            }

            else if (current_piece.sprite == &piece1 ) {
                current_piece.sprite = &piece2;
                current_piece.right_edge = 0;
            }

            else if (current_piece.sprite == &piece2 ) {
                current_piece.sprite = &piece3;
                current_piece.right_edge = 1;
            }

            else if (current_piece.sprite == &piece3 ) {
                current_piece.sprite = &piece0;
                current_piece.right_edge = 0;
            }
        }

        else if ( IsKeyDown(KEY_DOWN))  { steps = FALL_STEP_TIME; }
        else if ( IsKeyPressed(KEY_LEFT))  { current_piece.x -= BLOCK_SIZE; }
        else if ( IsKeyPressed(KEY_RIGHT)) { current_piece.x += BLOCK_SIZE; }


        //Taxa de atualização
        if ( steps == FALL_STEP_TIME ) {
            current_piece.y += BLOCK_SIZE;
            steps = 0;
        }


        //Limites da tela
        limites_laterais(&current_piece);


        BeginDrawing();
            ClearBackground(BLACK);
            mostrar_peca(&current_piece);
            DrawText(pontos, BLOCK_SIZE, SCREEN_HEIGHT - (BLOCK_SIZE * 2), 12, YELLOW);
        EndDrawing();

    }
    CloseWindow();
    return 0;
}



