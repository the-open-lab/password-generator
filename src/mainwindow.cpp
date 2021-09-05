#include "mainwindow.h"
#include "focusablelineedit.h"

#include "ui_mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QTimer>
#include <QtWidgets>
#include <QPixmap>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    getPreferences();
    connectEvents();
    setUnifiedTitleAndToolBarOnMac(true);
    resize(minimumSizeHint());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    auto settings = getSettingsAsJson();

    if (settings != *preferences) {
        const QMessageBox::StandardButton result = QMessageBox::warning(
                    this,
                    tr("Save Settings"),
                    tr("Save changes to settings?"),
                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
                );

        switch(result) {
            case QMessageBox::Save:
                MainWindow::setPreferences();
                event->accept();
                break;

            case QMessageBox::Cancel:
                event->ignore();
                break;

            default:
                event->accept();
        }
    } else {
        event->accept();
    }
}

void MainWindow::displayMessage(QLabel* label, QString message) {
    label->setVisible(true);
    label->setText(message);
    label->adjustSize();
    QTimer::singleShot(5000, label, &QLabel::hide);
}

void MainWindow::getPreferences() {
    preferences = new QJsonObject();

    // ------------------------------------------------------------------------

    settings.beginGroup(MAIN_WINDOW);

    const auto geometry = settings.value(GEOMETRY, QByteArray()).toByteArray();

    if (geometry.isEmpty()) setGeometry(200, 200, 300, 458);
    else restoreGeometry(geometry);

    settings.endGroup();

    // ------------------------------------------------------------------------

    settings.beginGroup(PREFERENCES);

    // Enforce Minimum Upper
    preferences->insert(
        ENFORCE_MIN_UPPER,
        settings.contains(ENFORCE_MIN_UPPER) ?
        settings.value(ENFORCE_MIN_UPPER).toBool() :
        true
    );

    // Minimum Upper
    preferences->insert(
        MIN_UPPER,
        settings.contains(MIN_UPPER) ?
        settings.value(MIN_UPPER).toInt() :
        1
    );

    // Enforce Minimum Lower
    preferences->insert(
        ENFORCE_MIN_LOWER,
        settings.contains(ENFORCE_MIN_LOWER) ?
        settings.value(ENFORCE_MIN_LOWER).toBool() :
        true
    );

    // Minimum Lower
    preferences->insert(
        MIN_LOWER,
        settings.contains(MIN_LOWER) ?
        settings.value(MIN_LOWER).toInt() :
        1
    );

    // Enforce Minimum Number
    preferences->insert(
        ENFORCE_MIN_NUMBER,
        settings.contains(ENFORCE_MIN_NUMBER) ?
        settings.value(ENFORCE_MIN_NUMBER).toBool() :
        true
    );

    // Minimum Number
    preferences->insert(
        MIN_NUMBER,
        settings.contains(MIN_NUMBER) ?
        settings.value(MIN_NUMBER).toInt() :
        1
    );

    // Enforce Minimum Length
    preferences->insert(
        ENFORCE_MIN_LENGTH,
        settings.contains(ENFORCE_MIN_LENGTH) ?
        settings.value(ENFORCE_MIN_LENGTH).toBool() :
        true
    );

    // Minimum Length
    preferences->insert(
        MIN_LENGTH,
        settings.contains(MIN_LENGTH) ?
        settings.value(MIN_LENGTH).toInt() :
        16
    );

    settings.endGroup();

    // ------------------------------------------------------------------------

    setUiState();
}

void MainWindow::setPreferences() {
    getUiState();

    // ------------------------------------------------------------------------

    settings.beginGroup(MAIN_WINDOW);

    settings.setValue(GEOMETRY, saveGeometry());

    settings.endGroup();

    // ------------------------------------------------------------------------

    settings.beginGroup(PREFERENCES);

    // Enforce Minimum Upper
    settings.setValue(
        ENFORCE_MIN_UPPER,
        preferences->contains(ENFORCE_MIN_UPPER) ?
        preferences->value(ENFORCE_MIN_UPPER).toBool() :
        true
    );

    // Minimum Upper
    settings.setValue(
        MIN_UPPER,
        preferences->contains(MIN_UPPER) ?
        preferences->value(MIN_UPPER).toInt() :
        1
    );

    // Enforce Minimum Lower
    settings.setValue(
        ENFORCE_MIN_LOWER,
        preferences->contains(ENFORCE_MIN_LOWER) ?
        preferences->value(ENFORCE_MIN_LOWER).toBool() :
        true
    );

    // Minimum Lower
    settings.setValue(
        MIN_LOWER,
        preferences->contains(MIN_LOWER) ?
        preferences->value(MIN_LOWER).toInt() :
        1
    );

    // Enforce Minimum Number
    settings.setValue(
        ENFORCE_MIN_NUMBER,
        preferences->contains(ENFORCE_MIN_NUMBER) ?
        preferences->value(ENFORCE_MIN_NUMBER).toBool() :
        true
    );

    // Minimum Number
    settings.setValue(
        MIN_NUMBER,
        preferences->contains(MIN_NUMBER) ?
        preferences->value(MIN_NUMBER).toInt() :
        1
    );

    // Enforce Minimum Length
    settings.setValue(
        ENFORCE_MIN_LENGTH,
        preferences->contains(ENFORCE_MIN_LENGTH) ?
        preferences->value(ENFORCE_MIN_LENGTH).toBool() :
        true
    );

    // Minimum Length
    settings.setValue(
        MIN_LENGTH,
        preferences->contains(MIN_LENGTH) ?
        preferences->value(MIN_LENGTH).toInt() :
        16
    );

    settings.endGroup();

    // ------------------------------------------------------------------------

    displayMessage(ui->settingsSavedLabel, "Settings saved");
}

