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
    void createBuffersVaca ();
    void createBuffersTerraIParet ();
    void carregaShaders ();
    void iniEscena ();
    void iniCamera ();
    void iniCamera2 ();

    void projectTransform ();
    void viewTransform1 ();
        void viewTransform2 ();

    void modelTransformTerra ();
    void modelTransformPatricio ();
    void modelTransformVaca ();
    void calculaCapsaModelPatr ();
    void calculaCapsaModelVaca ();

    // VAO i VBO names
    GLuint VAO_Patr;
    GLuint VAO_Terra;
    GLuint VAO_Vaca;

    // Program
    QOpenGLShaderProgram *program;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc;
    // attribute locations
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc;

    // model
    Model patr;
    Model vaca;
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 centrePatr;
    glm::vec3 centreVaca;



    float escalaPat,escalaVaca;
    // radi de l'escena
    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float angleY;
    float angleX;

    bool perspectiva;


    glm::vec3 boundingBoxMin;
    glm::vec3 boundingBoxMax;
    glm::vec3 centreEscena;
    float distCajaEscena;
    float radiEsc;
    float fov,ra,zn,zf;
    float rotate;
    float anguloini;

    bool carcel;
    GLuint carcelLoc;

    bool fescena;
    GLuint fescenaLoc;


    bool vacagris;
    GLuint vacagrisLoc;
    glm::vec3 VRP;
    glm::vec3 UP;
    glm::vec3 OBS;
    bool camara;
    public slots:
        void enviafocoEscena(bool b);
        void enviafocoCamara(bool b);

    signals:
        void focoEscena(bool);
        void focoCamara(bool);

};

