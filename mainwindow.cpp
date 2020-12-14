#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "htable.h"
#include "elem.h"
#include "QTableWidget"

#define name_of_enter_file "C:\\Users\\Ivan\\Desktop\\input_int.txt"
#define name_of_out_file "C:\\Users\\Ivan\\Desktop\\output_int.txt"

HTable<string> ht;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::vision(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::vision(bool v){
    ui->pushButton_2->setVisible(v);
    ui->pushButton_4->setVisible(v);
    ui->pushButton_5->setVisible(v);
    ui->pushButton_6->setVisible(v);
    ui->lineEdit_2->setVisible(v);
    ui->lineEdit_4->setVisible(v);
    ui->lineEdit_5->setVisible(v);
    ui->lineEdit_6->setVisible(v);
    ui->label->setVisible(v);
    ui->label_2->setVisible(v);
    ui->tableWidget->setVisible(v);
}

void MainWindow::click(){
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(ht.get_size());
    int k = 0;
    for (auto i = 0; i<def_size; i++){
        auto string_for_set = ht.get_mas_i(i).get_key();
        if (string_for_set != ""){
            QLabel *label = new QLabel(ui->tableWidget);
            label->setText(string_for_set.c_str());
            ui->tableWidget->setCellWidget(0, k, label);
            QLabel *label_v = new QLabel(ui->tableWidget);
            string ss = to_string(ht.get_mas_i(i).get_value());
            label_v->setText(ss.c_str());
            ui->tableWidget->setCellWidget(1, k, label_v);
            k++;
        }
    }
}


void MainWindow::on_pushButton_clicked() //считывание из файла
{
    ht.read_from_file(name_of_enter_file);
    MainWindow::click();
    MainWindow::vision(true);
}

void MainWindow::on_pushButton_2_clicked() //запись в файл
{
    ht.write_to_file(name_of_out_file);
}

void MainWindow::on_pushButton_3_clicked() //добавление элемента
{
    auto string_key = ui->lineEdit_3->text().toStdString();
    ht << string_key;
    ui->lineEdit_3->setText("");
    MainWindow::click();
    MainWindow::vision(true);
}

void MainWindow::on_pushButton_4_clicked() //удаление элемента
{
    auto string_key = ui->lineEdit_4->text().toStdString();
    try {
        ht.del_element(string_key);
        ui->lineEdit_4->setText("Element was deleted");
        MainWindow::click();
        if (ht.get_size() == 0){
            MainWindow::vision(false);
        }
    }
    catch (out_of_range& er) {
        ui->lineEdit_4->setText("Error: Referring to a non-existent key");
    }
}

void MainWindow::on_pushButton_5_clicked() //получение минимума
{
    auto min = ht.get_min_mis();
    ui->lineEdit_5->setText(min.c_str());
}

void MainWindow::on_pushButton_6_clicked() // получение максимума
{
    auto max = ht.get_max_mis();
    ui->lineEdit_6->setText(max.c_str());
}

