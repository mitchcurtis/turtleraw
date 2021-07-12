// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

#include <QDialog>
#include <QObject>
#include <QWidget>

#include <QStringList>

#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>

namespace turtleraw {

class AssignFileTypesDialog : public QDialog {
    Q_OBJECT
public:
    explicit AssignFileTypesDialog(QWidget *parent = nullptr);
    ~AssignFileTypesDialog();

protected:
    QStringList m_fmts;

private:
    QVBoxLayout *m_dialogLayout;
    QListWidget *m_fileTypesListWidget;
    QPushButton *m_applyBtn;
    QPushButton *m_cancelBtn;

private slots:
    void onApplyBtn_Clicked();
};

} // namespace