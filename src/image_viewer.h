// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

#include <QWidget>
#include <QObject>

#include <QLabel>
#include <QScrollArea>
#include <QPixmap>
#include <QSize>

namespace turtleraw {

class ImageViewerWidget : public QWidget {
    Q_OBJECT
public:
    ImageViewerWidget(QWidget *parent = nullptr);

    // Loads an image from a given file path. Nothing more, nothing less.
    QPixmap& loadImage(QString filePath, bool useThumbnails);
    
    // Clear the label holding the image.
    void clear() {
        m_imageLbl->clear();
        m_imageLbl->setText(tr("No image"));
    }

    QScrollArea *m_scrollArea;
    QSize reqSize;
protected:
    void resizeImage();

    QLabel *m_imageLbl;
    QPixmap m_pxmp;
};

} // namespace