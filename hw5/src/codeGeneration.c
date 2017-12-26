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
void genAssignStmt(AST_NODE *assignNode);
void genIf(AST_NODE *ifNode);
void genFunctionCall(AST_NODE *functionCallNode);
void genReturn(AST_NODE *returnNode);
void genWrite(AST_NODE *functionCallNode);

REG getReg();
void freeReg(REG reg);
REG genExprRelated(AST_NODE *exprRelated);
REG genRelopExpr(AST_NODE *relopExpr);
REG genVariableRef(AST_NODE *idNode);
REG genConstValue(AST_NODE *constValueNode);

int genIntLiteral(int i);
int genFloatLiteral(float i);
void genAlignment();

FILE *output;
int const_n;

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
        setIDGlobal(id_list, 1);
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
    fprintf(output, "_start_%s:\n", getIDName(id));
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
        genStmtList(stmt_list);
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
        //printf("%s offset %d\n", getIDName(id_list), getIDOffset(id_list));
        setIDGlobal(id_list, 0);
        if (id_list->child){
            *size += getArrayCount(id_list->child)*4;
        } else{
            *size += 4;
        }
    }
}

void genFunctionPrologue(int size)
{
    fprintf(output, "str x30, [sp, #-8]\n");
    fprintf(output, "str x29, [sp, #-16]\n");
    int offset = 16;
    for(int i = 19; i <= 29; ++i){
        offset += 8;
        fprintf(output, "str x%d, [sp, #%d]\n", i, -offset);
    }
    fprintf(output, "add x29, sp, #-104\n");
    fprintf(output, ".data\n");
    fprintf(output, "_AR_SIZE_%d: .word %d\n", const_n, size);
    fprintf(output, ".align 3\n");
    fprintf(output, ".text\n");
    fprintf(output, "ldr w19, _AR_SIZE_%d\n", const_n);
    fprintf(output, "sub sp, x29, w19\n");
    ++const_n;
    //_offset = 0
}

// does not need size actually
void genFunctionEpilogue(int size, DATA_TYPE returnType)
{
    fprintf(output, "add sp, x29, #-104\n");
    int offset = 0;
    for (int i = 29; i >= 19; ++i){
        fprintf(output, "ldr x%d, [x29, #%d]\n", i, offset);
        offset += 8;
    }
    fprintf(output, "ldr x30, [sp, #8]\n");
    fprintf(output, "ldr x29, [sp, #16]\n");
    fprintf(output, "ret x30\n");
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
                    genAssignStmt(stmt->child);
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
    AST_NODE *it = whileNode;
    unpack(it, test, stmt);
    int while_n = const_n++;

    fprintf(output, "_WHILE_%d:\n", while_n);
    if (test->nodeType == STMT_NODE && getStmtKind(test) == ASSIGN_STMT){
        genAssignStmt(test);
        test = test->child;
    }
    REG reg = genExprRelated(test);
    if (test->dataType == FLOAT_TYPE)
        fprintf(output, "fcvtzs w%d, s%d\n", reg, reg);

    fprintf(output, "cmp w%d, #0\n", reg);
    freeReg(reg);
    fprintf(output, "beq _WHILE_END_%d\n", while_n);
    genStmt(stmt);
    fprintf(output, "b _WHILE_%d\n", while_n);
    fprintf(output, "_WHILE_END_%d:\n", while_n);
}

void genAssignStmt(AST_NODE *assignNode)
{
    AST_NODE *it = assignNode;
    unpack(it, id, relop_expr);
    // TODO variable reference
    REG right_reg = genExprRelated(relop_expr);
    // stack[offset] = right_reg
}

