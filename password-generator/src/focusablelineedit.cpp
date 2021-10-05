#include "focusablelineedit.h"

#include <QApplication>
#include <QClipboard>
#include <QTimer>

FocusableLineEdit::FocusableLineEdit(QWidget* parent) : QLineEdit(parent) {}

FocusableLineEdit::~FocusableLineEdit() {}

void FocusableLineEdit::focusInEvent(QFocusEvent* event) {
    QLineEdit::focusInEvent(event);
    emit focused(true);
    QTimer::singleShot(0, this, [this]() {
        selectAll();
    });
}

void FocusableLineEdit::focusOutEvent(QFocusEvent* event) {
    QLineEdit::focusOutEvent(event);
    emit focused(false);
    this->deselect();
}
