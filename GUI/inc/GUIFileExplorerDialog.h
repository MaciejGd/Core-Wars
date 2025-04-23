#pragma once

#include "GUITextFieldButton.h"

#include <QtWidgets>

/// @brief Graphical user interface for choosing file from system.
///
/// Consists of window with a file system tree, text field showing
/// currently chosen file, and button for accepting the choice.
class GUIFileExplorerDialog : public QDialog {
    Q_OBJECT
public:
    GUIFileExplorerDialog(const QString& file_path = "", QWidget* parent = nullptr);
private:
    // widget for file system view
    QFileSystemModel* m_filesystem;
    // widget for textfield and button
    GUITextFieldButton* m_textfield;

    // init
    void m_InitTextField(const QString& file_path);
    QTreeView* m_InitFileSystemView();

    // callback for button press
    void m_OnLoadButtonPressed();

private slots:
    void SlotOnFileSelected(const QItemSelection &selected, const QItemSelection &deselected);

signals:
    // singnal to be emitted when chosen file path of file explorer changes
    void SignalFilePathChanged(QString& file_path);
};