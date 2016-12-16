#include "configdialog.h"


ConfigDialog::ConfigDialog(QWidget *parent): QDialog(parent)
{
    setupUI();
}


void ConfigDialog::setupUI()
{
    setObjectName("ConfigDialog");

    m_gridLayout = new QGridLayout(this);

    m_serverLabel = new QLabel(this);
    m_portLabel = new QLabel(this);
    m_callPortLabel = new QLabel(this);
    m_certLabel = new QLabel(this);

    m_serverInput = new QLineEdit(this);
    m_portInput = new QLineEdit(this);
    m_callPortInput = new QLineEdit(this);
    m_certInput = new QTextEdit(this);

    m_applyButton = new QPushButton(this);

    m_gridLayout->addWidget(m_serverLabel, 0, 0, 1, 1);
    m_gridLayout->addWidget(m_serverInput, 0, 1, 1, 1);
    m_gridLayout->addWidget(m_portLabel, 1, 0, 1, 1);
    m_gridLayout->addWidget(m_portInput, 1, 1, 1, 1);
    m_gridLayout->addWidget(m_callPortLabel, 2, 0, 1, 1);
    m_gridLayout->addWidget(m_callPortInput, 2, 1, 1, 1);
    m_gridLayout->addWidget(m_certLabel, 3, 0, 1, 1);
    m_gridLayout->addWidget(m_certInput, 3, 1, 1, 1);
    m_gridLayout->addWidget(m_applyButton, 4, 0, 1, 2);

    connect(m_applyButton, &QPushButton::pressed, this, &ConfigDialog::apply);

    retranslateUI();
}


void ConfigDialog::retranslateUI()
{
    setWindowTitle(QApplication::translate("ConfigDialog", "Configure", 0));
    m_serverLabel->setText(QApplication::translate("ConfigDialog", "Server", 0));
    m_portLabel->setText(QApplication::translate("ConfigDialog", "Port", 0));
    m_callPortLabel->setText(QApplication::translate("ConfigDialog", "Call Port", 0));
    m_certLabel->setText(QApplication::translate("ConfigDialog", "Cert", 0));
    m_applyButton->setText(QApplication::translate("ConfigDialog", "Apply", 0));
}


void ConfigDialog::apply()
{
    QSettings settings;
    settings.setValue("server", m_serverInput->text());
    settings.setValue("port", m_portInput->text());
    settings.setValue("callport", m_callPortInput->text());
    settings.setValue("cert", m_certInput->toPlainText());
    close();
}


void ConfigDialog::show()
{
    QSettings settings;
    m_serverInput->setText(settings.value("server").toString());
    m_portInput->setText(settings.value("port").toString());
    m_callPortInput->setText(settings.value("callport").toString());
    m_certInput->setText(settings.value("cert").toString());
    QDialog::show();
}
