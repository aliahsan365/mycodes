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
    void extraValues (); // mia
    void projectTransform ();
    void viewTransform ();
    void modelTransformTerra ();
    void modelTransformPatricio1 ();
    void modelTransformPatricio2 ();

    void calculaCapsaModel ();
    float gradoArad(float angulo);
    float radAgrado(float angulo);

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
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 centrePatr;
    float escala;
    // radi de l'escena


    typedef  enum {NONE, ROTATE, ZOOM} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float angleY,angleX;
    bool perspectiva;

    glm::vec3 boundingBoxMin;
    glm::vec3 boundingBoxMax;
    glm::vec3 centreEscena;
    float distCajaEscena;
    float radiEsc;

    float angulo,anguloini,fov,fovi,ra,zn,zf;
    float distancia;
    public slots:
        void changeFOV(int x);
    signals:
        void sliderValue(int);
};

