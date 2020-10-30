#define _GNU_SOURCE
#include "letter_parser.h"

lexem_t get_lexem(char *line) {
    if (strncasecmp(line, FROM, strlen(FROM)) == 0) {
        return L_FROM;
    }
    if (strncasecmp(line, TO, strlen(TO)) == 0) {
        return L_TO;
    }
    if (strncasecmp(line, DATE, strlen(DATE)) == 0) {
        return L_DATE;
    }
    if (strcasestr(line, BOUND) != NULL) {
        return L_BOUND;
    }
    return L_ERROR;
}

static char* store_args(char *line) {
    char* ptr;
    strtok_r(line, ":", &ptr);
    char *res;
    res = strtok_r(NULL, "\r\n", &ptr);
    return res + strspn(res, " ");
}

void store_from(char *line, letter_t *data) {
    data->from = store_args(line);
}

void store_to(char *line, letter_t *data) {
    data->to = store_args(line);
}

void store_date(char *line, letter_t *data) {
    data->date = store_args(line);
}

void store_bound(char *line, letter_t *data) {
    char *res = strcasestr(line, BOUND);
    if (strlen(res) != strlen(line)) {
        if ((*(res - 1) != 32) && (*(res - 1) != '\t') && (*(res-1) != ';')) {
            return;
        }
    }
    res = res + strlen(BOUND) + strspn(res, " ");
    if (res[0] == '"') {
        res++;
        char *saveptr;
        res = strtok_r(res, "\"", &saveptr);
    } else {
        char *saveptr;
        res = strtok_r(res, "\r\n ", &saveptr);
    }
    data->bound = res;
}

rule_t syntax[S_COUNT][L_COUNT] = {
                            /* L_FROM             L_TO    L_DATE                           L_BOUND */
/* S_HEAD */           {{S_FROM, store_from},            {S_TO, store_to},
                                {S_DATE, store_date},            {S_BOUND, store_bound}},
/* S_FROM */           {{S_ERR, NULL},                   {S_FROM_TO, store_to},
                                {S_FROM_DATE, store_date},       {S_FROM_BOUND, store_bound}},
/* S_TO */             {{S_FROM_TO, store_from},         {S_ERR, NULL},
                                {S_TO_DATE, store_date},         {S_TO_BOUND, store_bound}},
/* S_DATE */           {{S_FROM_DATE, store_from},       {S_TO_DATE, store_to},
                                {S_ERR, NULL},                   {S_DATE_BOUND, store_bound}},
/* S_BOUND */          {{S_FROM_BOUND, store_from},      {S_TO_BOUND, store_to},
                                {S_DATE_BOUND, store_date},      {S_ERR, NULL}},

/* S_FROM_TO */        {{S_ERR, NULL},                   {S_ERR, NULL},
                                {S_FROM_TO_DATE, store_date},    {S_FROM_TO_BOUND, store_bound}},
/* S_FROM_DATE */      {{S_ERR, NULL},                   {S_FROM_TO_DATE, store_to},
                                {S_ERR, NULL},                   {S_FROM_DATE_BOUND, store_bound}},
/* S_FROM_BOUND */     {{S_ERR, NULL},                   {S_FROM_TO_BOUND, store_to},
                                {S_FROM_DATE_BOUND, store_date}, {S_ERR, NULL}},

/* S_TO_DATE */        {{S_FROM_TO_DATE, store_from},    {S_ERR, NULL},
                                {S_DATE, NULL},                  {S_TO_DATE_BOUND, store_bound}},
/* S_TO_BOUND */       {{S_FROM_TO_BOUND, store_from},   {S_ERR, NULL},
                                {S_TO_DATE_BOUND, store_date},   {S_ERR, NULL}},
/* S_DATE_BOUND */     {{S_FROM_DATE_BOUND, store_from}, {S_TO_DATE_BOUND, store_to},
                                {S_ERR, NULL},                   {S_ERR, NULL}},

/* S_FROM_TO_DATE */   {{S_ERR, NULL},                   {S_ERR, NULL},
                                {S_ERR, NULL},                   {S_END, store_bound}},
/* S_FROM_TO_BOUND */  {{S_ERR, NULL},                   {S_ERR, NULL},
                                {S_END, store_date},             {S_ERR, NULL}},
/* S_FROM_DATE_BOUND */{{S_ERR, NULL},                   {S_END, store_to},
                                {S_ERR, NULL},                   {S_ERR, NULL}},
/* S_TO_DATE_BOUND */  {{S_END, NULL},                   {S_ERR, NULL},
                                {S_ERR, NULL},                   {S_ERR, NULL}},
};

