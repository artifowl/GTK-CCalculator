#ifndef CALCULATOR_LOGIC_H
#define CALCULATOR_LOGIC_H

#include <gtk/gtk.h>

//number 
void display_number(GtkWidget *button, gpointer user_data);
//operator
void display_operator(GtkWidget *button, gpointer user_data);
//DEL
void delete_lastNumber(GtkWidget *button, gpointer user_data);
//CE-C
void delete_number(GtkWidget *button, gpointer user_data);
// +/-
void change_signNumber(GtkWidget *button, gpointer user_data);
// . 
void convert_decimal(GtkWidget *button, gpointer user_data);
// = 
void calculate(GtkWidget *button, gpointer user_data);


#endif