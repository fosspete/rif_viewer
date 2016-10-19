#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <QList>
#include "rifparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_actionOpen_RIF_triggered();

    void on_buttonParseXml_clicked();

    void on_actionExport_CVS_triggered();

    void on_reqListWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_searchButton_clicked();

    void on_searchLineEdit_returnPressed();

    void on_searchLineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QString filename;
    QXmlStreamReader xml;
    QList <int> specList;
    RifParser theParser;

};

#endif // MAINWINDOW_H
