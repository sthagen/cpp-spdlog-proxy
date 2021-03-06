#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <string>
#include <sstream>

#include <doctest/doctest.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/ostream_sink.h>


TEST_SUITE ("Example derived tests.") {
    TEST_CASE ("First test.") {
        std::ostringstream oss;
        auto os_logger = spdlog::get("test_logger");
        if (!os_logger) {
            auto os_sink = std::make_shared<spdlog::sinks::ostream_sink_st>(oss);
            os_logger = std::make_shared<spdlog::logger>("test_logger", os_sink);
            os_logger->set_pattern("%v");
            os_logger->set_level(spdlog::level::debug);
        }
        spdlog::set_default_logger(os_logger);

        SUBCASE("Welcome to spdlog.") {
            /* Example snippet:
             *
             * spdlog::info("Welcome to spdlog!");
             */
            auto payload = "Welcome to spdlog!";
            spdlog::info(payload);
            
            std::string test = oss.str();
                INFO(">>>", test, "<<<");
                CHECK(!test.empty());
                CHECK(test.find(payload) != std::string::npos);
                REQUIRE(test.find('\n') != std::string::npos);
            oss.str("");
        }

        SUBCASE("Some error message with arg.") {
            /* Example snippet:
             *
             * spdlog::error("Some error message with arg: {}", 1);
             */
            auto payload = "Some error message with arg: 1";
            spdlog::error("Some error message with arg: {}", 1);
            
            std::string test = oss.str();
                REQUIRE(test.find(payload) != std::string::npos);
            oss.str("");
        }

        SUBCASE("Easy padding in numbers like.") {
            /* Example snippet:
             *
             * spdlog::warn("Easy padding in numbers like {:08d}", 12);
             */
            auto payload = "Easy padding in numbers like 00000012";
            spdlog::warn("Easy padding in numbers like {:08d}", 12);
            
            std::string test = oss.str();
                REQUIRE(test.find(payload) != std::string::npos);
            oss.str("");
        }

        SUBCASE("Support for int,  hex, oct, and bin.") {
            /* Example snippet:
             *
             * spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
             */
            auto payload = "Support for int: 42;  hex: 2a;  oct: 52; bin: 101010";
            spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
            
            std::string test = oss.str();
                REQUIRE(test.find(payload) != std::string::npos);
            oss.str("");
        }

        SUBCASE("Support for floats.") {
            /* Example snippet:
             *
             * spdlog::info("Support for floats {:03.2f}", 1.23456);
             */
            auto payload = "Support for floats 1.23";
            spdlog::info("Support for floats {:03.2f}", 1.23456);
            
            std::string test = oss.str();
                REQUIRE(test.find(payload) != std::string::npos);
            oss.str("");
        }

        SUBCASE("Positional args are supported too.") {
            /* Example snippet:
             *
             * spdlog::info("Positional args are {1} {0}..", "too", "supported");
             */
            auto payload = "Positional args are supported too..";
            spdlog::info("Positional args are {1} {0}..", "too", "supported");
            
            std::string test = oss.str();
                REQUIRE(test.find(payload) != std::string::npos);
            oss.str("");
        }

        SUBCASE("Left aligned.") {
            /* Example snippet:
             *
             * spdlog::info("{:<30}", "left aligned");
             */
            auto payload = "left aligned";
            spdlog::info("{:<30}", "left aligned");
            
            std::string test = oss.str();
                REQUIRE(test.find(payload) != std::string::npos);
            oss.str("");
        }

        SUBCASE("This (debug) message should be displayed.") {
            /* Example snippet:
             *
             * spdlog::set_level(spdlog::level::debug); // Set global log level to debug
             * spdlog::debug("This message should be displayed..");  
             */
            auto payload = "This message should be displayed.";
            spdlog::set_level(spdlog::level::debug); // Set global log level to debug
            spdlog::debug("This message should be displayed..");  
            
            std::string test = oss.str();
                REQUIRE(test.find(payload) != std::string::npos);
            oss.str("");
        }
    }
}
