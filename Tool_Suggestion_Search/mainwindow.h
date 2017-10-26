#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QQmlContext>
#include<QObject>
#include <QTimer>
#include <QStringList>
#include <QString>
#include <iostream>
#include <QtCore>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QtSql>
#include <QSqlDatabase>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QSqlRelationalDelegate>

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList getSuggest READ getSuggest WRITE set_suggest NOTIFY disStrChanged)
     Q_PROPERTY(QStringList getResult READ getResult WRITE set_result NOTIFY disresultChanged)
    Q_PROPERTY(QString setTextSearch READ setTextSearch WRITE set_InputText NOTIFY texttSearchChanged)
    Q_PROPERTY(bool setVisible_List_Text READ setVisible_List_Text WRITE set_visble_List_Text NOTIFY set_visble_List_Text_Changed)
    Q_PROPERTY(bool setClear_Input_Text READ setClear_Input_Text WRITE set_Clear_All_Input_Text NOTIFY set_Clear_All_Input_Changed)

private:
    QStringList m_result ;
    QString m_settextinput;
    QStringList m_textresult;
    QStringList m_textsugest;
    bool m_setvisible_list_text;
    bool m_clear_input_text;
    QQmlApplicationEngine* m_engine; //con tro chi den QML
public:
    //explicit demo(QObject *parent=0); //
    //~ssdemo();
    MainWindow();
    void reloadAllSQL();
    void initData(QQmlApplicationEngine* engine);
    QStringList getSuggest() const { return m_textsugest ; }
    QStringList getResult() const { return m_textresult ; }
    QString setTextSearch() const { return m_settextinput ; }
    bool setVisible_List_Text() const { return m_setvisible_list_text ; }
    bool setClear_Input_Text() const { return m_clear_input_text ; }

    void set_suggest(QStringList lsT);
    void set_result(QStringList str);
    void set_InputText(QString str1);
    void set_visble_List_Text(bool str1);
    void set_Clear_All_Input_Text(bool str1);
   // void set_setTextSearch

    QStringList searchSQLDataContainData(QString data);
    QStringList listAllDataContain(QStringList data,QString datacompaire);
    QStringList sortDataNumberSecsion(QStringList data);
    void savetodatabase(QString input);
    void startSuggest(QString input);
    void chooseSuggest();

signals:
    void disStrChanged();
    void disresultChanged();
    void texttSearchChanged();
    void setInputText();
    void set_visble_List_Text_Changed();
    void set_Clear_All_Input_Changed();
public slots:
    void onApplicationStateChanged(Qt::ApplicationState state);
    void slotHandlerEvent(QString data);
    void slotClearEvent();
    void slotTextSuggestEvent(QString strg);
    //void slotTextSTA(QString strg);
    void slotTextChoiceInListData(int point);
    void onTimeout();
    void onCheckInputData(QString strg);

private:
    QTimer *m_timer;
    QStringList m_newlist;
    QStringList m_newcity;

    QStringList mpoiner;
    QString mdatasave;
    QString mdatadelete="";
    bool notfound;
    bool msettypedata=true;
    bool msetsearchdata=false;
    QSqlDatabase db;
    int foundfist=0;
};

#endif // MAINWINDOW_H
