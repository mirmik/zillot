#ifndef ZILLOT_CONTEXT_H
#define ZILLOT_CONTEXT_H

#include <igris/compiler.h>
#include <stdint.h>

#if !__NOARCH
#include <asm/context.h>
#endif

struct context;

__BEGIN_DECLS

void context_switch(struct context *save, struct context *load);
void context_init(struct context *ctx,
                  uintptr_t stck,
                  void (*func)(void *),
                  void *param,
                  uint8_t irqen);

void context_save(struct context *next);
void context_load(struct context *next);
void context_save_and_displace(struct context *cntxt);

void context_dprint(struct context *cntxt);
void __context_drop__();

__END_DECLS

#endif
