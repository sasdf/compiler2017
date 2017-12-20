#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "header.h"
#include "symbolTable.h"
#include "macros.h"

typedef int REG;

void codeGeneration(AST_NODE *root);
void genProgramNode(AST_NODE *root);
void genVariableDeclList(AST_NODE *declListNode);
void genTypeDecl(AST_NODE *typeDeclNode);
void genVariableDecl(AST_NODE *variableDeclNode);
void genFunctionDecl(AST_NODE *functionDeclNode);
void countDeclListInBlock(AST_NODE *curr, int* size);
void countVariableListSize(AST_NODE *declListNode, int* size);
void countVariableSize(AST_NODE *declNode, int* size);
void genBlock(AST_NODE *block);
void genFunctionPrologue(int size);
void genFunctionEpilogue(int size, DATA_TYPE returnType);
void genStmtList(AST_NODE *stmtList);
void genStmt(AST_NODE *stmt);
void genWhile(AST_NODE *whileNode);
void genAssign(AST_NODE *assignNode);
void genIf(AST_NODE *ifNode);
void genFunctionCall(AST_NODE *functionCallNode);
void genReturn(AST_NODE *returnNode);

REG getReg();
void freeReg(REG reg);
REG genExprRelated(AST_NODE *exprRelated);
REG genRelopExpr(AST_NODE *relopExpr);
REG genVariableRef(AST_NODE *idNode);
REG genConstValue(AST_NODE *constValueNode);

FILE *output;

void codeGeneration(AST_NODE *root)
{
    output = fopen("output.s", "w");
    genProgramNode(root);
    fclose(output);
    return;
}

void genProgramNode(AST_NODE *root)
{
    AST_NODE *it = root->child;
    forEach(it){
        if (it->nodeType == VARIABLE_DECL_LIST_NODE){
            fprintf(output, ".data\n");
            genVariableDeclList(it);
        } else if (it->nodeType == DECLARATION_NODE){
            fprintf(output, ".text\n");
            genFunctionDecl(it);
        } else {
            assert("not variable nor function declare" == 0);
        }
    }
}

void genVariableDeclList(AST_NODE *declListNode)
{
    AST_NODE *it = declListNode->child;
    forEach(it){
        assert(it->nodeType == DECLARATION_NODE);
        switch (getDeclKind(it)){
            case TYPE_DECL:
                genTypeDecl(it->child);
                break;
            case VARIABLE_DECL:
                genVariableDecl(it->child);
                break;
            default:
                printf("Undefined variable list kind\n");
        }
    }
}

void genTypeDecl(AST_NODE *typeDeclNode)
{
    // Nothing to do
    return;
}

int getArrayCount(AST_NODE *dim){
    int size = 1;
    forEach(dim){
        size *= getExprValue(dim);
    }
    return size;
}

void genVariableDecl(AST_NODE *variableDeclNode)
{
    AST_NODE *it = variableDeclNode;
    unpack(it, type, id_list);
    forEach(id_list){
        if (id_list->child){
            int size = getArrayCount(id_list->child)*4;
            fprintf(output, "_g_%s: .space %d\n", getIDName(id_list), size);
        } else{
            fprintf(output, "_g_%s: .word 0\n", getIDName(id_list));
        }
    }
}

void genFunctionDecl(AST_NODE *functionDeclNode)
{
    AST_NODE *it = functionDeclNode->child;
    unpack(it, head, id, param, block);

    TypeDescriptor *td = getTypeDescriptor(head);
    DATA_TYPE returnType = td->properties.dataType;
    fprintf(output, "_%s:\n", getIDName(id));
    // this hw only has parameterless function call
    // no need to proceed param
    
    int size = 0;
    // size = ...
    countDeclListInBlock(block, &size);
    printf("local stack size %d\n", size);
    genFunctionPrologue(size);

    genBlock(block);

    genFunctionEpilogue(size, returnType);
}

void genBlock(AST_NODE *block)
{
    assert(block->nodeType == BLOCK_NODE);
    
    AST_NODE *it = block->child;
    // block -> decl_list stmt_list
    if (it->rightSibling){
        unpack(it, decl_list, stmt_list);
        assert(decl_list->nodeType == VARIABLE_DECL_LIST_NODE);
        assert(stmt_list->nodeType == STMT_LIST_NODE);
    }
    // block -> decl_list | stmt_list
    else {
        if (it->nodeType == VARIABLE_DECL_LIST_NODE){
            // nothing to do
        } else if (it->nodeType == STMT_LIST_NODE){
            genStmtList(it);
        } else {
            puts("Undefined block child nodeType");
        }
    }

    //__asm__("int3");
}

