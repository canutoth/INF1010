#include <stdio.h>
#include <stdlib.h>

typedef struct patient Patient;
struct patient {
    int num;
    char color;
    Patient* next;
};

typedef struct queue Queue;
struct queue {
    Patient* head;
    Patient* tail;
};

Patient* createPatient(int num, char color);
void enqueue(Queue* q, Patient* p);
Patient* dequeue(Queue* q);
void printQueue(Queue* q);
void manageQueue(FILE* file, Queue* q);
void removePatient(Queue* q, int num, char color);

int main(void) {
    FILE* file = fopen("sugestao_arq.txt", "r");
    if (file == NULL) {
        printf("Error: could't open the file.\n\n");
        exit(1);
    }

    Queue q = { NULL, NULL };
    manageQueue(file, &q);
    fclose(file);

    return 0;
}

Patient* createPatient(int num, char color) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    if (newPatient == NULL) {
        printf("Error of memory allocation.\n\n");
        exit(1);
    }
    newPatient->num = num;
    newPatient->color = color;
    newPatient->next = NULL;
    return newPatient;
}

void enqueue(Queue* q, Patient* p) {
    if (q->head == NULL) {
        q->head = q->tail = p;
        return;
    }

    Patient* current = q->head;
    Patient* prev = NULL;

    while (current != NULL) {
        if (p->color == 'R' && current->color != 'R') {
            break;
        }
        if (p->color == 'Y' && current->color == 'G') {
            break;
        }
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        p->next = q->head;
        q->head = p;
    }
    else {
        prev->next = p;
        p->next = current;
        if (current == NULL) {
            q->tail = p;
        }
    }
}

Patient* dequeue(Queue* q) {
    if (q->head == NULL) {
        printf("Queue is empty.\n\n");
        return NULL;
    }

    Patient* temp = q->head;
    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
    }

    return temp;
}

void removePatient(Queue* q, int num, char color) {
    if (q->head == NULL) {
        printf("Queue is empty.\n\n");
        return;
    }

    Patient* current = q->head;
    Patient* prev = NULL;

    while (current != NULL && current->num != num) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Couldn't find Patient %d.\n\n", num);
        return;
    }

    if (prev == NULL) {
        q->head = current->next;
    }
    else {
        prev->next = current->next;
    }

    if (current == q->tail) {
        q->tail = prev;
    }

    free(current);
    if (color == 'R') {
        printf("Patient %d with RED (high) priority left the hospital queue.\n\n", num);
    }
    else if (color == 'Y'){
        printf("Patient %d with YELLOW (medium) priority left the hospital queue.\n\n", num);
    }
    else printf("Patient %d with GREEN (low) priority left the hospital queue.\n\n", num);
}

void printQueue(Queue* q) {
    Patient* current = q->head;
    int redCount = 0, yellowCount = 0, greenCount = 0;

    printf("\nPatient list:\n");
    while (current != NULL) {
        if (current->color == 'R'){
          printf("Patient %d - Priority RED (high)\n", current->num);
          redCount++;
        }
        else if (current->color == 'Y'){
          printf("Patient %d - Priority YELLOW (medium)\n", current->num);
          yellowCount++;
        }
        else if (current->color == 'G'){
          printf("Patient %d - Priority GREEN (low)\n", current->num);
          greenCount++;
        }
        current = current->next;
    }
    printf("Red: %d, Yellow: %d, Green: %d\n\n", redCount, yellowCount, greenCount);
}

void manageQueue(FILE* file, Queue* q) {
    char action;
    int num;
    char color;

    while (fscanf(file, " %c %d %c", &action, &num, &color) != EOF) {
        if (action == 'E') {
            Patient* p = createPatient(num, color);
            enqueue(q, p);
          if (color == 'R') {
            printf("Patient %d with RED (high) priority joined the hospital queue.\n\n", num);
          }
          else if (color == 'Y'){
            printf("Patient %d with YELLOW (medium) priority joined the hospital queue.\n\n", num);
          }
          else if (color == 'G') printf("Patient %d with GREEN (low) priority joined the hospital queue.\n\n", num);
          else printf("Invalid priority. %c is neither RED (high), YELLOW (medium) or GREEN (low) priority", color);
        }
        else if (action == 'S') {
            Patient* p = dequeue(q);
            if (p != NULL) {
              if (color == 'R') {
                printf("Patient %d with RED (high) priority was treated (removed from the queue).\n\n", num);
              }
              else if (color == 'Y'){
                printf("Patient %d with YELLOW (medium) priority was treated (removed from the queue).\n\n", num);
              }
              else if (color == 'G') printf("Patient %d with GREEN (low) priority was treated (removed from the queue).\n\n", num);
              else printf("Invalid priority. %c is neither RED (high), YELLOW (medium) or GREEN (low) priority", color);
              free(p);
            }
        }
        else if (action == 'D') {
            removePatient(q, num, color);
        }
        else printf ("Invalid action: %c is neither an Entrance, an Exit or a Desistance.\n\n", action);
        printQueue(q);
    }
}