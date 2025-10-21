#pragma once

#include "enums.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

    void SetDigitKeyCallback(std::function<void(int key)> cb);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

private slots:

    void on_cmb_controller_currentIndexChanged();

    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();

    void on_btn_mem_clear_clicked();
    void on_btn_mem_read_clicked();
    void on_btn_mem_save_clicked();

    void on_tb_extra_clicked();
    void on_btn_backspace_clicked();

    void on_btn_clear_clicked();
    void on_btn_sign_change_clicked();

    void on_btn_add_clicked();

    void on_btn_sub_clicked();

    void on_btn_mul_clicked();

    void on_btn_div_clicked();

    void on_btn_pow_clicked();

    void on_btn_result_clicked();

private:
    Ui::MainWindow* ui;
    std::function<void(int key)> digit_cb_;
    std::function<void(Operation key)> operation_cb_;
    std::function<void(ControlKey key)> control_cb_;
    std::function<void(ControllerType controller)> controller_cb_;

};

