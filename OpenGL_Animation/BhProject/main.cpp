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
GLfloat R_Arm_x = 0; // 오른쪽 어깨
GLfloat R_Arm_y = -50; // 오른쪽 팔
GLfloat L_Arm_x = 0; // 왼쪽 어깨
GLfloat L_Arm_y = -50; // 왼쪽 팔
GLfloat R_Leg_x = 0; // 오른 허벅지
GLfloat R_Leg_y = 30; // 오른 종아리
GLfloat L_Leg_x = 0; // 왼 허벅지
GLfloat L_Leg_y = 30; // 왼 종아리

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

void glInit(void) { // 지엘 초기화 함수 
	glEnable(GL_DEPTH_TEST); // 깊이 테스팅 사용
	glEnable(GL_NORMALIZE);  // 정규화
	glEnable(GL_SMOOTH);     // 각 정점의 색상을 부드럽게 연결하여 칠해지도록  하므로, 각정점에 적용된 색상이 혼합되어 적용된다. 
	glEnable(GL_LIGHTING);   // 지엘 조명. 빛을 받는 각도에 따라 로봇 색상이 변화

							 /* 빛을 받는 각도에 따라 로봇 색깔의 변화를 위한 설정 */
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

	glClearColor(1.0, 1.0, 1.0, 1.0); // 배경 검은색
	glMatrixMode(GL_PROJECTION);   // 모드 설정
	glLoadIdentity();              // CTM 값 초기화 
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 가시 범위 설정
}

void Draw_Color() { // 색상을 그리는 함수
	glColor3f(0.2, 0.2, 0.2);
}

void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();       // 색 설정
	glRotatef(x, a, b, c);  // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해)
	glTranslatef(0.25, 0.0, 0.0);    // 왼쪽 어깨 시작점으로 이동
	glRotatef(15.0, 0.0, 1.0, 0.0); // 왼쪽 어깨를 y축을 기준으로 15도 회전
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
}

/*
로봇 왼쪽 손을 그리는 함수
*/
void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();       // 색 설정
	    // 실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22); // 왼손 시작점
	glRotatef(y, a, b, c);        // 파라미터 값만큼 회전
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);           // 실린더를 그림
	glPopMatrix();
}

/*
로봇 오른팔을 그리는 함수
*/
void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();     // 색 설정
	  // 실린더 객체 생성
	glRotatef(x, a, b, c);  // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축을 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해)
	glTranslatef(-0.25, 0.0, 0.0); //우측 어깨 시작점으로 이동
	glRotatef(-15.0, 0.0, 1.0, 0.0); //우측 어깨 -15도 y축기준 회전
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림

}
/*
로봇 오른쪽 손을 그리는 함수
*/
void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(); // 색 설정
	 //실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22);//오른쪽 손 시작점
	glRotatef(y, a, b, c);// 파라미터값 만큼 회전
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}

/*
로봇 몸체를 그리는 함수
*/
void DrawBody(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();
	 //실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glRotatef(x, a, b, c);//파라미터값 만큼 회전
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 왼쪽 허벅지를 그리는 함수
*/
void DrawL_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();
	 //실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.1, 0.0, 0.42);//왼쪽 허벅지 시작점
	glRotatef(x, a, b, c);//파라미터만큼 회전
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// 실린더 그림

}
/*
로봇 왼쪽 종아리를 그리는 함수
*/
void DrawL_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();
	 //실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.18);//왼쪽 종아리 시작점
	glRotatef(y, a, b, c);//파라미터만큼 회전
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 오른쪽 허벅지를 그리는 함수
*/
void DrawR_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();
	 //실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(-0.1, 0.0, 0.42);//오른쪽 허벅지 시작점
	glRotatef(x, a, b, c);//파라미터만큼 회전
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// 실린더 그림

}
/*
로봇 오른쪽 종아리를 그리는 함수
*/
void DrawR_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color();
	 //실린더 객체 생성

	glTranslatef(0.0, 0.0, 0.18);//오른쪽 종아리 시작점
	glRotatef(y, a, b, c);//파라미터만큼 회전

	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 목을 그리는 함수
*/

