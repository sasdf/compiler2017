#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
#include "macros.h"
#include "assert.h"

// This file is for reference only, you are not required to follow the implementation. //
// You only need to check for errors stated in the hw4 assignment document. //
int g_anyErrorOccur = 0;

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
int processProgramNode(AST_NODE *programNode);
int processDeclarationNode(AST_NODE* declarationNode);
SymbolTableEntry* declarePrimitiveType(char* name, DATA_TYPE type);
int declareIdList(AST_NODE* typeNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize);
int declareFunction(AST_NODE* returnTypeNode);
int processDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int isParameter);
int processTypeNode(AST_NODE* typeNode);
int processBlockNode(AST_NODE* blockNode);
int processStmtNode(AST_NODE* stmtNode);
int processGeneralNode(AST_NODE *node);
int checkAssignable(DATA_TYPE type, DATA_TYPE val, int isParameter);
int checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode);
int checkWhileStmt(AST_NODE* whileNode);
int checkForStmt(AST_NODE* forNode);
int checkAssignmentStmt(AST_NODE* assignmentNode);
int checkIfStmt(AST_NODE* ifNode);
int checkWriteFunction(AST_NODE* functionCallNode);
int checkFunctionCall(AST_NODE* functionCallNode);
int processExprRelatedNode(AST_NODE* exprRelatedNode);
int checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter);
int checkReturnStmt(AST_NODE* returnNode);
int processExprNode(AST_NODE* exprNode);
int processVariableValue(AST_NODE* idNode, int isParameter);
int processVariableLValue(AST_NODE* idNode);
int processVariableRValue(AST_NODE* idNode);
int processConstValueNode(AST_NODE* constValueNode);
int evaluateExprValue(AST_NODE* exprNode);
int processAssignStmt(AST_NODE *assignNode);

typedef enum ErrorMsgKind
{
    SYMBOL_IS_NOT_TYPE,
    SYMBOL_REDECLARE,
    SYMBOL_UNDECLARED,
    NOT_FUNCTION_NAME,
    TRY_TO_INIT_ARRAY,
    EXCESSIVE_ARRAY_DIM_DECLARATION,
    RETURN_ARRAY,
    VOID_VARIABLE,
    TYPEDEF_VOID_ARRAY,
    PARAMETER_TYPE_UNMATCH,
    TOO_FEW_ARGUMENTS,
    TOO_MANY_ARGUMENTS,
    RETURN_TYPE_UNMATCH,
    INCOMPATIBLE_ARRAY_DIMENSION,
    NOT_ASSIGNABLE,
    NOT_ARRAY,
    IS_TYPE_NOT_VARIABLE,
    IS_FUNCTION_NOT_VARIABLE,
    STRING_OPERATION,
    ARRAY_SIZE_NOT_INT,
    ARRAY_SIZE_NEGATIVE,
    ARRAY_SUBSCRIPT_NOT_INT,
    PASS_ARRAY_TO_SCALAR,
    PASS_SCALAR_TO_ARRAY
} ErrorMsgKind;

typedef enum WarningMsgKind
{
    FLOAT_TO_INT,
    INT_TO_FLOAT
} WarningMsgKind;

void printErrorMsgSpecial(AST_NODE* node1, char* name2, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node1->linenumber);
    switch(errorMsgKind) {
        case SYMBOL_UNDECLARED:
            printf("ID \"%s\" undeclared.\n", name2);
            break;
        case SYMBOL_REDECLARE:
            printf("ID \"%s\" redeclared.\n", name2);
            break;
        case TOO_FEW_ARGUMENTS:
            printf("too few arguments to function \"%s\".\n", name2);
            break;
        case TOO_MANY_ARGUMENTS:
            printf("too many arguments to function \"%s\".\n", name2);
            break;
        case PASS_ARRAY_TO_SCALAR:
            printf("Array passed to scalar parameter \"%s\"\n", name2);
            break;
        case PASS_SCALAR_TO_ARRAY:
            printf("Scalar passed to array parameter \"%s\"\n", name2);
            break;
        default:
            printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
            break;
    }
}


void printErrorMsg(AST_NODE* node, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node->linenumber);
    switch(errorMsgKind) {
        case NOT_ASSIGNABLE:
            printf("Not assignable.\n");
            break;
        case RETURN_TYPE_UNMATCH:
            printf("Incompatible return type.\n");
            break;
        case INCOMPATIBLE_ARRAY_DIMENSION:
            printf("Incompatible array dimensions.\n");
            break;
        case ARRAY_SUBSCRIPT_NOT_INT:
            printf("Array subscript is not an integer.\n");
            break;
        case ARRAY_SIZE_NOT_INT:
            printf("Array subscript is not an integer\n");
            break;
        default:
            printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
            break;
    }
}

