#include "definitions.h"
#include <string.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;

/**
 * @brief Function to draw the axes
 */
void draw_axes()
{

    /**
      * @brief Draw 3 dimensional axes
      * Change @param KG_COL_XYZ_RGB constant value in definitions.h to display diferent colors for each axis 
     **/

    /*Draw X axis*/
    glColor3f(KG_COL_X_AXIS_R,KG_COL_X_AXIS_G,KG_COL_X_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(1000,0,0);
    glVertex3d(0,0,0);
    glEnd();
    /*Draw Y axis*/
    glColor3f(KG_COL_Y_AXIS_R,KG_COL_Y_AXIS_G,KG_COL_Y_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,30,0);
    glVertex3d(0,0,0);
    glEnd();
    /*Draw Z axis*/
    glColor3f(KG_COL_Z_AXIS_R,KG_COL_Z_AXIS_G,KG_COL_Z_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,0,1000);
    glVertex3d(0,0,0);
    glEnd();
}

/**
 * @brief Draw a grid
 * 
 */
void draw_grid()
{
} 


/**
 * @brief Printing on window
 * 
 * @param x x coordinate of the window point where the text will be displayed
 * @param y y coordinate of the window point where the text will be displayed
 * @param r Red color amount for the text in rgb format
 * @param g Green color amount for the text in rgb format
 * @param b Blue color amount for the text in rgb format
 * @param font Font type for the text
 * @param string Text to display
 */
void output(int x, int y, float r, float g, float b, void* font, char *string)
{
  glColor3f( r, g, b );
  x = x / KG_WINDOW_WIDTH;
  y = y / KG_WINDOW_HEIGHT;
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  printf("%d",len);
  for (i = 0; i < len; i++) {

    glutBitmapCharacter(font, string[i]);
  }
}

/**
 * @brief Callback reshape function. We just store the new proportions of the window
 * @param width New width of the window
 * 
 * @param height New height of the window
 */
void reshape(int width, int height) {
    // we will use a rectangular viewport allways
    if (width > height)
        glViewport(0, 0, height, height);
      else 
        glViewport(0, 0, width, width);
    //  old code
    //  glViewport(0, 0, width, height);
    //  Take care, the width and height are integer numbers, but the ratio is a GLdouble so, in order to avoid
    //  rounding the ratio to integer values we need to cast width and height before computing the ratio */
    // _window_ratio = (GLdouble) width / (GLdouble) height;
}


/**
 * @brief Callback display function
 */
void display(void) {
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;

    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Define the projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
/*
    //When the window is wider than our original projection plane we extend the plane in the X axis //
    if ((_ortho_x_max - _ortho_x_min) / (_ortho_y_max - _ortho_y_min) < _window_ratio) {
        // New width //
        GLdouble wd = (_ortho_y_max - _ortho_y_min) * _window_ratio;
        // Midpoint in the X axis //
        GLdouble midpt = (_ortho_x_min + _ortho_x_max) / 2;
        // Definition of the projection //
        glOrtho(midpt - (wd / 2), midpt + (wd / 2), _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);
    } else {// In the opposite situation we extend the Y axis //
        // New height //
        GLdouble he = (_ortho_x_max - _ortho_x_min) / _window_ratio;
        // Midpoint in the Y axis //
        GLdouble midpt = (_ortho_y_min + _ortho_y_max) / 2;
        //Definition of the projection//
        glOrtho(_ortho_x_min, _ortho_x_max, midpt - (he / 2), midpt + (he / 2), _ortho_z_min, _ortho_z_max);
    }
*/    
    glOrtho(_ortho_x_min, _ortho_x_max, _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);

    /* Now we start drawing the object */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10,1,10, 0,0,0, 0,45,0);

    /*First, we draw the axes*/
    draw_axes();

    /*Now we draw the grid*/
    draw_grid();

    
    /*Now each of the objects in the list*/
    while (aux_obj != 0) {

        /* Select the color, depending on whether the current object is the selected one or not */
        if (aux_obj == _selected_object){
            glColor3f(KG_COL_SELECTED_R,KG_COL_SELECTED_G,KG_COL_SELECTED_B);
        }else{
            glColor3f(KG_COL_NONSELECTED_R,KG_COL_NONSELECTED_G,KG_COL_NONSELECTED_B);
        }

        /* Draw the object; for each face create a new polygon with the corresponding vertex */
        glLoadMatrixd(aux_obj->MZptr->M);
        //glLoadIdentity(); 
        for (f = 0; f < aux_obj->num_faces; f++) {
            glBegin(GL_POLYGON);
            for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {
                v_index = aux_obj->face_table[f].vertex_table[v];
                glVertex3d(aux_obj->vertex_table[v_index].coord.x,
                        aux_obj->vertex_table[v_index].coord.y,
                        aux_obj->vertex_table[v_index].coord.z);

            }
            glEnd();
        }
        aux_obj = aux_obj->next;
    }
    /*Do the actual drawing*/
    glFlush();
}
