#include "mainwindow.h"
#include "ui_mainwindow.h"

void applyHeaderStyles(QTableWidget *tableWidget){
    QColor colorBlack("#242A38");
    QBrush brushBlack(colorBlack);

    // Выделение всей строки при нажатии на ячейку
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            if (item) {
                if (col != 0 && col != 3){
                    item->setTextAlignment(Qt::AlignCenter); // Размещение текста по центру
                }
                if (row % 2 == 0){
                    item->setBackground(brushBlack); // Стилизация нечетных строк
                }
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Read-only mode для ячеек
            }
        }
    }
    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch); // Адаптивный дизайн для первого столбца
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    applyHeaderStyles(ui->tableWidget);

    editform = new EditForm;
    connect(editform, &EditForm::addNewRecordRequested, this, &MainWindow::addNewRecord);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    editform->show();
}

void MainWindow::addNewRecord(const Car &car)
{
    int row = ui->tableWidget->rowCount();

    QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(car.getModel()));
    QTableWidgetItem *yearItem = new QTableWidgetItem(QString::number(car.getYear()));
    QTableWidgetItem *mileageItem = new QTableWidgetItem(QString::number(car.getMileage()) + " KM");
    QTableWidgetItem *bodyItem = new QTableWidgetItem(QString::fromStdString(car.getBody()));
    QTableWidgetItem *gearboxItem = new QTableWidgetItem(QString::fromStdString(car.getGearbox()));
    QTableWidgetItem *driveItem = new QTableWidgetItem(QString::fromStdString(car.getDrive()));
    QTableWidgetItem *positionItem = new QTableWidgetItem(QString::fromStdString((car.getPosition()) ? "R" : "L"));

    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, nameItem);
    ui->tableWidget->setItem(row, 1, yearItem);
    ui->tableWidget->setItem(row, 2, mileageItem);
    ui->tableWidget->setItem(row, 3, bodyItem);
    ui->tableWidget->setItem(row, 4, gearboxItem);
    ui->tableWidget->setItem(row, 5, driveItem);
    ui->tableWidget->setItem(row, 6, positionItem);

    applyHeaderStyles(ui->tableWidget);
}

void MainWindow::on_editButton_clicked()
{
    editform->show();
}
