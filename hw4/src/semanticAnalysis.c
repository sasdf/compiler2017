#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
#include "macros.h"

// This file is for reference only, you are not required to follow the implementation. //
// You only need to check for errors stated in the hw4 assignment document. //
int g_anyErrorOccur = 0;

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
void processProgramNode(AST_NODE *programNode);
void processDeclarationNode(AST_NODE* declarationNode);
void declareIdList(AST_NODE* typeNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize);
int declareFunction(AST_NODE* returnTypeNode);
int declareParameter(AST_NODE* returnTypeNode);
void processDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize);
int processTypeNode(AST_NODE* typeNode);
void processBlockNode(AST_NODE* blockNode);
void processStmtNode(AST_NODE* stmtNode);
void processGeneralNode(AST_NODE *node);
void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode);
void checkWhileStmt(AST_NODE* whileNode);
void checkForStmt(AST_NODE* forNode);
void checkAssignmentStmt(AST_NODE* assignmentNode);
void checkIfStmt(AST_NODE* ifNode);
void checkWriteFunction(AST_NODE* functionCallNode);
void checkFunctionCall(AST_NODE* functionCallNode);
void processExprRelatedNode(AST_NODE* exprRelatedNode);
void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter);
void checkReturnStmt(AST_NODE* returnNode);
void processExprNode(AST_NODE* exprNode);
void processVariableLValue(AST_NODE* idNode);
void processVariableRValue(AST_NODE* idNode);
void processConstValueNode(AST_NODE* constValueNode);
void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue);
void evaluateExprValue(AST_NODE* exprNode);


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
    // TODO: declare INT, FLOAT...
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


// program -> [global_decl ...]
int processProgramNode(AST_NODE *programNode)
{
    AST_NODE *global_decl = programNode->child;
    while (global_decl){
        processDeclarationNode(global_decl->child);
        global_decl = global_decl->rightSibling;
    }
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
            declareParameter(declarationNode->child);
            break;
    }
}

int processTypeNode(AST_NODE* typeNode)
{
    SymbolTableEntry* typeEntry = retrieveSymbol(getIDName(typeNode));
    setTypeEntry(typeNode, typeEntry);
    if (!typeEntry) {
        // TODO: error - undeclare
    } else {
        SymbolAttribute* typeAttribute = typeEntry->attribute;
        if (typeAttribute->attributeKind != TYPE_ATTRIBUTE) {
            // TODO: error - not a type
        }
    }
    return true;
}


int declareIdList(AST_NODE* declarationNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize)
{
    AST_NODE *iterator = declarationNode;
    unpack(iterator, type);
    int retval = true;
    if (!processTypeNode(typeNode)){
        // TODO: error - invalid type
    } else {
        forEach (iterator){
            if (!declaredLocally(getIDName(iterator))) {
                retval = false;
                // TODO: error - redeclare
            } else {
                SymbolAttribute *attribute = new(SymbolAttribute);
                attribute->attributeKind = isVariableOrTypeAttribute;
                setTypeDescriptor(attribute, getTypeDesciptor(typeNode));
                switch (getIDKind(iterator)) {
                    case NORMAL_ID:
                        break;
                    case ARRAY_ID:
                        break;
                    case WITH_INIT_ID:
                        break;
                }
            }
        }
    }
    return retval;
}

void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode)
{
}

void checkWhileStmt(AST_NODE* whileNode)
{
}


void checkForStmt(AST_NODE* forNode)
{
}


void checkAssignmentStmt(AST_NODE* assignmentNode)
{
}


void checkIfStmt(AST_NODE* ifNode)
{
}

void checkWriteFunction(AST_NODE* functionCallNode)
{
}

void checkFunctionCall(AST_NODE* functionCallNode)
{
}

void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter)
{
}


void processExprRelatedNode(AST_NODE* exprRelatedNode)
{
}

void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue)
{
}

void evaluateExprValue(AST_NODE* exprNode)
{
}


void processExprNode(AST_NODE* exprNode)
{
}


void processVariableLValue(AST_NODE* idNode)
{
}

void processVariableRValue(AST_NODE* idNode)
{
}


void processConstValueNode(AST_NODE* constValueNode)
{
}


void checkReturnStmt(AST_NODE* returnNode)
{
}


void processBlockNode(AST_NODE* blockNode)
{
}


void processStmtNode(AST_NODE* stmtNode)
{
}


void processGeneralNode(AST_NODE *node)
{
}

void processDeclDimList(AST_NODE* idNode, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize)
{
}

// param -> [type (id | array)]
int declareParameter(AST_NODE* iterator)
{
    unpack(iterator, typeNode, idNode);
    openScope();

    SymbolAttribute* attribute = new(SymbolAttribute);
    FunctionSignature* signature = new(FunctionSignature);

    // attribute
    attribute->attributeKind = FUNCTION_SIGNATURE;
    attribute->attr.functionSignature = signature;

    // signature
    // returnType
    if (!processTypeNode(typeNode)) {
        // TODO: error - invalid return type
    } else {
        TypeDescriptor* typeDescriptor = getTypeDescriptor(typeNode);
        if (typeDescriptor->kind != SCALAR_TYPE_DESCRIPTOR) {
            // TODO: error - return array
        } else {
            signature->returnType = typeDescriptor->properties.dataType;
        }
    }
    /* int parametersCount; */
    /* Parameter* parameterList; */
    if (!processDeclarationNode(param)) {
    
    }

    if (declaredLocally(getIDName(idNode))) {
        // TODO: error - redeclare
    } else {
        SymbolTableEntry* entry = enterSymbol(getIDName(idNode), attribute);
        getIDEntry(idNode) = entry;
    }

    closeScope();
    return true;
}

int declareFunction(AST_NODE* iterator)
{
    unpack(iterator, typeNode, idNode, paramIterator, blockNode);
    openScope();

    SymbolAttribute* attribute = new(SymbolAttribute);
    FunctionSignature* signature = new(FunctionSignature);

    // attribute
    attribute->attributeKind = FUNCTION_SIGNATURE;
    attribute->attr.functionSignature = signature;

    // signature
    // returnType
    if (!processTypeNode(typeNode)) {
        // TODO: error - invalid return type
    } else {
        TypeDescriptor* typeDescriptor = getTypeDescriptor(typeNode);
        if (typeDescriptor->kind != SCALAR_TYPE_DESCRIPTOR) {
            // TODO: error - return array
        } else {
            signature->returnType = typeDescriptor->properties.dataType;
        }
    }
    /* int parametersCount; */
    /* Parameter* parameterList; */
    forEach (paramIterator) {
        if (!processDeclarationNode(param)) {
        } else {
        }
    }

    if (declaredLocally(getIDName(idNode))) {
        // TODO: error - redeclare
    } else {
        SymbolTableEntry* entry = enterSymbol(getIDName(idNode), attribute);
        getIDEntry(idNode) = entry;
    }

    closeScope();
    return true;
}
