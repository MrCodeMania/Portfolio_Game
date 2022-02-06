#include<windows.h>
#include<MMSystem.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<math.h>

#define Timer 1

static double Scene[11] = { 0 , 0 , 0 , 0 , 0 , 0 , 1.0 , 0 , 0.04 , 0, 50 };
static bool SceneFlag[5] = { true,false,true,false,false };
static double Day[10] = { 0.9,0.9,0.8,-0.01,0.02,0.03 };
static int Divide = 0;
GLfloat R_Arm_x = 0; // ������ ���
GLfloat R_Arm_y = -50; // ������ ��
GLfloat L_Arm_x = 0; // ���� ���
GLfloat L_Arm_y = -50; // ���� ��
GLfloat R_Leg_x = 0; // ���� �����
GLfloat R_Leg_y = 30; // ���� ���Ƹ�
GLfloat L_Leg_x = 0; // �� �����
GLfloat L_Leg_y = 30; // �� ���Ƹ�

GLUquadricObj* cyl = gluNewQuadric();
static double DayFlag = 0;
static double it = 0.1f;
static int Jump = 0;
static bool BigSmall = true;
static bool RunOrWalk = true;

double RED = 0.0f;
double GREEN = 0.0f;
double BLUE = 0.0f;

static bool UpDown = true;

GLfloat MyVertices[4][3] = {
	{ 0.0, 0.036, -0.018 },
	{ -0.05, -0.05, 0.0 },
	{ 0.05, -0.05, 0.0 },
	{ 0.0, 0.0, 0.0707 },
};
GLubyte MyVertexList[12] = {
	0, 3, 2,
	0, 1, 3,
	3, 1, 2,
	2, 1, 0
};

void glInit(void) { // ���� �ʱ�ȭ �Լ� 
	glEnable(GL_DEPTH_TEST); // ���� �׽��� ���
	glEnable(GL_NORMALIZE);  // ����ȭ
	glEnable(GL_SMOOTH);     // �� ������ ������ �ε巴�� �����Ͽ� ĥ��������  �ϹǷ�, �������� ����� ������ ȥ�յǾ� ����ȴ�. 
	glEnable(GL_LIGHTING);   // ���� ����. ���� �޴� ������ ���� �κ� ������ ��ȭ

							 /* ���� �޴� ������ ���� �κ� ������ ��ȭ�� ���� ���� */
	GLfloat ambientLight[] = { 0.3f,0.3f,0.3f,1.0f };
	GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat position[] = { 400.0,300.0,-700.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glClearColor(1.0, 1.0, 1.0, 1.0); // ��� ������
	glMatrixMode(GL_PROJECTION);   // ��� ����
	glLoadIdentity();              // CTM �� �ʱ�ȭ 
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // ���� ���� ����
}

void Draw_Color() { // ������ �׸��� �Լ�
	glColor3f(0.2, 0.2, 0.2);
}

void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();       // �� ����
	glRotatef(x, a, b, c);  // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ��(�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(0.25, 0.0, 0.0);    // ���� ��� ���������� �̵�
	glRotatef(15.0, 0.0, 1.0, 0.0); // ���� ����� y���� �������� 15�� ȸ��
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
}

/*
�κ� ���� ���� �׸��� �Լ�
*/
void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();       // �� ����
	    // �Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.22); // �޼� ������
	glRotatef(y, a, b, c);        // �Ķ���� ����ŭ ȸ��
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);           // �Ǹ����� �׸�
	glPopMatrix();
}

/*
�κ� �������� �׸��� �Լ�
*/
void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();     // �� ����
	  // �Ǹ��� ��ü ����
	glRotatef(x, a, b, c);  // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x���� �������� 90�� ȸ��(�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(-0.25, 0.0, 0.0); //���� ��� ���������� �̵�
	glRotatef(-15.0, 0.0, 1.0, 0.0); //���� ��� -15�� y����� ȸ��
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// �Ǹ��� �׸�

}
/*
�κ� ������ ���� �׸��� �Լ�
*/
void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(); // �� ����
	 //�Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.22);//������ �� ������
	glRotatef(y, a, b, c);// �Ķ���Ͱ� ��ŭ ȸ��
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// �Ǹ��� �׸�
	glPopMatrix();
}

