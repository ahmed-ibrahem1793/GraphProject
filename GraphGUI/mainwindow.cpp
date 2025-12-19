#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // 1. Setup UI Layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // File Selection
    btnLoadFile = new QPushButton("Load Graph File (.txt)", this);
    lblFileStatus = new QLabel("No file loaded", this);
    layout->addWidget(btnLoadFile);
    layout->addWidget(lblFileStatus);

    // Separator
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    layout->addWidget(line);

    // MST Buttons
    btnPrim = new QPushButton("Run Prim's MST", this);
    btnKruskal = new QPushButton("Run Kruskal's MST", this);
    layout->addWidget(btnPrim);
    layout->addWidget(btnKruskal);

    // Dijkstra Section
    QHBoxLayout *dijkstraLayout = new QHBoxLayout();
    lblSourceNode = new QLabel("Start Node:", this);
    inputStartNode = new QLineEdit("1", this); // Default to 1
    btnDijkstra = new QPushButton("Run Dijkstra", this);
    dijkstraLayout->addWidget(lblSourceNode);
    dijkstraLayout->addWidget(inputStartNode);
    dijkstraLayout->addWidget(btnDijkstra);
    layout->addLayout(dijkstraLayout);

    // Output Display
    outputDisplay = new QTextEdit(this);
    outputDisplay->setReadOnly(true);
    layout->addWidget(outputDisplay);

    setCentralWidget(centralWidget);
    resize(500, 600); // Window size

    // 2. Connect Buttons to Functions
    connect(btnLoadFile, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(btnPrim, &QPushButton::clicked, this, &MainWindow::runPrim);
    connect(btnKruskal, &QPushButton::clicked, this, &MainWindow::runKruskal);
    connect(btnDijkstra, &QPushButton::clicked, this, &MainWindow::runDijkstra);
}

MainWindow::~MainWindow() {}

void MainWindow::loadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Graph File", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        currentGraphFile = fileName.toStdString();
        lblFileStatus->setText("Loaded: " + fileName);
        outputDisplay->setText("Graph loaded successfully.");
    }
}

void MainWindow::runPrim() {
    if (currentGraphFile.empty()) {
        QMessageBox::warning(this, "Error", "Please load a file first!");
        return;
    }
    Graph g(currentGraphFile);
    g.primMST("prim_result.txt");

    // Read result back and display
    string result = Graph::readFileContent("prim_result.txt");
    outputDisplay->setText(QString::fromStdString(result));
}

void MainWindow::runKruskal() {
    if (currentGraphFile.empty()) {
        QMessageBox::warning(this, "Error", "Please load a file first!");
        return;
    }
    Graph g(currentGraphFile);
    g.kruskalMST("kruskal_result.txt");

    string result = Graph::readFileContent("kruskal_result.txt");
    outputDisplay->setText(QString::fromStdString(result));
}

void MainWindow::runDijkstra() {
    if (currentGraphFile.empty()) {
        QMessageBox::warning(this, "Error", "Please load a file first!");
        return;
    }

    bool ok;
    int src = inputStartNode->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Please enter a valid integer for Start Node");
        return;
    }

    Graph g(currentGraphFile);
    g.dijkstra(src, "dijkstra_result.txt");

    string result = Graph::readFileContent("dijkstra_result.txt");
    outputDisplay->setText(QString::fromStdString(result));
}