void genIf(AST_NODE *ifNode)
{
    AST_NODE *it = ifNode;
    unpack(it, test, stmt, elseStmt);
    int if_n = const_n++;
    
    fprintf(output, "_IF_%d:\n", if_n);
    if (test->nodeType == STMT_NODE && getStmtKind(test) == ASSIGN_STMT){
        genAssignStmt(test);
        test = test->child;
    }
    REG reg = genExprRelated(test);
    if (test->dataType == FLOAT_TYPE)
        fprintf(output, "fcvtzs w%d, s%d\n", reg, reg);

    fprintf(output, "cmp w%d, #0\n", reg);
    freeReg(reg);
    fprintf(output, "beq _ELSE_%d\n", if_n);
    genStmt(stmt);
    fprintf(output, "b _END_IF_%d\n", if_n);
   

    fprintf(output, "_ELSE_%d:\n", if_n);
    //if (elseStmt->nodeType != NUL_NODE)
    genStmt(elseStmt);
    fprintf(output, "_END_IF_%d:\n", if_n);
}

void genWrite(AST_NODE *functionCallNode){
    AST_NODE *it = functionCallNode;
    unpack(it, id, paramList);
    AST_NODE *param = paramList->child;
    
    REG reg = genExprRelated(param);
    switch(param->dataType){
        case INT_TYPE:
            fprintf(output, "mov w0, w%d\n", reg);
            fprintf(output, "bl _write_int\n");
            break;
        case FLOAT_TYPE:
            fprintf(output, "mov s0, s%d\n", reg);
            fprintf(output, "bl _write_float\n");
            break;
        case CONST_STRING_TYPE:
            fprintf(output, "mov x0, x%d\n", reg);
            fprintf(output, "bl _write_str\n");
            break;
    }
    freeReg(reg);
}

void genFunctionCall(AST_NODE *functionCallNode)
{
    AST_NODE *it = functionCallNode;
    unpack(it, id, param);

    char *name = getIDName(id);
    if (!strcmp(name, "write")){
        genWrite(functionCallNode);
    } else if (!strcmp(name, "read")){
        fprintf(output, "bl _read_int\n");
    } else if (!strcmp(name, "fread")){
        fprintf(output, "bl _read_float\n");
    } else {
        fprintf(output, "bl _start_%s\n", name);
    }
}

void genReturn(AST_NODE *returnNode)
{
    AST_NODE *it = returnNode;
    unpack(it, exprRelated);
    REG reg;
    if (exprRelated->nodeType != NUL_NODE){
        reg = genExprRelated(exprRelated);
    }

    AST_NODE *parent = returnNode;
    findParentDecl(parent, FUNCTION_DECL);
    FunctionSignature *fs = getHeadFunctionSignature(parent->child);
    switch(fs->returnType){
        case INT_TYPE:
            if (returnNode->dataType == INT_TYPE)
                fprintf(output, "mov w0, w%d\n", reg);
            else if (returnNode->dataType == FLOAT_TYPE){
                fprintf(output, "fmov s0, s%d\n", reg);
                fprintf(output, "fcvtzs w0, s0\n");
            } else {
                puts("return type error");
            }
            break;
        case FLOAT_TYPE:
            if (returnNode->dataType == INT_TYPE){
                fprintf(output, "mov w0, w%d\n", reg);
                fprintf(output, "scvtf s0, w0\n");
            } else if (returnNode->dataType == FLOAT_TYPE){
                fprintf(output, "fmov s0, s%d\n", reg);
            } else {
                puts("return type error");
            }
            break;
        case VOID_TYPE:
            break;
        default:
            puts("Undefined return type");
            break;
    }
    freeReg(reg);
}

