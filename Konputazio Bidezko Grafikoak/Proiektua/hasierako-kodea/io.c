#include "definitions.h"
#include "load_obj.h"
#include "display.h"
#include <GL/glut.h>
#include <stdio.h>

extern object3d * _first_object;
extern object3d * _selected_object;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

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
    printf("<I>\t\t Objektuari dagokion informazioa pantailaratu");
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
            auxiliar_object->MZptr = NULL;
            for (i = 0; i < 16; i++){
                auxiliar_object->MZptr->M[i] = 0, 0;
            }
            auxiliar_object->MZptr->M[0] = 1, 0;
            auxiliar_object->MZptr->M[5] = 1, 0;
            auxiliar_object->MZptr->M[10] = 1, 0;
            auxiliar_object->MZptr->M[15] = 1, 0;
            /*Insert the new object in the list*/
            auxiliar_object->next = _first_object;
            _first_object = auxiliar_object;
            _selected_object = _first_object;
            printf("%s\n",KG_MSSG_FILEREAD);
            break;
        }
        break;
    
    case 'i':
    case 'I':
        //TODO:
        //Check if there's an object selected
        if(_selected_object == 0) break; 
        //GLint n_faces = (char) _selected_object->num_faces;
        //GLint n_vertices = _selected_object->num_vertices;
        //output(750, 750, 0, 0, 0, GLUT_BITMAP_HELVETICA_10,  n_faces);
        output(1000, 500, 0, 0, 0, GLUT_BITMAP_HELVETICA_10, "PATATA");

    case 9: /* <TAB> */
        //Check if there's any object selected
        if (_selected_object == 0){
            _selected_object = _first_object;
        } else {
            //If there is, pass to the next object
            _selected_object = _selected_object->next;
        }
        break;

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

    case '-': //ZOOM   
        /* Decrease the projection plane; compute the new dimensions*/
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

    case '+': //ZOOM_OUT
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

    case '?':
        print_help();
        break;

    case 27: /* <ESC> */
        exit(0);
        break;

    default:
        printf("Default");
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}

