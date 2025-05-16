#ifndef GAMMING_H
#define GAMMING_H

#include <stdint.h>
#include <raylib.h>
#include <stdbool.h>

typedef struct GameStatus {
    uint8_t tela;
    uint8_t fase;
    uint8_t nivel;
    uint8_t reino_fluxo;
    uint8_t vidas;
    uint8_t vitalidade;
    uint8_t vitalidade_maxima;
    uint8_t arma_corrente;
    bool fim_de_jogo;
    uint32_t steps;
    uint32_t pontos;
} game_status_t;

void proxima_tela(game_status_t *g);
void tela_anterior(game_status_t *g);
void ir_para_tela(game_status_t *g, uint8_t numero_tela);
void proxima_fase(game_status_t *g);
void proximo_nivel(game_status_t *g);
void ganhar_vida(game_status_t *g);
void perder_vida(game_status_t *g);
void recuperar_vitalidade(game_status_t *g, uint8_t quantidade);
void perder_vitalidade(game_status_t *g, uint8_t quantidade);
void definir_arma(game_status_t *g, uint8_t tipo);
void zerar_steps(game_status_t *g);
void incrementar_steps(game_status_t *g);
void ganhar_pontos(game_status_t *g, uint32_t quantidade);
void perder_pontos(game_status_t *g, uint32_t quantidade);
void desenhar_pontos(game_status_t *g, int x, int y, int tamanho_fonte, Color cor);
bool fim_de_jogo(game_status_t *g);

#endif
