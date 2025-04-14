#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "syntax : %s <file1> [<file2>...]\n", argv[0]);
        return 1;
    }

    uint32_t total = 0;
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            fprintf(stderr, "Could not open file: %s\n", argv[i]);
            return 1;
        }

        uint32_t num;
        size_t read_bytes = fread(&num, sizeof(uint32_t), 1, fp);
        if (read_bytes != 1) {
            fprintf(stderr, "Failed to read 4 bytes from file: %s\n", argv[i]);
            fclose(fp);
            return 1;
        }

        fclose(fp);

        uint32_t host_num = ntohl(num);
        printf("%u(0x%08x)", host_num, host_num);

        if (i < argc - 1)
            printf(" + ");

        total += host_num;
    }

    printf(" = %u(0x%08x)\n", total, total);
    return 0;
}
