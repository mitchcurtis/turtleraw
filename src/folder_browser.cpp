// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "folder_browser.h"

#include "folder_browser_element.h"

namespace turtleraw {

FolderBrowser::FolderBrowser(QWidget *parent) : QWidget(parent) {
    m_layout = new QHBoxLayout(this);
    {
        m_layout->setMargin(2);
        m_layout->setSpacing(3);  
    }
    setLayout(m_layout);

    FolderBrowserElement *test = new FolderBrowserElement;
    m_layout->addWidget(test);
}

FolderBrowser::~FolderBrowser() {
}

} // namespace