void MainWindow::getUiState() {
    preferences->insert(ENFORCE_MIN_UPPER, ui->capitalCheckBox->isChecked());
    preferences->insert(MIN_UPPER, ui->capitalSpinBox->value());
    preferences->insert(ENFORCE_MIN_LOWER, ui->minisculeCheckBox->isChecked());
    preferences->insert(MIN_LOWER, ui->minisculeSpinBox->value());
    preferences->insert(ENFORCE_MIN_NUMBER, ui->numeralCheckBox->isChecked());
    preferences->insert(MIN_NUMBER, ui->numeralSpinBox->value());
    preferences->insert(ENFORCE_MIN_LENGTH, ui->minimumLengthCheckBox->isChecked());
    preferences->insert(MIN_LENGTH, ui->minimumLengthSpinBox->value());
}

void MainWindow::setUiState() {
    ui->capitalCheckBox->setChecked(preferences->value(ENFORCE_MIN_UPPER).toBool());
    ui->capitalSpinBox->setValue(preferences->value(MIN_UPPER).toInt());
    ui->minisculeCheckBox->setChecked(preferences->value(ENFORCE_MIN_LOWER).toBool());
    ui->minisculeSpinBox->setValue(preferences->value(MIN_LOWER).toInt());
    ui->numeralCheckBox->setChecked(preferences->value(ENFORCE_MIN_NUMBER).toBool());
    ui->numeralSpinBox->setValue(preferences->value(MIN_NUMBER).toInt());
    ui->minimumLengthCheckBox->setChecked(preferences->value(ENFORCE_MIN_LENGTH).toBool());
    ui->minimumLengthSpinBox->setValue(preferences->value(MIN_LENGTH).toInt());
}

void MainWindow::upperCheckBoxClicked() {
    bool state = ui->capitalCheckBox->isChecked();
    preferences->insert(ENFORCE_MIN_UPPER, state);
    ui->capitalSpinBox->setEnabled(state);
}

void MainWindow::upperSpinBoxChanged() {
    preferences->insert(MIN_UPPER, ui->capitalSpinBox->value());
}

void MainWindow::lowerCheckBoxClicked() {
    bool state = ui->minisculeCheckBox->isChecked();
    preferences->insert(ENFORCE_MIN_LOWER, state);
    ui->minisculeSpinBox->setEnabled(state);
}

void MainWindow::lowerSpinBoxChanged() {

}

void MainWindow::numberCheckBoxClicked() {
    bool state = ui->numeralCheckBox->isChecked();
    preferences->insert(ENFORCE_MIN_NUMBER, state);
    ui->numeralSpinBox->setEnabled(state);
}

void MainWindow::numberSpinBoxChanged() {

}

void MainWindow::specialCheckBoxClicked() {
    bool state = ui->capitalCheckBox->isChecked();
    preferences->insert(ENFORCE_MIN_SPECIAL, state);
    ui->capitalSpinBox->setEnabled(state);
}

void MainWindow::specialSpinBoxChanged() {

}

void MainWindow::lengthCheckBoxClicked() {
    bool state = ui->capitalCheckBox->isChecked();
    preferences->insert(ENFORCE_MIN_UPPER, state);
    ui->capitalSpinBox->setEnabled(state);
}

void MainWindow::lengthSpinBoxChanged() {

}

