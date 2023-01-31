#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <GL/gl.h>

/** DEFINITIONS **/

#define KG_WINDOW_TITLE                     "Irene Quesada Pizarro"
#define KG_WINDOW_WIDTH                     500
#define KG_WINDOW_HEIGHT                    500
#define KG_WINDOW_X                         50
#define KG_WINDOW_Y                         50

#define KG_MSSG_SELECT_FILE                 "Idatz ezazu fitxategiaren path-a: "
#define KG_MSSG_FILENOTFOUND                "Fitxategi hori ez da existitzen!!"
#define KG_MSSG_INVALIDFILE                 "Arazoren bat egon da fitxategiarekin ..."
#define KG_MSSG_EMPTYFILE                   "Fitxategia hutsik dago"
#define KG_MSSG_FILEREAD                    "Fitxategiaren irakurketa buruta"

#define KG_STEP_MOVE                        5.0f
#define KG_STEP_ROTATE                      10.0f
#define KG_STEP_ZOOM                        0.75
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

#define KG_COL_SELECTED_R                   1.00f
#define KG_COL_SELECTED_G                   0.75f
#define KG_COL_SELECTED_B                   0.00f

#define KG_COL_NONSELECTED_R                1.00f
#define KG_COL_NONSELECTED_G                1.00f
#define KG_COL_NONSELECTED_B                1.00f

#define KG_COL_X_AXIS_R                     1.0f
#define KG_COL_X_AXIS_G                     0.0f
#define KG_COL_X_AXIS_B                     0.0f

#define KG_COL_Y_AXIS_R                     0.0f
#define KG_COL_Y_AXIS_G                     1.0f
#define KG_COL_Y_AXIS_B                     0.0f

#define KG_COL_Z_AXIS_R                     0.0f
#define KG_COL_Z_AXIS_G                     0.0f
#define KG_COL_Z_AXIS_B                     1.0f

#define KG_MAX_DOUBLE                       10E25

#define FLAT                                0
#define SMOOTH                              1

#define EGUZKIA                             0
#define BONBILLA                            1
#define KAM_ARGIA                           2
#define OBJ_ARGIA                           3

/*Egoera aldagaia lokala (0) edo globala (1) den adierazten du*/
extern int LG;
/*Biraketan mugituko den angelua*/
extern double biraketa_matrizea;
/*Lekuz aldaketa*/
//extern double traslazioa;
/*Eskalaketa aldaketa*/
extern double eskalaketa;
/*Aukeratutako objektu mota*/
extern int obj_mota;
/*kameraren moduak: hegaldi modua (0), analisi modua(1)*/
extern int kamera_mota;
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
    vector3 b_normala;                  /* erpin bakoitzak bektoren normal bat dauka */
} vertex;

/****************************
 * Structure to store       *
 * objects' faces or        *
 * polygons                 *
 ****************************/
typedef struct {
    GLint num_vertices;                 /* number of vertices in the face */
    GLint *vertex_table;                /* table with the index of each vertex */
    vector3 b_normala;                  /* aurpegi bakoitzak bektoren normal bat dauka*/
} face;

/****************************
 *Matrize zerrenda definitu *
 ****************************/

typedef struct mz{
    double M[16];
    struct mz * hptr;
}mz;

/****************************
 *     Materiala definitu   *
 ****************************/
typedef struct {
    /*Materialak zehazteko behar diren parametroak*/
    GLfloat m_difusioa[4];           
    GLfloat m_ingurunea[4];
    GLfloat m_espekularra[4];
    GLfloat argirik_ez[1];
} materialak;


/****************************
 *    Argia definitu        *
 ****************************/
typedef struct
{
    GLfloat a_difusioa[4];
    GLfloat a_ingurunea[4];
    GLfloat a_espekularra[4];
    GLfloat a_posizioa[4];
    GLint is_on;
    GLint type;
    GLfloat direkzioa[3];
    GLfloat matrize_obj[16];
    GLfloat cut_off;
}argiak;


/****************************
 *  Matrize lista definitu  *
 ****************************/
typedef struct matrizeen_lista{
    GLfloat M[16];
    struct matrizeen_lista *nextptr;
} matrizeen_lista;

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
    mz*mzptr;                           /* Hurrengo matrizearen erakuslea*/
    GLint fs;                           /* flat (FLAT edo 0) edo smooth (SMOOTH edo 1) aukeratzeko*/
    materialak *materialak;             /*objektua osatzen duen materiala*/
    matrizeen_lista * matrizeen_lista;
};

typedef struct object3d object3d;

//Kamera objektu bat bezala kudeatuko dugu, erpin eta poligonorik gabe, beraz, ez dugu egitura berria definitu behar
/****************************
 *     Kamera definitu      *
 ****************************/
    //struct kamera{
    //double Xmax;                     /* Kameren ikuspegiaren altuera maximoa */
    //double Xmin;                     /* Kameren ikuspegiaren altuera minimoa */
    //double Ymax;                     /* Kameren ikuspegiaren zabalera maximoa */
    //double Ymin;                     /* Kameren ikuspegiaren zabalera minimoa */
    //double near;                     /* hurbileko planoa */
    //double far;                      /* urruneko planoa */
    //int proiekzioa;                  /* proiekzioa perspektiban edo paraleloan */
    //struct kamera *next;             /* Pilako hurrego kamera */
    //mz*mzptr;                        /* Hurrengo matrizearen erakuslea */
//};
//typedef struct kamera kamera;



#endif // DEFINITIONS_H
