#include <ui/MainMenuBar.h>

#include <logging/Logger.h>

MainMenuBar::MainMenuBar() {
  SetupFileMenu();
  SetupEditMenu();
  SetupViewMenu();
  SetupHelpMenu();
}

void MainMenuBar::SetupFileMenu() {
  auto &file_menu = GetOrAddMenu("File");

  file_menu.AddItem("New", [this]() { Logger::Trace("New menu item clicked"); });
  file_menu.AddItem("Open", [this]() {
    Logger::Trace("Open menu item clicked");
    file_dialog_.SetTitle("Open File");
    // file_dialog_.SetTypeFilters({".h", ".cpp"});
    file_dialog_.Open();
  });
  file_menu.AddItem("Save", [this]() {
    Logger::Trace("Save menu item clicked");
    file_dialog_.SetTitle("Save File");
    // file_dialog_.SetTypeFilters({".h", ".cpp"});
    file_dialog_.Open();
  });

  file_menu.AddItem("Save As", [this]() {
    Logger::Trace("Save As menu item clicked");
    file_dialog_.SetTitle("Save File As");
    // file_dialog_.SetTypeFilters({".h", ".cpp"});
    file_dialog_.Open();
  });
  file_menu.AddItem(
      "Exit", []() { Logger::Trace("Save As menu item clicked"); });
}

void MainMenuBar::SetupEditMenu() {
  auto &edit_menu = GetOrAddMenu("Edit");

  edit_menu.AddItem("Undo", []() { Logger::Trace("Undo menu item clicked"); });
  edit_menu.AddItem("Redo", []() { Logger::Trace("Redo menu item clicked"); });
  edit_menu.AddItem("Cut", []() { Logger::Trace("Cut menu item clicked"); });
  edit_menu.AddItem("Copy", []() { Logger::Trace("Copy menu item clicked"); });
  edit_menu.AddItem("Paste", []() { Logger::Trace("Paste menu item clicked"); });
  edit_menu.AddItem(
      "Delete", []() { Logger::Trace("Delete menu item clicked"); });
}

void MainMenuBar::SetupViewMenu() {
  auto &view_menu = GetOrAddMenu("View");

  view_menu.AddItem(
      "Zoom In", []() { Logger::Trace("Zoom In menu item clicked"); });
  view_menu.AddItem(
      "Zoom Out", []() { Logger::Trace("Zoom Out menu item clicked"); });
  view_menu.AddItem(
      "Reset Zoom", []() { Logger::Trace("Reset Zoom menu item clicked"); });
}

void MainMenuBar::SetupHelpMenu() {
  auto &help_menu = GetOrAddMenu("Help");

  help_menu.AddItem("Documentation",
      []() { Logger::Trace("Documentation menu item clicked"); });
  help_menu.AddItem("About", []() { Logger::Trace("About menu item clicked"); });
}

auto MainMenuBar::GetFileDialog() -> ImGui::FileBrowser & {
  return file_dialog_;
}

void MainMenuBar::Show() {
  BaseMenuBar::Show();
  file_dialog_.Display();
}
