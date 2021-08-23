<<<<<<< HEAD
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_allowRepeatsCheckBox_stateChanged();

  void on_maximumRepeatsCheckBox_stateChanged();

  void on_copyPasswordButton_clicked();

  void on_generatePasswordButton_clicked();

  void on_actionAbout_triggered();

private:
  Ui::MainWindow *ui;

  void toggleMaximumRepeats();
};
#endif // MAINWINDOW_H
||||||| empty tree
=======
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_allowRepeatsCheckBox_stateChanged();

  void on_maximumRepeatsCheckBox_stateChanged();

  void on_copyPasswordButton_clicked();

  void on_generatePasswordButton_clicked();

private:
  Ui::MainWindow *ui;

  void toggleMaximumRepeats();
};
#endif // MAINWINDOW_H
>>>>>>> f2d7a06d0ec3f30d6445bb38fd65ac390d243b62
