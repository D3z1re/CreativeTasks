#ifndef RESULTFORM_H
#define RESULTFORM_H

#include <QDialog>

namespace Ui {
class ResultForm;
}

class ResultForm : public QDialog
{
    Q_OBJECT

public:
    explicit ResultForm(QWidget *parent = nullptr);
    ~ResultForm();

    double old_sum, new_sum, difference;
    QString value;
    void show_result();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ResultForm *ui;
};

#endif // RESULTFORM_H
