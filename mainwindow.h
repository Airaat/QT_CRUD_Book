#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <editform.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class EditForm;
class Car;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_removeButton_clicked();

    void onTableSelectionChanged();

private:
    Ui::MainWindow *ui;
    EditForm *editform;

public slots:
    void addNewRecord(const Car &obj, int indexRow);
};
#endif // MAINWINDOW_H
