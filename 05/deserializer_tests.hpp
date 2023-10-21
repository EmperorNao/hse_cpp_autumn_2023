#pragma once

#include "gtest/gtest.h"

#include "deserializer.hpp"
#include "supportive_data.hpp"


class TestDeserializer: public ::testing::Test {

protected:

    void SetUp() { }
    void TearDown() { }

};


TEST_F(TestDeserializer, testLoadingDeserializer) {
    std::stringstream out;
    Deserializer deserializer(out);
    Error err;

    Data d{0, false, 0};
    out << "1 true 2";
    err = deserializer.load(d);

    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(d.a, 1);
    ASSERT_EQ(d.b, true);
    ASSERT_EQ(d.c, 2);
}


TEST_F(TestDeserializer, testLoadingDifferentSequencesDeserializer) {
    std::stringstream out;
    Deserializer deserializer(out);
    Error err;

    uint64_t uia = 0, uib = 0, uic = 0;
    out << "1 2 3";
    err = deserializer(uia, uib, uic);

    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(uia, 1);
    ASSERT_EQ(uib, 2);
    ASSERT_EQ(uic, 3);
    out = std::stringstream();


    bool b1 = false, b2 = false;
    out << "false true";
    err = deserializer(b1, b2);


    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(b1, false);
    ASSERT_EQ(b2, true);
}

TEST_F(TestDeserializer, testBoolCorruptionDeserializer) {
    std::stringstream out;
    Deserializer deserializer(out);
    Error err;

    out << "truesads";

    bool b1 = false, b2 = false;
    err = deserializer(b1);
    ASSERT_EQ(err, Error::CorruptedArchive);
    out = std::stringstream();

    out << "true falsesad";

    b1 = false, b2 = false;
    err = deserializer(b1, b2);
    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST_F(TestDeserializer, testUint64CorruptionDeserializer) {
    std::stringstream out;
    Deserializer deserializer(out);
    Error err;

    out << "-1 0";

    uint64_t ui1 = 0, ui2 = 0;
    err = deserializer(ui1, ui2);
    ASSERT_EQ(err, Error::CorruptedArchive);
    out = std::stringstream();

    out << "9999999999999999999999 0";
    ui1 = 0, ui2 = 0;
    err = deserializer(ui1, ui2);
    ASSERT_EQ(err, Error::CorruptedArchive);
}