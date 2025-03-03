#pragma once

#include "GUITextFieldButton.h"

#include <QtWidgets>

/// @brief Graphical user interface for choosing file from system.
///
/// Consists of window with a file system tree, text field showing
/// currently chosen file, and button for accepting the choice.
class GUIFileExplorer : public QDialog {
    Q_OBJECT
public:
    GUIFileExplorer(const QString& file_path = "", QWidget* parent = nullptr);
private:
    // widget for file system view
    QFileSystemModel* m_filesystem;
    // widget for textfield and button
    GUITextFieldButton* m_textfield;

    // constants
    const int TEXT_FIELD_HEIGHT = 30;
    const int LOAD_BTN_WIDTH = 100;
    std::string WINDOW_TITLE = "choose player";
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 400;

    // init
    void m_InitTextField(const QString& file_path);
    QTreeView* m_InitFileSystemView();

    // callback for button press
    void m_OnLoadButtonPressed();

private slots:
    void m_OnFileSelected(const QItemSelection &selected, const QItemSelection &deselected);

signals:
    // singnal to be emitted when chosen file path of file explorer changes
    void FilePathChanged(QString& file_path);
};