#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "QtSvgWidgets/QtSvgWidgets"

QT_BEGIN_NAMESPACE
namespace Ui {
    class AboutDialog;
}
QT_END_NAMESPACE

class AboutDialog : public QDialog {
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
