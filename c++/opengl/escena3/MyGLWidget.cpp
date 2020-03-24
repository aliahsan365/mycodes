#include "MyGLWidget.h"

#include <iostream>
using namespace std;
MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  xClick = yClick = 0;
  DoingInteractive = NONE;
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}



void MyGLWidget::iniEscena ()
{
  boundingBoxMax = glm::vec3(2,1.5,2);
  cout <<  "boundingBoxMax.x " << boundingBoxMax.x << " boundingBoxMax.y " << boundingBoxMax.y << " boundingBoxMax.z " << boundingBoxMax.z << endl;

  boundingBoxMin = glm::vec3(-2,-1,-2);

  cout <<  "boundingBoxMin.x " << boundingBoxMin.x << " boundingBoxMin.y " << boundingBoxMin.y <<  " boundingBoxMin.z " << boundingBoxMin.z << endl;
  centreEscena = glm::vec3((boundingBoxMax.x + boundingBoxMin.x)/2, (boundingBoxMax.y + boundingBoxMin.y)/2, (boundingBoxMax.z + boundingBoxMin.z)/2);

  cout <<  "centreEscena.x " << centreEscena.x <<  " centreEscena.y " << centreEscena.y << " centreEscena.z "  << centreEscena.z << endl;
  radiEsc = distance(boundingBoxMin,boundingBoxMax)/2;
  cout <<  "radiEsc " << radiEsc << endl;
  xd = -2;
  posFocus = glm::vec3(xd,2,0);
  OBS = glm::vec3(xd,1.5,0);
  cout << "posfocus : "  << posFocus[0] << " " << posFocus[1] << " " << posFocus[2] << endl;
  glUniform3fv(posFocusLoc,  1,  &posFocus[0]);
  camara = false;

}


void MyGLWidget::iniCamera ()
{
  angleY = 0.0;
  angleX = 0.0;


  perspectiva = true;
  // vamos a poner que observador esta a dos veces la distancia del radio
  // como cte para programar
  float distancia = 2*radiEsc;
  ra = 1.0;
  //ha de ser constantemente 1 el raw para que no haya deformacion
  cout << "ra que hace de raw: " << ra << endl;
  //establecemos un zn razonbale como radiEscena
  zn = radiEsc;
  cout << "zn fijado " << endl;
  // zf es zn + lo que de la circunferencia(2*radiEscena)
  zf = zn + 2*radiEsc;
  cout << "zf calculado: " << zf << endl;
  //trigonometria, es asin , no atan.
  fov = 2*asin(radiEsc/distancia);
  cout << "fov en rads " << fov << endl;
  anguloini = asin(radiEsc/distancia);
  projectTransform ();
  viewTransform ();
}




void MyGLWidget::iniCamera2 ()
{
  angleY = 0.0;
  angleX = 0.0;


  UP = glm::vec3(0,1,0);
  //OBS = glm::vec3(-2,1.5,0);
  VRP = glm::vec3(2,0.25,0);

  perspectiva = true;
  // vamos a poner que observador esta a dos veces la distancia del radio
  // como cte para programar
  ra = 1.0;
  //ha de ser constantemente 1 el raw para que no haya deformacion
  cout << "ra que hace de raw: " << ra << endl;
  //establecemos un zn razonbale como radiEscena
  zn = 0.1;
  cout << "zn fijado " << endl;
  // zf es zn + lo que de la circunferencia(2*radiEscena)
  zf = 100;
  cout << "zf calculado: " << zf << endl;
  //trigonometria, es asin , no atan.
  fov = float(M_PI/2);
  cout << "fov en rads " << fov << endl;
  anguloini = float(M_PI/2);
  projectTransform ();
  viewTransform2 ();
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable (GL_DEPTH_TEST);
  carregaShaders();
  r = 0.8;
  g = 0.0;
  b = 0.8;
  diff =  glm::vec3(r,g,b);
  createBuffersPatricio();
  createBuffersTerraIParet();

  iniEscena();
  iniCamera();
}



void MyGLWidget::paintGL ()
{
  glViewport (0, 0, width(), height()); // Aquesta crida no caldria perquè Qt la fa de forma automàtica amb aquests paràmetres

  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activem el VAO per a pintar el terra
  glBindVertexArray (VAO_Terra);

  modelTransformTerra ();

  // pintem
  glDrawArrays(GL_TRIANGLES, 0, 12);

  // Activem el VAO per a pintar el Patricio
  glBindVertexArray (VAO_Patr);

  modelTransformPatricio1 ();

  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);



  glBindVertexArray (VAO_Patr);

  modelTransformPatricio2 ();

  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);


  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
    float ranew = float (w) / float (h);
    if (ranew >= 1) {
        ra = ranew;
       }
     else  {
        ra = ranew;
        if (camara) {
            fov = 2*atan(tan(anguloini2)/ra);
            }
        else {
            fov = 2*atan(tan(anguloini)/ra);
        }
      }
     projectTransform();
     glViewport(0,0,w,h);
}

