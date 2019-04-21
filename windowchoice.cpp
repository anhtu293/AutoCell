#include "mainwindow2D.h"
#include "firstwindowconfig.h"
#include "windowchoice.h"
#include "firstwindow2d.h"
#include "windowchoiceconfig.h"

WindowChoice::WindowChoice(QWidget* parent):QDialog(parent){


    title=new QLabel("Choisissez le type d'automate que vous souhaitez utiliser :\n", this);

    buttonOneD=new QPushButton("Automate 1 Dimension", this);
    buttonTwoD=new QPushButton("Automate 2 Dimensions", this);
      QObject::connect(buttonTwoD, SIGNAL(clicked()), this, SLOT(launchWindow2D()));
    buttonThreeD=new QPushButton("Automate 3 Dimensions", this);

    verticalUpBox=new QVBoxLayout;

    verticalUpBox->addWidget(title);
    verticalUpBox->addWidget(buttonOneD);

    verticalUpBox->addWidget(buttonTwoD);
    verticalUpBox->addWidget(buttonThreeD);


    this->setLayout(verticalUpBox);

}

void WindowChoice::launchWindow2D(){
    hide();

   FirstWindow2D wind(this);
   wind.setModal(true);//On est jamais trop prudent
   wind.exec();
}
