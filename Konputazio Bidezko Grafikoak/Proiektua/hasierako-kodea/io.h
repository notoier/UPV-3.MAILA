#ifndef IO_H
#define IO_H
#include "definitions.h"

void keyboard(unsigned char key, int x, int y);
void print_help();
void keyboard_func(int key, int x, int y);
void lighting_init();
void material_init();
void put_light(GLint i);
void fokoaren_matrizea();
void kameraren_matrizea();
void objektu_fokoa_hasieratu();
void camera_focus_init();
void materiala_jarri(int i, object3d *aux_obj);
void change_material();
#endif // IO_H
