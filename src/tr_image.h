// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

#include <QString>
#include <QFileInfo>

namespace turtleraw {

class TRImage {
public:
    TRImage() { };
    TRImage(const QString &filePath);
    ~TRImage();

    // Checks if the path to the image is valid.
    bool isValidPath();

    void setFilePath(const QString &filePath);

    // Read the file and return a valid QImageReader to work with.
    QString read();

    // Return the absolute file path to the image.
    QString filePath() {
        return m_filePath;
    }

    // Return the file name, e.g. "IMG_05672.CR2".
    QString fileName() {
        return m_fileName;
    }

    // Date & time when the file was last modified.
    QString lastModify() {
        return m_fileLastModifed;
    }

    // Get the image mime type, e.g. "image/canon-raw-cr2".
    QString mimeType() {
        return m_fileMimeType;
    }

protected:
    QString m_filePath;
    QString m_fileName;
    QString m_fileLastModifed;
    QString m_fileMimeType;

    QFileInfo m_fileInfo;
};

} // namespace