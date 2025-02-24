#pragma once

#include <QtWidgets>

namespace GUIFileExplorerData {
    const int TEXT_FIELD_HEIGHT = 30;
    const int LOAD_BTN_WIDTH = 100;
};



class GUIFileExplorer : public QDialog {
    Q_OBJECT
public:
    GUIFileExplorer(QWidget* parent = nullptr);
private:
    QTextEdit* m_textfield;
    QPushButton* m_load_btn;
    QWidget* m_textfield_wrapper;
    QFileSystemModel* m_filesystem;

    void m_InitTextFieldWrapper();
    void m_OnFileSelected(const QItemSelection &selected, const QItemSelection &deselected);
    QTreeView* m_InitFileSystemView();

private slots:
    void m_OnLoadButtonPressed();

signals:
    void FilePathChanged(QString& file_path);
};