// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "main_window.h"
#include "hella.h"
#include "easylogging++.h"

#include <QApplication>
#include <QFileInfo>

namespace turtleraw {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_toolBar = new QToolBar(this);
    {
        m_toolBar->setObjectName("WindowToolBar");
        // Fixed to top
        m_toolBar->setFloatable(false);
        m_toolBar->setMovable(false);

        // Fill the toolbar with actions
        fillToolBar();
    }
    addToolBar(Qt::TopToolBarArea, m_toolBar);

    setCentralWidget(createLayout());
}

MainWindow::~MainWindow() {
}

void MainWindow::carryArguments(const QStringList &l) {
    // Based off documentation, the first argument (0) should be usually the application.
    // We assume that we get the path in the second argument.
    QString possiblePath;
    if (l.count() < 2) {
        LOG(INFO) << "No startup arguments attached.";
        return;
    } else {
        possiblePath = l.at(1);
    }
    
    if (possiblePath.startsWith("/")) {
        QFileInfo fileCheck(possiblePath);
        if (fileCheck.exists())
            m_startupArguments = l;
        else
            LOG(ERROR) << "File to open was moved or deleted during startup.";
    } else {
        LOG(ERROR) << "Invalid startup argument. Expected file, not given.";
    }
}

void MainWindow::createToolBarButton(QPushButton *btn, QToolBar *tb, const QString &shortcut, const QString &tipText, bool checkable) {
    tb->addWidget(btn);
    btn->setShortcut(QKeySequence(shortcut));
    btn->setCheckable(checkable);
    if (!shortcut.isEmpty())
        btn->setToolTip(tipText + " (" + QKeySequence(btn->shortcut()).toString() + ")");
    else
        btn->setToolTip(tipText);
}

void MainWindow::createMenuAction(QAction *act, QMenu *m, const QString &shortcut, bool checkable, bool enabledByDefault) {
    m->addAction(act);
    act->setShortcut(QKeySequence(shortcut));
    act->setCheckable(checkable);
    act->setEnabled(enabledByDefault);
}

void MainWindow::fillToolBar() {
    m_previousBtn = new QPushButton("\uE5C4", m_toolBar);
    createToolBarButton(m_previousBtn, m_toolBar, Hella::shFromIni("previous"), tr("Previous"), false);
    m_toolBarBtns.append(m_previousBtn);

    m_nextBtn = new QPushButton("\uE5C8", m_toolBar);
    createToolBarButton(m_nextBtn, m_toolBar, Hella::shFromIni("next"), tr("Next"), false);
    m_toolBarBtns.append(m_nextBtn);

    m_metaDataBtn = new QPushButton("\uE88E", m_toolBar);
    createToolBarButton(m_metaDataBtn, m_toolBar, Hella::shFromIni("show_metadata"), tr("Show metadata"), true);
    m_toolBarBtns.append(m_metaDataBtn);

    m_toolBar->addSeparator();

    m_deleteBtn = new QPushButton("\uE872", m_toolBar);
    createToolBarButton(m_deleteBtn, m_toolBar, Hella::shFromIni("delete_img"), tr("Delete"), false);
    m_toolBarBtns.append(m_deleteBtn);

    QWidget *_toolBarSpacer = new QWidget(m_toolBar);
    _toolBarSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_toolBar->addWidget(_toolBarSpacer);

    m_menuBtn = new QPushButton("\uE5D2", m_toolBar);
    createToolBarButton(m_menuBtn, m_toolBar, Hella::shFromIni("menu"), tr("Menu"), false);
    m_toolBarBtns.append(m_menuBtn);
    {
        m_menu = new QMenu(m_menuBtn);

        m_fileMenu = m_menu->addMenu(tr("File"));
        {
            m_closeAction = new QAction(tr("Close Image"), this);
            createMenuAction(m_closeAction, m_fileMenu, Hella::shFromIni("close_img"), false, false);
            connect(m_closeAction, SIGNAL(triggered()), this, SLOT(onCloseAction_Triggered()));
        }
        m_editMenu = m_menu->addMenu(tr("Edit"));
        {
            m_editPreferencesAction = new QAction(tr("Edit Preferences..."), this);
            createMenuAction(m_editPreferencesAction, m_editMenu, Hella::shFromIni("edit_preferences"), false, true);
            connect(m_editPreferencesAction, SIGNAL(triggered()), this, SLOT(settingsDialogRequired()));
        }
        m_viewMenu = m_menu->addMenu(tr("View"));
        m_toolsMenu = m_menu->addMenu(tr("Tools"));
        m_helpMenu = m_menu->addMenu(tr("Help"));

        m_menuBtn->setMenu(m_menu);
    }

    foreach(QPushButton *tbBtn, m_toolBarBtns) {
        tbBtn->setObjectName("ToolBarButton");
        tbBtn->setFont(QFont("Material Design Sharp", 16));
    }
}

