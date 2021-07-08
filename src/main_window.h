// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QPointer>

#include <QToolBar>

#include <QVBoxLayout>

#include <QScrollArea>
#include <QPushButton>

#include "settings.h"
#include "folder_browser.h"

namespace turtleraw {

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QToolBar *m_toolBar;
    
    QPointer<QScrollArea> folderBrowserScroll;
    QPointer<FolderBrowser> folderBrowserView;
    bool m_folderBrowserShown;

    void carrySettings(Settings *s) {
        m_settings = s;
    }
    
protected:
    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;
    QPushButton *m_showFolderBrowserBtn;

    QWidget* createLayout();

    Settings *m_settings;

public slots:
    void onShowFolderBrowserBtn_Clicked();
};

} // namespace