#include <iostream>

enum Token {
    tok_eof = -1,

    tok_def = -2,
    tok_extern = -3,

    tok_identifier = -4,
    tok_number = -5,
};

static std::string IdentifierStr;
static double NumVal;

//返回从标准输入输出中获得的下一个Token
static int get_tok() {
    static char LastChar = ' ';

    //跳过空格
    while (std::isspace(LastChar)) {
        std::cin >> LastChar;
    }

    //处理标识符
    if (std::isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while (std::cin >> LastChar) {
            if (std::isalnum(LastChar)) {
                IdentifierStr += LastChar;
            } else {
                break;
            }
        }
        if (IdentifierStr == "def") {
            return tok_def;
        } else if (IdentifierStr == "extern") {
            return tok_extern;
        } else {
            return tok_identifier;
        }
    }

    //处理浮点数
    if (std::isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;
        do {
            NumStr += LastChar;
            std::cin >> LastChar;
        } while (std::isdigit(LastChar) || LastChar == '.');

        NumVal = std::stod(NumStr);
        return tok_number;
    }

    //处理注释
    if (LastChar == '#') {
        //#之后的字符全部忽略
        do {
            std::cin >> LastChar;
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF) {
            return get_tok();
        }
    }

    //如果上述的判断都不满足，那么LastChar要么是个EOF，要么是个操作符（如'+'）
    //对于操作符（如'+'），直接返回它的ASCII码
    if (LastChar == EOF) {
        return tok_eof;
    }

    int op_ascii = LastChar;
    std::cin >> LastChar;
    return op_ascii;
}

int main() {
    char a = '+';
    int b = a;
    std::cout << b;

    return 0;
}