void printWarningMsg(AST_NODE* node, WarningMsgKind warningMsgKind)
{
    printf("Warning found in line %d\n", node->linenumber);
    switch(warningMsgKind) {
        case FLOAT_TO_INT:
            printf("Incompatible return type. (Truncating float to int).\n");
            break;
        case INT_TO_FLOAT:
            printf("Incompatible return type. (Implicit conversion from int to float)\n");
            break;
        default:
            printf("Unhandled case in void printWarningMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
            break;
    }
}

void semanticAnalysis(AST_NODE *root)
{
    //initializeSymbolTable();
    openScope();
    SymbolTableEntry* tInt = declarePrimitiveType(SYMBOL_TABLE_INT_NAME, INT_TYPE);
    SymbolTableEntry* tFloat = declarePrimitiveType(SYMBOL_TABLE_FLOAT_NAME, FLOAT_TYPE);
    SymbolTableEntry* tVoid = declarePrimitiveType(SYMBOL_TABLE_VOID_NAME, VOID_TYPE);
    /* SymbolTableEntry* tStr = declarePrimitiveType("", CONST_STRING_TYPE); */
    if(!processProgramNode(root))
        g_anyErrorOccur = 1;
    closeScope();
    //symbolTableEnd();
}


DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2)
{
    if(dataType1 == ERROR_TYPE || dataType2 == ERROR_TYPE) {
        return ERROR_TYPE;
    } else if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE) {
        return FLOAT_TYPE;
    } else {
        return INT_TYPE;
    }
}

// [decl ...]
int processDeclarationList(AST_NODE* declarationList){
    int flag = true;
    AST_NODE *decl = declarationList->child;
    forEach (decl){
        if (decl->nodeType == VARIABLE_DECL_LIST_NODE) {
            flag &= processDeclarationList(decl);
        } else {
            flag &= processDeclarationNode(decl);
        }
    }
    return flag;
}

// program -> [global_decl ...]
int processProgramNode(AST_NODE *programNode)
{
    return processDeclarationList(programNode);
}

// global_decl -> var_decl | type_decl | func_decl | func_param_decl
int processDeclarationNode(AST_NODE* declarationNode)
{
    int retval = true;
    switch (getDeclKind(declarationNode)){
        case VARIABLE_DECL:
            setDeclKind(declarationNode, VARIABLE_DECL);
            retval &= declareIdList(declarationNode->child, VARIABLE_ATTRIBUTE, false);
            break;
        case TYPE_DECL:
            setDeclKind(declarationNode, TYPE_DECL);
            retval &= declareIdList(declarationNode->child, TYPE_ATTRIBUTE, false);
            break;
        case FUNCTION_DECL:
            retval &= declareFunction(declarationNode->child);
            break;
        case FUNCTION_PARAMETER_DECL:
            retval &= declareIdList(declarationNode->child, VARIABLE_ATTRIBUTE, true);
            break;
    }
    return retval;
}

// typeNode -- idNode
int processTypeNode(AST_NODE* typeNode)
{
    assert(typeNode->nodeType == IDENTIFIER_NODE);
    int retval = true;
    loop1 {
        SymbolTableEntry* typeEntry = retrieveSymbol(getIDName(typeNode));
        if (!typeEntry) {
            // TODO: error - SYMBOL_UNDECLARED
            printErrorMsgSpecial(typeNode, getIDName(typeNode), SYMBOL_UNDECLARED);
            retval = false;
            break;
        }
        SymbolAttribute* typeAttribute = typeEntry->attribute;
        if (typeAttribute->attributeKind != TYPE_ATTRIBUTE) {
            // TODO: error - not a type
            retval = false;
            break;
        }
        setTypeEntry(typeNode, typeEntry);
    }
    return retval;
}

int checkAssignable(DATA_TYPE type, DATA_TYPE val, int isParameter)
{
    if (isParameter) {
        if (type == INT_PTR_TYPE && val == INT_PTR_TYPE)
            return true;
        if (type == FLOAT_PTR_TYPE && val == INT_PTR_TYPE)
            return true;
        if (type == FLOAT_PTR_TYPE && val == FLOAT_PTR_TYPE)
            return true;
    }
    if (val != INT_TYPE && val != FLOAT_TYPE)
        return false;
    if (type != INT_TYPE && type != FLOAT_TYPE)
        return false;
    if (getBiggerType(type, val) != type)
        return false;
    return true;
}

SymbolTableEntry* declarePrimitiveType(char* name, DATA_TYPE type)
{
    TypeDescriptor* typeDescriptor = new(TypeDescriptor);
    typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;
    typeDescriptor->properties.dataType = type;

    SymbolAttribute *attribute = new(SymbolAttribute);
    attribute->attributeKind = TYPE_ATTRIBUTE;
    attribute->attr.typeDescriptor = typeDescriptor;

    SymbolTableEntry* entry = enterSymbol(name, attribute);
    return entry;
}

// [type id]
int declareNormalId(AST_NODE* idNode, TypeDescriptor* type, SymbolAttribute* attribute, int isParameter)
{
    assert(idNode->nodeType == IDENTIFIER_NODE);
    attribute->attr.typeDescriptor = type;
    if (type->kind == SCALAR_TYPE_DESCRIPTOR &&
            type->properties.dataType == VOID_TYPE &&
            attribute->attributeKind == VARIABLE_ATTRIBUTE) {
        // TODO: error - VOID_VARIABLE
        return false;
    }
    return true;
}

