#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_THREADS 3

char* zeile = NULL;
int laenge;
pthread_t pts[NUM_THREADS];

void* threadFunktion(void* arg) {
    int start = *((int*)arg);
    int end = (start + 1) * laenge / NUM_THREADS;
    int i, temp = 0;
    
    for (i = start; i < end; i++) {
        if (zeile[i] == '1') {
            int power = end - i - 1;
            temp += pow(2, power);
        }
    }
    
    int* ergebnis = malloc(sizeof(int));
    *ergebnis = temp;
    
    pthread_exit(ergebnis);
}

int main() {
    int i, zahl = 0;
    printf("Binärzahl: ");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character

    zeile = malloc(strlen(buffer) + 1);
    strcpy(zeile, buffer);
    laenge = strlen(zeile);
    
    int intervalle[NUM_THREADS];
    
    for (i = 0; i < NUM_THREADS; i++) {
        intervalle[i] = i * laenge / NUM_THREADS;
        pthread_create(&pts[i], NULL, threadFunktion, (void*)&intervalle[i]);
    }
    
    for (i = 0; i < NUM_THREADS; i++) {
        void* erg;
        pthread_join(pts[i], &erg);
        zahl += *((int*)erg);
        free(erg);
    }
    
    printf("Dezimalzahl: %d\n", zahl);
    
    free(zeile);
    
    return 0;
}
