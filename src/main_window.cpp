// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "main_window.h"
#include "hella.h"

#include <QApplication>

namespace turtleraw {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setMenuBar(windowMenuBar());
    setCentralWidget(createLayout());
}

MainWindow::~MainWindow() {
}

QMenuBar* MainWindow::windowMenuBar() {
    m_windowMenuBar = new QMenuBar(this);
    m_windowMenuBar->setObjectName("WindowMenuBar");

    m_fileMenu = m_windowMenuBar->addMenu(tr("File"));
    m_editMenu = m_windowMenuBar->addMenu(tr("Edit"));
    m_viewMenu = m_windowMenuBar->addMenu(tr("View"));
    m_toolsMenu = m_windowMenuBar->addMenu(tr("Tools"));
    m_helpMenu = m_windowMenuBar->addMenu(tr("Help"));

    return m_windowMenuBar;
}

QWidget* MainWindow::createLayout() {
    m_centralWidget = new QWidget(this);

    m_mainLayout = new QVBoxLayout(m_centralWidget);
    {
        m_mainLayout->setMargin(0);
        m_mainLayout->setSpacing(0);
    }

    // todo, we currently show an empty placeholder
    QWidget *__p =  new QWidget;
    __p->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

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

    m_mainLayout->addWidget(__p);
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

void MainWindow::onShowFolderBrowserBtn_Clicked() {
    if (!m_folderBrowserShown) {
        propAnimation(folderBrowserScroll, "maximumHeight", 100, 0, 180);
        m_folderBrowserShown = true;
        m_showFolderBrowserBtn->setText("\uE5CF");
    } else {
        propAnimation(folderBrowserScroll, "maximumHeight", 100, 180, 0);
        m_folderBrowserShown = false;
        m_showFolderBrowserBtn->setText("\uE5CE");
    }
}

} // namespace