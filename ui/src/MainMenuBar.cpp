#include <MainMenuBar.h>

#include <Logger.h>

MainMenuBar::MainMenuBar() {
  SetupFileMenu();
  SetupEditMenu();
  SetupViewMenu();
  SetupHelpMenu();
}

void MainMenuBar::SetupFileMenu() {
  auto &fileMenu = GetOrAddMenu("File");

  fileMenu.AddItem("New", []() { Logger::Trace("New menu item clicked"); });
  fileMenu.AddItem("Open", []() { Logger::Trace("Open menu item clicked"); });
  fileMenu.AddItem("Save", []() { Logger::Trace("Save menu item clicked"); });
  fileMenu.AddItem(
      "Save As", []() { Logger::Trace("Save As menu item clicked"); });
  fileMenu.AddItem(
      "Exit", []() { Logger::Trace("Save As menu item clicked"); });
}

void MainMenuBar::SetupEditMenu() {
  auto &editMenu = GetOrAddMenu("Edit");

  editMenu.AddItem("Undo", []() { Logger::Trace("Undo menu item clicked"); });
  editMenu.AddItem("Redo", []() { Logger::Trace("Redo menu item clicked"); });
  editMenu.AddItem("Cut", []() { Logger::Trace("Cut menu item clicked"); });
  editMenu.AddItem("Copy", []() { Logger::Trace("Copy menu item clicked"); });
  editMenu.AddItem("Paste", []() { Logger::Trace("Paste menu item clicked"); });
  editMenu.AddItem(
      "Delete", []() { Logger::Trace("Delete menu item clicked"); });
}

void MainMenuBar::SetupViewMenu() {
  auto &viewMenu = GetOrAddMenu("View");

  viewMenu.AddItem(
      "Zoom In", []() { Logger::Trace("Zoom In menu item clicked"); });
  viewMenu.AddItem(
      "Zoom Out", []() { Logger::Trace("Zoom Out menu item clicked"); });
  viewMenu.AddItem(
      "Reset Zoom", []() { Logger::Trace("Reset Zoom menu item clicked"); });
}

void MainMenuBar::SetupHelpMenu() {
  auto &helpMenu = GetOrAddMenu("Help");

  helpMenu.AddItem("Documentation",
      []() { Logger::Trace("Documentation menu item clicked"); });
  helpMenu.AddItem("About", []() { Logger::Trace("About menu item clicked"); });
}