/*
�κ� ��ü�� �׸��� �Լ�
*/
void DrawBody(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();
	 //�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glRotatef(x, a, b, c);//�Ķ���Ͱ� ��ŭ ȸ��
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ���� ������� �׸��� �Լ�
*/
void DrawL_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();
	 //�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(0.1, 0.0, 0.42);//���� ����� ������
	glRotatef(x, a, b, c);//�Ķ���͸�ŭ ȸ��
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// �Ǹ��� �׸�

}
/*
�κ� ���� ���Ƹ��� �׸��� �Լ�
*/
void DrawL_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();
	 //�Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.18);//���� ���Ƹ� ������
	glRotatef(y, a, b, c);//�Ķ���͸�ŭ ȸ��
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ������ ������� �׸��� �Լ�
*/
void DrawR_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();
	 //�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(-0.1, 0.0, 0.42);//������ ����� ������
	glRotatef(x, a, b, c);//�Ķ���͸�ŭ ȸ��
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// �Ǹ��� �׸�

}
/*
�κ� ������ ���Ƹ��� �׸��� �Լ�
*/
void DrawR_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();
	 //�Ǹ��� ��ü ����

	glTranslatef(0.0, 0.0, 0.18);//������ ���Ƹ� ������
	glRotatef(y, a, b, c);//�Ķ���͸�ŭ ȸ��

	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ���� �׸��� �Լ�
*/

void Drawneck() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);//�� ����(���)
	 //�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(0.0, 0.0, 0.0); // �� ������
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
���� �׸��� �Լ�
���� Ŀ�ٶ� ���� �����Ͽ���.
���� �ð��� ���� ȸ���Ͽ��� ��ġ �κ���
������ �پ�� ������ �鵵�� �����Ͽ���.
*/
void DrawFlower()
{
	//////
	glScalef(1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0);
	glutSolidSphere(0.017, 30, 10);

	glPushMatrix();

	for (int i = 0; i < 10; i++)
	{
		glRotatef(36, 0, 0, 1);
		glPushMatrix();
		glTranslatef(0.0f, 0.017f, 0.0f);
		glColor3f(1.0, 1.0, 1.0);
		glutSolidSphere(0.01, 20, 10);
		glFlush();
		glPopMatrix();
	}
	glPopMatrix();

	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.0f, -0.049f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(cyl, 0.005, 0.005, 0.03, 50, 2);
	glPopMatrix();
	glPushMatrix();
	glRotatef(30.0, 0, 0, 1);
	glTranslatef(0.01f, -0.002f, 0.0f);
	glScalef(1.5f, 0.3f, 0.3f);
	glutSolidSphere(0.01, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(30.0, 0, 0, -1);
	glTranslatef(-0.01f, -0.002f, 0.0f);
	glScalef(1.5f, 0.3f, 0.3f);
	glutSolidSphere(0.01, 20, 10);
	glPopMatrix();
}
void DrawSun()
{
	//////
	glTranslatef(0, -0.2, 0.5);
	glRotatef(Scene[5], 0, 0, 1);

	glPushMatrix();
	glTranslatef(1.0f, 0.3f, 0.2f);
	glRotatef(-Scene[5], 0, 0, 1);
	glScalef(1.0f + Scene[4], 1.0f + Scene[4], 1.0f + Scene[4]);
	//glRotatef(30, 1, 0, 0);
	glColor3f(1.0f, 0.0f, 0);
	glutSolidSphere(0.16, 40, 10);

	glPushMatrix();

	for (int i = 0; i < 21; i++)
	{
		glRotatef(17.2, 0, 0, 1);
		glPushMatrix();
		glTranslatef(0.0f, 0.2f, 0.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, MyVertices);
		for (GLint i = 0; i < 4; i++)
		{
			glColor3f(1.0, 0.7, 0);
			glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, &MyVertexList[3 * i]);
		}
		glFlush();
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0f, -0.3f, -0.2f);
	glRotatef(-Scene[5], 0, 0, 1);
	glScalef(1.0f + Scene[4], 1.0f + Scene[4], 1.0f + Scene[4]);
	//glRotatef(30, 1, 0, 0);
	glColor3f(0.7f, 0.7f, 0.0f);
	glutSolidSphere(0.10, 40, 10);
	glPopMatrix();

	///////
}
void DrawTree()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.3f, 0.0f);
	glColor3f(0, 1.0f, 0);
	glutSolidSphere(0.28, 20, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.3f, 0.0f);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.4f, 0.15f, 0.0f);
	gluCylinder(cyl, 0.15, 0.10, 0.4, 50, 1);
	glPopMatrix();
}

