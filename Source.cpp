#include<iostream>
#include<glut.h>
#include<time.h>

using namespace std;
int score = 0;
static int window;
static int menu_id;
static int submenu_id;
static int value = 0;

void menu(int num) {
	if (num == 0) {
		glutDestroyWindow(window);
		exit(0);
	}
	else {
		value = num;
	}
	glutPostRedisplay();
}

void createMenu(void) {
	submenu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Sphere", 2);
	glutAddMenuEntry("Cone", 3);
	glutAddMenuEntry("Torus", 4);
	glutAddMenuEntry("Teapot", 5);

	menu_id = glutCreateMenu(menu);
	glutAddMenuEntry("Clear", 1);
	glutAddSubMenu("Draw", submenu_id);
	glutAddMenuEntry("Quit", 0);

	glutAttachMenu(GLUT_LEFT_BUTTON);
}

void menuDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	if (value == 1) {
		return;
	}
	else if (value == 2) {
		glPushMatrix();
		glColor3d(1.0, 0.0, 0.0);
		glutWireSphere(0.5, 50, 50);
		glPopMatrix();
	}
	else if (value == 3) {
		glPushMatrix();
		glColor3d(0.0, 1.0, 0.0);
		glRotated(65, -1.0, 0.0, 0.0);
		glutWireCone(0.5, 1.0, 50, 50);
		glPopMatrix();
	}
	else if (value == 4) {
		glPushMatrix();
		glColor3d(0.0, 0.0, 1.0);
		glutWireTorus(0.3, 0.6, 100, 100);
		glPopMatrix();
	}
	else if (value == 5) {
		glPushMatrix();
		glColor3d(1.0, 0.0, 1.0);
		glutSolidTeapot(0.5);
		glPopMatrix();
	}
	glFlush();
}

void one_quadrant_init() {
	glClearColor(0, 0, 0, 1);
	gluOrtho2D(0, 500, 0, 500);
}

void loading() {
	glClear(GL_COLOR_BUFFER_BIT);

	char text[30] = "Loading...";
	glColor3f(1, 1, 1);
	glRasterPos2f(200, 50);

	for (unsigned int j = 0; j < strlen(text); j++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[j]);
	}

	for (float i = 1; i <= 500; i += 50) {
		glBegin(GL_POLYGON);
		glColor3f(0, 0, 1);
		glVertex2f(0 + i, 0);
		glVertex2f(50 + i, 0);
		glVertex2f(50 + i, 500);
		glVertex2f(0 + i, 500);
		glEnd();
		Sleep(300);
		glFlush();
	}
	exit(0);
}

char ch = 's', temp;
void game(unsigned char key) {
	char intro[] = "Welcome to the blind game! Type the new letter which POPS ;)", gameover[] = "OOPS Wrong Key :(";
	char subintro[] = "If you don't see anything popped, you can press previous popped key to proceed!";
	unsigned char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	time_t t;
	srand((unsigned)time(&t));
	temp = ch;
	int r = rand() % 26 + 1, xrand = rand() % 300 + 100, yrand = rand() % 300 + 100;
	ch = alphabets[r];

	glColor3f(1, 1, 1);
	glRasterPos2f(10, 450);
	for (unsigned int i = 0; i < strlen(intro); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, intro[i]);
	}
	glColor3f(0, 1, 0);
	glRasterPos2f(10, 420);
	for (unsigned int i = 0; i < strlen(subintro); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, subintro[i]);
	}

	glColor3f(1, 1, 1);
	glRasterPos2f((float)xrand, (float)yrand);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, alphabets[r]);

	glColor3f(1, 0, 0);
	glRasterPos2f(300, 300);
	if (score > 2 && tolower(key) != tolower(temp)) {
		for (unsigned int i = 0; i < strlen(gameover); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameover[i]);
		}
	}

	score += 1;
	glEnd();
	glFlush();
}

void clearColorBuffer() {
	glClear(GL_COLOR_BUFFER_BIT);
	char intro[] = "Maximize the Window and Press any key to start :)";
	glColor3f(1.0f, 0.5f, 0.1f);
	glRasterPos2f(10, 480);
	for (unsigned int i = 0; i < strlen(intro); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, intro[i]);
	}
	glFlush();
}

void keyPressed(unsigned char pressedKey, int x, int y) {
	//glutPostRedisplay();
	game(pressedKey);
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	int choice;
	cout << "\n\n\t\t\t\t\tWelcome to <GraphicsLibrary.h>\n\n";
	cout << "\t\t\t\t\t\t1. Loading Window Demo\n\t\t\t\t\t\t2. Blind Challenger\n\t\t\t\t\t\t3. Menu Demo\n\t\t\t\t\t\t4. Exit\n\n";
	cout << "\t\t\t\t\t\tEnter Choice: ";
	cin >> choice;

	switch (choice) {
	case 1: //Loading Window Demo
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(500, 50);
		glutInitWindowPosition(50, 50);
		glutCreateWindow("Boot Manager");
		one_quadrant_init();
		glutDisplayFunc(loading);
		break;

	case 2: //Blind Game		
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(1920, 1080);
		glutCreateWindow("Focus needed, both in life and in this game :D");
		glutKeyboardFunc(keyPressed);
		one_quadrant_init();
		glutDisplayFunc(clearColorBuffer);
		break;

	case 3: //Menu
		glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(100, 100);
		window = glutCreateWindow("Menu Demo");
		createMenu();
		glClearColor(0, 0, 0, 0);
		glutDisplayFunc(menuDisplay);
		glutMainLoop();
		break;

	default:
		exit(0);
	}

	glutMainLoop();
	return 0;
}
