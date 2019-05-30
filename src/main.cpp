#include <iostream>

extern int yyparse();
extern NBlock* programBlock;

static void traversal(NBlock *blockNode);

int main(int argc, char **argv) {
    yyparse();

    traversal(programBlock);

    return 0;
}