// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "settings_dialog.h"

namespace turtleraw {

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("Preferences"));
    setFixedSize(QSize(720, 640));
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint | Qt::CustomizeWindowHint));

    m_dialogLayout = new QVBoxLayout(this);
    {
        m_dialogLayout->setMargin(2);
        m_dialogLayout->setSpacing(2);
    }

    m_centralWidget = new QTabWidget(this);
    m_centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_dialogLayout->addWidget(m_centralWidget);

    // placeholders
    m_centralWidget->addTab(new QWidget(), "General");
    m_centralWidget->addTab(new QWidget(), "Image");
    m_centralWidget->addTab(new QWidget(), "Folders");
    m_centralWidget->addTab(new QWidget(), "Lua");
    m_centralWidget->addTab(new QWidget(), "Shortcuts");

    m_buttonLayout = new QHBoxLayout(this);
    {
        m_buttonLayout->setMargin(0);
        m_buttonLayout->setSpacing(0);

        m_okBtn = new QPushButton(tr("Ok"), this);
        m_cancelBtn = new QPushButton(tr("Cancel"), this);
        connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
        QWidget *_btnLayoutSpacer = new QWidget(this);
        _btnLayoutSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        
        m_buttonLayout->addWidget(_btnLayoutSpacer);
        m_buttonLayout->addWidget(m_okBtn);
        m_buttonLayout->addWidget(m_cancelBtn);
    }
    m_dialogLayout->addLayout(m_buttonLayout);

    setLayout(m_dialogLayout);
}

SettingsDialog::~SettingsDialog() {
}

void SettingsDialog::onOkBtn_Clicked() {
    // todo
}

} // namespace