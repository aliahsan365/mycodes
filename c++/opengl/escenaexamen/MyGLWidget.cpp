#include "MyGLWidget.h"

#include <iostream>
using namespace std;
MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
  xClick = yClick = 0;
  angleY = 0.0f;
  angleX = 0.0f;
  anguloGiro = 0.0f;
  camara = false;
  perspectiva = true;

  DoingInteractive = NONE;
  //radiEsc = sqrt(5);
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  g = 1.0f;
  colFocus = glm::vec3(1.0f,g,1.0f);
  cout << "posfocus : "  << colFocus[0] << " " << colFocus[1] << " " << colFocus[2] << endl;
  glUniform3fv(colFocusLoc,  1,  &colFocus[0]);
  calculaRadiEscena();
  if(!camara) {iniCamara1();}
  else {iniCamara2();}
  createBuffersModel();
  createBuffersTerra();
  projectTransform ();
  if (!camara) {viewTransform1();}
  else {
      viewTransform2();
  }
}

void MyGLWidget::iniCamara1() {
  // vamos a poner que observador esta a dos veces la distancia del radio
  // como cte para programar
  float distancia = 2*radiEsc;
  ra = 1.0;
  //ha de ser constantemente 1 el raw para que no haya deformacion
  cout << "ra que hace de raw: " << ra << endl;
  //establecemos un zn razonbale como radiEscena
  zn = radiEsc;
  cout << "zn fijado " << zn << endl;
  // zf es zn + lo que de la circunferencia(2*radiEscena)
  zf = zn + 2*radiEsc;
  cout << "zf calculado: " << zf << endl;
  //trigonometria, es asin , no atan.
  fov = 2*asin(radiEsc/distancia);
  cout << "fov en rads " << fov << endl;
  anguloini = asin(radiEsc/distancia);
  cout << "angulo " << fov << endl;

}

void MyGLWidget::iniCamara2() {
  // vector up (cabeza en vertical con eje_y)
  UP = glm::vec3(0.0f,1.0f,0.0f);
  //OBS segun enunciado
  OBS = glm::vec3(0.0f,2.5f,0.0f);
  //vrp segun enunciado , pero es +1.0f en obs.z para mirar a  (+z)
  VRP.x = OBS.x;
  VRP.y = OBS.y;
  VRP.z = OBS.z + 1.0f;


  ra = 1.0f;
  //ha de ser constantemente 1 el raw para que no haya deformacion
  cout << "ra que hace de raw: " << ra << endl;
  //establecemos un zn razonbale que sea mayor que 0.0
  zn = 0.1f;
  cout << "zn primer persona " <<  zf << endl;
  // zf es los suficientemente grande para que permite ver todo
  // p.e 100
  zf = 100.0f;
  cout << "zf primera persona: " << zf << endl;
  // fov es fijo
  fov = float(M_PI/2.0);
  cout << "fov en rads " << fov << endl;
  //realmente no hace falta guardarse el angulo
  //anguloini2 = float(M_PI/4.0);
}

void MyGLWidget::paintGL ()
{
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activem el VAO per a pintar el terra
  glBindVertexArray (VAO_Terra);

  modelTransformIdent ();
  // pintem terra
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Activem el VAO per a pintar el Model
  glBindVertexArray (VAO_Model);

  modelTransformModel1 ();
  // Pintem Model
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);

  // Activem el VAO per a pintar el Model
  glBindVertexArray (VAO_Model);

  modelTransformModel2 ();
  // Pintem Model
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);

  // Activem el VAO per a pintar el Model
  glBindVertexArray (VAO_Model);

  modelTransformModel3 ();
  // Pintem Model
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);

  // Activem el VAO per a pintar el Model
  glBindVertexArray (VAO_Model);

  modelTransformModel4 ();
  // Pintem Model
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);
  glBindVertexArray(0);
}


void MyGLWidget::resizeGL (int w, int h)
{
    float ranew = float (w) / float (h);
    if (ranew >= 1) {
        if (camara) {
           ra = ranew;
          }
        else {
         //calulo de las tranaparencias opengl de idi para resize
         // en perpestiva
         ra = ranew;
         //recuperamos el angulo
         fov = 2.0f*anguloini;
        }
     }
     else  {
        if (camara) {
          ra = ranew;
        }
        else {
        //calulo de las tranaparencias opengl de idi para resize
        // en perpestiva
        ra = ranew;
        fov = 2.0f*atan(tan(anguloini)/ra);
       }
     }
   projectTransform();
   glViewport(0,0,w,h);
}





