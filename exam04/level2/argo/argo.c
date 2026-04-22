#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct json {
    enum { MAP, INTEGER, STRING } type;
    union {
        struct { struct pair *data; size_t size; } map;
        int  integer;
        char *string;
    };
} json;

typedef struct pair { char *key; json value; } pair;

void free_json(json j);
int  argo(json *dst, FILE *stream);

int peek(FILE *stream)
{
    int c = getc(stream);
    ungetc(c, stream);
    return c;
}

void unexpected(FILE *stream)
{
    if (peek(stream) != EOF)
        printf("unexpected token '%c'\n", peek(stream));
    else
        printf("unexpected end of input\n");
}

int accept(FILE *stream, char c)
{
    if (peek(stream) == c)
        return (void)getc(stream), 1;
    return 0;
}

int expect(FILE *stream, char c)
{
    if (accept(stream, c))
        return 1;
    unexpected(stream);
    return 0;
}

void free_json(json j)
{
    switch (j.type)
    {
        case MAP:
            for (size_t i = 0; i < j.map.size; i++)
            {
                free(j.map.data[i].key);
                free_json(j.map.data[i].value);
            }
            free(j.map.data);
            break;
        case STRING: free(j.string); break;
        default: break;
    }
}

void serialize(json j)
{
    switch (j.type)
    {
        case INTEGER: printf("%d", j.integer); break;
        case STRING:
            putchar('"');
            for (int i = 0; j.string[i]; i++)
            {
                if (j.string[i] == '\\' || j.string[i] == '"')
                    putchar('\\');
                putchar(j.string[i]);
            }
            putchar('"');
            break;
        case MAP:
            putchar('{');
            for (size_t i = 0; i < j.map.size; i++)
            {
                if (i != 0) putchar(',');
                serialize((json){.type = STRING, .string = j.map.data[i].key});
                putchar(':');
                serialize(j.map.data[i].value);
            }
            putchar('}');
            break;
    }
}

static char *parse_str(FILE *stream)
{
    size_t size = 0, cap = 16;
    char *buf = malloc(cap);
    int c;

    while ((c = getc(stream)) != '"')
    {
        if (c == EOF)
            return free(buf), printf("unexpected end of input\n"), NULL;
        if (c == '\\')
        {
            c = getc(stream);
            if (c == EOF)
                return free(buf), printf("unexpected end of input\n"), NULL;
            if (c != '\\' && c != '"')
                return free(buf), ungetc(c, stream), unexpected(stream), NULL;
        }
        if (size + 2 > cap)
            buf = realloc(buf, cap *= 2);
        buf[size++] = c;
    }
    buf[size] = '\0';
    return buf;
}

int argo(json *dst, FILE *stream)
{
    int c = peek(stream);

    if (isdigit(c) || c == '-')
    {
        if (fscanf(stream, "%d", &dst->integer) != 1)
            return unexpected(stream), -1;
        dst->type = INTEGER;
        return 1;
    }
    if (c == '"')
    {
        getc(stream);
        char *str = parse_str(stream);
        if (!str)
            return dst->type = INTEGER, -1;
        dst->type = STRING;
        dst->string = str;
        return 1;
    }
    if (c == '{')
    {
        getc(stream);
        dst->type = MAP;
        dst->map.data = NULL;
        dst->map.size = 0;
        if (accept(stream, '}'))
            return 1;
        while (1)
        {
            if (!expect(stream, '"'))
                return -1;
            char *key = parse_str(stream);
            if (!key || !expect(stream, ':'))
                return free(key), -1;
            json value = {.type = INTEGER};
            if (argo(&value, stream) != 1)
                return free(key), -1;
            dst->map.data = realloc(dst->map.data, sizeof(pair) * (dst->map.size + 1));
            dst->map.data[dst->map.size++] = (pair){key, value};
            if (accept(stream, '}'))
                return 1;
            if (!expect(stream, ','))
                return -1;
        }
    }
    unexpected(stream);
    return -1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    FILE *stream = fopen(argv[1], "r");
    json file = {.type = INTEGER};
    if (argo(&file, stream) != 1)
        return free_json(file), 1;
    serialize(file);
    printf("\n");
}