// [type id -> [expr ...]]
int declareArrayId(AST_NODE* idNode, TypeDescriptor* type, SymbolAttribute* attribute, int isParameter)
{
    assert(idNode->nodeType == IDENTIFIER_NODE);
    int retval = true;
    loop1 {
        if (type->kind == ARRAY_TYPE_DESCRIPTOR) {
            assert(type->properties.dataType == INT_TYPE || 
                    type->properties.dataType == FLOAT_TYPE);

            TypeDescriptor* typeDescriptor = new(TypeDescriptor);
            typeDescriptor->kind = ARRAY_TYPE_DESCRIPTOR;
            typeDescriptor->properties.arrayProperties.elementType = type->properties.dataType;

            if (!processDeclDimList(idNode->child, typeDescriptor, isParameter)) {
                retval = false;
                break;
            }
            if (typeDescriptor->properties.arrayProperties.dimension + 
                    type->properties.arrayProperties.dimension > MAX_ARRAY_DIMENSION) {
                // TODO: error - EXCESSIVE_ARRAY_DIM_DECLARATION
                retval = false;
                break;
            }
            int sdim = type->properties.arrayProperties.dimension;
            int tdim = typeDescriptor->properties.arrayProperties.dimension;
            int *s = type->properties.arrayProperties.sizeInEachDimension;
            int *t = typeDescriptor->properties.arrayProperties.sizeInEachDimension;
            memcpy(t + tdim, s, sdim);
            typeDescriptor->properties.arrayProperties.dimension = tdim + sdim;
            attribute->attr.typeDescriptor = typeDescriptor;
        } else {
            assert(type->kind == SCALAR_TYPE_DESCRIPTOR);
            if (type->properties.dataType == VOID_TYPE) {
                if (attribute->attributeKind == VARIABLE_ATTRIBUTE) {
                    // TODO: error - VOID_VARIABLE
                    retval = false;
                }
                if (attribute->attributeKind == TYPE_ATTRIBUTE) {
                    // TODO: error - TYPEDEF_VOID_ARRAY
                    retval = false;
                }
            } else {
                assert(type->properties.dataType == INT_TYPE || 
                        type->properties.dataType == FLOAT_TYPE);
            }

            TypeDescriptor* typeDescriptor = new(TypeDescriptor);
            typeDescriptor->kind = ARRAY_TYPE_DESCRIPTOR;
            typeDescriptor->properties.arrayProperties.elementType = type->properties.dataType;

            retval &= processDeclDimList(idNode->child, typeDescriptor, isParameter);

            attribute->attr.typeDescriptor = typeDescriptor;
        }
    }
    return retval;
}

// [type id -> expr]
int declareInitId(AST_NODE* idNode, TypeDescriptor* type, SymbolAttribute* attribute, int isParameter)
{
    assert(idNode->nodeType == IDENTIFIER_NODE);
    int retval = true;
    assert(!isParameter); // enforced by grammar
    if (type->kind == ARRAY_TYPE_DESCRIPTOR) {
        // TODO: error - TRY_TO_INIT_ARRAY
        // not tested yet
        printErrorMsgSpecial(idNode,  getIDName(idNode), TRY_TO_INIT_ARRAY);
        return false;
    } else {
        attribute->attr.typeDescriptor = type;
        retval &= processExprRelatedNode(idNode->child);
        if (retval) {
            DATA_TYPE dataType = type->properties.dataType;
            DATA_TYPE exprType = getExprType(idNode->child);
            if (checkAssignable(dataType, exprType, isParameter)) {
                // TODO: error - NOT_ASSIGNABLE
                if (dataType == INT_TYPE && exprType == FLOAT_TYPE){
                    printWarningMsg(idNode, FLOAT_TO_INT);
                    return retval;
                }
                if (dataType == FLOAT_TYPE && exprType == INT_TYPE){
                    printWarningMsg(idNode, INT_TO_FLOAT);
                    return retval;
                }
                if ((dataType == FLOAT_TYPE && exprType == FLOAT_TYPE) ||
                    (dataType == INT_TYPE && exprType == INT_TYPE)){
                    // nothing
                } else {
                    retval = 0;
                    printErrorMsg(idNode, NOT_ASSIGNABLE);
                }
            }
        }
    }
    return retval;
}

// [type (NORMAL_ID | ARRAY_ID | WITH_INIT_ID)]
int declareId(AST_NODE* idNode, TypeDescriptor* type, SymbolAttributeKind kind, int isParameter)
{
    assert(idNode->nodeType == IDENTIFIER_NODE);
    int retval;
    SymbolAttribute *attribute = new(SymbolAttribute);
    attribute->attributeKind = kind;
    switch (getIDKind(idNode)) {
        case NORMAL_ID:
            retval = declareNormalId(idNode, type, attribute, isParameter);
            break;
        case ARRAY_ID:
            retval = declareArrayId(idNode, type, attribute, isParameter);
            break;
        case WITH_INIT_ID:
            retval = declareInitId(idNode, type, attribute, isParameter);
            break;
        default:
            assert(0/* unknown id kind */);
    }
    if (retval) {
        SymbolTableEntry* entry = enterSymbol(getIDName(idNode), attribute);
        setIDEntry(idNode, entry);
    }
    return retval;
}

// idList -> [type id ...]
int declareIdList(AST_NODE* declarationNode, SymbolAttributeKind kind, int isParameter)
{
    AST_NODE *iterator = declarationNode;
    unpack(iterator, typeNode);
    int retval = true;
    if (!processTypeNode(typeNode)){
        // TODO: error - invalid type
    } else {
        TypeDescriptor* typeDescriptor = getTypeDescriptor(typeNode);
        forEach (iterator){
            if (declaredLocally(getIDName(iterator))) {
                retval = false;
                printErrorMsgSpecial(declarationNode, getIDName(iterator), SYMBOL_REDECLARE);
            } else {
                retval &= declareId(iterator, typeDescriptor, kind, isParameter);
            }
        }
    }
    return retval;
}

