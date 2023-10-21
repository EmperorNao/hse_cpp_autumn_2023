#pragma once

#include "gtest/gtest.h"

#include "serializer.hpp"
#include "supportive_data.hpp"


class TestSerializer: public ::testing::Test {

protected:

    void SetUp() { }
    void TearDown() { }

};


TEST_F(TestSerializer, testSavingSerializer) {
    std::stringstream out;
    Serializer serializer(out);
    Error err;

    Data d{1, true, 2};

    err = serializer.save(d);
    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(out.str(), "1 true 2");
    out = std::stringstream();

    d = Data{3, false, 5};
    err = serializer.save(d);
    ASSERT_EQ(err, Error::NoError);    
    ASSERT_EQ(out.str(), "3 false 5");
}


TEST_F(TestSerializer, testSavingDifferentSequencesSerializer) {
    std::stringstream out;
    Serializer serializer(out);
    Error err;

    err = serializer(true);
    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(out.str(), "true");
    out = std::stringstream();

    err = serializer(true, false);
    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(out.str(), "true false");
    out = std::stringstream();

    err = serializer(1ul, 2ul, 3ul, 4ul, 5ul);
    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(out.str(), "1 2 3 4 5");
}