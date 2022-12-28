#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setMouseTracking(true);
    activateWindow();
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);//

    /*CustomView *view = new CustomView();
    view->show();//测试代码记得删除*/
    QTimer *time = new QTimer(this);
    time->setSingleShot(true);
    time->start(10);
    connect(time,&QTimer::timeout,this,[=](){init();});
}


void MainWindow::init(){
    //初始化关闭打开最大化的按钮，按钮均用qss重新配置，funcLayout就是摆放三个按钮的位置
    QFile file_op(":/op.qss");
    //QFile file_line(":/lineEdit.qss");
    file_op.open(QFile::ReadOnly);
    //file_line.open(QFile::ReadOnly);
    this->setFixedSize(800,600);
    ui->closebutton->setMaximumSize(QSize(20,20));
    ui->minButton->setMaximumSize(QSize(20,20));
    ui->maxButton->setMaximumSize(QSize(20,20));
    ui->closebutton->setObjectName("closeBtn");
    ui->minButton->setObjectName("minBtn");
    ui->maxButton->setObjectName("maxBtn");
    ui->funcLayout->setSpacing(10);
    ui->funcLayout->setContentsMargins(0,0,0,0);
    ui->funcLayout->setAlignment(Qt::AlignLeft);

    ui->pwdEdit->setFixedSize(200,70);//账号和密码的输入框
    ui->pwdEdit->setFixedHeight(20);
    ui->actEdit->setFixedSize(200,70);
    ui->actEdit->setFixedHeight(20);
    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    qApp->setStyleSheet(file_op.readAll());
    //按钮文件配置
    ui->loginBtn->setStyleSheet("QPushButton{font: 12 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed

    ui->registerBtn->setStyleSheet("QPushButton{font: 12 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    //这里就是标题栏
    QFont fontTitle("Corbel Light", 20);
    QLabel *titlelabel = new QLabel("START");
    fontTitle.setPixelSize(30);//解决不同分辨率下字体显示不全的问题
    titlelabel->setFont(fontTitle);
    ui->titleLayout->insertWidget(0,titlelabel);
    ui->titleLayout->setAlignment(Qt::AlignHCenter);

    //绑定设置按钮功能与动画

    CustomIcon *optionIcon = new CustomIcon(":/settings.png",Qt::transparent,ui->centralwidget);
    ui->funcLayout->insertWidget(0,optionIcon);
    betterOption *optionWidget = new betterOption(this,cornerradius);
    //optionWidget->show();
    //SheildLayer *temp = new SheildLayer(ui->centralwidget);
    connect(optionIcon,&CustomIcon::clicked,this,[=](){
        QPropertyAnimation *rotate = new QPropertyAnimation(optionIcon, "rotateAngle", this);
        rotate->setDuration(750);
        rotate->setStartValue(0);
        rotate->setEndValue(90);
        rotate->setEasingCurve(QEasingCurve::Linear);
        rotate->start();//完成icon点击的动画


        QPropertyAnimation *slide = new QPropertyAnimation(optionWidget,"pos");
        slide->setDuration(750);
        slide->setStartValue(optionWidget->startpoint());
        slide->setEndValue(QPoint(optionWidget->width()-190,optionWidget->height()-450));
        slide->setEasingCurve(QEasingCurve::InOutQuad);
        optionWidget->show();

        //ui->funcLayout->addWidget(temp);
        //temp->show();
        slide->start();
        optionWidget->setIsopen(true);


        //设置页滑出完成，但是可以改进
        //10.26该写法就是错的，此时还在按下的那个事件里面
        //ui->centralwidget->setEnabled(false);//相当于自己创造了模态，
        //应该有更好的办法，这个办法太蠢了
    });
    connect(optionWidget,&betterOption::colorChanged,this,[=](int x){
       setTheme(x);
       repaint();
    });

}
MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checklogin()
{
    bool account_exist = false;
    bool pwd_check = false;
    QFile fs_account("useraccount.txt");
    fs_account.open(QIODevice::ReadOnly);
    QFile pwd_account("userpwd.txt");
    pwd_account.open(QIODevice::ReadOnly);//只读方式打开文件
    QString account = ui->actEdit->text();
    QString pwd = ui->pwdEdit->text();
    QCryptographicHash *hashcode_account = new QCryptographicHash(QCryptographicHash::Md5);
    hashcode_account->addData(account.toUtf8());
    QCryptographicHash *hashcode_pwd = new QCryptographicHash(QCryptographicHash::Md5);
    hashcode_pwd->addData(pwd.toUtf8());
    int ac_count = 0;
    while(!fs_account.atEnd()){
        QByteArray tempac = fs_account.readLine();
        tempac = tempac.trimmed();//这里读出来有一个换行符，导致一直不对
        //qDebug()<< hashcode_account->result().toHex()<<endl;
        //qDebug()<<tempac<<endl;
        ++ac_count;
        if(tempac == hashcode_account->result().toHex()){
            account_exist = true;//一直遍历直到找到这个账号
            break;
        }
    }
    fs_account.close();
    if(!account_exist){
        return false;
    }
    int pwd_count = 0;
    while(!pwd_account.atEnd()){
        QByteArray temppwd = pwd_account.readLine();
        temppwd = temppwd.trimmed();
        ++pwd_count;
        if(temppwd == hashcode_pwd->result().toHex() && pwd_count == ac_count){
            if(account_exist){
                pwd_check = true;
            }
            //
            break;
        }
    }
    if(pwd_check){
        return true;
    }
    else{
        return false;
    }
}

void MainWindow::paintEvent(QPaintEvent *event){//重写paintevent实现圆角矩形，
                                                //其实就是直接画一个出来
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(QGradient(static_cast<QGradient::Preset>(themecolor))));
        painter.setPen(Qt::transparent);
        painter.drawRoundedRect(rect(), 20, 20);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
        if(m_mousepressed&&(event->button() == Qt::NoButton)){

            this->move(event->globalPos() - m_curmousepos);//这里鼠标的坐标变化
            //思考一下，如果这里鼠标不动，那就还是会move到刚刚的原位置，
            //一旦鼠标动了一个像素点，这个之间的差值就会增加，随之move到新的位置
            event->accept();
        }
        if(abs(event->pos().x() - ui->centralwidget->width())<=10){
            setCursor(Qt::SizeBDiagCursor);
        }
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        m_mousepressed = true;
        qDebug()<<event->globalPos();
        m_curmousepos = event->globalPos() - this->pos();//相当于鼠标和部件边框之间差了多少
        qDebug()<<m_curmousepos;
        event->accept();
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    m_mousepressed = false;
}

void MainWindow::on_closebutton_clicked()
{
    close();
}

void MainWindow::on_minButton_clicked()
{
    showMinimized();
}

void MainWindow::on_maxButton_clicked()
{
    if(!ismaxed){
     showFullScreen();
     ismaxed = true;
    }
    else{
        showNormal();
        ismaxed = false;
    }

}

void MainWindow::on_loginBtn_clicked()
{
    if(checklogin()){
        qDebug()<<"准确对咯"<<endl;
        MainGraph *Maingraph = new MainGraph(nullptr,ui->actEdit->text(),themecolor);
        Maingraph->show();
        this->setVisible(false);
    }
    else{
          QMessageBox msgBox;
          msgBox.setWindowTitle("错误");
          msgBox.setText("账号或密码错误，请重试");
          msgBox.exec();
    }
}

void MainWindow::on_registerBtn_clicked()
{
    //实现弹出界面进行注册

    REgisterdialog *dlg = new REgisterdialog(this);
    dlg->setModal(true);
    dlg->show();
}
