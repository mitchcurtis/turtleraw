// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "folder_browser.h"

#include "folder_browser_element.h"

namespace turtleraw {

FolderBrowser::FolderBrowser(QWidget *parent) : QWidget(parent) {
    m_layout = new QHBoxLayout(this);
    {
        m_layout->setMargin(0);
        m_layout->setSpacing(1);  
    }
    setLayout(m_layout);

    // playing
    FolderBrowserElement *element1 = new FolderBrowserElement;
    FolderBrowserElement *element2 = new FolderBrowserElement;
    FolderBrowserElement *element3 = new FolderBrowserElement;
    FolderBrowserElement *element4 = new FolderBrowserElement;
    FolderBrowserElement *element5 = new FolderBrowserElement;
    FolderBrowserElement *element6 = new FolderBrowserElement;
    m_layout->addWidget(element1);
    m_layout->addWidget(element2);
    m_layout->addWidget(element3);
    m_layout->addWidget(element4);
    m_layout->addWidget(element5);
    m_layout->addWidget(element6);
}

FolderBrowser::~FolderBrowser() {
}

} // namespace