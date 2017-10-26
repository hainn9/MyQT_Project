#include "mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QEvent>
#include <QKeyEvent>



MainWindow::MainWindow()
{
    qDebug("Start MainWindow::MainWindow");
        m_timer = new QTimer(this);
        m_timer->setSingleShot(true);
        m_timer->setInterval(100);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
        m_timer->stop();
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("test");
        db.setUserName("root");
        db.setPassword("");
        set_visble_List_Text(false);
        set_Clear_All_Input_Text(false);
        qDebug("End MainWindow::MainWindow");
}


void MainWindow::initData(QQmlApplicationEngine *engine){
    qDebug("Start MainWindow::initData");
    m_engine=engine;
    QObject::connect((m_engine)->rootObjects().first(),SIGNAL(click_search(QString)),this,SLOT(slotHandlerEvent(QString)));
    QObject::connect((m_engine)->rootObjects().first(),SIGNAL(input_search(QString)),this,SLOT(slotTextSuggestEvent(QString)));
    QObject::connect((m_engine)->rootObjects().first(),SIGNAL(to_click(int)),this,SLOT(slotTextChoiceInListData(int)));
    QObject::connect((m_engine)->rootObjects().first(),SIGNAL(clear()),this,SLOT(slotClearEvent()));
    QObject::connect((m_engine)->rootObjects().first(),SIGNAL(check_input_interver(QString)),this,SLOT(onCheckInputData(QString)));
    qDebug("Start MainWindow::initData");
}

void MainWindow::onApplicationStateChanged(Qt::ApplicationState state)
{
    qDebug() << "void LAACApplication::onApplicationStateChanged(Qt::ApplicationState state =" << state << ")";
}

void MainWindow::set_suggest(QStringList lsT)
{
    qDebug("MainWindow::set_suggest");
        m_textsugest = lsT ;
    emit disStrChanged();
}

void MainWindow::set_result(QStringList str)
{
    qDebug("MainWindow::set_result");
        m_textresult = str ;
    emit disresultChanged();
}
void MainWindow::set_InputText(QString str1){
        m_settextinput=str1;
    emit texttSearchChanged();
}

void MainWindow::set_visble_List_Text(bool str1){
        m_setvisible_list_text=str1;
    emit set_visble_List_Text_Changed();
}

void MainWindow::set_Clear_All_Input_Text(bool str1){
    //if(str1!=m_setvisible_list_text)
        m_clear_input_text=str1;
    emit set_Clear_All_Input_Changed();
}

void MainWindow::slotHandlerEvent(QString data)
{
    qDebug("MainWindow::slotHandlerEvent");
    if(msettypedata){
            mdatasave=data;
           startSuggest(data);
           msetsearchdata=true;
    }
}

void MainWindow::onCheckInputData(QString strg)
{
    qDebug("MainWindow::slotHandlerEvent");
    if(msettypedata){
        mdatasave=strg;
        startSuggest(strg);
    }

}

void MainWindow::slotClearEvent()
{
    qDebug("MainWindow::slotClearEvent");
    m_timer->start();
    mdatasave="";
    msettypedata=false;
    set_InputText(mdatasave);
    set_Clear_All_Input_Text(true);


}
void MainWindow::slotTextSuggestEvent(QString strg)
{
    qDebug()<<"MainWindow::slotTextSuggestEvent "<<strg;
    if(msettypedata){
        mdatasave=strg;
        startSuggest(strg);
    }
    else
    {
        set_visble_List_Text(false);
        if(!m_clear_input_text){
            for(int i=0;i<mpoiner.count();i++)
                qDebug()<<mpoiner[i];
            set_result(mpoiner);
        }
    }
}

void MainWindow::slotTextChoiceInListData(int point){
    QStringList dataevent;
    QString strg=m_newcity[point];
    m_timer->start();
    qDebug()<<"MainWindow::slotTextChoiceInListData >>"<<point<<">>>data is:"<<strg ;
    mdatasave=strg;
    QString str_tmp = m_newlist[point];
    savetodatabase(str_tmp);
    QStringList infolist = str_tmp.split(";");
    QString datasubget=" City:" + infolist[0] + "\n";
    dataevent<<datasubget;
    datasubget="Population : "+ infolist[1] + "\n";
    dataevent<<datasubget;
    datasubget="Area : "+ infolist[2] + "\n";
    dataevent<<datasubget;
    datasubget="Density : "+ infolist[3] + "\n";
    dataevent<<datasubget;
    datasubget="Founded : "+ infolist[4] + "\n";
    dataevent<<datasubget;
    qDebug()<<dataevent;
    mpoiner=dataevent;
    msettypedata=false;
    set_InputText(strg);
    set_visble_List_Text(false);
    if(!m_clear_input_text){
        set_result(mpoiner);
    }
    msetsearchdata=false;

}
void MainWindow::onTimeout(){
    qDebug()<<"MainWindow::onTimeout ";
    msettypedata=true;
    m_timer->stop();
    set_Clear_All_Input_Text(false);
}



