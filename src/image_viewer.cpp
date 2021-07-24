// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "image_viewer.h"
#include "easylogging++.h"
#include <QDebug>

#include <QHBoxLayout>
#include <QScrollBar>

#include <QImageReader>
#include <QImage>
#include <QPixmap>

#include <QFileInfo>

namespace turtleraw {

ImageViewerWidget::ImageViewerWidget(QWidget *parent) : QWidget(parent) {
    m_imageLbl = new QLabel;
    {
        m_imageLbl->setText(tr("No image"));
        m_imageLbl->setAlignment(Qt::AlignCenter);
        m_imageLbl->setScaledContents(true);
    }

    m_scrollArea = new QScrollArea;
    {
        m_scrollArea->setContentsMargins(0, 0, 0, 0);
        m_scrollArea->setAlignment(Qt::AlignCenter);
        m_scrollArea->setFrameStyle(0);
        m_scrollArea->setWidget(m_imageLbl);
        m_scrollArea->setWidgetResizable(true);
    }

    QHBoxLayout *widgetLayout = new QHBoxLayout(this);
    {
        widgetLayout->setMargin(4);
        widgetLayout->setSpacing(0);
        widgetLayout->addWidget(m_scrollArea);
    }

    setLayout(widgetLayout);
}

bool ImageViewerWidget::loadImage(QString filePath, bool useThumbnails) {
    // Clear contents first.
    clear();

    QFileInfo fileInf(filePath);
    if (!fileInf.exists())
        LOG(FATAL) << "This should not happen. Image moved/deleted on load.";

    QImageReader rd(filePath);
    qDebug() << "INT original size: " << rd.size();
    origSize = rd.size();
    m_useThumbs = false;
    if (rd.size().isValid()) {
        if (useThumbnails) {
            reqSize = QSize(rd.size().width()/4, rd.size().height()/4);
            m_useThumbs = true;
            // We use QDebug here because I had a issue open in QtRaw...
            qDebug() << "INT requested size: " << reqSize;
            rd.setScaledSize(reqSize);
        }
        QSize rsz = rd.size();
        rsz.scale(QSize(m_imageLbl->width(), m_imageLbl->height()), Qt::KeepAspectRatio);
        QImage previewImage;
        rd.read(&previewImage);
        m_pxmp = QPixmap::fromImage(previewImage);
    } else {
        // TODO: for whatever reason on HEIC images it returns a original size of (-1, -1). Why?
        LOG(WARNING) << "Invalid size. Lets try to display it anyway...";
        QImage invalidImage;
        rd.read(&invalidImage);
        m_pxmp = QPixmap::fromImage(invalidImage);
    }

    m_imageLbl->setPixmap(m_pxmp);
    resizeImage();

    return true;
}

void ImageViewerWidget::resizeImage() {
    const QPixmap *px = m_imageLbl->pixmap();
    if (!px)
        return;
    
    QSize pxSize = px->size();

    if (pxSize.width() > m_scrollArea->width() || pxSize.height() > m_scrollArea->height()) {
        if (m_useThumbs) {
            if (reqSize.width() < 0)
                pxSize.scale(m_scrollArea->width(), m_scrollArea->height(), Qt::KeepAspectRatio);
            else
                pxSize.scale(reqSize.width(), reqSize.height(), Qt::KeepAspectRatio);
        } else {
            if (origSize.width() < 0)
                pxSize.scale(m_scrollArea->width(), m_scrollArea->height(), Qt::KeepAspectRatio);
            else
                pxSize.scale(origSize.width(), origSize.height(), Qt::KeepAspectRatio);
        }
    }
    
    m_imageLbl->resize(pxSize);
    m_imageLbl->setMaximumSize(pxSize);
    m_imageLbl->adjustSize();
}

} // namespace