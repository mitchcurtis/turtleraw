// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

// Useful Qt functions, provided to be used wherever needed.

#include <QWidget>
#include <QByteArray>
#include <QString>
#include <QPropertyAnimation>

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