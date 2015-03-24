#include "ubled_gui.h"

Ubled_GUI::Ubled_GUI(Shared_Memory *shared_memory)
{
    this->shared_memory = shared_memory;
    mainlayout = new QGridLayout();

    button_NUbled = new QPushButton("Continue");
    label_NUbled = new QLabel("N Ubled: ");
    spinNUbled = new QSpinBox();

    spinNUbled->setValue(2);

    mainlayout->addWidget(label_NUbled, 0, 0);
    mainlayout->addWidget(spinNUbled, 0, 1);
    mainlayout->addWidget(button_NUbled, 0, 2);

    setLayout(mainlayout);

    connect(button_NUbled, SIGNAL(clicked()), this, SLOT(on_button_NUbled_clicked()));

    N_UBLED = 0;

    show();
}

void Ubled_GUI::on_button_NUbled_clicked()
{
    connect(button_NUbled, SIGNAL(clicked()), this, SLOT(on_button_NUbled_clicked()));

    N_UBLED = spinNUbled->value();

    QLayoutItem* item;
    while((item=mainlayout->takeAt(0))){
        if(item->widget()){
            delete item->widget();
        }
        delete item;
    }

    int row = 0;
    int colum =0;
    for(int i = 0; i < N_UBLED; i++){
        QComboBox* combo_box = new QComboBox();
        QLabel* label_led = new QLabel(QString("Led %1: ").arg(i+1));
        combo_box->addItem("Red"); //21
        combo_box->addItem("Blue"); //7
        combo_box->addItem("Green"); //6
        combo_box->addItem("Yellow"); //14
        combo_box->addItem("Purple"); //15
        combo_box->addItem("Blue Green"); //17
        combo_box->addItem("Red blinking"); //19
        combo_box->addItem("Blue blinking"); //10
        combo_box->addItem("Green blinking"); //9
        combo_box->addItem("Yellow blinking"); // 2
        mainlayout->addWidget(label_led, row, colum);
        mainlayout->addWidget(combo_box, row, colum+1);
        colum = colum + 2;
        if(i==4){
            row++;
            colum=0;
        }
        combobox_list.push_back(combo_box);
        connect(combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_changed()));
    }
}

void Ubled_GUI::on_comboBox_changed()
{
    std::vector<int> ubled_status;

    for(int i = 0; i < N_UBLED; i++){

        int index = 0;
        if(combobox_list[i]->currentText()==QString("Red"))
            index =21;
        if(combobox_list[i]->currentText()==QString("Blue"))
            index = 7;
        if(combobox_list[i]->currentText()==QString("Green"))
            index = 6;
        if(combobox_list[i]->currentText()==QString("Yellow"))
            index =14;
        if(combobox_list[i]->currentText()==QString("Purple"))
            index= 15;
        if(combobox_list[i]->currentText()==QString("Blue Green"))
            index = 17;
        if(combobox_list[i]->currentText()==QString("Red blinking"))
            index = 19;
        if(combobox_list[i]->currentText()==QString("Blue blinking"))
            index = 10;
        if(combobox_list[i]->currentText()==QString("Green blinking"))
            index = 9;
        if(combobox_list[i]->currentText()==QString("Yellow blinking"))
            index = 2;

        ubled_status.push_back(index );
    }
    shared_memory->setUbled_status(ubled_status);
}
