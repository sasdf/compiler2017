#define STRINGIZE(arg)  STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_1(what, iter, x, ...) what(iter, x)
#define FOR_EACH_2(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_1(what, iter, __VA_ARGS__);
#define FOR_EACH_3(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_2(what, iter, __VA_ARGS__);
#define FOR_EACH_4(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_3(what, iter,  __VA_ARGS__);
#define FOR_EACH_5(what, iter, x, ...)\
      what(iter, x);\
       FOR_EACH_4(what,  iter, __VA_ARGS__);
#define FOR_EACH_6(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_5(what,  iter, __VA_ARGS__);
#define FOR_EACH_7(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_6(what,  iter, __VA_ARGS__);
#define FOR_EACH_8(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_7(what,  iter, __VA_ARGS__);

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__) 
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N 
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, iter, x, ...) CONCATENATE(FOR_EACH_, N)(what, iter, x, __VA_ARGS__)
#define FOR_EACH(what, iter, x, ...) FOR_EACH_(FOR_EACH_NARG(x, __VA_ARGS__), what, iter, x, __VA_ARGS__)

#define UNPACK_INTERNAL(iter, varname) AST_NODE* varname = iter; iter = iter->rightSibling;

#define unpack(iter, ...) FOR_EACH(UNPACK_INTERNAL, iter, __VA_ARGS__)
#define new(type) ((type*) malloc(sizeof(type)))
#define forEach(iter, block) while(iter){ block; iter = iter->rightSibling; }

#define getIDName(idNode) (idNode->semantic_value.identifierSemanticValue.identifierName)
#define getIDEntry(idNode) (idNode->semantic_value.identifierSemanticValue.symbolTableEntry)
#define getDeclKind(declNode) (declNode->semantic_value.declSemanticValue.kind)

/* unpack example
AST_NODE* it = parentNode->child;
unpack(it, a, b, d);

=>

a = it; it = it->rightSibling;
...
*/

/* new example
TYPE* x = new(TYPE);
*/

/* forEach example
AST_NODE* it = parentNode->child;
forEach(it, {
    it->...
})
*/
