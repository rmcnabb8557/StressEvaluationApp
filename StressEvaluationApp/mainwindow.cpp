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
    log->setFileName(QString("log_" + now.currentDate().toString() + ".txt"));
    parser = new Parser(log);
    ui->debug_console->setLog(log);
    ui->run_console->setLog(log);
    m_csv.setFileName(QString(QString("data_" + now.currentDate().toString() + ".csv")));
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
    log->logEvent(QString("Transitioned to Setup Tab for Run Start"));
}

void MainWindow::setupDebugTab()
{
    ui->tabWidget->setCurrentIndex(1);
    connect(ui->stressStart_button, SIGNAL(clicked()), this, SLOT(startDebugEval()));
    log->logEvent(QString("Transitioned to Setup Tab for Debug Start"));
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
    log->logEvent(QString("Connected Parser to Console"));
    parser->setSerialInterface(settings.port_name);
    connect(parser, SIGNAL(dataUpdate(quint64,qint16,quint16)),
            this, SLOT(updatePlot(quint64,qint16,quint16)));
    //parser->writeMessage(QString("sync"));
    syncTimer = new QTimer(this);
    connect(syncTimer, &QTimer::timeout, this, &MainWindow::sendSyncMessage);
    syncTimer->start(120000);
    runTimer = new QTimer(this);
    connect(runTimer, &QTimer::timeout, this, &MainWindow::updateClock);
    runTimer->start(1000);
    parser->writeMessage(QString("run")); //                                         fix this
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
    log->logEvent(QString("Connected Parser to Debug Console"));
    parser->setSerialInterface(settings.port_name);
    log->logEvent(QString("Started Serial Interface"));
    // starts debug interface object here
}


void MainWindow::updatePlot(quint64 time,
qint16 ecg_diff, quint16 pcg_diff)
{
    quint8 ecg_state = 0;
    quint8 ecg_out = 0;
    quint8 pcg_state = 0;
    quint8 pcg_out = 0;
    double rmssd = 0;
    double latency_avg = 0;
    double hr = 0;
    double stress = 0;

    v_time.append(double(time));
    v_ecg_diff.append(double(ecg_diff));
    v_pcg_avg.append(double(pcg_diff));
    v_stress.append(double(pcg_diff));
    if(v_time.size() > 1000)
    {
       v_time.removeFirst();
       v_ecg_diff.removeFirst();
       v_pcg_avg.removeFirst();
       v_stress.removeFirst();
    }
    ui->ecg_plot->addGraph();
    ui->ecg_plot->graph(0)->setData(v_time, v_ecg_diff);
    // give the axes some labels:
    ui->ecg_plot->xAxis->setLabel("Time");
    ui->ecg_plot->yAxis->setLabel("ECG Diff");
    // set axes ranges, so we see all data:
    ui->ecg_plot->xAxis->setRange(v_time.first(), v_time.last());
    ui->ecg_plot->yAxis->setRange(-32768, 32767);
    ui->ecg_plot->replot();

    ui->pcg_plot->addGraph();
    ui->pcg_plot->graph(0)->setData(v_time, v_pcg_avg);
    // give the axes some labels:
    ui->pcg_plot->xAxis->setLabel("Time");
    ui->pcg_plot->yAxis->setLabel("PCG Average");
    // set axes ranges, so we see all data:
    ui->pcg_plot->xAxis->setRange(v_time.first(), v_time.last());
    ui->pcg_plot->yAxis->setRange(0, 65536);
    ui->pcg_plot->replot();

    ui->stress_plot->addGraph();
    ui->stress_plot->graph(0)->setData(v_time, v_stress);
    // give the axes some labels:
    ui->stress_plot->xAxis->setLabel("Time");
    ui->stress_plot->yAxis->setLabel("Stress");
    // set axes ranges, so we see all data:
    ui->stress_plot->xAxis->setRange(v_time.first(), v_time.last());
    ui->stress_plot->yAxis->setRange(-32768, 32767);
    ui->stress_plot->replot();
    m_csv.logEvent(QString::number(time)    + QString(",") +
                   QString::number(ecg_diff)        + QString(",") +
                   QString::number(ecg_state)       + QString(",") +
                   QString::number(ecg_out)         + QString(",") +
                   QString::number(pcg_diff)        + QString(",") +
                   QString::number(pcg_state)       + QString(",") +
                   QString::number(pcg_out)         + QString(",") +
                   QString::number(rmssd)       + QString(",") +
                   QString::number(latency_avg) + QString(",") +
                   QString::number(hr)          + QString(",") +
                   QString::number(stress));
}

void MainWindow::sendSyncMessage(){
    parser->writeMessage(QString("sync"));
}

void MainWindow::updateClock(){
    static uint16_t time_secs = 0;
    static QTime clockTime = QTime();
    ui->run_timeEdit->setTime(clockTime.addSecs(1));
    time_secs++;
    if(time_secs < (settings.rest_1_length)*60)
    {
        ui->run_status_label->setText("Rest Period 1");
    }
    else if(time_secs < (settings.rest_1_length + settings.stress_1_length)*60)
    {
        ui->run_status_label->setText("Stress Period 1");
    }
    else if(time_secs < (settings.rest_1_length + settings.stress_1_length + settings.rest_2_length)*60)
    {
        ui->run_status_label->setText("Rest Period 2");
    }
    else if(time_secs < (settings.rest_1_length + settings.stress_1_length +
                         settings.rest_2_length + settings.stress_2_length)*60)
    {
        ui->run_status_label->setText("Stress Period 2");
    }
    else
    {
        runTimer->stop();
        syncTimer->stop();

    }
}
