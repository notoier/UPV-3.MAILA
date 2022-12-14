#include "definitions.h"
#include "load_obj.h"
#include "display.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

extern object3d * _first_object;
extern object3d * _selected_object;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern char _change_type; /*Variable used to define the type of change to be done to a selected object*/
extern char _change_scope; /*Defines the types of changes (global or local)*/
extern char _change_mode; /*Variable used to define the thing to change (camera, object...)*/
extern char _camera_mode;
/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){
    printf("KbG Irakasgaiaren Praktika. Programa honek 3D objektuak \n");
    printf("aldatzen eta bistaratzen ditu.  \n\n");
    printf("\n\n");
    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t Programatik irten \n");
    printf("<F>\t\t Objektua bat kargatu\n");
    printf("<I>\t\t Objektuari dagokion informazioa pantailaratu\n");
    printf("<Z,z>\t\t Objektuari egindako aldaketa desegin\n");
    printf("<T,t>\t\t Translazioa aktibatu\n");
    printf("<R,r>\t\t Rotazioak aktibatu\n");
    printf("<S,s>\t\t Escalak aktibatu\n");

    printf("<G,g>\t\t Aldaketa global aktibatu\n");
    printf("<L,l>\t\t Aldaketa lokalak aktibatu\n");

    printf("<GEZIAK / AVPAG / REPAG>\t\t Aldaketak egin\n");

    printf("<O,o>\t\t Aldaketak objektuei egin\n");
    printf("<C,c>\t\t Aldaketak camerari egin\n");   
    printf("<A,a>\t\t Aldaketak argiari egin\n");
    
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n");
    printf("\n\n");
}
/**
 * @brief Free all memory allocated to an object 
 * @param object Object to free
 */
void freeall(object3d *object){
    GLint i;
    for (i = 0; i < object->num_faces; ++i){
        free(object->face_table[i].vertex_table);
    }
    free(object->vertex_table);
    free(object->face_table);
}


/**
  * @brief Get the translation matrix object
  * 
  * @param mptr Object's translation matrix
  * @param x X coordinate
  * @param y Y coordinate
  * @param z Z coordinate
  */
void translation_matrix(double x, double y, double z){
    double mptr[16];
    MZ* mlagptr;
    // AZ* alagptr;

    mptr[0] = 1.0; mptr[4] = 0.0; mptr[8]  = 0.0; mptr[12] = x*KG_TRAN_STEP;
    mptr[1] = 0.0; mptr[5] = 1.0; mptr[9]  = 0.0; mptr[13] = y*KG_TRAN_STEP;
    mptr[2] = 0.0; mptr[6] = 0.0; mptr[10] = 1.0; mptr[14] = z*KG_TRAN_STEP;
    mptr[3] = 0.0; mptr[7] = 0.0; mptr[11] = 0.0; mptr[15] = 1.0;

    glMatrixMode(GL_MODELVIEW);
    switch(_change_scope){
        case 'l':
            glLoadMatrixd(_selected_object->MZptr->M);
            glMultMatrixd(&(mptr[0]));
            break;

        case 'g':
            glLoadIdentity();
            glMultMatrixd(&(mptr[0]));
            glMultMatrixd(_selected_object->MZptr->M);
            break;
    }

    mlagptr = (MZ*)(malloc(sizeof(MZ)));
    glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr -> M);
    mlagptr->hptr = _selected_object->MZptr;
    _selected_object->MZptr = mlagptr;

  /*   alagptr = (AZ*)malloc(sizeof(AZ));
    alagptr->c =_change_scope;
    alagptr->hptr = _selected_object->AZptr;
    _selected_object->AZptr = alagptr; */

    printf("Object moved in:  X: %f, Y: %f, Z: %f. \n", x,y,z );
}

/**
  * @brief Get the rotation matrix object
  * 
  * @param mptr Object's rotation matrix (Rodriges' formula)
  * @param x X coordinate
  * @param y Y coordinate
  * @param z Z coordinate
  */
