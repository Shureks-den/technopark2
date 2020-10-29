#include "letter_parcer.h"

typedef enum {
    L_COLON, //:
    L_FROM, //From
    L_TO, //To
    L_DATE, //Date
    L_CONTENT, //Content-type
    L_STRING,
    L_PART, //Контент разделенный пустой строкОЙ, как минимум одной
    L_NULSTR, // Пустые строки разделяющие основные части
    L_COUNT,
    L_ERROR,
} lexem_t;

typedef enum {
    S_HEAD,
    S_FROM,
    S_COLON,
    S_STRING,
    S_TO,
    S_DATE,
    S_NULSTR,
    S_CONT,
    S_ONEPART,
    S_PART,
    S_COUNT,
    S_ERR,
} state_t;

typedef int (*action_t)(const char *s);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

const rule_t syntax[S_COUNT][L_COUNT] = {
            /* L_NULSTR          L_COLON              L_FROM           L_TO             L_DATE            L_CONTENT            L_STRING            L_PART */
/*S_HEAD*/  {{S_NULSTR, NULL}},  {{S_ERR, NULL}},   {{S_FROM, NULL}}, {{S_TO, NULL}},  {{S_DATE, NULL}}, {{S_CONT, NULL}},    {{S_ERR, NULL}},    {{S_ERR, NULL}},        
/*S_FROM*/  {{S_ERR, NULL}},     {{S_COLON, NULL}}, {{S_ERR, NULL}},  {{S_ERR, NULL}}, {{S_ERR, NULL}},  {{S_ERR, NULL}},     {{S_ERR, NULL}},    {{S_ERR, NULL}}, 
/*S_COLON*/ {{S_ERR, NULL}},     {{S_ERR, NULL}},   {{S_ERR, NULL}},  {{S_ERR, NULL}}, {{S_ERR, NULL}},  {{S_CONT, NULL}},    {{S_STRING, NULL}}, {{S_ERR, NULL}},
/*S_STRING*/{{S_HEAD, NULL}},    {{S_ERR, NULL}},   {{S_ERR, NULL}},  {{S_ERR, NULL}}, {{S_ERR, NULL}},  {{S_ERR, NULL}},     {{S_ERR, NULL}},    {{S_ERR, NULL}},
/*S_TO*/    {{S_ERR, NULL}},     {{S_COLON, NULL}}, {{S_ERR, NULL}},  {{S_ERR, NULL}}, {{S_ERR, NULL}},  {{S_ERR, NULL}},     {{S_ERR, NULL}},    {{S_ERR, NULL}}, 
/*S_DATE*/  {{S_ERR, NULL}},     {{S_COLON, NULL}}, {{S_ERR, NULL}},  {{S_ERR, NULL}}, {{S_ERR, NULL}},  {{S_ERR, NULL}},     {{S_ERR, NULL}},    {{S_ERR, NULL}}, 
/*S_NULSTR*/{{S_ERR, NULL}},     {{S_ERR, NULL}},   {{S_ERR, NULL}},  {{S_ERR, NULL}}, {{S_ERR, NULL}},  {{S_ERR, NULL}},     {{S_ERR, NULL}},    {{S_PART, NULL}},
/*S_CONT*/  {{S_HEAD, NULL}},    {{S_ERR, NULL}},   {{S_ERR, NULL}},  {{S_ERR, NULL}}, {{S_ERR, NULL}},  {{S_ERR, NULL}},     {{S_ERR, NULL}},    {{S_ERR, NULL}},
/*S_PART*/  {{S_NULSTR, NULL}},  {{S_ERR, NULL}},   {{S_ERR, NULL}},  {{S_ERR, NULL}}, {{S_ERR, NULL}},  {{S_CONT, NULL}},    {{S_ERR, NULL}},    {{S_ERR, NULL}},
};