#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Set up Save menu item
  //  QAction *save = ui->actionSave;

  // Set up Exit menu item
  QAction *exit = ui->actionExit;
  connect(exit, &QAction::triggered, qApp, QApplication::quit);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_allowRepeatsCheckBox_stateChanged() {
  toggleMaximumRepeats();
}

void MainWindow::on_maximumRepeatsCheckBox_stateChanged() {
  toggleMaximumRepeats();
}

void MainWindow::on_copyPasswordButton_clicked() {
  ui->passwordLineEdit->selectAll();
  ui->passwordLineEdit->copy();
}

void MainWindow::on_generatePasswordButton_clicked() {
  ui->passwordLineEdit->setText("Success");
}

void MainWindow::on_actionAbout_triggered() {
  Dialog *dialog = new Dialog();
  dialog->exec();
}