/*
int checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode)
{
}


int checkAssignmentStmt(AST_NODE* assignmentNode)
{
    //TODO: error - NOT_ASSIGNABLE
}

*/
int checkWriteFunction(AST_NODE* funcNode)
{
    assert(funcNode->nodeType == STMT_NODE);
    assert(getStmtKind(funcNode) == FUNCTION_CALL_STMT);
    int retval = true;
    funcNode->dataType = VOID_TYPE;
    AST_NODE *iterator = funcNode->child;
    unpack(iterator, idNode, paramNode);
    assert(paramNode->nodeType == NUL_NODE ||
            paramNode->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE);

    loop1 {
        if (paramNode->nodeType == NUL_NODE) {
            break;
        }
        AST_NODE* ap = paramNode->child;
        forEach(ap) {
            if (ap->nodeType == IDENTIFIER_NODE) {
                retval &= processVariableValue(ap, true);
            } else if (ap->nodeType == CONST_VALUE_NODE && getConstType(ap) == STRINGC) {
                // Don't check
            } else {
                retval &= processExprRelatedNode(ap);
            }
        }
    }
    return retval;
}

int checkFunctionCall(AST_NODE* funcNode)
{
    assert(funcNode->nodeType == STMT_NODE);
    assert(getStmtKind(funcNode) == FUNCTION_CALL_STMT);
    int retval = true;
    funcNode->dataType = ERROR_TYPE;
    AST_NODE *iterator = funcNode->child;
    unpack(iterator, idNode, paramNode);
    loop1{
        if (strcmp(getIDName(idNode), "write") == 0) {
            retval &= checkWriteFunction(funcNode);
            break;
        }
        SymbolTableEntry* funcEntry = retrieveSymbol(getIDName(idNode));
        if (!funcEntry) {
            // TODO: error - SYMBOL_UNDECLARED
            printErrorMsgSpecial(funcNode, getIDName(idNode), SYMBOL_UNDECLARED);
            retval = false;
            break;
        }
        SymbolAttribute* typeAttribute = funcEntry->attribute;
        if (typeAttribute->attributeKind != FUNCTION_SIGNATURE) {
            // TODO: error - not a func
            retval = false;
            break;
        }
        setIDEntry(idNode, funcEntry);
        FunctionSignature* sig = funcEntry->attribute->attr.functionSignature;
        Parameter *param = sig->parameterList;
        retval = checkParameterPassing(param, paramNode);
        if (retval) {
            funcNode->dataType = sig->returnType;
        }
    }
    return retval;
}

int checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter)
{
    int retval = true;
    assert(actualParameter->nodeType == NUL_NODE ||
            actualParameter->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE);

    loop1 {
        if (actualParameter->nodeType == NUL_NODE) {
            if (formalParameter != NULL) {
                //TODO: error - TOO_FEW_ARGUMENTS,
                printErrorMsgSpecial(actualParameter, getIDName(actualParameter->leftmostSibling), TOO_FEW_ARGUMENTS);
                retval = false;
                break;
            }
        } else {
            AST_NODE* ap = actualParameter->child;
            Parameter* fp = formalParameter;
            int ret;
            for(;ap&&fp;ap=ap->rightSibling,fp=fp->next) {
                if (ap->nodeType == IDENTIFIER_NODE) {
                    retval &= ( ret = processVariableValue(ap, true) );
                } else {
                    retval &= ( ret = processExprRelatedNode(ap) );
                }
                if (!ret) continue;
                switch (ap->dataType) {
                    case INT_TYPE:
                    case INT_PTR_TYPE:
                        if (getParamType(fp) != INT_TYPE) {
                            /* retval = false; */
                            // TODO: error - PARAMETER_TYPE_UNMATCH
                        }
                        break;
                    case FLOAT_TYPE:
                    case FLOAT_PTR_TYPE:
                        if (getParamType(fp) != FLOAT_TYPE) {
                            /* retval = false; */
                            // TODO: error - PARAMETER_TYPE_UNMATCH
                        }
                        break;
                    case ERROR_TYPE:
                        retval = false;
                        break;

                }
                switch (ap->dataType) {
                    case INT_TYPE:
                    case FLOAT_TYPE:
                        if (fp->type->kind == ARRAY_TYPE_DESCRIPTOR) {
                            // TODO: error - PASS_SCALAR_TO_ARRAY
                            printErrorMsgSpecial(ap, fp->parameterName, PASS_SCALAR_TO_ARRAY);
                            retval = false;
                        }
                        break;
                    case INT_PTR_TYPE:
                    case FLOAT_PTR_TYPE:
                        if (fp->type->kind == SCALAR_TYPE_DESCRIPTOR) {
                            // TODO: error - PASS_ARRAY_TO_SCALAR
                            printErrorMsgSpecial(ap, fp->parameterName, PASS_ARRAY_TO_SCALAR);
                            retval = false;
                        }
                        break;
                }
            }
            if (ap != NULL && fp == NULL) {
                retval = false;
                //TODO: error - TOO_MANY_ARGUMENTS,
                printErrorMsgSpecial(actualParameter, getIDName(actualParameter->leftmostSibling), TOO_MANY_ARGUMENTS);
            } else if (ap == NULL && fp != NULL) {
                retval = false;
                //TODO: error - TOO_FEW_ARGUMENTS,
                printErrorMsgSpecial(actualParameter, getIDName(actualParameter->leftmostSibling), TOO_FEW_ARGUMENTS);
            }
        }
    }
    return retval;
}


