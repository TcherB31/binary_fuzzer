#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: %s <target_elf_binary> <target_input_txt_file>\n", argv[0]);
        return 1;
    }

    char *target_elf_binary = argv[1];
    char *target_input_txt_file = argv[2];

    // Generate test cases using radamsa fuzzer
    char cmd[MAX_INPUT_SIZE];
    snprintf(cmd, MAX_INPUT_SIZE, "radamsa %s -o test_case.txt", target_input_txt_file);
    system(cmd);

    // Execute the target binary with the generated test cases
    FILE *fp = fopen("test_case.txt", "r");
    if (fp == NULL) {
        printf("Error: Failed to open test_case.txt\n");
        return 1;
    }

    char input[MAX_INPUT_SIZE];
    while (fgets(input, MAX_INPUT_SIZE, fp) != NULL) {
        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;

        // Execute the target binary
        pid_t pid = fork();
        if (pid == 0) {
            execl(target_elf_binary, target_elf_binary, input, NULL);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
    }

    fclose(fp);

    return 0;
}