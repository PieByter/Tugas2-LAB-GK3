#include <glut.h>
#include <iostream>
using namespace std;

bool gameStarted = false; // Menunjukkan apakah permainan sudah dimulai

// Posisi awal objek 1 (atas kiri)
float object1X = -0.85f;
float object1Y = 0.85f;

// Posisi awal objek 2 (bawah kanan)
float object2X = 0.85f;
float object2Y = -0.85f;

// Posisi kotak 1 & 2
float box1X = -0.2f;
float box1Y = 0.0f;
float box2X = 0.2f;
float box2Y = 0.0f;

// Status objek 1 dan objek 2 sudah masuk kotak atau belum
bool obj1InBox = false;
bool obj2InBox = false;

//Menampilkan pesan sekali pada terminal
bool messageDisplayed = false;

// Fungsi untuk mengatur tulisan
void write(float x, float y, float z, void* font, const char* string) {
    const char* c;
    glColor3f(1, 1, 1);
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Fungsi untuk menggambar objek
void drawObjects() {
    if (!gameStarted) {
        write(-0.75f, 0.2f, 0, GLUT_BITMAP_HELVETICA_18, "Press 'SPACE' to Start the Game");
        // Kotak 1 (Merah)
        glLoadIdentity();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(box1X, box1Y, 0.0f);
        glutWireCube(0.3f);
        glEnd();

        // Kotak 2 (Hijau)
        glLoadIdentity();
        glColor3f(0.0f, 1.0f, 0.0f);
        glTranslatef(box2X, box2Y, 0.0f);
        glutWireCube(0.3f);
        glEnd();
        glFlush();
    }
    else {
        // Objek 1 (Merah)
        glLoadIdentity();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(object1X, object1Y, 0.0f);
        glutSolidCube(0.2f);
        glEnd();

        // Objek 2 (Hijau)
        glLoadIdentity();
        glColor3f(0.0f, 1.0f, 0.0f);
        glTranslatef(object2X, object2Y, 0.0f);
        glutSolidCube(0.2f);
        glEnd();

        // Kotak 1 (Merah)
        glLoadIdentity();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(box1X, box1Y, 0.0f);
        glutWireCube(0.3f);
        glEnd();

        // Kotak 2 (Hijau)
        glLoadIdentity();
        glColor3f(0.0f, 1.0f, 0.0f);
        glTranslatef(box2X, box2Y, 0.0f);
        glutWireCube(0.3f);
        glEnd();
        glFlush();
    }

    
}

// Fungsi untuk mengecek objek sudah atau belum memasuki kotak
bool IsInsideBox(float objX, float objY, float boxX, float boxY, float boxSize) {
    float leftX = boxX - boxSize;
    float rightX = boxX + boxSize;
    float topY = boxY + boxSize;
    float bottomY = boxY - boxSize;

    return (objX >= leftX && objX <= rightX && objY >= bottomY && objY <= topY);
}

// Fungsi untuk mereset semua variabel ke kondisi awal
void resetGame() {
    object1X = -0.85f;
    object1Y = 0.85f;
    object2X = 0.85f;
    object2Y = -0.85f;
    box1X = -0.2f;
    box1Y = 0.0f;
    box2X = 0.2f;
    box2Y = 0.0f;
    obj1InBox = false;
    obj2InBox = false;
    gameStarted = false;
}

// Fungsi logika permainan
static void update() {
    if (gameStarted) {
        // Periksa apakah objek A berada dalam kotak 1
        bool obj1InBox1 = IsInsideBox(object1X, object1Y, box1X, box1Y, 0.07f);

        // Periksa apakah objek B berada dalam kotak 2
        bool obj2InBox2 = IsInsideBox(object2X, object2Y, box2X, box2Y, 0.07f);
        
        // Jika keduanya berada dalam kotak, permainan selesai
        if (obj1InBox1 && obj2InBox2) {
            if (!messageDisplayed) { // Cek apakah pesan sudah ditampilkan
                cout << "The 2 Object is inside the Square!" << endl;
                messageDisplayed = true; // Setel variabel ke true agar pesan tidak ditampilkan lagi
            }
            
            write(-0.8f, -0.3f, 0, GLUT_BITMAP_HELVETICA_18, "The 2 Object is inside the Square!");
            write(-0.68f, -0.4f, 0, GLUT_BITMAP_HELVETICA_18, "Press 'ENTER' to replay...");
            write(-0.73f, -0.5f, 0, GLUT_BITMAP_HELVETICA_18, "Press 'ESC' to exit the game...");
        }
        else if (obj1InBox1 == false || obj2InBox2 == false) {
            messageDisplayed = false;
        }
    }
}


// Fungsi tampilan
static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawObjects();
    update();
    glutPostRedisplay();
    glutSwapBuffers();
}

// Fungsi keyboard khusus untuk objek 2
void specialKeyboard(int key, int x, int y) {
    if (gameStarted) {
        switch (key) {
        case GLUT_KEY_UP:
            object2Y += 0.05;
            cout << "(" << object2X << ", " << object2Y << ")" << endl;
            break;
        case GLUT_KEY_DOWN:
            object2Y -= 0.05;
            cout << "(" << object2X << ", " << object2Y << ")" << endl;
            break;
        case GLUT_KEY_RIGHT:
            object2X += 0.05;
            cout << "(" << object2X << ", " << object2Y << ")" << endl;
            break;
        case GLUT_KEY_LEFT:
            object2X -= 0.05;
            cout << "(" << object2X << ", " << object2Y << ")" << endl;
            break;
        }
        // Periksa batas untuk mencegah objek 2 keluar dari layar
        if (object2X < -0.9f) {
            object2X = -0.9f;
        }
        if (object2X > 0.9f) {
            object2X = 0.9f;
        }
        if (object2Y < -0.9f) {
            object2Y = -0.9f;
        }
        if (object2Y > 0.9f) {
            object2Y = 0.9f;
        }
    }
    else if (key == ' ') {
        gameStarted = true;
    }
}

// Fungsi keyboard umum untuk objek 1
void keyboard(unsigned char key, int x, int y) {
    if (gameStarted) {
        switch (key) {
        case 'w':
        case 'W':
            object1Y += 0.05;
            cout << "(" << object1X << ", " << object1Y << ")" << endl;
            break;
        case 's':
        case 'S':
            object1Y -= 0.05;
            cout << "(" << object1X << ", " << object1Y << ")" << endl;
            break;
        case 'a':
        case 'A':
            object1X -= 0.05;
            cout << "(" << object1X << ", " << object1Y << ")" << endl;
            break;
        case 'd':
        case 'D':
            object1X += 0.05;
            cout << "(" << object1X << ", " << object1Y << ")" << endl;
            break;
        case 27:
            cout << "Exit Game" << endl;
            exit(0);
            break;
        case 13:
            resetGame();
            cout << "Game Reset" << endl;
            break;
        }

        // Periksa batas untuk mencegah objek 1 keluar dari layar
        if (object1X < -0.9f) {
            object1X = -0.9f;
        }
        if (object1X > 0.9f) {
            object1X = 0.9f;
        }
        if (object1Y < -0.9f) {
            object1Y = -0.9f;
        }
        if (object1Y > 0.9f) {
            object1Y = 0.9f;
        }
        
    }
    else if (key == ' ') {
        cout << "Game Start" << endl;
        gameStarted = true;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("2D Graphics Simple Game");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 480, 0, 480);

    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutSpecialFunc(specialKeyboard);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
