#include <internal/portugol/ast/ast_node.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Type
ast_get_type(AST_Node* node)
{
    if (node)
    {
        /* return the node type */
        return node->type;
    }

    return AST_UNKNOWN;
} /* end of : ASTType
              ast_get_type(AST_Node* node) */

AST_Pos
ast_get_position(AST_Node* node)
{
    if (node)
    {
        /* return the node position information */
        return node->pos;
    }

    AST_Pos pos = {{0, 0}, {0, 0}};
    return pos;
} /* end of : AST_Pos
              ast_get_position(AST_Node* node) */

VType
ast_get_return_type(AST_Node* node)
{
    return VUNKNOWN;
} /* end of : VType
              ast_get_return_type(AST_Node* node) */

Variant*
ast_execute(AST_Node* node,
            Variant* result)
{
    if (node)
    {
        /* redirect to the node execution function */
        return node->vtable.execute(node, result);
    }

    return result;
} /* end of : Variant*
              ast_execute(AST_Node* node,
                          Variant* result) */

void
ast_output(AST_Node* node,
           const size_t level,
           const char* prefix)
{
    if (node)
    {
        /* redirect to the node output function */
        node->vtable.output(node, level, prefix);
    }
} /* end of : void
              ast_output(AST_Node* node,
                         const size_t level,
                         const char* prefix) */

void
ast_destroy(AST_Node** node)
{
    if (   node
        && *node)
    {
        /* redirect to the node destroy function */
        (*node)->vtable.destroy(node);
    }
} /* end of : void
              ast_destroy(AST_Node** node) */
