#include "windowchoiceconfig.h"

#include "mainwindow2D.h"
#include "firstwindowconfig.h"
#include "windowchoice.h"
#include "firstwindow2d.h"

windowChoiceConfig::windowChoiceConfig(QWidget* parent):QDialog(parent){

    questionUp=new QLabel("Importez votre configuration :\n\n", this);

    quit=new QPushButton("Quitter", this);
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));


    //Partie sauvegarde

    browse=new QTextEdit("C://Documents/blabla.uml",this);
    browse->setMaximumHeight(30);

    //  METTRE ICI LE CONNECT QUAND TU VEUX CHERCHER DANS LES DOCS valueChanged() ou qqch comme ça

    import=new QPushButton("Importer un état");

    xport=new QPushButton("Sauvegarder l'état");

    vbox=new QVBoxLayout;
    hbox=new QHBoxLayout;

    vbox->addWidget(questionUp);

   hbox->addWidget(browse);
   hbox->addWidget(import);
   hbox->addWidget(xport);
    vbox->addLayout(hbox);
    vbox->addWidget(quit);


    this->setLayout(vbox);

}

void windowChoiceConfig::launchSomething(){
    hide();

   FirstWindowConfig wind(this);
   wind.setModal(true);//On est jamais trop prudent
   wind.exec();
}
