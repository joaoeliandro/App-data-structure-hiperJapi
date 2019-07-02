#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QDialog>

namespace Ui {
class feedback;
}

class feedback : public QDialog
{
    Q_OBJECT

public:
    explicit feedback(QWidget *parent = 0);
    ~feedback();

private slots:
    void on_btn_enviar_clicked();

    void on_btn_UltimoFeed_clicked();

    void ultimosfeeds();

private:
    Ui::feedback *ui;

    QString ultimoFb[5];
    int i = 0;
};

#endif // FEEDBACK_H
