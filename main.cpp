#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat image;

float t=0;
float vx=0;
float vy=0;
float vz=1;

void display(void);
void update(int num);


int main(int argc, char *argv[]){
    image=imread("/home/EdwinLara/Documentos/Proyectos/build-iluminacion-Desktop-Debug/2.bmp",CV_LOAD_IMAGE_COLOR);
    cout<<image.cols<<" "<<image.rows<<endl;
    glutInit(&argc,argv);
    //glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,480);
    glutCreateWindow("imagen");
    glRotated(45,1.0,0.0,0.0);
    glutDisplayFunc(display);
    glutPostRedisplay();
    glutTimerFunc(100,update,0);
    glutMainLoop();
    return 0;
}

void display(void){
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT1);
        GLfloat lightColor1[]={0.0,0.0,1.0,0.0};
        GLfloat lightPos[]={cos(t),sin(t),1.0,7};
        glLightfv(GL_LIGHT3,GL_DIFFUSE,lightColor1);
        glLightfv(GL_LIGHT3,GL_POSITION,lightPos);

        GLfloat lightColor2[]={1.0,0.0,0.0,0.0};
        GLfloat lightPos1[]={-cos(t),-sin(t),1.0,7};
        glLightfv(GL_LIGHT1,GL_DIFFUSE,lightColor2);
        glLightfv(GL_LIGHT1,GL_POSITION,lightPos1);

    for(float x=0;x<image.cols-1;x++)
        for(float y=0;y<image.rows;y++)
        {
            float t11x = x;
            float t11y = y;
            float t11z = ((float)image.at<Vec3b>(y,x)[2]+(float)image.at<Vec3b>(y,x)[1] +(float)image.at<Vec3b>(y,x)[0])/255/3;

            float t12x = x;
            float t12y = y+1;
            float t12z = ((float)image.at<Vec3b>(y+1,x)[2]+(float)image.at<Vec3b>(y+1,x)[1] +(float)image.at<Vec3b>(y+1,x)[0])/255/3;

            float t13x = x+1;
            float t13y = y+1;
            float t13z = ((float)image.at<Vec3b>(y+1,x+1)[2]+(float)image.at<Vec3b>(y+1,x+1)[1] +(float)image.at<Vec3b>(y+1,x+1)[0])/255/3;

            float v11x = t12x - t11x;
            float v11y = t12y - t11y;
            float v11z = t12z - t11z;

            float v12x = t13x - t11x;
            float v12y = t13y - t11y;
            float v12z = t13z - t11z;

            float vn1x = -(v11y*v12z-v11z*v12y);
            float vn1y = -(v11z*v12x-v11x*v12z);
            float vn1z = -(v11x*v12y-v11y*v12x);

            vn1x /= sqrt(vn1x*vn1x + vn1y*vn1y + vn1z*vn1z);
            vn1y /= sqrt(vn1x*vn1x + vn1y*vn1y + vn1z*vn1z);
            vn1z /= sqrt(vn1x*vn1x + vn1y*vn1y + vn1z*vn1z);

            float intensidad  =  vn1x*vx + vn1y*vy + vn1z*vz;

            glBegin(GL_TRIANGLES);
                glNormal3f(vn1x,vn1y,vn1z);
                glColor3f(1.0,1.0,1.0);
                glVertex3f(2*t11x/(image.cols)-1, 1-2*t11y/(image.rows),t11z/5);
                glVertex3f(2*t12x/(image.cols)-1, 1-2*t12y/(image.rows),t12z/5);
                glVertex3f(2*t13x/(image.cols)-1, 1-2*t13y/(image.rows),t13z/5);
            glEnd();

                        float t21x = x;
                        float t21y = y;
                        float t21z = ((float)image.at<Vec3b>(y,x)[2]+(float)image.at<Vec3b>(y,x)[1] +(float)image.at<Vec3b>(y,x)[0])/255/3;

                        float t22x = x+1;
                        float t22y = y;
                        float t22z = ((float)image.at<Vec3b>(y,x+1)[2]+(float)image.at<Vec3b>(y,x+1)[1] +(float)image.at<Vec3b>(y,x+1)[0])/255/3;

                        float t23x = x+1;
                        float t23y = y+1;
                        float t23z = ((float)image.at<Vec3b>(y+1,x+1)[2]+(float)image.at<Vec3b>(y+1,x+1)[1] +(float)image.at<Vec3b>(y+1,x+1)[0])/255/3;

                        float v21x = t22x - t21x;
                        float v21y = t22y - t21y;
                        float v21z = t22z - t21z;

                        float v22x = t23x - t21x;
                        float v22y = t23y - t21y;
                        float v22z = t23z - t21z;

                        float vn2x = (v21y*v12z-v21z*v22y);
                        float vn2y = (v21z*v12x-v21x*v22z);
                        float vn2z = (v21x*v12y-v21y*v22x);

                        vn2x /= sqrt(vn2x*vn2x + vn2y*vn2y + vn2z*vn2z);
                        vn2y /= sqrt(vn2x*vn2x + vn2y*vn2y + vn2z*vn2z);
                        vn2z /= sqrt(vn2x*vn2x + vn2y*vn2y + vn2z*vn2z);

                        float intensidad2  =  vn2x*vx + vn2y*vy + vn2z*vz;

                        glBegin(GL_TRIANGLES);
                            glNormal3f(vn2x,vn2y,vn2z);
                            glColor3f(1.0,1.0,1.0);
                            glVertex3f(2*t21x/(image.cols)-1, 1-2*t21y/(image.rows),t21z/5);
                            glVertex3f(2*t22x/(image.cols)-1, 1-2*t22y/(image.rows),t22z/5);
                            glVertex3f(2*t23x/(image.cols)-1, 1-2*t23y/(image.rows),t23z/5);
                        glEnd();
        }
    glFlush();
}

void update(int num){
    t += 0.1;
    vx=cos(t);
    vy=sin(t);
    glutPostRedisplay();
    glutTimerFunc(100,update,0);
    glRotated(0.5,0.0,0.0,1.0);
}
