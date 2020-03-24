#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <utility>
#include <QPair>
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
    void createBuffersTerraIParet ();
    void carregaShaders ();
    void iniEscena ();
    void iniCamera ();
    void projectTransform ();
    void viewTransform ();
    void modelTransformTerra ();
    
    void modelTransformModel1 ();
    void modelTransformModel2 ();

    void calculaCapsaModel ();

    // VAO names
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
    glm::vec3 centreBasePatr;
    float escalaP1,escalaP2;
    // radi de l'escena
    float radiEsc;

    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float angleY;
    bool perspectiva;
    glm::vec3 boundingBoxMin,boundingBoxMax;
    float dist;
    
    glm::vec3 posFocus;
    GLuint posFocusLoc;
    
    bool fescena;
    GLuint fescenaLoc;
    
    int nf;
    
    //es  un pair que nos dice si hay algun patricio selecionado y cual
    // en caso de q haya alguno
    QPair<bool,int> selected;
    
    // pos de pat1 en el plano xz pat1
    float xp1,zp1;
    //pos del pat2 en el plano xz pat2
    float xp2,zp2;
    
    //pos de focus
    float xf,zf;
    
    float ra;
    
    
   
    
    
    
    
};

