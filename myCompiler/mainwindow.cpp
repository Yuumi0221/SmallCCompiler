#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->browser, &QPushButton::clicked, this, [=](){
        open();
    });

    connect(ui->save, &QPushButton::clicked, this, [=](){
        save();
    });

    connect(ui->saveAs, &QPushButton::clicked, this, [=](){
        saveAs();
    });

    connect(ui->compile, &QPushButton::clicked, this, [=](){
        saveCode("c_o_d_e.txt");
        readUserInput("finput.txt");

        QString command = "./smallC.exe";

        QProcess p(0);
        p.start(command);
        p.waitForFinished();

        loadCode(1, "foutput.txt");
        loadCode(2, "fcode.txt");
        loadCode(3, "ftable.txt");
        loadCode(4, "fresult.txt");
    });
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
        loadCode(0, fileName);
}

void MainWindow::loadCode(const int choice, const QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MyCompiler"), tr("Cannot read file %1:\n%2.")
                .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    if(!fileName.isEmpty() && fileName!="foutput.txt" && fileName!="fcode.txt" && fileName!="ftable.txt" && fileName!="fresult.txt" && fileName!="finput.txt" && fileName!="c_o_d_e.txt")
        setCurrentFile(fileName);

//    qDebug() << curFile;

    QTextStream in(&file);

    QPlainTextEdit * text = NULL;

    switch(choice){
    case 0:
        text = ui->input;
        break;
    case 1:
        text = ui->success;
        break;
    case 2:
        text = ui->instructions;
        break;
    case 3:
        text = ui->table;
        break;
    case 4:
        text = ui->result;
        break;
    default:
        text = ui->input;
        break;
    }

    text->setPlainText(in.readAll());
    file.close();
}

bool MainWindow::readUserInput(const QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MyCompiler"), tr("Cannot read file %1:\n%2.")
                .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->userInput->toPlainText();
    file.close();
    return true;
}

bool MainWindow::saveCode(const QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MyCompiler"), tr("Cannot read file %1:\n%2.")
                .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->input->toPlainText();
    file.close();
    if(!fileName.isEmpty() && fileName!="c_o_d_e.txt")
        setCurrentFile(fileName);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName) {
    curFile = fileName;
    ui->input->document()->setModified(false);

    QString shownName = curFile;
    if(curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

bool MainWindow::save() {
    if(curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveCode(curFile);
    }
}

bool MainWindow::saveAs(){
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if(dialog.exec() != QDialog::Accepted)
        return false;
    return saveCode(dialog.selectedFiles().first());
}

MainWindow::~MainWindow()
{
    delete ui;
}

