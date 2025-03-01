#include "GUIFileExplorer.h"

using namespace GUIFileExplorerData;

GUIFileExplorer::GUIFileExplorer(QWidget* parent): QDialog(parent) {

    setWindowTitle("File Explorer");
    resize(600, 400); // Set the window size (optional)

    // Create a layout for this window
    QVBoxLayout *layout = new QVBoxLayout(this);
    QTreeView* tree = m_InitFileSystemView();

    // Add the tree view to the layout
    layout->addWidget(tree);

    // initialize widget for text field and add it to layout
    m_InitTextField();
    layout->addWidget(m_textfield_wrapper);

    //setLayout(layout);
}

QTreeView* GUIFileExplorer::m_InitFileSystemView() {
    m_filesystem = new QFileSystemModel;
    m_filesystem->setRootPath(QDir::currentPath());

    // Create the tree view widget and set the file system model
    QTreeView *tree = new QTreeView(this);
    tree->setModel(m_filesystem);
    tree->setRootIndex(m_filesystem->index("/"));
    // call m_OnFileSelected every time selection changes
    connect(tree->selectionModel(), &QItemSelectionModel::selectionChanged, this, &GUIFileExplorer::m_OnFileSelected);
    return tree;
}

void GUIFileExplorer::m_InitTextField() {
    // init push button
    m_load_btn = new QPushButton("Load", this);
    m_load_btn->setFixedSize(LOAD_BTN_WIDTH, TEXT_FIELD_HEIGHT);
    connect(m_load_btn, &QPushButton::released, this, &GUIFileExplorer::m_OnLoadButtonPressed);
    // init text field
    m_textfield = new QTextEdit(this);
    m_textfield->setFixedHeight(TEXT_FIELD_HEIGHT);
    // init text field wrapper and layout
    m_textfield_wrapper = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout{m_textfield_wrapper};
    layout->addWidget(m_textfield);
    layout->addWidget(m_load_btn);
    m_textfield_wrapper->setLayout(layout);
    m_textfield_wrapper->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

void GUIFileExplorer::m_OnFileSelected(const QItemSelection &selected, const QItemSelection &deselected) {
    QModelIndex index = selected.indexes().first();
    QString file_path = m_filesystem->filePath(index);
    m_textfield->setText(file_path);
}

void GUIFileExplorer::m_OnLoadButtonPressed() {
    // what we want to do in here is to emit signal with path and close the window
    QString file_path = m_textfield->toPlainText();
    emit FilePathChanged(file_path);
    done(0);
}