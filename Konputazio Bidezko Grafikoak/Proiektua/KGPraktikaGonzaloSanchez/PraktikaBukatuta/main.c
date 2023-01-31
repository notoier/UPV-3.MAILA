#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "display.h"
#include "io.h"
#include "definitions.h"

extern void tekla_berezien_arretarako_funtzioa(int key, int x, int y);
extern void argiak_hasieratu();
extern void materialak_hasieratu();

/** GLOBAL VARIABLES **/

GLdouble _window_ratio;                     /*Control of window's proportions */
GLdouble _ortho_x_min,_ortho_x_max;         /*Variables for the control of the orthographic projection*/
GLdouble _ortho_y_min ,_ortho_y_max;        /*Variables for the control of the orthographic projection*/
GLdouble _ortho_z_min,_ortho_z_max;         /*Variables for the control of the orthographic projection*/

object3d * _first_object= 0;                /*List of objects*/
object3d * _selected_object = 0;            /*Object currently selected*/
kamera * _first_kamera;                /*List of objects*/
kamera * _selected_kamera; 
char aldaketa_mota = 't';                         /*t = translation, r=rotation, e=escale*/
double biraketa_angelua;
double lekuzaldaketa;
double eskalaketa;
int LG;
int flat_smooth=0;

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

    /*Definition of the background color*/
    glClearColor(KG_COL_BACK_R, KG_COL_BACK_G, KG_COL_BACK_B, KG_COL_BACK_A);

    /*Definition of the method to draw the objects*/
    glPolygonMode ( GL_FRONT_AND_BACK , GL_FILL );
    glEnable(GL_DEPTH_TEST);

    if (flat_smooth) glShadeModel(GL_SMOOTH);
    else glShadeModel(GL_FLAT);

    biraketa_angelua = 0.5;
    lekuzaldaketa = 1;
    eskalaketa = 0.5;

    LG = 1;


}

void initialize_kamera(){
    kamera *kam_aux=0;
    kam_aux = (kamera *) malloc(sizeof (kamera));
    kam_aux->MZptr=(MZ*) malloc(sizeof(MZ));
    kam_aux->MZptr -> hptr = 0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetDoublev(GL_MODELVIEW_MATRIX, kam_aux->MZptr->M);
    _selected_kamera=kam_aux;
}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {

    /*First of all, print the help information*/
    print_help();

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    glEnable ( GL_DEPTH_TEST );
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // poligonoak betetzea nahi dugu

    glEnable(GL_DEPTH_TEST); // Sakonera testa aktibatu (Z-buffer)

    glEnable ( GL_LIGHTING );

    glShadeModel ( GL_SMOOTH );


    /* set the callback functions */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(tekla_berezien_arretarako_funtzioa);

    /* this initialization has to be AFTER the creation of the window */
    initialization();
    initialize_kamera();
    argiak_hasieratu();
    materialak_hasieratu();
    kamera_fokoa_hasieratu();


    /* start the main loop */
    glutMainLoop();
    return 0;
}
