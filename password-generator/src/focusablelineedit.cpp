#include "focusablelineedit.h"

#include <QTimer>

FocusableLineEdit::FocusableLineEdit(QWidget* parent) : QLineEdit(parent) {}

FocusableLineEdit::~FocusableLineEdit() {}

void FocusableLineEdit::focusInEvent(QFocusEvent* event) {
    QLineEdit::focusInEvent(event);
    emit focused(true);
    QTimer::singleShot(0, this, [this]() {
        selectAll();
    });
    this->copy();
}

void FocusableLineEdit::focusOutEvent(QFocusEvent* event) {
    QLineEdit::focusOutEvent(event);
    emit focused(false);
    this->deselect();
}
