// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

// Useful Qt functions, provided to be used wherever needed.

#include <QWidget>
#include <QByteArray>
#include <QString>
#include <QPropertyAnimation>
#include <QFileInfo>
#include <QStandardPaths>
#include <QFile>
#include <QTextStream>

namespace Hella {

///
/// Simple wrapper around QPropertyAnimation's.
///
void propAnimation(QWidget *w, const QString &prop, int dur, int sVal, int eVal) {
    QByteArray _prop = prop.toUtf8();
    QPropertyAnimation *anim = new QPropertyAnimation(w, _prop);
    anim->setDuration(dur);
    anim->setStartValue(sVal);
    anim->setEndValue(eVal);

    anim->start();
}

///
/// Read shortcuts from ini files
///
QString shFromIni(const QString &id) {
    QString ini;
    QString qrc = ":/resources/default_shortcuts.ini";
    QString custom = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/TurtleRaw/shortcuts.ini";
    QFileInfo fi(custom);
    if (fi.exists())
        ini = custom;
    else
        ini = qrc;
    
    QFile shortcutFile(ini);
    if (shortcutFile.open( QIODevice::ReadOnly )) {
        QTextStream in(&shortcutFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QString _id(id + " = ");
            int pos = line.indexOf(_id);
            if (pos >= 0)
                return line.mid(pos + _id.length());
        }
    }
    return qrc;
}

} // namespace
