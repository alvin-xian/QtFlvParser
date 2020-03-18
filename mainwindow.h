#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "flvfileparser.h"
#include <QTextEdit>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
private:
    void showFlvInfo();
private:
    Ui::MainWindow *ui;
    FlvFileParser *m_flvParser = Q_NULLPTR;
    void addStrToTextEdit(QTextEdit *edit, QString discribe, QString text, bool bnewline = true);
};

#endif // MAINWINDOW_H
