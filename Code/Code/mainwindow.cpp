#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gerente.h"
#include "feedback.h"
#include <iostream>
#include <QMessageBox>

int i = 0; //variavel de controle de linhas da tabela

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(geometry().width(), geometry().height());

    setLista(lista); //função no construtor settando/criando uma lista
}

MainWindow::~MainWindow()
{
    delete ui;
}

//função de buscar por codigo na lista passada retornando os dados
int MainWindow::buscar(int codBuscar, EstruturaLista &lista)
{
    int i, cod = -1; // variavel de controle e variavel para retorna os dados encontrado

    for(i = lista.inicio; i < lista.fim; i++)
    {
        if(lista.dados[i].codigo == codBuscar) cod = lista.dados[i].codigo; // settando os dados encontrados por codigo
    }
    return cod;
}

void MainWindow::on_btn_Buscar_clicked()
{
    int maiorNum = ui->tbl_produto->rowCount(); //guardando na variavel o final da lista na tabela
    int codBuscar = 0; // variavel para armazenar o codigo para busca

    if(ui->line_Codigo->text() == NULL) QMessageBox::warning(this, "Error", "Digite um código para buscar");

    else
    {
        codBuscar = ui->line_Codigo->text().toInt();

        // verificação se o codigo está na lista e tabela
        if(codBuscar > 0 && codBuscar <= maiorNum)
        {
            for(int lin = 0; lin < ui->tbl_produto->rowCount(); ++lin)
            {
                int cod = ui->tbl_produto->item(lin, 0)->text().toInt();

                if(cod == buscar(codBuscar, lista))
                {
                    ui->tbl_produto->selectRow(lin);
                }
            }
        }
        else
        {
            QMessageBox::information(this, "Error 404", "Não existe este código");
        }
        ui->line_Codigo->clear();
        ui->line_Qtn->clear();
    }
}

// função criando a lista iniciando e terminando na primeira linha na linha 0
void MainWindow::setLista(EstruturaLista &lista)
{
    lista.inicio = 0;
    lista.fim = 0;
}

// função inserindo os dados passados por valor e colocando na lista referenciada
void MainWindow::inserirLista(EstruturaColuna aux, EstruturaLista &lista)
{
    lista.dados[lista.fim] = aux;   //na estrutura lista coloca a copia dos dados no espaços da lista posicionados no final da lista
    lista.fim++;                    //adciona uma nova linha a lista
}

void MainWindow::on_btn_Adcionar_clicked()
{
    if(ui->line_Codigo->text() == NULL && ui->line_Qtn->text() == NULL){
        QMessageBox::warning(this, "Error", "Preencha com um código e a quantidade do produto");
    }else{

        aux.codigo = ui->line_Codigo->text().toInt(); //colocando na variavel codigo da estrutura dados o codigo digitado
        aux.qtn = ui->line_Qtn->text().toInt();       //colocando na variavel qtn da estrutura dados a quantidade digitado

        inserirLista(aux, lista);                     //função inserindo a lista passando os dados e a lista que será usada

        ui->tbl_produto->insertRow(i);                // inserindo uma linha na tabela
        //inserindo na coluna codigo o codigo da lista da linha i
        ui->tbl_produto->setItem(i, codigo, new QTableWidgetItem(QString::number(lista.dados[i].codigo)));
        //inserindo na coluna quant a qtn da lista da linha i
        ui->tbl_produto->setItem(i, quant, new QTableWidgetItem(QString::number(lista.dados[i].qtn)));
        //variavel de controle para pular a proxima linha
        i++;

        ui->line_Codigo->clear();
        ui->line_Qtn->clear();
    }
}

// função que apaga os dados encontrados por codigo
void MainWindow::apagarDaLista(int cod, EstruturaLista &lista)
{
    int i; // variavel de controle

    //busca dos dados para serem apagados por codigo
    for(i = lista.inicio; i < lista.fim; i++)
    {
        if(cod == lista.dados[i].codigo)
        {
            // loop para apagar os dados selecionados
            do
            {
                lista.dados[i] = lista.dados[i+1]; // coloca no dado selecionado o proximo da fila
                i++; // soma mais 1 para pular a posição pra o proximo dado da fila
            }
            while(i < lista.fim); // enquanto o proximo não for o nulo(final da lista que estará vazia)
        }
    }
}

// Função que apaga da tabela e da lista
void MainWindow::on_btn_Apagar_clicked()
{
    int linha = ui->tbl_produto->currentRow(); // linha selecionada na tabela

    // passa como paramentro o valor da linha selecionada na coluna 0 (coluna codigo) e a lista para ser alterada
    apagarDaLista(ui->tbl_produto->item(linha, 0)->text().toInt(), lista);

    // remove da tabela
    ui->tbl_produto->removeRow(ui->tbl_produto->currentRow());
}

// Função que altera os dados da lista
void MainWindow::trocar(int cod, int codAlt, int qtn, EstruturaLista &lista)
{
    // verficação por codigo
    for(int i = lista.inicio; i < lista.fim; i++)
    {
        if(cod == lista.dados[i].codigo)
        {
            lista.dados[i].codigo = codAlt; // Na coluna codigo da lista recebe o codigo novo passado por parametro
            lista.dados[i].qtn = qtn; // Na coluna qtn da lista a qtn nova passada por parametro
        }
    }
}

// Função que altera na tabela e na lista
void MainWindow::on_btn_Trocar_clicked()
{
    if(!ui->tbl_produto->currentItem())
    {
        QMessageBox::warning(this, "Error", "Selecione algum produto para trocar");
    }
    else if(ui->line_Qtn->text() == NULL && ui->line_Codigo->text() == NULL)
    {
        QMessageBox::warning(this, "Error", "Digite um código e quantidade para troca");
    }
    else
    {
        int linha = ui->tbl_produto->currentRow(); // linha selecionada na tabela
        int codLinha = ui->tbl_produto->item(linha, 0)->text().toInt(); // valor da linha selecionada na coluna 0 (coluna codigo)
        int cod = ui->line_Codigo->text().toInt(), qtn = ui->line_Qtn->text().toInt(); //codigo e qtn digitados nos linetext

        // chamada da função para alterar passando os paramentros
        trocar(codLinha, cod, qtn, lista);

        //alterando na tabela os novos valores
        ui->tbl_produto->setItem(linha, codigo, new QTableWidgetItem(ui->line_Codigo->text()));
        ui->tbl_produto->setItem(linha, quant, new QTableWidgetItem(ui->line_Qtn->text()));

        ui->line_Codigo->clear();
        ui->line_Qtn->clear();
    }
}

void MainWindow::on_btn_Gerente_clicked()
{
    gerente geren;
    geren.setModal(true);
    geren.exec();
}

void MainWindow::on_btn_FeedBack_clicked()
{
    feedback fb;
    fb.setModal(true);
    fb.exec();
}
