#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);

  private:
    void createBuffersModel ();
    void createBuffersTerra ();
    void carregaShaders ();
    void projectTransform ();
    void projectTransform1 ();
    void projectTransform2 ();
	void projectTransform3 ();
    void projectTransform4 ();

    void viewTransform ();
    void viewTransform1 ();
    void viewTransform2 ();
	void viewTransform3 ();
	void viewTransform4 ();

    void modelTransformTerra ();
    void modelTransformPatricio ();
    void calculaCapsaModel ();
    void calculaRadiEscena();
    void iniCamera ();
    void calculaRadiEscena1();
    void iniCamera1();
    void calculaRadiEscena2();
    void iniCamera2();
    void calculaRadiEscena3();
    void iniCamera3();
    void calculaRadiEscena4();
    void iniCamera4();
    
    // VAO i VBO names
    GLuint VAO_Patr;
    GLuint VAO_Terra;
    // Program
    QOpenGLShaderProgram *program;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc;
    // attribute locations
    GLuint vertexLoc, colorLoc;

    // model
    Model patr;
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 centreBasePatr;
    glm::vec3 centreEscena;
    glm::vec3 VRP,OBS,UP;
    float radiEscena;
    float escala;
    
    float FOVini;
    float FOV;
    
    float ra;
    float Znear;
    float Zfar;
    float theta;
    float psi;
    float FOVfix;
    
};