void rotation_matrix(double x, double y, double z){

    double mptr[16];
    MZ* mlagptr;
    // AZ* alagptr;
/* 
    mptr[0] = cos(KG_ROT_ANGLE) + pow(x, 2)*(1-cos(KG_ROT_ANGLE));   mptr[4] = x*y*(1-cos(KG_ROT_ANGLE)) - z*sin(KG_ROT_ANGLE);       mptr[8]  = x*z*(1-cos(KG_ROT_ANGLE)) + y*sin(KG_ROT_ANGLE);       mptr[12] = 0.0;
    mptr[1] = y*x*(1-cos(KG_ROT_ANGLE)) + z*sin(KG_ROT_ANGLE);       mptr[5] = cos(KG_ROT_ANGLE) + pow(y, 2)*(1-cos(KG_ROT_ANGLE));   mptr[9]  = y*z*(1-cos(KG_ROT_ANGLE)) - x*sin(KG_ROT_ANGLE);       mptr[13] = 0.0;
    mptr[2] = z*x*(1-cos(KG_ROT_ANGLE) - y*sin(KG_ROT_ANGLE));       mptr[6] = z*y*(1-cos(KG_ROT_ANGLE) + x*sin(KG_ROT_ANGLE));       mptr[10] = cos(KG_ROT_ANGLE) + pow(z, 2)*(1-cos(KG_ROT_ANGLE));   mptr[14] = 0.0;
    mptr[3] = 0.0;                                                   mptr[7] = 0.0;                                                   mptr[11] = 0.0;                                                   mptr[15] = 1.0;
*/
    double alpha = x * KG_ROT_ANGLE;
    double beta = y * KG_ROT_ANGLE;
    double gamma = z * KG_ROT_ANGLE;

    mptr[0] = cos(beta) * cos(gamma); mptr[4] = sin(alpha) * sin(beta) * cos (gamma) - cos(alpha) * sin(gamma); mptr[8] = cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma); mptr[12] = 0.0;
    mptr[1] = cos(beta) * sin(gamma); mptr[5] = sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma);  mptr[9] = cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma); mptr[13] = 0.0;
    mptr[2] = -sin(beta);             mptr[6] = sin(alpha) * cos(beta);                                         mptr[10] = cos(alpha) * cos(beta);                                       mptr[14] = 0.0;
    mptr[3] = 0.0;                    mptr[7] = 0.0;                                                            mptr[11] = 0.0;                                                          mptr[15] = 1.0;

    glMatrixMode(GL_MODELVIEW);
    switch(_change_scope){
        case 'l':
            glLoadMatrixd(_selected_object->MZptr->M);
            glMultMatrixd(&(mptr[0]));
            break;

        case 'g':
            glLoadIdentity();
            glMultMatrixd(&(mptr[0]));
            glMultMatrixd(_selected_object->MZptr->M);
            break;
    }

    mlagptr = (MZ*)malloc(sizeof(MZ));
    glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr -> M);
    mlagptr->hptr = _selected_object->MZptr;
    _selected_object->MZptr = mlagptr;

/*     alagptr = (AZ*)malloc(sizeof(AZ));
    alagptr->c =_change_scope;
    alagptr->hptr = _selected_object->AZptr;
    _selected_object->AZptr = alagptr; */

    printf("Object rotated %f?? in:  X: %f, Y: %f, Z: %f. \n", KG_ROT_ANGLE*180/M_PI, x*KG_ROT_ANGLE*180/M_PI, y*KG_ROT_ANGLE*180/M_PI, z*KG_ROT_ANGLE*180/M_PI);
}
/**
  * @brief Get scale matrix object
  * 
  * @param mptr Object's scale matrix
  * @param x X coordinate
  * @param y Y coordinate
  * @param z Z coordinate
  */
