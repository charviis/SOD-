CC = clang
CFLAGS = -lm -Ofast -march=native -Wall -std=c99

sod: sod.c
	$(CC) sod.c samples/cnn_face_detection.c -o sod_face_detect -I. $(CFLAGS)

	