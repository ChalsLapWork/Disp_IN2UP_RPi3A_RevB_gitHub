#include <gtk/gtk.h>

// Función que se ejecuta cuando se hace clic en el botón
static void on_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("¡Botón clickeado!\n");
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;

    // Inicializa GTK
    gtk_init(&argc, &argv);

    // Crea una ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ventana GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Conecta el evento de cerrar la ventana
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Crea un botón
    button = gtk_button_new_with_label("Haz clic aquí");

    // Conecta el evento del botón
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // Agrega el botón a la ventana
    gtk_container_add(GTK_CONTAINER(window), button);

    // Muestra todo
    gtk_widget_show_all(window);

    // Entra al loop principal de GTK
    gtk_main();

    return 0;
}
