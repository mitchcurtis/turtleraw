// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

#include <QWidget>
#include <QObject>

#include <QHBoxLayout>

namespace turtleraw {

class FolderBrowser : public QWidget {
    Q_OBJECT
public:
    explicit FolderBrowser(QWidget *parent = nullptr);
    ~FolderBrowser();

    QHBoxLayout *m_layout;
};

} // namespace