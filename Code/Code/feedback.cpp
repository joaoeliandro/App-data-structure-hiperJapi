#include "feedback.h"
#include "ui_feedback.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

feedback::feedback(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::feedback)
{
    ui->setupUi(this);
    setFixedSize(geometry().width(), geometry().height());
    ultimosfeeds();
}

feedback::~feedback()
{
    delete ui;
}

void feedback::on_btn_enviar_clicked()
{
    if(ui->txt_fb->text() != NULL){
        ultimoFb[4] = ui->txt_fb->text();
        ui->txt_fb->clear();
    }else{
        QMessageBox::information(this, NULL, "Digite um feedBack para nós");
    }
}

void feedback::on_btn_UltimoFeed_clicked()
{
    ui->txt_UltimoFeed->clear();
    if(i > 4)
        i = 0;
    else{
        ui->txt_UltimoFeed->setText(ultimoFb[i]);
        i++;
    }
}

void feedback::ultimosfeeds(){
    ultimoFb[0] = "Nossa, maravilhoso!";
    ultimoFb[1] = "Achei bem prático";
    ultimoFb[2] = "Muito bom!";
    ultimoFb[3] = "Very good program!";
    ultimoFb[4] = "Vale 10!!!";
}
