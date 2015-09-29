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
    Variant result = ast_execute(ast, runtime);

    runtime_print(runtime);

    switch (result.type)
    {
        case VBOOLEAN:  printf("program result value : boolean(%d)",  result.value.boolean);    break;
        case VINT32:    printf("program result value : int32(%d)",    result.value.int32);      break;
        case VFLOAT32:  printf("program result value : float32(%f)",  result.value.float32);    break;
        case VTEXT:     printf("program result value : text(%s)",     result.value.text);       break;
        case VFUNCTION: printf("program result value : function(%p)", result.value.function);   break;
    }
    printf("\n");
    variant_uninit(&result);

    runtime_destroy(&runtime);
    ast_destroy(&ast);

    return 0;
}