void countDeclListInBlock(AST_NODE *curr, int* size)
{
    if (curr->child){
        AST_NODE *it = curr->child;
        forEach(it){
            if (it->nodeType == VARIABLE_DECL_LIST_NODE){
                countVariableListSize(it, size);
            }
            countDeclListInBlock(it, size);
        }
    }
}

void countVariableListSize(AST_NODE *declListNode, int* size)
{
    AST_NODE *it = declListNode->child;
    forEach(it){
        assert(it->nodeType == DECLARATION_NODE);
        switch (getDeclKind(it)){
            case TYPE_DECL:
                // nothing to do
                break;
            case VARIABLE_DECL:
                countVariableSize(it->child, size);
                break;
            default:
                printf("Undefined variable list kind\n");
        }
    }
}

void countVariableSize(AST_NODE *declNode, int* size)
{
    AST_NODE *it = declNode;
    unpack(it, type, id_list);
    assert ( id_list->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(id_list) != NULL );
    assert ( getIDAttr(id_list)->attributeKind == VARIABLE_ATTRIBUTE );
    forEach(id_list){
        setIDOffset(id_list, *size);
        if (id_list->child){
            *size += getArrayCount(id_list->child)*4;
        } else{
            *size += 4;
        }
    }
}

void genFunctionPrologue(int size)
{

}

void genFunctionEpilogue(int size, DATA_TYPE returnType)
{

}

void genStmtList(AST_NODE *stmtList)
{
    AST_NODE *it = stmtList->child;
    forEach(it){
        genStmt(it);
    }
}

void genStmt(AST_NODE *stmt)
{
    switch(stmt->nodeType){
        case BLOCK_NODE:
            genBlock(stmt);
            break;
        case STMT_NODE:
            switch(getStmtKind(stmt)){
                case WHILE_STMT:
                    genWhile(stmt->child);
                    break;
                case ASSIGN_STMT:
                    genAssign(stmt->child);
                    break;
                case IF_STMT:
                    genIf(stmt->child);
                    break;
                case FUNCTION_CALL_STMT:
                    genFunctionCall(stmt->child);
                    break;
                case RETURN_STMT:
                    genReturn(stmt->child);
                    break;
                default:
                    puts("Undefined statement");
            }
            break;
        case NUL_NODE:
            // nothing to do
            break;
        default:
            puts("Undefined stmt node");
    }
}

void genWhile(AST_NODE *whileNode)
{

}

void genAssign(AST_NODE *assignNode)
{

}

void genIf(AST_NODE *ifNode)
{

}

void genFunctionCall(AST_NODE *functionCallNode)
{

}

void genReturn(AST_NODE *returnNode)
{
    unpack(returnNode->child, exprRelated);
    REG reg = genExprRelated(exprRelated);
    // TODO; mov w0, %reg
}

REG genExprRelated(AST_NODE *exprRelated)
{
    switch(exprRelated->nodeType)
    {
    case EXPR_NODE:
        return genRelopExpr(exprRelated);
        break;
    case STMT_NODE:
        //function call
        // TODO
        /* return genFunctionCall(exprRelated); */
        break;
    case IDENTIFIER_NODE:
        return genVariableRef(exprRelated);
        break;
    case CONST_VALUE_NODE:
        return genConstValue(exprRelated);
        break;
    default:
        printf("Unhandle case in void processExprRelatedNode(AST_NODE* exprRelatedNode)\n");
        exprRelated->dataType = ERROR_TYPE;
        break;
    }
}

#define NUM_REG 28
int isRegInUse[NUM_REG];

REG getReg()
{
    for (int i=1; i<NUM_REG; ++i) {
        if (!isRegInUse[i]) {
            isRegInUse[i] = 1;
            return i;
        }
    }
    assert ( 0 && "No more register" );
}

void freeReg(REG reg)
{
    assert ( reg >= 1 && reg < NUM_REG );
    isRegInUse[reg] = 0;
}

REG genRelopExpr(AST_NODE *relopExpr)
{

}

REG genVariableRef(AST_NODE *idNode)
{
    assert ( idNode->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(idNode) != NULL );
    assert ( getIDAttr(idNode)->attributeKind == VARIABLE_ATTRIBUTE );
    TypeDescriptor* typeDescriptor = getIDTypeDescriptor(idNode);
    REG reg = getReg();
    if (typeDescriptor->global) {
        // TODO: mov %reg, %getIDName(idNode)
    } else {
        // TODO: mov %reg, [x29, #%getIDOffset(idNode)]
    }
    return reg;
}

REG genConstValue(AST_NODE *constValueNode)
{
    assert ( constValueNode->nodeType == CONST_VALUE_NODE );
    REG reg = getReg();
    // TODO: mov %reg, %const;
    return reg;

}

