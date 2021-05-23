#include "resultform.h"
#include "ui_resultform.h"

double temp;

ResultForm::ResultForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultForm)
{
    ui->setupUi(this);
}

ResultForm::~ResultForm()
{
    delete ui;
}

void ResultForm::show_result()
{
    QString new_lbl;

    new_lbl = QString::number(new_sum, 'g', 10);
    ui->label_res->setText(new_lbl);

    new_lbl = QString::number(old_sum, 'g', 10);
    ui->label_old->setText(new_lbl);

    new_lbl = QString::number(difference, 'g', 10);
    ui->label_difference->setText(new_lbl);

    ui->label_value_1->setText(value);
    ui->label_value_2->setText(value);
    ui->label_value_3->setText(value);
}

void ResultForm::on_pushButton_clicked()
{
    close();
}
