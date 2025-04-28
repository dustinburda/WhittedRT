//
// Created by Dustin on 4/26/25.
//

#include "../include/XMLParser.h"



XMLParser::XMLParser(std::string src) : src_{std::move(src)}, pos_{0} {}

XMLParser::XMLParser(std::filesystem::path path) : pos_{0} {
    std::ifstream file {path};
    auto file_size = std::filesystem::file_size(path);

    src_.resize(file_size);
    file.read(src_.data(), file_size);
}

XMLNodePtr XMLParser::Parse() {
    auto root_node = ParseNode();
    return root_node;
}

std::optional<char> XMLParser::Peek() {
    if (pos_ >= src_.size())
        return std::nullopt;

    return src_[pos_];
}

std::optional<std::string> XMLParser::PeekAhead(int n) {
    int amount_left = std::max(std::min(n, static_cast<int>(src_.size() - pos_)), 0);

    if (amount_left == 0)
        return std::nullopt;

    return src_.substr(pos_, amount_left);
}

std::optional<char> XMLParser::Consume() {
    if (pos_ >= src_.size())
        return std::nullopt;

    auto next_char = src_[pos_];
    pos_++;

    return next_char;
}

bool XMLParser::IsWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

void XMLParser::ConsumeWhitespace() {
    while (Peek().has_value() && IsWhitespace(Peek().value()))
        pos_++;
}

std::string XMLParser::ConsumeAlphabetic() {
    std::string s;
    while (Peek().has_value() && std::isalpha(Peek().value()))
        s.push_back(Consume().value());
    return s;
}

int XMLParser::ConsumeNumeric() {
    std::string s;
    while (Peek().has_value() && std::isdigit(Peek().value()))
        s.push_back(Consume().value());
    return std::stoi(s);
}

std::string XMLParser::ConsumeAlphaNumeric() {
    std::string s;
    while (Peek().has_value() && std::isalnum(Peek().value()))
        s.push_back(Consume().value());
    return s;
}

std::string XMLParser::ConsumeUntilToken(char c) {
    std::string s;
    while (Peek().has_value() && Peek().value() != c) {
        s.push_back(Consume().value());
    }

    return s;
}

std::unordered_map<std::string, std::string> XMLParser::ParseAttributes() {
    std::unordered_map<std::string, std::string> attributes;

    while (Peek() != '>') {
        ConsumeWhitespace();
        auto attribute = ConsumeUntilToken('=');
        Consume(); // =
        Consume(); // '
        auto value = ConsumeUntilToken('\"');
        Consume(); //'
        attributes[attribute] = value;
    }

    return attributes;
}

XMLNodePtr XMLParser::ParseNode() {
    ConsumeWhitespace();

    auto node = std::make_unique<XMLNode>();

    Consume(); // <
    ConsumeWhitespace();

    node->tag_ = ConsumeAlphaNumeric();
    ConsumeWhitespace();

    node->attributes_ = ParseAttributes();
    ConsumeWhitespace();

    ConsumeUntilToken('>');
    Consume(); // >

    node->children_ = ParseChildren();

    ConsumeWhitespace();
    Consume(); // <
    Consume(); // /
    ConsumeUntilToken('>'); // tagname
    Consume(); // >


    return node;
}

std::vector<XMLNodePtr> XMLParser::ParseChildren() {
    std::vector<XMLNodePtr> children;

    while(PeekAhead(2).has_value() && PeekAhead(2).value() != "</") {
        children.push_back(ParseNode());
    }

    return children;
}