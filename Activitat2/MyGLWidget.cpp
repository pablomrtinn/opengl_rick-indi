#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>
#include <QDebug>

// initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
void MyGLWidget::initializeGL ( ){
    //alçades inicials
    alcadaRick = 1.5;
    alcadaVideoCamera = 0.5;

    //angle inicial de la camera (no es modifica en el programa)
    angleVideoCamera = 0;

    //Capsa de l'escena
    glm::vec3 pmin(-6,0,-4);
    glm::vec3 pmax(6,2.75,4);
    calculaCapsaEscena(pmin, pmax);

    // Paràmetres de la càmera que no es modifiquen
    d = 2*radiEscena;
    obs = glm::vec3(0, 2.25, -1);
    up = glm::vec3(0,1,0);

    BL2GLWidget::initializeGL();

    // tempsTimer = 1000ms (1seg) / FPS que volem
    timer->start(tempsTimer);

    canviCamera();
}

MyGLWidget::~MyGLWidget() {
    BL2GLWidget::~BL2GLWidget();
}

// paintGL - Mètode cridat cada cop que cal refrescar la finestra.
// Tot el que es dibuixa es dibuixa aqui.
void MyGLWidget::paintGL ()
{
    // Esborrem el frame-buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rick
    glBindVertexArray (VAO_Rick);
    RickTransform();
    glDrawArrays(GL_TRIANGLES, 0, rick.faces().size()*3);

    // VideoCamera
    if(!esVideoCamera){ //Si estem en videocamera no pintem el model.
        glBindVertexArray (VAO_VideoCamera);
        VideoCameraTransform();
        glDrawArrays(GL_TRIANGLES, 0, videoCamera.faces().size()*3);
    }

    // Cub esquerre
    glBindVertexArray (VAO_Cub);
    CubTransform(posParetEsquerre, escalaCub);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Cub dret
    glBindVertexArray (VAO_Cub);
    CubTransform(posParetDreta, escalaCub);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Cub porta (vermella)
    glBindVertexArray(VAO_Cub);
    glUniform1i(pintaVermellLoc, GL_TRUE);
    // Efecte de lliscar la porta.
    if ((posRick.x > 2 || posRick.x < -2) && posPorta.z > 0) posPorta.z -= velocitatPorta;
    else if ((posRick.x <= 2 && posRick.x >= -2) && posPorta.z < 2) posPorta.z += velocitatPorta;
    CubTransform(posPorta, escalaPorta);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glUniform1i(pintaVermellLoc, GL_FALSE);

    // Terra
    glBindVertexArray (VAO_Terra);
    identTransform();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray (0);
}

// resizeGL - És cridat quan canvia la mida del widget
void MyGLWidget::resizeGL(int w, int h){
#ifdef __APPLE__
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    ample = vp[2];
    alt = vp[3];
#else
    ample = w;
    alt = h;
#endif
    float raV = float(w) / float(h);
    if(raV < 1) fov = 2*atan(tan(alpha)/raV);
    ra = raV;
    projectTransform();
}

// carregaShaders - Aquí carreguem els shaders, els compilem i els linkem. També busquem els uniform locations que fem servir.
void MyGLWidget::carregaShaders(){
    BL2GLWidget::carregaShaders();
    pintaVermellLoc = glGetUniformLocation(program->programId(), "pintaVermell");
}

// calculaCapsaEscena - Calcula el centre i el radi de l'escena.
void MyGLWidget::calculaCapsaEscena(glm::vec3 pmin, glm::vec3 pmax){
    centreEscena = (pmin + pmax) / 2.0f;
    radiEscena = glm::distance(pmin, pmax) / 2.0f;
}

// iniEscena - inicialitza les variables de l'escena.
void MyGLWidget::iniEscena(){
    //Variables del BL2GLWidget modificades
    angleRick = M_PI/2;
    posRick = glm::vec3(-5,0,0);

    //Variables del MYGLWidget
    posPorta = glm::vec3(0,0,0);
    esVideoCamera = false;
    esAutomatic = false;
    rickXPositiu = true;
}

// iniCamera - inicialitza les variables de la camera.
void MyGLWidget::iniCamera(){
    // Camera lliure.
    alpha = asin(radiEscena / d);
    fov = 2*alpha;

    //Paràmetres camera inicial (no videocamera).
    // Els angles inicialment estàn en decimal i no radiants perque en el viewTransform() es fa la conversió.
    factorAngleX = M_PI/4;
    factorAngleY = -M_PI/4;

    viewTransform();
}

