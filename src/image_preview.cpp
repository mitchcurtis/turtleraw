// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "image_preview.h"
#include <QDebug>

#include <QHBoxLayout>
#include <QScrollBar>

#include <QImageReader>
#include <QImage>
#include <QPixmap>
#include <QSize>

namespace turtleraw {

ImagePreviewWidget::ImagePreviewWidget(QWidget *parent) : QWidget(parent) {
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
        m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_scrollArea->verticalScrollBar()->blockSignals(true);
        m_scrollArea->horizontalScrollBar()->blockSignals(true);
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

QPixmap& ImagePreviewWidget::loadImage(QString filePath, bool useThumbnails) {
    // Clear contents first.
    clear();

    QImageReader rd(filePath);
    if (rd.size().isValid()) {
        if (useThumbnails) {
            QSize reqSize = QSize(rd.size().width()/4, rd.size().height()/4);
            // We use QDebug here because I had a issue open in QtRaw...
            qDebug() << "INT requested size: " << reqSize;
            rd.setScaledSize(reqSize);
        }
        QSize rsz = rd.size();
        rsz.scale(QSize(m_imageLbl->width(), m_imageLbl->height()), Qt::KeepAspectRatio);
        QImage previewImage;
        rd.read(&previewImage);
        m_previewPxmp = QPixmap::fromImage(previewImage);
    }

    m_imageLbl->setPixmap(m_previewPxmp);
    resizeImagePreview();
}

void ImagePreviewWidget::resizeImagePreview() {
    const QPixmap *px = m_imageLbl->pixmap();
    if (!px)
        return;
    
    QSize pxSize = px->size();
    if (pxSize.width() > m_scrollArea->width() || pxSize.height() > m_scrollArea->height())
        pxSize.scale(m_scrollArea->width(), m_scrollArea->height(), Qt::KeepAspectRatio);
    
    m_imageLbl->setFixedSize(pxSize);
    m_imageLbl->adjustSize();
}

} // namespace