void Drawneck() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);//색 지정(흰색)
	 //실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.0, 0.0, 0.0); // 목 시작점
	//Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1);// 실린더 그림
	glPopMatrix();
}
/*
땅을 그리는 함수
땅은 커다란 구로 설정하였다.
땅은 시간에 따라 회전하여서 마치 로봇이
앞으로 뛰어가는 느낌이 들도록 설계하였다.
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
{	///////////////////// 지구 /////////////////////////////////////

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
	////////////////////// 나무 ////////////////////////////////////

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

	/////////////////////////// 바위 //////////////////////////////////

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glColor3f(0.25, 0.25, 0.25);
	glTranslatef(0, 0, -0.55);//땅 시작점
	glutSolidSphere(0.2, 8, 10);
	glPushMatrix();
	glTranslatef(0.05, 0.05, 0.04);
	glutSolidSphere(0.2, 7, 10);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-55, 0, 1, 0);
	glColor3f(0.25, 0.25, 0.25);
	glTranslatef(0, 0, 0.55);//땅 시작점
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
		glColor3f(RED - (R_M * mul), GREEN - (G_M * mul), BLUE - (B_M * mul)); // 주-남
		glVertex2f(-1, Bottom);
		glColor3f(RED, GREEN, BLUE); // 주황색
		glVertex2f(-1, Top);
		glColor3f(RED, GREEN, BLUE); // 주황색
		glVertex2f(1, Top);
		glColor3f(RED - (R_M * mul), GREEN - (G_M * mul), BLUE - (B_M * mul)); // 주-남
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
	glRotatef(0.0 + Scene[3] - 15, 0.0, 0.0, 1);// z축 기준으로 time4만큼 땅이 회전 
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
로봇 머리를 그리는 함수
로봇의 머리에 달려있는 뿔과
로봇의 눈을 설정하였다.
*/
void DrawHead() {
	glTranslatef(0.0, 0.02, 0.0);//머리 시작점
	glPushMatrix();// 처음 저장 좌표 다시 저장
	 
	//Change_Wire_Or_Solid(flag);
	Draw_Color();//색깔 설정
	gluSphere(cyl, 0.20, 30, 10);//머리 그리기
								 /*왼쪽 뿔 그리기*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(-0.16, 0.0, -0.22);//왼쪽 뿔 시작점
	glRotatef(35.0, 0.0, 1.0, 0.0);//35도 y축 기준 회전
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);//실린더 그림
	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

				   /*오른쪽 뿔 그리기*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.16, 0.0, -0.22);//오른쪽 뿔 시작점
	glRotatef(-35.0, 0.0, 1.0, 0.0);//-35도 y축 기준 회전
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);//실린더 그림
	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.	
	glPushMatrix();// 처음 저장 좌표 다시 저장

				   /*왼쪽 눈 그리기*/
	glTranslatef(-0.1, 0.1, 0.13);//왼쪽 눈 시작점
	glColor3f(0.0, 0.0, 0.0);// 눈 컬러 설정(흑색)
	gluSphere(cyl, 0.03, 10, 10);

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

				   /*오른쪽 눈 그리기*/
	glTranslatef(0.1, 0.1, 0.13);//오른쪽 눈 시작점
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();// 처음 저장 좌표 다시 저장

	
}
/*
안드로이드 전체 모습을 그리는 함수
*/
void DrawAndroid() {
	Drawneck(); // 목함수 호출
	DrawHead(); // 머리 호출
	DrawBody(0, 0, 0, 0); // 몸통 함수 호출
	DrawL_Legs(L_Leg_x, 1, 0, 0);  //좌측다리
	DrawL_foot(L_Leg_y, 1, 0, 0);  //좌측발		 
	DrawR_Legs(R_Leg_x, 1, 0, 0);  //우측다리
	DrawR_foot(R_Leg_y, 1, 0, 0);  //우측발
	DrawL_Arm(L_Arm_x, 1, 0, 0);   //좌측팔뚝
	DrawL_Hand(L_Arm_y, 1, 0, 0);//좌측손호출
	DrawR_Arm(R_Arm_x, 1, 0, 0);//우측팔뚝
	DrawR_Hand(R_Arm_y, 1, 0, 0);  //우측팔호출

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
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW);
	
	
	glRotatef(180.0, 0, 1, 0);
	glRotatef(30.0, 1, 0, 0);
	glPushMatrix();// 처음 저장 좌표 다시 저장


	glTranslatef(0.0, 0.0, 0.0);//최초 로봇의 위치 
	glScalef(3.0, 3.0, 3.0);

	DrawL_Legs(L_Leg_x, 1, 0, 0);  //좌측다리
	DrawL_foot(L_Leg_y, 1, 0, 0);  //좌측발		 
	DrawR_Legs(R_Leg_x, 1, 0, 0);  //우측다리
	DrawR_foot(R_Leg_y, 1, 0, 0);  //우측발

	DrawR_Arm(R_Arm_x, 1, 0, 0);//우측팔뚝
	DrawR_Hand(R_Arm_y, 1, 0, 0);  //우측팔호출

	glRotatef(-50, 1, 0, 0);
	DrawL_Arm(0, 1, 0, 0);   //좌측팔뚝

	glRotatef(45, 0, 0, 1);
	DrawL_Hand(-100, 1, 0, 0);//좌측손호출
	
	double Angle = sin(Scene[0]) * 5 + 50;

	if(Angle >= 54.99 && Scene[5] == 1)
		UpDown = false;

	glRotatef(Angle, 1, 0, 0);
	glRotatef(sin(Scene[4]) * 10, 0, 1, 0);
	Drawneck(); // 목함수 호출
	DrawHead(); // 머리 호출
	DrawBody(0, 0, 0, 0); // 몸통 함수 호출
	
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
	 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW);
	
	L_Arm_x = 0;           //왼팔은 80도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	R_Arm_x = -L_Arm_x;               //오른팔은 왼팔반대로 80도각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정.
	R_Arm_y = -50;  //우측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 
	L_Arm_y = -100; //좌측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 

	R_Leg_y = 30;  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y = 30;   //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x = 0;          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x = -R_Leg_x;

	glPushMatrix();

	glRotatef(180.0 - Scene[1], 0, 1, 0);
	glRotatef(30.0 - Scene[3], 1, 0, 0);
	glTranslatef(0.0, Scene[2], 0.2);//최초 로봇의 위치 
	glScalef(Scene[0], Scene[0], Scene[0]);
	DrawAndroid();
	glutSwapBuffers();
	glPopMatrix();
}

