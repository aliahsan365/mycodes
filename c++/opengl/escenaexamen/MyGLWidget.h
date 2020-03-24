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
    void createBuffersModel ();
    void createBuffersTerra ();
    void carregaShaders ();
    void projectTransform ();
    void viewTransform1 ();
        void viewTransform2 ();


    void calculaRadiEscena ();

    void modelTransformIdent ();
    void modelTransformModel1 ();
    void modelTransformModel2 ();
    void modelTransformModel3 ();
    void modelTransformModel4 ();

    void iniCamara1();
    void iniCamara2();
    void calculaCapsaModel (Model &p, float &escala, glm::vec3 &CentreBase);

    // VAO i VBO names
    GLuint VAO_Model, VBO_ModelPos, VBO_ModelNorm, VBO_ModelMatamb, VBO_ModelMatdiff, VBO_ModelMatspec, VBO_ModelMatshin;
    GLuint VAO_Terra, VBO_TerraPos, VBO_TerraNorm, VBO_TerraMatamb, VBO_TerraMatdiff, VBO_TerraMatspec, VBO_TerraMatshin;
    // Program
    QOpenGLShaderProgram *program;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc;
    // attribute locations
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc;

    // model
    Model m;
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 centreBaseP1;
    glm::vec3 centreBaseP2;
    glm::vec3 centreBaseP3;
    glm::vec3 centreBaseP4;



    float escalaP1;
    float escalaP2;
    float escalaP3;
    float escalaP4;


    // radi de l'escena
    float radiEsc;

    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float angleY, angleX;
    bool perspectiva;

    glm::vec3 centreEscena;
    glm::vec3 boundingBoxMax;
    glm::vec3 boundingBoxMin;

    float ra,fov,zn,zf,anguloini,anguloini2;
    float anguloGiro;
    bool camara;

    glm::vec3 OBS;
    glm::vec3 VRP;
    glm::vec3 UP;



     glm::vec3 colFocus;
     float g;
  GLuint colFocusLoc;

    public slots:
        void giraY(int value);
        void changeG(int value);
    signals:

};

