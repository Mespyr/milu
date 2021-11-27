#include "../include/ops.h"
#include "../include/compiler.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include <cstdlib>
#include <vector>
#include <iostream>

int main(int argc, char* argv[]) 
{
    File f("examples/1.ilu", MODE_READ);
    std::string code = f.read();

    std::vector<std::string> tokens = tokenize(code);
    std::vector<Op> program = parse_tokens(tokens);

    std::cout << "[info] compiling to out.asm" << std::endl;
    compile_to_asm(program, "out.asm");
    
    std::cout << "[info] generating object file" << std::endl;
    int return_code = std::system("nasm -felf64 out.asm");
    if (return_code != 0) exit(1);

    std::cout << "[info] linking to ./a.out" << std::endl;
    return_code = std::system("ld out.o");
    if (return_code != 0) exit(1);

    return 0;
}
