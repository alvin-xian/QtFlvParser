#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    m_flvParser = new FlvFileParser(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//开始解析
void MainWindow::on_pushButton_clicked()
{
    QString file = ui->lineEdit->text();
    if(file.isEmpty()||!QFile::exists(file)){
        return;
    }
    m_flvParser->open(file);
    showFlvInfo();
}

//获取文件路径
void MainWindow::on_pushButton_2_clicked()
{
    QString file = QFileDialog::getOpenFileName();
    if(file.isEmpty()){
        return;
    }
    ui->lineEdit->setText(file);
}
void MainWindow::addStrToTextEdit(QTextEdit *edit, QString discribe, QString text, bool bnewline)
{
    if(!bnewline){
        edit->insertPlainText(";  [" + discribe +":" + text+"]");
    }else{
        edit->append(discribe +":" + text);
    }
}

#include <QApplication>
void MainWindow::showFlvInfo()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    FlvHeader *header = m_flvParser->header();
    QFileInfo info(ui->lineEdit->text());

    addStrToTextEdit(ui->textEdit, tr("FileName:"), info.fileName());
    addStrToTextEdit(ui->textEdit, tr("StarStr:"), header->startStr());
    addStrToTextEdit(ui->textEdit, tr("hasAudio"), header->hasAudio()?"yes":"no");
    addStrToTextEdit(ui->textEdit, tr("hasVideo"), header->hasVideo()?"yes":"no");
    addStrToTextEdit(ui->textEdit, tr("version"), QString::number(header->version()));

    addStrToTextEdit(ui->textEdit_2, tr("header"), "", false);
    int i = 1;
    foreach (ITag *tag, m_flvParser->packagets()) {
        QApplication::processEvents();
        addStrToTextEdit(ui->textEdit_2,
                         QString("[") +QString::number(i++)+tr("]Type:"),
                         tag->getTypeStr(tag->type()));
        addStrToTextEdit(ui->textEdit_2,
                         tr("size"),
                         QString::number(tag->size())+" byte", false);
        addStrToTextEdit(ui->textEdit_2,
                         tr("timestamp"),
                         QString::number(tag->timeStamp())+"ms", false);
        addStrToTextEdit(ui->textEdit_2,
                         tr("steamid"),
                         QString::number(tag->steamid()), false);
        if(tag->type() == ITag::Flv_VideoTag){
            FlvVideoTag *vtag = qobject_cast<FlvVideoTag*>(tag);
            addStrToTextEdit(ui->textEdit_2,
                             tr("FrameType"),
                             vtag->getFrameType(vtag->frameType()),
                             false);
            addStrToTextEdit(ui->textEdit_2,
                             tr("VideoCode"),
                             vtag->getVideoCodeStr(vtag->codeType()),
                             false);
        }
    }

}
