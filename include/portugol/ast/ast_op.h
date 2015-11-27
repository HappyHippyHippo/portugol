#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_add(const AST_Pos pos,
           AST_Node* op1,
           AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_subtract(const AST_Pos pos,
                AST_Node* op1,
                AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_multiply(const AST_Pos pos,
                AST_Node* op1,
                AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_divide(const AST_Pos pos,
              AST_Node* op1,
              AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_remainder(const AST_Pos pos,
                 AST_Node* op1,
                 AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_equal(const AST_Pos pos,
             AST_Node* op1,
             AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_inequal(const AST_Pos pos,
               AST_Node* op1,
               AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_greater(const AST_Pos pos,
               AST_Node* op1,
               AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_greater_or_equal(const AST_Pos pos,
                        AST_Node* op1,
                        AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_lesser(const AST_Pos pos,
              AST_Node* op1,
              AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_lesser_or_equal(const AST_Pos pos,
                       AST_Node* op1,
                       AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_and(const AST_Pos pos,
           AST_Node* op1,
           AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_or(const AST_Pos pos,
          AST_Node* op1,
          AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_xor(const AST_Pos pos,
           AST_Node* op1,
           AST_Node* op2);

/// @brief
///
/// @param pos
/// @param op
/// @return
AST_Node*
ast_op_negate(const AST_Pos pos,
              AST_Node* op);

/// @brief
///
/// @param pos
/// @param op
/// @return
AST_Node*
ast_op_negative(const AST_Pos pos,
                AST_Node* op);

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @return
AST_Node*
ast_op_assign(const AST_Pos pos,
              AST_Node* op1,
              AST_Node* op2);