QJsonObject MainWindow::getSettingsAsJson() {
    QJsonObject result;

    settings.beginGroup(PREFERENCES);
    result.insert(ENFORCE_MIN_UPPER, settings.value(ENFORCE_MIN_UPPER).toBool());
    result.insert(MIN_UPPER, settings.value(MIN_UPPER).toInt());
    result.insert(ENFORCE_MIN_LOWER, settings.value(ENFORCE_MIN_LOWER).toBool());
    result.insert(MIN_LOWER, settings.value(MIN_LOWER).toInt());
    result.insert(ENFORCE_MIN_NUMBER, settings.value(ENFORCE_MIN_NUMBER).toBool());
    result.insert(MIN_NUMBER, settings.value(MIN_NUMBER).toInt());
    result.insert(ENFORCE_MIN_LENGTH, settings.value(ENFORCE_MIN_LENGTH).toBool());
    result.insert(MIN_LENGTH, settings.value(MIN_LENGTH).toInt());
    settings.endGroup();

    return result;
}

void MainWindow::connectEvents() {
    // Create File Menu
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.svg"));
    QAction* saveAction = new QAction(saveIcon, tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save settings"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveAction);
    fileMenu->addAction(saveAction);

    const QIcon quitIcon = QIcon::fromTheme("application-exit", QIcon(":/images/exit.svg"));
    QAction* quitAction = new QAction(quitIcon, tr("&Quit"), this);
    quitAction->setShortcuts(QKeySequence::Quit);
    quitAction->setStatusTip("Exit the program");
    connect(quitAction, &QAction::triggered, this, &MainWindow::quitAction);
    fileMenu->addAction(quitAction);

    // Create Help Menu
    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));

    const QIcon aboutIcon = QIcon::fromTheme("help-about", QIcon(":/images/help.svg"));
    QAction* aboutAction = new QAction(aboutIcon, tr("&About"), this);
    aboutAction->setShortcuts(QKeySequence::WhatsThis);
    aboutAction->setStatusTip("About this program");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutAction);
    helpMenu->addAction(aboutAction);

    // ------------------------------------------------------------------------

    FocusableLineEdit* lineEdit = ui->passwordLineEdit;
    connect(lineEdit, SIGNAL(focused(bool)), this, SLOT(passwordLineEditFocusChanged(bool)));

    QPushButton* saveSettingsButton = ui->saveSettingsButton;
    connect(saveSettingsButton, SIGNAL(clicked(bool)), this, SLOT(saveSettingsButtonClicked()));

    QPushButton* generatePasswordButton = ui->generatePasswordButton;
    connect(generatePasswordButton, SIGNAL(clicked(bool)), this, SLOT(generatePasswordButtonClicked()));

    // ------------------------------------------------------------------------

    // Minimum Upper
    QCheckBox* upperCheckBox = ui->capitalCheckBox;
    connect(upperCheckBox, SIGNAL(toggled(bool)), this, SLOT(upperCheckBoxClicked()));
    QSpinBox* upperSpinBox = ui->capitalSpinBox;
    connect(upperSpinBox, SIGNAL(valueChanged(int)), this, SLOT(upperSpinBoxChanged()));
}

void MainWindow::saveAction() {
    MainWindow::setPreferences();
}

void MainWindow::quitAction() {
    qApp->quit();
}

void MainWindow::aboutAction() {
    QMessageBox messageBox;
    messageBox.setIconPixmap(QPixmap(":/images/logo.svg"));
    messageBox.setWindowTitle(tr("About " PROJECT_NAME));
    messageBox.setText(QString(tr("<h3>" PROJECT_NAME " " PROJECT_VER "</h3>")));
    messageBox.setInformativeText(
        tr(
            "<p>The <b>" PROJECT_NAME "</b> program uses the RANDOM.org API to generate truly random passwords</p>"
            "<hr />"
            "<p>Built on: <b>" __DATE__ " " __TIME__ "</b></p>"
            "<p>Copyright &copy; 2021 " AUTHOR "/" ORGANIZATION_NAME ". All rights reserved.</p>"
            "<p>This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License (GPL) as published by the Free Software Foundation (FSF), either version 3 of the License, or (at your option) any later version.</p>"
            "<p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.</p>"
            "<p>You should have received a copy of the GNU General Public License along with this program. If not, see &lt;https://www.gnu.org/licenses/&gt;.</p>"
        )
    );
    messageBox.exec();
}

void MainWindow::passwordLineEditFocusChanged(bool isFocusGained) {
    if(isFocusGained) {
        displayMessage(ui->copiedToClipboardLabel, "Copied to clipboard");
    }
}

void MainWindow::saveSettingsButtonClicked() {
    displayMessage(ui->settingsSavedLabel, "Settings saved");
}

void MainWindow::generatePasswordButtonClicked() {
    ui->passwordLineEdit->setText("Success");
}
