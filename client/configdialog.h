#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QSettings>


class ConfigDialog: public QDialog
{
    Q_OBJECT

private:
    QGridLayout *m_gridLayout;
    QLabel *m_serverLabel;
    QLabel *m_portLabel;
    QLabel *m_callPortLabel;
    QLabel *m_certLabel;
    QLineEdit *m_serverInput;
    QLineEdit *m_portInput;
    QLineEdit *m_callPortInput;
    QTextEdit *m_certInput;
    QPushButton *m_applyButton;

public:
    ConfigDialog(QWidget *parent);

    void setupUI();
    void retranslateUI();

public slots:
    void apply();
    void show();

};

#endif
