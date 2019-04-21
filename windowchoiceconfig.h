#ifndef WINDOWCHOICECONFIG_H
#define WINDOWCHOICECONFIG_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QFont>
#include <QTextEdit>

class windowChoiceConfig: public QDialog{
Q_OBJECT
   QLabel *questionUp;

    QPushButton *quit;
    //Partie sauvegarde
    QTextEdit* browse;
    QPushButton* import;
    QPushButton* xport;
    QVBoxLayout *vbox;
    QHBoxLayout *hbox;

private slots:
    void launchSomething();
public:
   explicit windowChoiceConfig( QWidget* parent = 0);
};

#endif // WINDOWCHOICECONFIG_H
