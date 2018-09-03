#include <mem.h>
#include "j_commands.h"

_Bool is_full_command(char answer[]) {
    return strcmp(answer, "full\n") == 0;
}

_Bool is_count_command(char answer[]) {
    return strcmp(answer, "count\n") == 0;
}

_Bool is_step_by_step_command(char answer[]) {
    return strcmp(answer, "sbs\n") == 0;
}

_Bool is_step_by_step_with_debug_command(char *answer) {
    return strcmp(answer, "sbs -deb\n") == 0;
}


_Bool is_exit_command(char answer[]) {
    return strcmp(answer, "exit\n") == 0;
}

_Bool is_help_command(char answer[]) {
    return strcmp(answer, "help\n") == 0 || strcmp(answer, "h") == 0;
}

_Bool is_empty_string(char answer[]) {
    return strcmp(answer, "") == 0;
}