// const | (expr -> [op ...])
int processExprRelatedNode(AST_NODE* exprRelatedNode)
{
    int retval = true;
    switch(exprRelatedNode->nodeType) {
        case CONST_VALUE_NODE:
            retval &= processConstValueNode(exprRelatedNode);
            break;
        case IDENTIFIER_NODE:
            retval &= processVariableRValue(exprRelatedNode);
            break;
        case STMT_NODE:
            retval &= processStmtNode(exprRelatedNode);
            break;
        case EXPR_NODE:
            retval &= processExprNode(exprRelatedNode);
            break;
        default:
            assert(0/* invalid type for expr */);
    }
    return retval;
}

// constant folding
int evaluateExprValue(AST_NODE* exprNode)
{
    assert(exprNode->nodeType == EXPR_NODE);
    int retval = true;
    exprNode->semantic_value.exprSemanticValue.isConstEval = true;
    setExprType(exprNode, INT_TYPE);

    // Need to be constant expr
    AST_NODE* operand = exprNode->child;
    forEach(operand) {
        switch (getExprType(operand)) {
            case INT_TYPE:
            case FLOAT_TYPE:
                break;
            case ERROR_TYPE:
                retval = false;
                exprNode->semantic_value.exprSemanticValue.isConstEval = false;
                break;
            case INT_PTR_TYPE:
            case FLOAT_PTR_TYPE:
                retval = false;
                // TODO: error - array operation
                exprNode->semantic_value.exprSemanticValue.isConstEval = false;
                return false;
            case CONST_STRING_TYPE:
                retval = false;
                // TODO: error - string operation
                exprNode->semantic_value.exprSemanticValue.isConstEval = false;
                return false;
            case VOID_TYPE:
                retval = false;
                // TODO: error - void operation
                exprNode->semantic_value.exprSemanticValue.isConstEval = false;
                return false;
            case NONE_TYPE:
                assert(0/* Operation on strange type */);
                break;
        }
        setExprType(exprNode, getBiggerType(getExprType(exprNode), getExprType(operand)));
        if (!isConstExpr(operand)) {
            exprNode->semantic_value.exprSemanticValue.isConstEval = false;
        }
    }
    if (!isConstExpr(exprNode)) return retval;

    // Evaluate
    if (getExprKind(exprNode) == UNARY_OPERATION) {
        AST_NODE* iterator = exprNode->child;
        unpack(iterator, x);
        setExprType(exprNode, getExprType(x));
        switch(getExprOp(exprNode)) {
            case UNARY_OP_POSITIVE:
                setExprValue(exprNode, +getExprValue(x));
                break;
            case UNARY_OP_NEGATIVE:
                setExprValue(exprNode, -getExprValue(x));
                break;
            case UNARY_OP_LOGICAL_NEGATION:
                setExprValue(exprNode, !getExprValue(x));
                break;
            default:
                assert(0/* unknown op */);
        }
    } else if (getExprKind(exprNode) == BINARY_OPERATION) {
        AST_NODE* iterator = exprNode->child;
        unpack(iterator, x, y);
        setExprType(exprNode, getBiggerType(getExprType(x), getExprType(y)));
        switch(getExprOp(exprNode)) {
            case BINARY_OP_ADD:
                setExprValue(exprNode, getExprValue(x) + getExprValue(y));
                break;
            case BINARY_OP_SUB:
                setExprValue(exprNode, getExprValue(x) - getExprValue(y));
                break;
            case BINARY_OP_MUL:
                setExprValue(exprNode, getExprValue(x) * getExprValue(y));
                break;
            case BINARY_OP_DIV:
                if (getExprValue(y) == 0) {
                    retval = false;
                    // TODO: error - division by zero
                } else {
                    setExprValue(exprNode, getExprValue(x) / getExprValue(y));
                }
                break;
            case BINARY_OP_EQ:
                setExprValue(exprNode, getExprValue(x) == getExprValue(y));
                break;
            case BINARY_OP_GE:
                setExprValue(exprNode, getExprValue(x) >= getExprValue(y));
                break;
            case BINARY_OP_LE:
                setExprValue(exprNode, getExprValue(x) <= getExprValue(y));
                break;
            case BINARY_OP_NE:
                setExprValue(exprNode, getExprValue(x) != getExprValue(y));
                break;
            case BINARY_OP_GT:
                setExprValue(exprNode, getExprValue(x) > getExprValue(y));
                break;
            case BINARY_OP_LT:
                setExprValue(exprNode, getExprValue(x) < getExprValue(y));
                break;
            case BINARY_OP_AND:
                setExprValue(exprNode, getExprValue(x) && getExprValue(y));
                break;
            case BINARY_OP_OR:
                setExprValue(exprNode, getExprValue(x) || getExprValue(y));
                break;
            default:
                assert(0/* unknown op */);
        }
    } else {
        assert(0/* unknown op kind */);
    }

    return retval;
}


// expr -> [op ...]
int processExprNode(AST_NODE* exprNode)
{
    assert(exprNode->nodeType == EXPR_NODE);
    int retval = true;
    int stringOperation = false;

    AST_NODE* operand = exprNode->child;
    forEach(operand) {
        retval &= processExprRelatedNode(operand);
        if (operand->dataType == CONST_STRING_TYPE) {
            stringOperation = true;
        }
    }
    if (stringOperation) {
        retval = false;
        // TODO: error - STRING_OPERATION
    }
    if(!evaluateExprValue(exprNode)) {
        retval = false;
    }
    return retval;
}


