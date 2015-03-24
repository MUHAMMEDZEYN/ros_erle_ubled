#ifndef UBLED_GUI_H
#define UBLED_GUI_H

#include <QtGui>
#include "shared_memory.h"

class Ubled_GUI: public QWidget
{
    Q_OBJECT
public:
    Ubled_GUI(Shared_Memory* shared_memory);
private:
    QGridLayout* mainlayout;
    QPushButton* button_NUbled;
    QSpinBox* spinNUbled;
    QLabel* label_NUbled;
    Shared_Memory* shared_memory;

    std::vector<QComboBox*> combobox_list;

    int N_UBLED;

public slots:
    void on_button_NUbled_clicked();
    void on_comboBox_changed();
};

#endif // UBLED_GUI_H
