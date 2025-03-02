#pragma once

#include "GUITextFieldButton.h"

#include <QtWidgets>


namespace GUIFileExplorerData {
    const int TEXT_FIELD_HEIGHT = 30;
    const int LOAD_BTN_WIDTH = 100;
};



class GUIFileExplorer : public QDialog {
    Q_OBJECT
public:
    GUIFileExplorer(const QString& file_path = "", QWidget* parent = nullptr);
private:
    QFileSystemModel* m_filesystem;
    GUITextFieldButton* m_textfield;

    void m_InitTextField(const QString& file_path);
    void m_OnFileSelected(const QItemSelection &selected, const QItemSelection &deselected);
    QTreeView* m_InitFileSystemView();

private slots:
    void m_OnLoadButtonPressed();

signals:
    void FilePathChanged(QString& file_path);
};