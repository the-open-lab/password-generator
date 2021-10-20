#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    application.setOrganizationName(MainWindow::ORG_NAME);
    application.setOrganizationDomain(MainWindow::ORG_DOMAIN);
    application.setApplicationName(MainWindow::APP_NAME);
    application.setWindowIcon(QIcon(":/assets/icon.ico"));

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for (const QString& locale : uiLanguages) {
        const QString baseName = "password-generator_" + QLocale(locale).name();

        if (translator.load(":/i18n/" + baseName)) {
            application.installTranslator(&translator);
            break;
        }
    }

    MainWindow window;
    window.show();
    return application.exec();
}