//---------------------------------------------------------
QStringList MainWindow::searchSQLDataContainData(QString data)
{
    QStringList textmaplist;
    QStringList textcitylist;
     qDebug("Start searchSQLDataContainData");
    if (!db.open())
    {
        db.close();
        qDebug("get data SQL failse");
    }
    else
    {
        qDebug("reloadAllSQL OK");
        QSqlQuery query;
        QString q = "SELECT * FROM cityinfo WHERE City LIKE '%"+ data
                + "%' ORDER BY Priority+1/(20+INSTR(City,'"+data +"')) DESC;";
        query.exec(q);
        while (query.next())
        {
            QString pass1 = query.value(0).toString();
            QString pass2 = query.value(1).toString();
            QString pass3 = query.value(2).toString();
            QString pass4 = query.value(3).toString();
            QString pass5 = query.value(4).toString();
            QString pass6 = query.value(5).toString();
            QString dataexert=pass1+";"+pass2+";"+pass3+";"
                    +pass4+";"+pass5+";"+pass6;
            textcitylist<<pass1;
            textmaplist<<dataexert;
            qDebug()<<"data TTL :"<<dataexert;
        }
    }
    m_newcity=textcitylist;
    return textmaplist;
}




QStringList MainWindow::listAllDataContain(QStringList data,QString datacompaire){
    QStringList datasecond=data;
    QStringList alldatata;
    int i=0;
    qDebug("searchDataContainLV2to ");
    int numbercheck[datasecond.count()][2];
    QStringList datasecondnew;
    for(i=0;i<datasecond.count();i++){
        QString str_temp = datasecond[i];
        QStringList list_tmp = str_temp.split(";");
        numbercheck[i][0]=i;
        QString dataswtq0=list_tmp[0];
        datasecondnew<<dataswtq0;
        QString dataswtq1=list_tmp[1];
        numbercheck[i][1]=(int)(dataswtq1.toInt()+20/(1+dataswtq0.indexOf(datacompaire,0,Qt::CaseInsensitive)));
    }
    int father,child;
    for(i=0;i<datasecond.count();i++){
        for(int j=i+1;j<datasecond.count();j++){
            if(numbercheck[i][1]<numbercheck[j][1]){
                father=numbercheck[i][0];
                child=numbercheck[i][1];
                numbercheck[i][0]=numbercheck[j][0];
                numbercheck[i][1]=numbercheck[j][1];
                numbercheck[j][0]=father;
                numbercheck[j][1]=child;
            }
        }
    }
    for(i=0;i<datasecond.count();i++){
        QString str_temp = datasecondnew[numbercheck[i][0]];
        alldatata <<str_temp;
    }
    return alldatata;
}
void MainWindow::startSuggest(QString pattern)
{
    qDebug("Start MainWindow::startSuggest");
    if(pattern.length()>0){
        set_visble_List_Text(true);
        m_newlist=searchSQLDataContainData(pattern);
        set_suggest(m_newcity);
    }
    else
    {
        set_visble_List_Text(false);
    }
    qDebug("End MainWindow::startSuggest");
}

void MainWindow::savetodatabase(QString input){
    if (!db.open())
    {
        db.close();
        qDebug("reloadAllSQL failse");
    }
    else
    {
        bool existing=false;
        QString numberset;
        QString pcity;
        QStringList list_tmp = input.split(";");
        if(list_tmp.count()>0){
            QString str;
            pcity=list_tmp[0];
            QString dats=list_tmp[5];
            str.setNum(dats.toInt()+1);
            numberset=str;
            existing=true;
        }

        if(existing){
            qDebug("data has been up date");
            QSqlQuery query;
            QString q = "UPDATE cityinfo SET Priority="+numberset +" WHERE City='"+pcity+"';";
            if(query.exec(q)){
                qDebug("data has been up date oK~~~~~~~~~~~~~~~~~");
            }
            else
            {
                qDebug("data has been up date false~~~~~~~~~~~~~~~~~");
            }

        }

    }
    db.close();
}

void MainWindow::chooseSuggest()
{
    qDebug("Start MainWindow::chooseSuggest");

    qDebug("End MainWindow::chooseSuggest");
}
