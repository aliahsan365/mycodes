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
    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event
    // corresponent de ratolí
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

  private:
    void createBuffersPatricio ();
    void createBuffersTerraIParet ();
    void carregaShaders ();
    void iniEscena ();
    void iniCamera ();
        void iniCamera2 ();

    void projectTransform ();
    void viewTransform ();
        void viewTransform2 ();

    void modelTransformTerra ();
    void modelTransformPatricio1 ();
    void modelTransformPatricio2 ();

    void calculaCapsaModel ();

    // VAO i VBO names
    GLuint VAO_Patr;
    GLuint VAO_Terra;
    // Program
    QOpenGLShaderProgram *program;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc;
    // attribute locations
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc;

    // model
    Model patr;



    // radi de l'escena
    float radiEsc;
   glm::vec3 centreEscena;

    glm::vec3 boundingBoxMin;
    glm::vec3 boundingBoxMax;

    glm::vec3 CBP1;
    glm::vec3 CBP2;

    float escalaP1;
    float escalaP2;

    float fov,ra,zn,zf;
    float anguloini;


    bool camara;

    float xd;


    glm::vec3 posFocus;
    GLuint posFocusLoc;

    float anguloini2;

    //camarados
    glm::vec3 UP;
    glm::vec3 OBS;
    glm::vec3 VRP;

    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float angleY,angleX;
    bool perspectiva;


    glm::vec3 diff;
    float r,g,b;
    public slots:
        void changeCamara(bool b);
        void changeR(int x);
        void changeG(int x);
        void changeB(int x);

    signals:
        void changeRadio();

};

