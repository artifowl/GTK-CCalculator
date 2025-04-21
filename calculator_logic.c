#include "calculator_logic.h"
#include <gtk/gtk.h>
#include <ctype.h>


#define NUMBER(x) ((x) == '0' || (x) == '1' || (x) == '2' || (x) == '3' || (x) == '4' || (x) == '5' || (x) == '6' || (x) == '7' || (x) == '8' || (x) == '9' )
#define OPERATOR(x) ((x) == '+' || (x) == '-' || (x) == '*' || (x) == '/')


void delete_lastNumber(GtkWidget *button, gpointer user_data)
{
    const char *label_text = gtk_label_get_label(GTK_LABEL(user_data));
    char *text = NULL;

    size_t size = strlen(label_text);

    if (strcmp(label_text, "0") == 0) {
        return;
    }
    else if (size == 1) {
        text = g_strdup("0");
    }
    else {
        text = g_malloc(size); 
        memcpy(text, label_text, size - 1);
        text[size - 1] = '\0';
    }

    gtk_label_set_label(GTK_LABEL(user_data), text);
    g_free(text);
}


void delete_number(GtkWidget *button, gpointer user_data)
{
    gtk_label_set_label(GTK_LABEL(user_data), "0");
}


void display_number(GtkWidget *button, gpointer user_data)
{
    const char *button_text = gtk_button_get_label(GTK_BUTTON(button));
    const char *label_text = gtk_label_get_text(GTK_LABEL(user_data));

    if (!button_text || !label_text)
        return;

    char *text = (strcmp(label_text, "0") == 0)
        ? g_strdup(button_text)
        : g_strconcat(label_text, button_text, NULL);

    gtk_label_set_text(GTK_LABEL(user_data), text);
    g_free(text);
}


void display_operator(GtkWidget *button, gpointer user_data)
{
    const char *button_text = gtk_button_get_label(GTK_BUTTON(button));
    const char *label_text = gtk_label_get_text(GTK_LABEL(user_data));
    
    if (!button_text || !label_text)
        return;
    
    size_t size_label = strlen(label_text);
    
    char last_char = label_text[size_label - 1];
    if (OPERATOR(last_char)) 
    {
        return;
    }

    char *text = g_strconcat(label_text, button_text, NULL);
    gtk_label_set_text(GTK_LABEL(user_data), text);
    g_free(text);
}

void change_signNumber(GtkWidget *button, gpointer user_data)
{
    const char *label_text = gtk_label_get_text(GTK_LABEL(user_data));
    if (!label_text) return;

    size_t size_label = strlen(label_text);
    if (size_label == 0) return;

    int i = size_label - 1;

    while (i >= 0 && !OPERATOR(label_text[i])) {
        i--;
    }

    size_t start_index = (i >= 0) ? i + 1 : 0;
    char *number = g_strdup(label_text + start_index);
    char *prefix = g_strndup(label_text, start_index);

    // Change sign
    if (prefix[i] == '-') prefix[i] = '+';
    else if (prefix[i] == '+') prefix[i] = '-';
    else {
        char *tmp = g_strconcat("-", number, NULL);
        g_free(number);
        number = tmp;
    }

    char *result = g_strconcat(prefix, number, NULL);
    gtk_label_set_text(GTK_LABEL(user_data), result);

    g_free(prefix);
    g_free(number);
    g_free(result);
}


void convert_decimal(GtkWidget *button, gpointer user_data)
{
    const char *label_text = gtk_label_get_text(user_data);
    size_t size_label = strlen(label_text);
    int i = size_label - 1;

    while(i > 0 && !OPERATOR(label_text[i]))
    {
        g_print("%c", label_text[i]);
        if (label_text[i] == '.') return;
        i--;
    }   
    
    char *text = g_strconcat(label_text, ".", NULL);
    gtk_label_set_text(GTK_LABEL(user_data), text);
    g_free(text);

}

void calculate(GtkWidget *button, gpointer user_data)
{
    const char *label_text = gtk_label_get_text(GTK_LABEL(user_data));
    size_t size_label = strlen(label_text);

    if (size_label == 0) return;

    char number[64] = {0};   
    char *endptr;
    int j = 0;
    double result = 0.0, val;
    short int sign_calcul = 1;
    char last_op = '+';      

    for (int i = 0; i < size_label; i++)
    {
        if (isdigit(label_text[i]) || label_text[i] == '.')  
        {
            number[j++] = label_text[i];
        }
        else
        {
            if (j == 0)  
            {
                if (label_text[i] == '-') sign_calcul = -1;
                else sign_calcul = 1;
                continue;
            }

            number[j] = '\0';
            val = strtod(number, &endptr);

            if (*endptr != '\0') {
                printf("Invalid conversion for : %s\n", number);
                return;
            }

            switch (last_op) {
                case '+': result += sign_calcul * val; break;
                case '-': result -= sign_calcul * val; break;
                case '*': result *= sign_calcul * val; break;
                case '/':
                    if (val != 0) result /= sign_calcul * val;
                    else {
                        printf("Division per zero.\n");
                        return;
                    }
                    break;
                default:
                    printf("unknown operator : %c\n", last_op);
                    return;
            }

            last_op = label_text[i];
            sign_calcul = 1;
            j = 0;
        }
    }

    if (j > 0) {
        number[j] = '\0';
        val = strtod(number, &endptr);
        if (*endptr == '\0') {
            switch (last_op) {
                case '+': result += sign_calcul * val; break;
                case '-': result -= sign_calcul * val; break;
                case '*': result *= sign_calcul * val; break;
                case '/':
                    if (val != 0) result /= sign_calcul * val;
                    else {
                        printf("Division per zero.\n");
                        return;
                    }
                    break;
            }
        }
    }

    char buffer[50];
    if (result == (int)result){
        snprintf(buffer, sizeof(buffer), "%.0f", result);
    }
    else{
        snprintf(buffer, sizeof(buffer), "%.2f", result);
    }
    
    gtk_label_set_text(GTK_LABEL(user_data), buffer);
}

