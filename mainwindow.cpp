#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_smtp(NULL)
{
    ui->setupUi(this); 
    
    connect(ui->btn_add, &QPushButton::clicked, this, &MainWindow::OnAddProjectItem);
    connect(ui->btn_delete, &QPushButton::clicked, this, &MainWindow::OnRemoveProjectItem);
    connect(ui->btn_create, &QPushButton::clicked, this, &MainWindow::onCreateMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<MainWindow::PROJECT_MESSAGE> MainWindow::GetProjectsMessage()
{
    std::vector<MainWindow::PROJECT_MESSAGE> array;
    int len = this->ui->projectList->count();
    for (int j = 0; j < len; j++){
            PROJECT_MESSAGE message;
            QListWidgetItem* pItem = ui->projectList->item(j);
            ProjectItemWidget* widget = (ProjectItemWidget*)(ui->projectList->itemWidget(pItem));

            message.projectName       = widget->GetProjectName();
            message.projectPath       = widget->GetProjectPath();
            message.projectBranchName = widget->GetProjectBranchName();
            array.push_back(std::move(message));
    }

    return std::move(array);
}

void MainWindow::onCreateMessage() {

   std::vector<MainWindow::PROJECT_MESSAGE> array = GetProjectsMessage();
   std::vector<MainWindow::PROJECT_MESSAGE>::iterator iter;
   QString  str_email = "";

   for (iter = array.begin(); iter != array.end(); iter++)
   {
        str_email += Parser(*iter);
   }

   ui->textEdit->setText(str_email);

   /*QList<Project::COMMIT_MSG_TYPE>::Iterator iter;
   Project::GIT_MSG_TYPE data;
   std::stringstream s;
   std::string msg_str;
   Project* helper;

   helper = new Project("F:\\chendaole\\Boxiu_WOA_Jade");
   msg = helper->GetMessage("develop","chendaole", 1000);

   for (iter = data.cMsg.begin(); iter != data.cMsg.end(); iter++)
   {
       s << (*iter).text.toStdString() << "\n";
        qDebug() << QString::fromStdString((*iter).text.toStdString());
   }

   s << "项目:" << msg.projectName.toStdString() << "\n";
   s >> msg_str;
   return QString::fromStdString(msg_str);*/


   qDebug() << "test";
}

void MainWindow::Create()
{
    /*QString msg = CreateMessage();
    QString email = CreateEmail("chendaole", msg);

    //连接服务器
    m_smtp = new SmtpClient(this->ui->smtp->text(),
                    this->ui->port->text().toInt(),
                    SmtpClient::SslConnection);

    //设置用户名密码
    m_smtp->setUser(this->ui->password->text());
    m_smtp->setPassword(this->ui->password->text());

    if (!m_smtp->login()) {

    }*/
}

void MainWindow::SendEmail()
{

}

void MainWindow::OnAddProjectItem()
{
    QListWidgetItem* item = new QListWidgetItem(this->ui->projectList);
    ProjectItemWidget* widget = new ProjectItemWidget();

    item->setSizeHint(QSize(0, 90));
    this->ui->projectList->addItem(item);
    this->ui->projectList->setItemWidget(item, widget);
}

void MainWindow::OnRemoveProjectItem()
{
    QListWidgetItem* item = ui->projectList->takeItem(ui->projectList->currentRow());
    delete item;
}


QString MainWindow::Parser(const MainWindow::PROJECT_MESSAGE &project)
{
   QString str_message =  QString("项目[%1] \n").arg(project.projectName);

   //解析信息
   std::vector<GIT_MESSAGE> msgs = GetGitMessage(project.projectPath, "chendaole", project.projectBranchName);
   foreach (GIT_MESSAGE msg, msgs) {
       str_message += ("\b" + msg.content + "\n");
   }

   return str_message;
}

std::vector<MainWindow::GIT_MESSAGE> MainWindow::GetGitMessage(const QString& path, const QString& author, const QString& branchName)
{
    QProcess* myProcess;
    QString program;
    QString str_log;
    QStringList commits;
    std::vector<MainWindow::GIT_MESSAGE> ret;

    myProcess = new QProcess(this);
    program = "git";

    //切换分支
    auto checkout = [=](const QString& branchName) -> QString
    {
        QStringList args;

        //填充参数
        args.append("checkout");
        args.append(branchName);

        //执行命令
        myProcess->start(program, args);
        myProcess->waitForFinished();

        return myProcess->readAll();
    };

    //获取提交日志
    auto log = [=](const QString& author) -> QString
    {
        QStringList args;

        //填充参数
        args.append("log");
        args.append(QString("--author=%1").arg(author));
        args.append(QString("--since=%1.days").arg(2014));

        //执行命令
        myProcess->start(program, args);
        myProcess->waitForFinished();

        return myProcess->readAll();
    };

    //切换工作目录
    myProcess->setWorkingDirectory(path);
    //切换分支
    checkout(branchName);
    //获取提交信息
    str_log = log(author);

    //分割提交信息
    commits = str_log.split("commit");

    foreach (QString commit, commits) {
       if(commit.contains("Author"))
       {
           QStringList describe;
           GIT_MESSAGE message;

           //切割具体项
           describe = commit.split("\n");

           //存储数据
           message.id        = describe.at(0);
           message.author    = describe.at(1);
           message.timestamp = describe.at(2);
           message.content   = describe.at(4);

           ret.push_back(std::move(message));
       }
    }
    return ret;
}
