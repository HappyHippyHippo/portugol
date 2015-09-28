#include <stdio.h>
#include <stdlib.h>

#include <portugol/ast.h>
#include <portugol/variant.h>
#include <portugol/runtime.h>

extern int yyparse();
extern int yyset_in(FILE*);

int main(int argc, char **argv)
{
    // TESTE DE PARSING
    FILE* fp = fopen((argc == 1 ? "code.portugol" : argv[1]), "r");
    if (fp == NULL) {
        perror("Error opening source file : ");
        exit(-1);
    }

    yyset_in(fp);
    yyparse();
    fclose(fp);

    if (ast_error)
        return -1;

    ast_print(ast, 0, "");

    Runtime* runtime = runtime_create();
    ast_execute(ast, runtime);

    runtime_print(runtime);
    runtime_destroy(&runtime);

    ast_destroy(&ast);

    return 0;
}
