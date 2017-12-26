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
    fprintf(output, "str x30, [sp, #0]\n");
    fprintf(output, "str x29, [sp, #-8]\n");
    fprintf(output, "add x29, sp, #-8\n");
    fprintf(output, "add sp, sp, #-16\n");
    int offset = 0;
    for(int i = 19; i <= 29; ++i){
        offset += 8;
        fprintf(output, "str x%d, [x29, #%d]\n", i, -offset);
    }
    fprintf(output, ".data\n");
    fprintf(output, "_AR_SIZE_%d: .word %d\n", const_n, offset);
    fprintf(output, ".align 3\n");
    fprintf(output, ".text\n");
    fprintf(output, "ldr w19, _AR_SIZE_%d\n", const_n);
    fprintf(output, "sub sp, sp, w19\n");
    ++const_n;
    //_offset = 0
}

void genFunctionEpilogue(int size, DATA_TYPE returnType)
{
    int offset = 0;
    for (int i = 19; i <= 29; ++i){
        offset += 8;
        fprintf(output, "ldr x%d, [x29, #%d]\n", i, -offset);
    }
    fprintf(output, "ldr x30, [x29, #8]\n");
    fprintf(output, "add sp, x29, #8\n");
    fprintf(output, "ldr x29, [x29, #0]\n");
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
    fprintf(output, "beq _WHILE_END_%d\n", while_n);
    genStmt(stmt);
    fprintf(output, "b _WHILE_%d\n", while_n);
    fprintf(output, "_WHILE_END_%d:\n", while_n);
    freeReg(reg);
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

REG genExprRelated(AST_NODE *exprRelatedNode)
{
    REG reg;
    switch(exprRelatedNode->nodeType)
    {
    case EXPR_NODE:
        return genRelopExpr(exprRelatedNode);
        break;
    case STMT_NODE:
        //function call
		genFunctionCall(exprRelatedNode);
        reg = getReg();
        switch(exprRelatedNode->dataType){
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
        return genVariableRef(exprRelatedNode);
        break;
    case CONST_VALUE_NODE:
        return genConstValue(exprRelatedNode);
        break;
    default:
        printf("Unhandle case in void genExprRelated(AST_NODE* exprRelatedNode)\n");
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


REG genIntLiteral(int i){
    static int counter = 0;
    fprintf(output, ".data\n");
    fprintf(output, "_INT_CONST_%d: .word %d\n", counter, i);
    genAlignment();
    fprintf(output, ".text\n");
    REG reg = getReg();
    fprintf(output, "ldr x%d, _INT_CONST_%d\n", reg, counter);
    counter++;
    return reg;
}

REG genFloatLiteral(float f){
    static int counter = 0;
    fprintf(output, ".data\n");
    fprintf(output, "_FLOAT_CONST_%d: .float %f\n", counter, f);
    genAlignment();
    fprintf(output, ".text\n");
    REG reg = getReg();
    fprintf(output, "ldr s%d, _FLOAT_CONST_%d\n", reg, counter);
    counter++;
    return reg;
}

REG genStrLiteral(char* s){
    static int counter = 0;
    fprintf(output, ".data\n");
    fprintf(output, "_STR_CONST_%d: .asciz %s\n", counter, s);
    genAlignment();
    fprintf(output, ".text\n");
    REG reg = getReg();
    fprintf(output, "ldr x%d, =_STR_CONST_%d\n", reg, counter);
    counter++;
    return reg;
}

void genAlignment(){
    fprintf(output, ".align 3\n");
}

REG genBoolean(char* branch)
{
    static int counter = 0;
    REG reg = getReg();
    fprintf(output, "%s _TRUE_%d\n", branch, counter);
    fprintf(output, "mov w%d, #0\n", reg);
    fprintf(output, "b _BOOLEAN_END_%d\n", counter);
    fprintf(output, "_TRUE_%d:\n", counter);
    fprintf(output, "mov w%d, #1\n", reg);
    fprintf(output, "_BOOLEAN_END_%d:\n", counter);
    counter++;
    return reg;
}

REG genRelopExpr(AST_NODE *exprNode)
{
    /* AST_NODE* it = exprNode->child; */

    /* if (isConstExpr(exprNode)) */
        /* return genConstValue(exprNode); */

	/* if (getExprKind(exprNode) == BINARY_OPERATION) { */
        /* unpack(it, lvalue, rvalue); */

        /* REG LReg = genExprRelated(lvalue); */
        /* REG RReg = genExprRelated(rvalue); */

        /* if(lvalue->dataType == INT_TYPE && rvalue->dataType == INT_TYPE){ */
            /* switch(getExprOp(exprNode)){ */
                /* case BINARY_OP_ADD: */
                    /* fprintf(output, "add w%d, w%d, w%d\n", LReg, LReg, RReg); */
                    /* break; */
                /* case BINARY_OP_SUB: */
                    /* fprintf(output, "sub w%d, w%d, w%d\n", LReg, LReg, RReg); */
                    /* break; */
                /* case BINARY_OP_MUL: */
                    /* fprintf(output, "mul w%d, w%d, w%d\n", LReg, LReg, RReg); */
                    /* break; */
                /* case BINARY_OP_DIV: */
                    /* fprintf(output, "sdiv w%d, w%d, w%d\n", LReg, LReg, RReg); */
                    /* break; */

                /* case BINARY_OP_EQ: */
                    /* fprintf(output, "cmp w%d, w%d\n", LReg, RReg); */
                    /* reg = genBoolean("beq"); */
                    /* break; */
                /* case BINARY_OP_GE: */
                    /* fprintf(output, "cmp w%d, w%d\n", LReg, RReg); */
                    /* reg = genBoolean("bge"); */
                    /* break; */
                /* case BINARY_OP_LE: */
                    /* fprintf(output, "cmp w%d, w%d\n", LReg, RReg); */
                    /* reg = genBoolean("ble"); */
                    /* break; */
                /* case BINARY_OP_NE: */
                    /* fprintf(output, "cmp w%d, w%d\n", LReg, RReg); */
                    /* reg = genBoolean("bne"); */
                    /* break; */
                /* case BINARY_OP_GT: */
                    /* fprintf(output, "cmp w%d, w%d\n", LReg, RReg); */
                    /* reg = genBoolean("bgt"); */
                    /* break; */
                /* case BINARY_OP_LT: */
                    /* fprintf(output, "cmp w%d, w%d\n", LReg, RReg); */
                    /* reg = genBoolean("blt"); */
                    /* break; */

                /* case BINARY_OP_AND: */
                    /* fprintf(output, "cmp w%d, #0\n", LReg); */
                    /* fprintf(output, "beq _ELSE_%d\n", _const); */
                    /* fprintf(output, "cmp w%d, #0\n", RReg); */
                    /* fprintf(output, "beq _ELSE_%d\n", _const); */
                    /* fprintf(output, "mov w%d, #1\n", LReg); */
                    /* fprintf(output, "b _END_%d\n", _const); */
                    /* fprintf(output, "_ELSE_%d:\n", _const); */
                    /* fprintf(output, "mov w%d, #0\n", LReg); */
                    /* fprintf(output, "_END_%d:\n", _const); */
                    /* ++_const; */
                    /* break; */
                /* case BINARY_OP_OR: */
                    /* fprintf(output, "cmp w%d, #0\n", LReg); */
                    /* fprintf(output, "bne _ELSE_%d\n", _const); */
                    /* fprintf(output, "cmp w%d, #0\n", RReg); */
                    /* fprintf(output, "bne _ELSE_%d\n", _const); */
                    /* fprintf(output, "mov w%d, #0\n", LReg); */
                    /* fprintf(output, "b _END_%d\n", _const); */
                    /* fprintf(output, "_ELSE_%d:\n", _const); */
                    /* fprintf(output, "mov w%d, #1\n", LReg); */
                    /* fprintf(output, "_END_%d:\n", _const); */
                    /* ++_const; */
                    /* break; */
            /* } */
            /* freeReg(reg2); */
            /* return reg1; */
        /* }else{ */
            /* exprNode->dataType = FLOAT_TYPE; */
            /* if(leftOp->dataType == INT_TYPE){ */
                /* fprintf(output, "scvtf s%d, w%d\n", reg1, reg1); */
            /* } */
            /* if(rightOp->dataType == INT_TYPE){ */
                /* fprintf(output, "scvtf s%d, w%d\n", reg2, reg2); */
            /* } */
            /* switch(exprNode->semantic_value.exprSemanticValue.op.binaryOp){ */
                /* case BINARY_OP_ADD: */
                    /* fprintf(output, "fadd s%d, s%d, s%d\n", reg1, reg1, reg2); */
                    /* break; */
                /* case BINARY_OP_SUB: */
                    /* fprintf(output, "fsub s%d, s%d, s%d\n", reg1, reg1, reg2); */
                    /* break; */
                /* case BINARY_OP_MUL: */
                    /* fprintf(output, "fmul s%d, s%d, s%d\n", reg1, reg1, reg2); */
                    /* break; */
                /* case BINARY_OP_DIV: */
                    /* fprintf(output, "fdiv s%d, s%d, s%d\n", reg1, reg1, reg2); */
                    /* break; */
                /* case BINARY_OP_EQ: */
                    /* exprNode->dataType = INT_TYPE; */
                    /* fprintf(output, "fcmp s%d, s%d\n", reg1, reg2); */
                    /* fprintf(output, "beq _ELSE_%d\n", _const); */
                    /* fprintf(output, "mov w%d, #0\n", reg1); */
                    /* fprintf(output, "b _END_%d\n", _const); */
                    /* fprintf(output, "_ELSE_%d:\n", _const); */
                    /* fprintf(output, "mov w%d, #1\n", reg1); */
                    /* fprintf(output, "_END_%d:\n", _const); */
                    /* ++_const; */
                    /* break; */
                /* case BINARY_OP_GE: */
                    /* exprNode->dataType = INT_TYPE; */
                    /* fprintf(output, "fcmp s%d, s%d\n", reg1, reg2); */
                    /* fprintf(output, "bge _ELSE_%d\n", _const); */
                    /* fprintf(output, "mov w%d, #0\n", reg1); */
                    /* fprintf(output, "b _END_%d\n", _const); */
                    /* fprintf(output, "_ELSE_%d:\n", _const); */
                    /* fprintf(output, "mov w%d, #1\n", reg1); */
                    /* fprintf(output, "_END_%d:\n", _const); */
                    /* ++_const; */
                    /* break; */
                /* case BINARY_OP_LE: */
                    /* exprNode->dataType = INT_TYPE; */
                    /* fprintf(output, "fcmp s%d, s%d\n", reg1, reg2); */
                    /* fprintf(output, "ble _ELSE_%d\n", _const); */
                    /* fprintf(output, "mov w%d, #0\n", reg1); */
                    /* fprintf(output, "b _END_%d\n", _const); */
                    /* fprintf(output, "_ELSE_%d:\n", _const); */
                    /* fprintf(output, "mov w%d, #1\n", reg1); */
                    /* fprintf(output, "_END_%d:\n", _const); */
                    /* ++_const; */
                    /* break; */
                /* case BINARY_OP_NE: */
                    /* exprNode->dataType = INT_TYPE; */
                    /* fprintf(output, "fcmp s%d, s%d\n", reg1, reg2); */
                    /* fprintf(output, "bne _ELSE_%d\n", _const); */
                    /* fprintf(output, "mov w%d, #0\n", reg1); */
                    /* fprintf(output, "b _END_%d\n", _const); */
                    /* fprintf(output, "_ELSE_%d:\n", _const); */
                    /* fprintf(output, "mov w%d, #1\n", reg1); */
                    /* fprintf(output, "_END_%d:\n", _const); */
                    /* ++_const; */
                    /* break; */
                /* case BINARY_OP_GT: */
                    /* exprNode->dataType = INT_TYPE; */
                    /* fprintf(output, "fcmp s%d, s%d\n", reg1, reg2); */
                    /* fprintf(output, "bgt _ELSE_%d\n", _const); */
                    /* fprintf(output, "mov w%d, #0\n", reg1); */
                    /* fprintf(output, "b _END_%d\n", _const); */
                    /* fprintf(output, "_ELSE_%d:\n", _const); */
                    /* fprintf(output, "mov w%d, #1\n", reg1); */
                    /* fprintf(output, "_END_%d:\n", _const); */
                    /* ++_const; */
                    /* break; */
                /* case BINARY_OP_LT: */
                    /* exprNode->dataType = INT_TYPE; */
                    /* fprintf(output, "fcmp s%d, s%d\n", reg1, reg2); */
                    /* fprintf(output, "blt _ELSE_%d\n", _const); */
                    /* fprintf(output, "mov w%d, #0\n", reg1); */
                    /* fprintf(output, "b _END_%d\n", _const); */
                    /* fprintf(output, "_ELSE_%d:\n", _const); */
                    /* fprintf(output, "mov w%d, #1\n", reg1); */
                    /* fprintf(output, "_END_%d:\n", _const); */
                    /* ++_const; */
                    /* break; */
                /* case BINARY_OP_AND: */
                    /* exprNode->dataType = INT_TYPE; */
                    /* fprintf(output, "fcmp s%d, #0\n", reg1); */
                    /* fprintf(output, "beq _ELSE_%d\n", _const); */
                    /* fprintf(output, "cmp s%d, #0\n", reg2); */
                    /* fprintf(output, "beq _ELSE_%d\n", _const); */
                    /* fprintf(output, "mov w%d, #1\n", reg1); */
                    /* fprintf(output, "b _END_%d\n", _const); */
                    /* fprintf(output, "_ELSE_%d:\n", _const); */
                    /* fprintf(output, "mov w%d, #0\n", reg1); */
                    /* fprintf(output, "_END_%d:\n", _const); */
                    /* ++_const; */
                    /* break; */
                /* case BINARY_OP_OR: */
                    /* exprNode->dataType = INT_TYPE; */
                    /* fprintf(output, "fcmp s%d, #0\n", reg1); */
                    /* fprintf(output, "bne _ELSE_%d\n", _const); */
                    /* fprintf(output, "cmp s%d, #0\n", reg2); */
                    /* fprintf(output, "bne _ELSE_%d\n", _const); */
                    /* fprintf(output, "mov w%d, #0\n", reg1); */
                    /* fprintf(output, "b _END_%d\n", _const); */
                    /* fprintf(output, "_ELSE_%d:\n", _const); */
                    /* fprintf(output, "mov w%d, #1\n", reg1); */
                    /* fprintf(output, "_END_%d:\n", _const); */
                    /* ++_const; */
                    /* break; */
            /* } */
            /* freeReg(reg2); */
            /* return reg1; */
        /* } */
	/* }else{ */
		/* [> Unary operation <] */
		/* AST_NODE* operand = exprNode->child; */
		/* processExprRelatedNode(operand); */
		/* exprNode->dataType = operand->dataType; */

		/* if((exprNode->dataType != ERROR_TYPE) && */
				/* (operand->nodeType == CONST_VALUE_NODE || (operand->nodeType == EXPR_NODE && operand->semantic_value.exprSemanticValue.isConstEval)) */
		  /* ){ */
			/* evaluateExprValue(exprNode); */
			/* exprNode->semantic_value.exprSemanticValue.isConstEval = 1; */
			/* fprintf(output, ".data\n"); */
			/* if(exprNode->dataType == INT_TYPE){ */
				/* fprintf(output, "_integer_const_%d: .word %d\n", _const, exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue); */
			/* }else{ */
				/* fprintf(output, "_float_const_%d: .float %f\n", _const, exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue); */
			/* } */
			/* emitAlignment(); */
			/* fprintf(output, ".text\n"); */
			/* int reg = getReg(); */
			/* if(exprNode->dataType == INT_TYPE){ */
				/* fprintf(output, "ldr w%d, _integer_const_%d\n", reg, _const); */
			/* }else{ */
				/* fprintf(output, "ldr s%d, _float_const_%d\n", reg, _const); */
			/* } */
			/* ++_const; */
			/* return reg; */
		/* }else{ */
			/* int reg = emitExprRelatedNode(operand); */
			/* if(operand->dataType == INT_TYPE){ */
				/* exprNode->dataType = INT_TYPE; */
				/* switch(exprNode->semantic_value.exprSemanticValue.op.unaryOp){ */
					/* case UNARY_OP_POSITIVE: */
						/* break; */
					/* case UNARY_OP_NEGATIVE: */
						/* fprintf(output, "neg w%d, w%d", reg, reg); */
						/* break; */
					/* case UNARY_OP_LOGICAL_NEGATION: */
						/* fprintf(output, "cmp w%d, #0\n", reg); */
						/* fprintf(output, "beq _ELSE_%d\n", _const); */
						/* fprintf(output, "mov w%d, #0\n", reg); */
						/* fprintf(output, "b _END_%d\n", _const); */
						/* fprintf(output, "_ELSE_%d:\n", _const); */
						/* fprintf(output, "mov w%d, #1\n", reg); */
						/* fprintf(output, "_END_%d:\n", _const); */
						/* ++_const; */
						/* break; */
				/* } */
			/* }else{ */
				/* exprNode->dataType = FLOAT_TYPE; */
				/* switch(exprNode->semantic_value.exprSemanticValue.op.unaryOp){ */
					/* case UNARY_OP_POSITIVE: */
						/* break; */
					/* case UNARY_OP_NEGATIVE: */
						/* fprintf(output, "fneg s%d, s%d", reg, reg); */
						/* break; */
					/* case UNARY_OP_LOGICAL_NEGATION: */
						/* exprNode->dataType = INT_TYPE; */
						/* fprintf(output, "fcvtzs w%d, s%d\n", reg, reg); */
						/* fprintf(output, "cmp w%d, #0\n", reg); */
						/* fprintf(output, "beq _ELSE_%d\n", _const); */
						/* fprintf(output, "mov w%d, #0\n", reg); */
						/* fprintf(output, "b _END_%d\n", _const); */
						/* fprintf(output, "_ELSE_%d:\n", _const); */
						/* fprintf(output, "mov w%d, #1\n", reg); */
						/* fprintf(output, "_END_%d:\n", _const); */
						/* ++_const; */
						/* break; */
				/* } */
			/* } */
			/* return reg; */
		/* } */
	/* } */
}

REG genArrayRef(AST_NODE *idNode)
{
    assert ( idNode->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(idNode) != NULL );
    assert ( getIDAttr(idNode)->attributeKind == VARIABLE_ATTRIBUTE );
    assert ( getIDKind(idNode) == ARRAY_ID );
    TypeDescriptor* typeDescriptor = getIDTypeDescriptor(idNode);

    REG varReg;
    if(getIDGlobal(idNode)){
        varReg = getReg();
        fprintf(output, "ldr x%d, =_%s\n", varReg, getIDName(idNode));
    }else{
        int stackOffset = getIDOffset(idNode);
        REG varReg = genIntLiteral(stackOffset);
        fprintf(output, "sub x%d, x29, x%d\n", varReg, varReg);
    }

    int i = 0;
    int *sizes = typeDescriptor->properties.arrayProperties.sizeInEachDimension;
    AST_NODE *dimNode = idNode->child;

    REG offsetReg = getReg();
    fprintf(output, "mov x%d, #0\n", offsetReg);
    forEach(dimNode){
        REG sizeReg = genIntLiteral(sizes[i]);
        fprintf(output, "mul x%d, x%d, x%d\n", offsetReg, offsetReg, sizeReg);
        freeReg(sizeReg);

        REG indexReg = genExprRelated(dimNode);
        fprintf(output, "lsl x%d, x%d, #2\n", indexReg, indexReg);
        fprintf(output, "add x%d, x%d, x%d\n", offsetReg, offsetReg, indexReg);
        freeReg(indexReg);

        ++i;
    }

    fprintf(output, "add x%d, x%d, x%d\n", varReg, varReg, offsetReg);
    freeReg(offsetReg);
    if(idNode->dataType == INT_TYPE){
        fprintf(output, "ldr w%d, [x%d, #0]\n", varReg, varReg);
    }else{
        fprintf(output, "ldr s%d, [x%d, #0]\n", varReg, varReg);
    }

    return varReg;
}

REG genVariableRef(AST_NODE *idNode)
{
    assert ( idNode->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(idNode) != NULL );
    assert ( getIDAttr(idNode)->attributeKind == VARIABLE_ATTRIBUTE );
    TypeDescriptor* typeDescriptor = getIDTypeDescriptor(idNode);

    REG reg;

    if(getIDKind(idNode) == ARRAY_ID){
        return genArrayRef(idNode);
    }else{
        if(getIDGlobal(idNode)){
            reg = getReg();
            if(idNode->dataType == INT_TYPE){
                fprintf(output, "ldr w%d, _%s\n", reg, getIDName(idNode));
            }else{
                fprintf(output, "ldr s%d, _%s\n", reg, getIDName(idNode));
            }
        }else{
            int offset = getIDOffset(idNode);
            REG reg = genIntLiteral(offset);
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
    assert ( constValueNode->nodeType == CONST_VALUE_NODE ||
            (constValueNode->nodeType == EXPR_NODE && isConstExpr(constValueNode)) );

    REG reg;

    if(constValueNode->dataType == INT_TYPE){
        reg = genIntLiteral(getExprValue(constValueNode));
    }else if(constValueNode->dataType == FLOAT_TYPE){
        reg = genFloatLiteral(getExprValue(constValueNode));
    }else{
        reg = genStrLiteral(constValueNode->semantic_value.const1->const_u.sc);
    }

    return reg;
}
