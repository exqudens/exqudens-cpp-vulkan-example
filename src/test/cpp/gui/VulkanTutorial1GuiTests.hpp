#pragma once

#include <cstdlib>
#include <exception>
#include <iostream>

#include <gtest/gtest.h>
#include <exqudens/Log.hpp>
#include <exqudens/log/api/Logging.hpp>

// glfw
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "TestUtils.hpp"

class VulkanTutorial1GuiTests: public testing::Test {

    public:

        inline static const char* LOGGER_ID = "VulkanTutorial1GuiTests";

    protected:

        class Application {

            private:

                inline static const uint32_t WIDTH = 800;
                inline static const uint32_t HEIGHT = 600;

                GLFWwindow* window = nullptr;

            public:

                void run() {
                    initWindow();
                    initVulkan();
                    mainLoop();
                    cleanup();
                }

            private:

                void initWindow() {
                    glfwInit();

                    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

                    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
                }

                void initVulkan() {
                }

                void mainLoop() {
                    while (!glfwWindowShouldClose(window)) {
                        glfwPollEvents();
                    }
                }

                void cleanup() {
                    glfwDestroyWindow(window);
                    glfwTerminate();
                }

        };

};


/*
    @brief vulkan-tutorial.com/Drawing_a_triangle/Setup/Base_code
*/
TEST_F(VulkanTutorial1GuiTests, test1) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        EXQUDENS_LOG_INFO(LOGGER_ID) << "bgn";

        Application app;

        app.run();

        EXQUDENS_LOG_INFO(LOGGER_ID) << "end";
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}
