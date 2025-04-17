#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVector>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Vector;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();
    void on_btnTriangle_clicked();
    void on_btnParallelogram_clicked();
    void on_btnClear_clicked();

private:
    QColor getRandomColor();
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QVector<Vector*> vectors;
    QList<Vector*> selectedVectors() const;
};
