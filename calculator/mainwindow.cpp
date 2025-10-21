#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setText(QString::fromStdString(text));
    ui->l_result->setStyleSheet("");
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setText(QString::fromStdString(text));
    ui->l_result->setStyleSheet("color: red;");
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}


void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if(key == std::nullopt){
        ui->tb_extra->setVisible(false);
    } else {
        ui->tb_extra->setText(QString::fromStdString(key.value()));
        ui->tb_extra->setVisible(true);
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb){
    digit_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb){
    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb){
    control_cb_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb){   
    controller_cb_ = cb;
}


void MainWindow::on_cmb_controller_currentIndexChanged() {
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");


    if (!controller_cb_) {
        return;
    }

    const auto& controller_name = ui->cmb_controller->currentText();

    if (controller_name == "double") {
        controller_cb_(ControllerType::DOUBLE);
    }
    else if (controller_name == "float") {
        controller_cb_(ControllerType::FLOAT);
    }
    else if (controller_name == "uint8_t") {
        controller_cb_(ControllerType::UINT8_T);
    }
    else if (controller_name == "int") {        
        controller_cb_(ControllerType::INT);
    }
    else if (controller_name == "int64_t") {
        controller_cb_(ControllerType::INT64_T);
    }
    else if (controller_name == "size_t") {
        controller_cb_(ControllerType::SIZE_T);
    }
    else if (controller_name == "Rational") {
        controller_cb_(ControllerType::RATIONAL);
    }
}


// Кнопки с цифрами
void MainWindow::on_btn_0_clicked() {
    digit_cb_(0);
}

void MainWindow::on_btn_1_clicked() {
    digit_cb_(1);
}

void MainWindow::on_btn_2_clicked() {
    digit_cb_(2);
}

void MainWindow::on_btn_3_clicked() {
    digit_cb_(3);
}

void MainWindow::on_btn_4_clicked() {
    digit_cb_(4);
}

void MainWindow::on_btn_5_clicked() {
    digit_cb_(5);
}

void MainWindow::on_btn_6_clicked() {
    digit_cb_(6);
}

void MainWindow::on_btn_7_clicked() {
    digit_cb_(7);
}

void MainWindow::on_btn_8_clicked() {
    digit_cb_(8);
}

void MainWindow::on_btn_9_clicked() {
    digit_cb_(9);
}


// Кнопка с точкой (теперь ещё и с дробью)
void MainWindow::on_tb_extra_clicked() {
    control_cb_(ControlKey::EXTRA_KEY);
}


// Память
void MainWindow::on_btn_mem_clear_clicked() {
    control_cb_(ControlKey::MEM_CLEAR);
}

void MainWindow::on_btn_mem_read_clicked() {
    control_cb_(ControlKey::MEM_LOAD);
}

void MainWindow::on_btn_mem_save_clicked() {
    control_cb_(ControlKey::MEM_SAVE);
}


//Кнопка "очистить"
void MainWindow::on_btn_clear_clicked() {
    control_cb_(ControlKey::CLEAR);  
}


//Backspace
void MainWindow::on_btn_backspace_clicked() {
    control_cb_(ControlKey::BACKSPACE);
}

//Смена знака
void MainWindow::on_btn_sign_change_clicked() {
    control_cb_(ControlKey::PLUS_MINUS);
}


//Операции
void MainWindow::on_btn_add_clicked() {
    operation_cb_(Operation::ADDITION);
}

void MainWindow::on_btn_sub_clicked() {
    operation_cb_(Operation::SUBTRACTION);
}

void MainWindow::on_btn_mul_clicked() {
    operation_cb_(Operation::MULTIPLICATION);
}

void MainWindow::on_btn_div_clicked() {
    operation_cb_(Operation::DIVISION);
}

void MainWindow::on_btn_pow_clicked() {
    operation_cb_(Operation::POWER);
}


// Результат
void MainWindow::on_btn_result_clicked() {
    control_cb_(ControlKey::EQUALS);
}
