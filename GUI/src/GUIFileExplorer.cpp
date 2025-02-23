#include "GUIFileExplorer.h"

GUIFileExplorer::GUIFileExplorer(QWidget* parent): QDialog(parent) {

    setWindowTitle("File Explorer");
    resize(600, 400); // Set the window size (optional)

    // Create a layout for this window
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create the file system model to represent the file system
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    // Create the tree view widget and set the file system model
    QTreeView *tree = new QTreeView(this);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));

    // Add the tree view to the layout
    layout->addWidget(tree);

    setLayout(layout);
}