REG genExprRelated(AST_NODE *exprRelated)
{
    REG reg;
    switch(exprRelated->nodeType)
    {
    case EXPR_NODE:
        return genRelopExpr(exprRelated);
        break;
    case STMT_NODE:
        //function call
		genFunctionCall(exprRelated);
        reg = getReg();
        switch(exprRelated->dataType){
          case INT_TYPE:
            fprintf(output, "mov w%d, w0\n", reg);
            break;
          case FLOAT_TYPE:
            fprintf(output, "fmov s%d, s0\n", reg);
            break;
        }
        return reg;
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


int genIntLiteral(int i){
    fprintf(output, ".data\n");
    fprintf(output, "_CONST_%d: .word %d\n", const_n, i);
    genAlignment();
    fprintf(output, ".text\n");
    return const_n++;
}

int genFloatLiteral(float f){
    fprintf(output, ".data\n");
    fprintf(output, "_CONST_%d: .float %f\n", const_n, f);
    genAlignment();
    fprintf(output, ".text\n");
    return const_n++;
}

void genAlignment(){
    fprintf(output, ".align 3\n");
}

REG genRelopExpr(AST_NODE *relopExpr)
{

}

REG genArrayRef(AST_NODE *idNode)
{
    assert ( idNode->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(idNode) != NULL );
    assert ( getIDAttr(idNode)->attributeKind == VARIABLE_ATTRIBUTE );
    TypeDescriptor* typeDescriptor = getIDTypeDescriptor(idNode);
    REG reg = getReg();
    if (typeDescriptor->global) {
        fprintf(output, ".data\n");
        // TODO: mov %reg, %getIDName(idNode)
    } else {
        // TODO: mov %reg, [x29, #%getIDOffset(idNode)]
    }
    return reg;
}

REG genVariableRef(AST_NODE *idNode)
{
    assert ( idNode->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(idNode) != NULL );
    assert ( getIDAttr(idNode)->attributeKind == VARIABLE_ATTRIBUTE );
    TypeDescriptor* typeDescriptor = getIDTypeDescriptor(idNode);

    REG reg = getReg();

    if(getIDKind(idNode) == ARRAY_ID){
        return genArrayRef(idNode);
    }else{
      if(typeDescriptor->global){
        if(idNode->dataType == INT_TYPE){
          fprintf(output, "ldr w%d, _%s\n", reg, getIDName(idNode));
        }else{
          fprintf(output, "ldr s%d, _%s\n", reg, getIDName(idNode));
        }
      }else{
        int offset = getIDOffset(idNode);
        int id = genIntLiteral(offset);
        fprintf(output, "ldr w%d, _const_%d\n", reg, id);
        fprintf(output, "sub x%d, x29, x%d\n", reg, reg);
        if(idNode->dataType == INT_TYPE){
          fprintf(output, "ldr w%d, [x%d, #0]\n", reg, reg);
        }else{
          fprintf(output, "ldr s%d, [x%d, #0]\n", reg, reg);
        }
      }
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

/* REG a() { */
    /* case IDENTIFIER_NODE: */
      /* // emitVariableRValue(exprRelatedNode); */
      /* { */
        /* AST_NODE* idNode = exprRelatedNode; */
        /* SymbolTableEntry *symbolTableEntry = retrieveSymbol(idNode->semantic_value.identifierSemanticValue.identifierName); */
        /* idNode->semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry; */
        /* TypeDescriptor *typeDescriptor = idNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor; */
        /* if(idNode->semantic_value.identifierSemanticValue.kind == NORMAL_ID){ */
          /* idNode->dataType = typeDescriptor->properties.dataType; */
          /* if(symbolTableEntry->attribute->global){ */
            /* if(idNode->dataType == INT_TYPE){ */
              /* fprintf(adotout, "ldr w%d, _%s\n", reg, idName(idNode)); */
            /* }else{ */
              /* fprintf(adotout, "ldr s%d, _%s\n", reg, idName(idNode)); */
            /* } */
          /* }else{ */
            /* int offset = symbolTableEntry->attribute->offset; */
            /* int id = emitIntLiteral(offset); */
            /* fprintf(adotout, "ldr w%d, _const_%d\n", reg, id); */
            /* fprintf(adotout, "sub x%d, x29, x%d\n", reg, reg); */
            /* if(idNode->dataType == INT_TYPE){ */
              /* fprintf(adotout, "ldr w%d, [x%d, #0]\n", reg, reg); */
            /* }else{ */
              /* fprintf(adotout, "ldr s%d, [x%d, #0]\n", reg, reg); */
            /* } */
          /* } */
        /* }else{ */
          /* idNode->dataType = typeDescriptor->properties.arrayProperties.elementType; */
          /* int dimension = 0; */
          /* int * arrayDims = typeDescriptor->properties.arrayProperties.sizeInEachDimension; */
          /* AST_NODE *traverseDimList = idNode->child; */
          /* fprintf(adotout, "mov x%d, #0\n", reg); */
          /* while(traverseDimList){ */
            /* int id = emitIntLiteral(arrayDims[dimension]); */
            /* int _reg = getReg(); */
            /* fprintf(adotout, "ldr x%d, _const_%d\n", _reg, id); */
            /* fprintf(adotout, "mul x%d, x%d, x%d\n", reg, reg, _reg); */
            /* freeReg(_reg); */
            /* int indexReg = emitExprRelatedNode(traverseDimList); */
            /* fprintf(adotout, "lsl x%d, x%d, #2\n", indexReg, indexReg); */
            /* fprintf(adotout, "add x%d, x%d, x%d\n", reg, reg, indexReg); */
            /* freeReg(indexReg); */
            /* traverseDimList = traverseDimList->rightSibling; */
            /* ++dimension; */
          /* } */
          /* int offset = symbolTableEntry->attribute->offset; */
          /* int _reg = getReg(); */
          /* if(symbolTableEntry->attribute->global){ */
            /* fprintf(adotout, "ldr x%d, =_%s\n", _reg, idName(idNode)); */
          /* }else{ */
            /* fprintf(adotout, "add x%d, x%d, x%d\n", reg, reg, 29); */
            /* int id = emitIntLiteral(offset); */
            /* fprintf(adotout, "ldr x%d, _const_%d\n", _reg, id); */
            /* fprintf(adotout, "neg x%d, x%d\n", _reg, _reg); */
          /* } */
          /* freeReg(_reg); */
          /* fprintf(adotout, "add x%d, x%d, x%d\n", reg, reg, _reg); */
          /* if(idNode->dataType == INT_TYPE){ */
            /* fprintf(adotout, "ldr w%d, [x%d, #0]\n", reg, reg); */
          /* }else{ */
            /* fprintf(adotout, "ldr s%d, [x%d, #0]\n", reg, reg); */
          /* } */
        /* } */
      /* } */
      /* break; */
    /* case CONST_VALUE_NODE: */
      /* switch(exprRelatedNode->semantic_value.const1->const_type){ */
        /* case INTEGERC: */
          /* exprRelatedNode->dataType = INT_TYPE; */
          /* exprRelatedNode->semantic_value.exprSemanticValue.constEvalValue.iValue = */
            /* exprRelatedNode->semantic_value.const1->const_u.intval; */
          /* fprintf(adotout, ".data\n"); */
          /* fprintf(adotout, "_integer_const_%d: .word %d\n", _const, exprRelatedNode->semantic_value.const1->const_u.intval); */
          /* emitAlignment(); */
          /* fprintf(adotout, ".text\n"); */
          /* fprintf(adotout, "ldr w%d, _integer_const_%d\n", reg, _const); */
          /* _const++; */
          /* break; */
        /* case FLOATC: */
          /* exprRelatedNode->dataType = FLOAT_TYPE; */
          /* exprRelatedNode->semantic_value.exprSemanticValue.constEvalValue.fValue = */
            /* exprRelatedNode->semantic_value.const1->const_u.fval; */
          /* fprintf(adotout, ".data\n"); */
          /* fprintf(adotout, "_float_const_%d: .float %f\n", _const, exprRelatedNode->semantic_value.const1->const_u.fval); */
          /* emitAlignment(); */
          /* fprintf(adotout, ".text\n"); */
          /* fprintf(adotout, "ldr s%d, _float_const_%d\n", reg, _const); */
          /* _const++; */
          /* break; */
        /* case STRINGC: */
          /* exprRelatedNode->dataType = CONST_STRING_TYPE; */
          /* fprintf(adotout, ".data\n"); */
          /* fprintf(adotout, "_string_const_%d: .asciz %s\n", _const, exprRelatedNode->semantic_value.const1->const_u.sc); */
          /* emitAlignment(); */
          /* fprintf(adotout, ".text\n"); */
          /* fprintf(adotout, "ldr x%d, =_string_const_%d\n", reg, _const); */
          /* _const++; */
          /* break; */
      /* } */
      /* break; */
  /* } */
  /* return reg; */
/* } */
