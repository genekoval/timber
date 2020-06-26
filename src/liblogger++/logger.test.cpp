#include <logger/logger.h>

#include <gtest/gtest.h>

using namespace std::literals;

class LoggerTest : public testing::Test {

};

TEST_F(LoggerTest, Printing) {
    auto log = logger::log(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        logger::level::info
    );

    log.message << "Test message";

    ASSERT_EQ("src/liblogger++/logger.test.cpp"s, log.filename);
    ASSERT_EQ("TestBody"s, log.function_name);
    ASSERT_EQ(15, log.line);
    ASSERT_EQ(logger::level::info, log.log_level);
    ASSERT_EQ("Test message"s, log.message.str());
}
