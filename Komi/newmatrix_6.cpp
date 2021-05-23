#include "newmatrix_6.h"
#include "ui_newmatrix_6.h"

NewMatrix_6::NewMatrix_6(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMatrix_6)
{
    ui->setupUi(this);
}

NewMatrix_6::~NewMatrix_6()
{
    delete ui;
}

void NewMatrix_6::on_pushButton_clicked()
{
    isSaved = true;
    s_0_0 = 0; s_0_1 = ui->s_0_1->value(); s_0_2 = ui->s_0_2->value();
    s_0_3 = ui->s_0_3->value(); s_0_4 = ui->s_0_4->value(); s_0_5 = ui->s_0_5->value();

    s_1_0 = ui->s_1_0->value(); s_1_1 = 0; s_1_2 = ui->s_1_2->value();
    s_1_3 = ui->s_1_3->value(); s_1_4 = ui->s_1_4->value(); s_1_5 = ui->s_1_5->value();

    s_2_0 = ui->s_2_0->value(); s_2_1 = ui->s_2_1->value(); s_2_2 = 0;
    s_2_3 = ui->s_2_3->value(); s_2_4 = ui->s_2_4->value(); s_2_5 = ui->s_2_5->value();

    s_3_0 = ui->s_3_0->value(); s_3_1 = ui->s_3_1->value(); s_3_2 = ui->s_3_2->value();
    s_3_3 = 0; s_3_4 = ui->s_3_4->value(); s_3_5 = ui->s_3_5->value();

    s_4_0 = ui->s_4_0->value(); s_4_1 = ui->s_4_1->value(); s_4_2 = ui->s_4_2->value();
    s_4_3 = ui->s_4_3->value(); s_4_4 = 0; s_4_5 = ui->s_4_5->value();

    s_5_0 = ui->s_5_0->value(); s_5_1 = ui->s_5_1->value(); s_5_2 = ui->s_5_2->value();
    s_5_3 = ui->s_5_3->value(); s_5_4 = ui->s_5_4->value(); s_5_5 = 0;

    close();
}
