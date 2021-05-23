#include "settingsform.h"
#include "ui_settingsform.h"

SettingsForm::SettingsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::check_percents()
{
    ui->spin_p_1->setValue(p);
    ui->spin_p_2->setValue(p1);
    ui->spin_p_3->setValue(p2);
    ui->spin_p_4->setValue(p3);
    ui->spin_usd->setValue(usd);
    ui->spin_eur->setValue(eur);
}

void SettingsForm::on_spin_p_1_valueChanged(double arg1)
{
    p = ui->spin_p_1->value();
}

void SettingsForm::on_spin_p_2_valueChanged(double arg1)
{
    p1 = ui->spin_p_2->value();
}

void SettingsForm::on_spin_p_3_valueChanged(double arg1)
{
    p2 = ui->spin_p_3->value();
}

void SettingsForm::on_spin_p_4_valueChanged(double arg1)
{
    p3 = ui->spin_p_4->value();
}

void SettingsForm::on_button_discharge_clicked()
{
    p = old_p; ui->spin_p_1->setValue(p);
    p1 = old_p1; ui->spin_p_2->setValue(p1);
    p2 = old_p2; ui->spin_p_3->setValue(p2);
    p3 = old_p3; ui->spin_p_4->setValue(p3);
    usd = old_usd; ui->spin_usd->setValue(usd);
    eur = old_eur; ui->spin_eur->setValue(eur);
}

void SettingsForm::on_button_save_clicked()
{
    is_saved = true;
    close();
}

void SettingsForm::on_spin_usd_valueChanged(double arg1)
{
    usd = ui->spin_usd->value();
}

void SettingsForm::on_spin_eur_valueChanged(double arg1)
{
    eur = ui->spin_eur->value();
}
