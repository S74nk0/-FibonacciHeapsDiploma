#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *e);

private slots:
    void on_pushButton_Insert_clicked();

    void on_pushButton_ExtractMin_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_DecreaseKey_clicked();

    void on_pushButton_SwitchHeap_clicked();

    void on_pushButton_Union_clicked();

    void on_pushButton_NextStep_clicked();

    void on_actionSave_Selected_Heap_triggered();

    void on_actionLoad_To_selected_Heap_triggered();

    void on_pushButton_Clear_clicked();

    void on_pushButton_ClearAll_clicked();

private:
    Ui::MainWindow *ui;
    void updateComponents();
};

#endif // MAINWINDOW_H
