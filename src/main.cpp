// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include <QApplication>
#include "easylogging++.h"

#include "phantomstyle.h"
#include <QStyle>
#include <QPalette>
#include <QColor>

#include <QFontDatabase>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include <QList>
#include <QByteArray>
#include <QImageReader>

#include "settings.h"
#include "main_window.h"
#include "assign_filetypes_dialog.h"

using namespace turtleraw;

INITIALIZE_EASYLOGGINGPP

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

static bool areWeRawYet() {
    QList<QByteArray> fmts = QImageReader::supportedImageFormats();

    // TurtleRaw focuses on raw images, so support for raw images MUST be given. Because
    // QtRaw includes a multiple list of Raw formats, we can simply check for one of them,
    // in this case Canon raw v2, to know, if raw support is enabled.
    if (!fmts.contains("cr2")) {
        LOG(FATAL) << "Something messed up during build. Raw support not given. "
                        "Please rebuild application with QtRaw plugin enabled.";
        return false;
    }

    // Even though HEIF/HEIC is necessary for me, you can build TurtleRaw without the HEIF
    // plugin.
    if (!fmts.contains("heif")) {
        LOG(WARNING) << "HEIF plugin was not enabled during build. We allow that.";
        return true;
    }
    return true;
}

int main(int argc, char *argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    QApplication turtlerawApp(argc, argv);
    turtlerawApp.setApplicationName(QLatin1String("TurtleRaw"));
    turtlerawApp.setApplicationDisplayName(QLatin1String("TurtleRaw"));
    turtlerawApp.setApplicationVersion(QString("0.0.0"));
    turtlerawApp.setStyle(new PhantomStyle);
    installFonts();
    LOG(INFO) << "loaded fonts and initialized QApp object";

    if (!areWeRawYet())
        return 1;

    // Set the palette before we show the first window / dialog so we have a consistent style.
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

    Settings *settings = new Settings;
    QDir configSettingsDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));
    if (!configSettingsDir.exists()) {
        LOG(WARNING) << "TurtleRaw config dir does not exist. We assume that this is the first run...";
        configSettingsDir.mkpath(".");
        if (settings->init()) {
            AssignFileTypesDialog _assignFileTypesDlg;
            _assignFileTypesDlg.exec();
        }
    }

    if (!settings->read()) {
        // TODO
    }

    if (!settings->systemFontWanted())
        turtlerawApp.setFont(QFont("Roboto Condensed", 11));

    QFile stylesheetFile("://resources/styles/Stylesheet.qss");
    stylesheetFile.open(QIODevice::ReadOnly);
    turtlerawApp.setStyleSheet(stylesheetFile.readAll());

    MainWindow win;
    win.carrySettings(settings);
    win.create();

    return turtlerawApp.exec();
}