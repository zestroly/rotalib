/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *labelIPaddress;
    QLineEdit *lineEditIPaddress;
    QLabel *labelNetmask;
    QLineEdit *lineEditNetmask;
    QLabel *labelGateway;
    QLineEdit *lineEditGateway;
    QLabel *labelDNS;
    QLineEdit *lineEditDNS;
    QComboBox *comboBoxIP;
    QComboBox *comboBoxDNS;
    QPushButton *Save;
    QWidget *tab_2;
    QPushButton *WifiScan;
    QPushButton *WifiSetting;
    QComboBox *WifiSSID;
    QLineEdit *WIFIPASS;
    QPushButton *Wifi_switch;
    QPushButton *pushButtonSocketWifiStatus;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButtonSocketWifiStatus_2;
    QPushButton *pushButtonSocketWifiStatus_3;
    QWidget *tab_4;
    QPushButton *pushButton_7;
    QWidget *tab_3;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QComboBox *comboBox_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(829, 480);
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 20, 791, 431));
        tabWidget->setBaseSize(QSize(0, 0));
        QFont font;
        font.setPointSize(28);
        tabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        formLayoutWidget = new QWidget(tab);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 481, 272));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        labelIPaddress = new QLabel(formLayoutWidget);
        labelIPaddress->setObjectName(QString::fromUtf8("labelIPaddress"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelIPaddress);

        lineEditIPaddress = new QLineEdit(formLayoutWidget);
        lineEditIPaddress->setObjectName(QString::fromUtf8("lineEditIPaddress"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditIPaddress);

        labelNetmask = new QLabel(formLayoutWidget);
        labelNetmask->setObjectName(QString::fromUtf8("labelNetmask"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelNetmask);

        lineEditNetmask = new QLineEdit(formLayoutWidget);
        lineEditNetmask->setObjectName(QString::fromUtf8("lineEditNetmask"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditNetmask);

        labelGateway = new QLabel(formLayoutWidget);
        labelGateway->setObjectName(QString::fromUtf8("labelGateway"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelGateway);

        lineEditGateway = new QLineEdit(formLayoutWidget);
        lineEditGateway->setObjectName(QString::fromUtf8("lineEditGateway"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditGateway);

        labelDNS = new QLabel(formLayoutWidget);
        labelDNS->setObjectName(QString::fromUtf8("labelDNS"));

        formLayout->setWidget(5, QFormLayout::LabelRole, labelDNS);

        lineEditDNS = new QLineEdit(formLayoutWidget);
        lineEditDNS->setObjectName(QString::fromUtf8("lineEditDNS"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEditDNS);

        comboBoxIP = new QComboBox(formLayoutWidget);
        comboBoxIP->setObjectName(QString::fromUtf8("comboBoxIP"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, comboBoxIP);

        comboBoxDNS = new QComboBox(formLayoutWidget);
        comboBoxDNS->setObjectName(QString::fromUtf8("comboBoxDNS"));

        formLayout->setWidget(4, QFormLayout::SpanningRole, comboBoxDNS);

        Save = new QPushButton(tab);
        Save->setObjectName(QString::fromUtf8("Save"));
        Save->setGeometry(QRect(400, 290, 81, 44));
        Save->setFont(font);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        WifiScan = new QPushButton(tab_2);
        WifiScan->setObjectName(QString::fromUtf8("WifiScan"));
        WifiScan->setGeometry(QRect(40, 270, 151, 81));
        WifiSetting = new QPushButton(tab_2);
        WifiSetting->setObjectName(QString::fromUtf8("WifiSetting"));
        WifiSetting->setGeometry(QRect(200, 270, 151, 81));
        WifiSSID = new QComboBox(tab_2);
        WifiSSID->setObjectName(QString::fromUtf8("WifiSSID"));
        WifiSSID->setGeometry(QRect(40, 180, 311, 41));
        WIFIPASS = new QLineEdit(tab_2);
        WIFIPASS->setObjectName(QString::fromUtf8("WIFIPASS"));
        WIFIPASS->setGeometry(QRect(40, 230, 311, 31));
        Wifi_switch = new QPushButton(tab_2);
        Wifi_switch->setObjectName(QString::fromUtf8("Wifi_switch"));
        Wifi_switch->setGeometry(QRect(40, 110, 311, 61));
        pushButtonSocketWifiStatus = new QPushButton(tab_2);
        pushButtonSocketWifiStatus->setObjectName(QString::fromUtf8("pushButtonSocketWifiStatus"));
        pushButtonSocketWifiStatus->setGeometry(QRect(510, 10, 261, 51));
        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(0, 10, 181, 41));
        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(190, 10, 241, 41));
        pushButtonSocketWifiStatus_2 = new QPushButton(tab_2);
        pushButtonSocketWifiStatus_2->setObjectName(QString::fromUtf8("pushButtonSocketWifiStatus_2"));
        pushButtonSocketWifiStatus_2->setGeometry(QRect(510, 70, 261, 51));
        pushButtonSocketWifiStatus_3 = new QPushButton(tab_2);
        pushButtonSocketWifiStatus_3->setObjectName(QString::fromUtf8("pushButtonSocketWifiStatus_3"));
        pushButtonSocketWifiStatus_3->setGeometry(QRect(510, 130, 261, 51));
        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        pushButton_7 = new QPushButton(tab_4);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(30, 20, 141, 61));
        tabWidget->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayoutWidget = new QWidget(tab_3);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 401, 141));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 3, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 2, 3, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 1, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        comboBox_2 = new QComboBox(gridLayoutWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 2, 2, 1, 1);

        pushButton_5 = new QPushButton(tab_3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(450, 20, 221, 71));
        pushButton_6 = new QPushButton(tab_3);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(450, 100, 221, 71));
        tabWidget->addTab(tab_3, QString());

        retranslateUi(Widget);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        labelIPaddress->setText(QApplication::translate("Widget", "IP     \345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        labelNetmask->setText(QApplication::translate("Widget", "\345\255\220\347\275\221\346\216\251\347\240\201", 0, QApplication::UnicodeUTF8));
        labelGateway->setText(QApplication::translate("Widget", "\351\273\230\350\256\244\347\275\221\345\205\263", 0, QApplication::UnicodeUTF8));
        labelDNS->setText(QApplication::translate("Widget", "DNS        ", 0, QApplication::UnicodeUTF8));
        comboBoxIP->clear();
        comboBoxIP->insertItems(0, QStringList()
         << QApplication::translate("Widget", "\350\207\252\345\212\250\350\216\267\345\276\227IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Widget", "\344\275\277\347\224\250\344\270\213\351\235\242\347\232\204IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
        );
        comboBoxDNS->clear();
        comboBoxDNS->insertItems(0, QStringList()
         << QApplication::translate("Widget", "\350\207\252\345\212\250\350\216\267\345\276\227DNS\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Widget", "\344\275\277\347\224\250\344\270\213\351\235\242\347\232\204DNS\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
        );
        Save->setText(QApplication::translate("Widget", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "\346\234\211\347\272\277\347\275\221\347\273\234", 0, QApplication::UnicodeUTF8));
        WifiScan->setText(QApplication::translate("Widget", "\346\211\253\346\217\217", 0, QApplication::UnicodeUTF8));
        WifiSetting->setText(QApplication::translate("Widget", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        WIFIPASS->setText(QString());
        Wifi_switch->setText(QApplication::translate("Widget", "Wifi\345\274\200", 0, QApplication::UnicodeUTF8));
        pushButtonSocketWifiStatus->setText(QApplication::translate("Widget", "wifi\350\277\236\346\216\245\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("Widget", "Wifi \345\274\200\345\205\263\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("Widget", "\346\211\253\346\217\217\345\267\262\351\205\215\347\275\256wifi", 0, QApplication::UnicodeUTF8));
        pushButtonSocketWifiStatus_2->setText(QApplication::translate("Widget", "wifi\345\257\206\347\240\201\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        pushButtonSocketWifiStatus_3->setText(QApplication::translate("Widget", "json To conf", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "Wifi\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("Widget", "scan", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Widget", "Bluetooth", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Widget", "\346\237\245\346\211\276", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "Progress  ", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Widget", "\346\235\200\346\255\273\350\277\233\347\250\213", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "PID", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("Widget", "Sys\345\261\217\345\271\225\346\240\241\345\207\206", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("Widget", "QT\345\261\217\345\271\225\346\240\241\345\207\206", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Widget", "SystemIO", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