void DrawEarth()
{	///////////////////// ���� /////////////////////////////////////

	glColor3f(0.2, 0.4f, 0.1);
	glutSolidSphere(0.6, 100, 30);

	glPushMatrix();
	glColor3f(0.4f, 0.15f, 0.0f);
	glRotatef(90, 0, 1, 0);
	gluCylinder(cyl, 0.605, 0.5879, 0.15, 50, 1);
	glPushMatrix();
	glTranslatef(0.0, 0, -0.15);
	gluCylinder(cyl, 0.5879, 0.605, 0.15, 50, 1);
	glPopMatrix();
	glPopMatrix();
	////////////////////// ���� ////////////////////////////////////

	glPushMatrix();
	glRotatef(50, 0, 1, 0);
	glTranslatef(0.62, 0, 0);
	glRotatef(-90, 0, 0, 1);
	DrawTree();
	glPopMatrix();

	glPushMatrix();
	glRotatef(40, 0, 0, 1);
	glTranslatef(0, 0.62, 0);
	DrawTree();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-60, 0, 0, 1);
	glRotatef(40, 1, 0, 0);
	glTranslatef(0, 0.62, 0);
	DrawTree();
	glPopMatrix();

	/////////////////////////// ���� //////////////////////////////////

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glColor3f(0.25, 0.25, 0.25);
	glTranslatef(0, 0, -0.55);//�� ������
	glutSolidSphere(0.2, 8, 10);
	glPushMatrix();
	glTranslatef(0.05, 0.05, 0.04);
	glutSolidSphere(0.2, 7, 10);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-55, 0, 1, 0);
	glColor3f(0.25, 0.25, 0.25);
	glTranslatef(0, 0, 0.55);//�� ������
	glutSolidSphere(0.2, 8, 10);
	glPushMatrix();
	glTranslatef(0.05, 0.05, -0.04);
	glutSolidSphere(0.2, 7, 10);
	glPopMatrix();
	//glPopMatrix();
}

void DrawBackGround(double R, double G, double B, double R_M, double G_M, double B_M, double mul)
{
	double Top = 1.0f;
	double Bottom = 0.9f;
	RED = R;
	GREEN = G;
	BLUE = B;

	while (Bottom > -1.1f)
	{
		glBegin(GL_POLYGON);
		glColor3f(RED - (R_M * mul), GREEN - (G_M * mul), BLUE - (B_M * mul)); // ��-��
		glVertex2f(-1, Bottom);
		glColor3f(RED, GREEN, BLUE); // ��Ȳ��
		glVertex2f(-1, Top);
		glColor3f(RED, GREEN, BLUE); // ��Ȳ��
		glVertex2f(1, Top);
		glColor3f(RED - (R_M * mul), GREEN - (G_M * mul), BLUE - (B_M * mul)); // ��-��
		glVertex2f(1, Bottom);
		glEnd();

		RED -= R_M; GREEN -= G_M; BLUE -= B_M;
		Top -= 0.1f; Bottom -= 0.1f;
	}
	if (DayFlag == 0)
	{
		Day[0] -= (0.2f / 100.0f) * Timer;
		Day[1] += (0.1f / 100.0f) * Timer;
		Day[2] += (0.2f / 100.0f) * Timer;
		Day[3] += (0.01f / 100.0f) * Timer;
		Day[4] -= (1.02f / 100.0f) * Timer;
		Day[5] -= (1.03f / 100.0f) * Timer;
	}
	else if (DayFlag == 1)
	{
		Day[0] += (0.2f / 500.0f) * Timer;
		Day[1] -= (0.1f / 500.0f) * Timer;
		Day[2] -= (0.1f / 500.0f) * Timer;
		Day[3] += (0.09f / 500.0f) * Timer;
		Day[4] += (1.09f / 500.0f) * Timer;
		Day[5] += (1.05f / 500.0f) * Timer;
	}
	else if (DayFlag == 2)
	{
		Day[2] -= (0.1f / 600.0f) * Timer;
		Day[3] -= (0.1f / 600.0f) * Timer;
		Day[4] -= (0.07f / 600.0f) * Timer;
		Day[5] -= (0.02f / 600.0f) * Timer;
	}

	if (Day[3] < 0)
		DayFlag = 0;
	else if (Day[5] < -1.00f)
		DayFlag = 1;
	else if (Day[5] > 0.05f)
		DayFlag = 2;
}

