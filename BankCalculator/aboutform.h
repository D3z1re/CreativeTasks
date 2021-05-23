#ifndef ABOUTFORM_H
#define ABOUTFORM_H

#include <QDialog>

namespace Ui {
class AboutForm;
}

class AboutForm : public QDialog
{
    Q_OBJECT

public:
    explicit AboutForm(QWidget *parent = nullptr);
    ~AboutForm();

    void fill_percents(double p1, double p2, double p3, double p4);

private:
    Ui::AboutForm *ui;
};

#endif // ABOUTFORM_H
