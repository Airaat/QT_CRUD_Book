#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QMenuBar>
#include <editform.h>
#include <filterform.h>

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
    void setupHeaderStyles(QTableWidget *tableWidget);
    void setupMenuBar(QMenuBar *menubar);
    ~MainWindow();

private slots:
    void addEntry();
    void editEntry();
    void removeEntry();
    void filterEntry();

    void readFromFile();
    void writeToFile();
    void onTableSelectionChanged();

private:
    Ui::MainWindow *ui;
    EditForm *editform;
    FilterForm *filterform;

    QAction *act_add;
    QAction *act_edit;
    QAction *act_remove;

public slots:
    void addNewRecord(const Car &obj, int indexRow);
    void filterRecords(const size_t min, const size_t max);
};
#endif // MAINWINDOW_H
