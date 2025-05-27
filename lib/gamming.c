#include "gamming.h"


void tela_anterior(game_status_t *g){
    if ((int)g->tela - 1 < 0) {
        g->tela = 0;
        return;
    }
    g->tela--;
}


void ir_para_tela(game_status_t *g, uint8_t numero_tela){
    g->tela = numero_tela;
}


void proxima_fase(game_status_t *g) {
    g->fase++;
}


void proximo_nivel(game_status_t *g) {
    g->nivel++;
}


void ganhar_vida(game_status_t *g) {
    g->vidas++;
}


void perder_vida(game_status_t *g) {
    if ((int)g->vidas - 1 < 0) {
        g->fim_de_jogo = true;
        return;
    }
    g->vidas--;
    g->vitalidade = g->vitalidade_maxima;
}


void recuperar_vitalidade(game_status_t *g, uint8_t quantidade) {
    if (g->vitalidade + quantidade > g->vitalidade_maxima) {
        g->vitalidade = g->vitalidade_maxima;
        return;
    }
    g->vitalidade += quantidade;
}


void perder_vitalidade(game_status_t *g, uint8_t quantidade) {
    if ((int)g->vitalidade - quantidade < 0) {
        g->vitalidade = 0;
        perder_vida(g);
        return;
    }
    g->vitalidade -= quantidade;
}


void definir_arma(game_status_t *g, uint8_t tipo) {
    g->arma_corrente = tipo;
}


void zerar_steps(game_status_t *g) {
    g->steps = 0;
}


void incrementar_steps(game_status_t *g) {
    g->steps++;
}


void ganhar_pontos(game_status_t *g, uint32_t quantidade) {
    g->pontos += quantidade;
}


void perder_pontos(game_status_t *g, uint32_t quantidade) {
    if ((int)g->pontos - quantidade < 0) {
        g->pontos = 0;
    }
    g->pontos -= quantidade;
}


void desenhar_pontos(game_status_t *g, int x, int y, int tamanho_fonte, Color cor) {
    //implementar...
}


bool fim_de_jogo(game_status_t *g) {
    return g->fim_de_jogo;
}

