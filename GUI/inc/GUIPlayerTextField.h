#pragma once 

#include "GUIFileExplorer.h"
#include "GUITextFieldButton.h"

#include <memory>

class GUIPlayerTextField : public QWidget {
    Q_OBJECT
public:
    GUIPlayerTextField(const QString& player_name="Player", QWidget* parent = nullptr);
private:
    // logic related fields
    std::string m_player_path;
    // GUI related fields
    // QTextEdit* m_textfield;
    // QPushButton* m_btn;
    GUITextFieldButton* m_textfield;
    QLabel* m_player_id;
    std::unique_ptr<GUIFileExplorer> m_file_explorer;

    // constants 
    const int TEXT_FIELD_HEIGHT = 30;
    const int BTN_WIDTH = 100;


    // init label
    void m_InitLabel(const QString& player_name);
    void m_InitTextField();
private slots:
    void PlayerPathChangedCb(QString& path);
    void ChoosePlayersCb();
};