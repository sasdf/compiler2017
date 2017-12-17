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
        } else if (it->nodeType == FUNCTION_DECL){
            genFunctionDecl(it);
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
    return;
}

int getArraySize(AST_NODE *dim){
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
            int size = getArraySize(id_list->child);
            fprintf(output, "_g_%s: .space %d\n", getIDName(id_list), size);
        } else{
            fprintf(output, "_g_%s: .word 0\n", getIDName(id_list));
        }
    }
}

void genFunctionDecl(AST_NODE *functionDeclNode)
{
    assert(1);
}

