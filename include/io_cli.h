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
void ler_input_uint8(const char* etiqueta, uint8_t *resposta);
void ler_input_uint32(const char* etiqueta, uint32_t *buffer);
void ler_input_float(const char* etiqueta, float *resposta);
void ler_input_double(const char* etiqueta, double *resposta);

int quantidade_opcoes_selecionadas(char* buffer);
int* traduzir_selecao(char* buffer_in, int *buffer_out);
int tamanho_string_selecao(char* buffer);
int retornar_inteiro_resultante_de_multipla_escolha(int* array_selecao, int arr_size);
int any_in(int* valores_respostas, int n_respostas, int* valores_testes, int n_valores_teste);
void imprimir_opcoes(const char** opcoes, int limite_maximo);
void selecionar_opcoes(char* etiqueta, const char** opcoes, int limite_maximo, int* endereco_respostas); 


#endif