int processVariableValue(AST_NODE* idNode, int isParameter)
{
    int retval = true;
    idNode->dataType = ERROR_TYPE;
    assert(idNode->nodeType == IDENTIFIER_NODE);
    loop1 {
        SymbolTableEntry* idEntry = retrieveSymbol(getIDName(idNode));
        if (!idEntry) {
            // TODO: error - SYMBOL_UNDECLARED
            printErrorMsgSpecial(idNode, getIDName(idNode), SYMBOL_UNDECLARED);
            retval = false;
            break;
        }
        SymbolAttribute* typeAttribute = idEntry->attribute;
        if (typeAttribute->attributeKind != VARIABLE_ATTRIBUTE) {
            // TODO: error - not a variable
            retval = false;
            break;
        }
        setIDEntry(idNode, idEntry);
        TypeDescriptor* typeDescriptor = getTypeDescriptor(idNode);
        
        if (getIDKind(idNode) == NORMAL_ID) {
            if (typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR && !isParameter) {
                // TODO: error - INCOMPATIBLE_ARRAY_DIMENSION
                printErrorMsg(idNode, INCOMPATIBLE_ARRAY_DIMENSION);
                retval = false;
                break;
            }
            if (typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR && isParameter) {
                DATA_TYPE elementType = typeDescriptor->properties.arrayProperties.elementType;
                switch(elementType) {
                    case INT_TYPE:
                        idNode->dataType = INT_PTR_TYPE;
                        break;
                    case FLOAT_TYPE:
                        idNode->dataType = FLOAT_PTR_TYPE;
                        break;
                }
                break;
            }
            idNode->dataType = typeDescriptor->properties.dataType;
        } else if (getIDKind(idNode) == ARRAY_ID) {
            AST_NODE *dimNodes = idNode->child;
            int dimensions = 0;
            forEach(dimNodes){
                dimensions++;
                retval &= processExprRelatedNode(dimNodes);
                if (dimNodes->dataType != INT_TYPE && dimNodes->dataType != ERROR_TYPE) {
                    // TODO: error - ARRAY_SUBSCRIPT_NOT_INT
                    printErrorMsg(idNode, ARRAY_SUBSCRIPT_NOT_INT);
                    retval = false;
                }
            }
            if (typeDescriptor->kind != ARRAY_TYPE_DESCRIPTOR) {
                // TODO: error - NOT_ARRAY
                retval = false;
                break;
            }
            int trueDim = typeDescriptor->properties.arrayProperties.dimension;
            if (dimensions < trueDim && isParameter) {
                DATA_TYPE elementType = typeDescriptor->properties.arrayProperties.elementType;
                switch(elementType) {
                    case INT_TYPE:
                        idNode->dataType = INT_PTR_TYPE;
                        break;
                    case FLOAT_TYPE:
                        idNode->dataType = FLOAT_PTR_TYPE;
                        break;
                }
                break;
            }
            if (dimensions != trueDim) {
                // TODO: error - INCOMPATIBLE_ARRAY_DIMENSION
                printErrorMsg(idNode, INCOMPATIBLE_ARRAY_DIMENSION);
                retval = false;
                break;
            }
            idNode->dataType = typeDescriptor->properties.arrayProperties.elementType;
        }
    }
    if (!retval) idNode->dataType = ERROR_TYPE;
    return retval;
}

int processVariableLValue(AST_NODE* idNode)
{
    return processVariableValue(idNode, false);
}
int processVariableRValue(AST_NODE* idNode)
{
    return processVariableValue(idNode, false);
}


// const
int processConstValueNode(AST_NODE* constValueNode)
{
    assert(constValueNode->nodeType == CONST_VALUE_NODE);
    switch(constValueNode->semantic_value.const1->const_type) {
        case INTEGERC:
            constValueNode->dataType = INT_TYPE;
            break;
        case FLOATC:
            constValueNode->dataType = FLOAT_TYPE;
            break;
        case STRINGC:
            constValueNode->dataType = CONST_STRING_TYPE;
            break;
        default:
            assert(0 == "unknown const type");

    }
    return true;
}

int  processStatementList(AST_NODE *stmtList){
    int flag = true;
    AST_NODE *stmt = stmtList->child;
    forEach (stmt){
        flag &= processStmtNode(stmt);
    }
    return flag;
}

// block -> decl_list stmt_list | stmt_list | decl_list
int processBlockNode(AST_NODE* blockNode)
{
    int flag = true;
    openScope();
    loop1 {
        AST_NODE *child = blockNode->child;
        if (!child) {
            break;
        }
        if (child->rightSibling){       // decl_list stmt_list
            flag &= processDeclarationList(child);
            flag &= processStatementList(child->rightSibling);
        } else{
            if (child->nodeType == VARIABLE_DECL_LIST_NODE)     // decl_list
                flag &= processDeclarationList(child);
            else if (child->nodeType == STMT_LIST_NODE)         // stmt_list
                flag &= processStatementList(child);
            else assert(0 == "unknown block's child type");
        }
    }
    closeScope();
    return flag;
}

int processNonEmptyAssignExprList(AST_NODE *assignExprList)
{
    int flag = true;
    AST_NODE *it = assignExprList;
    forEach (it){
        flag &= processAssignStmt(it);
    }
    return flag;
}

int processAssignExprList(AST_NODE *assignExprList)
{
    if (assignExprList->nodeType == NUL_NODE)
        return 1;
    return processNonEmptyAssignExprList(assignExprList->child);
}

int processNonEmptyRelopExprList(AST_NODE *relopExprList)
{
    int flag = true;
    AST_NODE *it = relopExprList;
    forEach (it){
        flag &= processExprRelatedNode(it);
    }
    return flag;
}

