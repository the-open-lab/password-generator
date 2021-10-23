#include "licensedialog.h"
#include "ui_licensedialog.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>

LicenseDialog::LicenseDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::LicenseDialog) {
    ui->setupUi(this);
}

LicenseDialog::~LicenseDialog() {
    delete ui;
}
