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
int declarePrimitiveType(char* name, DATA_TYPE type);
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
int processVariableLValue(AST_NODE* idNode);
int processVariableRValue(AST_NODE* idNode);
int processConstValueNode(AST_NODE* constValueNode);
int evaluateExprValue(AST_NODE* exprNode);


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

void printErrorMsgSpecial(AST_NODE* node1, char* name2, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node1->linenumber);
    /*
       switch(errorMsgKind)
       {
       default:
       printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
       break;
       }
       */
}


void printErrorMsg(AST_NODE* node, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node->linenumber);
    /*
       switch(errorMsgKind)
       {
       printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
       break;
       }
       */
}


void semanticAnalysis(AST_NODE *root)
{
    initializeSymbolTable();
    declarePrimitiveType(SYMBOL_TABLE_INT_NAME, INT_TYPE);
    declarePrimitiveType(SYMBOL_TABLE_FLOAT_NAME, FLOAT_TYPE);
    declarePrimitiveType(SYMBOL_TABLE_VOID_NAME, VOID_TYPE);
    openScope();
    processProgramNode(root);
    closeScope();
    symbolTableEnd();
}


DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2)
{
    if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE) {
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
        flag &= processDeclarationNode(decl->child);
    }
    return flag;
}

// program -> [global_decl ...]
int processProgramNode(AST_NODE *programNode)
{
    processDeclarationList(programNode);
    //AST_NODE *global_decl = programNode->child;
    //forEach (global_decl){
    //    processDeclarationNode(global_decl->child);
    //}
}

// global_decl -> var_decl | type_decl | func_decl | func_param_decl
int processDeclarationNode(AST_NODE* declarationNode)
{
    switch (getDeclKind(declarationNode)){
        case VARIABLE_DECL:
            setDeclKind(declarationNode, VARIABLE_DECL);
            declareIdList(declarationNode->child, VARIABLE_ATTRIBUTE, false);
            break;
        case TYPE_DECL:
            setDeclKind(declarationNode, TYPE_DECL);
            declareIdList(declarationNode->child, TYPE_ATTRIBUTE, false);
            break;
        case FUNCTION_DECL:
            declareFunction(declarationNode->child);
            break;
        case FUNCTION_PARAMETER_DECL:
            declareIdList(declarationNode->child, VARIABLE_ATTRIBUTE, true);
            break;
    }
}

// typeNode -- idNode
int processTypeNode(AST_NODE* typeNode)
{
    int retval = true;
    loop1 {
        SymbolTableEntry* typeEntry = retrieveSymbol(getIDName(typeNode));
        if (!typeEntry) {
            // TODO: error - SYMBOL_UNDECLARED
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

int declarePrimitiveType(char* name, DATA_TYPE type)
{
    TypeDescriptor* typeDescriptor = new(TypeDescriptor);
    typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;
    typeDescriptor->properties.dataType = type;

    SymbolAttribute *attribute = new(SymbolAttribute);
    attribute->attributeKind = TYPE_ATTRIBUTE;
    attribute->attr.typeDescriptor = typeDescriptor;

    SymbolTableEntry* entry = enterSymbol(name, attribute);
    return true;
}

// [type id]
int declareNormalId(AST_NODE* idNode, TypeDescriptor* type, SymbolAttribute* attribute, int isParameter)
{
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
    int retval = true;
    loop1 {
        if (type->kind == ARRAY_TYPE_DESCRIPTOR) {
            // TODO: error - array of array
            retval = false;
            break;
        }

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
            assert(type->properties.dataType == INT_TYPE || type->properties.dataType == FLOAT_TYPE);
        }

        TypeDescriptor* typeDescriptor = new(TypeDescriptor);
        typeDescriptor->kind = ARRAY_TYPE_DESCRIPTOR;
        typeDescriptor->properties.arrayProperties.elementType = type->properties.dataType;

        retval &= processDeclDimList(idNode->child, typeDescriptor, isParameter);

        attribute->attr.typeDescriptor = typeDescriptor;
    }
    return retval;
}

// [type id -> expr]
int declareInitId(AST_NODE* idNode, TypeDescriptor* type, SymbolAttribute* attribute, int isParameter)
{
    int retval = true;
    assert(!isParameter); // enforced by grammar
    if (type->kind == ARRAY_TYPE_DESCRIPTOR) {
        // TODO: error - TRY_TO_INIT_ARRAY
    } else {
        attribute->attr.typeDescriptor = type;
        retval &= processExprNode(idNode->child);
        if (retval) {
            DATA_TYPE dataType = type->properties.dataType;
            DATA_TYPE exprType = getExprType(idNode->child);
            if (checkAssignable(dataType, exprType, isParameter)) {
                // TODO: error - NOT_ASSIGNABLE
            }
        }
    }
    return retval;
}

// [type (NORMAL_ID | ARRAY_ID | WITH_INIT_ID)]
int declareId(AST_NODE* idNode, TypeDescriptor* type, SymbolAttributeKind kind, int isParameter)
{
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
            retval = declareArrayId(idNode, type, attribute, isParameter);
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
            if (!declaredLocally(getIDName(iterator))) {
                retval = false;
                // TODO: error - SYMBOL_REDECLARE
            } else {
                retval &= declareId(iterator, typeDescriptor, kind, isParameter);
            }
        }
    }
    return retval;
}

int checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode)
{
}

int checkWhileStmt(AST_NODE* whileNode)
{
}


int checkForStmt(AST_NODE* forNode)
{
}


int checkAssignmentStmt(AST_NODE* assignmentNode)
{
}


int checkIfStmt(AST_NODE* ifNode)
{
}

int checkWriteFunction(AST_NODE* functionCallNode)
{
}

int checkFunctionCall(AST_NODE* functionCallNode)
{
}

int checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter)
{
}


// const | (expr -> [op ...])
int processExprRelatedNode(AST_NODE* exprRelatedNode)
{
    int retval = true;
    switch(exprRelatedNode->nodeType) {
        case CONST_VALUE_NODE:
            retval &= processConstValueNode(exprRelatedNode);
        case EXPR_NODE:
            retval &= processExprNode(exprRelatedNode);
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

    // Need to be constant expr
    AST_NODE* operand = exprNode->child;
    forEach(operand) {
        if (!isConstExpr(operand)) {
            exprNode->semantic_value.exprSemanticValue.isConstEval = false;
            return true;
        }
    }

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
    if(retval) {
        if(!evaluateExprValue(exprNode)) {
            retval = false;
        }
    }
    return retval;
}


int processVariableLValue(AST_NODE* idNode)
{
}

int processVariableRValue(AST_NODE* idNode)
{
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
            assert(0/* unknown const type */);

    }
    return true;
}


int checkReturnStmt(AST_NODE* returnNode)
{
}

int  processStatementList(AST_NODE *stmtList){
    int flag = true;
    AST_NODE *stmt = stmtList->child;
    forEach (stmt){
        flag &= processStmtNode(stmt->child);
    }
    return flag;
}

// block -> decl_list stmt_list | stmt_list | decl_list
int processBlockNode(AST_NODE* blockNode)
{
    int flag = true;
    AST_NODE *child = blockNode->child;
    if (child->rightSibling){       // decl_list stmt_list
        flag &= processDeclarationList(child);
        flag &= processStatementList(child->rightSibling);
    } else{
        if (child->nodeType == VARIABLE_DECL_LIST_NODE)     // decl_list
            flag &= processDeclarationList(child);
        else if (child->nodeType == STMT_LIST_NODE)         // stmt_list
            flag &= processStatementList(child);
        else assert(0);
    }
    return flag;
}


int processStmtNode(AST_NODE* stmtNode)
{
    
}


int processGeneralNode(AST_NODE *node)
{
}

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
                // TODO: error - ARRAY_SIZE_NOT_INT
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
            if (arrayProperties->dimension >= 10) {
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
    openScope();

    SymbolAttribute* attribute = new(SymbolAttribute);
    FunctionSignature* signature = new(FunctionSignature);

    // attribute
    attribute->attributeKind = FUNCTION_SIGNATURE;
    attribute->attr.functionSignature = signature;

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
                Parameter* parameter = new(Parameter);
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

    // declare
    if (declaredLocally(getIDName(idNode))) {
        // TODO: error - SYMBOL_REDECLARE
        retval = false;
    }
    if (retval) {
        SymbolTableEntry* entry = enterSymbol(getIDName(idNode), attribute);
        getIDEntry(idNode) = entry;
    }

    closeScope();
    return retval;
}
