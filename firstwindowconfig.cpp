
#include "mainwindow2D.h"
#include "firstwindowconfig.h"
#include "windowchoice.h"
#include "firstwindow2d.h"

#include "windowchoiceconfig.h"

FirstWindowConfig::FirstWindowConfig(QWidget* parent):QDialog(parent){
    welcome=new QLabel("Bienvenue sur notre projet AutoCell !\n\n", this);
    QFont f( "Arial", 15, QFont::Bold);
    welcome->setFont(f);
    questionUp=new QLabel("Souhaitez vous charger une configuration ?\n\n", this);
    yesUpConfig=new QPushButton("Oui", this);
    QObject::connect(yesUpConfig, SIGNAL(clicked()), this, SLOT(launchWindowChoiceConfig()));

    noUpConfig=new QPushButton("Non, choisir directement un automate.", this);
    QObject::connect(noUpConfig, SIGNAL(clicked()), this, SLOT(launchWindowChoice()));


    quit=new QPushButton("Quitter", this);
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));


    student=new QLabel("\nProjet réalisé par :\n\nGRANDINIER Maxime\nNATANELIC Béranger\nTU Anh", this);
    verticalUpBox=new QVBoxLayout;

    verticalUpBox->addWidget(welcome);
    verticalUpBox->addWidget(questionUp);

    verticalUpBox->addWidget(yesUpConfig);
    verticalUpBox->addWidget(noUpConfig);
    verticalUpBox->addWidget(quit);

    verticalUpBox->addWidget(student);

    this->setLayout(verticalUpBox);

}

void FirstWindowConfig::launchWindowChoice(){
    hide();

   WindowChoice wind(this);
   wind.setModal(true);//On est jamais trop prudent
   wind.exec();
}
void FirstWindowConfig::launchWindowChoiceConfig(){
    hide();

   windowChoiceConfig wind(this);
   wind.setModal(true);//On est jamais trop prudent
   wind.exec();
}
