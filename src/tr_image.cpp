// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "tr_image.h"
#include "easylogging++.h"

#include <QDateTime>
#include <QMimeType>
#include <QMimeDatabase>

namespace turtleraw {

TRImage::TRImage(const QString &filePath) : m_filePath(filePath) {
    m_fileInfo.setFile(m_filePath);
}

TRImage::~TRImage() {
    m_filePath = "";
    m_fileName = "";
    m_fileLastModifed = "";
    m_fileMimeType = "";
}

bool TRImage::isValidPath() {
    if (!m_fileInfo.exists()) {
        LOG(ERROR) << "(TRImage) Given file does not exist.";
        return false;
    } else {
        return true;
    }
    return false;
}

void TRImage::setFilePath(const QString &filePath) {
    m_fileInfo.setFile(filePath);
    if (isValidPath())
        m_filePath = filePath;
}

QString TRImage::read() {
    if (m_filePath.isEmpty()) {
        LOG(ERROR) << "(TRImage) No file given. Return m_filePath.";
        return m_filePath;
    }

    if (!isValidPath()) {
        LOG(ERROR) << "(TRImage) Given file does not exist. Return m_filePath.";
        return m_filePath;
    }

    m_fileName = m_fileInfo.fileName();
    m_fileLastModifed = m_fileInfo.lastModified().toString();
    
    QMimeType f_mimeType = QMimeDatabase().mimeTypeForFile(m_fileInfo);
    m_fileMimeType = f_mimeType.name();

    return m_filePath;
}

} // namespace