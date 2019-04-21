#include "mainwindow2D.h"
#include "firstwindowconfig.h"
#include "windowchoice.h"
#include "firstwindow2d.h"
#include "windowchoiceconfig.h"

#include <unistd.h>
#include "../jeuVie/jeuvie.h"

Window2D::Window2D(unsigned int size, unsigned int nbBorn, unsigned int nbMini, unsigned int nbMaxi , QWidget* parent):dimension(size),m_nbBorn(nbBorn), m_nbMini(nbMini), m_nbMaxi(nbMaxi),jeu(nbBorn,nbMini, nbMaxi ), state(dimension, dimension), QDialog(parent){
    stopOption =false;
    layout=new QHBoxLayout;

    time=1;
    timer =new QTimer(this);

int taille=25;

//Affichage et parametrage de la grille empty
simulation = new QTableWidget(dimension, dimension, this);
simulation->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
simulation->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
simulation->horizontalHeader()->setVisible(false); // masque le header horizontal
simulation->verticalHeader()->setVisible(false); // masque le header vertical
simulation->setSelectionMode(QAbstractItemView::NoSelection); //Enleve le rectanle bleu
simulation->setFixedHeight(dimension*taille);
simulation->setFixedWidth(dimension*taille);


//Créer chaque cellule item et creer le connect

for(unsigned int counterRow=0; counterRow<dimension; ++counterRow){
    for(unsigned int counter=0; counter<dimension; ++counter){
        simulation->setColumnWidth(counter, taille);
        simulation->setRowHeight(counterRow, taille);
      simulation->setItem(counterRow,counter, new QTableWidgetItem(""));
      simulation->item(counterRow, counter)->setBackgroundColor("white");
      simulation->item(counterRow, counter)->setTextColor("white");
    }
}
connect(simulation, SIGNAL(clicked(QModelIndex)), this,SLOT(launchActivation(QModelIndex)));


//Initialisation des différents boutons et organisation de la fenêtre

title1=new QLabel(this);
title1->setText("Execution manuelle");
title1->setFont(QFont("Arial", 10, QFont::Bold, false));


random=new QPushButton("Aléatoire", this);
QObject::connect(random, SIGNAL(clicked()), this, SLOT(launchRandom()));


oneByOne=new QPushButton("Coup par coup", this);
QObject::connect(oneByOne, SIGNAL(clicked()), this, SLOT(launchNext()));

clear=new QPushButton("Effacer", this);
QObject::connect(clear, SIGNAL(clicked()), this, SLOT(launchClear()));


title2=new QLabel(this);
title2->setText("Execution automatique");
title2->setFont(QFont("Arial", 10, QFont::Bold, false));

launch=new QPushButton("Lancer !", this);
QObject::connect(launch, SIGNAL(clicked()), this, SLOT(launchNonStop()));
QObject::connect(this,SIGNAL(iterationSignal()), this, SLOT(showTableSlot()));

stop=new QPushButton("Arrêt", this);
QObject::connect(stop, SIGNAL(clicked()), this, SLOT(launchStop()));

frequency=new QSpinBox(this);
frequency->setMinimum(0);
frequency->setValue(500);
frequency->setMaximum(10000);
QObject::connect(frequency, SIGNAL(valueChanged(int)), this, SLOT(launchChangingTime(int)));

chooseStep=new QLabel(this);
chooseStep->setText("Choisir le pas (milli-secondes)");

std::cout<<size<<std::endl;
title3=new QLabel(this);
title3->setText("Sauvegarde");
title3->setFont(QFont("Arial", 10, QFont::Bold, false));

//Partie sauvegarde

browse=new QTextEdit("C://Documents/blabla.uml",this);
browse->setMaximumHeight(30);
import=new QPushButton("Importer un état");
xport=new QPushButton("Sauvegarder l'état");


//Footer
quit=new QPushButton("Fenêtre d'accueil", this);
QObject::connect(quit, SIGNAL(clicked()), this, SLOT(launchHome()));

hboxMain = new QHBoxLayout;
vboxMain = new QVBoxLayout;
hboxMain->addWidget(simulation);

//Créer les titres sur la fenetre
ht1=new QHBoxLayout;
ht2=new QHBoxLayout;
ht3=new QHBoxLayout;
ht1->addWidget(title1);
ht2->addWidget(title2);
ht3->addWidget(title3);

hboxManual=new QHBoxLayout;
hboxManual->addWidget(random);
hboxManual->addWidget(oneByOne);
hboxManual->addWidget(clear);

hboxAuto=new QHBoxLayout;
hboxAuto->addWidget(chooseStep);
hboxAuto->addWidget(frequency);
hboxAuto->addWidget(launch);
hboxAuto->addWidget(stop);

hboxSave=new QHBoxLayout;
hboxSave->addWidget(browse);
hboxSave->addWidget(import);
hboxSave->addWidget(xport);

vboxMain->addLayout(ht1);
vboxMain->addLayout(hboxManual);
vboxMain->addLayout(ht2);
vboxMain->addLayout(hboxAuto);
vboxMain->addLayout(ht3);
vboxMain->addLayout(hboxSave);
vboxMain->addWidget(quit);

hboxMain->addLayout(vboxMain);

//layout->addWidget(hboxMain);
this->setLayout(hboxMain);


}

