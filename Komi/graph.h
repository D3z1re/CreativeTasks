#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QString>
#include <QGraphicsTextItem>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class Graph; }
QT_END_NAMESPACE

//int MAX_SIZE = 20;

class Graph : public QMainWindow
{
    Q_OBJECT

private:
    Ui::Graph *ui;
    QGraphicsScene *scene;

public:
    int kol;
    std::vector<std::vector<int>> matrix;

    Graph(QWidget *parent = nullptr);
    ~Graph();
    int GetWeight(const int vert1, const int vert2);
    void DrawLines(QGraphicsScene* scene);
    void DrawArrows(QGraphicsScene* scene);
    void DrawNodes(QGraphicsScene* scene);
    void DrawGraph(QGraphicsScene* scene);
    void Draw();
    void Add_Vert();
    void Del_Vert(int vert);
    void New_Edge();
    void Add_Edge(int source, int target, int weight);
    void Del_Edge(int src, int trg);
    void New_Matrix_6();

    QString komi();
    QString Print_Matrix();
private slots:
    void on_b_addVert_clicked();
    void on_b_komi_clicked();
    void on_b_newMatrix_clicked();
    void on_b_addEdge_clicked();
    void on_b_delVert_clicked();
    void on_b_delEdge_clicked();
    void on_b_newMatrix_6_clicked();
};
#endif // GRAPH_H
