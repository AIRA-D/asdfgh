#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <variant>
#include <unordered_map>
#include <string>
#include <algorithm>

// (1 + 2) * 3 / 4 + 5 * (6 - 7)

// 1. Токенизация
// 2. Парсер (построение дерева разбора выражения)

// +, -, *, /, %

struct OpeningBracket {};
struct ClosingBracket {};
struct Number { int value; };
struct UnknownToken { std::string value; };
struct MinToken {};
struct MaxToken {};
struct AbsToken {};
struct Plus {};
struct Minus {};
struct Multiply {};
struct Modulo {};
struct Divide {};
struct Sqr {};

using Token = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, MaxToken, AbsToken, Plus, Minus, Multiply, Modulo, Divide, Sqr>;
// 1234

const std::unordered_map<char, Token> kSymbol2Token{
        {'+', Plus{}}, {'-', Minus{}}, {'*', Multiply{}}, {'/', Divide{}}, {'%', Modulo{}}, {'^', Sqr{}}, {'(', OpeningBracket{}}, {')', ClosingBracket{}}, {'|', AbsToken{}}
};

int ToDigit(unsigned char symbol) {
    return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos) {
    int value = 0;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isdigit(symbol)) {
        value = value * 10 + ToDigit(symbol);
        if (pos == input.size() - 1) {
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }
    return Number{value};
}

Token ParseName(const std::string& input, size_t& pos) {
    std::string token_name;
    size_t start_pos = pos;
    while (pos < input.size() && std::isalpha(input[pos])) {
        pos++;
    }
    if (start_pos == pos) {
        return UnknownToken{"Unknown"};
    }
    token_name = input.substr(start_pos, pos - start_pos);
    if (token_name == "min") {
        return MinToken{};
    } else if (token_name == "max") {
        return MaxToken{};
    }
    else return UnknownToken{token_name};
}

std::vector<Token> Tokenize(const std::string &input) {
    std::vector<Token> tokens;
    std::string input_without_spaces = input;
    input_without_spaces.erase(std::remove(input_without_spaces.begin(), input_without_spaces.end(), ' '), input_without_spaces.end());
    const size_t size = input_without_spaces.size();
    size_t position = 0;
    while (position < size) {
        const auto symbol = static_cast<unsigned char>(input_without_spaces[position]);
        if (std::isdigit(symbol)) {
            tokens.emplace_back(ParseNumber(input_without_spaces, position)); continue;
        } else if (auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()) {
            tokens.emplace_back(it->second);
        } else {
            tokens.emplace_back(ParseName(input_without_spaces, position));
        }
        ++position;
    }
    return tokens;
}
