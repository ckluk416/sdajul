#ifndef HIDROLISIS_H
#define HIDROLISIS_H

#include "salt.h"
#include "stack.h"
#include "queue.h"
#include "db_ph.h"

void hidrolisis_process(const Salt* salt_list, const char* nama_garam, Stack* history, Queue* q, const KaKbEntry* db, int ndb);

#endif