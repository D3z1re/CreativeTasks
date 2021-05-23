#include "graph.h"
#include "newedgeform.h"
#include "newmatrixform.h"
#include "newmatrix_6.h"
#include "delvertform.h"
#include "deledgeform.h"
#include "ui_graph.h"
#include <cmath>

int     radiusA = 30,
        radiusB = 230;

QString Graph::komi() //решение задачи комивояжера
{
    int n;
    int* res;
    int** help;
    int*** mat;

    n = kol;
    help = new int* [n];
    res = new int[n];
    mat = new int** [n];

    for (int i = 0; i <= n; i++) {
        help[i] = new int[n];
    }

    for (int i = 0; i < n; i++) //замена нулей матрицы на нулевые указатели
    {
        mat[i] = new int* [n];
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                mat[i][j] = nullptr;
                continue;
            }
            mat[i][j] = new int(matrix[i][j]);
        }
    }

    for (int l = 0; l < n; l++)
    {
        for (int i = 0; i < n; i++) //поиск минимальных элементов и редукция матрицы
        {
            int min = 1000000;
            for (int j = 0; j < n; j++)
                if (mat[i][j] && min > * mat[i][j])
                    min = *mat[i][j];
            for (int j = 0; j < n; j++)
                if (mat[i][j])
                    *mat[i][j] -= min;
        }
        for (int j = 0; j < n; j++)
        {
            int min = 1000000;
            for (int i = 0; i < n; i++)
                if (mat[i][j] && min > * mat[i][j])
                    min = *mat[i][j];
            for (int i = 0; i < n; i++)
                if (mat[i][j])
                    *mat[i][j] -= min;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                help[i][j] = 0;

        for (int i = 0; i < n; i++)                      //оценка нулей
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] && !*mat[i][j])
                {
                    int hmin = 1000000;
                    int vmin = 1000000;

                    for (int l = 0; l < n; l++)
                        if (l != i && mat[l][j] && hmin > * mat[l][j]) hmin = *mat[l][j];
                    for (int l = 0; l < n; l++)
                        if (l != j && mat[i][l] && vmin > * mat[i][l]) vmin = *mat[i][l];
                    help[i][j] = hmin + vmin;
                }
            }

        int mcost = 0, mi = 0, mj = 0;           //чистка карты
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (mat[i][j] && mcost < help[i][j]) {
                    mcost = help[i][j];
                    mi = i;
                    mj = j;
                }
        res[mi] = mj;

        for (int i = 0; i < n; i++)
            mat[i][mj] = nullptr;

        for (int i = 0; i < n; i++)
            mat[mi][i] = nullptr;

        mat[mj][mi] = nullptr;
    }
    int s = 0;                                 //подсчет длины пути
    for (int i = 0, j = 0; i < n; i++)
        {
            j = res[i];
            s += matrix[i][j];
        }
    QString tmp = "";                        //вывод кратчайшего маршрута и его длинны
    tmp += QString("\nПуть: ");
    int temp = 0;
    for (int l = 0; l < n;) {
        for (int i = 0, j = 0; i < n; i++) {
            if (temp == 0 || i + 1 == temp) {
                if (temp == 0) tmp += QString::number(i + 1);
                j = res[i];
                temp = j + 1;
                if (temp > 0)	tmp += QString(" -> ") + QString::number(temp);
                l++;
            }
        }
    }
    tmp += QString("\nРасстояние: ") + QString::number(s);
    return tmp;
}

QString Graph::Print_Matrix() //вывод матрицы смежности
{
    QString tmp = "";
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            if (i == j)
                tmp += "M\t";
            else
                tmp += QString::number(matrix[i][j]) + "\t";
        }
        tmp += "\n";
    }
    return tmp;
}

int Graph::GetWeight(const int vert1, const int vert2) //получение веса ребра
{
    if (vert1 >= 0 && vert1 < matrix.size() && vert2 >=0 && vert2 < matrix.size())
        return matrix[vert1][vert2];
    else
        return 0;
}

void Graph::DrawLines(QGraphicsScene* scene) //отрисовка ребер графа
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    int     centerX= scene->width() / 2,
            centerY = scene->height() / 2;
    double iter = 2 * 3.1415 / matrix.size();
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            if (GetWeight(i, j) > 0){
                int     vert_1_x = centerX + cos(iter * i) * radiusB,
                        vert_1_y = centerY - sin(iter * i) * radiusB,
                        vert_2_x = centerX + cos(iter * j) * radiusB,
                        vert_2_y = centerY - sin(iter * j) * radiusB;
                scene->addLine(vert_1_x, vert_1_y, vert_2_x, vert_2_y, pen);
                QGraphicsTextItem *number = scene->addText(QString::number(GetWeight(i, j)), QFont("Times", 14));
                number->setPos((vert_2_x + vert_1_x) / 2, (vert_2_y + vert_1_y) / 2);
            }
        }
    }
}

