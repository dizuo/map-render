/*
 * Quaternion slerp animation
 * dizuo
 */
#include <gtl\quat.hpp>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

gtl::Quatf begQuat;	// ��ʼ״̬
gtl::Quatf endQuat;	// ����״̬
gtl::Vec3f begPos;	
gtl::Vec3f endPos;

int frameIdx = 0;
int frameNum = 200;

float			g_fWidth = 512;			// ����Ŀ��
float			g_fHeight = 392;		// ����ĸ߶�

void	init(void);			// ��ʼ��opengl�Ļ���
void	reshape(int w,int h);	// �ú���������ı��Ժ���Ӧ�����������ӿ�
void	display(void);			// ��Ⱦopengl����
void	keyboard(unsigned char, int, int);	// ��Ӧ����¼�

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize (g_fWidth, g_fHeight);
	glutInitWindowPosition (0, 0);
	glutCreateWindow("ModelRotate");
	init ();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc( keyboard );
	glutMainLoop();
	return 0;
}


void init (void)
{ 
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClearDepth(1);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// yaw, pitch, roll
	//	Y	 X		Z
	begQuat.setValue(0,0,0);
	endQuat.setValue(0,-45,30);

	begPos.setValue(0,0,5);
	endPos.setValue(0,0,3);
}

/* Rotate about x-axis when "x" typed; rotate about y-axis
   when "y" typed; "i" returns torus to original view */
void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 27:
		exit(0);
		break;

	case 'y':
		break;
	}
	
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	g_fWidth = w;
	g_fHeight = h;

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);       //�ظ�ԭ�е�����  
    glLoadIdentity ();  
	gluPerspective(30, g_fWidth/g_fHeight, 0.001, 100.0);
}
void display(void)
{
	float alpha = frameIdx*1.0/frameNum;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gtl::Vec3f deltaPos = endPos - begPos;
	gtl::Vec3f cameraPos = begPos + alpha*deltaPos;
	// gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	gluLookAt(cameraPos.x(), cameraPos.y(), cameraPos.z(),
		0, 0, 0, 0, 1, 0);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColor3f (.0, .0, .0);  // ����Ļ��ɫ

	//glPushMatrix();
	//float rectVerticesBuf[] = {1,-1,0, 1,1,0, -1,1,0, -1,-1,0};
	//unsigned short rectIndicesBuf[] = {0,1,2, 0,2,3};
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, rectVerticesBuf);
	//glDrawElements(GL_TRIANGLES, sizeof(rectIndicesBuf)/sizeof(rectIndicesBuf[0]), GL_UNSIGNED_SHORT, rectIndicesBuf);
	//glPopMatrix();	

	glColor3f(0.4,0.4, 0);

	glPushMatrix();
	gtl::Quatf rotQuat = gtl::Quatf::slerp(begQuat, endQuat, alpha);
	gtl::Vec4f value = rotQuat.getValue();
	cout << value << endl;
	gtl::Matrix4f rotMat = rotQuat.getMatrix();
	cout << rotMat << endl;
	glMultMatrixf( rotMat );
	// glRotatef(45, 0,1,0);
	glScalef(2,2,0.3);
	glutSolidCube(1);
	glPopMatrix();

	frameIdx = (frameIdx+1) % frameNum;

	glutSwapBuffers();	// ��ֹˢ��������˫�������

	glutPostRedisplay(); // �ظ���������
}
