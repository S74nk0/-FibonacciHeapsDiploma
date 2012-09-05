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
    Q_UNUSED(e);
    ui->fibHeapView->resize(MainWindow::width()/*-20*/, MainWindow::height()-105);
}

void MainWindow::on_pushButton_Insert_clicked()
{
    ui->fibHeapView->insertNode(ui->spinBox->value());
}

void MainWindow::on_pushButton_ExtractMin_clicked()
{
    ui->fibHeapView->extractMin();
    updateComponents();
}

void MainWindow::on_pushButton_Delete_clicked()
{
    ui->fibHeapView->deleteNode();
    updateComponents();
}

void MainWindow::on_pushButton_DecreaseKey_clicked()
{
    ui->fibHeapView->decreaseKey(ui->spinBox->value());
    updateComponents();
}

void MainWindow::on_pushButton_SwitchHeap_clicked()
{
    ui->fibHeapView->switchHeap();
    updateComponents();
}

void MainWindow::on_pushButton_Union_clicked()
{
    ui->fibHeapView->unionOperation();
    updateComponents();
}

void MainWindow::on_pushButton_NextStep_clicked()
{
    ui->fibHeapView->nextStep();
    updateComponents();
}

void MainWindow::updateComponents()
{
    bool enabled = !ui->fibHeapView->blockComponents();
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
    ui->fibHeapView->ExportHeap();
}

void MainWindow::on_actionLoad_To_selected_Heap_triggered()
{
    ui->fibHeapView->ImportHeap();
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->fibHeapView->clearSelected();
}

void MainWindow::on_pushButton_ClearAll_clicked()
{
    ui->fibHeapView->reset(); // reset = clearAll
}
