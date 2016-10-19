#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <rifparser.h>
#include <requirementlist.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->buttonParseXml->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_RIF_triggered()
{
   filename = QFileDialog::getOpenFileName(this, tr("Open RIF"), "c:", tr("Image Files (*.xml)"));
   qDebug()<< "filename = " << filename <<"\n";
   RequirementList *reqList = theParser.getReqList();
   if(reqList != NULL)
   {
       reqList->Clear();
       ui->reqListWidget->setRowCount(0);
   }
   this->on_buttonParseXml_clicked();
}

void MainWindow::on_buttonParseXml_clicked()
{
    QFile xmlFile(this->filename);

    if(this->filename != "")
    {

        xmlFile.open(QIODevice::ReadOnly);
        xml.setDevice(&xmlFile);

        int nbrOfXmlElements = 0;

        xmlFile.open(QIODevice::ReadOnly);
        xml.setDevice(&xmlFile);

        while (xml.atEnd() == false && xml.readNext()  )
        {
            nbrOfXmlElements ++;
            if(xml.isStartElement())
            {
                theParser.parseElement(xml.name().toString(), &xml);
            }
        }

        bool finished = false;
        RequirementList *reqList = theParser.getReqList();

        reqList->GoToStart();
        while (!finished)
        {
            QString temp = reqList->GetNameOfReq();
            this->ui->reqListWidget->insertRow(ui->reqListWidget->rowCount());
            this->ui->reqListWidget->setItem(ui->reqListWidget->rowCount()-1, 0, new QTableWidgetItem(reqList->GetClassOfReq()));
            this->ui->reqListWidget->setItem(ui->reqListWidget->rowCount()-1, 1, new QTableWidgetItem(reqList->GetIdOfReq()));
            this->ui->reqListWidget->setItem(ui->reqListWidget->rowCount()-1, 2, new QTableWidgetItem(temp));

            if (reqList->GoToNextReqId("") == "")
            {
                finished = true;
            }
        }
    }
}


void MainWindow::on_actionExport_CVS_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save file", "", ".csv");

    RequirementList *reqList = theParser.getReqList();

    reqList->SaveToCSV(filename);
}


void MainWindow::on_reqListWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    qDebug()<< "on_reqListWidget_currentCellChanged, currentRow= "<<currentRow;

    if(currentRow >=0)
    {
        QString reqid = ui->reqListWidget->item(currentRow, 1)->text();

        RequirementList *reqList = theParser.getReqList();

        if(reqList->GoToReqWithID(reqid)!="")
        {
            // requirment was found
            ui->reqText->document()->setPlainText(reqList->GetTextOfReq());
        }
        ui->reqProperties->setRowCount(0);

        ui->reqProperties->insertRow(ui->reqProperties->rowCount());
        ui->reqProperties->setItem(ui->reqProperties->rowCount()-1, 0,new QTableWidgetItem("Requirement state"));
        ui->reqProperties->setItem(ui->reqProperties->rowCount()-1, 1, new QTableWidgetItem(reqList->GetStateOfReq()));

        ui->reqProperties->insertRow(ui->reqProperties->rowCount());
        ui->reqProperties->setItem(ui->reqProperties->rowCount()-1, 0,new QTableWidgetItem("Revision"));
        ui->reqProperties->setItem(ui->reqProperties->rowCount()-1, 1, new QTableWidgetItem(reqList->GetRevOfReq()));
    }
}

void MainWindow::on_searchButton_clicked()
{
    QString searchstring = ui->searchLineEdit->text();

    ui->reqListWidget->setRowCount(0);

    bool finished = false;
    RequirementList *reqList = theParser.getReqList();

    reqList->GoToStart();
    if (reqList->GoToNextReqId(searchstring) == "")
    {
        finished = true;
    }

    while (!finished)
    {
        QString temp = reqList->GetNameOfReq();
        this->ui->reqListWidget->insertRow(ui->reqListWidget->rowCount());
        this->ui->reqListWidget->setItem(ui->reqListWidget->rowCount()-1, 0, new QTableWidgetItem(reqList->GetClassOfReq()));
        this->ui->reqListWidget->setItem(ui->reqListWidget->rowCount()-1, 1, new QTableWidgetItem(reqList->GetIdOfReq()));
        this->ui->reqListWidget->setItem(ui->reqListWidget->rowCount()-1, 2, new QTableWidgetItem(temp));

        if (reqList->GoToNextReqId(searchstring) == "")
        {
            finished = true;
        }
    }
}

void MainWindow::on_searchLineEdit_returnPressed()
{
    this->on_searchButton_clicked();
}

void MainWindow::on_searchLineEdit_textChanged(const QString &arg1)
{
    this->on_searchButton_clicked();
}
