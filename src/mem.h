#ifndef MEM_H
#define MEM_H

#include "widget.h"

/* Free every alloca'd memory, surface and font */
void
minegui_clean_root(struct minegui_root *root);

#endif /* MEM_H */
