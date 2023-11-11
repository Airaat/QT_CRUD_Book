#ifndef FILTERFORM_H
#define FILTERFORM_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class FilterForm;
}

class FilterForm : public QDialog
{
    Q_OBJECT

public:
    explicit FilterForm(QWidget *parent = nullptr);
    ~FilterForm();
    size_t getMin() const;
    size_t getMax() const;

private slots:
    void Confirm();
    void Decline();

private:
    Ui::FilterForm *ui;
    size_t _min;
    size_t _max;

signals:
    void filterRecordsRequested(const size_t min, const size_t max);
};

#endif // FILTERFORM_H
