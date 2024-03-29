#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "header.h"


int main( int argc, char *argv[] )
{
    FILE *source, *target;
    Program program;
    SymbolTable symtab;

    if( argc == 3){
        source = fopen(argv[1], "r");
        target = fopen(argv[2], "w");
        if( !source ){
            printf("can't open the source file\n");
            exit(2);
        }
        else if( !target ){
            printf("can't open the target file\n");
            exit(2);
        }
        else{
            program = parser(source);
            fclose(source);
            symtab = build(program);
            check(&program, &symtab);
            constantFolding(program.statements);
            gencode(program, target, &symtab);
        }
    }
    else{
        printf("Usage: %s source_file target_file\n", argv[0]);
    }


    return 0;
}


/********************************************* 
  Scanning 
 *********************************************/
Token getNumericToken( FILE *source, char c )
{
    Token token;
    int i = 0;

    while( isdigit(c) ) {
        token.tok[i++] = c;
        c = fgetc(source);
    }

    if( c != '.' ){
        ungetc(c, source);
        token.tok[i] = '\0';
        token.type = IntValue;
        return token;
    }

    token.tok[i++] = '.';

    c = fgetc(source);
    if( !isdigit(c) ){
        ungetc(c, source);
        printf("Expect a digit : %c\n", c);
        exit(1);
    }

    while( isdigit(c) ){
        token.tok[i++] = c;
        c = fgetc(source);
    }

    ungetc(c, source);
    token.tok[i] = '\0';
    token.type = FloatValue;
    return token;
}

Token scanner( FILE *source )
{
    char c;
    int i;
    Token token;

    while( !feof(source) ){
        c = fgetc(source);

        while( isspace(c) ) c = fgetc(source);

        if( isdigit(c) )
            return getNumericToken(source, c);

        token.tok[0] = c;
        token.tok[1] = '\0';
        if( islower(c) ){
            for( i=1; i<1024; ++i ) {
                token.tok[i] = fgetc(source);
                if( !islower(token.tok[i]) ) {
                    ungetc( token.tok[i], source);
                    token.tok[i] = '\0';
                }
            }
            if( strcmp(token.tok, "f") == 0 )
                token.type = FloatDeclaration;
            else if( strcmp(token.tok, "i") == 0 )
                token.type = IntegerDeclaration;
            else if( strcmp(token.tok, "p") == 0 )
                token.type = PrintOp;
            else
                token.type = Alphabet;
            return token;
        }

        switch(c){
            case '=':
                token.type = AssignmentOp;
                return token;
            case '+':
                token.type = PlusOp;
                return token;
            case '-':
                token.type = MinusOp;
                return token;
            case '*':
                token.type = MulOp;
                return token;
            case '/':
                token.type = DivOp;
                return token;
            case EOF:
                token.type = EOFsymbol;
                token.tok[0] = '\0';
                return token;
            default:
                printf("Invalid character : %c\n", c);
                exit(1);
        }
    }

    token.tok[0] = '\0';
    token.type = EOFsymbol;
    return token;
}


/********************************************************
  Parsing
 *********************************************************/
Declaration parseDeclaration( FILE *source, Token token )
{
    Token token2;
    switch(token.type){
        case FloatDeclaration:
        case IntegerDeclaration:
            token2 = scanner(source);
            if (strcmp(token2.tok, "f") == 0 ||
                    strcmp(token2.tok, "i") == 0 ||
                    strcmp(token2.tok, "p") == 0) {
                printf("Syntax Error: %s cannot be used as id\n", token2.tok);
                exit(1);
            }
            return makeDeclarationNode( token, token2 );
        default:
            printf("Syntax Error: Expect Declaration %s\n", token.tok);
            exit(1);
    }
}

Declarations *parseDeclarations( FILE *source )
{
    int i;
    Token token = scanner(source);
    Declaration decl;
    Declarations *decls;
    switch(token.type){
        case FloatDeclaration:
        case IntegerDeclaration:
            decl = parseDeclaration(source, token);
            decls = parseDeclarations(source);
            return makeDeclarationTree( decl, decls );
        case PrintOp:
        case Alphabet:
            for(i=strlen(token.tok)-1;i>=0;--i) 
              ungetc(token.tok[i], source);
            return NULL;
        case EOFsymbol:
            return NULL;
        default:
            printf("Syntax Error: Expect declarations %s\n", token.tok);
            exit(1);
    }
}

