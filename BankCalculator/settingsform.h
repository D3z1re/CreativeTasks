#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QDialog>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();

    double p, p1, p2, p3;
    double old_p, old_p1, old_p2, old_p3;
    double usd, eur, old_usd, old_eur;
    bool is_saved = false;

    void check_percents();

private slots:
    void on_spin_p_1_valueChanged(double arg1);

    void on_spin_p_2_valueChanged(double arg1);

    void on_spin_p_3_valueChanged(double arg1);

    void on_spin_p_4_valueChanged(double arg1);

    void on_button_discharge_clicked();

    void on_button_save_clicked();

    void on_spin_usd_valueChanged(double arg1);

    void on_spin_eur_valueChanged(double arg1);

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
