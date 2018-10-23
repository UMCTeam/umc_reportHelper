#include "projectitemwidget.h"
#include "ui_projectitemwidget.h"

ProjectItemWidget::ProjectItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectItemWidget)
{
    ui->setupUi(this);

   connect(this->ui->btn_openDir, &QPushButton::clicked, this, &ProjectItemWidget::OnOpenDir);
}

ProjectItemWidget::~ProjectItemWidget()
{
    delete ui;
}

void ProjectItemWidget::OnOpenDir()
{
   QString path = QFileDialog::getExistingDirectory(this, tr("选择工程"),
                                      QApplication::applicationDirPath(),
                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
   this->ui->projectPath->setText(path);
}

QString ProjectItemWidget::GetProjectName() const
{
    return ui->projectName->text();
}

QString ProjectItemWidget::GetProjectPath() const
{
    return ui->projectPath->text();
}

QString ProjectItemWidget::GetProjectBranchName() const
{
    return ui->projectBranchName->text();
}

