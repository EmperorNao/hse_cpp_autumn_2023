#pragma once

#include <map>
#include <ranges>
#include <limits>

#include "gtest/gtest.h"

#include "parser.hpp"


class TestParser: public ::testing::Test {

protected:
    TokenParser* parser;
    std::map<std::string, int> strMap;
    std::map<uint64_t, int> uint64Map;

    StringTokenCallback stringCallback;
    DigitTokenCallback digitCallback;

    StartEndCallback startCallback;
    StartEndCallback endCallback;

    void SetUp() { 
        parser = new TokenParser(); 
        strMap.clear();
        uint64Map.clear();

        stringCallback = [&strMap = strMap](std::string_view& s){ 
            auto copy_of_string = std::string{s};
            if (!strMap.contains(copy_of_string)) {
                strMap[copy_of_string] = 0;
            }
            strMap[copy_of_string] += 1;
        };

        digitCallback = [&uint64Map = uint64Map](uint64_t number){ 
            if (!uint64Map.contains(number)) {
                uint64Map[number] = 0;
            }
            uint64Map[number] += 1;
        };

        startCallback = [&strMap = strMap, &uint64Map = uint64Map](){ 
            strMap.clear();
            uint64Map.clear();
        };

        endCallback = [&strMap = strMap, &uint64Map = uint64Map](){ 
            strMap["end"] = 1;
            uint64Map[0] = 1;
        };        
        
    }

    void TearDown() { delete parser; }

};


TEST_F(TestParser, testEmptyStringParser) {
    ASSERT_NO_THROW(parser->parse(""));
}

TEST_F(TestParser, testStringTokenCallbackParser) {

    parser->setStringTokenCallback(this->stringCallback);

    parser->parse("one one");
    ASSERT_EQ(2, strMap["one"]);
    ASSERT_NE(2, strMap["two"]);
}

TEST_F(TestParser, testDelimitersParser) {

    parser->setStringTokenCallback(this->stringCallback);

    parser->parse("  \none\tone one   two");

    auto kv = std::views::keys(strMap);
    std::vector<std::string> keys{ kv.begin(), kv.end()};

    ASSERT_EQ(2, keys.size());
    ASSERT_EQ(3, strMap["one"]);
    ASSERT_EQ(1, strMap["two"]);
}

TEST_F(TestParser, testDigitTokenCallbackParser) {

    parser->setStringTokenCallback(this->stringCallback);
    parser->setDigitTokenCallback(this->digitCallback);

    parser->parse("one\t123\none123");
    ASSERT_EQ(1, strMap["one"]);
    ASSERT_EQ(1, uint64Map[123]);
}

TEST_F(TestParser, testSignedFloatDigitTokenCallbackParser) {

    parser->setStringTokenCallback(this->stringCallback);
    parser->setDigitTokenCallback(this->digitCallback);

    parser->parse("+1 -1 +0 -0 0 2.0");

    auto kv = std::views::keys(uint64Map);
    std::vector<uint64_t> keys{ kv.begin(), kv.end()};

    ASSERT_EQ(1, keys.size());
    ASSERT_EQ(1, uint64Map[0]);
}

TEST_F(TestParser, testMaxUint64DigitTokenCallbackParser) {

    parser->setStringTokenCallback(this->stringCallback);
    parser->setDigitTokenCallback(this->digitCallback);

    auto max_uint64 = std::numeric_limits<uint64_t>::max();
    auto str_max_uint64 = std::to_string(max_uint64);
    auto overflow_str = str_max_uint64 + "1";

    parser->parse(str_max_uint64);
    ASSERT_EQ(0, strMap[str_max_uint64]);
    ASSERT_EQ(1, uint64Map[max_uint64]);
}

TEST_F(TestParser, testOverflowDigitTokenCallbackParser) {

    parser->setStringTokenCallback(this->stringCallback);
    parser->setDigitTokenCallback(this->digitCallback);

    auto max_uint64 = std::numeric_limits<uint64_t>::max();
    auto str_max_uint64 = std::to_string(max_uint64);
    auto overflow_str = str_max_uint64 + "1";

    parser->parse(overflow_str);
    auto kv = std::views::keys(uint64Map);
    std::vector<uint64_t> keys{ kv.begin(), kv.end()};

    ASSERT_EQ(1, strMap[overflow_str]);
    ASSERT_EQ(0, keys.size());

}

TEST_F(TestParser, testStartCallbackParser) {

    parser->setStringTokenCallback(this->stringCallback);

    parser->parse("one two");
    ASSERT_EQ(1, strMap["one"]);
    ASSERT_EQ(1, strMap["two"]);

    parser->parse("one two");
    ASSERT_EQ(2, strMap["one"]);
    ASSERT_EQ(2, strMap["two"]);

    parser->setStartCallback(this->startCallback);

    parser->parse("one two");
    ASSERT_EQ(1, strMap["one"]);
    ASSERT_EQ(1, strMap["two"]);

}

TEST_F(TestParser, testEndCallbackParser) {

    parser->setStringTokenCallback(this->stringCallback);

    parser->parse("one two");
    ASSERT_EQ(false, strMap.contains("end"));

    parser->setEndCallback(this->endCallback);

    parser->parse("one two");
    ASSERT_EQ(true, strMap.contains("end"));

}
