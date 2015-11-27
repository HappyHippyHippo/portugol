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

    ast_root_load("bin/programa.portugol");

    if (!ast_error)
    {
        ast_root_output();
        printf("\n");

        Variant result;
        ast_root_execute(&result);

        exit_result = result.value.vint32;
        variant_uninit(&result);
    }
    else
    {
        printf("Loading error ...\n");
    }

    return exit_result;
}
