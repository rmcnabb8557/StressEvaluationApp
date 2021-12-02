#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "serialinterface.h"
#include "logger.h"
#include "parser.h"
#include "csvwriter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Logger *log;

private:
    Ui::MainWindow *ui;
    Parser *parser;
    CSVWriter m_csv;
    QTimer *runTimer;
    QTimer *syncTimer;
    //SerialInterface *serial;
    struct PortSettings{
        QString port_name;
        QString csv_file_location;
        quint8  rest_1_length;
        quint8  rest_2_length;
        quint8  stress_1_length;
        quint8  stress_2_length;
    };
    PortSettings settings = {
        "", "", 0, 0, 0, 0
    };

    QVector<double> v_time;
    QVector<double> v_ecg_diff;
    QVector<double> v_pcg_avg;
    QVector<double> v_stress;

private slots:
    void setupTab();
    void setupDebugTab();
    void startRunEval();
    void startDebugEval();
    void updatePlot(quint64 time,
                    qint16 ecg_diff, quint16 pcg_avg);
    void sendSyncMessage();
    void updateClock();
};
#endif // MAINWINDOW_H