void Run() {
	sndPlaySound(TEXT("../JilPung.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity();//CTM 초기화
					 /*
					 기본적인 로봇의 움직임의 가속도는 sin() 함수를 통해 표현하였다
					 또한 관절의 제한범위를 생각하여 abs() 함수를 통해 관절의 움직임을 제한하였다.
			*/
	if (RunOrWalk)
	{
		if (Jump == 0)
		{
			L_Arm_x = sin(Scene[0]) * 80;           //왼팔은 80도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
			R_Arm_x = -L_Arm_x;               //오른팔은 왼팔반대로 80도각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정.
			R_Arm_y = -abs(sin(Scene[0]) * 60 + 50);  //우측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 
			L_Arm_y = -abs(-sin(Scene[0]) * 60 + 50); //좌측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 

			R_Leg_y = abs(-sin(Scene[0]) * 30 - 30);  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
			L_Leg_y = abs(sin(Scene[0]) * 30 - 30);   //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
			R_Leg_x = sin(Scene[0]) * 60;          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
			L_Leg_x = -R_Leg_x;              //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

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
		L_Arm_x = sin(Scene[0]) * 80 * Scene[6];           //왼팔은 80도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
		R_Arm_x = -L_Arm_x;               //오른팔은 왼팔반대로 80도각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정.
		R_Arm_y = -abs(sin(Scene[0]) * 60  + 50)* Scene[6];  //우측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 
		L_Arm_y = -abs(-sin(Scene[0]) * 60 + 50) * Scene[6]; //좌측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 

		R_Leg_y = abs(-sin(Scene[0]) * 30 - 30) * Scene[6];  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
		L_Leg_y = abs(sin(Scene[0]) * 30 - 30) * Scene[6];   //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
		R_Leg_x = sin(Scene[0]) * 60 * Scene[6];          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
		L_Leg_x = -R_Leg_x;              //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정

	DrawSun();

	glLoadIdentity();//CTM 초기화
	if(RunOrWalk)
		glRotatef(sin(Scene[0]) * 10, 0, 1, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정
	else if(!RunOrWalk)
		glRotatef(sin(Scene[0]) * 8, 0, 1, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

	glPushMatrix();
	glTranslatef(0, -0.9, 0.2);
	glRotatef((Scene[0] * 30), 1, 0, 1);
	glRotatef(135, 0, 1, 0);
	DrawEarth();
	glPopMatrix();

	glLoadIdentity();//CTM 초기화
	glTranslatef(0, 0, 0.7);
	DrawBackGround(Day[0], Day[1], Day[2], Day[3], Day[4], Day[5], 1); // 점심
	
					 /*
					 로봇이 달리면서 앞,뒤로 뒤뚱거리고 몸이 틀어지는 것을 표현
					 */
	glLoadIdentity();//CTM 초기화

	if (RunOrWalk)
	{
		glRotatef(abs(sin(Scene[0]) * 13), 1, 0, 0);//x축으로 16도 까지 각도틀어짐(abs절대값을 줌으로써 몸체가 뒤로 꺾이지 않는 한계점을 설정)
		glRotatef(sin(Scene[0]) * 15 + 135, 0, 1, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

		float i = 0;
		i = abs(sin(Scene[0])*0.05 + 0.04); //i변수값 설정
		glPushMatrix();// 처음 저장 좌표 다시 저장

		glTranslatef(0.0, i, 0); //변수 i만큼 로봇의 몸체가 Y축기준으로 움직임.
		glTranslatef(0.0, 0.3, 0.2);//최초 로봇의 위치 

		glScalef(0.8f, 0.8f, 0.8f);
		DrawAndroid();
		glPopMatrix();
	}
	
	else if(!RunOrWalk)
	{
		glRotatef(abs(sin(Scene[0]) * 13)* Scene[6], 1, 0, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

		glRotatef((sin(Scene[0]) * 15)+ 135 - Scene[9], 0, 1, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

		float i = 0;
		i = abs(sin(Scene[0])*0.05 + Scene[8]); //i변수값 설정
		glPushMatrix();// 처음 저장 좌표 다시 저장

		glTranslatef(0.0, i, 0); //변수 i만큼 로봇의 몸체가 Y축기준으로 움직임.
		glTranslatef(0.0 + Scene[7], 0.3, 0.2);//최초 로봇의 위치 

		glScalef(0.8f, 0.8f, 0.8f);
		DrawAndroid();
		glPopMatrix();
	}

	glutSwapBuffers();
	glPopMatrix();

	//여자친구와 싸웠다
	//질풍가도
	//태연 - 사랑해요
}

void Final()
{
	glLoadIdentity();

	L_Arm_x = -abs(sin(Scene[0]) * 60);           //왼팔은 80도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	R_Arm_x = L_Arm_x;               //오른팔은 왼팔반대로 80도각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정.
	R_Arm_y = -abs(sin(Scene[0]) * 30);  //우측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 
	L_Arm_y = -abs(sin(Scene[0]) * 30); //좌측팔뚝 각도조절(abs절대값을 줌으로써 팔뚝이 뒤로꺾이지 않는 한계점을 설정) 

	R_Leg_y = abs(-sin(Scene[0]) * 90);  //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y = abs(sin(Scene[0]) * 60 );   //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x = 0;          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x = -sin(Scene[0]) * 60;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정

	DrawSun();

	glLoadIdentity();//CTM 초기화
	glTranslatef(0, 0, 0.7);
	DrawBackGround(Day[0], Day[1], Day[2], Day[3], Day[4], Day[5], 1); // 점심


	glLoadIdentity();//CTM 초기화

	glPushMatrix();
	glTranslatef(0, -0.9, 0.2);
	glRotatef(135 + Scene[2], 0, 1, 0);
	DrawEarth();
	glPopMatrix();
	
	glLoadIdentity();//CTM 초기화
	
	glRotatef(135 + Scene[2], 0, 1, 0); //y축으로 16도 까지 각도틀어짐, sin()함수를 사용하여 주기적인 움직임 설정

	glRotatef(abs(sin(Scene[0]) * 20), 1, 0, 0);//x축으로 16도 까지 각도틀어짐(abs절대값을 줌으로써 몸체가 뒤로 꺾이지 않는 한계점을 설정)
	
	glPushMatrix();// 처음 저장 좌표 다시 저장

	glTranslatef(0.0, 0.4 - Scene[1], 0.2);//최초 로봇의 위치 

	glScalef(0.8f, 0.8f, 0.8f); 
	Drawneck(); // 목함수 호출
	DrawHead(); // 머리 호출
	DrawBody(0, 0, 0, 0); // 몸통 함수 호출
	DrawL_Legs(L_Leg_x, 1, 0, 0);  //좌측다리
	DrawL_foot(L_Leg_y, 1, 0, 0);  //좌측발		 
	DrawR_Legs(R_Leg_x, 1, 0, 0);  //우측다리
	DrawR_foot(R_Leg_y, 1, 0, 0);  //우측발
	DrawL_Arm(L_Arm_x, 1, 1, 0);   //좌측팔뚝
	DrawL_Hand(L_Arm_y, 1, 1, 0);//좌측손호출
	DrawR_Arm(R_Arm_x, 1, -1, 0);//우측팔뚝
	DrawR_Hand(R_Arm_y, 1, -1, 0);  //우측팔호출
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
	{							// 눈물 흐름, 고개
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

		if (Scene[2] < -0.063f)	// 눈물 처음 위치
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
	glutInit(&argc, argv);//초기화
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//디스플레이 모드 설정
	glutInitWindowSize(800, 800);//윈도우 크기 설정
	glutInitWindowPosition(0, 0);//윈도우 초기 위치 설정
	glutCreateWindow("프로젝트");//윈도우 생성
	glInit(); // 조명 초기화
	
	glutTimerFunc(50, MyTimer, 1); //타이머 함수
	glutDisplayFunc(MyDisplay); //디스플레이
	glutMainLoop();
	return 0;
}