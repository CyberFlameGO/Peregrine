#include "lexer/lexer.hpp"
#include "lexer/tokens.hpp"
#include "parser/parser.hpp"
#include "codegen/codegen.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    std::ifstream file("./Peregrine/test.pe");
    std::stringstream buf;
    buf << file.rdbuf();

    std::vector<Token> tokens = lexer("54 * 12 / 2", "test");
    
    for (auto& tok : tokens) {
        std::cout << tok.keyword << " " << tok.tk_type << "\n";
    }

    Parser parser(tokens);

    AstNodePtr program = parser.parse();
    
    std::cout << program->stringify() << "\n";

    Codegen codegen("out.txt");

    codegen.generate(program);

    return 0;
}