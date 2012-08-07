#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateComponents();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *e)
{
    ui->graphicsView->resize(MainWindow::width()/*-20*/, MainWindow::height()-105);
}

void MainWindow::on_pushButton_Insert_clicked()
{
    ui->graphicsView->insertNode(ui->spinBox->value());
//    ui->spinBox->clear();
}

void MainWindow::on_pushButton_ExtractMin_clicked()
{
    ui->graphicsView->extractMin();
    updateComponents();
}

void MainWindow::on_pushButton_Delete_clicked()
{
    ui->graphicsView->deleteNode();
    updateComponents();
}

void MainWindow::on_pushButton_DecreaseKey_clicked()
{
    ui->graphicsView->decreaseKey(ui->spinBox->value());
//    ui->spinBox->clear();
    updateComponents();
}

void MainWindow::on_pushButton_SwitchHeap_clicked()
{
    ui->graphicsView->switchHeap();
    updateComponents();
}

void MainWindow::on_pushButton_Union_clicked()
{
//    ui->graphicsView->unionOperation();
    updateComponents();
}

void MainWindow::on_pushButton_NextStep_clicked()
{
    ui->graphicsView->nextStep();
    updateComponents();
}

void MainWindow::updateComponents()
{
    bool enabled = !ui->graphicsView->blockComponents();
    ui->pushButton_Clear->setEnabled(enabled);
    ui->pushButton_DecreaseKey->setEnabled(enabled);
    ui->pushButton_Delete->setEnabled(enabled);
    ui->pushButton_ExtractMin->setEnabled(enabled);
    ui->pushButton_Insert->setEnabled(enabled);
    ui->pushButton_NextStep->setEnabled(!enabled);
    ui->pushButton_SwitchHeap->setEnabled(enabled);
    ui->pushButton_Union->setEnabled(enabled);
    ui->pushButton_ClearAll->setEnabled(enabled);
    ui->menuFile->setEnabled(enabled);
}

void MainWindow::on_actionSave_Selected_Heap_triggered()
{
    ui->graphicsView->ExportHeap();
}

void MainWindow::on_actionLoad_To_selected_Heap_triggered()
{
//    ui->graphicsView->ImportHeap();
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->graphicsView->clearSelected();
}

void MainWindow::on_pushButton_ClearAll_clicked()
{
    ui->graphicsView->reset(); // reset = clearAll
}
