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
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_upperCheckBox_toggled(bool checked);
    void on_lowerCheckBox_toggled(bool checked);
    void on_numberCheckBox_toggled(bool checked);
    void on_specialCheckBox_toggled(bool checked);
    void on_minLengthCheckBox_toggled(bool checked);
    void on_passwordLineEdit_focused(bool hasFocus);
    void on_generatePasswordButton_clicked();

private:
    // -- Private Methods -----------------------------------------------------
    void getSettings();
    void setSetting(const QString& key, const QVariant& value);

    // -- Private Fields ------------------------------------------------------
    Ui::MainWindow* ui;

    const QString UPPER_KEY = "upper";
    const QString LOWER_KEY = "lower";
    const QString NUMBER_KEY = "number";
    const QString SPECIAL_KEY = "special";
    const QString LENGTH_KEY = "length";
};
#endif // MAINWINDOW_H
