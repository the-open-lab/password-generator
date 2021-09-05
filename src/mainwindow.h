#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define AUTHOR              "Jonathan E. Landrum"
#define ORGANIZATION_NAME   "The Open Lab"
#define ORGANIZATION_URL    "ch.open-lab"
#define PROJECT_NAME        "Password Generator"
#define PROJECT_VER_MAJOR   "1"
#define PROJECT_VER_MINOR   "0"
#define PROJECT_VER_PATCH   "0"
#define PROJECT_VER         PROJECT_VER_MAJOR "." PROJECT_VER_MINOR "." PROJECT_VER_PATCH

#define ENFORCE_MIN_UPPER   "enforceMinUpper"
#define MIN_UPPER           "minUpper"
#define ENFORCE_MIN_LOWER   "enforceMinLower"
#define MIN_LOWER           "minLower"
#define ENFORCE_MIN_NUMBER  "enforceMinNumber"
#define MIN_NUMBER          "minNumber"
#define ENFORCE_MIN_SPECIAL "enforceMinSpecial"
#define MIN_SPECIAL         "minSpecial"
#define ENFORCE_MIN_LENGTH  "enforceMinLength"
#define MIN_LENGTH          "minLength"

#define MAIN_WINDOW         "MainWindow"
#define GEOMETRY            "geometry"
#define PREFERENCES         "Preferences"

#include "focusablelineedit.h"

#include <QSettings>
#include <QSessionManager>
#include <QMainWindow>
#include <QLabel>
#include <QJsonObject>

#include <string>
#include <vector>

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

protected:
    void closeEvent(QCloseEvent*) override;

private slots:
    void saveAction();
    void quitAction();
    void aboutAction();
    void upperCheckBoxClicked();
    void upperSpinBoxChanged();
    void lowerCheckBoxClicked();
    void lowerSpinBoxChanged();
    void numberCheckBoxClicked();
    void numberSpinBoxChanged();
    void specialCheckBoxClicked();
    void specialSpinBoxChanged();
    void lengthCheckBoxClicked();
    void lengthSpinBoxChanged();
    void saveSettingsButtonClicked();
    void generatePasswordButtonClicked();
    void passwordLineEditFocusChanged(bool);

private:
    Ui::MainWindow* ui;
    QSettings settings;
    QJsonObject* preferences;

    void displayMessage(QLabel*, QString);
    void getPreferences();
    void setPreferences();
    void getUiState();
    void setUiState();
    QJsonObject getSettingsAsJson();
    void connectEvents();
    void createStatusBar();
};
#endif // MAINWINDOW_H
