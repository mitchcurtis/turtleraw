// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "folder_browser_element.h"

#include <QDebug>

namespace turtleraw {

FolderBrowserElement::FolderBrowserElement(QWidget *parent) : QWidget(parent) {
    setFixedSize(QSize(228, 228));
    setStyleSheet("background-color: rgb(102, 102, 102);");

    m_layout = new QVBoxLayout(this);
    {
        m_layout->setMargin(0);
        m_layout->setSpacing(0);

        setLayout(m_layout);
    }

    m_fileExtensionLbl = new QLabel(this);
    {
        // Why can't we write this in one line?
        QFont fEf("Roboto Condensed Light", 22);
        fEf.setItalic(true);

        m_fileExtensionLbl->setFont(fEf);
        m_fileExtensionLbl->setStyleSheet("color: rgb(124, 124, 124);");
    }

    m_imageLbl = new QLabel(this);
    {
        m_imageLbl->installEventFilter(this);
        m_imageLbl->setObjectName("FolderBrowserImageLabel");
        m_imageLbl->setStyleSheet("border: none;");
        m_imageLbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    }

    m_layout->addWidget(m_fileExtensionLbl, Qt::AlignLeft);
    m_layout->addWidget(m_imageLbl, Qt::AlignVCenter);
}

FolderBrowserElement::~FolderBrowserElement() {
}

bool FolderBrowserElement::eventFilter(QObject *object, QEvent *event) {
    if (object == (QObject*)m_imageLbl) {
        if (event->type() == QEvent::Enter)
            setStyleSheet("background-color: rgb(154, 154, 154);");
        else if (event->type() == QEvent::Leave)
            setStyleSheet("background-color: rgb(102, 102, 102);");
        else if (event->type() == QEvent::MouseButtonDblClick)
            qDebug() << "double click";
        else if (event->type() == QEvent::ContextMenu)
            qDebug() << "context menu required!";
        return QWidget::eventFilter(object, event);
    }
}

} // namespace