void Graph::DrawArrows(QGraphicsScene* scene) //отрисовка стрелок
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    int     centerX= scene->width() / 2,
            centerY = scene->height() / 2;
    double len = 15.0;
    double ostr = 0.35;
    double arr_x, arr_y;
    double iter = 2 * 3.1415 / matrix.size();
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            if (GetWeight(i, j) > 0){
                int     vert_1_x = centerX + cos(iter * i) * radiusB,
                        vert_1_y = centerY - sin(iter * i) * radiusB,
                        vert_2_x = centerX + cos(iter * j) * radiusB,
                        vert_2_y = centerY - sin(iter * j) * radiusB;
                double angle = atan2(((double)vert_2_y - vert_1_y), ((double)(vert_2_x - vert_1_x)));
                //double t = radiusA / sqrt((vert_2_x - vert_1_x) * (vert_2_x - vert_1_x) + (vert_2_y - vert_1_y) * (vert_2_y - vert_1_y));
                arr_x = (vert_2_x - (radiusA * cos(angle))) - (len * cos(angle + ostr));
                arr_y = (vert_2_y - (radiusA * sin(angle))) - (len * sin(angle + ostr));
                scene->addLine(vert_2_x - (radiusA * cos(angle)), vert_2_y - (radiusA * sin(angle)), arr_x, arr_y, pen);
                arr_x = (vert_2_x - (radiusA * cos(angle))) - (len * cos(angle - ostr));
                arr_y = (vert_2_y - (radiusA * sin(angle))) - (len * sin(angle - ostr));
                scene->addLine(vert_2_x - (radiusA * cos(angle)), vert_2_y - (radiusA * sin(angle)), arr_x, arr_y, pen);
            }
        }
    }
}

void Graph::DrawNodes(QGraphicsScene* scene) //отрисовка вершин графа
{
    QPen pen(Qt::black);
    pen.setWidth(3);
    int     centerX= scene->width() / 2,
            centerY = scene->height() / 2;
    double iter = 2 * 3.1415 / matrix.size();
    for (int i = 0; i < matrix.size(); i++){
        scene->addEllipse(centerX + cos(iter * i) * radiusB - radiusA,
                          centerY - sin(iter * i) * radiusB - radiusA, 2*radiusA, 2*radiusA,
                          pen, QBrush(QColor(193,251,227)));

        QGraphicsTextItem *number = scene->addText(QString::number(i+1), QFont("Times", 14));
        number->setPos(centerX + cos(iter * i) * radiusB - radiusA + 18,
                       centerY - sin(iter * i) * radiusB - radiusA + 10);
    }
}


void Graph::DrawGraph(QGraphicsScene* scene) //отрисовка графа
{
    DrawLines(scene);
    DrawArrows(scene);
    DrawNodes(scene);
}

void Graph::Draw() //отрисовка сцены с графом
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 700, 630);

    ui->graphicsView->setScene(scene);
    scene->clear();
    scene->setBackgroundBrush(QBrush(QColor(214,237,255), Qt::SolidPattern));
    ui->label_Matrix->setText(Print_Matrix());
    DrawGraph(scene);
}

void Graph::Add_Vert() //добавление вершины
{
    for (int i = 0; i < kol; i++)
    {
        matrix[i].push_back(0);
    }

    matrix.push_back({});
    kol++;
    for (int i = 0; i < kol; i++)
    {
        matrix[kol - 1].push_back(0);
    }

}

void Graph::Del_Vert(int vert) //удаление вершины
{
    matrix.erase(matrix.begin() + vert);
    kol--;
    for (int i = 0; i < kol; i++)
    {
        matrix[i].erase(matrix[i].begin() + vert);
    }
}

void Graph::Del_Edge(int src, int trg) //удаление ребра
{
    matrix[src - 1][trg - 1] = 0;
}

void Graph::Add_Edge(int source, int target, int weight) //добавление ребра
{
    if (source > 0 && source <= kol && target > 0 && target <= kol && weight > 0)
    {
        matrix[source - 1][target - 1] = weight;
    }
}

