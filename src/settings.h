// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

#include <QString>

namespace turtleraw {

class Settings {
public:
    Settings();

    bool write();
    bool read();

    // Only call on startup during first run check.
    bool init();

    // By default "Roboto Condensed" is used. The user can opt-in to use the
    // systems default font.
    void useSystemFont(bool yn) {
        m_systemFont = yn;
    }
    bool systemFontWanted() {
        return m_systemFont;
    }

    // TurtleRaw shows only thumbnails in the preview of raw images by default. This
    // should significantly improve the performance of the program. As always, the user can
    // of course decide against this and let full images load.
    void useThumbnailsAlways(bool yn) {
        m_alwaysThumbnails = yn;
    }
    bool alwaysThumbnails() {
        return m_alwaysThumbnails;
    }

private:
    QString m_xmlLocation;

    bool m_systemFont;
    bool m_alwaysThumbnails;
};

} // namespace