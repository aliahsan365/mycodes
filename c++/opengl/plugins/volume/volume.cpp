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

#include "Volume.h"




void Volume::onPluginLoad()
{
  float volume = 0.0;
  vector<Vertex>& vvo = scene()->objects()[0].vertices(); 
  const vector<Face>& caras = (scene()->objects()[0]).faces(); 
  for (auto i = 0; i < caras.size(); ++i) {
      Face f = caras[i];
      Point p1 = vvo[f.vertexIndex(0)].coord();
      Point p2 = vvo[f.vertexIndex(1)].coord();
      Point p3 = vvo[f.vertexIndex(2)].coord();
      //centroide
      float p1x = p1.x();
      float p2x = p2.x();
      float p3x = p3.x();
      float C = (p1x + p2x + p3x)/3.0;
      //normal cara
      float normalx = f.normal().x(); 
      Point v = p1-p2;
      Point u = p1-p3;
      QVector3D cp = QVector3D::crossProduct(v,u);
      float area_paralelogram = cp.length();
      float area_triangulo = area_paralelogram  / 2.0;
        // (C.x * N.x * A)
      volume += (C*normalx*area_triangulo);
 }
  
  cout << "Volume: " << volume << endl;
}

void Volume::preFrame() 
{


}

void Volume::postFrame() 
{
    
}




