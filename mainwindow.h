#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <sstream>
#include <iostream>
#include <vector>
#include <utility>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>

#include "SmtpMime"
#include "projectitemwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    typedef struct
    {
        QString projectName;
        QString projectBranchName;
        QString projectPath;
    } PROJECT_MESSAGE;

    typedef struct
    {
        QString id;
        QString author;
        QString timestamp;
        QString content;
    } GIT_MESSAGE;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::vector<MainWindow::PROJECT_MESSAGE> GetProjectsMessage();

public slots:
    void    Create();
    void    SendEmail();
    void    OnAddProjectItem();
    void    OnRemoveProjectItem();
    void    onCreateMessage();

private:
    std::vector<GIT_MESSAGE> GetGitMessage(const QString& path, const QString& author, const QString& branchName);
    QString Parser(const MainWindow::PROJECT_MESSAGE& project);

private:
    QStringList m_eamils;  //邮递列表
    SmtpClient* m_smtp;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
