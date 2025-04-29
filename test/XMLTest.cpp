//
// Created by Dustin on 4/27/25.
//

#include "../include/XMLParser.h"

#include <gtest/gtest.h>

TEST(XMLTest, BasicTagNoAttributesNoChildren) {
    auto& p = XMLParser::GetInstance();

    std::string src = "<tag></tag>";
    auto node = p.Parse(src);

    EXPECT_EQ(node->tag_, "tag");
    EXPECT_EQ(node->children_.size(), 0);
    EXPECT_EQ(node->attributes_.size(), 0);
}

TEST(XMLTest, BasicTagNoChildren) {
    auto& p = XMLParser::GetInstance();

    std::string src = "<tag attr1=\"val1\" attr2=\"val2\"></tag>";
    auto node = p.Parse(src);

    EXPECT_EQ(node->tag_, "tag");
    EXPECT_EQ(node->children_.size(), 0);
    EXPECT_EQ(node->attributes_.size(), 2);
    EXPECT_EQ(node->attributes_["attr1"], "val1");
    EXPECT_EQ(node->attributes_["attr2"], "val2");
}

TEST(XMLTest, BasicTag) {
    auto& p = XMLParser::GetInstance();

    std::string src = "<tag1 attr1=\"val1\" attr2=\"val2\">"
                      "<tag2></tag2>"
                      "<tag3 attr1=\"val1\" attr2=\"val2\" attr3=\"val3\"></tag3>"
                      "</tag1>";
    auto node = p.Parse(src);

    EXPECT_EQ(node->tag_, "tag1");
    EXPECT_EQ(node->children_.size(), 2);
    EXPECT_EQ(node->attributes_.size(), 2);
    EXPECT_EQ(node->attributes_["attr1"], "val1");
    EXPECT_EQ(node->attributes_["attr2"], "val2");

    auto& child1 = node->children_[0];
    EXPECT_EQ(child1->tag_, "tag2");
    EXPECT_EQ(child1->children_.size(), 0);
    EXPECT_EQ(child1->attributes_.size(), 0);


    auto& child2 = node->children_[1];
    EXPECT_EQ(child2->tag_, "tag3");
    EXPECT_EQ(child2->children_.size(), 0);
    EXPECT_EQ(child2->attributes_.size(), 3);
    EXPECT_EQ(child2->attributes_["attr1"], "val1");
    EXPECT_EQ(child2->attributes_["attr2"], "val2");
    EXPECT_EQ(child2->attributes_["attr3"], "val3");
}

//TEST(XMLTest, BasicTagNested) {
//    std::string src = "<tag1 attr1=\"val1\" attr2=\"val2\">"
//                      "<tag2>"
//                      "<nestedChildTag1></nestedChildTag1>"
//                      "<nestedChildTag2></nestedChildTag2>"
//                      "</tag2>"
//                      "<tag3 attr1=\"val1\" attr2=\"val2\"></tag3>"
//                      "</tag1>";
//}