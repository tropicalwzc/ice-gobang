#include "dialog.h"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout* mainlayout=new QGridLayout;
    int i,j;
    for( i=0;i<15;i++)
        for( j=0;j<15;j++)
        {
          chessboard[i][j]=new QPushButton;
          chessboard[i][j]->setFixedHeight(51);
          chessboard[i][j]->setFixedWidth(51);
          chessboard[i][j]->setObjectName(string_of_id(i,j));
          chessboard[i][j]->setStyleSheet("background-color:rgb(188,188,188)");

          connect(chessboard[i][j],SIGNAL(clicked(bool)),this,SLOT(colorchange()));
          mainlayout->addWidget(chessboard[i][j],i,j);

        }
    QPushButton* restart=new QPushButton;
    restart->setFixedHeight(60);
    restart->setFixedWidth(150);
    restart->setFont(QFont("黑体",20));
    restart->setText("重新开始");
    connect(restart,SIGNAL(clicked(bool)),this,SLOT(clearchessboard()));
    QPushButton* goback=new QPushButton;
    goback->setFixedHeight(60);
    goback->setFixedWidth(150);
    goback->setFont(QFont("黑体",20));
    goback->setText("撤销一步");
    connect(goback,SIGNAL(clicked(bool)),this,SLOT(goback()));
    finalresult=new QLabel;
    finalresult->setFixedHeight(500);
    finalresult->setFixedWidth(150);
    finalresult->setFont(QFont("Segoe Print",12));
    finalresult->setText("");
    finalresult->setStyleSheet("color:rgb(188,188,188)");
    finalresult->setText("黑棋禁止走双三\n双四以及长连\n你先下我再下\n这是因为五子棋\n经过数学推导\n先下方必胜\n我先下你肯定输\n但是我后下\n你未必赢");

    QVBoxLayout* lefter=new QVBoxLayout;
    lefter->addWidget(finalresult);

    lefter->addWidget(restart);
    lefter->addWidget(goback);
    QHBoxLayout* masterlayout=new QHBoxLayout(this);
    masterlayout->addLayout(lefter);
    masterlayout->addLayout(mainlayout);
}

Dialog::~Dialog()
{

}

