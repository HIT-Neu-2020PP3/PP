#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QDebug>
#include <QTableView>
#include <QString>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    bool btnc1=0;
    bool btnc2=0;
    bool btnc3=0;

    void putin(QTableView *view_in,QTableView *patientView_in,QTableView *devicePatientView_in );
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
    QTableView *view;
    QTableView *patientView;
    QTableView *devicePatientView ;
    void drawwave();

};

#endif // WIDGET_H
