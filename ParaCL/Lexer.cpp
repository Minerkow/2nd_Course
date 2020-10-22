#include "Lexer.h"

namespace lexer {
    Lexer_t::Lexer_t(const std::string& code) {
        size_t lineNum = 1;

        int i = 0;
        while (code[i]) {
            //READ SPACE

            if (isspace(code[i])) {
                if (code[i] == '\n') {
                    lineNum++;
                }
                i++;
                continue;
            }

            //READ NUMBERS

            if (isdigit(code[i])) {
                int num = 0;
                while (isdigit(code[i])) {
                    num = num * 10 + code[i] - '0';
                    i++;
                }
                lexArray_.push_back(Number_t{ lineNum, num});
                i++;
                continue;
            }

            //READ OPERATION

            if (IsOperation(code[i])) {
                lexArray_.push_back(Operation_t{ lineNum, code[i]});
                i++;
                continue;
            }

            //READ COMPAR SIGNS

            if (IsComparSign(code[i])) {
                std::string sign{code[i]};
                if (IsComparSign(code[i + 1])) {
                    sign.push_back(code[i+1]);
                }
                lexArray_.push_back(ComparSign_t{lineNum, sign});
                if (sign != "=") {
                    i += sign.size();
                    continue;
                }
            }

            //READ BRACE

            if (IsBrace(code[i])) {
                lexArray_.push_back(Brace_t{lineNum, code[i]});
                i++;
                continue;
            }

            //READ VARIABLES AND COMMAND

            if (isalpha(code[i])) {
                std::string word;
                while (isalpha(code[i]) || isdigit(code[i])) {
                    word.push_back(code[i]);
                    i++;
                }
                if (IsCommand(word)) {
                    lexArray_.push_back(Command_t{lineNum, word});
                    continue;
                }
                if (variables_.count(word) == 0) {
                    variables_.emplace(word, NAN);
                }
                continue;
            }

            //READ SPECIAL CHARACTERS

            if (IsSpecialCharacters(code[i])) {
                lexArray_.push_back(Command_t{lineNum, code[i]});
                i++;
                continue;
            }
        }
    }

    Operation_t::Operation_t(size_t line, char sym) : Lexem_t(line) {
        switch ( sym )
        {
            case '+':
                kind_ = ADD; break;
            case '-':
                kind_ = SUB; break;
            case '*':
                kind_ = MUL; break;
            case '/':
                kind_ = DIV;
            default:
                std::cerr << "Unknown symbol, line - " << line << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    ComparSign_t::ComparSign_t(size_t line, std::string &sign) : Lexem_t(line) {
        if (sign == "!") {
            kind_ = NOT;
            return;
        }
        if (sign == "==") {
            kind_ = EQUAL;
            return;
        }
        if (sign == "!=") {
            kind_ = NOT_EQUAL;
            return;
        }
        if (sign == ">=") {
            kind_ = EQ_OR_GR;
            return;
        }
        if (sign == "<=") {
            kind_ = EQ_OR_LESS;
            return;
        }
        if (sign == "==") {
            kind_ = EQUAL;
            return;
        }
        if (sign == ">") {
            kind_ = GREATER;
            return;
        }
        if (sign == "<") {
            kind_ = LESS;
            return;
        }
        std::cerr << "Unknown symbol, line - " << line << std::endl;
        exit(EXIT_FAILURE);
    }

    Brace_t::Brace_t(size_t line, char sym) : Lexem_t(line) {
        switch (sym) {
            case '(':
                kind_ = LBRAC; break;
            case ')':
                kind_ = RBRAC; break;
            case '{':
                kind_ = LFIGURBRAC; break;
            case '}':
                kind_ = RFIGURBRAC; break;
            default:
                std::cerr << "Unknown symbol, line - " << line << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    Command_t::Command_t(size_t line, char sym) : Lexem_t(line){
        switch (sym) {
            case '?':
                kind_ = INPUT; break;
            case ';':
                kind_ = END_COMMAND; break;
            case '=':
                kind_ = ASSIGN; break;
            default:
                std::cerr << "Unknown symbol, line - " << line << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    Command_t::Command_t(size_t line, std::string &command) : Lexem_t(line) {
        if (command == "print") {
            kind_ = PRINT;
        }
        if (command == "if") {
            kind_ = IF;
        }
        if (command == "while") {
            kind_ = WHILE;
        }
        std::cerr << "Unknown symbol, line - " << line << std::endl;
        exit(EXIT_FAILURE);
    }
}

namespace lexer {
    bool IsOperation(char sym) {
        return sym == '+' || sym == '-' || sym == '/' || sym == '*';
    }

    bool IsComparSign(char sym) {
        return sym == '<' || sym == '>' || sym == '=';
    }

    bool IsBrace(char sym) {
        return sym == '(' || sym == ')';
    }

    bool IsSpecialCharacters(char sym) {
        return sym == '=' || sym == '?' || sym == ';';
    }

    bool IsCommand(const std::string& word) {
        return word == "print" || word == "if" || word == "while";
    }
}