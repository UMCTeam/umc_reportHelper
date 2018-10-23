#ifndef PROJECTITEMWIDGET_H
#define PROJECTITEMWIDGET_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class ProjectItemWidget;
}

class ProjectItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectItemWidget(QWidget *parent = 0);
    ~ProjectItemWidget();
    QString GetProjectName() const;
    QString GetProjectPath() const;
    QString GetProjectBranchName() const;

public slots:
    void OnOpenDir();

private:
    Ui::ProjectItemWidget *ui;
};

#endif // PROJECTITEMWIDGET_H
