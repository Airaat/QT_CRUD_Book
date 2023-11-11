#include "filterform.h"
#include "ui_filterform.h"

FilterForm::FilterForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterForm)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &FilterForm::Confirm);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &FilterForm::Decline);
}

FilterForm::~FilterForm()
{
    delete ui;
}

size_t FilterForm::getMin() const { return _min; }
size_t FilterForm::getMax() const { return _max; }

void FilterForm::Confirm(){
    QString minText = ui->edit_min->text();
    QString maxText = ui->edit_max->text();
    if (!(minText.isEmpty() & maxText.isEmpty())){
        _min = minText.toUInt();
        _max = maxText.toUInt();
        emit filterRecordsRequested(_min, _max);
        close();
        ui->edit_min->clear();
        ui->edit_max->clear();
    }
}

void FilterForm::Decline(){
    close();
    ui->edit_min->clear();
    ui->edit_max->clear();
}