Expression *parseValue( FILE *source )
{
    Token token = scanner(source);
    Expression *value = (Expression *)malloc( sizeof(Expression) );
    value->leftOperand = value->rightOperand = NULL;

    switch(token.type){
        case Alphabet:
            (value->v).type = Identifier;
            strncpy((value->v).val.id, token.tok, 1024);
            break;
        case IntValue:
            (value->v).type = IntConst;
            (value->v).val.ivalue = atoi(token.tok);
            break;
        case FloatValue:
            (value->v).type = FloatConst;
            (value->v).val.fvalue = atof(token.tok);
            break;
        default:
            printf("Syntax Error: Expect Identifier or a Number %s\n", token.tok);
            exit(1);
    }

    return value;
}

Expression *parseExpressionTail( FILE *source, Expression *lvalue )
{
    Token token = scanner(source);
    Expression *expr;
    int i;

    switch(token.type){
        case PlusOp:
            expr = (Expression *)malloc( sizeof(Expression) );
            (expr->v).type = PlusNode;
            (expr->v).val.op = Plus;
            expr->leftOperand = lvalue;
            expr->rightOperand = parseTerm(source);
            return parseExpressionTail(source, expr);
        case MinusOp:
            expr = (Expression *)malloc( sizeof(Expression) );
            (expr->v).type = MinusNode;
            (expr->v).val.op = Minus;
            expr->leftOperand = lvalue;
            expr->rightOperand = parseTerm(source);
            return parseExpressionTail(source, expr);
        case Alphabet:
        case PrintOp:
            for(i=strlen(token.tok)-1;i>=0;--i) 
              ungetc(token.tok[i], source);
            return lvalue;
        case EOFsymbol:
            return lvalue;
        default:
            printf("Syntax Error: Expect a numeric value or an identifier %s\n", token.tok);
            exit(1);
    }
}

Expression *parseExpression( FILE *source, Expression *lvalue )
{
    Token token = scanner(source);
    Expression *expr;
    char *s;
    int i,k;

    switch(token.type){
        case PlusOp:
            expr = (Expression *)malloc( sizeof(Expression) );
            (expr->v).type = PlusNode;
            (expr->v).val.op = Plus;
            expr->leftOperand = lvalue;
            expr->rightOperand = parseTerm(source);
            return parseExpressionTail(source, expr);
        case MinusOp:
            expr = (Expression *)malloc( sizeof(Expression) );
            (expr->v).type = MinusNode;
            (expr->v).val.op = Minus;
            expr->leftOperand = lvalue;
            expr->rightOperand = parseTerm(source);
            return parseExpressionTail(source, expr);
        case Alphabet:
        case PrintOp:
            for(i=strlen(token.tok)-1;i>=0;--i) 
              ungetc(token.tok[i], source);
            return NULL;
        case EOFsymbol:
            return NULL;
        default:
            printf("Syntax Error: Expect a numeric value or an identifier %s\n", token.tok);
            exit(1);
    }
}

Expression *parseTermp( FILE *source, Expression *lvalue )
{
    Token token = scanner(source);
    Expression *expr;
    int i;

    switch(token.type){
        case MulOp:
            expr = (Expression *)malloc( sizeof(Expression) );
            (expr->v).type = MulNode;
            (expr->v).val.op = Mul;
            expr->leftOperand = lvalue;
            expr->rightOperand = parseValue(source);
            return parseTermp(source, expr);
        case DivOp:
            expr = (Expression *)malloc( sizeof(Expression) );
            (expr->v).type = DivNode;
            (expr->v).val.op = Div;
            expr->leftOperand = lvalue;
            expr->rightOperand = parseValue(source);
            return parseTermp(source, expr);
        case Alphabet:
        case PrintOp:
        case PlusOp:
        case MinusOp:
            for(i=strlen(token.tok)-1;i>=0;--i) 
              ungetc(token.tok[i], source);
        case EOFsymbol:
            return lvalue;
        default:
            printf("Syntax Error: Expect a numeric value or an identifier %s\n", token.tok);
            exit(1);
    }
}