void MyGLWidget::modelTransformModel1 ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
    TG = glm::rotate(TG,anguloGiro, glm::vec3(0,1,0));

  TG = glm::translate(TG, glm::vec3(-2.5f,0.0f,0.0f));
  TG = glm::rotate(TG,float(M_PI/2), glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3(escalaP1,escalaP1,escalaP1));
  TG = glm::translate(TG, -centreBaseP1);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}
void MyGLWidget::modelTransformModel2 ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  TG = glm::rotate(TG,anguloGiro, glm::vec3(0,1,0));

  TG = glm::translate(TG, glm::vec3(0.0f,0.0f,2.5f));
  TG = glm::rotate(TG,float(-M_PI), glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3(escalaP2,escalaP2,escalaP2));
  TG = glm::translate(TG, -centreBaseP2);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformModel3 ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
    TG = glm::rotate(TG,anguloGiro, glm::vec3(0,1,0));

  TG = glm::translate(TG, glm::vec3(2.5f,0.0f,0.0f));
  TG = glm::rotate(TG,float(-M_PI/2), glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3(escalaP3,escalaP3,escalaP3));
  TG = glm::translate(TG, -centreBaseP3);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}


void MyGLWidget::modelTransformModel4 ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
    TG = glm::rotate(TG,anguloGiro, glm::vec3(0,1,0));

  TG = glm::translate(TG, glm::vec3(0.0f,0.0f,-2.5f));
  TG = glm::scale(TG, glm::vec3(escalaP4,escalaP4,escalaP4));
  TG = glm::translate(TG, -centreBaseP4);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}
void MyGLWidget::modelTransformIdent ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform ()
{
  glm::mat4 Proj;  // Matriu de projecció
  if (perspectiva)
    Proj = glm::perspective(fov, ra, zn, zf);
  else
    Proj = glm::ortho(-radiEsc, radiEsc, -radiEsc, radiEsc, radiEsc, 3.0f*radiEsc);

  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform1 ()
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
   glm::mat4 View;
   View = glm::lookAt(OBS,VRP,UP);
   glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}



void MyGLWidget::calculaRadiEscena ()
{
  boundingBoxMax = glm::vec3(10.0f,5.0f,10.0f);
  cout <<  "boundingBoxMax.x " << boundingBoxMax.x << " boundingBoxMax.y " << boundingBoxMax.y << " boundingBoxMax.z " << boundingBoxMax.z << endl;
  boundingBoxMin = glm::vec3(-10.0f,-0.0f,-10.0f);
  cout <<  "boundingBoxMin.x " << boundingBoxMin.x << " boundingBoxMin.y " << boundingBoxMin.y <<  " boundingBoxMin.z " << boundingBoxMin.z << endl;
  centreEscena = glm::vec3((boundingBoxMax.x + boundingBoxMin.x)/2, (boundingBoxMax.y + boundingBoxMin.y)/2, (boundingBoxMax.z + boundingBoxMin.z)/2);
  cout <<  "centreEscena.x " << centreEscena.x <<  " centreEscena.y " << centreEscena.y << " centreEscena.z "  << centreEscena.z << endl;
  radiEsc = distance(boundingBoxMin,boundingBoxMax)/2;
  cout <<  "radiEsc " << radiEsc << endl;
}