void scaling_matrix(double x, double y, double z){

    double mptr[16];
    MZ* mlagptr;
    // AZ* alagptr;

    mptr[0] = x;                mptr[4] = 0.0;              mptr[8]  = 0.0;             mptr[12] = 0.0;
    mptr[1] = 0.0;              mptr[5] = y;                mptr[9]  = 0.0;             mptr[13] = 0.0;
    mptr[2] = 0.0;              mptr[6] = 0.0;              mptr[10] = z;               mptr[14] = 0.0;
    mptr[3] = 0.0;              mptr[7] = 0.0;              mptr[11] = 0.0;             mptr[15] = 1.0;

    glMatrixMode(GL_MODELVIEW);
    switch(_change_scope){
        case 'l':
            glLoadMatrixd(_selected_object->MZptr->M);
            glMultMatrixd(&(mptr[0]));
            break;

        case 'g':
            glLoadIdentity();
            glMultMatrixd(&(mptr[0]));
            glMultMatrixd(_selected_object->MZptr->M);
            break;
    }

    mlagptr = (MZ*)malloc(sizeof(MZ));
    glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr -> M);
    mlagptr->hptr = _selected_object->MZptr;
    _selected_object->MZptr = mlagptr;

    printf("Object's size changed in:  X: %f, Y: %f, Z: %f. \n", x,y,z);

/*     alagptr = (AZ*)malloc(sizeof(AZ));
    alagptr->c =_change_scope;
    alagptr->hptr = _selected_object->AZptr;
    _selected_object->AZptr = alagptr; */
}
/**
 * @brief Undo the last change done to an object
 * 
 */