Expression *parseTerm( FILE *source )
{
    Expression *val = parseValue(source);
    return parseTermp(source, val);
}

Statement parseStatement( FILE *source, Token token )
{
    Token next_token;
    Expression *value, *expr;

    switch(token.type){
        case Alphabet:
            next_token = scanner(source);
            if(next_token.type == AssignmentOp){
                value = parseTerm(source);
                expr = parseExpression(source, value);
                return makeAssignmentNode(token.tok, value, expr);
            }
            else{
                printf("Syntax Error: Expect an assignment op %s\n", next_token.tok);
                exit(1);
            }
        case PrintOp:
            next_token = scanner(source);
            if(next_token.type == Alphabet)
                return makePrintNode(next_token.tok);
            else{
                printf("Syntax Error: Expect an identifier %s\n", next_token.tok);
                exit(1);
            }
            break;
        default:
            printf("Syntax Error: Expect a statement %s\n", token.tok);
            exit(1);
    }
}

Statements *parseStatements( FILE * source )
{

    Token token = scanner(source);
    Statement stmt;
    Statements *stmts;

    switch(token.type){
        case Alphabet:
        case PrintOp:
            stmt = parseStatement(source, token);
            stmts = parseStatements(source);
            return makeStatementTree(stmt , stmts);
        case EOFsymbol:
            return NULL;
        default:
            printf("Syntax Error: Expect statements %s\n", token.tok);
            exit(1);
    }
}


/*********************************************************************
  Build AST
 **********************************************************************/
Declaration makeDeclarationNode( Token declare_type, Token identifier )
{
    Declaration tree_node;

    switch(declare_type.type){
        case FloatDeclaration:
            tree_node.type = Float;
            break;
        case IntegerDeclaration:
            tree_node.type = Int;
            break;
        default:
            break;
    }
    strncpy(tree_node.name, identifier.tok, 1024);

    return tree_node;
}

Declarations *makeDeclarationTree( Declaration decl, Declarations *decls )
{
    Declarations *new_tree = (Declarations *)malloc( sizeof(Declarations) );
    new_tree->first = decl;
    new_tree->rest = decls;

    return new_tree;
}


Statement makeAssignmentNode( const char* id, Expression *v, Expression *expr_tail )
{
    Statement stmt;
    AssignmentStatement assign;

    stmt.type = Assignment;
    strncpy(assign.id, id, 1024);
    if(expr_tail == NULL)
        assign.expr = v;
    else
        assign.expr = expr_tail;
    stmt.stmt.assign = assign;

    return stmt;
}

Statement makePrintNode( const char* id )
{
    Statement stmt;
    stmt.type = Print;
    strncpy(stmt.stmt.variable, id, 1024);

    return stmt;
}

Statements *makeStatementTree( Statement stmt, Statements *stmts )
{
    Statements *new_tree = (Statements *)malloc( sizeof(Statements) );
    new_tree->first = stmt;
    new_tree->rest = stmts;

    return new_tree;
}

/* parser */
Program parser( FILE *source )
{
    Program program;

    program.declarations = parseDeclarations(source);
    program.statements = parseStatements(source);

    return program;
}


/********************************************************
  Build symbol table
 *********************************************************/
void InitializeTable( SymbolTable *table )
{
    int i;

    for(i = 0 ; i < 26; i++)
        table->table[i] = Notype;
        table->name[i][0] = 0;
}

void add_table( SymbolTable *table, const char* c, DataType t )
{
    static int index = 0;
    int i;

    for (i=0;i<26;++i)
      if (strcmp(table->name[i], c) == 0)
        break;
    if(i != 26)
        printf("Error : id %s has been declared\n", c);//error
    while(index == 'f' - 'a'
        || index == 'i' - 'a'
        || index == 'q' - 'a'
        ) ++index;
    table->table[index] = t;
    strncpy(table->name[index], c, 1024);
    ++index;
}

