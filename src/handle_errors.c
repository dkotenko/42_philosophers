#include "philosophers.h"



void handle_error(char *message)
{
    printf("%sError: %s%s", RED, message, RESET);
    exit(0);
}

void handle_error_int(char *message, int d)
{
    printf("%sError: %s: %d%s", RED, message, d, RESET);
    exit(0);
}

void handle_error_str(char *message, char *s)
{
    printf("%sError: %s: %s%s", RED, message, s, RESET);
    exit(0);
}
