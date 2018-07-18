/********************************************************************************
** Form generated from reading UI file 'ipsetting.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPSETTING_H
#define UI_IPSETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *Save;
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

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(404, 317);
        Save = new QPushButton(Form);
        Save->setObjectName(QString::fromUtf8("Save"));
        Save->setGeometry(QRect(320, 270, 81, 44));
        QFont font;
        font.setPointSize(28);
        Save->setFont(font);
        formLayoutWidget = new QWidget(Form);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 0, 401, 271));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        labelIPaddress = new QLabel(formLayoutWidget);
        labelIPaddress->setObjectName(QString::fromUtf8("labelIPaddress"));
        labelIPaddress->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, labelIPaddress);

        lineEditIPaddress = new QLineEdit(formLayoutWidget);
        lineEditIPaddress->setObjectName(QString::fromUtf8("lineEditIPaddress"));
        lineEditIPaddress->setFont(font);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditIPaddress);

        labelNetmask = new QLabel(formLayoutWidget);
        labelNetmask->setObjectName(QString::fromUtf8("labelNetmask"));
        labelNetmask->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, labelNetmask);

        lineEditNetmask = new QLineEdit(formLayoutWidget);
        lineEditNetmask->setObjectName(QString::fromUtf8("lineEditNetmask"));
        lineEditNetmask->setFont(font);

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditNetmask);

        labelGateway = new QLabel(formLayoutWidget);
        labelGateway->setObjectName(QString::fromUtf8("labelGateway"));
        labelGateway->setFont(font);

        formLayout->setWidget(3, QFormLayout::LabelRole, labelGateway);

        lineEditGateway = new QLineEdit(formLayoutWidget);
        lineEditGateway->setObjectName(QString::fromUtf8("lineEditGateway"));
        lineEditGateway->setFont(font);

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditGateway);

        labelDNS = new QLabel(formLayoutWidget);
        labelDNS->setObjectName(QString::fromUtf8("labelDNS"));
        labelDNS->setFont(font);

        formLayout->setWidget(5, QFormLayout::LabelRole, labelDNS);

        lineEditDNS = new QLineEdit(formLayoutWidget);
        lineEditDNS->setObjectName(QString::fromUtf8("lineEditDNS"));
        lineEditDNS->setFont(font);

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEditDNS);

        comboBoxIP = new QComboBox(formLayoutWidget);
        comboBoxIP->setObjectName(QString::fromUtf8("comboBoxIP"));
        comboBoxIP->setFont(font);

        formLayout->setWidget(0, QFormLayout::SpanningRole, comboBoxIP);

        comboBoxDNS = new QComboBox(formLayoutWidget);
        comboBoxDNS->setObjectName(QString::fromUtf8("comboBoxDNS"));
        comboBoxDNS->setFont(font);

        formLayout->setWidget(4, QFormLayout::SpanningRole, comboBoxDNS);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        Save->setText(QApplication::translate("Form", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        labelIPaddress->setText(QApplication::translate("Form", "IP     \345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        labelNetmask->setText(QApplication::translate("Form", "\345\255\220\347\275\221\346\216\251\347\240\201", 0, QApplication::UnicodeUTF8));
        labelGateway->setText(QApplication::translate("Form", "\351\273\230\350\256\244\347\275\221\345\205\263", 0, QApplication::UnicodeUTF8));
        labelDNS->setText(QApplication::translate("Form", "DNS        ", 0, QApplication::UnicodeUTF8));
        comboBoxIP->clear();
        comboBoxIP->insertItems(0, QStringList()
         << QApplication::translate("Form", "\350\207\252\345\212\250\350\216\267\345\276\227IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Form", "\344\275\277\347\224\250\344\270\213\351\235\242\347\232\204IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
        );
        comboBoxDNS->clear();
        comboBoxDNS->insertItems(0, QStringList()
         << QApplication::translate("Form", "\350\207\252\345\212\250\350\216\267\345\276\227DNS\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Form", "\344\275\277\347\224\250\344\270\213\351\235\242\347\232\204DNS\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPSETTING_H
