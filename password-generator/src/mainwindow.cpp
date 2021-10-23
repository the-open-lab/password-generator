#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "licensedialog.h"
#include <QClipboard>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>
#include <QSysInfo>
#include <QTimer>
#include <QtDebug>
#include <QScrollArea>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

#ifdef Q_OS_WIN
    settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, ORG_NAME, APP_NAME);
#else
    settings = new QSettings(QSettings: NativeFormat, QSettings::UserScope, ORG_NAME, APP_NAME);
#endif

    loadSettings();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    saveSettings();
    event->accept();
}

void MainWindow::loadSettings() {
    settings->beginGroup(ORG_DOMAIN);
    ui->upperCheckBox->setChecked(settings->value(UPPER_CHK).toBool());
    ui->upperSpinBox->setValue(settings->value(UPPER_VAL).toInt());
    ui->lowerCheckBox->setChecked(settings->value(LOWER_CHK).toBool());
    ui->lowerSpinBox->setValue(settings->value(LOWER_VAL).toInt());
    ui->numberCheckBox->setChecked(settings->value(NUMBER_CHK).toBool());
    ui->numberSpinBox->setValue(settings->value(NUMBER_VAL).toInt());
    ui->specialCheckBox->setChecked(settings->value(SPECIAL_CHK).toBool());
    ui->specialSpinBox->setValue(settings->value(SPECIAL_VAL).toInt());
    ui->lengthCheckBox->setChecked(settings->value(LENGTH_CHK).toBool());
    ui->lengthSpinBox->setValue(settings->value(LENGTH_VAL).toInt());
    settings->endGroup();
}

void MainWindow::saveSettings() {
    settings->beginGroup(ORG_DOMAIN);
    settings->setValue(UPPER_CHK, ui->upperCheckBox->isChecked());
    settings->setValue(UPPER_VAL, ui->upperSpinBox->value());
    settings->setValue(LOWER_CHK, ui->lowerCheckBox->isChecked());
    settings->setValue(LOWER_VAL, ui->lowerSpinBox->value());
    settings->setValue(NUMBER_CHK, ui->numberCheckBox->isChecked());
    settings->setValue(NUMBER_VAL, ui->numberSpinBox->value());
    settings->setValue(SPECIAL_CHK, ui->specialCheckBox->isChecked());
    settings->setValue(SPECIAL_VAL, ui->specialSpinBox->value());
    settings->setValue(LENGTH_CHK, ui->lengthCheckBox->isChecked());
    settings->setValue(LENGTH_VAL, ui->lengthSpinBox->value());
    settings->endGroup();
}

void MainWindow::on_actionExit_triggered(bool) {
    this->close();
}

void MainWindow::on_actionAbout_triggered(bool) {
    QMessageBox::about(this, "About " + MainWindow::APP_NAME,
                       "<h3>" + MainWindow::APP_NAME + " 1.0.0</h3>"
                       "<hr>"
                       "<p>Built on " + __TIMESTAMP__ + ".</p>"
                       "<p>Copyright &copy; 2021 " + MainWindow::ORG_NAME + ".</p>"
                      );
}

void MainWindow::on_actionLicense_triggered(bool) {
    auto dialog = new LicenseDialog();
    dialog->show();
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
    if(!ui->passwordLineEdit->text().isEmpty() && hasFocus) {
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

QString MainWindow::ORG_NAME = "The Open Lab";
QString MainWindow::ORG_DOMAIN = "ch.open-lab";
QString MainWindow::APP_NAME = "Password Generator";
