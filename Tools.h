/* Arthur Hiratsuka Rezende - 13687108 */
#ifndef TOOLS_H
#define TOOLS_H

#include "Lista.h"
// Auxiliares
void swap(elem *elem_a, elem *elem_b);
void checkpoint(int numero);

// Ordenacao
void bubbleSort(LIST *list);
void optimized_BubbleSort(LIST *list);
void quickSort(LIST *list, long start, long end);
void radixSort(LIST *list);
void heapSort(LIST *list);

#endif
