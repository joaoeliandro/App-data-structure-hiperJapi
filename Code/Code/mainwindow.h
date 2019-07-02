#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define tamanho 1000    // quantidade de dados(linhas) que pode ser inserido na lista

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
    void on_btn_Buscar_clicked();

    void on_btn_Adcionar_clicked();

    void on_btn_Apagar_clicked();

    void on_btn_Trocar_clicked();

    void on_btn_Gerente_clicked();

    void on_btn_FeedBack_clicked();

private:
    Ui::MainWindow *ui;

    //enumerador para setar as colunas de codigo e quantidade
    enum colunas{
        codigo, quant
    };

    //variavel tipada para indicar um apontador para inicio e fim de uma lista
    typedef int apontador;

    //estrutura para setar as colunas da tabela coluna 0 e coluna 1
    struct
    {
        int codigo; // coluna 0 para os codigos
        int qtn;    // coluna 1 para as quantidades
    }typedef EstruturaColuna;

    //estrutura para setar linhas para a tabela com linhas de tamanho 1000
    struct
    {
        EstruturaColuna dados[tamanho]; // instancia das colunas para receber as linhas com tamanho 1000

        apontador inicio;               // instancia de um apontador para o inicio da lista
        apontador fim;                  // instancia de um apontador para o fim da lista

    }typedef EstruturaLista;

    EstruturaColuna aux;                // instancia de uma variavel do tipo EstruturaColuna para receber os dados digitados
    EstruturaLista lista;               // instancia de uma variavel do tipo EstruturaLista para receber os dados das colunas e colocar nas linhas da lista

    void setLista(EstruturaLista &lista); // função para criar uma lista

    void inserirLista(EstruturaColuna aux, EstruturaLista &lista);      // função para inserir os dados na lista

    int buscar(int codBuscar, EstruturaLista &lista);                   // função para busca por codigo na lista

    void trocar(int cod, int codAlt, int qtn, EstruturaLista &lista);   // função de alterar dados na lista buscando por codigo

    void apagarDaLista(int cod, EstruturaLista &lista);                 // função de apagar dados da lista por codigo
};

#endif // MAINWINDOW_H
