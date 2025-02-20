#ifndef IO_CLI_H
#define IO_CLI_H

#define BUFFER_SIZE 30
#define PARSER_SIZE 10


typedef enum InputKind {
    INT,
    FLOAT,
    DOUBLE,
    STRING
} input_king_t;


typedef union InputData {
    char texto[BUFFER_SIZE];
    double n_real_d;
    float n_real_f;
    int n_int;
} input_data_t;


typedef struct InputReceiver {
    input_king_t tipo;
    input_data_t valor;
} input_rec_t;


typedef struct ParserIntOutput {
    int parsed;
    char not_parsed[BUFFER_SIZE];
} parsed_int_t;


char* executar_comando_externo(const char *command);

input_rec_t input_text_on_receiver(const char* etiqueta, input_rec_t ir);
input_rec_t input_int_on_receiver(const char* etiqueta, input_rec_t ir);
input_rec_t input_float_on_receiver(const char* etiqueta, input_rec_t ir);
input_rec_t input_double_on_receiver(const char* etiqueta, input_rec_t ir);


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
int selecionar_opcoes(char* etiqueta, const char** opcoes, int limite_maximo); 


#endif