// {Rick/VideoCamera/Cub/ident}Transform - Funcions per construir i enviar al shader diferents matrius de transformació geomètrica TG
void MyGLWidget::RickTransform () {
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, posRick);
    TG=glm::rotate(TG, angleRick, glm::vec3(0,1,0));
    TG=glm::scale(TG, glm::vec3(escalaRick));
    TG=glm::translate(TG, -centreCaixaRick);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::VideoCameraTransform () {
    glm::mat4 TG(1.0f);
    TG=glm::translate(TG, posVideoCamera);
    TG=glm::rotate(TG, angleVideoCamera, glm::vec3(0,1,0));
    TG=glm::scale(TG, glm::vec3(escalaVideoCamera));
    TG=glm::translate(TG, -centreCaixaVideoCamera);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::CubTransform (glm::vec3 posicioCub, glm::vec3 midaCub) {
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, posicioCub);
    TG = glm::scale(TG, midaCub);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

// viewTransform i projecTransform - Es fan servir per a construir i enviar als shader les matrius de càmera (View i Projection respectivament).
void MyGLWidget::projectTransform() {
    glm::mat4 Proj = glm::perspective(fov, ra, znear, zfar);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform() {
    glm::mat4 VM(1.0f);
    if(!esVideoCamera){ // Ens podem moure lliurement.
        vrp = glm::vec3(centreEscena);
        VM = glm::translate(VM, glm::vec3(0.0f, 0.0f, -d));
        VM = glm::rotate(VM, factorAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
        VM = glm::rotate(VM, factorAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
        VM = glm::translate(VM, glm::vec3(-vrp));
    }
    else{ // És la videocàmera. El vrp sempre serà la posició d'en Rick.
        vrp = glm::vec3(posRick);
        VM = glm::lookAt(obs, vrp, up);
    }
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &VM[0][0]);
}

// canviCamera - reconfigura les variables per adaptar-les a la càmara acutal.
void MyGLWidget::canviCamera(){
    if(!esVideoCamera) alpha = asin(radiEscena / d);
    else alpha = M_PI/4;
    fov = 2*alpha;

    if(!esVideoCamera){
        znear = d - radiEscena;
        zfar = d + radiEscena;
    }
    else{
        znear = 0.01;
        zfar = distance(obs, glm::vec3(6, 2.25, 4));
    }

    ample = width();
    alt = height();
    resizeGL(ample, alt);
    viewTransform();
}


// keyPressEvent - Es cridat quan es prem una tecla
void MyGLWidget::keyPressEvent(QKeyEvent* event) {
    makeCurrent();
    switch (event->key()) {
    case Qt::Key_Up: {
        if(posRick.x < 6 && !esAutomatic){
            ++posRick.x;
            if(posRick.x > 6) posRick.x = 6;
            angleRick = M_PI/2;
            rickXPositiu = true;
            viewTransform();
        }
        break;
    }
    case Qt::Key_Down: {
        if(posRick.x > -6 && !esAutomatic){
            --posRick.x;
            if(posRick.x < -6) posRick.x = -6;
            angleRick = -M_PI/2;
            rickXPositiu = false;
            viewTransform();
        }
        break;
    }
    case Qt::Key_C: {
        esVideoCamera = !esVideoCamera;
        canviCamera();
        emit(modificaCheckBoxVideocamera(esVideoCamera));
        break;
    }
    case Qt::Key_R: {
        Reset();
        break;
    }
    case Qt::Key_A: {
        esAutomatic = !esAutomatic;
        emit(modificaCheckBoxAutomatic(esAutomatic));
        timer->start(tempsTimer);
        break;
    }
    default: event->ignore(); break;
    }
    update();
}

// mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event
// corresponent de ratolí
void MyGLWidget::mousePressEvent(QMouseEvent *e) {
    makeCurrent();
    xClick = e->x();
    yClick = e->y();

    if (e->button() == Qt::LeftButton && !esVideoCamera)
        DoingInteractive = ROTATE;
    update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    makeCurrent();
    if (DoingInteractive == ROTATE)
    {
        // Fem la rotació
        factorAngleX += (e->y() - yClick) * M_PI / alt;
        factorAngleY += (e->x() - xClick) * M_PI / ample;
        viewTransform ();
    }

    xClick = e->x();
    yClick = e->y();

    update ();
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *) {
    makeCurrent();
    DoingInteractive = NONE;
    update();
}

// updatePosition - actualitza la posició d'en Rick si està en mode automàtic.
void MyGLWidget::updatePosition(){
    makeCurrent();
    if(esAutomatic){
        if(rickXPositiu){
            if(posRick.x < 6) posRick.x += 0.25;
            else{
                rickXPositiu = false;
                angleRick = -M_PI/2;
            }
        }
        else{
            if(posRick.x > -6) posRick.x -= 0.25;
            else{
                rickXPositiu = true;
                angleRick = M_PI/2;
            }
        }
        viewTransform();
    }
    update();
}

// activaVideocamera - activa la videocamera des de la ui
void MyGLWidget::activaVideocamera(bool activat){
    esVideoCamera = activat;
    canviCamera();
}

// activaVideocamera - activa el Rick automàtic des de la ui
void MyGLWidget::activaRickAutomatic(bool activat){
    esAutomatic = activat;
    if(activat) timer->start(tempsTimer);
}

// Reset - reinicia l'escena amb els paràmetres inicials
void MyGLWidget::Reset(){
    iniCamera();
    iniEscena();
    emit(modificaCheckBoxVideocamera(false));
    emit(modificaCheckBoxAutomatic(false));
    timer->stop();
}
