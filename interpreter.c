#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libtcc.h>
#include <regex.h>

void readfile(char*, char*);
char *line_analyzer(char *);


char *line_analyzer(char *to_parse)
{
    if (*to_parse == '#')
        return to_parse;
    return "0\n";
}

void readfile(char *source_file, char *string_code)
{
    FILE *fp;
    char *line;
    char *mode = "r";
    size_t len = 0;
    ssize_t read;

    int tmp = 0;

    fp = fopen(source_file, mode);

    if (fp == NULL) {
        perror("File doesn't exist");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        if (read > 1) {
            string_code = realloc(string_code, 128 * sizeof(char));
            strcat(string_code, line_analyzer(line));
        } else {
            string_code = realloc(string_code, 128 * sizeof(char));
            strcat(string_code, "\n");
        }
    }

    printf("%s\n", string_code);

    fclose(fp);

    if (line)
        free(line);
}

void main(int ac, char **av)
{
    // char *result = malloc(1);
    // *result = '\0';

    // readfile(av[1], result);

    // printf("%s\n", result);

    regex_t preg;
    int err, match;
    const char *str_request = "ASSIGN a 3";
    const char *regex = "^ASSIGN[ ]+[$][[:alnum:]]+[ ]+[[:digit:]]";

    err = regcomp (&preg, regex, REG_NOSUB | REG_EXTENDED);

    match = regexec(&preg, str_request, 0, NULL, 0);

    printf("%d\n", match);

    return;
}