void undo(){
    if (_selected_object != 0){
        if (_selected_object->MZptr != 0){
            if(_selected_object->MZptr->hptr != 0){        
                MZ *auxptr;
                auxptr = _selected_object->MZptr;
                _selected_object->MZptr =_selected_object->MZptr->hptr;

                free(auxptr);
            }
        }
    }  
}

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboard(unsigned char key, int x, int y) {

    char fname[128]; /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd,he,midx,midy;

    switch (key) {
        // Load an object
        case 'f':
        case 'F':
            /*Ask for file*/
            printf("%s", KG_MSSG_SELECT_FILE);
            scanf("%s", &(fname[0]));
            /*Allocate memory for the structure and read the file*/
            auxiliar_object = (object3d *) malloc(sizeof (object3d));
            read = read_wavefront(fname, auxiliar_object);
            switch (read) {
            /*Errors in the reading*/
            case 1:
                printf("%s: %s\n", fname, KG_MSSG_FILENOTFOUND);
                break;
            case 2:
                printf("%s: %s\n", fname, KG_MSSG_INVALIDFILE);
                break;
            case 3:
                printf("%s: %s\n", fname, KG_MSSG_EMPTYFILE);
                break;
            /*Read OK*/
            case 0:
                int i;
                auxiliar_object->MZptr = (MZ*)malloc(sizeof(MZ));
                for (i = 0; i < 16; i++){
                    if (i % 5 == 0){
                        auxiliar_object->MZptr->M[i] = 1.0;
                    } else {
                        auxiliar_object->MZptr->M[i] = 0.0;
                    }
                }
                
                //Insert the new object in the list
            
                auxiliar_object->next = _first_object;
                _first_object = auxiliar_object;
                _selected_object = _first_object;
                printf("%s\n",KG_MSSG_FILEREAD);
                break;
            }
            break;
        
        //Print object's information (TO BE FIXED)
  /*    case 'i':
        case 'I': //Print object's information on window
            //Check if there's an object selected
            if(_selected_object == 0){
                break;
            } 
            GLchar n_faces = _selected_object->num_faces;
            GLchar n_vertices = _selected_object->num_vertices;
            char* string1 = ("Faces: " + n_faces);
            char* string2 = "Vertices: " + n_vertices;
            output(2, 3, 0.2, 0.89, 0.89, GLUT_BITMAP_HELVETICA_10, "OBJECT INFORMATION");
            output(1, 2, 0.2, 0.89, 0.89, GLUT_BITMAP_HELVETICA_10, string1);
            output(2, 2.5, 0.2, 0.89, 0.89, GLUT_BITMAP_HELVETICA_10, string2);
            return;
  */
        //Enable translation mode
        case 't':
        case 'T':
            _change_type = 't'; //Translate
            printf("Translation mode enabled\n");
            break;
        
        //Enable rotation mode
        case 'r':
        case 'R':
            _change_type = 'r'; //Rotate
            printf("Rotation mode enabled\n");
            break;

        //Enable scaling mode
        case 'e':
        case 'E':
            _change_type = 'e'; //Scale 
            printf("Scaling mode enabled\n");
            break;

        //Set changes to affect locally
        case 'l':
        case 'L':
            if (_change_mode != 'c'){
                _change_scope = 'l'; //Local change
                printf("Changes set to: Local\n");
                break;
            }else{
                //CAMARA ALDAKETAK
                _camera_mode = 'f';
                printf("Flying camera is active");
            }
        //Set changes to affect globaly
        case 'g':
        case 'G':
            if (_change_mode != 'c'){
                _change_scope = 'g'; //Global change
                printf("Changes set to: Global\n");
                break;
            }else{
                //CAMARA ALDAKETAK
                _camera_mode = 'a';
                printf("Camera set in analisis mode");
            }
        //Set changes to affect only to objects
        case 'o':
        case 'O':
            _change_mode = 'o'; //Sets changes to affect the objects
            printf("Changes now affect only to: Objects\n");
            break;
        
        //Set changes to affect only to the camera
        case 'c':
        case 'C':
            _change_mode = 'c'; //Sets changes to affect the camera
            printf("Changes now affect only to: Camera\n");
            break;

        //Set changes to affect only to lights    
        case 'a':
        case 'A':
            _change_mode = 'a'; //Sets changes to affect the light
            printf("Changes now affect only to: Light\n");
            break;

        //Undo the last change done to an object
        case 'z':
        case 'Z':
            undo();
            break;

        //Change between loaded objects
        case 9: /* <TAB> */
            //Check if there's any object selected
            if (_selected_object == 0){
                _selected_object = _first_object;
            } else {
                //If there is, pass to the next object
                _selected_object = _selected_object->next;
            }
            break;

        //Delete the current selected object
        case 127: /* <SUPR> */
            //No memory will be freed if there's no object loaded
            if (_selected_object != 0){
                /*Erasing an object depends on whether it is the first one or not*/
                if (_selected_object == _first_object)
                {
                    /*To remove the first object we just set the first as the current's next*/
                    _first_object = _first_object->next;
                    /*Once updated the pointer to the first object it is save to free the memory*/
                    freeall(_selected_object);
                    free(_selected_object);
                    /*Finally, set the selected to the new first one*/
                    _selected_object = _first_object;

                } else {
                    /*In this case we need to get the previous element to the one we want to erase*/
                    auxiliar_object = _first_object;
                    while (auxiliar_object->next != _selected_object)
                        auxiliar_object = auxiliar_object->next;
                    /*Now we bypass the element to erase*/
                    auxiliar_object->next = _selected_object->next;
                    /*free the memory*/
                    freeall(_selected_object);
                    free(_selected_object);
                    /*and update the selection. It is the previous to the deleted one. */
                    _selected_object = auxiliar_object;
                }
            }
            break;
        
        //ZOOM IN
        case '-': //ZOOM   
            /* Decrease the projection plane; compute the new dimensions*/
            switch (_change_mode)
            {
            case 'c':
                if (glutGetModifiers() == GLUT_ACTIVE_CTRL){ 
                    // with or without pressing CTRL key 
                    }
                    
                    wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
                    he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
                    /*In order to avoid moving the center of the plane, we get its coordinates*/
                    midx = (_ortho_x_max+_ortho_x_min)/2;
                    midy = (_ortho_y_max+_ortho_y_min)/2;
                    /*The new limits are set, keeping the center of the plane*/
                    _ortho_x_max = midx + wd/2;
                    _ortho_x_min = midx - wd/2;
                    _ortho_y_max = midy + he/2;
                    _ortho_y_min = midy - he/2;
                
                break;
            
            case 'o':
                if (_selected_object!=0)
                    scaling_matrix(1.0/KG_SCALE_NUM, 1.0/KG_SCALE_NUM, 1.0/KG_SCALE_NUM);
                break;
            }

            break;
        //ZOOM_OUT
        case '+':
            switch (_change_mode)
            {
            case 'c':
                if (glutGetModifiers() == GLUT_ACTIVE_CTRL){ 
                // with or without pressing CTRL key 
                }
                
                wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
                he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                //The new limits are set, keeping the center of the plane//
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;            
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;

                break;

            case 'o':
                if (_selected_object!=0)
                    scaling_matrix(1.0*KG_SCALE_NUM, 1.0*KG_SCALE_NUM, 1.0*KG_SCALE_NUM);
                break;
            }
            break;

        //Prints the program functionalities
        case '?':
            print_help();
            break;

        //Close the program
        case 27: /* <ESC> */
            exit(0);
            break;

        //Prints the pressed key if it has no functionality
        default:
            printf("Default");
            /*In the default case we just print the code of the key. This is usefull to define new cases*/
            printf("%d %c\n", key, key);
        }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}

