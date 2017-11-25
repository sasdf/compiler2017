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
void declareFunction(AST_NODE* returnTypeNode);
void processDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize);
void processTypeNode(AST_NODE* typeNode);
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

int processDeclarationList(AST_NODE* declarationList){
    int flag = true;
    AST_NODE *decl = declarationList->child;
    forEach (decl){
        flag &= processDeclarationNode(decl->child);
    }
    return flag;
}

// program -> [global_decl]
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
            declareIdList(declarationNode->child, VARIABLE_ATTRIBUTE, 0);
            break;
        case TYPE_DECL:
            setDeclKind(declarationNode, TYPE_DECL);
            declareIdList(declarationNode->child, TYPE_ATTRIBUTE, 0);
            break;
        case FUNCTION_DECL:
            break;
        case FUNCTION_PARAMETER_DECL:
            break;
    }
}

void processTypeNode(AST_NODE* idNodeAsType)
{
    SymbolTableEntry* typeEntry = getTypeEntry(typeNode);
    if (!typeEntry) {
        // TODO: error - undeclare
    } else {
        SymbolAttribute* typeAttribute = typeEntry->attribute;
        if (typeAttribute->attributeKind != TYPE_ATTRIBUTE) {
            // TODO: error - not a type
        } else {
            TypeDescriptor* typeDescriptor = typeAttribute->attr.typeDescriptor;
            if (typeDescriptor->kind != SCALAR_TYPE_DESCRIPTOR) {
                // TODO: error - return array
            } else {
                signature->returnType = typeDescriptor->properties.dataType;
            }
        }
    }
}


void declareIdList(AST_NODE* declarationNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize)
{
    AST_NODE *it = declarationNode;
    unpack(it, type);
    if (!processTypeNode(type)){
        // TODO
    } else {
        forEach (it){
            SymbolAttribute *tmp = new(SymbolAttribute);
            tmp->attributeKind = isVariableOrTypeAttribute;
            setTypeDescriptor(tmp, getTypeDesciptor(type));
            // TODO
    }
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


void processStmtNode(AST_NODE* stmtNode)
{
    
}


void processGeneralNode(AST_NODE *node)
{
}

void processDeclDimList(AST_NODE* idNode, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize)
{
}

// func -> [type id param block]
int declareFunction(AST_NODE* declarationNode)
{
    AST_NODE* iterator = declarationNode->child;
    unpack(iterator, typeNode, idNode, paramNode, blockNode);

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
        TypeDescriptor* typeDescriptor = typeAttribute->attr.typeDescriptor;
        if (typeDescriptor->kind != SCALAR_TYPE_DESCRIPTOR) {
            // TODO: error - return array
        } else {
            signature->returnType = typeDescriptor->properties.dataType;
        }
    }

    if (declaredLocally(getIDName(idNode))) {
        // TODO: error - redeclare
    } else {
        SymbolTableEntry* entry = enterSymbol(getIDName(idNode), attribute);
        getIDEntry(idNode) = entry;
    }
    return true;
}
