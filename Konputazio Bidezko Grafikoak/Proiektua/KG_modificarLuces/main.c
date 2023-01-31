#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "display.h"
#include "io.h"
#include "definitions.h"

/** GLOBAL VARIABLES **/

GLdouble _window_ratio;                     /*Control of window's proportions */
GLdouble _ortho_x_min,_ortho_x_max;         /*Variables for the control of the orthographic projection*/
GLdouble _ortho_y_min ,_ortho_y_max;        /*Variables for the control of the orthographic projection*/
GLdouble _ortho_z_min,_ortho_z_max;         /*Variables for the control of the orthographic projection*/

object3d * _first_object= 0;                /*List of objects*/
object3d * _selected_object = 0;            /*Object currently selected*/
char aldaketa_mota;                         /*Aldaketa mota (traslazioa,biraketa,eskalaketa) adierazten digu*/
int LG;                                     /*Egoera aldagaia lokala (0) edo globala (1) den adierazten du*/
double biraketa_angelua;                    /*Biraketan mugituko den angelua*/
//double traslazioa;                        /*Lekuz aldaketa*/ //AZKENEAN EZ DUT ERABILI
double eskalaketa;                          /*Eskalaketa aldaketa*/
object3d * _first_kamera;                    /*Kamera zerrenda*/
object3d * _selected_kamera=0;               /*Aukeratutako kamera eta bere hasieraketa*/
int obj_mota;                               /*Aldaketa mota kameraren (1), objektuaren (0) edo argiaren (2) gainean egin nahi dugun adierazten du.*/
/*Azkenean ez dut erabiliko,
LG aldagaiaren baliokidea baita.*/
//int kamera_mota = 0;                      /*kamerak hegaldi moduan (0), kamerak analisi modua(1)*/
int nondik_ikusi;                           /*kameraren iksupuntua kanpotik egiten bada (0) edo objektutik egiten bada (1)*/

int fs;                                     /*flat (FLAT edo 0) edo smooth (SMOOTH edo 1) aukeratzeko*/

/*KAMERAREN HASIERAKETA*/
void kamera_hasieratu() {
    object3d * kamera_aux = 0;
    kamera_aux = (object3d *) malloc(sizeof(object3d));
    kamera_aux -> mzptr = (mz*) malloc(sizeof(mz));
    kamera_aux -> mzptr -> hptr = 0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetDoublev(GL_MODELVIEW_MATRIX, kamera_aux->mzptr->M);
    _selected_kamera=kamera_aux;
}

/** GENERAL INITIALIZATION **/
void initialization (){

    /*Initialization of all the variables with the default values*/
    _ortho_x_min = KG_ORTHO_X_MIN_INIT;
    _ortho_x_max = KG_ORTHO_X_MAX_INIT;
    _ortho_y_min = KG_ORTHO_Y_MIN_INIT;
    _ortho_y_max = KG_ORTHO_Y_MAX_INIT;
    _ortho_z_min = KG_ORTHO_Z_MIN_INIT;
    _ortho_z_max = KG_ORTHO_Z_MAX_INIT;

    _window_ratio = (GLdouble) KG_WINDOW_WIDTH / (GLdouble) KG_WINDOW_HEIGHT;
    /*Aldaketa motaren hasieraketa traslazioa da*/
    aldaketa_mota='t';
    /*LG-ren hasieraketa 1 (globala) da*/
    LG=1;
    /*Ojbektu motaren hasieraketa 0 (objektua) da*/
    obj_mota=0;
    /*eskalaketa faktorea 1.2*/
    eskalaketa=1.2;
    /*Biraketa angelua hasieratu*/
    biraketa_angelua=0.0872665;
    /*kameraren ikuspuntua objektutik hasi*/
    nondik_ikusi=0;
    /*Definition of the background color*/
    glClearColor(KG_COL_BACK_R, KG_COL_BACK_G, KG_COL_BACK_B, KG_COL_BACK_A);

    /*Definition of the method to draw the objects*/
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    /*kameraren hasieraketa*/
    kamera_hasieratu();

    /*fs FLAT bezala hasieratu eta hasieratuta badago, balorea aldatu.*/
    if (fs==FLAT){
        glShadeModel(GL_SMOOTH);
     } 
    else{
        glShadeModel(GL_FLAT);
    } 

    argia_hasieratu();
    materiala_hasieratu();
    foku_kam_matrizea();
}



/** MAIN FUNCTION **/
int main(int argc, char** argv) {

    /*First of all, print the help information*/
    print_help();

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);

    /* set the callback functions */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(tekla_berezien_arretarako_funtzioa);

    /* this initialization has to be AFTER the creation of the window */
    initialization();

    /* start the main loop */
    glutMainLoop();
    return 0;
}
