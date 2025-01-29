#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function prototypes
void generate_password(GtkButton *button, gpointer user_data);
void save_data(GtkButton *button, gpointer user_data);
void toggle_password_visibility(GtkButton *button, gpointer user_data);

// Global widgets
GtkWidget *title_entry, *email_entry, *username_entry, *password_entry, *length_entry, *special_checkbox, *save_label, *toggle_button;
gboolean show_password = FALSE;

void generate_password(GtkButton *button, gpointer user_data) {
    const char *length_text = gtk_entry_get_text(GTK_ENTRY(length_entry));
    int length = atoi(length_text);
    gboolean include_special = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(special_checkbox));

    const char *lower_case = "abcdefghijklmnopqrstuvwxyz";
    const char *upper_case = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *digits = "0123456789";
    const char *symbols = "!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?";

    char all_chars[256] = "";
    strcat(all_chars, lower_case);
    strcat(all_chars, upper_case);
    strcat(all_chars, digits);
    if (include_special) {
        strcat(all_chars, symbols);
    }

    char password[256] = "";
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        password[i] = all_chars[rand() % strlen(all_chars)];
    }
    password[length] = '\0';

    gtk_entry_set_text(GTK_ENTRY(password_entry), password);
}

void save_data(GtkButton *button, gpointer user_data) {
    const char *title = gtk_entry_get_text(GTK_ENTRY(title_entry));
    const char *email = gtk_entry_get_text(GTK_ENTRY(email_entry));
    const char *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const char *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    FILE *file = fopen("passwords.txt", "a");
    if (file) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char time_str[64];
        strftime(time_str, sizeof(time_str), "%d-%m-%Y %H:%M:%S", t);

        fprintf(file, "Title: %s\n", title);
        fprintf(file, "Email: %s\n", email);
        fprintf(file, "Username: %s\n", username);
        fprintf(file, "Password: %s\n", password);
        fprintf(file, "Time: %s\n", time_str);
        fprintf(file, "==========================================\n");
        fclose(file);

        gtk_label_set_text(GTK_LABEL(save_label), "Saved Successfully!");
    } else {
        gtk_label_set_text(GTK_LABEL(save_label), "Error saving data!");
    }

    gtk_entry_set_text(GTK_ENTRY(title_entry), "");
    gtk_entry_set_text(GTK_ENTRY(email_entry), "");
    gtk_entry_set_text(GTK_ENTRY(username_entry), "");
    gtk_entry_set_text(GTK_ENTRY(password_entry), "");
    gtk_entry_set_text(GTK_ENTRY(length_entry), "12");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(special_checkbox), FALSE);
}

void toggle_password_visibility(GtkButton *button, gpointer user_data) {
    if (show_password) {
        gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
        gtk_button_set_label(GTK_BUTTON(toggle_button), "Show Password");
    } else {
        gtk_entry_set_visibility(GTK_ENTRY(password_entry), TRUE);
        gtk_button_set_label(GTK_BUTTON(toggle_button), "Hide Password");
    }
    show_password = !show_password;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Password Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a grid layout
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    // Title
    GtkWidget *title_label = gtk_label_new("Title:");
    gtk_grid_attach(GTK_GRID(grid), title_label, 0, 0, 1, 1);
    title_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), title_entry, 1, 0, 2, 1);

    // Email
    GtkWidget *email_label = gtk_label_new("Email:");
    gtk_grid_attach(GTK_GRID(grid), email_label, 0, 1, 1, 1);
    email_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), email_entry, 1, 1, 2, 1);

    // Username
    GtkWidget *username_label = gtk_label_new("Username:");
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 2, 1, 1);
    username_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 2, 2, 1);

    // Password
    GtkWidget *password_label = gtk_label_new("Password:");
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 3, 1, 1);
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 3, 1, 1);

    toggle_button = gtk_button_new_with_label("Show Password");
    g_signal_connect(toggle_button, "clicked", G_CALLBACK(toggle_password_visibility), NULL);
    gtk_grid_attach(GTK_GRID(grid), toggle_button, 2, 3, 1, 1);

    // Password settings
    GtkWidget *settings_label = gtk_label_new("Password Settings:");
    gtk_grid_attach(GTK_GRID(grid), settings_label, 0, 4, 2, 1);

    GtkWidget *length_label = gtk_label_new("Length:");
    gtk_grid_attach(GTK_GRID(grid), length_label, 0, 5, 1, 1);
    length_entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(length_entry), "12");
    gtk_grid_attach(GTK_GRID(grid), length_entry, 1, 5, 1, 1);

    special_checkbox = gtk_check_button_new_with_label("Include special characters");
    gtk_grid_attach(GTK_GRID(grid), special_checkbox, 1, 6, 2, 1);

    GtkWidget *generate_button = gtk_button_new_with_label("Generate Password");
    g_signal_connect(generate_button, "clicked", G_CALLBACK(generate_password), NULL);
    gtk_grid_attach(GTK_GRID(grid), generate_button, 0, 7, 3, 1);

    // Save button
    GtkWidget *save_button = gtk_button_new_with_label("Save");
    g_signal_connect(save_button, "clicked", G_CALLBACK(save_data), NULL);
    gtk_grid_attach(GTK_GRID(grid), save_button, 0, 8, 3, 1);

    // Save status label
    save_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), save_label, 0, 9, 3, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
