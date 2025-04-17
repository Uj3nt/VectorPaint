#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector.h"

#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->scale(1, -1);
    scene->addLine(-1000, 0, 1000, 0, QPen(Qt::darkGray));
    scene->addLine(0, -1000, 0, 1000, QPen(Qt::darkGray));

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setInteractive(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QColor MainWindow::getRandomColor() {
    QColor color;
    do {
        int r = QRandomGenerator::global()->bounded(256);
        int g = QRandomGenerator::global()->bounded(256);
        int b = QRandomGenerator::global()->bounded(256);
        color.setRgb(r, g, b);
    } while (color == Qt::red || color == Qt::blue);
    return color;
}

QList<Vector*> MainWindow::selectedVectors() const {
    QList<Vector*> selected;
    for (Vector* v : vectors) {
        if (v->m_selected) {
            selected.append(v);
        }
    }
    return selected;
}


void MainWindow::on_btnAdd_clicked() {
    bool ok;
    double x = QInputDialog::getDouble(this, "Начало X", "Введите X:", 0, -1000, 1000, 1, &ok);
    if (!ok) return;
    double y = QInputDialog::getDouble(this, "Начало Y", "Введите Y:", 0, -1000, 1000, 1, &ok);
    if (!ok) return;
    double dx = QInputDialog::getDouble(this, "Dx", "Введите смещение по X:", 0, -1000, 1000, 1, &ok);
    if (!ok) return;
    double dy = QInputDialog::getDouble(this, "Dy", "Введите смещение по Y:", 0, -1000, 1000, 1, &ok);
    if (!ok) return;

    QColor random = getRandomColor();

    Vector *v = new Vector(x, y, x + dx, y + dy, random);
    scene->addItem(v);
    vectors.append(v);
}

void MainWindow::on_btnTriangle_clicked()
{
    QList<Vector*> selected = selectedVectors();

    qDebug() << "Выделено векторов:" << selected.size();

    Vector *v1 = nullptr;
    Vector *v2 = nullptr;

    if (selected.size() == 2) {
        v1 = selected[0];
        v2 = selected[1];
    } else if (vectors.size() >= 2) {
        v1 = vectors[vectors.size() - 2];
        v2 = vectors[vectors.size() - 1];
    } else {
        return;
    }

    QPointF start = v1->start();
    QPointF end = start + (v1->end() - v1->start()) + (v2->end() - v2->start());
    Vector *result = new Vector(start.x(), start.y(), end.x(), end.y(), Qt::red);
    scene->addItem(result);
    vectors.append(result);
}

void MainWindow::on_btnParallelogram_clicked()
{
    QList<Vector*> selected = selectedVectors();

    Vector *v1 = nullptr;
    Vector *v2 = nullptr;

    if (selected.size() == 2) {
        v1 = selected[0];
        v2 = selected[1];
    } else if (vectors.size() >= 2) {
        v1 = vectors[vectors.size() - 2];
        v2 = vectors[vectors.size() - 1];
    } else {
        return;
    }

    QPointF origin = v1->start();
    QPointF a = v1->end() - v1->start();
    QPointF b = v2->end() - v2->start();

    QPointF end = origin + a + b;
    Vector *result = new Vector(origin.x(), origin.y(), end.x(), end.y(), Qt::blue);
    scene->addItem(result);
    vectors.append(result);

    Vector *side1 = new Vector(origin.x(), origin.y(), (origin + a).x(), (origin + a).y(), Qt::gray);
    Vector *side2 = new Vector(origin.x(), origin.y(), (origin + b).x(), (origin + b).y(), Qt::gray);
    Vector *opposite = new Vector((origin + b).x(), (origin + b).y(), end.x(), end.y(), Qt::gray);
    Vector *opposite2 = new Vector((origin + a).x(), (origin + a).y(), end.x(), end.y(), Qt::gray);

    scene->addItem(side1);
    scene->addItem(side2);
    scene->addItem(opposite);
    scene->addItem(opposite2);
}

void MainWindow::on_btnClear_clicked() {
    QList<Vector*> toDelete = selectedVectors();
    qDebug() << "Выделено под удаление:" << toDelete.size();
    if (toDelete.size() == 0) {
        scene->clear();
        vectors.clear();
        scene->addLine(-1000, 0, 1000, 0, QPen(Qt::darkGray));
        scene->addLine(0, -1000, 0, 1000, QPen(Qt::darkGray));
    } else {
        for (Vector* v : toDelete) {
            v->m_selected = 0;
            scene->removeItem(v);
            vectors.removeAll(v);
            delete v;
        }
    }
}
