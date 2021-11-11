#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QStandardPaths>
#include <QScrollArea>
#include <QNetworkReply>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // -- Public Methods ------------------------------------------------------
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent* event);

    // -- Public Fields -------------------------------------------------------
    static QString ORG_NAME;
    static QString ORG_DOMAIN;
    static QString APP_NAME;
    static QString API_KEY;

private slots:
    void onPostReply(QNetworkReply*);
    void on_actionExit_triggered(bool);
    void on_actionAbout_triggered(bool);
    void on_enforceUpperCheckBox_toggled(bool);
    void on_enforceLowerCheckBox_toggled(bool);
    void on_enforceNumberCheckBox_toggled(bool);
    void on_enforceSpecialCheckBox_toggled(bool);
    void on_includeUpperCheckBox_toggled(bool);
    void on_includeLowerCheckBox_toggled(bool);
    void on_includeNumberCheckBox_toggled(bool);
    void on_includeSpecialCheckBox_toggled(bool);
    void on_passwordLineEdit_focused(bool);
    void on_generatePasswordButton_clicked();

private:
    // --- Private Types ------------------------------------------------------
    using QSettingsPtr = std::unique_ptr<QSettings>;
    using QStringPtr = std::unique_ptr<QString>;

    // -- Private Methods -----------------------------------------------------
    void loadSettings();
    void saveSettings();
    void configurePasswordCharacters();
    void setCandidate();
    QString shuffleCandidate(QString);
    QJsonValue getPasswordCharacters();

    // -- Private Fields ------------------------------------------------------
    const QString UPPER_CHK = "upperChecked";
    const QString UPPER_VAL = "upperValue";
    const QString LOWER_CHK = "lowerChecked";
    const QString LOWER_VAL = "lowerValue";
    const QString NUMBER_CHK = "numberChecked";
    const QString NUMBER_VAL = "numberValue";
    const QString SPECIAL_CHK = "specialChecked";
    const QString SPECIAL_VAL = "specialValue";
    const QString LENGTH_VAL = "lengthValue";
    QString numbers = "";
    QString uppers = "";
    QString lowers = "";
    QString specials = "";
    Ui::MainWindow* ui;
    QSettingsPtr settings;
    QString candidate;
};
#endif // MAINWINDOW_H