void DrawGround() {
	glRotatef(0.0 + Scene[3] - 15, 0.0, 0.0, 1);// z�� �������� time4��ŭ ���� ȸ�� 
	glPushMatrix();
	glColor3f(0.4f, 0.15f, 0.0f);
	glRotatef(90, 0, 1, 0);
	gluCylinder(cyl, 0.605, 0.5879, 0.15, 50, 1);
	glPushMatrix();
	glTranslatef(0.0, 0, -0.15);
	gluCylinder(cyl, 0.5879, 0.605, 0.15, 50, 1);
	glPopMatrix();
	glPopMatrix();
}
/*
�κ� �Ӹ��� �׸��� �Լ�
�κ��� �Ӹ��� �޷��ִ� �԰�
�κ��� ���� �����Ͽ���.
*/
void DrawHead() {
	glTranslatef(0.0, 0.02, 0.0);//�Ӹ� ������
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����
	 
	//Change_Wire_Or_Solid(flag);
	Draw_Color();//���� ����
	gluSphere(cyl, 0.20, 30, 10);//�Ӹ� �׸���
								 /*���� �� �׸���*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(-0.16, 0.0, -0.22);//���� �� ������
	glRotatef(35.0, 0.0, 1.0, 0.0);//35�� y�� ���� ȸ��
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);//�Ǹ��� �׸�
	glPopMatrix(); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

				   /*������ �� �׸���*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(0.16, 0.0, -0.22);//������ �� ������
	glRotatef(-35.0, 0.0, 1.0, 0.0);//-35�� y�� ���� ȸ��
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);//�Ǹ��� �׸�
	glPopMatrix(); // ó�� ���� ��ǥ�� ���� ����.	
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

				   /*���� �� �׸���*/
	glTranslatef(-0.1, 0.1, 0.13);//���� �� ������
	glColor3f(0.0, 0.0, 0.0);// �� �÷� ����(���)
	gluSphere(cyl, 0.03, 10, 10);

	glPopMatrix(); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

				   /*������ �� �׸���*/
	glTranslatef(0.1, 0.1, 0.13);//������ �� ������
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();// ó�� ���� ��ǥ �ٽ� ����

	
}
/*
�ȵ���̵� ��ü ����� �׸��� �Լ�
*/
void DrawAndroid() {
	Drawneck(); // ���Լ� ȣ��
	DrawHead(); // �Ӹ� ȣ��
	DrawBody(0, 0, 0, 0); // ���� �Լ� ȣ��
	DrawL_Legs(L_Leg_x, 1, 0, 0);  //�����ٸ�
	DrawL_foot(L_Leg_y, 1, 0, 0);  //������		 
	DrawR_Legs(R_Leg_x, 1, 0, 0);  //�����ٸ�
	DrawR_foot(R_Leg_y, 1, 0, 0);  //������
	DrawL_Arm(L_Arm_x, 1, 0, 0);   //�����ȶ�
	DrawL_Hand(L_Arm_y, 1, 0, 0);//������ȣ��
	DrawR_Arm(R_Arm_x, 1, 0, 0);//�����ȶ�
	DrawR_Hand(R_Arm_y, 1, 0, 0);  //������ȣ��

}


