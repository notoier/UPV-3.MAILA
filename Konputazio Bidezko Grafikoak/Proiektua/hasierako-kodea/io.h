#ifndef IO_H
#define IO_H

void keyboard(unsigned char key, int x, int y);
void print_help();
void keyboard_func(int key, int x, int y);
void get_translation_matrix(double *mptr, double x, double y, double z);
#endif // IO_H
