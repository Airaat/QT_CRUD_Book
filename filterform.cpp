#include "filterform.h"
#include "ui_filterform.h"

FilterForm::FilterForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterForm)
{
    ui->setupUi(this);
}

FilterForm::~FilterForm()
{
    delete ui;
}
