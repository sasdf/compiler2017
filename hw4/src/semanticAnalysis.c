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
/*added function*/
int processRelopExpr(AST_NODE *relopExpr);


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
    switch(errorMsgKind) {
        case RETURN_TYPE_UNMATCH:
            printf("Incompatible return type.\n");
            break;
        default:
            printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
            break;
    }
}


void semanticAnalysis(AST_NODE *root)
{
    //initializeSymbolTable();
    openScope();
    declarePrimitiveType(SYMBOL_TABLE_INT_NAME, INT_TYPE);
    declarePrimitiveType(SYMBOL_TABLE_FLOAT_NAME, FLOAT_TYPE);
    declarePrimitiveType(SYMBOL_TABLE_VOID_NAME, VOID_TYPE);
    if(!processProgramNode(root))
        g_anyErrorOccur = 1;
    closeScope();
    //symbolTableEnd();
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
        flag &= processDeclarationNode(decl);
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

/*
int checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode)
{
}


int checkAssignmentStmt(AST_NODE* assignmentNode)
{
    //TODO: error - NOT_ASSIGNABLE
}

int checkWriteFunction(AST_NODE* functionCallNode)
{
}
*/

int checkFunctionCall(AST_NODE* funcNode)
{
    assert(funcNode->nodeType == STMT_NODE);
    assert(getStmtKind(funcNode) == FUNCTION_CALL_STMT);
    int retval = true;
    loop1{
        SymbolTableEntry* funcEntry = retrieveSymbol(getIDName(funcNode));
        if (!funcEntry) {
            // TODO: error - SYMBOL_UNDECLARED
            retval = false;
            break;
        }
        SymbolAttribute* typeAttribute = funcEntry->attribute;
        if (typeAttribute->attributeKind != FUNCTION_SIGNATURE) {
            // TODO: error - not a func
            retval = false;
            break;
        }
        setTypeEntry(funcNode, funcEntry);
    }
    return retval;
}

int checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter)
{
    int retval = true;
    //TODO: error - TOO_FEW_ARGUMENTS,
    //TODO: error - TOO_MANY_ARGUMENTS,
    //TODO: error - PASS_ARRAY_TO_SCALAR
    //TODO: error - PASS_SCALAR_TO_ARRAY
    //TODO: error - PARAMETER_TYPE_UNMATCH,
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
            case NONE_TYPE:
            case ERROR_TYPE:
                assert(0/* Operation on strange type */);
                break;
        }
        setExprType(exprNode, getBiggerType(getExprType(exprNode), getExprType(operand)));
        if (!isConstExpr(operand)) {
            exprNode->semantic_value.exprSemanticValue.isConstEval = false;
        }
    }
    if (!isConstExpr(exprNode)) return true;

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
    // TODO
}

int processVariableRValue(AST_NODE* idNode)
{
    // TODO
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
    AST_NODE *child = blockNode->child;
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
    return flag;
}

int processAssignExpr(AST_NODE *assignExpr)
{
    int flag = true;
    if (assignExpr->nodeType == STMT_NODE){                 // ID = relopExpr
        AST_NODE *it = assignExpr->child;
        unpack(it, id, relopExpr);
        flag &= processRelopExpr(relopExpr);
        // TODO: check id == relopExpr        
    } else {                                                // relopExpr
        flag &= processRelopExpr(assignExpr);
    }
    return flag;
}

int processNonEmptyAssignExprList(AST_NODE *assignExprList)
{
    int flag = true;
    AST_NODE *it = assignExprList;
    forEach (it){
        flag &= processAssignExpr(it);
    }
    return flag;
}

int processAssignExprList(AST_NODE *assignExprList)
{
    if (assignExprList->nodeType == NUL_NODE)
        return 1;
    return processNonEmptyAssignExprList(assignExprList->child);
}

int processRelopFactor(AST_NODE *relopFactor)
{
    return processExprRelatedNode(relopFactor);
}

