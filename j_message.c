#include <stdio.h>

void send_file_is_not_found(char *file_name) {
    printf("\nInput file %s not found or not correct format command_chunk \"run.exe input.txt output.txt\".\n"
           "Name input/output files set default (input.txt/output.txt)\n", file_name);
}

void print_j_commands() {
    printf("\n Choose way of running program: \n"

           " full       Full running \n"
           " count      Running count of steps \n"
           " sbs        Run code step by step \n"
           " sbs -deb   Run code step by step with printing results \n"
           " exit       exit from program\n");
}