void Window2D::launchHome(){
    hide();

   FirstWindowConfig wind(this);
   wind.setModal(true);//On est jamais trop prudent
   wind.exec();
}



//Efface le contenu graphiquement
void Window2D::launchClear(){

    for(unsigned int counterRow=0; counterRow<dimension; ++counterRow){
        for(unsigned int counter=0; counter<dimension; ++counter){
    state.setCellule(counterRow, counter,false);
    simulation->item(counterRow, counter)->setBackgroundColor("white");
    simulation->item(counterRow, counter)->setText("");
    simulation->item(counterRow, counter)->setTextColor("white");
        }
    }
}

//Colorie des cases randomly et modifie d'état de départ
void Window2D::launchRandom(){


    //Etat_2D state(dimension,dimension);
    for(unsigned int counterRow=0; counterRow<dimension; ++counterRow){
        for(unsigned int counter=0; counter<dimension; ++counter){
    state.setCellule(counterRow, counter, false);
        }
    }
       state.random();


       for(unsigned int counterRow=0; counterRow<dimension; ++counterRow){
           for(unsigned int counter=0; counter<dimension; ++counter){
                if(state.getCellule(counterRow, counter)==true){
                    simulation->item(counterRow, counter)->setBackgroundColor("black");
                    simulation->item(counterRow, counter)->setText("_");
                    simulation->item(counterRow, counter)->setTextColor("black");
                }
                else{

                    simulation->item(counterRow, counter)->setBackgroundColor("white");
                    simulation->item(counterRow, counter)->setText("");
                    simulation->item(counterRow, counter)->setTextColor("white");
                }

           }
         }

}

//Passe d'un état au suivant au coup par coup
void Window2D::launchNext(){
    stopOption=false;
    Etat_2D etat(dimension,dimension);
    jeu.appliquer_transition(state,etat);
    state=etat;

    this->showTable();

}

//FONCTION EN COURS Passe d'états aux suivant sans arrêt
void Window2D::launchNonStop(){

    timer->start(time);

    connect(timer, SIGNAL(timeout()), this, SLOT(launchTransition()));

}




//FONCTION EN COURS Passe d'états aux suivant sans arrêt
void Window2D::launchTransition(){


Etat_2D etat(dimension,dimension);

    jeu.appliquer_transition(state,etat);
    state=etat;
   // connect(timer, SIGNAL(timeout()), this, SLOT(showTableSlot()));
   // timer->start(5000);
    emit iterationSignal();

}



//Arrête le défilement
void Window2D::launchStop(){

    timer->stop();
}


void Window2D::launchChangingTime(int i){
    time=i;
}

//Colorie/décolorie ou Créé cellule true/false
void Window2D::launchActivation(const QModelIndex& index){
    if(simulation->item(index.row(), index.column())->text()==""){
        simulation->item(index.row(), index.column())->setText("_");
        simulation->item(index.row(), index.column())->setBackgroundColor("black");
        simulation->item(index.row(), index.column())->setTextColor("black");
        state.setCellule(index.row(),index.column(), true);

    }else{

        simulation->item(index.row(), index.column())->setText("");
        simulation->item(index.row(), index.column())->setBackgroundColor("white");
        simulation->item(index.row(), index.column())->setTextColor("white");
        state.setCellule(index.row(),index.column(), false);
    }
}

//Affichage graphique de l'etat resultant de la transition
void Window2D::showTable(){

    for(unsigned int counterRow=0; counterRow<dimension; ++counterRow){
        for(unsigned int counter=0; counter<dimension; ++counter){
             if(state.getCellule(counterRow, counter)==true){
                 simulation->item(counterRow, counter)->setBackgroundColor("black");
                 simulation->item(counterRow, counter)->setText("_");
                 simulation->item(counterRow, counter)->setTextColor("black");
             }
             else{

                 simulation->item(counterRow, counter)->setBackgroundColor("white");
                 simulation->item(counterRow, counter)->setText("");
                 simulation->item(counterRow, counter)->setTextColor("white");
             }

        }
      }

}

//Pour le moment non fonctionnel
void Window2D::showTableSlot(){
    //Affichage de l'etat resultant de la transition
    for(unsigned int counterRow=0; counterRow<dimension; ++counterRow){
        for(unsigned int counter=0; counter<dimension; ++counter){
             if(state.getCellule(counterRow, counter)==true){
                 simulation->item(counterRow, counter)->setBackgroundColor("black");
                 simulation->item(counterRow, counter)->setText("_");
                 simulation->item(counterRow, counter)->setTextColor("black");
             }
             else{

                 simulation->item(counterRow, counter)->setBackgroundColor("white");
                 simulation->item(counterRow, counter)->setText("");
                 simulation->item(counterRow, counter)->setTextColor("white");
             }

        }
      }

}


