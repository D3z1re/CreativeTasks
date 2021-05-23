#ifndef NEWMATRIX_6_H
#define NEWMATRIX_6_H

#include <QDialog>

namespace Ui {
class NewMatrix_6;
}

class NewMatrix_6 : public QDialog
{
    Q_OBJECT

public:
    explicit NewMatrix_6(QWidget *parent = nullptr);
    ~NewMatrix_6();
    bool isSaved = false;

    int s_0_0, s_0_1, s_0_2, s_0_3, s_0_4, s_0_5,
        s_1_0, s_1_1, s_1_2, s_1_3, s_1_4, s_1_5,
        s_2_0, s_2_1, s_2_2, s_2_3, s_2_4, s_2_5,
        s_3_0, s_3_1, s_3_2, s_3_3, s_3_4, s_3_5,
        s_4_0, s_4_1, s_4_2, s_4_3, s_4_4, s_4_5,
        s_5_0, s_5_1, s_5_2, s_5_3, s_5_4, s_5_5;
private slots:
    void on_pushButton_clicked();

private:
    Ui::NewMatrix_6 *ui;
};

#endif // NEWMATRIX_6_H