void MyGLWidget::createBuffersPatricio ()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  patr.load("./models/Patricio.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModel ();

  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Patr);
  glBindVertexArray(VAO_Patr);

  // Creació dels buffers del model patr
  GLuint VBO_Patr[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Patr);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3*3, patr.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patr[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patr.faces().size()*3, patr.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}


void MyGLWidget::createBuffersTerraIParet ()
{
  // VBO amb la posició dels vèrtexs
  glm::vec3 posterra[12] = {
    glm::vec3(-2.0, -1.0, 2.0),
    glm::vec3(2.0, -1.0, 2.0),
    glm::vec3(-2.0, -1.0, -2.0),
    glm::vec3(-2.0, -1.0, -2.0),
    glm::vec3(2.0, -1.0, 2.0),
    glm::vec3(2.0, -1.0, -2.0),
    glm::vec3(-2.0, -1.0, -2.0),
    glm::vec3(2.0, -1.0, -2.0),
    glm::vec3(-2.0, 1.0, -2.0),
    glm::vec3(-2.0, 1.0, -2.0),
    glm::vec3(2.0, -1.0, -2.0),
    glm::vec3(2.0, 1.0, -2.0)
  };

  // VBO amb la normal de cada vèrtex
  glm::vec3 norm1 (0,1,0);
  glm::vec3 norm2 (0,0,1);
  glm::vec3 normterra[12] = {
    norm1, norm1, norm1, norm1, norm1, norm1, // la normal (0,1,0) per als primers dos triangles
    norm2, norm2, norm2, norm2, norm2, norm2  // la normal (0,0,1) per als dos últims triangles
  };

  // Definim el material del terra
  glm::vec3 amb(0.2,0,0.2);
  //glm::vec3 diff(0.8,0,0.8);
  glm::vec3 spec(0,0,0);
  float shin = 100;

  // Fem que aquest material afecti a tots els vèrtexs per igual
  glm::vec3 matambterra[12] = {
    amb, amb, amb, amb, amb, amb, amb, amb, amb, amb, amb, amb
  };
  glm::vec3 matdiffterra[12] = {
    diff, diff, diff, diff, diff, diff, diff, diff, diff, diff, diff, diff
  };
  glm::vec3 matspecterra[12] = {
    spec, spec, spec, spec, spec, spec, spec, spec, spec, spec, spec, spec
  };
  float matshinterra[12] = {
    shin, shin, shin, shin, shin, shin, shin, shin, shin, shin, shin, shin
  };

// Creació del Vertex Array Object del terra
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[6];
  glGenBuffers(6, VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posterra), posterra, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(normterra), normterra, GL_STATIC_DRAW);

  // Activem l'atribut normalLoc
  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matambterra), matambterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matdiffterra), matdiffterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matspecterra), matspecterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matshinterra), matshinterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/fragshad.frag");
  vs.compileSourceFile("shaders/vertshad.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “normal” del vertex shader
  normalLoc = glGetAttribLocation (program->programId(), "normal");
  // Obtenim identificador per a l'atribut “matamb” del vertex shader
  matambLoc = glGetAttribLocation (program->programId(), "matamb");
  // Obtenim identificador per a l'atribut “matdiff” del vertex shader
  matdiffLoc = glGetAttribLocation (program->programId(), "matdiff");
  // Obtenim identificador per a l'atribut “matspec” del vertex shader
  matspecLoc = glGetAttribLocation (program->programId(), "matspec");
  // Obtenim identificador per a l'atribut “matshin” del vertex shader
  matshinLoc = glGetAttribLocation (program->programId(), "matshin");

  // Demanem identificadors per als uniforms del vertex shader
  transLoc = glGetUniformLocation (program->programId(), "TG");
  projLoc = glGetUniformLocation (program->programId(), "proj");
  viewLoc = glGetUniformLocation (program->programId(), "view");


   posFocusLoc = glGetUniformLocation (program->programId(), "posFocus");
}

void MyGLWidget::modelTransformPatricio1 ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació

  TG = glm::translate(TG, glm::vec3(xd,-1,0));
  TG = glm::rotate(TG,float(M_PI/2), glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3(escalaP1, escalaP1, escalaP1));
  TG = glm::translate(TG, -CBP1);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}