SymbolTable build( Program program )
{
    SymbolTable table;
    Declarations *decls = program.declarations;
    Declaration current;

    InitializeTable(&table);

    while(decls !=NULL){
        current = decls->first;
        add_table(&table, current.name, current.type);
        decls = decls->rest;
    }

    return table;
}


/********************************************************************
  Type checking
 *********************************************************************/

void convertType( Expression * old, DataType type )
{
    if(old->type == Float && type == Int){
        printf("error : can't convert float to integer\n");
        return;
    }
    if(old->type == Int && type == Float){
        Expression *tmp = (Expression *)malloc( sizeof(Expression) );
        if(old->v.type == Identifier)
            printf("convert to float %s \n",old->v.val.id);
        else
            printf("convert to float %d \n", old->v.val.ivalue);
        tmp->v = old->v;
        tmp->leftOperand = old->leftOperand;
        tmp->rightOperand = old->rightOperand;
        tmp->type = old->type;

        Value v;
        v.type = IntToFloatConvertNode;
        v.val.op = IntToFloatConvert;
        old->v = v;
        old->type = Float;
        old->leftOperand = tmp;
        old->rightOperand = NULL;
    }
}

DataType generalize( Expression *left, Expression *right )
{
    if(left->type == Float || right->type == Float){
        printf("generalize : float\n");
        return Float;
    }
    printf("generalize : int\n");
    return Int;
}

char lookup_id( SymbolTable *table, const char* n )
{
    int i;

    for (i=0;i<26;++i)
      if (strcmp(table->name[i], n) == 0)
        break;
    if(i == 26)
        printf("Error : identifier %s is not declared\n", n);//error
    return i + 'a';
}

DataType lookup_table( SymbolTable *table, const char* n )
{
    int i;

    for (i=0;i<26;++i)
      if (strcmp(table->name[i], n) == 0)
        break;
    if(i == 26)
        printf("Error : identifier %s is not declared\n", n);//error
    return table->table[i];
}

void checkexpression( Expression * expr, SymbolTable * table )
{
    const char* c;
    if(expr->leftOperand == NULL && expr->rightOperand == NULL){
        switch(expr->v.type){
            case Identifier:
                c = expr->v.val.id;
                printf("identifier : %s\n",c);
                expr->type = lookup_table(table, c);
                break;
            case IntConst:
                printf("constant : int\n");
                expr->type = Int;
                break;
            case FloatConst:
                printf("constant : float\n");
                expr->type = Float;
                break;
                //case PlusNode: case MinusNode: case MulNode: case DivNode:
            default:
                break;
        }
    }
    else{
        Expression *left = expr->leftOperand;
        Expression *right = expr->rightOperand;

        checkexpression(left, table);
        checkexpression(right, table);

        DataType type = generalize(left, right);
        convertType(left, type);//left->type = type;//converto
        convertType(right, type);//right->type = type;//converto
        expr->type = type;
    }
}

void checkstmt( Statement *stmt, SymbolTable * table )
{
    if(stmt->type == Assignment){
        AssignmentStatement assign = stmt->stmt.assign;
        printf("assignment : %s \n",assign.id);
        checkexpression(assign.expr, table);
        stmt->stmt.assign.type = lookup_table(table, assign.id);
        if (assign.expr->type == Float && stmt->stmt.assign.type == Int) {
            printf("error : can't convert float to integer\n");
        } else {
            convertType(assign.expr, stmt->stmt.assign.type);
        }
    }
    else if (stmt->type == Print){
        printf("print : %s \n",stmt->stmt.variable);
        lookup_table(table, stmt->stmt.variable);
    }
    else printf("error : statement error\n");//error
}

void check( Program *program, SymbolTable * table )
{
    Statements *stmts = program->statements;
    while(stmts != NULL){
        checkstmt(&stmts->first,table);
        stmts = stmts->rest;
    }
}


/***********************************************************************
  Code generation
 ************************************************************************/
