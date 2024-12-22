# Options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# fichiers source
SRCS = main.c noeud.c data.c 
OBJS = $(SRCS:.c=.o)
TARGET = C-wire

# creation de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# génration de l'édition de lien
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# suppression des fichiers temporaires
clean:
	rm -f $(OBJS) $(TARGET)