/**
 * @brief Callback function to control de special keyboard keys
 * 
 * @param key key that has been pressed 
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y y coordinate of the mouse pointer when key was pressed
 */
void keyboard_func(int key, int x, int y){
    if (_selected_object != 0) //We'll make changes only if there's an object selected
    {
        switch(key){

            //UP ARROW
            case GLUT_KEY_UP:
                switch(_change_type){
                    case 't':
                        translation_matrix(0.0, 1.0, 0.0);
                        break;
                    case 'r':
                        rotation_matrix(1.0, 0.0, 0.0);
                        break;
                    case 'e':
                        scaling_matrix(1.0, 1.0*KG_SCALE_NUM, 1.0);
                        break;
                }
                break;
            
            //DOWN ARROW
            case GLUT_KEY_DOWN:
                switch(_change_type){
                    case 't':
                        translation_matrix(0.0, -1.0, 0.0);
                        break;
                    case 'r':
                        rotation_matrix(-1.0, 0.0, 0.0);
                        break;
                    case 'e':
                        scaling_matrix(1.0, 1.0/KG_SCALE_NUM, 1.0);
                        break;
                }
                break;

            //LEFT ARROW
            case GLUT_KEY_LEFT:
                switch(_change_type){
                    case 't':
                        translation_matrix(-1.0, 0.0, 0.0);
                        break;
                    case 'r':
                        rotation_matrix(0.0, -1.0, 0.0);
                        break;
                    case 'e':
                        scaling_matrix(1.0/KG_SCALE_NUM, 1.0, 1.0);
                        break;
                }
                break;

            //RIGHT ARROW
            case GLUT_KEY_RIGHT: 
                switch(_change_type){
                    case 't':
                        translation_matrix(1.0, 0.0, 0.0);
                        break;
                    case 'r':
                        rotation_matrix(0.0, 1.0, 0.0);
                        break;
                    case 'e':
                        scaling_matrix(1.0*KG_SCALE_NUM, 1.0, 1.0);
                        break;
                }
                break;

            //AVPAG KEY
            case GLUT_KEY_PAGE_UP:
                switch(_change_type){
                    case 't':
                        translation_matrix(0.0, 0.0, 1.0);
                        break;
                    case 'r':
                        rotation_matrix(0.0, 0.0, 1.0);
                        break;
                    case 'e':
                        scaling_matrix(1.0, 1.0, 1.0*KG_SCALE_NUM);
                        break;
                }
                break;

            //REPAG KEY
            case GLUT_KEY_PAGE_DOWN:
                switch(_change_type){
                    case 't':
                        translation_matrix(0.0, 0.0, -1.0);
                        break;
                    case 'r':
                        rotation_matrix(0.0, 0.0, -1.0);
                        break;
                    case 'e':
                        scaling_matrix(1.0, 1.0, 1.0/KG_SCALE_NUM);
                        break;
                }
                break;

            break;
        }
        glutPostRedisplay();
    }
};