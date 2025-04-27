//
// Created by Dustin on 4/26/25.
//

#include "../include/XMLParser.h"



XMLParser::XMLParser(std::string src) : src_{std::move(src)}, pos_{0} {}

XMLParser::XMLParser(std::filesystem::path path) : pos_{0} {
    std::ifstream file {path};

    std::stringstream ss;
    ss << file.rdbuf();

    src_ = ss.str();
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

std::optional<char> XMLParser::Consume() {
    if (pos_ >= src_.size())
        return std::nullopt;

    auto next_char = src_[pos_];
    pos_++;

    return src_[pos_];
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



XMLNodePtr XMLParser::ParseNode() {
    ConsumeWhitespace();

    auto node = std::make_unique<XMLNode>();

    Consume(); // <
    ConsumeWhitespace();

//    node->tag_
//    node->children_ = ParseChildren();
    return nullptr;
}

std::vector<XMLNodePtr> XMLParser::ParseChildren() {
//    std::vector<XMLNodePtr> children;
//
//    while(Peek())
    return {};
}