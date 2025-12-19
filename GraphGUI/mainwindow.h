#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "graph_logic.h"

class MainWindow : public QMainWindow {
    Q_OBJECT // Necessary for Qt signals/slots

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadFile();
    void runPrim();
    void runKruskal();
    void runDijkstra();

private:
    // UI Elements
    QPushButton *btnLoadFile;
    QLabel *lblFileStatus;

    QPushButton *btnPrim;
    QPushButton *btnKruskal;

    QLabel *lblSourceNode;
    QLineEdit *inputStartNode;
    QPushButton *btnDijkstra;

    QTextEdit *outputDisplay;

    // Logic Data
    string currentGraphFile;
};

#endif // MAINWINDOW_H
