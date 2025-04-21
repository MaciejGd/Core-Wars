#include "GUIFileExplorerDialog.h"

GUIFileExplorerDialog::GUIFileExplorerDialog(const QString& file_path, QWidget* parent): QDialog(parent) 
{
    setWindowTitle(QString(WINDOW_TITLE.c_str()));
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QTreeView* tree = m_InitFileSystemView();
    m_InitTextField(file_path);

    layout->addWidget(tree);
    layout->addWidget(m_textfield);
}

QTreeView* GUIFileExplorerDialog::m_InitFileSystemView() 
{
    m_filesystem = new QFileSystemModel;
    //m_filesystem->setRootPath(QDir::currentPath());
    m_filesystem->setRootPath("");

    QTreeView *tree = new QTreeView(this);
    tree->setModel(m_filesystem);
    tree->setRootIndex(m_filesystem->index("/"));
    // call m_OnFileSelected every time selection changes
    connect(tree->selectionModel(), &QItemSelectionModel::selectionChanged, this, &GUIFileExplorerDialog::m_OnFileSelected);
    return tree;
}

void GUIFileExplorerDialog::m_InitTextField(const QString& file_path) 
{
    m_textfield = new GUITextFieldButton{LOAD_BTN_WIDTH, TEXT_FIELD_HEIGHT, "LOAD"};
    // set m_OnLoadButtonPressed as textfield button callback
    m_textfield->SetButtonCallback(this, &GUIFileExplorerDialog::m_OnLoadButtonPressed);
    m_textfield->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_textfield->SetText(file_path);
}

void GUIFileExplorerDialog::m_OnFileSelected(const QItemSelection &selected, const QItemSelection &deselected) 
{
    // retrieve actually set file path and set it in textfield
    QModelIndex index = selected.indexes().first();
    QString file_path = m_filesystem->filePath(index);
    m_textfield->SetText(file_path);
}

void GUIFileExplorerDialog::m_OnLoadButtonPressed() 
{
    // what we want to do in here is to emit signal with path and close the window
    QString file_path = m_textfield->GetText();
    emit FilePathChanged(file_path);
    done(0);
}