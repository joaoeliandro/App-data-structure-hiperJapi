#ifndef GERENTE_H
#define GERENTE_H

#include <QDialog>

namespace Ui {
class gerente;
}

class gerente : public QDialog
{
    Q_OBJECT

public:
    explicit gerente(QWidget *parent = 0);

    ~gerente();

private slots:
    void on_btn_ok_clicked();

private:
    Ui::gerente *ui;
};

#endif // GERENTE_H
