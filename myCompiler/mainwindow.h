#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void open();

private:
    Ui::MainWindow *ui;
    QString curFile;
    void setCurrentFile(const QString &fileName);
    bool saveCode(const QString fileName);
    bool save();
    bool saveAs();
    void loadCode(const int choice, const QString fileName);
    bool readUserInput(const QString fileName);
};
#endif // MAINWINDOW_H