int processRelopExprList(AST_NODE *relopExprList)
{
    // TODO: fill symboltable??
    if (relopExprList->nodeType == NUL_NODE)
        return 1;
    return processNonEmptyRelopExprList(relopExprList);
}

int processWhileStmt(AST_NODE *whileNode)
{
    int flag = true;
    AST_NODE *it = whileNode;
    unpack(it, test, stmt);
    flag &= processAssignStmt(test);
    flag &= processStmtNode(stmt);
    return flag;
}

int processForStmt(AST_NODE *forNode)
{
    int flag = true;
    AST_NODE *it = forNode;
    unpack(it, assignExprList, relopExprList, assignExprList2, stmt);
    flag &= processAssignExprList(assignExprList);
    flag &= processRelopExprList(relopExprList);
    flag &= processAssignExprList(assignExprList2);
    flag &= processStmtNode(stmt);
    return flag;
}

int processAssignStmt(AST_NODE *assignNode)
{
    int flag = true;
    if (assignNode->nodeType == STMT_NODE && getStmtKind(assignNode) == ASSIGN_STMT){
        AST_NODE *it = assignNode->child;
        unpack(it, id, relopExpr);
        flag &= processExprRelatedNode(relopExpr);
        flag &= processVariableLValue(id);
        DATA_TYPE idType = id->dataType;
        DATA_TYPE exprType = relopExpr->dataType;
        
        if (idType == INT_PTR_TYPE || idType == FLOAT_PTR_TYPE){
            puts("A");
            printErrorMsg(assignNode, NOT_ASSIGNABLE);
            return 0;
        }
        if (idType == INT_TYPE && exprType == FLOAT_TYPE)
            printWarningMsg(assignNode, FLOAT_TO_INT);
        if (idType == FLOAT_TYPE && exprType == INT_TYPE)
            printWarningMsg(assignNode, INT_TO_FLOAT);
    } else if (assignNode->nodeType == IDENTIFIER_NODE ||
               assignNode->nodeType == CONST_VALUE_NODE ||
               assignNode->nodeType == EXPR_NODE ||
               assignNode->nodeType == STMT_NODE){
        AST_NODE *it = assignNode;
        unpack(it, relopExpr);
        flag &= processExprRelatedNode(relopExpr);
    }

    return flag;
}

int processIfStmt(AST_NODE *ifNode)
{
    int flag = true;
    AST_NODE *it = ifNode;
    unpack(it, test, stmt, elseStmt);
    flag &= processAssignStmt(test);
    flag &= processStmtNode(stmt);
    if (elseStmt->nodeType != NUL_NODE)
        flag &= processStmtNode(elseStmt);
    return flag;
}

int checkReturnStmt(AST_NODE* returnNode)
{
    int flag = true;
    AST_NODE *parent = returnNode;
    findParentDecl(parent, FUNCTION_DECL);

    FunctionSignature *sig = getFunctionSignature(parent);
    if (sig->returnType == ERROR_TYPE)
        return 0;

    TypeDescriptor *type = getTypeDescriptor(parent->child);
    assert(type->kind == SCALAR_TYPE_DESCRIPTOR);
    /*
    assert(type->properties.dataType == INT_TYPE || 
           type->properties.dataType == FLOAT_TYPE ||
           type->properties.dataType == VOID_TYPE
    );*/

    // return array not done yet
    switch (returnNode->nodeType){
        case NUL_NODE:
            if (type->properties.dataType != VOID_TYPE){
                printErrorMsg(returnNode, RETURN_TYPE_UNMATCH);
                return 0;
            }
            break;  
        case IDENTIFIER_NODE:
        case STMT_NODE:
        case CONST_VALUE_NODE:
        case EXPR_NODE:
            flag &= processExprRelatedNode(returnNode);
            DATA_TYPE childType = getExprType(returnNode);

            if (childType == INT_PTR_TYPE || childType == FLOAT_PTR_TYPE){
                printErrorMsg(returnNode, RETURN_ARRAY);
                return 0;
            }

            if (childType == ERROR_TYPE){
                return 0;
            }

            assert(childType == INT_TYPE || childType == FLOAT_TYPE || childType == VOID_TYPE);

            if (type->properties.dataType == INT_TYPE){
                if (childType == FLOAT_TYPE){
                    printWarningMsg(returnNode, FLOAT_TO_INT);
                    return flag;
                }
                if (childType == VOID_TYPE){
                    printErrorMsg(returnNode, RETURN_TYPE_UNMATCH);
                    return 0;
                }
            } else if (type->properties.dataType == FLOAT_TYPE){
                if (childType == INT_TYPE){
                    printWarningMsg(returnNode, INT_TO_FLOAT);
                    return flag;
                }
                if (childType == VOID_TYPE){
                    printErrorMsg(returnNode, RETURN_TYPE_UNMATCH);
                    return 0;
                }
            } else if (type->properties.dataType == VOID_TYPE){
                if (childType != VOID_TYPE){
                    printErrorMsg(returnNode, RETURN_TYPE_UNMATCH);
                    return 0;
                }
            }
            break;
        default:
            assert(0 == "unknown return node");
    }
    return flag;
}

