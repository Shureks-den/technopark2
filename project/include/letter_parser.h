#ifndef PROJECT_INCLUDE_LETTER_PARSER_H_
#define PROJECT_INCLUDE_LETTER_PARSER_H_



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>


#define FROM "from:"
#define TO "to:"
#define DATE "date:"
#define BOUND "boundary="

typedef enum {
    L_FROM,  // From
    L_TO,  // To
    L_DATE,  // Date
    L_BOUND,  // boundary=
    L_COUNT,
    L_ERROR,
} lexem_t;

typedef enum {
    S_HEAD,  // 0
    S_FROM,  // 1
    S_TO,    // 2
    S_DATE,  // 3
    S_BOUND,  // 4
    S_FROM_TO,  // 5
    S_FROM_DATE,  // 6
    S_FROM_BOUND,  // 7
    S_TO_DATE,  // 8
    S_TO_BOUND,  // 9
    S_DATE_BOUND,  // 10
    S_FROM_TO_DATE,  // 11
    S_FROM_TO_BOUND,  // 12
    S_FROM_DATE_BOUND,  // 13
    S_TO_DATE_BOUND,  // 14
    S_COUNT,  // 15
    S_ERR,  // 16
    S_END,  // 17
} state_t;

typedef struct {
    char *from;
    char *to;
    char *date;
    char *bound;
    size_t num_parts;
} letter_t;

typedef void (*action_t)(char *line, letter_t *data);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

void parse_letter(const char *path_to_eml);

#endif  // PROJECT_INCLUDE_LETTER_PARSER_H_