void fprint_op( FILE *target, ValueType op )
{
    switch(op){
        case MinusNode:
            fprintf(target,"-\n");
            break;
        case PlusNode:
            fprintf(target,"+\n");
            break;
        case MulNode:
            fprintf(target,"*\n");
            break;
        case DivNode:
            fprintf(target,"/\n");
            break;
        default:
            fprintf(target,"Error in fprintf_op ValueType = %d\n",op);
            break;
    }
}

void fprint_expr( FILE *target, Expression *expr, SymbolTable* table)
{

    if(expr->leftOperand == NULL){
        switch( (expr->v).type ){
            case Identifier:
                fprintf(target,"l%c\n", lookup_id(table, (expr->v).val.id));
                break;
            case IntConst:
                if (expr->v.val.ivalue < 0)
                    fprintf(target,"0\n%d\n-",-(expr->v).val.ivalue);
                else
                    fprintf(target,"%d\n",(expr->v).val.ivalue);
                break;
            case FloatConst:
                if (expr->v.val.fvalue < 0)
                    fprintf(target,"0.0\n%f\n-", -(expr->v).val.fvalue);
                else
                    fprintf(target,"%f\n", (expr->v).val.fvalue);
                break;
            default:
                fprintf(target,"Error In fprint_left_expr. (expr->v).type=%d\n",(expr->v).type);
                break;
        }
    }
    else{
        fprint_expr(target, expr->leftOperand, table);
        if(expr->rightOperand == NULL){
            fprintf(target,"5k\n");
        }
        else{
            //	fprint_right_expr(expr->rightOperand);
            fprint_expr(target, expr->rightOperand, table);
            fprint_op(target, (expr->v).type);
        }
    }
}

void foldNode(Expression *curr){
    static short end = 0;
    int lt = -1, rt = -1, swap = 0;
    /* if(!curr || end) return; */
    if(!curr) return;
    Expression *lc = curr->leftOperand, *rc = curr->rightOperand, *tmp;
    foldNode(lc);
    foldNode(rc);
    /* if(end) return; */
    printf("jizz: ");
    print_expr(curr);
    puts("");
    if (lc) lt = lc->v.type;
    if (rc) rt = rc->v.type;
    switch((curr->v).type){
            case Identifier:
                //printf("%s ", (expr->v).val.id);
                end = 1;
                break;
            case IntConst:
            case FloatConst:
            case IntToFloatConvertNode:
                break;
            case MinusNode:
            case MulNode:
            case DivNode:
            case PlusNode:
                //printf("+ ");
                if (lt == IntConst && rt == IntConst){
                    if (curr->v.type == PlusNode)
                        curr->v.val.ivalue = lc->v.val.ivalue + rc->v.val.ivalue;
                    if (curr->v.type == MinusNode)
                        curr->v.val.ivalue = lc->v.val.ivalue - rc->v.val.ivalue;
                    if (curr->v.type == MulNode)
                        curr->v.val.ivalue = lc->v.val.ivalue * rc->v.val.ivalue;
                    if (curr->v.type == DivNode)
                        curr->v.val.ivalue = lc->v.val.ivalue / rc->v.val.ivalue;
                    curr->v.type = IntConst;
                    free(lc);
                    free(rc);
                    curr->leftOperand = NULL;
                    curr->rightOperand = NULL;
                }
                else if (lt == FloatConst && rt == FloatConst){
                    if (curr->v.type == PlusNode)
                        curr->v.val.fvalue = lc->v.val.fvalue + rc->v.val.fvalue;
                    if (curr->v.type == MinusNode)
                        curr->v.val.fvalue = lc->v.val.fvalue - rc->v.val.fvalue;
                    if (curr->v.type == MulNode)
                        curr->v.val.fvalue = lc->v.val.fvalue * rc->v.val.fvalue;
                    if (curr->v.type == DivNode)
                        curr->v.val.fvalue = lc->v.val.fvalue / rc->v.val.fvalue;
                    curr->v.type = FloatConst;
                    free(lc);
                    free(rc);
                    curr->leftOperand = NULL;
                    curr->rightOperand = NULL;
                }
                else if (lt == FloatConst || rt == FloatConst){
                    if (rt == FloatConst){
                        tmp = rc;
                        rc = lc;
                        lc = tmp;
                        swap = 1;
                    }
                    if (curr->v.type == PlusNode)
                        curr->v.val.fvalue = lc->v.val.fvalue + rc->leftOperand->v.val.ivalue;
                    if (curr->v.type == MinusNode)
                        if (swap) curr->v.val.fvalue = -lc->v.val.fvalue + rc->leftOperand->v.val.ivalue;
                        else curr->v.val.fvalue = lc->v.val.fvalue - rc->leftOperand->v.val.ivalue;
                    if (curr->v.type == MulNode)
                        curr->v.val.fvalue = lc->v.val.fvalue * rc->leftOperand->v.val.ivalue;
                    if (curr->v.type == DivNode)
                        if (swap) curr->v.val.fvalue = rc->leftOperand->v.val.ivalue / lc->v.val.fvalue;
                        else curr->v.val.fvalue = lc->v.val.fvalue / rc->leftOperand->v.val.ivalue;
                    curr->v.type = FloatConst;
                    free(rc->leftOperand);
                    free(lc);
                    free(rc);
                    curr->leftOperand = NULL;
                    curr->rightOperand = NULL;
                }
                break;
            default:
                printf("error %d\n", curr->v.type);
                break;
    }
}


