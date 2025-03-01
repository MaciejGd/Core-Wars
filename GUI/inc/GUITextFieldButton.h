#pragma once 

#include <QtWidgets>
#include <functional>


class GUITextFieldButton : public QWidget {
    Q_OBJECT
public:
    GUITextFieldButton(int btn_width, int height, const QString& btn_txt, QWidget* parent = nullptr);

    void SetReadOnly(bool read_only);
    void SetText(const QString& text);
    const QString GetText() const;

    template<typename T>
    void SetButtonCallback(T* wgt,  void (T::*cb)()) {
        connect(m_btn, &QPushButton::pressed, wgt, cb);
    }; // setting method as a callback
private:

    QTextEdit* m_textfield;
    QPushButton* m_btn;

    std::string m_player_path;
    QString m_btn_txt;
    int m_btn_width;
    int m_height;

    void m_InitTextField();
    void m_InitButton();

};