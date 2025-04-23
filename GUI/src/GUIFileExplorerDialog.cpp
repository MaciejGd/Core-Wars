#include "GUIFileExplorerDialog.h"
#include "GUIConstants.h"

GUIFileExplorerDialog::GUIFileExplorerDialog(const QString& file_path, QWidget* parent): QDialog(parent) 
{
    setWindowTitle(GUI::FILE_EXPLORER_WINDOW_TITLE);
    resize(GUI::FILE_EXPLORER_WIDTH, GUI::FILE_EXPLORER_HEIGHT);

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
    // call SlotOnFileSelected every time selection changes
    connect(tree->selectionModel(), &QItemSelectionModel::selectionChanged, this, &GUIFileExplorerDialog::SlotOnFileSelected);
    return tree;
}

void GUIFileExplorerDialog::m_InitTextField(const QString& file_path) 
{
    m_textfield = new GUITextFieldButton{GUI::FILE_EXPLORER_LOAD_BTN_WIDTH, 
                                            GUI::FILE_EXPLORER_TEXTFIELD_HEIGHT, "load"};
    // set m_OnLoadButtonPressed as textfield button callback
    m_textfield->SetButtonCallback(this, &GUIFileExplorerDialog::m_OnLoadButtonPressed);
    m_textfield->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_textfield->SetText(file_path);
}

void GUIFileExplorerDialog::SlotOnFileSelected(const QItemSelection &selected, const QItemSelection &deselected) 
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
    emit SignalFilePathChanged(file_path);
    done(0);
}