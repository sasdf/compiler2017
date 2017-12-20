#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "header.h"
#include "symbolTable.h"
#include "macros.h"

void codeGeneration(AST_NODE *root);
void genProgramNode(AST_NODE *root);
void genVariableDeclList(AST_NODE *declListNode);
void genTypeDecl(AST_NODE *typeDeclNode);
void genVariableDecl(AST_NODE *variableDeclNode);
void genFunctionDecl(AST_NODE *functionDeclNode);
void genBlock(AST_NODE *block, DATA_TYPE returnType);
int getVariableListSize(AST_NODE *declListNode);
int getVariableSize(AST_NODE *declNode);
void genFunctionPrologue(int size);
void genFunctionEpilogue(int size, DATA_TYPE returnType);
void genStmt(AST_NODE *stmt);

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

    SymbolTableEntry *st = getTypeEntry(head);
    //FunctionSignature *fs = getHeadFunctionSignature(head);
    FunctionSignature *fs = getFunctionSignature(functionDeclNode);
    __asm__("int3");
    DATA_TYPE returnType = getHeadFunctionSignature(head)->returnType;
    fprintf(output, "_%s:\n", getIDName(id));
    // this hw only has parameterless function call
    // no need to proceed param
    genBlock(block, returnType);
}

void genBlock(AST_NODE *block, DATA_TYPE returnType)
{
    assert(block->nodeType == BLOCK_NODE);
    
    int size = 0;
    // size = ...
    AST_NODE *it = block->child;
    if (it->nodeType == VARIABLE_DECL_LIST_NODE){
        size = getVariableListSize(it);
    }
    printf("local stack size %d\n", size);
    genFunctionPrologue(size);

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
            genStmt(it);
        } else {
            puts("Undefined block child nodeType");
        }
    }

    genFunctionEpilogue(size, returnType);
    //__asm__("int3");
}

int getVariableListSize(AST_NODE *declListNode)
{
    int size = 0;
    AST_NODE *it = declListNode->child;
    forEach(it){
        assert(it->nodeType == DECLARATION_NODE);
        switch (getDeclKind(it)){
            case TYPE_DECL:
                // nothing to do
                break;
            case VARIABLE_DECL:
                size += getVariableSize(it->child);
                break;
            default:
                printf("Undefined variable list kind\n");
        }
    }
    return size;
}

int getVariableSize(AST_NODE *declNode)
{
    int size = 0;
    AST_NODE *it = declNode;
    unpack(it, type, id_list);
    forEach(id_list){
        if (id_list->child){
            size += getArrayCount(id_list->child)*4;
        } else{
            size += 4;
        }
    }
    return size;
}

void genFunctionPrologue(int size)
{

}

void genFunctionEpilogue(int size, DATA_TYPE returnType)
{

}

void genStmt(AST_NODE *stmt)
{

}
