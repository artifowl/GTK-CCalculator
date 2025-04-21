#include <gtk/gtk.h>
#include <string.h>
#include "calculator_logic.h"


#define ROW_CALCULATOR 5
#define COLUMN_CALCULATOR 4

static void create_button(GtkWidget *box, GtkWidget *result);
static void app_activate(GApplication *app);


typedef struct {
    const char *label;
    GCallback callback;
}ButtonHandler;



const ButtonHandler handlers[5][4] = {
    {{"DEL", G_CALLBACK(delete_lastNumber)},{"C", G_CALLBACK(delete_number)}, {"CE",  G_CALLBACK(delete_number)},{"/", G_CALLBACK(display_operator)}},
    {{"7", G_CALLBACK(display_number)},{"8", G_CALLBACK(display_number)},{"9", G_CALLBACK(display_number)},{"*", G_CALLBACK(display_operator)}}, 
    {{"4", G_CALLBACK(display_number)},{"5", G_CALLBACK(display_number)},{"6", G_CALLBACK(display_number)},{"+", G_CALLBACK(display_operator)}},
    {{"1", G_CALLBACK(display_number)},{"2", G_CALLBACK(display_number)},{"3", G_CALLBACK(display_number)},{"-", G_CALLBACK(display_operator)}},
    {{"+/-", G_CALLBACK(change_signNumber)},{"0", G_CALLBACK(display_number)},{".", G_CALLBACK(convert_decimal)},{"=", G_CALLBACK(calculate)}}                      
};



static void create_button(GtkWidget *box, GtkWidget *result)
{
    GtkWidget *grid;

    grid = gtk_grid_new();
    gtk_box_append(GTK_BOX(box), grid);
    gtk_widget_set_hexpand(grid,TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_FILL);

    for(int row = 0; row < ROW_CALCULATOR; row++ )
    {
        for(int column = 0; column < COLUMN_CALCULATOR; column++)
        {
            ButtonHandler bh = handlers[row][column];
            GtkWidget *btn = gtk_button_new_with_label(bh.label);
            if (bh.callback != NULL) {
                g_signal_connect(btn, "clicked", bh.callback, result);
            }
            gtk_grid_attach(GTK_GRID(grid), btn, column, row, 1, 1);
            gtk_widget_set_hexpand(btn, TRUE);
            gtk_widget_set_vexpand(btn, TRUE);
        }
    }
}


static void app_activate(GApplication *app)
{
    GtkWindow *win;
    GtkWidget *box;
    GtkWidget *result;
    
    win = GTK_WINDOW(gtk_application_window_new(GTK_APPLICATION(app)));

    // Window's parameter 
    gtk_window_set_title(win, "C Calculator");
    gtk_window_set_default_size(win,400, 600);
    gtk_window_set_resizable(win, FALSE);

    // Box's parameter
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // Result's field
    result = gtk_label_new("0");
    
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_frame_set_child(GTK_FRAME(frame), result);

    gtk_widget_set_size_request(result, 100, 120);

    gtk_widget_set_halign(result, GTK_ALIGN_END);
    gtk_widget_set_valign(result, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(box), frame);


    // Button's parameter
    create_button(box, result);
    

    gtk_window_set_child(win,box);
    gtk_window_present(win);
}


int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;
  
  app = gtk_application_new("com.github.artifowl.calculator", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);

  g_object_unref(app);
  return status;

}
