#include "gerente.h"
#include "ui_gerente.h"

gerente::gerente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gerente)
{
    ui->setupUi(this);
    setFixedSize(geometry().width(), geometry().height());
}

gerente::~gerente()
{
    delete ui;

}

void gerente::on_btn_ok_clicked()
{
    this->close();
}
