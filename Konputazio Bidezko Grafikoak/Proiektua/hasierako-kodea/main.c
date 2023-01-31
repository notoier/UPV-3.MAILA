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
object3d * _selected_object = 0;  

camera * _first_camera;
camera * _selected_camera;          /*Object currently selected*/

char _change_type = 't';
char _change_scope = 'l';
char _change_mode = 'o';
char _camera_mode = 'a';

int flat_smooth = 0;

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


    //Camera init
    camera *aux_cam=0;
    aux_cam = (camera *) malloc(sizeof (camera));
    aux_cam->MZptr=(MZ*) malloc(sizeof(MZ));
    aux_cam->MZptr -> hptr = 0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetDoublev(GL_MODELVIEW_MATRIX, aux_cam->MZptr->M);
    _selected_camera = aux_cam;

    /*Definition of the method to draw the objects*/
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable ( GL_DEPTH_TEST );

    if (flat_smooth)
        glShadeModel(GL_SMOOTH);
    else
        glShadeModel(GL_FLAT);

    lighting_init();
    material_init();
    camera_focus_init();
}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {

    /*First of all, print the help information*/
    print_help();

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    glEnable ( GL_DEPTH_TEST );

    /** Change the window ratio by applying two integers before each window constant
      * @param int * KG_WINDOW_WIDTH and @param int * KG_WINDOW_HEIGHT
      * It can also be directly changed in definitions.h
     **/
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT); //Set window's size
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y); //Set where the window will appear
    glutCreateWindow(KG_WINDOW_TITLE); //Create window

    glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL); //Fill object's polygons
    glEnable(GL_DEPTH_TEST); //Enable depth
    glEnable (GL_LIGHTING );
    glShadeModel(GL_SMOOTH);
    
    /* set the callback functions */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutSpecialFunc(keyboard_func); //Set keyboard_func() as special function
    /* this initialization has to be AFTER the creation of the window */
    initialization();

    /* start the main loop */
    glutMainLoop();
    return 0;
}
