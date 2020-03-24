#include "area.h"
#include <cmath>

void Area::onPluginLoad()
{
    printInfo();
}

void Area::onObjectAdd()
{
    printInfo();
}

void Area::printInfo()
{
    const vector<Object> &vObj = scene()->objects();
    int nObjects = vObj.size();
    float areaTotal;
    

    for(int i = 0; i < nObjects; ++i)
    {
        areaTotal = 0;
        const vector<Face> &vFace = vObj[i].faces();
        const vector<Vertex> &vVertex ) vObj[i].vertices();
        for(int j = 0; j < (int) vFace.size(); ++j)
        {
            const Face &face = vFace[j];
            int i0,i1,i2;
            i0 = face.vertexIndex(0);
            i1 = face.vertexIndex(1);
            i2 = face.vertexIndex(2);
            
            Vertex v1 = vVertex(i0); 
            Vertex v2 = vVertex(i1);
            Vertex v3 = vVertex(i2);
            

            Point p1,p2,p3;
            
            p1 = v1.coord();
            p2 = v2.coord();
            p3 = v3.coord();
            
            vector<float> v1; v1.push_back(p1.x()); v1.push_back(p1.y()); v1.push_back(p1.z());
            vector<float> v2; v2.push_back(p2.x()); v2.push_back(p2.y()); v2.push_back(p2.z());
            vector<float> v3; v3.push_back(p2.x()); v3.push_back(p3.y()); v3.push_back(p3.z());
            
            vector<float> u,v;
            u.push_back(v1[0] - v2[0]); u.push_back(v1[1] - v2[1]); u.push_back(v1[2] - v2[2]);
            v.push_back(v1[0] - v3[0]); v.push_back(v1[1] - v3[1]); v.push_back(v1[2] - v3[2]);
            
            vector<float> cross;
            cross.push_back(u[0]*v[0]); cross.push_back(u[1]*v[1]); cross.push_back(u[2]*v[2]);
            float mod = sqrt( cross[0]*cross[0] - cross[1]*cross[1] - cross[2]*cross[2]);
            float area = mod/2.0;
            
            areaTotal += area;
        }
        cout << "Objecte " << i << " Area: " << areaTotal;
    }
    
}

#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2(draw-vbo-ext, DrawVBO)   // plugin name, plugin class
#endif
