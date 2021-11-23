#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    log = new Logger();
    QDate now;
    log->SetFileName(QString("log_" + now.currentDate().toString() + ".txt"));
    parser = new Parser(log);
    // CHANGE VIEW SIGNALS AND SLOTS
    connect(ui->stressTest_button, SIGNAL(clicked()), this, SLOT(setupTab()));
    connect(ui->debug_button, SIGNAL(clicked()), this, SLOT(setupDebugTab()));

//    connect(ui->homebutton2, SIGNAL(clicked()), this, SLOT(HomeLobby()));
//    connect(ui->leaveButton, SIGNAL(clicked()), this, SLOT(HomeLobby()));
//    connect(ui->leaveButton2, SIGNAL(clicked()), this, SLOT(HomeLobby()));
//    connect(ui->quitButtonGameLobby, SIGNAL(clicked()), this, SLOT(HomeLobby()));
}

MainWindow::~MainWindow()
{
    delete parser;
    delete log;
    delete ui;
}

void MainWindow::setupTab()
{
    ui->tabWidget->setCurrentIndex(1);
    connect(ui->stressStart_button, SIGNAL(clicked()), this, SLOT(startRunEval()));
    log->LogEvent(QString("Transitioned to Setup Tab for Run Start"));
}

void MainWindow::setupDebugTab()
{
    ui->tabWidget->setCurrentIndex(1);
    connect(ui->stressStart_button, SIGNAL(clicked()), this, SLOT(startDebugEval()));
    log->LogEvent(QString("Transitioned to Setup Tab for Debug Start"));
}

void MainWindow::startRunEval()
{
    settings.port_name = ui->serial_port_lineEdit->displayText();
    settings.csv_file_location = ui->csv_file_loc->displayText();
    settings.rest_1_length = ui->rest_1_length->displayText().toUShort();
    settings.rest_2_length = ui->rest_2_length->displayText().toUShort();
    settings.stress_1_length = ui->stress_1_length->displayText().toUShort();
    settings.stress_2_length = ui->stress_2_length->displayText().toUShort();
    if(false)
        return;
    ui->tabWidget->setCurrentIndex(2);
    parser->setConsole(ui->run_console, false);
    log->LogEvent(QString("Connected Parser to Console"));
    parser->setSerialInterface(settings.port_name);
    parser->writeMessage(QString("run"));
    // something to send the start message, start parser as well probably
}

void MainWindow::startDebugEval()
{
    settings.port_name = ui->serial_port_lineEdit->displayText();
    settings.csv_file_location = ui->csv_file_loc->displayText();
    if(settings.port_name.isNull()||settings.csv_file_location.isNull())
        return;
    // set up csv file here
    ui->tabWidget->setCurrentIndex(3);
    parser->setConsole(ui->debug_console, true);
    log->LogEvent(QString("Connected Parser to Debug Console"));
    parser->setSerialInterface(settings.port_name);
    log->LogEvent(QString("Started Serial Interface"));
    // starts debug interface object here
}


void MainWindow::updatePlot(QVector<double>& time,
QVector<double>& ecg_diff, QVector<double>& pcg_avg, QVector<double>& stress)
{
    ui->ecg_plot->graph(0)->setData(time, ecg_diff);
    // give the axes some labels:
    ui->ecg_plot->xAxis->setLabel("Time");
    ui->ecg_plot->yAxis->setLabel("ECG Diff");
    // set axes ranges, so we see all data:
    /*customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);*/
    ui->ecg_plot->replot();

    ui->pcg_plot->graph(0)->setData(time, pcg_avg);
    // give the axes some labels:
    ui->pcg_plot->xAxis->setLabel("Time");
    ui->pcg_plot->yAxis->setLabel("PCG Average");
    // set axes ranges, so we see all data:
    /*customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);*/
    ui->pcg_plot->replot();

    ui->stress_plot->graph(0)->setData(time, stress);
    // give the axes some labels:
    ui->stress_plot->xAxis->setLabel("Time");
    ui->stress_plot->yAxis->setLabel("Stress");
    // set axes ranges, so we see all data:
    /*customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);*/
    ui->stress_plot->replot();
}
