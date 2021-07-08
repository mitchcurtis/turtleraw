// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "settings.h"

#include <QStandardPaths>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QVariant>

namespace turtleraw {

Settings::Settings() {
    m_xmlLocation = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/TurtleRaw/settings.xml";
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
    writer.writeTextElement("UseAlwaysThumbnails", QVariant(m_alwaysThumbnails).toString());

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
                } else if (reader.name() == "UseAlwaysThumbnails") {
                    reader.readNext();
                    useThumbnailsAlways(QVariant(reader.text().toString()).toBool());
                }
            }
        }
        if (reader.hasError())
            return false;
        xmlSettingsFile.close();
    } else {
        return false;
    }
    return true;
}

bool Settings::init() {
    if (m_xmlLocation.isEmpty())
        return false;
    
    useSystemFont(false);
    useThumbnailsAlways(true);
    // todo

    if (write())
        return true;
    return false;
}

} // namespace