void MyGLWidget::createBuffersModel ()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  m.load("./models/Patricio.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModel (m, escalaP1, centreBaseP1);
  calculaCapsaModel (m, escalaP2, centreBaseP2);
  calculaCapsaModel (m, escalaP3, centreBaseP3);
  calculaCapsaModel (m, escalaP4, centreBaseP4);

  // Creació del Vertex Array Object del Model
  glGenVertexArrays(1, &VAO_Model);
  glBindVertexArray(VAO_Model);

  // Creació dels buffers del model patr
  // Buffer de posicions
  glGenBuffers(1, &VBO_ModelPos);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_ModelPos);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*3*3, m.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glGenBuffers(1, &VBO_ModelNorm);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_ModelNorm);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*3*3, m.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glGenBuffers(1, &VBO_ModelMatamb);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_ModelMatamb);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*3*3, m.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glGenBuffers(1, &VBO_ModelMatdiff);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_ModelMatdiff);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*3*3, m.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glGenBuffers(1, &VBO_ModelMatspec);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_ModelMatspec);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*3*3, m.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glGenBuffers(1, &VBO_ModelMatshin);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_ModelMatshin);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*3, m.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::createBuffersTerra ()
{
  // Dades del terra
  // VBO amb la posició dels vèrtexs
  glm::vec3 posterra[4] = {
        glm::vec3(-10.0, 0.0, -10.0),
        glm::vec3(-10.0, 0.0,  10.0),
        glm::vec3( 10.0, 0.0, -10.0),
        glm::vec3( 10.0, 0.0,  10.0)
  };

  // VBO amb la normal de cada vèrtex
  glm::vec3 normt (0,1,0);
  glm::vec3 normterra[4] = {
    normt, normt, normt, normt
  };

  // Definim el material del terra
  glm::vec3 amb(0.1,0.1,0);
  glm::vec3 diff(0.6,0.6,0.0);
  glm::vec3 spec(1.0f,1.0f,1.0f);
  float shin = 2.0f;

  // Fem que aquest material afecti a tots els vèrtexs per igual
  glm::vec3 matambterra[4] = {
    amb, amb, amb, amb
  };
  glm::vec3 matdiffterra[4] = {
    diff, diff, diff, diff
  };
  glm::vec3 matspecterra[4] = {
    spec, spec, spec, spec
  };
  float matshinterra[4] = {
    shin, shin, shin, shin
  };

// Creació del Vertex Array Object del terra
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  glGenBuffers(1, &VBO_TerraPos);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_TerraPos);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posterra), posterra, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glGenBuffers(1, &VBO_TerraNorm);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_TerraNorm);
  glBufferData(GL_ARRAY_BUFFER, sizeof(normterra), normterra, GL_STATIC_DRAW);

  // Activem l'atribut normalLoc
  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glGenBuffers(1, &VBO_TerraMatamb);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_TerraMatamb);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matambterra), matambterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glGenBuffers(1, &VBO_TerraMatdiff);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_TerraMatdiff);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matdiffterra), matdiffterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glGenBuffers(1, &VBO_TerraMatspec);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_TerraMatspec);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matspecterra), matspecterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glGenBuffers(1, &VBO_TerraMatshin);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_TerraMatshin);
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

    colFocusLoc = glGetUniformLocation (program->programId(), "colFocus");
}

void MyGLWidget::calculaCapsaModel (Model &p, float &escala, glm::vec3 &centreBase)
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = p.vertices()[0];
  miny = maxy = p.vertices()[1];
  minz = maxz = p.vertices()[2];
  for (unsigned int i = 3; i < p.vertices().size(); i+=3)
  {
    if (p.vertices()[i+0] < minx)
      minx = p.vertices()[i+0];
    if (p.vertices()[i+0] > maxx)
      maxx = p.vertices()[i+0];
    if (p.vertices()[i+1] < miny)
      miny = p.vertices()[i+1];
    if (p.vertices()[i+1] > maxy)
      maxy = p.vertices()[i+1];
    if (p.vertices()[i+2] < minz)
      minz = p.vertices()[i+2];
    if (p.vertices()[i+2] > maxz)
      maxz = p.vertices()[i+2];
  }
  escala = 5.0/(maxy-miny);
  centreBase[0] = (minx+maxx)/2.0; centreBase[1] = miny; centreBase[2] = (minz+maxz)/2.0;
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_O: { // canvia òptica entre perspectiva i axonomètrica
      perspectiva = !perspectiva;
      projectTransform ();
      break;
    }
    case Qt::Key_C: { // canvia òptica entre perspectiva i axonomètrica
      camara = !camara;
      if(camara) {
          cout << "llamo caramara 2" << endl;
          iniCamara2();
          viewTransform2();
          projectTransform();
       }
      else  {
          iniCamara1();
          viewTransform1();
          projectTransform();

       }
      break;
    }
    default: event->ignore(); break;
  }
  update();
}
void MyGLWidget::giraY(int value)
{
  makeCurrent();
  cout << "grado " << value << endl;
  anguloGiro = (float(M_PI)*float(value))/180.0f;
  modelTransformModel1 ();
  modelTransformModel2 ();
  modelTransformModel3 ();
  modelTransformModel4 ();
  update();
}


void MyGLWidget::changeG(int value)
{
  makeCurrent();
  cout << value << endl;
  g = value/100.0f;

  colFocus = glm::vec3(1.0f,g,1.0f);
  cout << "colFocus : "  << colFocus[0] << " " << colFocus[1] << " " << colFocus[2] << endl;
  glUniform3fv(colFocusLoc,  1,  &colFocus[0]);
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
  if (!camara) {
    if (DoingInteractive == ROTATE)
        {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / 180.0;
    angleX += (e->y() - yClick) * M_PI / 180.0;
    viewTransform1 ();
       }
  }
  xClick = e->x();
  yClick = e->y();

  update ();
}


