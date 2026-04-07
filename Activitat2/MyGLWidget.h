#include "BL2GLWidget.h"
#include <QCheckBox>
#include "model.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    void initializeGL() override;

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    void paintGL() override;

    // resizeGL - És cridat quan canvia la mida del widget
    void resizeGL (int width, int height) override;

    // carregaShaders - Aquí carreguem els shaders, els compilem i els linkem. També busquem els uniform locations que fem servir.
    void carregaShaders() override;
    
    // iniEscena - Aqui incluim les inicialitzacions de l'escena
    void iniEscena() override;
    // iniCamera - Aqui incluim les inicialitzacions de la camera
    void iniCamera() override;

    // {Rick/VideoCamera/Cub/ident}Transform - Funcions per construir i enviar al shader diferents matrius de transformació geomètrica TG
    void RickTransform() override;
    void VideoCameraTransform() override;
    void CubTransform(glm::vec3 posicioCub, glm::vec3 midaCub);
    
    // viewTransform i projecTransform - Es fan servir per a construir i enviar als shader les matrius de càmera (View i Projection respectivament).
    void projectTransform() override;
    void viewTransform() override;
    
    // keyPressEvent - Es cridat quan es prem una tecla
    void keyPressEvent (QKeyEvent *event) override;

    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event
    // corresponent de ratolí
    void mousePressEvent (QMouseEvent *e) override;
    void mouseReleaseEvent (QMouseEvent *e) override;
    void mouseMoveEvent (QMouseEvent *e) override;

  private:

    // calculaCapsaEscena - Calcula el radi i el centre de l'esfera contenidora de l'escena.
    void calculaCapsaEscena(glm::vec3 pmin, glm::vec3 pmax);

    // canviCamera - reconfigura les variables per adaptar-les a la càmara acutal.
    void canviCamera();

    // uniform locations
    GLint pintaVermellLoc;

    //Transformacions Rick
    bool esAutomatic = false;
    bool rickXPositiu = true;

    //Transformacions Parets
    glm::vec3 posParetEsquerre = glm::vec3(0,0,2.5);
    glm::vec3 posParetDreta = glm::vec3(0,0,-2.5); //La que a sobre té la videocàmera.
    glm::vec3 escalaCub = glm::vec3(0.5,2,3);

    //Transformacions porta
    glm::vec3 posPorta = glm::vec3(0,0,0);
    float velocitatPorta = 0.25f;
    glm::vec3 escalaPorta = glm::vec3(0.25,2,2);

    //Transformacions Video Camera
    glm::vec3 posVideoCamera = glm::vec3(0,2.25,-1);

    //variables de camera
    float d, alpha;
    bool esVideoCamera = false;

    // controla com de ràpid gira la càmera quan mous el ratolí. Com més gran és, més lent gira.
    float sensibilitatCamera = 20.0;

    // determina cada quants milisegons s'ha de cridar el timer.
    // Per saber quantes crides al timer volem fer, s'ha de fer 1000/vegades que volem cridar-lo per segon.
    // El 1000 són 1000ms = 1s.
    float tempsTimer = 1000/60; // Volem 60 crides.

  public slots:
    void updatePosition() override;
    void activaVideocamera(bool activat);
    void activaRickAutomatic(bool activat);
    void Reset();

  signals:
    void modificaCheckBoxVideocamera(bool activat);
    void modificaCheckBoxAutomatic(bool activat);
};