QWidget* MainWindow::createLayout() {
    m_centralWidget = new QWidget(this);

    m_mainLayout = new QVBoxLayout(m_centralWidget);
    {
        m_mainLayout->setMargin(0);
        m_mainLayout->setSpacing(0);
    }

    if (!imagePreviewWidget)
        imagePreviewWidget = new ImagePreviewWidget(this);
    // this is just for testing
    imagePreviewWidget->loadImage("/home/nitroo/Projects/turtleraw/resources/testimages/CanonRawTest.CR2", true);
    m_closeAction->setEnabled(true);
    // ---

    m_showFolderBrowserBtn = new QPushButton(m_centralWidget);
    {
        connect(m_showFolderBrowserBtn, SIGNAL(clicked()), this, SLOT(onShowFolderBrowserBtn_Clicked()));
        m_showFolderBrowserBtn->setObjectName("ShowFolderBrowserButton");
        m_showFolderBrowserBtn->setToolTip(tr("Display folder contents"));
        // Initial state, folder browser not shown.
        m_showFolderBrowserBtn->setFont(QFont("Material Design Sharp", 16));
        m_showFolderBrowserBtn->setText("\uE5CE");
        m_folderBrowserShown = false;
    }

    m_mainLayout->addWidget(imagePreviewWidget);
    m_mainLayout->addWidget(m_showFolderBrowserBtn);

    if (!folderBrowserScroll)
        folderBrowserScroll = new QScrollArea(m_centralWidget);
    if (!folderBrowserView)
        folderBrowserView = new FolderBrowser(m_centralWidget);
    folderBrowserScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    folderBrowserScroll->setStyleSheet("background-color: rgb(60, 60, 60);");
    folderBrowserScroll->setWidget(folderBrowserView);

    // Not shown by default.
    m_mainLayout->addWidget(folderBrowserScroll);
    folderBrowserScroll->setMaximumHeight(0);

    m_centralWidget->setLayout(m_mainLayout);
    return m_centralWidget;
}

void MainWindow::onCloseAction_Triggered() {
    if (imagePreviewWidget)
        imagePreviewWidget->clear();
    m_closeAction->setEnabled(false);
}

void MainWindow::onShowFolderBrowserBtn_Clicked() {
    if (!m_folderBrowserShown) {
        Hella::propAnimation(folderBrowserScroll, "maximumHeight", 100, 0, 230);
        m_folderBrowserShown = true;
        m_showFolderBrowserBtn->setText("\uE5CF");
    } else {
        Hella::propAnimation(folderBrowserScroll, "maximumHeight", 100, 230, 0);
        m_folderBrowserShown = false;
        m_showFolderBrowserBtn->setText("\uE5CE");
    }
}

void MainWindow::settingsDialogRequired() {
    if (!settingsDlg)
        settingsDlg = new SettingsDialog(this);
    
    settingsDlg->exec();
}

} // namespace