double abs(double x)
{
	if (x >= 0)
		return x;
	else return -x;
}

void Cry()
{
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW);
	
	
	glRotatef(180.0, 0, 1, 0);
	glRotatef(30.0, 1, 0, 0);
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����


	glTranslatef(0.0, 0.0, 0.0);//���� �κ��� ��ġ 
	glScalef(3.0, 3.0, 3.0);

	DrawL_Legs(L_Leg_x, 1, 0, 0);  //�����ٸ�
	DrawL_foot(L_Leg_y, 1, 0, 0);  //������		 
	DrawR_Legs(R_Leg_x, 1, 0, 0);  //�����ٸ�
	DrawR_foot(R_Leg_y, 1, 0, 0);  //������

	DrawR_Arm(R_Arm_x, 1, 0, 0);//�����ȶ�
	DrawR_Hand(R_Arm_y, 1, 0, 0);  //������ȣ��

	glRotatef(-50, 1, 0, 0);
	DrawL_Arm(0, 1, 0, 0);   //�����ȶ�

	glRotatef(45, 0, 0, 1);
	DrawL_Hand(-100, 1, 0, 0);//������ȣ��
	
	double Angle = sin(Scene[0]) * 5 + 50;

	if(Angle >= 54.99 && Scene[5] == 1)
		UpDown = false;

	glRotatef(Angle, 1, 0, 0);
	glRotatef(sin(Scene[4]) * 10, 0, 1, 0);
	Drawneck(); // ���Լ� ȣ��
	DrawHead(); // �Ӹ� ȣ��
	DrawBody(0, 0, 0, 0); // ���� �Լ� ȣ��
	
	glPushMatrix();
	glTranslatef(-0.110 + Scene[1], 0.066 + Scene[2], 0.124 + Scene[3]);
	glColor3f(0.1f, 0.1f, 0.977f);
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();
	
	glutSwapBuffers();
	glPopMatrix();
}

void CryToRun()
{
	glLoadIdentity();
	 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW);
	
	L_Arm_x = 0;           //������ 80�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	R_Arm_x = -L_Arm_x;               //�������� ���ȹݴ�� 80���������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����.
	R_Arm_y = -50;  //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 
	L_Arm_y = -100; //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 

	R_Leg_y = 30;  //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	L_Leg_y = 30;   //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	R_Leg_x = 0;          //�����ٸ��� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	L_Leg_x = -R_Leg_x;

	glPushMatrix();

	glRotatef(180.0 - Scene[1], 0, 1, 0);
	glRotatef(30.0 - Scene[3], 1, 0, 0);
	glTranslatef(0.0, Scene[2], 0.2);//���� �κ��� ��ġ 
	glScalef(Scene[0], Scene[0], Scene[0]);
	DrawAndroid();
	glutSwapBuffers();
	glPopMatrix();
}

