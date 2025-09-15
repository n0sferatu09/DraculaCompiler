gcc main.c -o main -Wall -Wextra $(pkg-config --cflags --libs glib-2.0)
