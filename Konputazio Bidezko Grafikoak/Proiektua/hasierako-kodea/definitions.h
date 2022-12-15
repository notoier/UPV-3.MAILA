#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <GL/gl.h>

/** DEFINITIONS **/

#define KG_WINDOW_TITLE                     "Oier Alvarez Parada"
#define KG_WINDOW_WIDTH                     1920
#define KG_WINDOW_HEIGHT                    1080
#define KG_WINDOW_X                         50
#define KG_WINDOW_Y                         50

#define KG_MSSG_SELECT_FILE                 "Idatz ezazu fitxategiaren path-a: "
#define KG_MSSG_FILENOTFOUND                "Fitxategi hori ez da existitzen!!"
#define KG_MSSG_INVALIDFILE                 "Arazoren bat egon da fitxategiarekin ..."
#define KG_MSSG_EMPTYFILE                   "Fitxategia hutsik dago"
#define KG_MSSG_FILEREAD                    "Fitxategiaren irakurketa buruta"
#define KG_MSSG_NOOBJECT                    "Ez dago objekturik aukeratuta"

//#define KG_STEP_MOVE                        5.0f
//#define KG_STEP_ROTATE                      10.0f
#define KG_STEP_ZOOM                        0.75
#define KG_STEP_ZOOM_OUT                    1.25
#define KG_STEP_CAMERA_ANGLE                5.0f

#define KG_ORTHO_X_MIN_INIT                -5
#define KG_ORTHO_X_MAX_INIT                 5
#define KG_ORTHO_Y_MIN_INIT                -5
#define KG_ORTHO_Y_MAX_INIT                 5
#define KG_ORTHO_Z_MIN_INIT                -10       // ikuslearen atzean negatiboa baita
#define KG_ORTHO_Z_MAX_INIT                 10000

#define KG_COL_BACK_R                       0.30f
#define KG_COL_BACK_G                       0.30f
#define KG_COL_BACK_B                       0.30f
#define KG_COL_BACK_A                       1.00f

#define KG_COL_SELECTED_R                   0.2f
#define KG_COL_SELECTED_G                   0.89f
#define KG_COL_SELECTED_B                   0.89f

#define KG_COL_NONSELECTED_R                1.00f
#define KG_COL_NONSELECTED_G                1.00f
#define KG_COL_NONSELECTED_B                1.00f

#define KG_COL_X_AXIS_R                     1.0f
#define KG_COL_X_AXIS_G                     0.0f    //Color: magenta
#define KG_COL_X_AXIS_B                     1.0f

#define KG_COL_Y_AXIS_R                     1.0f
#define KG_COL_Y_AXIS_G                     1.0f    //Color: yellow
#define KG_COL_Y_AXIS_B                     0.0f

#define KG_COL_Z_AXIS_R                     0.0f
#define KG_COL_Z_AXIS_G                     1.0f    //Color: cian
#define KG_COL_Z_AXIS_B                     1.0f

#define KG_TRAN_STEP                        0.5f
#define KG_ROT_ANGLE                        0.0872665f //5º in radians (5 * π/180)
#define KG_SCALE_NUM                        1.1

#define KG_GRID_LAYOUT                      1000

#define KG_MAX_DOUBLE                       10E25

/** STRUCTURES **/

/****************************
 * Structure to store the   *
 * coordinates of 3D points *
 ****************************/
typedef struct {
    GLdouble x, y, z;
} point3;

/*****************************
 * Structure to store the    *
 * coordinates of 3D vectors *
 *****************************/
typedef struct {
    GLdouble x, y, z;
} vector3;

/****************************
 * Structure to store the   *
 * colors in RGB mode       *
 ****************************/
typedef struct {
    GLfloat r, g, b;
} color3;

/****************************
 * Structure to store       *
 * objects' vertices         *
 ****************************/
typedef struct {
    point3 coord;                       /* coordinates,x, y, z */
    GLint num_faces;                    /* number of faces that share this vertex */
} vertex;


typedef struct MZ{
    double M[16];
    struct MZ *hptr;
} MZ;

/****************************
 * Structure to store       *
 * objects' faces or        *
 * polygons                 *
 ****************************/
typedef struct {
    GLint num_vertices;                 /* number of vertices in the face */
    GLint *vertex_table;                /* table with the index of each vertex */
} face;

/****************************
 * Structure to store all   *
 * changes done to an object*
 ****************************/
/* typedef struct AZ{
    char c;
    struct AZ* hptr;
} AZ;
 */

/****************************
 * Structure to store a     *
 * pile of 3D objects       *
 ****************************/
struct object3d{
    GLint num_vertices;                 /* number of vertices in the object*/
    vertex *vertex_table;               /* table of vertices */
    GLint num_faces;                    /* number of faces in the object */
    face *face_table;                   /* table of faces */
    point3 min;                         /* coordinates' lower bounds */
    point3 max;                         /* coordinates' bigger bounds */
    struct object3d *next;              /* next element in the pile of objects */
    MZ *MZptr;
    //AZ *AZptr;
};

struct camera{
    double x_max;   // Max X coordinate
    double x_min;   // Min X coordinate
    double y_max;   // Max Y coordinate
    double y_min;   // Min Y coordinate
    double near;    // Max Z coordinate
    double far;     // Min Z coordinate
    int projection; // Type of projection
    MZ *MZptr;      // Matrix list
    struct camera *hptr;  // Camera list
};

typedef struct object3d object3d;
typedef struct camera camera;

#endif // DEFINITIONS_H
