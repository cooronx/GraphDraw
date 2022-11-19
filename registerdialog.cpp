#include "registerdialog.h"
#include "ui_registerdialog.h"

REgisterdialog::REgisterdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::REgisterdialog)
{
    ui->setupUi(this);
    QFile fs(":/op.qss");
    fs.open(QIODevice::ReadOnly);
    this->setStyleSheet(fs.readAll());
    ui->closeBtn->setFixedSize(20,20);
    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);
    ui->pwdlineEdit_2->setEchoMode(QLineEdit::Password);
    ui->registerBtn->setStyleSheet("QPushButton{font: 12 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);//圆角窗口必备
    ui->Titlelabel->setFont(QFont("Cobel",20));
}

REgisterdialog::~REgisterdialog()
{
    delete ui;
}

void REgisterdialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::transparent);
    painter.drawRoundedRect(rect(), 20, 20);
}
void REgisterdialog::mouseMoveEvent(QMouseEvent *event){
        if(m_mousepressed&&(event->button() == Qt::NoButton)){
            //qDebug()<<event->globalPos();
            this->move(event->globalPos() - m_curmousepos);//这里鼠标的坐标变化
            //思考一下，如果这里鼠标不动，那就还是会move到刚刚的原位置，
            //一旦鼠标动了一个像素点，这个之间的差值就会增加，随之move到新的位置
            event->accept();
        }

}
void REgisterdialog::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        m_mousepressed = true;
        //qDebug()<<event->globalPos();
        m_curmousepos = event->globalPos() - this->pos();//相当于鼠标和部件边框之间差了多少
        //qDebug()<<m_curmousepos;
        event->accept();
    }
}
void REgisterdialog::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    m_mousepressed = false;
}

void REgisterdialog::on_closeBtn_clicked()
{
    close();
}

void REgisterdialog::on_registerBtn_clicked()
{
    //首先检查俩次密码是不是一样的，不是一样的让他重新输入
    if(ui->pwdlineEdit->text() != ui->pwdlineEdit_2->text()){
        QMessageBox::StandardButton result = QMessageBox::information(this, "提示","两次输入的密码不一样");
    }
    else{//用md5加密的方式将密码账号写入
        QMessageBox::StandardButton result = QMessageBox::information(this, "提示","注册成功");
        QFile fs_account("useraccount.txt");
        fs_account.open(QIODevice::ReadWrite|QIODevice::Append);//若文件不存在，qt会自动创建该文件
        QFile pwd_account("userpwd.txt");
        pwd_account.open(QIODevice::ReadWrite|QIODevice::Append);//若文件不存在，qt会自动创建该文件
        QCryptographicHash *hashcode_account = new QCryptographicHash(QCryptographicHash::Md5);
        hashcode_account->addData(ui->actlineEdit->text().toUtf8());
        QCryptographicHash *hashcode_pwd = new QCryptographicHash(QCryptographicHash::Md5);
        hashcode_pwd->addData(ui->pwdlineEdit->text().toUtf8());
        fs_account.write(hashcode_account->result().toHex());
        fs_account.write("\n");
        pwd_account.write(hashcode_pwd->result().toHex());
        pwd_account.write("\n");
        close();
    }
}
