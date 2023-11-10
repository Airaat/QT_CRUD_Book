#include "mainwindow.h"
#include "ui_mainwindow.h"

void applyHeaderStyles(QTableWidget *tableWidget){
    QColor colorBlack("#242A38");
    QColor colorDefault("#2F3542");
    QBrush brushBlack(colorBlack);
    QBrush brushDefault(colorDefault);

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
                } else {
                    item->setBackground(brushDefault); // Стилизация четных строк
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

    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);

    QMenu *fileMenu = menubar->addMenu("File");

    QAction *saveAct = new QAction("Save", this);
    QAction *openAct = new QAction("Open", this);
    QAction *exitAct = new QAction("Exit", this);

    fileMenu->addAction(saveAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    QMenu *toolMenu = menubar->addMenu("Edit");

    act_add = new QAction("Add", this);
    connect(act_add, &QAction::triggered, this, &MainWindow::addEntry);
    connect(ui->btn_add, &QPushButton::clicked, this, &MainWindow::addEntry);

    act_edit = new QAction("Edit", this);
    act_edit->setEnabled(false);
    connect(act_edit, &QAction::triggered, this, &MainWindow::editEntry);
    connect(ui->btn_edit, &QPushButton::clicked, this, &MainWindow::editEntry);

    act_remove = new QAction("Delete", this);
    act_remove->setEnabled(false);
    connect(act_remove, &QAction::triggered, this, &MainWindow::removeEntry);
    connect(ui->btn_remove, &QPushButton::clicked, this, &MainWindow::removeEntry);

    toolMenu->addAction(act_add);
    toolMenu->addAction(act_edit);
    toolMenu->addSeparator();
    toolMenu->addAction(act_remove);

    editform = new EditForm;
    connect(editform, &EditForm::addNewRecordRequested, this, &MainWindow::addNewRecord);
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::onTableSelectionChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Изменение состояния функциональных кнопок
void MainWindow::onTableSelectionChanged() {
    if (ui->tableWidget->selectedItems().isEmpty()) {
        ui->btn_edit->setEnabled(false);
        ui->btn_remove->setEnabled(false);
        act_edit->setEnabled(false);
        act_remove->setEnabled(false);
    } else {
        ui->btn_edit->setEnabled(true);
        ui->btn_remove->setEnabled(true);
        act_edit->setEnabled(true);
        act_remove->setEnabled(true);
    }
}

void MainWindow::addEntry()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    editform->setIndex(row);
    editform->show();
}

void MainWindow::editEntry()
{
    if (ui->tableWidget->selectedItems().isEmpty()) {
        return; // Ничего не делаем, если ни одна строка не выбрана.
    }

    // Получить выбранные элементы из таблицы.
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();

    if (selectedItems.count() < 7) {
        return; // Убедиться, что выбраны все элементы строки.
    }

    int row = selectedItems.at(0)->row();

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
    editform->setIndex(row);
    editform->show();

}

void MainWindow::removeEntry()
{
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow >= 0)
    {
        ui->tableWidget->removeRow(selectedRow);
        applyHeaderStyles(ui->tableWidget);
    }
}

void MainWindow::addNewRecord(const Car &car, int row)
{
    QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(car.getModel()));
    QTableWidgetItem *yearItem = new QTableWidgetItem(QString::number(car.getYear()));
    QTableWidgetItem *mileageItem = new QTableWidgetItem(QString::number(car.getMileage()) + " KM");
    QTableWidgetItem *bodyItem = new QTableWidgetItem(QString::fromStdString(car.getBody()));
    QTableWidgetItem *gearboxItem = new QTableWidgetItem(QString::fromStdString(car.getGearbox()));
    QTableWidgetItem *driveItem = new QTableWidgetItem(QString::fromStdString(car.getDrive()));
    QTableWidgetItem *positionItem = new QTableWidgetItem(QString::fromStdString((car.getPosition()) ? "R" : "L"));

    ui->tableWidget->setItem(row, 0, nameItem);
    ui->tableWidget->setItem(row, 1, yearItem);
    ui->tableWidget->setItem(row, 2, mileageItem);
    ui->tableWidget->setItem(row, 3, bodyItem);
    ui->tableWidget->setItem(row, 4, gearboxItem);
    ui->tableWidget->setItem(row, 5, driveItem);
    ui->tableWidget->setItem(row, 6, positionItem);

    applyHeaderStyles(ui->tableWidget);
}