void constantFolding(Statements *curr){
    while(curr){
        printf("folding: %s\n", curr->first.stmt.variable);
        foldNode(curr->first.stmt.assign.expr);
        curr = curr->rest;
    }
}

void gencode(Program prog, FILE * target, SymbolTable* table)
{
    Statements *stmts = prog.statements;
    Statement stmt;

    while(stmts != NULL){
        stmt = stmts->first;
        switch(stmt.type){
            case Print:
                fprintf(target,"l%c\n", lookup_id(table, stmt.stmt.variable));
                fprintf(target,"p\n");
                break;
            case Assignment:
                fprint_expr(target, stmt.stmt.assign.expr, table);
                /*
                   if(stmt.stmt.assign.type == Int){
                   fprintf(target,"0 k\n");
                   }
                   else if(stmt.stmt.assign.type == Float){
                   fprintf(target,"5 k\n");
                   }*/
                fprintf(target,"s%c\n",lookup_id(table, stmt.stmt.assign.id));
                fprintf(target,"0 k\n");
                break;
        }
        stmts=stmts->rest;
    }

}


/***************************************
  For our debug,
  you can omit them.
 ****************************************/
void print_expr(Expression *expr)
{
    if(expr == NULL)
        return;
    else{
        print_expr(expr->leftOperand);
        switch((expr->v).type){
            case Identifier:
                printf("%s ", (expr->v).val.id);
                break;
            case IntConst:
                printf("%d ", (expr->v).val.ivalue);
                break;
            case FloatConst:
                printf("%f ", (expr->v).val.fvalue);
                break;
            case PlusNode:
                printf("+ ");
                break;
            case MinusNode:
                printf("- ");
                break;
            case MulNode:
                printf("* ");
                break;
            case DivNode:
                printf("/ ");
                break;
            case IntToFloatConvertNode:
                printf("(float) ");
                break;
            default:
                printf("error %d\n", expr->v.type);
                break;
        }
        print_expr(expr->rightOperand);
    }
}

void test_parser( FILE *source )
{
    Declarations *decls;
    Statements *stmts;
    Declaration decl;
    Statement stmt;
    Program program = parser(source);

    decls = program.declarations;

    while(decls != NULL){
        decl = decls->first;
        if(decl.type == Int)
            printf("i ");
        if(decl.type == Float)
            printf("f ");
        printf("%s ",decl.name);
        decls = decls->rest;
    }

    stmts = program.statements;

    while(stmts != NULL){
        stmt = stmts->first;
        if(stmt.type == Print){
            printf("p %s ", stmt.stmt.variable);
        }

        if(stmt.type == Assignment){
            printf("%s = ", stmt.stmt.assign.id);
            print_expr(stmt.stmt.assign.expr);
        }
        stmts = stmts->rest;
    }

}
