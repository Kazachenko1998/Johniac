#ifndef RUN_J_COMMANDS_H
#define RUN_J_COMMANDS_H

_Bool is_full_command(char answer[]);

_Bool is_count_command(char answer[]);

_Bool is_step_by_step_command(char answer[]);

_Bool is_step_by_step_with_debug_command(char *answer);

_Bool is_exit_command(char answer[]);

_Bool is_help_command(char answer[]);

_Bool is_empty_string(char answer[]);

#endif //RUN_J_COMMANDS_H
