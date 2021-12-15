#ifndef SEM_H
#define SEM_H

#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

void initialize_semaphores(dane_procesow *dane);

#endif