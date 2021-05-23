#include "aboutform.h"
#include "ui_aboutform.h"

AboutForm::AboutForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutForm)
{
    ui->setupUi(this);
}

AboutForm::~AboutForm()
{
    delete ui;
}

void AboutForm::fill_percents(double p1, double p2, double p3, double p4)
{
    QString new_lbl;

    new_lbl = ui->label_term_1->text() + QString::number(p1, 'g', 10);
    ui->label_term_1->setText(new_lbl + "%.");

    new_lbl = ui->label_term_2->text() + QString::number(p2, 'g', 10);
    ui->label_term_2->setText(new_lbl + "%.");

    new_lbl = ui->label_term_3->text() + QString::number(p3, 'g', 10);
    ui->label_term_3->setText(new_lbl + "%.");

    new_lbl = ui->label_term_4->text() + QString::number(p4, 'g', 10);
    ui->label_term_4->setText(new_lbl + "%.");
}
