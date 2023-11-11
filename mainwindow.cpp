#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupHeaderStyles(ui->tableWidget);

    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);
    setupMenuBar(menubar);

    editform = new EditForm;
    filterform = new FilterForm;
    connect(editform, &EditForm::addNewRecordRequested, this, &MainWindow::addNewRecord);
    connect(filterform, &FilterForm::filterRecordsRequested, this, &MainWindow::filterRecords);
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::onTableSelectionChanged);
    connect(ui->btn_filter, &QPushButton::clicked, this, &MainWindow::filterEntry);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addEntry()
{
    int row = ui->tableWidget->rowCount();
    editform->setIndex(row);
    editform->show();
}

void MainWindow::filterEntry(){
    filterform->show();
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
        setupHeaderStyles(ui->tableWidget);
    }
}

void MainWindow::addNewRecord(const Car &car, int row)
{
    if(row == ui->tableWidget->rowCount()){
        //Если индекс == кол-ву строк -> добавляем запись
        ui->tableWidget->insertRow(row);
//        car.addCar(car);
    }

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

    setupHeaderStyles(ui->tableWidget);
}
//Можно добавить flag, который будет поднят если нашлась хотя бы одна запись
//и тогда выполняется второй цикл фор иначе QMessageBox (Совпадений нет)
void MainWindow::filterRecords(const size_t min, const size_t max){
    QList<Car> filteredCars;
    for(int row = 0; row < ui->tableWidget->rowCount(); row++){
        QString mileageText = ui->tableWidget->item(row, 2)->text();
        size_t mileage = mileageText.mid(0,mileageText.length()-3).toUInt();
        if(min <= mileage && mileage <= max){
            std::string name = ui->tableWidget->item(row, 0)->text().toStdString();
            size_t year = ui->tableWidget->item(row, 1)->text().toUInt();
            std::string body = ui->tableWidget->item(row, 3)->text().toStdString();
            std::string gearbox = ui->tableWidget->item(row, 4)->text().toStdString();
            std::string drive = ui->tableWidget->item(row, 5)->text().toStdString();
            bool position = (ui->tableWidget->item(row, 6)->text().toUpper() == "R") ? true : false;
            Car car(name, year, mileage, body, gearbox, drive, position);
            filteredCars.append(car);
        }
    }
    int row = 0;
    ui->tableWidget->setRowCount(filteredCars.size());
    for (const auto &car: std::as_const(filteredCars)){
        addNewRecord(car, row++);
    }
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

void MainWindow::readFromFile(){
    // Открываем диалоговое окно для выбора файла
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", "", "Text Files (*.dat)");
    QFile file(filePath);
    if (!filePath.isEmpty()) {
        qDebug() << "Выбран файл для открытия: " << filePath;

    } else {
        qDebug() << "Отменено пользователем.";
    }

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Ошибка при открытии файла"),file.errorString());
        return;
    }

    QList<Car> cars;
    QDataStream in(&file);
    in >> cars;

    if (cars.isEmpty()) {
        QMessageBox::information(this, tr("Нет данных в файле"),
                                 tr("Файл пустой."));
    } else {
        ui->tableWidget->setRowCount(cars.size());
        int row = 0;
        for (const auto &car: std::as_const(cars)){
            addNewRecord(car, row++);
        }
    }
}

void MainWindow::writeToFile(){
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.dat)");
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Ошибка при открытии файла"), file.errorString());
        return;
    }

    QDataStream out(&file);
    QList<Car> cars;

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QString name = ui->tableWidget->item(row, 0)->text();
        QString year = ui->tableWidget->item(row, 1)->text();
        QString mileage = ui->tableWidget->item(row, 2)->text();
        mileage = mileage.mid(0,mileage.length()-3);
        QString body = ui->tableWidget->item(row, 3)->text();
        QString gearbox = ui->tableWidget->item(row, 4)->text();
        QString drive = ui->tableWidget->item(row, 5)->text();
        QString position = ui->tableWidget->item(row, 6)->text();

        // Создаем объект Car и добавляем его в список
        Car car(
            name.toStdString(),
            year.toUInt(),
            mileage.toUInt(),
            body.toStdString(),
            gearbox.toStdString(),
            drive.toStdString(),
            (position.toUpper() == "R") ? 1 : 0
            );
        cars.append(car);
    }
    out << cars;
}

void MainWindow::setupHeaderStyles(QTableWidget *tableWidget){
    QColor colorBlack(2370104); //#242A38
    QColor colorDefault(3093826); //#2F3542
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

void MainWindow::setupMenuBar(QMenuBar *menubar){
    //                                (tr("&...")) для макросов Alt+...
    QMenu *fileMenu = menubar->addMenu(tr("&File"));

    QAction *saveAct = new QAction(tr("Save"), this);
    connect(saveAct, &QAction::triggered, this, &MainWindow::writeToFile);
    QAction *openAct = new QAction(tr("Open"), this);
    connect(openAct, &QAction::triggered, this, &MainWindow::readFromFile);
    QAction *exitAct = new QAction(tr("Exit"), this);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    fileMenu->addAction(saveAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    QMenu *toolMenu = menubar->addMenu(tr("&Edit"));

    act_add = new QAction(tr("&Add"), this);
    connect(act_add, &QAction::triggered, this, &MainWindow::addEntry);
    connect(ui->btn_add, &QPushButton::clicked, this, &MainWindow::addEntry);

    act_edit = new QAction(tr("&Edit"), this);
    act_edit->setEnabled(false);
    connect(act_edit, &QAction::triggered, this, &MainWindow::editEntry);
    connect(ui->btn_edit, &QPushButton::clicked, this, &MainWindow::editEntry);

    act_remove = new QAction(tr("&Delete"), this);
    act_remove->setEnabled(false);
    connect(act_remove, &QAction::triggered, this, &MainWindow::removeEntry);
    connect(ui->btn_remove, &QPushButton::clicked, this, &MainWindow::removeEntry);

    toolMenu->addAction(act_add);
    toolMenu->addAction(act_edit);
    toolMenu->addSeparator();
    toolMenu->addAction(act_remove);

}
