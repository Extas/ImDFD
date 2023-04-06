#include <BaseWindow.h>
#include <gtest/gtest.h>

class TestBaseWindow : public ::testing::Test {
protected:
  void SetUp() override {
    // Initialize ImGui
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = nullptr; // Disable .ini file
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Initialize test window
    m_Window = new BaseWindow("Test Window", ImVec2(400, 300));
  }

  void TearDown() override {
    // Cleanup
    delete m_Window;
    ImGui::DestroyContext();
  }

  BaseWindow *m_Window = nullptr;
};

TEST_F(TestBaseWindow, TestShow) {
  m_Window->Show();
}

// Automatically generates a main() function for running all the tests
GTEST_API_ int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
