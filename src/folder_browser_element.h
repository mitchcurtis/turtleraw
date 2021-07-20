// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

#include <QWidget>
#include <QObject>

#include <QVBoxLayout>

#include <QLabel>
#include <QPushButton>

#include <QMenu>
#include <QAction>

#include <QEvent>

namespace turtleraw {

class FolderBrowserElement : public QWidget {
    Q_OBJECT
public:
    FolderBrowserElement(QWidget *parent = nullptr);
    ~FolderBrowserElement();

    // Reimplement eventFilter to get onHover.
    bool eventFilter(QObject *object, QEvent *event);
protected:
    QVBoxLayout *m_layout;
    
    QLabel *m_fileExtensionLbl;
    QLabel *m_imageLbl;

    QMenu *m_contextMenu;
    QAction *m_showFolderAction;
};

} // namespace