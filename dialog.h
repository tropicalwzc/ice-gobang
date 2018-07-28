#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include <QChar>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "fiver.h"
using std::endl;
using std::cout;

class fiver;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    QString string_of_id(int i,int j);
    Dialog(QWidget *parent = 0);
    ~Dialog();
    int checkidea  (int x,int y,int mode=-1,int scale=5,int border=15);
    double deepanalysis(int x,int y);
    int keypoint(int x,int y,int mode=1,int maxchessline=15);
    void analysisboard(int maxchessline=15);

private:
    int chessid=0;
    int vsmode=1;
    int game_end=0;
    int chessdata[15][15]={};
    int process[225][2]={};
    QPushButton* chessboard[15][15];
    QLabel* finalresult;
private slots:
    void colorchange();
    void goback();
    void clearchessboard();

};

#endif // DIALOG_H
