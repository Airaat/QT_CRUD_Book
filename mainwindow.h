#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMenuBar>
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
    void setupHeaderStyles(QTableWidget *tableWidget);
    void setupMenuBar(QMenuBar *menubar);
    ~MainWindow();

private slots:
    void addEntry();
    void editEntry();
    void removeEntry();

    void onTableSelectionChanged();

private:
    Ui::MainWindow *ui;
    EditForm *editform;

    QAction *act_add;
    QAction *act_edit;
    QAction *act_remove;

public slots:
    void addNewRecord(const Car &obj, int indexRow);
};
#endif // MAINWINDOW_H
