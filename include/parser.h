#ifndef ILU_PARSER_H
#define ILU_PARSER_H

#include "ops.h"
#include "token.h"
#include "error.h"
#include "lexer.h"
#include "file.h"
#include "program.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

std::string add_escapes_to_string(std::string str);
void print_error_if_illegal_word(Token tok, Program program);
std::vector<Op> link_ops(std::vector<Op> ops);
Op convert_token_to_op(Token tok, Program program);
Program parse_tokens(std::vector<Token> tokens);

#endif
