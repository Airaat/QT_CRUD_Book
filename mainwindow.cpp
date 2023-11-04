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
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::onTableSelectionChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTableSelectionChanged() {
    if (ui->tableWidget->selectedItems().isEmpty()) {
        ui->editButton->setEnabled(false); // Сделать кнопку "Edit" недоступной, если ни одна строка не выбрана.
        ui->removeButton->setEnabled(false);
    } else {
        ui->editButton->setEnabled(true); // Сделать кнопку "Edit" доступной, если строка выбрана.
        ui->removeButton->setEnabled(true);
    }
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
    if (ui->tableWidget->selectedItems().isEmpty()) {
        return; // Ничего не делаем, если ни одна строка не выбрана.
    }

    // Получить выбранные элементы из таблицы.
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();

    if (selectedItems.count() < 7) {
        return; // Убедиться, что выбраны все элементы строки.
    }

    // Получить данные из выбранной строки.
    QString name = selectedItems.at(0)->text();
    QString year = selectedItems.at(1)->text();
    QString mileage = selectedItems.at(2)->text();
    mileage = mileage.mid(0,mileage.length()-3); // Отрезаем КМ
    QString body = selectedItems.at(3)->text();
    QString gearbox = selectedItems.at(4)->text();
    QString drive = selectedItems.at(5)->text();
    QString position = selectedItems.at(6)->text();

    // Создать и показать окно EditForm и передать в него данные.
    editform->setData(name,year,mileage,body,gearbox,drive,position);
    editform->show();

}

void MainWindow::on_removeButton_clicked()
{
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow >= 0)
    {
        ui->tableWidget->removeRow(selectedRow);
    }
}

