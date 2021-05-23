#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int current_value = 0;
    double p = 5, p1 = 3.2, p2 = 3, p3 = 2.6;
    double RUB_TO_USD = 74.0;
    double RUB_TO_EUR = 89.0;

private slots:
    void on_button_c_clicked();
    void add_digit();
    void show_percent();
    void convert_value();

    void on_button_point_clicked();

    void on_spin_mon_valueChanged();

    void on_spin_yr_valueChanged();

    void on_button_calc_clicked();

    void on_button_help_clicked();

    void on_button_settings_clicked();

    void on_button_erase_clicked();

private:
    Ui::MainWindow *ui;

    double calculate();
    void check_terms();
    bool check_right_summ();
    bool check_right_time();
};
#endif // MAINWINDOW_H