void MyGLWidget::modelTransformPatricio2 ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació

  TG = glm::translate(TG, glm::vec3(2,-1,0));
  TG = glm::rotate(TG,float(-M_PI/2), glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3(escalaP2, escalaP2, escalaP2));
  TG = glm::translate(TG, -CBP2);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}


void MyGLWidget::modelTransformTerra ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform ()
{
  glm::mat4 Proj;  // Matriu de projecció
  if (perspectiva) {
    Proj = glm::perspective(fov, ra, zn, zf);
    }
  else {
    Proj = glm::ortho(-radiEsc, radiEsc, -radiEsc, radiEsc, radiEsc, 3.0f*radiEsc);
    }
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform ()
{
  glm::mat4 View;  // Matriu de posició i orientació
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
  View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
  View = glm::translate(View, -centreEscena);
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}



void MyGLWidget::viewTransform2 ()
{
    glm::mat4 View = glm::lookAt(OBS,VRP,UP);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);

}
void MyGLWidget::calculaCapsaModel ()
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = patr.vertices()[0];
  miny = maxy = patr.vertices()[1];
  minz = maxz = patr.vertices()[2];
  for (unsigned int i = 3; i < patr.vertices().size(); i+=3)
  {
    if (patr.vertices()[i+0] < minx)
      minx = patr.vertices()[i+0];
    if (patr.vertices()[i+0] > maxx)
      maxx = patr.vertices()[i+0];
    if (patr.vertices()[i+1] < miny)
      miny = patr.vertices()[i+1];
    if (patr.vertices()[i+1] > maxy)
      maxy = patr.vertices()[i+1];
    if (patr.vertices()[i+2] < minz)
      minz = patr.vertices()[i+2];
    if (patr.vertices()[i+2] > maxz)
      maxz = patr.vertices()[i+2];
  }
  escalaP1 = 1.0/(maxy-miny);
  CBP1[0] = (minx+maxx)/2.0;
  CBP1[1] = miny;
  CBP1[2] = (minz+maxz)/2.0;


  escalaP2 = 2.5/(maxy-miny);
  CBP2[0] = (minx+maxx)/2.0;
  CBP2[1] = miny;
  CBP2[2] = (minz+maxz)/2.0;
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_C: { // canvia òptica entre perspectiva i axonomètrica
      camara  = !camara;
      if (camara) {
          iniCamera2();
          emit changeRadio();
        }
      else {
         iniCamera();
         emit changeRadio();
      }
      break;
    }

    case Qt::Key_O: { // canvia òptica entre perspectiva i axonomètrica
      perspectiva = !perspectiva;
      projectTransform ();
      break;
    }
    case Qt::Key_A: { // canvia òptica entre perspectiva i axonomètrica
      if (not(xd > 2.0)) {
         xd  += 0.2;
         posFocus = glm::vec3(xd,2,0);
         cout << "posfocus : "  << posFocus[0] << " " << posFocus[1] << " " << posFocus[2] << endl;
         glUniform3fv(posFocusLoc,  1,  &posFocus[0]);
                   OBS = glm::vec3(xd,1.5,0);
          if (camara) {
            iniCamera2();
            }
          else  {
            iniCamera();
           }
        }
      modelTransformPatricio1 ();
      break;
    }
    case Qt::Key_D: { // canvia òptica entre perspectiva i axonomètrica
      if (xd > -2.0) {
          xd -= 0.2;
          posFocus = glm::vec3(xd,2,0);
          cout << "posfocus : "  << posFocus[0] << " " << posFocus[1] << " " << posFocus[2] << endl;
          glUniform3fv(posFocusLoc,  1,  &posFocus[0]);
          OBS = glm::vec3(xd,1.5,0);
          if (camara) {
            iniCamera2();
            }
          else  {
            iniCamera();
            }
        }
      modelTransformPatricio1();
      break;
    }
    default: event->ignore(); break;
  }
  update();
}


void MyGLWidget::changeCamara(bool b) {

    makeCurrent();
    camara = b;
    if (camara) {
        iniCamera2();
        }
    else {
        iniCamera();
        }
    update();
    }
void MyGLWidget::changeR(int x) {
    makeCurrent();
    float aux = float(x)/float(100);
    diff.r = aux;
    createBuffersTerraIParet();
    update();

    }

void MyGLWidget::changeG(int x) {
    makeCurrent();
    float aux = float(x)/float(100);
    diff.y = aux;
    createBuffersTerraIParet();
    update();

    }

void MyGLWidget::changeB(int x) {
    makeCurrent();
    float aux = float(x)/float(100);
    diff.z = aux;
    createBuffersTerraIParet();
    update();

    }

void MyGLWidget::mousePressEvent (QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
}

void MyGLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / 180.0;
     angleX += (e->y() - yClick) * M_PI / 180.0;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}


