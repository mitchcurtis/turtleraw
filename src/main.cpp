// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include <QApplication>

#include "phantomstyle.h"
#include <QStyle>
#include <QPalette>
#include <QColor>

#include <QFontDatabase>
#include <QFile>

#include "main_window.h"

using namespace turtleraw;

static void installFonts() {
    // We assume that the user has not installed the font.
    QFontDatabase::addApplicationFont("://resources/fonts/RobotoCondensed-Regular.ttf");
    QFontDatabase::addApplicationFont("://resources/fonts/RobotoCondensed-Bold.ttf");
    QFontDatabase::addApplicationFont("://resources/fonts/RobotoCondensed-BoldItalic.ttf");
    QFontDatabase::addApplicationFont("://resources/fonts/RobotoCondensed-Light.ttf");
    QFontDatabase::addApplicationFont("://resources/fonts/RobotoCondensed-LightItalic.ttf");

    // Icon font
    QFontDatabase::addApplicationFont("://resources/fonts/MaterialIconsSharp-Regular.otf");
}

int main(int argc, char *argv[]) {
    QApplication turtlerawApp(argc, argv);
    turtlerawApp.setApplicationVersion(QString("0.0.0"));
    turtlerawApp.setStyle(new PhantomStyle);
    installFonts();

    // TODO: check useSystemFont
    turtlerawApp.setFont(QFont("Roboto Condensed", 11));

    QPalette appPalette;
    appPalette.setColor(QPalette::Base, QColor(80, 80, 80));
    appPalette.setColor(QPalette::Window, QColor(80, 80, 80));
    appPalette.setColor(QPalette::Button, QColor(80, 80, 80));
    appPalette.setColor(QPalette::Text, QColor(230, 230, 230));
    appPalette.setColor(QPalette::WindowText, QColor(230, 230, 230));
    appPalette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
    // Signature color
    appPalette.setColor(QPalette::Highlight, QColor(2, 143, 30));
    turtlerawApp.setPalette(appPalette);

    QFile stylesheetFile("://resources/styles/Stylesheet.qss");
    stylesheetFile.open(QIODevice::ReadOnly);
    turtlerawApp.setStyleSheet(stylesheetFile.readAll());

    MainWindow win;
    win.show();

    return turtlerawApp.exec();
}