void parse_letter(const char *path_to_eml) {
    int fd = open(path_to_eml, O_RDWR, S_IRUSR | S_IWUSR);
    struct stat statbuf;

    if (fstat(fd, &statbuf) < 0) {
        perror("PROBLEM WITH SIZE");
        return;
    }


    char* file_in_memory = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);

    int have_body = 0;
    int next_line = 0;
    int empty_line = 0;

    for (int i = 0; i < statbuf.st_size; i++) {
        if (empty_line == 1 && file_in_memory[i] != '\n' && file_in_memory[i] != '\r' &&
            file_in_memory[i] != '\0' && file_in_memory[i] != 10) {
            have_body = 1;
            break;
        }
        if (next_line == 1 && (file_in_memory[i] == '\n' || file_in_memory[i] == '\r')) {
            empty_line = 1;
            have_body = 0;
        }
        next_line = 0;
        if (file_in_memory[i] == '\n' || file_in_memory[i] == '\r') {
            next_line = 1;
        }
    }

    letter_t data = {0};
    lexem_t lexem;
    state_t state = S_HEAD;

    int is_body_found = 0;
    int have_afterpart = 0;
    int is_parts_begin = 0;

    char *saveptr;
    char *line = strtok_r(file_in_memory, "\n\r", &saveptr);

    rule_t rule = {17, NULL};
    char *new = NULL;
    char *new1 = NULL;
    while (line != NULL) {
        lexem = get_lexem(line);
        if (state < S_COUNT && lexem < L_COUNT) {
            rule = syntax[state][lexem];
        }
        if (state != S_END && state != S_ERR && (lexem < L_COUNT) && rule.action) {
            rule.action(line, &data);
        }
        if (is_body_found == 1) {
            if (strstr(line, data.bound) != NULL) {
                is_parts_begin = 1;
                have_afterpart = 0;
                data.num_parts++;
            }
            if (is_parts_begin == 1) {
                line = strtok_r(NULL, "\n\r", &saveptr);
                if (line != NULL) {
                    if (strlen(line) != 1) {
                        have_afterpart = 1;
                    }
                }
                continue;
            }
        }
    
        line = strtok_r(NULL, "\n", &saveptr);
        if (line != NULL && is_parts_begin == 0) {
            while (line[0] == ' ' && lexem < L_BOUND) {
                if (lexem == L_FROM &&
                    state != S_FROM &&
                    state != S_FROM_TO &&
                    state != S_FROM_TO_BOUND &&
                    state != S_FROM_BOUND &&
                    state != S_FROM_DATE &&
                    state != S_FROM_DATE_BOUND &&
                    state != S_FROM_TO_DATE &&
                    state != S_END) {
                    char *saveptr1;
                    char *saveptr2;
                    new = calloc(1, strlen(data.from) + strlen(line));
                    data.from = strtok_r(data.from, "\n\r", &saveptr1);
                    line = strtok_r(line, "\n\r", &saveptr2);
                    strncat(new, data.from, strlen(data.from));
                    strncat(new, line, strlen(line));
                    data.from = new;
                } 

                if (lexem == L_TO &&
                    state != S_TO &&
                    state != S_TO_BOUND &&
                    state != S_TO_DATE &&
                    state != S_TO_DATE_BOUND &&
                    state != S_FROM_TO &&
                    state != S_FROM_TO_DATE &&
                    state != S_END) {
                    char *extraptr;
                    strncat(data.to, line, strlen(line));
                    data.to = strtok_r(data.to, "\n\r", &extraptr);
                }

                if (lexem == L_DATE &&
                    state != S_DATE &&
                    state != S_DATE_BOUND &&
                    state != S_TO_DATE &&
                    state != S_TO_DATE_BOUND &&
                    state != S_FROM_TO_DATE &&
                    state != S_FROM_DATE_BOUND &&
                    state != S_FROM_DATE &&
                    state != S_END) {
                    char *saveptr1;
                    char *saveptr2;
                    new1 = calloc(1, strlen(data.date) + strlen(line));
                    data.date = strtok_r(data.date, "\n\r", &saveptr1);
                    line = strtok_r(line, "\n\r", &saveptr2);
                    strncat(new1, data.date, strlen(data.date));
                    strncat(new1, line, strlen(line));
                    data.date = new1;
                }
                line = strtok_r(NULL, "\n\r", &saveptr);
            }
        }
        if ((rule.state == S_BOUND ||
            rule.state == S_FROM_BOUND ||
            rule.state == S_DATE_BOUND ||
            rule.state == S_FROM_TO_BOUND ||
            rule.state == S_TO_BOUND ||
            rule.state == S_FROM_DATE_BOUND ||
            rule.state == S_END) && data.bound == NULL) {
        } else {
            state = rule.state;
        }

        if (state == S_BOUND ||
            state == S_FROM_BOUND ||
            state == S_DATE_BOUND ||
            state == S_FROM_TO_BOUND ||
            state == S_FROM_DATE_BOUND ||
            state == S_TO_DATE_BOUND ||
            state == S_END) {
            is_body_found = 1;
        }
    }
    if (data.num_parts != 0 && have_afterpart == 0) {
        data.num_parts--;
    } else if (have_body == 0) {
        data.num_parts = 0;
    } else if (data.num_parts == 0) {
        data.num_parts = 1;
    }
    if (data.from) {
        for (size_t i = 0; i < strlen(data.from); i++) {
            printf("%c", data.from[i]);
        }
    }
    printf("|");
    if (data.to) {
        printf("%s", data.to);
    }
    printf("|");
    if (data.date) {
        printf("%s", data.date);
    }
    printf("|%zu\n", data.num_parts);
    if (new != NULL) {
        free(new);
    }
    if (new1 != NULL) {
        free(new1);
    }
}