int processStmtNode(AST_NODE* stmtNode)
{
    int flag = true;
    switch (stmtNode->nodeType){
        case BLOCK_NODE:
            flag &= processBlockNode(stmtNode);
            break;
        case STMT_NODE:
            switch (stmtNode->semantic_value.stmtSemanticValue.kind){
                case WHILE_STMT:
                    flag &= processWhileStmt(stmtNode->child);
                    break;
                case FOR_STMT:
                    flag &= processForStmt(stmtNode->child);
                    break;
                case ASSIGN_STMT:
                    flag &= processAssignStmt(stmtNode);
                    break;
                case IF_STMT:
                    flag &= processIfStmt(stmtNode->child);
                    break;
                case FUNCTION_CALL_STMT:
                    flag &= checkFunctionCall(stmtNode);
                    break;
                case RETURN_STMT:
                    flag &= checkReturnStmt(stmtNode->child);
                    break;
                default:
                    assert(0 == "unknown statement");
            }
            break;
        case NUL_NODE:
            break;
        default:
            assert(0 == "unknown stmt node");
            break;
    }
    return flag;
}


/*
int processGeneralNode(AST_NODE *node)
{
}
*/

// dimlist -> [expr ...]
int processDeclDimList(AST_NODE* dimList, TypeDescriptor* typeDescriptor, int isParameter)
{
    int retval = true;
    ArrayProperties* arrayProperties = &typeDescriptor->properties.arrayProperties;
    DATA_TYPE elementType = arrayProperties->elementType;
    assert(elementType == INT_TYPE || elementType == FLOAT_TYPE || elementType == VOID_TYPE);

    arrayProperties->dimension = 0;
    AST_NODE* iterator = dimList;


    // Check whether first dimension can be null
    unpack(iterator, firstDim);
    if (!isParameter && isNullNode(firstDim)) {
        // TODO: error - empty array dim
        addArrayDim(arrayProperties, -1);
    } else if (isParameter && isNullNode(firstDim)) {
        switch(elementType) {
            case INT_TYPE:
                arrayProperties->elementType = INT_PTR_TYPE;
                break;
            case FLOAT_TYPE:
                arrayProperties->elementType = FLOAT_PTR_TYPE;
                break;
            case VOID_TYPE:
                // TODO: error - void array
                break;
            default:
                assert(0/* invalid type for dimension */);
        }
        addArrayDim(arrayProperties, -1);
    } else {
        // undo unpack
        iterator = dimList;
    }


    // Construct dimensions
    int excessiveDim = false;
    forEach(iterator) {
        assert(iterator->nodeType != NUL_NODE); // enforced by grammar
        loop1 {
            if(!processExprRelatedNode(iterator)) {
                retval = false;
                addArrayDim(arrayProperties, -2);
                break;
            }
            if (!isConstExpr(iterator)) {
                // TODO: error - array size not constant
                retval = false;
                addArrayDim(arrayProperties, -3);
                break;
            }
            if (getExprType(iterator) != INT_TYPE) {
                // error - ARRAY_SIZE_NOT_INT
                printErrorMsg(dimList, ARRAY_SIZE_NOT_INT);
                retval = false;
                addArrayDim(arrayProperties, -4);
                break;
            }
            if (getExprValue(iterator) < 0) {
                // TODO: error - ARRAY_SIZE_NEGATIVE
                retval = false;
                addArrayDim(arrayProperties, -5);
                break;
            }
            if (arrayProperties->dimension >= MAX_ARRAY_DIMENSION) {
                excessiveDim = true;
            }
            addArrayDim(arrayProperties, getExprValue(iterator));
        }
    }
    if (excessiveDim) {
        retval = false;
        // TODO: error - EXCESSIVE_ARRAY_DIM_DECLARATION
    }

    return retval;
}

// func -> [type id param -> [decl ...] block]
int declareFunction(AST_NODE* iterator)
{
    int retval = true;
    unpack(iterator, typeNode, idNode, paramList, blockNode);

    SymbolAttribute* attribute = new(SymbolAttribute);
    FunctionSignature* signature = new(FunctionSignature);

    // attribute
    attribute->attributeKind = FUNCTION_SIGNATURE;
    attribute->attr.functionSignature = signature;

    // declare
    if (declaredLocally(getIDName(idNode))) {
        // TODO: error - SYMBOL_REDECLARE
        printErrorMsgSpecial(typeNode, getIDName(idNode), SYMBOL_REDECLARE);
        retval = false;
    } 
    SymbolTableEntry* entry = enterSymbol(getIDName(idNode), attribute);
    setIDEntry(idNode, entry);

    // TODO: remove function from symtable if failed

    openScope();

    // signature
    // returnType
    loop1 {
        if (!processTypeNode(typeNode)) {
            retval = false;
            break;
        }

        TypeDescriptor* typeDescriptor = getTypeDescriptor(typeNode);
        if (typeDescriptor->kind != SCALAR_TYPE_DESCRIPTOR) {
            // TODO: error - RETURN_ARRAY
            retval = false;
            signature->returnType = ERROR_TYPE;
            break;
        }

        signature->returnType = typeDescriptor->properties.dataType;
    }
    // parameterList
    signature->parametersCount = 0;
    signature->parameterList = NULL;
    Parameter* parameter = NULL;
    AST_NODE* paramIterator = paramList->child;
    forEach (paramIterator) {
        if (!processDeclarationNode(paramIterator)) {
            retval = false;
        } else {
            if (!parameter) {
                parameter = new(Parameter);
                signature->parameterList = parameter;
            } else {
                parameter->next = new(Parameter);
                parameter = parameter->next;
            }
            parameter->next = NULL;
            parameter->parameterName = getParamDeclName(paramIterator);
            parameter->type = getParamDeclType(paramIterator);
            ++signature->parametersCount;
        }
    }

    // block
    retval &= processBlockNode(blockNode);

    closeScope();
    
    if (!retval) removeSymbol(entry);
    return retval;
}
