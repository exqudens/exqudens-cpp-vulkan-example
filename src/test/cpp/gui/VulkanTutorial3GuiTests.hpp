#pragma once

#include <cstdlib>
#include <cstdint>
#include <vector>
#include <memory>
#include <exception>
#include <iostream>

#include <gtest/gtest.h>
#include <exqudens/Log.hpp>
#include <exqudens/log/api/Logging.hpp>

// vulkan
#include <vulkan/vulkan_raii.hpp>

// glfw
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "TestUtils.hpp"

class VulkanTutorial3GuiTests: public testing::Test {

    public:

        inline static const char* LOGGER_ID = "VulkanTutorial3GuiTests";

    protected:

        struct Data {
            std::shared_ptr<vk::raii::Context> context = {};
            std::shared_ptr<vk::raii::Instance> instance = {};
        };

        class Application {

            private:

                inline static const uint32_t WIDTH = 800;
                inline static const uint32_t HEIGHT = 600;

                GLFWwindow* window = nullptr;

                std::shared_ptr<Data> data = {};

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
                    data = std::make_shared<Data>();
                    createInstance(*data.get());
                }

                void mainLoop() {
                    while (!glfwWindowShouldClose(window)) {
                        glfwPollEvents();
                    }
                }

                void cleanup() {
                    data.reset();
                    glfwDestroyWindow(window);
                    glfwTerminate();
                }

                void createInstance(Data& data) {
                    uint32_t glfwExtensionCount = 0;
                    const char** glfwExtensions = nullptr;
                    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
                    std::vector<const char*> glfwInstanceRequiredExtensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

                    EXQUDENS_LOG_INFO(LOGGER_ID) << "glfwInstanceRequiredExtensions.size: " << glfwInstanceRequiredExtensions.size();

                    vk::ApplicationInfo applicationInfo = vk::ApplicationInfo()
                        .setApiVersion(VK_API_VERSION_1_0)
                        .setPApplicationName("Hello Triangle")
                        .setApplicationVersion(VK_MAKE_VERSION(1, 0, 0))
                        .setPEngineName("No Engine")
                        .setEngineVersion(VK_MAKE_VERSION(1, 0, 0));

                    vk::InstanceCreateInfo instanceCreateInfo = vk::InstanceCreateInfo()
                        .setPApplicationInfo(&applicationInfo)
                        .setPEnabledExtensionNames(glfwInstanceRequiredExtensions)
                        .setEnabledLayerCount(0);

                    data.context = std::make_shared<vk::raii::Context>();
                    data.instance = std::make_shared<vk::raii::Instance>(
                        *data.context.get(),
                        instanceCreateInfo
                    );
                }

        };

};


/*
    @brief vulkan-tutorial.com/Drawing_a_triangle/Setup/Validation_layers
*/
TEST_F(VulkanTutorial3GuiTests, test1) {
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
