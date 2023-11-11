#ifndef FILTERFORM_H
#define FILTERFORM_H

#include <QDialog>

namespace Ui {
class FilterForm;
}

class FilterForm : public QDialog
{
    Q_OBJECT

public:
    explicit FilterForm(QWidget *parent = nullptr);
    ~FilterForm();

private:
    Ui::FilterForm *ui;
};

#endif // FILTERFORM_H
