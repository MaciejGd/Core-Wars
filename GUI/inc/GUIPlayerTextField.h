#pragma once 

#include "GUIFileExplorer.h"

#include <memory>

class GUIPlayerTextField : public QWidget {
    Q_OBJECT
public:
    GUIPlayerTextField(QWidget* parent = nullptr);
    
private:
    // logic related fields
    std::string m_player_path;
    // GUI related fields
    QTextEdit* m_textfield;
    QPushButton* m_btn;
    std::unique_ptr<GUIFileExplorer> m_file_explorer;

    // constants 
    const int TEXT_FIELD_HEIGHT = 30;
    const int BTN_WIDTH = 100;

private slots:
    void PlayerPathChangedCb(QString& path);
    void ChoosePlayersCb();
};