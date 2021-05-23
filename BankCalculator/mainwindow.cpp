#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultform.h"
#include "aboutform.h"
#include "settingsform.h"
#include <cmath>
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->button_0, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_1, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_2, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_3, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_4, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_5, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_6, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_7, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_8, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_9, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->combo_terms, SIGNAL(currentIndexChanged(int)), this, SLOT(show_percent()));
    connect(ui->combo_value, SIGNAL(currentIndexChanged(int)), this, SLOT(convert_value()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_terms() //изменение условий при изменении срока вклада
{
    int mn = ui->spin_mon->value() + (ui->spin_yr->value() * 12);
    if (mn < 6) {
        ui->combo_terms->setCurrentIndex(3);
    } else
    if (mn >= 6 && mn < 12) {
        ui->combo_terms->setCurrentIndex(2);
    } else
    if (mn >= 12 && mn < 36) {
        ui->combo_terms->setCurrentIndex(1);
    } else
    if (mn >= 36) {
        ui->combo_terms->setCurrentIndex(0);
    }
}

void MainWindow::convert_value() //конвертация валют
{
    QString new_lbl;
    double tmp = ui->result_show->text().toDouble();
    if (current_value == 1) {
        tmp *= RUB_TO_USD;
    } else
    if (current_value == 2) {
        tmp *= RUB_TO_EUR;
    }

    if (ui->combo_value->currentIndex() == 1) {
        tmp /= RUB_TO_USD;
    } else
    if (ui->combo_value->currentIndex() == 2) {
        tmp /= RUB_TO_EUR;
    }
    tmp = floor(tmp * 10) / 10;

    current_value = ui->combo_value->currentIndex();

    new_lbl = QString::number(tmp, 'g', 10);
    ui->result_show->setText(new_lbl);
}

bool MainWindow::check_right_summ() //проверка корректности введенной суммы вклада
{
    double tmp = ui->result_show->text().toDouble();
    double MIN_SUM, MAX_SUM;
    switch (current_value) {
    case 0: {
        MIN_SUM = 10000;
        MAX_SUM = 100000000;
        if (tmp < MIN_SUM || tmp > MAX_SUM) {
            QMessageBox msgBox;
            QPixmap icon(":/icons/icons/error.png");
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Введена некорректная сумма. \nМинимальная сумма вклада: 10000 RUB.\nМаксимальная сумма вклада: 100000000 RUB.");
            msgBox.setWindowIcon(icon);
            msgBox.setIconPixmap(icon.scaled(50, 50));
            msgBox.exec();
            return false;
        }
        break;
    }
    case 1: {
        MIN_SUM = 150;
        MAX_SUM = 1500000;
        if (tmp < MIN_SUM || tmp > MAX_SUM) {
            QMessageBox msgBox;
            QPixmap icon(":/icons/icons/error.png");
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Введена некорректная сумма. \nМинимальная сумма вклада: 150 USD.\nМаксимальная сумма вклада: 1500000 USD.");
            msgBox.setWindowIcon(icon);
            msgBox.setIconPixmap(icon.scaled(50, 50));
            msgBox.exec();
            return false;
        }
        break;
    }
    case 2:{
        MIN_SUM = 150;
        MAX_SUM = 1500000;
        if (tmp < MIN_SUM || tmp > MAX_SUM) {
            QMessageBox msgBox;
            QPixmap icon(":/icons/icons/error.png");
            msgBox.setWindowTitle("Ошибка");
            msgBox.setText("Введена некорректная сумма. \nМинимальная сумма вклада: 150 EUR.\nМаксимальная сумма вклада: 1500000 EUR.");
            msgBox.setWindowIcon(icon);
            msgBox.setIconPixmap(icon.scaled(50, 50));
            msgBox.exec();
            return false;
        }
        break;
    }
    }
    return true;
}

bool MainWindow::check_right_time() //проверка правильности выбранных условий вклада
{
    int index = ui->combo_terms->currentIndex();
    int mn = ui->spin_mon->value() + (ui->spin_yr->value() * 12);
    if (mn < 3) {
        QMessageBox msgBox;
        QPixmap icon(":/icons/icons/error.png");
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Минимальный срок вклада: 3 месяца.");
        msgBox.setWindowIcon(icon);
        msgBox.setIconPixmap(icon.scaled(50, 50));
        msgBox.exec();
        return false;
    } else
    if (mn < 6 && (index == 2 || index == 1 || index == 0)) {
        QMessageBox msgBox;
        QPixmap icon(":/icons/icons/error.png");
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Условия вклада выбраны неверно и были откорректированы автоматически.");
        msgBox.setWindowIcon(icon);
        msgBox.setIconPixmap(icon.scaled(50, 50));
        msgBox.exec();
        check_terms();
        return false;
    } else
    if (mn < 12 && (index == 1 || index == 0)) {
        QMessageBox msgBox;
        QPixmap icon(":/icons/icons/error.png");
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Условия вклада выбраны неверно и были откорректированы автоматически.");
        msgBox.setWindowIcon(icon);
        msgBox.setIconPixmap(icon.scaled(50, 50));
        msgBox.exec();
        check_terms();
        return false;
    } else
    if (mn < 36 && (index == 0)) {
        QMessageBox msgBox;
        QPixmap icon(":/icons/icons/error.png");
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Условия вклада выбраны неверно и были откорректированы автоматически.");
        msgBox.setWindowIcon(icon);
        msgBox.setIconPixmap(icon.scaled(50, 50));
        msgBox.exec();
        check_terms();
        return false;
    } else return true;
}

double MainWindow::calculate() //рассчет результата
{
    double tmp = ui->result_show->text().toDouble();

    switch (ui->combo_terms->currentIndex()) {
    case 0: {
        int yrs = ui->spin_yr->value();
        for (int i = 0; i < yrs;i++)
        {
            tmp = tmp + (tmp * (0.01 * p));
        } break;
    }
    case 1: {
        int months = ui->spin_mon->value() + (ui->spin_yr->value() * 12);
        for (int i = 0; i < months; i++)
        {
            tmp = tmp + (tmp * (0.01 * (p1 / 12.0)));
        } break;
    }
    case 2: {
        int days = (ui->spin_mon->value() * 30) + (ui->spin_yr->value() * 365);
        for (int i = 0; i < days; i++)
        {
            tmp = tmp + (((double)((int)tmp / 1000) * 1000) * ( 0.01 * (p2 / 365.0)));
        } break;
    }
    case 3: {
        int days = (ui->spin_mon->value() * 30) + (ui->spin_yr->value() * 365);
        for (int i = 0; i < days; i++)
        {
            tmp = tmp + (tmp * (0.01 * (3 / 365.0)));
        } break;
    }
    }
    return tmp;
}

void MainWindow::on_button_c_clicked() //стереть всё
{
    ui->result_show->setText("0");
}

void MainWindow::on_button_erase_clicked() //стереть последний элемент
{
    QString new_lbl = ui->result_show->text();
    if (new_lbl != "0") {
        new_lbl.chop(1);
        ui->result_show->setText(new_lbl);
    }
}

void MainWindow::add_digit() //ввод цифр
{
    double numbers;
    QString new_lbl;
    QPushButton *button = (QPushButton*)sender();

    if (ui->result_show->text().contains(".") && button->text() == "0") {
        new_lbl = ui->result_show->text() + button->text();
    } else {
    numbers = (ui ->result_show->text() + button->text()).toDouble();
    new_lbl = QString::number(numbers, 'g', 10);
    }
    ui->result_show->setText(new_lbl);
}

void MainWindow::on_button_point_clicked() //ввод точки
{
    if(!(ui->result_show->text().contains('.')))
            ui->result_show->setText(ui->result_show->text() + ".");
}

void MainWindow::on_spin_mon_valueChanged()
{
    if (ui->spin_mon->value() == 12 && ui->spin_yr->value() < 10)
    {
        ui->spin_yr->setValue(ui->spin_yr->value() + 1);
        ui->spin_mon->setValue(0);
    } else
    if (ui->spin_mon->value() == -1 && ui->spin_yr->value() > 0)
    {
        ui->spin_yr->setValue(ui->spin_yr->value() - 1);
        ui->spin_mon->setValue(11);
    } else
    if (ui->spin_mon->value() == -1 && ui->spin_yr->value() == 0)
    {
        ui->spin_mon->setValue(0);
    } else
    if (ui->spin_yr->value() == 10 && ui->spin_mon->value() > 0)
    {
        QMessageBox msgBox;
        QPixmap icon(":/icons/icons/warning.png");
        msgBox.setWindowTitle("Предупреждение");
        msgBox.setText("Максимальный срок вклада - 10 лет 0 месяцев.");
        msgBox.setWindowIcon(icon);
        msgBox.setIconPixmap(icon.scaled(50, 50));
        msgBox.exec();
        //QMessageBox::warning(this, "Предупреждение", "Максимальный срок вклада - 10 лет 0 месяцев.");
        ui->spin_mon->setValue(0);
    }
    check_terms();
}

void MainWindow::on_spin_yr_valueChanged()
{
    if (ui->spin_yr->value() == 11)
    {
        QMessageBox msgBox;
        QPixmap icon(":/icons/icons/warning.png");
        msgBox.setWindowTitle("Предупреждение");
        msgBox.setText("Максимальный срок вклада - 10 лет 0 месяцев.");
        msgBox.setWindowIcon(icon);
        msgBox.setIconPixmap(icon.scaled(50, 50));
        msgBox.exec();
        //QMessageBox::warning(this, "Предупреждение", "Максимальный срок вклада - 10 лет 0 месяцев.");

        ui->spin_yr->setValue(10);
        ui->spin_mon->setValue(0);
    } else
    if (ui->spin_yr->value() == 10)
    {
        ui->spin_mon->setValue(0);
    }
    check_terms();
}

void MainWindow::show_percent() //отображение процентной ставки
{
    switch (ui->combo_terms->currentIndex()) {
    case 0: {
        QString new_lbl;
        new_lbl = QString::number(p, 'g', 10);
        ui->percent_show->setText(new_lbl + "%");
        break;
    }
    case 1: {
        QString new_lbl;
        new_lbl = QString::number(p1, 'g', 10);
        ui->percent_show->setText(new_lbl + "%");
        break;
    }
    case 2: {
        QString new_lbl;
        new_lbl = QString::number(p2, 'g', 10);
        ui->percent_show->setText(new_lbl + "%");
        break;
    }
    case 3: {
        QString new_lbl;
        new_lbl = QString::number(p3, 'g', 10);
        ui->percent_show->setText(new_lbl + "%");
        break;
    }
    }
}

void MainWindow::on_button_calc_clicked() //рассчет и вывод результата
{
    double old;
    if (check_right_time() && check_right_summ()) {
        double diff = old = ui->result_show->text().toDouble();

        double result = calculate();

        result = floor(result * 10) / 10;

        diff = result - diff;
        diff = floor(diff * 10) / 10;

        ResultForm sec_win;
        sec_win.setWindowFlags (sec_win.windowFlags() & ~Qt::WindowContextHelpButtonHint);
        sec_win.setModal(true);
        sec_win.old_sum = old;
        sec_win.difference = diff;
        sec_win.new_sum = result;
        sec_win.value = ui->combo_value->currentText();
        sec_win.show_result();
        sec_win.exec();
    }
}

void MainWindow::on_button_help_clicked() //вывод окна-подсказки
{
    AboutForm about;
    about.setWindowFlags (about.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    about.setModal(true);
    about.fill_percents(p, p1, p2, p3);
    about.exec();
}

void MainWindow::on_button_settings_clicked() //вывод окна с настройками
{
    SettingsForm settings;
    settings.setWindowFlags (settings.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    settings.setModal(true);
    settings.old_p = settings.p = p;
    settings.old_p1 = settings.p1 = p1;
    settings.old_p2 = settings.p2 = p2;
    settings.old_p3 = settings.p3 = p3;
    settings.old_usd = settings.usd = RUB_TO_USD;
    settings.old_eur = settings.eur = RUB_TO_EUR;
    settings.check_percents();
    settings.exec();
    if (settings.is_saved) {
        p = settings.p;
        p1 = settings.p1;
        p2 = settings.p2;
        p3 = settings.p3;
        RUB_TO_USD = settings.usd;
        RUB_TO_EUR = settings.eur;
    }
    show_percent();
}
