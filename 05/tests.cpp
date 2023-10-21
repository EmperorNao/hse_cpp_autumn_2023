#include "error_tests.hpp"
#include "serializer_tests.hpp"
#include "deserializer_tests.hpp"


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}