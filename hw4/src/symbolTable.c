#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "macros.h"
// This file is for reference only, you are not required to follow the implementation. //

int HASH(char * str) {
    int idx=0;
    while (*str){
        idx = idx << 1;
        idx+=*str;
        str++;
    }
    return (idx & (HASH_TABLE_SIZE-1));
}

SymbolTable symbolTable;

SymbolTableEntry* freeSymbolTableEntry(SymbolTableEntry* entry)
{
    free(entry);
}

SymbolTableEntry* newSymbolTableEntry(int nestingLevel)
{
    SymbolTableEntry* symbolTableEntry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    symbolTableEntry->nextInHashChain = NULL;
    symbolTableEntry->prevInHashChain = NULL;
    symbolTableEntry->nextInSameLevel = NULL;
    symbolTableEntry->attribute = NULL;
    symbolTableEntry->name = NULL;
    symbolTableEntry->nestingLevel = nestingLevel;
    return symbolTableEntry;
}

void removeFromHashChain(int hashIndex, SymbolTableEntry* entry)
{
    // hash table
    assert(entry->prevInHashChain == NULL);
    assert(symbolTable.hashTable[hashIndex] == entry);
    symbolTable.hashTable[hashIndex] = entry->nextInHashChain;
    if (entry->nextInHashChain)
        entry->nextInHashChain->prevInHashChain = NULL;

    // scope display
    assert(symbolTable.scopeDisplay->nextInSameLevel == entry);
    symbolTable.scopeDisplay->nextInSameLevel = entry->nextInSameLevel;
}

void enterIntoHashChain(int hashIndex, SymbolTableEntry* entry)
{
    // hash table
    SymbolTableEntry *tmp = symbolTable.hashTable[hashIndex];
    symbolTable.hashTable[hashIndex] = entry;
    entry->nextInHashChain = tmp;
    entry->prevInHashChain = NULL;
    if (tmp) tmp->prevInHashChain = entry;

    // scope display
    entry->nextInSameLevel = symbolTable.scopeDisplay->nextInSameLevel;
    symbolTable.scopeDisplay->nextInSameLevel = entry;
    
}

void initializeSymbolTable()
{
    memset(&symbolTable, 0, sizeof(SymbolTable));
}

void symbolTableEnd()
{
    while (symbolTable.scopeDisplay) closeScope();
}

SymbolTableEntry* retrieveSymbol(char* symbolName)
{
    int hash = HASH(symbolName);
    SymbolTableEntry* entry = symbolTable.hashTable[hash];
    while (entry){
        if (strcmp(entry->name, symbolName) == 0)
            break;
        entry = entry->nextInHashChain;
    }
    return entry;
}

SymbolTableEntry* enterSymbol(char* symbolName, SymbolAttribute* attribute)
{
    int hash = HASH(symbolName);
    SymbolTableEntry *tmp = newSymbolTableEntry(symbolTable.currentLevel);
    tmp->name = strdup(symbolName);
    tmp->attribute = attribute;

    enterIntoHashChain(hash, tmp);
    
    return tmp;
}

//remove the symbol from the current scope
void removeSymbol(SymbolTableEntry* entry)
{
    int hash = HASH(entry->name);
    removeFromHashChain(hash, entry);
    assert(entry->name);
    free(entry->name);
    freeSymbolTableEntry(entry);
}

int declaredLocally(char* symbolName)
{
    SymbolTableEntry* entry = retrieveSymbol(symbolName);
    if (entry && entry->nestingLevel == symbolTable.currentLevel)
        return 1;
    return 0;
}

void openScope()
{
    ScopeEntry* scope = new(ScopeEntry);
    scope->nextInSameLevel = NULL;
    scope->outerScope = symbolTable.scopeDisplay;
    symbolTable.scopeDisplay = scope;
    ++symbolTable.currentLevel;
}

void closeScope()
{
    ScopeEntry* scope = symbolTable.scopeDisplay;
    assert (scope);
    while (scope->nextInSameLevel)
        removeSymbol(scope->nextInSameLevel);
    symbolTable.scopeDisplay = scope->outerScope;
    --symbolTable.currentLevel;
    free(scope);
}
