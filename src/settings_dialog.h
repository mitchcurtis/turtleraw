// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

#include <QDialog>
#include <QObject>
#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QTabWidget>
#include <QPushButton>

namespace turtleraw {

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private:
    QVBoxLayout *m_dialogLayout;
    QTabWidget *m_centralWidget;

    QHBoxLayout *m_buttonLayout;
    QPushButton *m_okBtn;
    QPushButton *m_cancelBtn;

private slots:
    void onOkBtn_Clicked();
};

} // namespace