#pragma once 

#include <QtWidgets>
#include <functional>


/// @brief Widget for textfield with associated button
class GUITextFieldButton : public QWidget {
    Q_OBJECT
public:
    GUITextFieldButton(int btn_width, int height, const QString& btn_txt, QWidget* parent = nullptr);

    /// @brief Change mode of the textfield to read-only/read-write
    /// @param read_only set to read-only if true, set to read-write if false
    void SetReadOnly(bool read_only);
    
    /// @brief Sets text in the textfield
    /// @param text 
    void SetText(const QString& text);
    const QString GetText() const;

    /// @brief Function that lets setting method of the class as a button callback
    /// @tparam T type of the calling class
    /// @param wgt pointer to the calling class
    /// @param cb method of the class to be executed as callback
    template<typename T>
    void SetButtonCallback(T* wgt,  void (T::*cb)()) {
        connect(m_btn, &QPushButton::pressed, wgt, cb);
    };
private:
    // widget for textfield
    QTextEdit* m_textfield;
    // widget for button
    QPushButton* m_btn;
    // button title
    QString m_btn_txt;
    // path to the player's code
    std::string m_player_path;

    int m_btn_width;
    int m_height;

    // init
    void m_InitTextField();
    void m_InitButton();
};