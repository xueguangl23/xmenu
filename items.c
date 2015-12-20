#include <stdio.h>
#include <stdlib.h>
#include "items.h"
#include "util.h"

Item *newItem(ItemList *list) {
  Item *item;
  /* We never free anything so pos should never loop. */
  if (list->len == list->cap) {
    list->cap += sizeof(Item) * BUFSIZ;
    if (!(list->item = realloc(list->item, list->cap))) {
      return NULL;
    }
  }
  item = list->item + list->len;
  (list->len)++;
  return item;
}

ItemList ReadStdin(void) {
  ItemList list;
  char *buf = NULL;
  size_t cap = 0;
  size_t len;
  while ((len = getline(&buf, &cap, stdin)) != -1) {
    if (len && buf[len - 1] == '\n') buf[len - 1] = '\0';
    Item *item = newItem(&list);
    if (item == NULL) goto end;
    item->sel = false;
    char *padded = pad(buf);
    item->text = CFStringCreateWithCString(NULL, padded, kCFStringEncodingUTF8);
    free(padded);
  }
end:
  free(buf);
  return list;
}
