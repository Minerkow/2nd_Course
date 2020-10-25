#include "Lexer.h"

namespace lexer {
    LexArray_t::LexArray_t(const std::string& code) {
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
                lexArray_.push_back(new Number_t{ lineNum, num});
                i++;
                continue;
            }

            //READ OPERATION

            if (IsOperation(code[i])) {
                lexArray_.push_back(new Operation_t{ lineNum, code[i]});
                i++;
                continue;
            }

            //READ COMPAR SIGNS

            if (IsComparSign(code[i])) {
                std::string sign{code[i]};
                if (IsComparSign(code[i + 1])) {
                    sign.push_back(code[i+1]);
                }
                if (sign != "=") {
                    lexArray_.push_back(new ComparSign_t{lineNum, sign});
                    i += sign.size();
                    continue;
                }
            }

            //READ BRACE

            if (IsBrace(code[i])) {
                lexArray_.push_back(new Brace_t{lineNum, code[i]});
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
                    lexArray_.push_back(new Command_t{lineNum, word});
                    continue;
                }
                lexArray_.push_back(new Variable_t{lineNum, word});
                continue;
            }

            //READ SPECIAL CHARACTERS

            if (IsSpecialCharacters(code[i])) {
                lexArray_.push_back(new Command_t{lineNum, code[i]});
                i++;
                continue;
            }
            std::cerr << "Unknown symbol" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    Operation_t::Operation_t(size_t line, char sym) : Lexem_t(line, OPERATION) {
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

    ComparSign_t::ComparSign_t(size_t line, std::string &sign) : Lexem_t(line, COMPAR_SIGN) {
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

    Brace_t::Brace_t(size_t line, char sym) : Lexem_t(line, BRACE) {
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

    Command_t::Command_t(size_t line, char sym) : Lexem_t(line, COMMAND){
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

    Command_t::Command_t(size_t line, std::string &command) : Lexem_t(line, COMMAND) {
        if (command == "print") {
            kind_ = PRINT;
            return;
        }
        if (command == "if") {
            kind_ = IF;
            return;
        }
        if (command == "while") {
            kind_ = WHILE;
            return;
        }
        std::cerr << "Unknown symbol, line - " << line << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ostream &Number_t::Print(std::ostream &os) {
        os << "NUM: " << number_ << " ";
        return os;
    }

    std::ostream &Operation_t::Print(std::ostream &os) {
        switch (kind_) {
            case ADD:
                os << "ADD "; break;
            case SUB:
                os << "SUB "; break;
            case MUL:
                os << "MUL "; break;
            case DIV:
                os << "DIV ";
            default:
                std::cerr << "Unknown Operation, line - " << line_ << std::endl;
                exit(EXIT_FAILURE);
        }
        return os;
    }

    std::ostream &ComparSign_t::Print(std::ostream &os) {
        switch (kind_) {
            case NOT:
                os << "NOT "; break;
            case  EQUAL:
                os << "EQUAL "; break;
            case NOT_EQUAL:
                os << "NOT_EQUAL "; break;
            case GREATER:
                os << "GREATER "; break;
            case LESS:
                os << "LESS "; break;
            case EQ_OR_LESS:
                os << "EQ_OR_LESS "; break;
            case EQ_OR_GR:
                os << "EQ_OR_GR "; break;
            default:
                std::cerr << "Unknown Operation, line - " << line_ << std::endl;
                exit(EXIT_FAILURE);
        }
        return os;
    }

    std::ostream &Brace_t::Print(std::ostream &os) {
        switch (kind_) {
            case LBRAC:
                os << "LBRAC "; break;
            case RBRAC:
                os << "RBRAC "; break;
            case LFIGURBRAC:
                os << "LFIGURBRAC "; break;
            case RFIGURBRAC:
                os << "RFIGURBRAC "; break;
            default:
                std::cerr << "Unknown Operation, line - " << line_ << std::endl;
                exit(EXIT_FAILURE);
        }
        return os;
    }

    std::ostream &Command_t::Print(std::ostream &os) {
        switch (kind_) {
            case PRINT:
                os << "PRINT "; break;
            case INPUT:
                os << "INPUT "; break;
            case ASSIGN:
                os << "ASSIGN "; break;
            case END_COMMAND:
                os << "END_COMMAND "; break;
            case IF:
                os << "IF "; break;
            case WHILE:
                os << "WHILE "; break;
            default:
                std::cerr << "Unknown Operation, line - " << line_ << std::endl;
                exit(EXIT_FAILURE);
        }
        return os;
    }

    std::ostream &Variable_t::Print(std::ostream &os) {
        os << "VAR: " << name_ << " ";
        return os;
    }


}

namespace lexer {
    bool IsOperation(char sym) {
        return sym == '+' || sym == '-' || sym == '/' || sym == '*';
    }

    bool IsComparSign(char sym) {
        return sym == '<' || sym == '>' || sym == '=' || sym == '!';
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

    std::ostream& operator<<(std::ostream& os, LexArray_t& lexer) {
        for (auto& it : lexer.lexArray_) {
            switch (it->KindLexem()) {
                case Lexem_t::NUMBER:
                    dynamic_cast<Number_t*>(it)->Print(os); break;
                case Lexem_t::OPERATION:
                    dynamic_cast<Operation_t*>(it)->Print(os); break;
                case Lexem_t::COMPAR_SIGN:
                    dynamic_cast<ComparSign_t*>(it)->Print(os); break;
                case Lexem_t::BRACE:
                    dynamic_cast<Brace_t*>(it)->Print(os); break;
                case Lexem_t::COMMAND:
                    dynamic_cast<Command_t*>(it)->Print(os); break;
                case Lexem_t::VARIABLE:
                    dynamic_cast<Variable_t*>(it)->Print(os); break;
                default:
                    std::cerr << "Unknown Lexem\n";
                    exit(EXIT_FAILURE);
            }
        }
        return os;
    }

    LexArray_t::~LexArray_t() {
        for (auto& it : lexArray_) {
            switch (it->KindLexem()) {
                case Lexem_t::NUMBER:
                    delete dynamic_cast<Number_t*>(it); break;
                case Lexem_t::OPERATION:
                    delete dynamic_cast<Operation_t*>(it); break;
                case Lexem_t::COMPAR_SIGN:
                    delete dynamic_cast<ComparSign_t*>(it); break;
                case Lexem_t::BRACE:
                    delete dynamic_cast<Brace_t*>(it); break;
                case Lexem_t::COMMAND:
                    delete dynamic_cast<Command_t*>(it); break;
                case Lexem_t::VARIABLE:
                    delete dynamic_cast<Variable_t*>(it); break;
                default:
                    std::cerr << "Delete ERROR\n";
                    exit(EXIT_FAILURE);
            }
        }
    }

    Brace_t::Kind_t LexArray_t::FigurBrace(size_t index) {
        Lexem_t* lex = lexArray_[index];
        if (lex->KindLexem() == Lexem_t::BRACE)
        {
            Brace_t* brace = dynamic_cast<Brace_t*>(lex);
            if (brace->Kind() == Brace_t::LFIGURBRAC ||
                brace->Kind() == Brace_t::RFIGURBRAC) {
                return brace->Kind();
            }
        }
        return Brace_t::POISON;
    }

    bool LexArray_t::IsEndCommand(size_t index) {
        Lexem_t *lex = lexArray_[index];
        if (lex->KindLexem() == Lexem_t::COMMAND) {
            Command_t *comm = dynamic_cast<Command_t *>(lex);
            if (comm->Kind() == Command_t::END_COMMAND) {
                return true;
            }
        }
        return false;
    }

    Command_t::Kind_t LexArray_t::Command(size_t index) {
        Lexem_t* lex = lexArray_[index];
        if (lex->KindLexem() == Lexem_t::COMMAND) {
            Command_t *comm = dynamic_cast<Command_t*>(lex);
            return comm->Kind();
        }
        return Command_t::POISON;
    }

    bool LexArray_t::IsComparison(size_t index) {
        Lexem_t* lex = lexArray_[index];
        if (lex->KindLexem() == Lexem_t::COMPAR_SIGN) {
            return true;
        }
        return false;
    }

    ComparSign_t::Kind_t LexArray_t::ComparSign(size_t index) {
        Lexem_t* lex = lexArray_[index];
        if (lex->KindLexem() == Lexem_t::COMPAR_SIGN) {
            ComparSign_t* cs = dynamic_cast<ComparSign_t*>(lex);
            return cs->Kind();
        }
        return ComparSign_t::POISON;
    }

    bool LexArray_t::IsAddSub(size_t index) {
        Lexem_t* lex = lexArray_[index];
        if (lex->KindLexem() == Lexem_t::OPERATION) {
            Operation_t* op = dynamic_cast<Operation_t*>(lex);
            if (op->Kind() == Operation_t::ADD || op->Kind() == Operation_t::SUB) {
                return true;
            }
        }
        return false;
    }

    bool LexArray_t::IsMulDiv(size_t index) {
        Lexem_t* lex = lexArray_[index];
        if (lex->KindLexem() == Lexem_t::OPERATION) {
            Operation_t* op = dynamic_cast<Operation_t*>(lex);
            if (op->Kind() == Operation_t::MUL || op->Kind() == Operation_t::DIV) {
                return true;
            }
        }
        return false;
    }

    bool LexArray_t::IsTerm(size_t index) {
        Lexem_t* lex = lexArray_[index];
        if (lex->KindLexem() == Lexem_t::COMMAND) {
            Command_t* cm = dynamic_cast<Command_t*>(lex);
            if (cm->Kind() == Command_t::INPUT) {
                return true;
            }
            return false;
        }
        if (lex->KindLexem() == Lexem_t::VARIABLE ||
            lex->KindLexem() == Lexem_t::NUMBER) {
            return true;
        }
        return false;
    }

    bool LexArray_t::IsInput(size_t index) {
        Lexem_t* lex = lexArray_[index];
        if (lex->KindLexem() == Lexem_t::COMMAND) {
            Command_t *cm = dynamic_cast<Command_t *>(lex);
            if (cm->Kind() == Command_t::INPUT) {
                return true;
            }
        }
        return false;
    }

    bool LexArray_t::IsNumber(size_t index) {
        if (lexArray_[index]->KindLexem() == Lexem_t::NUMBER) {
            return true;
        }
        return false;
    }

    bool LexArray_t::IsVariable(size_t index) {
        if (lexArray_[index]->KindLexem() == Lexem_t::VARIABLE) {
            return true;
        }
        return false;
    }

    Brace_t::Kind_t LexArray_t::Brace(size_t index) {
        Lexem_t* lex = lexArray_[index];
        if (lex->KindLexem() == Lexem_t::BRACE) {
            Brace_t* br = dynamic_cast<Brace_t*>(lex);
            return br->Kind();
        }
        return Brace_t::POISON;
    }


}