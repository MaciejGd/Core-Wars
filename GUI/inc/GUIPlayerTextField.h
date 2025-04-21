#pragma once 

#include "GUIFileExplorerDialog.h"
#include "GUITextFieldButton.h"

#include <memory>

/// @brief Widget for displaying and storing path to player's code
/// 
/// Displays, store and let the user choose the path to player's code
///
class GUIPlayerTextField : public QWidget {
    Q_OBJECT
public:
    GUIPlayerTextField(const QString& player_name="Player", QWidget* parent = nullptr);

    /// @brief Get player path shown in textfield
    /// @return player path as string
    const std::string& GetPlayerPath() { return m_player_path; };

    /// @brief Set color of the player
    void SetColor(const QString& color);
private:
    // path to a player's code
    std::string m_player_path;
    // widget for textfield with a button
    GUITextFieldButton* m_textfield;
    // label representing player's name
    QLabel* m_player_id;
    // ptr to file explorer created after button press
    std::unique_ptr<GUIFileExplorerDialog> m_file_explorer;

    // constants 
    const int TEXT_FIELD_HEIGHT = 30;
    const int BTN_WIDTH = 100;

    // init
    void m_InitLabel(const QString& player_name);
    void m_InitTextField();

private slots:
    // setting new path to player's code
    void PlayerPathChangedCb(QString& path);
    // lauching fileview on button press
    void ChoosePlayersCb();
    
};