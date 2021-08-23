#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_allowRepeatsCheckBox_stateChanged() {
  toggleMaximumRepeats();
}

void MainWindow::on_maximumRepeatsCheckBox_stateChanged() {
  toggleMaximumRepeats();
}

void MainWindow::toggleMaximumRepeats() {
  ui->maximumRepeatsSpinBox->setEnabled(
      ui->allowRepeatsCheckBox->isChecked() &&
      ui->maximumRepeatsCheckBox->isChecked());
}

void MainWindow::on_copyPasswordButton_clicked() {
  ui->passwordLineEdit->selectAll();
  ui->passwordLineEdit->copy();
}

void MainWindow::on_generatePasswordButton_clicked() {
  ui->passwordLineEdit->setText("Success");
}
