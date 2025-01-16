#ifndef IO_CLI_H
#define IO_CLI_H

typedef struct {
    int size;
    int* values;
} input_selection;

void separador_simples();
void separador_duplo();
char* executar_comando_externo(const char *command);
void ler_input(const char* etiqueta, char* resposta);
void ler_input_int(const char* etiqueta, int *resposta);
void ler_input_float(const char* etiqueta, float *resposta);
void ler_input_double(const char* etiqueta, double *resposta);
int quantidade_opcoes_selecionadas(char* buffer);
int* traduzir_selecao(char* buffer_in, int *buffer_out);


#endif
