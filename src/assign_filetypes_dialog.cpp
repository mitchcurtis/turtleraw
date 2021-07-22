// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#include "assign_filetypes_dialog.h"

#include <QList>
#include <QByteArray>
#include <QImageReader>
#include <QListWidgetItem>

#include <QLabel>
#include <QHBoxLayout>

namespace turtleraw {

AssignFileTypesDialog::AssignFileTypesDialog(QWidget *parent) : QDialog(parent) {
    setFixedSize(QSize(350, 350));
    setWindowTitle(tr("Default file types"));

    m_dialogLayout = new QVBoxLayout(this);
    {
        m_dialogLayout->setMargin(2);
        m_dialogLayout->setSpacing(2);
    }

    QLabel *_descrLbl = new QLabel(tr("Select the file types for which TurtleRaw should be used by default:"));
    _descrLbl->setWordWrap(true);
    m_dialogLayout->addWidget(_descrLbl);

    m_fileTypesListWidget = new QListWidget(this);
    QList<QByteArray> arrFmts = QImageReader::supportedImageFormats();
    foreach(QByteArray b, arrFmts) {
        m_fmts.append(QString(b));
    }
    m_fileTypesListWidget->addItems(m_fmts);
    QListWidgetItem *itm = 0;
    for (int i = 0; i < m_fileTypesListWidget->count(); ++i) {
        itm = m_fileTypesListWidget->item(i);
        itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable);
        if (itm->text().contains("cr2") || itm->text().contains("crw") || itm->text().contains("nef") || itm->text().contains("raf") 
            || itm->text().contains("dng") || itm->text().contains("heic") || itm->text().contains("heif"))
            itm->setCheckState(Qt::Checked);
        else
            itm->setCheckState(Qt::Unchecked);
        
        // TODO: add a note anywhere that this needs a special version of QtRaw and an
        // manual build of Libraw. Exiv2 may not work also!
        // CR3 support is currently experimental, thats why its also unchecked.
        if (itm->text().contains("cr3")) {
            itm->setText(tr("cr3 (experimental)"));
            itm->setToolTip(tr("<b>WARNING: </b>Support for Canon's raw format CR3 is currently experimental and should "
                            "not be selected by default."));
        }
    }
    m_dialogLayout->addWidget(m_fileTypesListWidget);

    QHBoxLayout *_btnLayout = new QHBoxLayout;
    m_applyBtn = new QPushButton(tr("Apply"), this);
    connect(m_applyBtn, SIGNAL(clicked()), this, SLOT(onApplyBtn_Clicked()));
    m_cancelBtn = new QPushButton(tr("Cancel"), this);
    connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
    {
        QWidget *_btnLayoutSpacer = new QWidget;
        _btnLayoutSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        _btnLayout->addWidget(_btnLayoutSpacer);
    }
    _btnLayout->addWidget(m_applyBtn);
    _btnLayout->addWidget(m_cancelBtn);
    m_dialogLayout->addLayout(_btnLayout);
}

AssignFileTypesDialog::~AssignFileTypesDialog() {
}

void AssignFileTypesDialog::onApplyBtn_Clicked() {
    // todo
}

} // namespace