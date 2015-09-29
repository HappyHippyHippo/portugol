#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast.h>

AST_Node*
ast_file(void)
{
    AST_SourcePos pos;
    memset(&pos, 0, sizeof(AST_SourcePos));

    AST_Node* file = ast_scope(pos);
    file->type = AST_FILE;

    return file;
}

Variant
ast_file_execute(AST_Node* node,
                 Runtime* runtime)
{
    AST_Scope* aux = (AST_Scope*) node;

    for (size_t idx = 0; idx < aux->inst.count; ++idx) {
        switch (aux->inst.list[idx]->type)
        {
            case AST_FUNCTION:
            {
                AST_Function* inst = (AST_Function*) aux->inst.list[idx];
                runtime_heap_push(runtime, inst->name, variant_init_function(inst));
                break;
            }
            case AST_DECL_BOOLEAN:
            case AST_DECL_INT32:
            case AST_DECL_FLOAT32:
            case AST_DECL_TEXT:
            {
                AST_Decl* inst = (AST_Decl*) aux->inst.list[idx];
                Variant value  = ast_execute(inst->value, runtime);
                runtime_heap_push(runtime, inst->name, value);
                variant_uninit(&value);
                break;
            }
            default:
                printf("Invalid global instruction type found : %d\n", aux->inst.list[idx]->type);
                break;
        }
    }

    Variant* program;
    if ((program = runtime_get(runtime, "programa")) == NULL)
        return variant_init_int32(0);

    runtime_scope_push_named(runtime, 1, "programa");
    Variant result = ast_execute((AST_Node*) program->value.function, runtime);
    runtime_scope_pop(runtime);

    return result;
}

void
ast_file_print(AST_Node* node,
               int level,
               char* prefix)
{
    printf("-------------------------------- AST Tree ---------------------------------\n");
    printf("file\n");
    for (size_t idx = 0; idx < ((AST_Scope*) node)->inst.count; ++idx)
        ast_print(((AST_Scope*) node)->inst.list[idx], level + 1, "");
    printf("---------------------------------------------------------------------------\n");
    printf("\n");
}

void
ast_file_destroy(AST_Node** node)
{
    ast_scope_destroy(node);
}