void Graph::New_Matrix_6() //ввод новой матрицы
{
    NewMatrix_6 window;
    window.setWindowFlags (window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    window.setModal(true);
    window.exec();
    if (window.isSaved)
    {
        matrix.clear();
        kol = 6;
        for (int i = 0; i < kol; i++)
        {
            matrix.push_back({});
            for (int j = 0; j < kol; j++)
            {
                matrix[i].push_back(0);
            }
        }

        matrix[0][0] = window.s_0_0;
        matrix[0][1] = window.s_0_1;
        matrix[0][2] = window.s_0_2;
        matrix[0][3] = window.s_0_3;
        matrix[0][4] = window.s_0_4;
        matrix[0][5] = window.s_0_5;

        matrix[1][0] = window.s_1_0;
        matrix[1][1] = window.s_1_1;
        matrix[1][2] = window.s_1_2;
        matrix[1][3] = window.s_1_3;
        matrix[1][4] = window.s_1_4;
        matrix[1][5] = window.s_1_5;

        matrix[2][0] = window.s_2_0;
        matrix[2][1] = window.s_2_1;
        matrix[2][2] = window.s_2_2;
        matrix[2][3] = window.s_2_3;
        matrix[2][4] = window.s_2_4;
        matrix[2][5] = window.s_2_5;

        matrix[3][0] = window.s_3_0;
        matrix[3][1] = window.s_3_1;
        matrix[3][2] = window.s_3_2;
        matrix[3][3] = window.s_3_3;
        matrix[3][4] = window.s_3_4;
        matrix[3][5] = window.s_3_5;

        matrix[4][0] = window.s_4_0;
        matrix[4][1] = window.s_4_1;
        matrix[4][2] = window.s_4_2;
        matrix[4][3] = window.s_4_3;
        matrix[4][4] = window.s_4_4;
        matrix[4][5] = window.s_4_5;

        matrix[5][0] = window.s_5_0;
        matrix[5][1] = window.s_5_1;
        matrix[5][2] = window.s_5_2;
        matrix[5][3] = window.s_5_3;
        matrix[5][4] = window.s_5_4;
        matrix[5][5] = window.s_5_5;
    }

}

void Graph::New_Edge() //вывод окна для добавления ребра
{
    NewEdgeForm window;
    window.setWindowFlags (window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    window.setModal(true);
    window.max_kol = kol + 1;
    window.check_max();
    window.exec();
    if(window.isSaved)
    {
        int source = window.source;
        int target = window.target;
        int weight = window.weight;
        bool way = window.way;
        Add_Edge(source, target, weight);
        if (way)
        {
            Add_Edge(target, source, weight);
        }
    }
}

Graph::Graph(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Graph)
{
    ui->setupUi(this);
    kol = 6;
    matrix = { {0, 14, 0, 0, 0, 0 },
               {0, 0, 0, 0, 42, 23 },
               {19, 0, 0, 9, 0, 0 },
               {0, 0, 0, 0, 0, 31 },
               {0, 0, 18, 0, 0, 0 },
               {28, 23, 0, 0, 0, 0 } };
    Draw();
}

Graph::~Graph()
{
    delete ui;
}

void Graph::on_b_addVert_clicked()
{
    Add_Vert();
    Draw();
}

void Graph::on_b_komi_clicked()
{
    ui->label_komi->setText(komi());
}

void Graph::on_b_newMatrix_clicked()
{
    NewMatrixForm new_mat;
    new_mat.setWindowFlags (new_mat.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    new_mat.setModal(true);
    new_mat.exec();
    if (new_mat.isSaved)
    {
        matrix.clear();
        kol = 0;
        for (int i = 0; i < new_mat.verts; i++)
        {
            Add_Vert();
        }
        int verts_num = new_mat.edges;
        for (int i = 0; i < verts_num; i++)
        {
            New_Edge();
        }
    }
    Draw();
}

void Graph::on_b_addEdge_clicked()
{
    New_Edge();
    Draw();
}

void Graph::on_b_delVert_clicked()
{
    DelVertForm window;
    window.setWindowFlags (window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    window.setModal(true);
    window.max_kol = kol + 1;
    window.check_max();
    window.exec();
    if (window.isSaved)
    {
        Del_Vert(window.kol - 1);
    }
    Draw();
}

void Graph::on_b_delEdge_clicked()
{
    DelEdgeForm window;
    window.setWindowFlags (window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    window.setModal(true);
    window.max_kol = kol + 1;
    window.check_max();
    window.exec();
    if (window.isSaved)
    {
        int source = window.source;
        int target = window.target;
        Del_Edge(source, target);
        Draw();
    }
}

void Graph::on_b_newMatrix_6_clicked()
{
    New_Matrix_6();
    Draw();
}
