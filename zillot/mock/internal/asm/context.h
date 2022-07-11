#ifndef ZILLOT_MOCK_ASM_CONTEXT_H
#define ZILLOT_MOCK_ASM_CONTEXT_H

#include <ucontext.h>
#include <igris/compiler.h>

struct context 
{
	struct ucontext_t uc;
};

__BEGIN_DECLS
void set_anchor_context(struct ucontext_t * uc);
__END_DECLS

#endif