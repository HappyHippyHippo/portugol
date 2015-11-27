#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <portugol/ast/ast.h>
#include <portugol/lex/lex.h>
#include <portugol/runtime.h>
#include <mem.h>

#define DEFAULT_SOURCE_FILE "bin/programa.portugol"

int main(int argc, char** argv) {
    ast_root_load(argc > 1 ? argv[1] : DEFAULT_SOURCE_FILE);

    ast_root_output();
    printf("\n");

    Variant result;
    ast_root_execute(&result);
    printf("result : "); variant_output(&result); printf("\n");
    variant_uninit(&result);

    return 0;
}
