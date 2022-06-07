#include "philosophers.h"

int t_queue_get (t_queue *q)
{
        int a = q->data[q->high--];
        q->count--;

        if (q->high < 0) {
                q->high = q->max - 1;
        }

        return a;
}

void t_queue_add (t_queue *q, int a)
{
    if (q->count == q->max) {
            fprintf (stderr, "not enough queue size\n");
            return;
    }

    q->data[q->low--] = a;
    q->count++;

    if (q->low < 0) {
            q->low = q->max - 1;
    }
}

t_queue *t_queue_init (size_t size)
{
        t_queue * q = calloc (1, sizeof (t_queue));
        q->data = calloc (size, sizeof (int));
        q->low = q->high = size - 1;
        q->max = size;

        return q;
}