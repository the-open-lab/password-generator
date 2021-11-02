#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>
#include <QSysInfo>
#include <QTimer>
#include <QtDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->adjustSize();
    QFont monospace = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    monospace.setStyleHint(QFont::TypeWriter);
    ui->passwordLineEdit->setFont(monospace);

    QSettings::Format format = QSettings::NativeFormat;
#ifdef Q_OS_WIN
    format = QSettings::IniFormat;
#endif
    settings = std::make_unique<QSettings>(format, QSettings::UserScope, ORG_NAME, APP_NAME);

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
    settings->setValue(LENGTH_VAL, ui->lengthSpinBox->value());
    settings->endGroup();
}

void MainWindow::setCandidate() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(onPostReply(QNetworkReply*)));
    const QUrl url(QStringLiteral("https://api.random.org/json-rpc/2/invoke"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject object;
    object.insert("jsonrpc", "2.0");
    object.insert("method", "generateStrings");
    object.insert("id", 42);

    QJsonObject params;
    params.insert("apiKey", API_KEY.isEmpty() ? "" : API_KEY);
    params.insert("n", 1);
    params.insert("length", ui->lengthSpinBox->value());
    params.insert("characters", getPasswordCharacters());
    params.insert("replacement", false);
    object.insert("params", params);

    QJsonDocument document(object);
    QByteArray body = document.toJson();
    QNetworkReply* reply = manager->post(request, body);

    while(!reply->isFinished()) {
        qApp->processEvents();
    }
}

QJsonValue MainWindow::getPasswordCharacters() {
    QString passwordCharacters = QString();

    if(
        !ui->upperCheckBox->isChecked() &&
        !ui->lowerCheckBox->isChecked() &&
        !ui->numberCheckBox->isChecked() &&
        !ui->specialCheckBox->isChecked()
    ) {
        passwordCharacters.append("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    } else {
        if(ui->upperCheckBox->isChecked()) {
            passwordCharacters.append("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        }

        if(ui->lowerCheckBox->isChecked()) {
            passwordCharacters.append("abcdefghijklmnopqrstuvwxyz");
        }

        if(ui->numberCheckBox->isChecked()) {
            passwordCharacters.append("0123456789");
        }

        if(ui->specialCheckBox->isChecked()) {
            passwordCharacters.append("~`!@#$%^&*()-_=+[]{}\\|;:'\",<.>/? ");
        }
    }

    return QJsonValue(passwordCharacters);
}

void MainWindow::onPostReply(QNetworkReply* reply) {
    if(reply->error() == QNetworkReply::NoError) {
        QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
        candidate = QString(
                        response.object()
                        .find("result")->toObject()
                        .find("random")->toObject()
                        .find("data")->toArray().at(0).toString()
                    );
    } else {
        QMessageBox::critical(this, "Error", "Error while accessing the RANDOM.org API: " + reply->errorString());
    }
}

void MainWindow::on_actionExit_triggered(bool) {
    this->close();
}

void MainWindow::on_actionAbout_triggered(bool) {
    QMessageBox::about(this, "About " + APP_NAME,
                       "<h3>" + APP_NAME + " 1.0.0</h3>"
                       "<hr>"
                       "<p>Built on " + __TIMESTAMP__ + ".</p>"
                       "<p>Copyright &copy; 2021 " + ORG_NAME + " and the contributors.</p>"
                      );
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

void MainWindow::on_passwordLineEdit_focused(bool hasFocus) {
    if(!ui->passwordLineEdit->text().isEmpty() && hasFocus) {
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(ui->passwordLineEdit->text(), QClipboard::Clipboard);

        if(clipboard->supportsSelection ()) {
            clipboard->setText(ui->passwordLineEdit->text(), QClipboard::Selection);
        }

        ui->statusBar->showMessage("Password Copied");
        QTimer::singleShot(3000, this, [ = ]() {
            ui->statusBar->showMessage("");
        });

#if defined(Q_OS_LINUX)
        QThread::msleep(1);
#endif
    }
}

void MainWindow::on_generatePasswordButton_clicked() {
    setCandidate();
    ui->passwordLineEdit->setText(candidate);
}

QString MainWindow::ORG_NAME = "The Open Lab";
QString MainWindow::ORG_DOMAIN = "ch.open-lab";
QString MainWindow::APP_NAME = "Password Generator";
QString MainWindow::API_KEY = getenv("RANDOM_ORG_API_KEY");
