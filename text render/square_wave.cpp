#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "controller.h"

static float rotAngle = 0.0f;
static float skewAngle = 0.0f;

static float cameraZ = 7.0f;
static float cameraY = 5.0f;

item_t* g_seed_items = NULL;
int	g_seed_num = 0;

float			g_fWidth = 500;			// ����Ŀ��
float			g_fHeight = 592;		// ����ĸ߶�

void	init(void);				// ��ʼ��opengl�Ļ���
void	reshape(int w, int h);	// �ú���������ı��Ժ���Ӧ�����������ӿ�
void	display(void);			// ��Ⱦopengl����
void	keyboard(unsigned char, int, int);	// ��Ӧ����¼�

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(g_fWidth, g_fHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("WaveDemo");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void load_seed_items(const char* fname)
{
	FILE* fp = fopen(fname, "r");
	if (!fp)
		return;

	char buffer[1024];
	g_seed_num = 0;
	int item_id = 0;
	const char* token = ", \t\n\r";

	while (fgets(buffer, 1024, fp))
	{
		if (g_seed_num == 0)
		{
			g_seed_num = atoi(buffer);

			if (g_seed_items)
				delete[] g_seed_items;
			
			g_seed_items = new item_t[g_seed_num];
			continue;
		}
		
		if (strlen(buffer) < 2)
			continue;

		if (!g_seed_items)
			continue;
		
		item_t& item = g_seed_items[item_id++];
		char* pch = strtok(buffer, token);
		item.pos[0] = atof(pch);

		pch = strtok(NULL, token);
		item.pos[1] = atof(pch);

		pch = strtok(NULL, token);
		item.size[0] = atof(pch);

		pch = strtok(NULL, token);
		item.size[1] = atof(pch);

		pch = strtok(NULL, token);
		item.height = atof(pch);

	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1);
	glShadeModel(GL_SMOOTH);

	load_seed_items("seed_items.txt");

	// glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
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
	default:
		break;
	}

	glutPostRedisplay();
}

void reshape(int w, int h)
{
	g_fWidth = w;
	g_fHeight = h;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);       //�ظ�ԭ�е�����  
	glLoadIdentity();
	gluPerspective(30, g_fWidth / g_fHeight, 0.001, 100.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
	//-----------------------------------------------------------------------------------------
	// 3D perspective
	//-----------------------------------------------------------------------------------------

	glPushMatrix();
	{
		// ������ɫ���飬���ö��㡢��������
		glDisableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glColor4f(1, 0, 0, 0.5f);

		float verts[] = {0,0,0, 1,0,0, 0,0,1};
		glVertexPointer(3, GL_FLOAT, 0, verts);
		glDrawArrays(GL_TRIANGLES, 0, 3);

	} glPopMatrix();

	
	glutSwapBuffers();
}