void Run() {
	sndPlaySound(TEXT("../JilPung.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity();//CTM �ʱ�ȭ
					 /*
					 �⺻���� �κ��� �������� ���ӵ��� sin() �Լ��� ���� ǥ���Ͽ���
					 ���� ������ ���ѹ����� �����Ͽ� abs() �Լ��� ���� ������ �������� �����Ͽ���.
			*/
	if (RunOrWalk)
	{
		if (Jump == 0)
		{
			L_Arm_x = sin(Scene[0]) * 80;           //������ 80�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
			R_Arm_x = -L_Arm_x;               //�������� ���ȹݴ�� 80���������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����.
			R_Arm_y = -abs(sin(Scene[0]) * 60 + 50);  //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 
			L_Arm_y = -abs(-sin(Scene[0]) * 60 + 50); //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 

			R_Leg_y = abs(-sin(Scene[0]) * 30 - 30);  //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
			L_Leg_y = abs(sin(Scene[0]) * 30 - 30);   //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
			R_Leg_x = sin(Scene[0]) * 60;          //�����ٸ��� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
			L_Leg_x = -R_Leg_x;              //�����ٸ��� �����ٸ��ݴ�� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

			if (L_Arm_x <= 0)
				Jump = 1;				 ////////////////display////////////////
		}
		else if (Jump == 1)
		{
			L_Arm_x = -abs(sin(Scene[0]) * 160);
			R_Arm_x = -abs(sin(Scene[0]) * 160);
			L_Arm_y = -abs(sin(Scene[0]) * 20) - 50;
			R_Arm_y = -abs(sin(Scene[0]) * 20) - 50;

			R_Leg_y = abs(sin(Scene[0]) * 120);
			L_Leg_y = abs(sin(Scene[0]) * 120);
			R_Leg_x = -abs(sin(Scene[0]) * 50);
			L_Leg_x = -R_Leg_x;

			if (L_Arm_x >= -20)
				Jump = 0;
		}
	}
	else if(!RunOrWalk)
	{
		L_Arm_x = sin(Scene[0]) * 80 * Scene[6];           //������ 80�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
		R_Arm_x = -L_Arm_x;               //�������� ���ȹݴ�� 80���������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����.
		R_Arm_y = -abs(sin(Scene[0]) * 60  + 50)* Scene[6];  //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 
		L_Arm_y = -abs(-sin(Scene[0]) * 60 + 50) * Scene[6]; //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 

		R_Leg_y = abs(-sin(Scene[0]) * 30 - 30) * Scene[6];  //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
		L_Leg_y = abs(sin(Scene[0]) * 30 - 30) * Scene[6];   //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
		R_Leg_x = sin(Scene[0]) * 60 * Scene[6];          //�����ٸ��� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
		L_Leg_x = -R_Leg_x;              //�����ٸ��� �����ٸ��ݴ�� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����

	DrawSun();

	glLoadIdentity();//CTM �ʱ�ȭ
	if(RunOrWalk)
		glRotatef(sin(Scene[0]) * 10, 0, 1, 0); //y������ 16�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	else if(!RunOrWalk)
		glRotatef(sin(Scene[0]) * 8, 0, 1, 0); //y������ 16�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	glPushMatrix();
	glTranslatef(0, -0.9, 0.2);
	glRotatef((Scene[0] * 30), 1, 0, 1);
	glRotatef(135, 0, 1, 0);
	DrawEarth();
	glPopMatrix();

	glLoadIdentity();//CTM �ʱ�ȭ
	glTranslatef(0, 0, 0.7);
	DrawBackGround(Day[0], Day[1], Day[2], Day[3], Day[4], Day[5], 1); // ����
	
					 /*
					 �κ��� �޸��鼭 ��,�ڷ� �ڶװŸ��� ���� Ʋ������ ���� ǥ��
					 */
	glLoadIdentity();//CTM �ʱ�ȭ

	if (RunOrWalk)
	{
		glRotatef(abs(sin(Scene[0]) * 13), 1, 0, 0);//x������ 16�� ���� ����Ʋ����(abs���밪�� �����ν� ��ü�� �ڷ� ������ �ʴ� �Ѱ����� ����)
		glRotatef(sin(Scene[0]) * 15 + 135, 0, 1, 0); //y������ 16�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

		float i = 0;
		i = abs(sin(Scene[0])*0.05 + 0.04); //i������ ����
		glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

		glTranslatef(0.0, i, 0); //���� i��ŭ �κ��� ��ü�� Y��������� ������.
		glTranslatef(0.0, 0.3, 0.2);//���� �κ��� ��ġ 

		glScalef(0.8f, 0.8f, 0.8f);
		DrawAndroid();
		glPopMatrix();
	}
	
	else if(!RunOrWalk)
	{
		glRotatef(abs(sin(Scene[0]) * 13)* Scene[6], 1, 0, 0); //y������ 16�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

		glRotatef((sin(Scene[0]) * 15)+ 135 - Scene[9], 0, 1, 0); //y������ 16�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

		float i = 0;
		i = abs(sin(Scene[0])*0.05 + Scene[8]); //i������ ����
		glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

		glTranslatef(0.0, i, 0); //���� i��ŭ �κ��� ��ü�� Y��������� ������.
		glTranslatef(0.0 + Scene[7], 0.3, 0.2);//���� �κ��� ��ġ 

		glScalef(0.8f, 0.8f, 0.8f);
		DrawAndroid();
		glPopMatrix();
	}

	glutSwapBuffers();
	glPopMatrix();

	//����ģ���� �ο���
	//��ǳ����
	//�¿� - ����ؿ�
}

void Final()
{
	glLoadIdentity();

	L_Arm_x = -abs(sin(Scene[0]) * 60);           //������ 80�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	R_Arm_x = L_Arm_x;               //�������� ���ȹݴ�� 80���������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����.
	R_Arm_y = -abs(sin(Scene[0]) * 30);  //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 
	L_Arm_y = -abs(sin(Scene[0]) * 30); //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 

	R_Leg_y = abs(-sin(Scene[0]) * 90);  //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	L_Leg_y = abs(sin(Scene[0]) * 60 );   //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	R_Leg_x = 0;          //�����ٸ��� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	L_Leg_x = -sin(Scene[0]) * 60;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����

	DrawSun();

	glLoadIdentity();//CTM �ʱ�ȭ
	glTranslatef(0, 0, 0.7);
	DrawBackGround(Day[0], Day[1], Day[2], Day[3], Day[4], Day[5], 1); // ����


	glLoadIdentity();//CTM �ʱ�ȭ

	glPushMatrix();
	glTranslatef(0, -0.9, 0.2);
	glRotatef(135 + Scene[2], 0, 1, 0);
	DrawEarth();
	glPopMatrix();
	
	glLoadIdentity();//CTM �ʱ�ȭ
	
	glRotatef(135 + Scene[2], 0, 1, 0); //y������ 16�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	glRotatef(abs(sin(Scene[0]) * 20), 1, 0, 0);//x������ 16�� ���� ����Ʋ����(abs���밪�� �����ν� ��ü�� �ڷ� ������ �ʴ� �Ѱ����� ����)
	
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

	glTranslatef(0.0, 0.4 - Scene[1], 0.2);//���� �κ��� ��ġ 

	glScalef(0.8f, 0.8f, 0.8f); 
	Drawneck(); // ���Լ� ȣ��
	DrawHead(); // �Ӹ� ȣ��
	DrawBody(0, 0, 0, 0); // ���� �Լ� ȣ��
	DrawL_Legs(L_Leg_x, 1, 0, 0);  //�����ٸ�
	DrawL_foot(L_Leg_y, 1, 0, 0);  //������		 
	DrawR_Legs(R_Leg_x, 1, 0, 0);  //�����ٸ�
	DrawR_foot(R_Leg_y, 1, 0, 0);  //������
	DrawL_Arm(L_Arm_x, 1, 1, 0);   //�����ȶ�
	DrawL_Hand(L_Arm_y, 1, 1, 0);//������ȣ��
	DrawR_Arm(R_Arm_x, 1, -1, 0);//�����ȶ�
	DrawR_Hand(R_Arm_y, 1, -1, 0);  //������ȣ��
	glPopMatrix();
	glTranslatef(0.0, -0.2 + Scene[6], 0.5);
	glScalef(1.2, 1.2, 1.2);
	DrawFlower();
	glutSwapBuffers();
	glPopMatrix();
}

void MyDisplay()
{
	if (SceneFlag[0])
	{							// ���� �帧, ��
		Scene[1] -= 0.00004 * Timer;
		Scene[2] -= 0.0007 * Timer;
		Scene[3] += 0.000042 * Timer;

		if (UpDown)
		{
			Scene[0] += 0.1 * Timer;
			Scene[5] = 1 * Timer;
		}
		else if (!UpDown)
		{
			Scene[4] += 0.1 * Timer;
			Divide += 1;
			if (Divide % (62 / Timer) == 0)
			{
				UpDown = true;
				Scene[5] = 0;
			}
		}

		if (Scene[2] < -0.063f)	// ���� ó�� ��ġ
		{
			Scene[1] = 0.0f;
			Scene[2] = 0.0f;
			Scene[3] = 0.0f;
		}
		Cry();
		if (Scene[0] > 14)
		{
			SceneFlag[0] = false;
			SceneFlag[1] = true;
			Scene[0] = 3.0f;
			Scene[1] = 0.0f;
			Scene[2] = 0.0f;
			Scene[3] = 0.0f;
			Scene[4] = 0.0f;
		}
	}
	else if (SceneFlag[1])
	{
		Scene[0] -= (2.2 / 90) * Timer;
		Scene[1] += 0.5;
		Scene[2] += (0.3 / 90) * Timer;
		Scene[3] += (30.0 / 90.0) * Timer;
		Scene[4] += (0.1 / 90) * Timer;
		CryToRun();
		if (Scene[0] < 0.8f)
		{
			SceneFlag[1] = false;
			SceneFlag[2] = true;
			Scene[0] = 0.0f;
			Scene[1] = 0.0f;
			Scene[2] = 0.0f;
			Scene[3] = 0.0f;
			Scene[4] = -0.3f;
			Scene[5] = 0.0f;
		}
	}
	else if (SceneFlag[2])
	{
		Scene[1] -= 0.01f * Timer;
		Scene[2] += 0.0001f * Timer;
		Scene[3] += 3.0f * Timer;
		Scene[5] += 0.3f * Timer;
	
		if (Scene[4] > 0.4)
			BigSmall = false;
		else if (Scene[4] < -0.4)
			BigSmall = true;

		if (BigSmall)
			Scene[4] += (0.8f / 300.0f) * Timer;
		else if (!BigSmall)
			Scene[4] -= (0.8f / 300.0f) * Timer;

		if (Scene[0] > 125)
		{
			SceneFlag[2] = false;
			SceneFlag[3] = true;
			Scene[1] = 0.0f;
			Scene[2] = 0.0f;
			Scene[3] = 0.0f;
			Scene[6] = 0.0f;
			Scene[7] = 0.0f;
			Scene[8] = 0.0f;
			Scene[9] = 0.0f;
			Scene[10] = 0.0f;
		}
		else if (Scene[6] < 0.3f)
			Scene[0] += 0.04f * Timer;
		else if (!RunOrWalk)
		{
			Scene[0] += it * Timer;
			Scene[6] -= 0.7f / 150.0f * Timer;
			Scene[7] += (0.2 / 150.0f) * Timer;
			Scene[8] -= (0.04 / 150.0f) * Timer;
			it -= 0.0004f * Timer;
			if(Scene[9] < 15)
				Scene[9] += (15 / 150.0f) * Timer;
			if (Scene[10] > 0)
				Scene[10] -= (50 / 150.0f) * Timer;
		}
		else if (L_Arm_x >= 0 && Scene[0] > 100)
			RunOrWalk = false;
		else
			Scene[0] += 0.1f * Timer;

		
		Run();
	}
	else if (SceneFlag[3])
	{
		Scene[5] += 0.3f * Timer;

		if (Scene[4] > 0.4)
			BigSmall = false;
		else if (Scene[4] < -0.4)
			BigSmall = true;

		if (BigSmall)
			Scene[4] += (0.8f / 300.0f) * Timer;
		else if (!BigSmall)
			Scene[4] -= (0.8f / 300.0f) * Timer;

		if (L_Arm_x >= -59)
		{
			Scene[6] += 0.3f / 130.0f;
			Scene[2] += 30.0f / 130.0f;
			Scene[0] += 0.01f;
			Scene[1] += (0.08f / 100.0f);
		}
		Final();
	}
}

void MyTimer(int Value) {
	glutPostRedisplay();
	glutTimerFunc(20, MyTimer, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);//�ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//���÷��� ��� ����
	glutInitWindowSize(800, 800);//������ ũ�� ����
	glutInitWindowPosition(0, 0);//������ �ʱ� ��ġ ����
	glutCreateWindow("������Ʈ");//������ ����
	glInit(); // ���� �ʱ�ȭ
	
	glutTimerFunc(50, MyTimer, 1); //Ÿ�̸� �Լ�
	glutDisplayFunc(MyDisplay); //���÷���
	glutMainLoop();
	return 0;
}