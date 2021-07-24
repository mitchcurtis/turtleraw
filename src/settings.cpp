// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "settings.h"
#include "easylogging++.h"

#include <QStandardPaths>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QVariant>

namespace turtleraw {

Settings::Settings() {
    m_xmlLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/settings.xml";
}

bool Settings::write() {
    if (m_xmlLocation.isEmpty())
        return false;
    
    QFile xmlSettingsFile(m_xmlLocation);
    if (!xmlSettingsFile.open( QIODevice::WriteOnly ))
        return false;
    
    QXmlStreamWriter writer(&xmlSettingsFile);
    writer.setAutoFormatting(true);

    writer.writeStartDocument();
    writer.writeStartElement("Settings");

    writer.writeTextElement("UseSystemFont", QVariant(m_systemFont).toString());
    writer.writeTextElement("AlwaysUseThumbnails", QVariant(m_useThumbnails).toString());

    writer.writeEndElement();
    writer.writeEndDocument();

    xmlSettingsFile.close();
    return true;
}

bool Settings::read() {
    if (m_xmlLocation.isEmpty())
        return false;
    
    QFile xmlSettingsFile(m_xmlLocation);
    if (xmlSettingsFile.exists() && xmlSettingsFile.open( QIODevice::ReadOnly )) {
        QXmlStreamReader reader(&xmlSettingsFile);
        while (!reader.atEnd()) {
            reader.readNext();
            if (reader.isStartElement()) {
                if (reader.name() == "UseSystemFont") {
                    reader.readNext();
                    useSystemFont(QVariant(reader.text().toString()).toBool());
                } else if (reader.name() == "AlwaysUseThumbnails") {
                    reader.readNext();
                    alwaysUseThumbnails(QVariant(reader.text().toString()).toBool());
                }
            }
        }
        if (reader.hasError()) {
            LOG(FATAL) << "Internal error in QXmlStreamReader!";
        }
        xmlSettingsFile.close();
    } else {
        LOG(ERROR) << "Could not open settings for read.";
        return false;
    }
    return true;
}

bool Settings::init() {
    if (m_xmlLocation.isEmpty())
        return false;
    
    useSystemFont(false);
    alwaysUseThumbnails(true);
    // todo

    if (write()) {
        LOG(INFO) << "Wrote settings to: " << m_xmlLocation;
        return true;
    }
    return false;
}

} // namespace