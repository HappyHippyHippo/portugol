#include <getopt.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <portugol/ast/ast.h>
#include <portugol/lex/lex.h>
#include <portugol/runtime.h>
#include <mem.h>

int main(int argc, char** argv) {
    int32_t exit_result = 0;

    int opt;
    int opt_print_ast = 0;
    char* opt_file = "programa.portugol";

    while ((opt = getopt(argc, argv, "f:p")) != -1) {
        switch (opt) {
        case 'p':
            opt_print_ast = 1;
            break;
        case 'f':
            opt_file = optarg;
            break;
        default: /* '?' */
            fprintf(stderr,
                    "Usage: %s [-f source] [-p]\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (ast_root_load(opt_file))
    {
        if (opt_print_ast)
        {
            printf("ASTree :\n");
            ast_root_output();
            printf("\n");
        }

        Variant result;
        ast_root_execute(&result);

        exit_result = result.value.vint32;
        variant_uninit(&result);
    }

    return exit_result;
}
