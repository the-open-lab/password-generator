#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    application.setOrganizationName(QString(ORGANIZATION_NAME));
    application.setOrganizationDomain(QString(ORGANIZATION_URL));
    application.setApplicationName(QString(PROJECT_NAME));
    application.setApplicationVersion(QString(PROJECT_VER));

    QCommandLineParser parser;
    parser.setApplicationDescription(QApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(application);

    MainWindow window;
    window.show();
    return application.exec();
}
