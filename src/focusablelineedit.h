#ifndef FOCUSABLELINEEDIT_H
#define FOCUSABLELINEEDIT_H

#include <QLineEdit>

class FocusableLineEdit : public QLineEdit {
    Q_OBJECT

public:
    FocusableLineEdit(QWidget* parent = 0);
    ~FocusableLineEdit();

signals:
    void focused(bool hasFocus);

protected:
    virtual void focusInEvent(QFocusEvent* event);
    virtual void focusOutEvent(QFocusEvent* event);
};

#endif // FOCUSABLELINEEDIT_H
