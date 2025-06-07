#ifndef STR_TOOL_H
#define STR_TOOL_H

/*

Funções para lidar com strings

*/

#define BUFFER_SIZE 30
#define PARSER_SIZE 15


typedef struct SubstringInfo {
    int index;
    int len;
    char *str_ptr;
} substring_info_t;


substring_info_t str_sub_match(char *string, char *substring);
int str_get_sub(substring_info_t sbt, char *buffer, int buffer_size);
int str_strip(char *string);
int str_remove_whitespace(char *string);
void str_cut(char *string, uint8_t cut_size);


#endif
