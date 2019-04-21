#ifndef FIRSTWINDOWCONFIG_H
#define FIRSTWINDOWCONFIG_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QFont>

class FirstWindowConfig: public QDialog{
Q_OBJECT
    QLabel *welcome;
    QLabel *questionUp;
    QPushButton *yesUpConfig;
    QPushButton *noUpConfig;
    QPushButton *quit;
    QVBoxLayout * verticalUpBox;
    QLabel *student;

private slots:
    void launchWindowChoice();
     void launchWindowChoiceConfig();
public:
   explicit FirstWindowConfig( QWidget* parent = 0);
};

#endif // FIRSTWINDOWCONFIG_H
