#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QCloseEvent>
#include <QSettings>
#include <QTimer>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    saveSettings();
    event->accept();
}

void MainWindow::on_upperCheckBox_toggled(bool checked) {
    ui->upperSpinBox->setEnabled(checked);
}

void MainWindow::on_lowerCheckBox_toggled(bool checked) {
    ui->lowerSpinBox->setEnabled(checked);
}

void MainWindow::on_numberCheckBox_toggled(bool checked) {
    ui->numberSpinBox->setEnabled(checked);
}

void MainWindow::on_specialCheckBox_toggled(bool checked) {
    ui->specialSpinBox->setEnabled(checked);
}

void MainWindow::on_lengthCheckBox_toggled(bool checked) {
    ui->lengthSpinBox->setEnabled(checked);
}

void MainWindow::on_passwordLineEdit_focused(bool hasFocus) {
    if(hasFocus) {
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(ui->passwordLineEdit->text(), QClipboard::Clipboard);

        if(clipboard->supportsSelection ()) {
            clipboard->setText(ui->passwordLineEdit->text(), QClipboard::Selection);
        }

        ui->statusBar->showMessage("Password Copied");
        QTimer::singleShot(3000, this, [ = ]() {
            ui->statusBar->showMessage ("");
        });

#if defined(Q_OS_LINUX)
        QThread::msleep(1);
#endif
    }
}

void MainWindow::on_generatePasswordButton_clicked() {
    ui->passwordLineEdit->setText("Success");
}

void MainWindow::loadSettings() {}

void MainWindow::saveSettings() {
    settings.setValue(UPPER_CHK, ui->upperCheckBox->isChecked());
    settings.setValue(UPPER_VAL, ui->upperSpinBox->value());
    settings.setValue(LOWER_CHK, ui->lowerCheckBox->isChecked());
    settings.setValue(LOWER_VAL, ui->lowerSpinBox->value());
    settings.setValue(NUMBER_CHK, ui->numberCheckBox->isChecked());
    settings.setValue(NUMBER_VAL, ui->numberSpinBox->value());
    settings.setValue(SPECIAL_CHK, ui->specialCheckBox->isChecked());
    settings.setValue(SPECIAL_VAL, ui->specialSpinBox->value());
    settings.setValue(LENGTH_CHK, ui->lengthCheckBox->isChecked());
    settings.setValue(LENGTH_VAL, ui->lengthSpinBox->value());
}