int processRelopTerm(AST_NODE *relopTerm)
{
    assert(relopTerm->nodeType == EXPR_NODE);
    int flag = true;

    if (getExprKind(relopTerm) == BINARY_OPERATION && getExprOp(relopTerm) == BINARY_OP_AND){
        AST_NODE *it = relopTerm->child;
        unpack(it, relopTerm2, relopFactor);
        flag &= processRelopTerm(relopTerm2);
        flag &= processRelopFactor(relopFactor);
    } else {
        flag &= processRelopFactor(relopTerm);
    }

    return flag;
}

int processRelopExpr(AST_NODE *relopExpr)
{
    assert(relopExpr->nodeType == EXPR_NODE);
    int flag = true;

    if (getExprKind(relopExpr) == BINARY_OPERATION && getExprOp(relopExpr) == BINARY_OP_OR){
        AST_NODE *it = relopExpr->child;
        unpack(it, relopExpr2, relopTerm);
        flag &= processRelopExpr(relopExpr2);
        flag &= processRelopTerm(relopTerm);
    } else {
        flag &= processRelopTerm(relopExpr);
    }

    return flag;
}

int processNonEmptyRelopExprList(AST_NODE *relopExprList)
{
    int flag = true;
    AST_NODE *it = relopExprList;
    forEach (it){
        flag &= processRelopExpr(it);
    }
    return flag;
}

int processRelopExprList(AST_NODE *relopExprList)
{
    if (relopExprList->nodeType == NUL_NODE)
        return 1;
    return processNonEmptyRelopExprList(relopExprList);
}

int processWhileStmt(AST_NODE *whileNode)
{
    int flag = true;
    AST_NODE *it = whileNode;
    unpack(it, test, stmt);
    flag &= processAssignExpr(test);
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
    AST_NODE *it = assignNode;
    unpack(it, id, relopExpr);
    flag &= processRelopExpr(relopExpr);
    // TODO: check type(id) == type(expr)
    return flag;
}

int processIfStmt(AST_NODE *ifNode)
{
    int flag = true;
    AST_NODE *it = ifNode;
    unpack(it, test, stmt, elseStmt);
    flag &= processAssignExpr(test);
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
    TypeDescriptor *type = getTypeDescriptor(parent->child);

    assert(type->kind == SCALAR_TYPE_DESCRIPTOR);
    assert(type->properties.dataType == INT_TYPE || 
           type->properties.dataType == FLOAT_TYPE ||
           type->properties.dataType == VOID_TYPE
    );

    // return array not done yet
    switch (returnNode->nodeType){
        case NUL_NODE:
            if (type->properties.dataType != VOID_TYPE){
                printErrorMsg(returnNode, RETURN_TYPE_UNMATCH);
                return 0;
            }
            break;  
        case IDENTIFIER_NODE:
        case CONST_VALUE_NODE:
        case EXPR_NODE:
            flag &= processExprRelatedNode(returnNode);
            DATA_TYPE childType = getExprType(returnNode);

            if (childType == INT_PTR_TYPE || childType == FLOAT_PTR_TYPE){
                printErrorMsg(returnNode, RETURN_ARRAY);
                return 0;
            }

            assert(childType == INT_TYPE || childType == FLOAT_TYPE);

            if (type->properties.dataType == INT_TYPE){
                if (childType == FLOAT_TYPE){
                    printErrorMsg(returnNode, RETURN_TYPE_UNMATCH);
                    return 0;
                }
            } else if (type->properties.dataType == FLOAT_TYPE){
                /*
                TODO: not sure
                if (childType == INT_TYPE){
                    printErrorMsg(returnNode, RETURN_TYPE_UNMATCH);
                    return 0;
                }
                */
            } else if (type->properties.dataType == VOID_TYPE){
                printErrorMsg(returnNode, RETURN_TYPE_UNMATCH);
                return 0;
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
                    flag &= processAssignStmt(stmtNode->child);
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
