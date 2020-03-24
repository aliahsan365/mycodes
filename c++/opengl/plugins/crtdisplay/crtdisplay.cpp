// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "crtdisplay.h"

void Crtdisplay::onPluginLoad()
{
    // Carregar shader, compile & link 

    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("crtdisplay.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;
 	
 	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("crtdisplay.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
}

void Crtdisplay::preFrame() 
{
    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("n", 6);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
}

void Crtdisplay::postFrame() 
{
    // unbind shader
    program->release();
}