QString Dialog::string_of_id(int i,int j)
{
    QString names;
    names+=i/10+48;
    names+=i%10+48;
    names+=j/10+48;
    names+=j%10+48;
    return names;
}
void Dialog::clearchessboard()
{
  game_end=0;
  finalresult->setText("");
  for(int i=0;i<15;i++)
      for(int j=0;j<15;j++)
      {
          chessdata[i][j]=0;
          chessboard[i][j]->setStyleSheet("background-color:rgb(188,188,188)");
      }
  chessid=0;
}
void Dialog::colorchange()
{
   QPushButton* btn= qobject_cast<QPushButton*>(sender());
   QString name=btn->objectName();
   int x_id=(name.at(0).unicode()-48)*10+(name.at(1).unicode()-48);
   int y_id=(name.at(2).unicode()-48)*10+(name.at(3).unicode()-48);

  if(chessdata[x_id][y_id]!=1&&chessdata[x_id][y_id]!=-1&&game_end==0)
  {
      if(chessid%2==0)
      {
         btn->setStyleSheet("background-color:black");
         chessdata[x_id][y_id]=1;
        if(checkidea(x_id,y_id,1,5)!=0)
        {
         finalresult->setText("You win");
         game_end=1;
        }
      }
      else{
          btn->setStyleSheet("background-color:white");
          chessdata[x_id][y_id]=-1;
          if(checkidea(x_id,y_id,-1,4)!=0)
            cout<<"white "<<checkidea(x_id,y_id,-1,4)<<"four"<<endl;
      }
      process[chessid][0]=x_id;
      process[chessid][1]=y_id;
      chessid++;

      if(vsmode==1&&game_end==0)
          analysisboard();
  }


}
void Dialog::goback()
{
    game_end=0;
    finalresult->setText("");
    if(chessid>0)
    {
       chessid--;
       chessdata[process[chessid][0]][process[chessid][1]]=0;
       chessboard[process[chessid][0]][process[chessid][1]]->setStyleSheet("background-color:rgb(188,188,188)");
    }
    if(chessid>0&&chessid%2==1)
    {
       chessid--;
       chessdata[process[chessid][0]][process[chessid][1]]=0;
       chessboard[process[chessid][0]][process[chessid][1]]->setStyleSheet("background-color:rgb(188,188,188)");
    }
}
int Dialog::checkidea(int x,int y,int mode,int scale,int border)
{
    int accumulate=0;
    int lastaccu=0;
    int bis=0;
    int doublethree=0;
    if(scale!=5)
        bis=1;

   int res=0;
   for(int i=x-scale+1-bis;i<x+1;i++)
   {
        res=0;
        for(int j=i;j<i+scale+bis&&j>=0&&j<border;j++)
        {
            if(j<0||j>border-1)
            {
                res=0;
                break;
            }
            res+=chessdata[j][y];
        }

       if(mode==1)
       {
           if(res==scale)
               accumulate++;
       }
       else{
           if(res==-scale)
               accumulate++;
       }
   }
   if(accumulate-lastaccu>1&&scale>3)
   {
   //   cout<<"four "<<rand()%1000<<endl;
   accumulate*=10;
   doublethree++;
   }
   lastaccu=accumulate;

   for(int i=y-scale+1-bis;i<y+1;i++)
   {
        res=0;
        for(int j=i;j<i+scale+bis;j++)
        {
            if(j<0||j>border-1)
            {
                res=0;
                break;
            }
            res+=chessdata[x][j];
        }

        if(mode==1)
        {
            if(res==scale)
                accumulate++;
        }
        else{
            if(res==-scale)
                accumulate++;
        }
   }
   if(accumulate-lastaccu>1&&scale>3)
   {
           //   cout<<"four "<<rand()%1000<<endl;
   accumulate*=10;
      doublethree++;
   }
   lastaccu=accumulate;

   for(int i=1-scale-bis;i<1;i++)
   {
        res=0;
        for(int j=i;j<i+scale+bis;j++)
        {
          if(x+j<0||x+j>border-1||y+j<0||y+j>border-1)
          {
              res=0;
              break;
          }
          res+=chessdata[x+j][y+j];
        }
        if(mode==1)
        {
            if(res==scale)
                accumulate++;
        }
        else{
            if(res==-scale)
                accumulate++;
        }
   }
   if(accumulate-lastaccu>1&&scale>3)
   {
         //     cout<<"four "<<rand()%1000<<endl;
      accumulate*=10;
      doublethree++;
   }
   lastaccu=accumulate;

   for(int i=1-scale-bis;i<1;i++)
   {
        res=0;
        for(int j=i;j<i+scale+bis;j++)
        {
            if(x-j<0||x-j>border-1||y+j<0||y+j>border-1)
            {
                res=0;
                break;
            }

          res+=chessdata[x-j][y+j];
        }
        if(mode==1)
        {
            if(res==scale)
                accumulate++;
        }
        else{
            if(res==-scale)
                accumulate++;
        }
   }
   if(accumulate-lastaccu>1&&scale>3)
   {
     //  cout<<"four "<<rand()%1000<<endl;
      accumulate*=10;
      doublethree++;
   }

   if(scale==5&&accumulate>0)
   {
        accumulate*=1000;
   }

   return accumulate;
}
int Dialog:: keypoint(int x,int y,int mode,int maxchessline)
{
    if(chessdata[x][y]!=0)
        return 0;

    chessdata[x][y]=mode;
    int aiming=mode*4;
    int tid=0;
    for(int d=x-5;d<x+1;d++)
    {
     int counter=0;
     for(int j=d;j<d+5;j++)
     {
         if(j<0||j>maxchessline-1)
         {
             counter=0;
             break;
         }
         counter+=chessdata[j][y];
     }

     if(counter==aiming)
     {
     tid++;
     }
    }
    for(int d=y-5;d<y+1;d++)
    {
     int counter=0;
     for(int j=d;j<d+5;j++)
     {
         if(j<0||j>maxchessline-1)
         {
             counter=0;
             break;
         }

         counter+=chessdata[x][j];
     }

     if(counter==aiming)
     {
      tid++;
     }
    }

    for(int d=-5;d<1;d++)
    {
     int counter=0;
     for(int j=d;j<d+5;j++)
     {
         if(x+j<0||x+j>maxchessline-1||y+j<0||y+j>maxchessline-1)
         {
             counter=0;
             break;
         }
          counter+=chessdata[x+j][y+j];
     }

     if(counter==aiming)
     {
     tid++;
     }
    }
    for(int d=-5;d<1;d++)
    {
     int counter=0;
     for(int j=d;j<d+5;j++)
     {
         if(x-j<0||x-j>maxchessline-1||y+j<0||y+j>maxchessline-1)
         {
             counter=0;
             break;
         }
        counter+=chessdata[x-j][y+j];
     }

     if(counter==aiming)
     {
      tid++;
     }
    }
    chessdata[x][y]=0;
    return tid;
}
void Dialog::analysisboard(int maxchessline)
{
  srand(time(0));
  int border_x_min=100,border_x_max=-1;
  int border_y_min=100,border_y_max=-1;
  for(int i=0;i<maxchessline;i++)
  {
    for(int j=0;j<maxchessline;j++)
    {
        if(chessdata[i][j]!=0)
        {
            if(i>border_x_max)
                border_x_max=i;
            if(j>border_y_max)
                border_y_max=j;
            if(i<border_x_min)
                border_x_min=i;
            if(j<border_y_min)
                border_y_min=j;
        }
    }
  }
  border_x_max++;
  border_y_max++;
  border_x_min--;
  border_y_min--;
  double pl_score=-1;
  int pl_x,pl_y;

  for(int i=border_x_min;i<border_x_max+1;i++)
  {
      if(i<0||i>maxchessline-1)
          continue;

      for(int j=border_y_min;j<border_y_max+1;j++)
      {
        if(j>maxchessline-1||j<0)
            continue;

        if(chessdata[i][j]!=0)
            continue;

        double attackscore=0;
        chessdata[i][j]=-1;

        for(int p=5;p>1;p--)
        {
           attackscore+=pow(2,p)*checkidea(i,j,-1,p);
           attackscore+=pow(2,p)*deepanalysis(i,j);
        }
        int defensescore=0;
        chessdata[i][j]=1;
        for(int p=5;p>1;p--)
        {
           defensescore+=pow(2,p)*checkidea(i,j,1,p);
           defensescore+=pow(2,p)*deepanalysis(i,j);
        }
        chessdata[i][j]=0;

        if(keypoint(i,j,-1)==1)
        {
            attackscore+=20000;
        }
        if(keypoint(i,j,-1)>=2)
        {
            attackscore+=200000;
        }
        if(keypoint(i,j,1)==1)
        {
            defensescore+=2000;
        }
        if(keypoint(i,j,1)>1)
        {
            defensescore+=200000;
        }
        if(keypoint(i,j,1)>0&&checkidea(i,j,1,4)>5)
        {
            defensescore+=200000;
        }

        double A_score=attackscore+defensescore-rand()%2;
        if(A_score>pl_score)
        {
         pl_score=A_score;
         pl_x=i;
         pl_y=j;
        // cout<<"id "<<rand()%1000<<" "<<i<<","<<j<<" score "<<pl_score<<endl;
        }

      }
  }
  chessboard[pl_x][pl_y]->setStyleSheet("background-color:white");
  chessdata[pl_x][pl_y]=-1;
  process[chessid][0]=pl_x;
  process[chessid][1]=pl_y;
  if(checkidea(pl_x,pl_y,-1,5)!=0)
  {
    finalresult->setText("Tropical fish\n win");
    game_end=1;
  }

  chessid++;
}
double Dialog::deepanalysis(int i,int j)
{
    double pl_score,attackscore=0,defensescore=0;
    chessdata[i][j]=-1;
    for(int p=5;p>1;p--)
    {
       attackscore+=pow(2,p)*checkidea(i,j,-1,p);
    }

    chessdata[i][j]=1;
    for(int p=5;p>1;p--)
    {
       defensescore+=pow(2,p)*checkidea(i,j,1,p);
    }
    pl_score=attackscore+defensescore;
    chessdata[i][j]=0;
    return pl_score;
}
