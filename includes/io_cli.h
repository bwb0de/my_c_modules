#ifndef IO_CLI_H
#define IO_CLI_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define BUFFER_SIZE 30
#define PARSER_SIZE 15


typedef enum InputKind {
    NUMEROS_INTEIROS,
    NUMEROS_REAIS_SIMPLES,
    NUMEROS_REAIS_DOUBLE,
    TEXTO
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


typedef struct ParserRealOutput {
    double parsed;
    char not_parsed[BUFFER_SIZE];
} parsed_real_t;



char* shellexec(const char *command);

parsed_int_t parse_int_partial(char *string_input);
parsed_real_t parse_real_partial(char *string_input);


input_rec_t input_text_on_receiver(const char *etiqueta, input_rec_t ir);
input_rec_t input_int_on_receiver(const char *etiqueta, input_rec_t ir);
input_rec_t input_float_on_receiver(const char *etiqueta, input_rec_t ir);
input_rec_t input_double_on_receiver(const char *etiqueta, input_rec_t ir);
input_rec_t input_selection(char *etiqueta, const char **opcoes, int limite_maximo, input_rec_t ir); 


uint8_t count_selected(char* buffer);
void parse_selected(char* buffer_in, int *buffer_out);
int return_selection_integer(int* array_selecao, int arr_size);
bool any_in(int* valores_respostas, size_t n_respostas, int* valores_testes, size_t n_valores_teste);
void print_ops(const char** opcoes, int limite_maximo);



#endif
