#include "ringbuf.h"
#include <assert.h>

// a ring buffer
// a simple copy of kfifo (removing usage of typeof, which is not available in ANSI C )
// by liigo, 20220224.

void* memcpy(void *dest, const void *src, size_t bytes);

// https://blog.csdn.net/dreamispossible/article/details/91162847
static unsigned int rounddown_pow_of_two(unsigned int n) {
	n|=n>>1; n|=n>>2; n|=n>>4; n|=n>>8; n|=n>>16;
	return (n+1) >> 1;
}

void ringbuf_init(struct ringbuf_t *self, unsigned int item_size, void *buf, unsigned int bufsize) {
    self->data = buf;
    self->esize = item_size;
    self->mask = rounddown_pow_of_two(bufsize / item_size) - 1;
    self->in = self->out = 0;
}

// item count in buf
unsigned int ringbuf_len(struct ringbuf_t *self) {
    return self->in - self->out;
};

// max item count in buf
unsigned int ringbuf_cap(struct ringbuf_t *self) {
    return self->mask + 1;
};

// avail item count
unsigned int ringbuf_avail(struct ringbuf_t *self) {
    return ringbuf_cap(self) - ringbuf_len(self);
};

int ringbuf_is_full(struct ringbuf_t *self) {
    return ringbuf_len(self) > self->mask;
};

int ringbuf_is_empty(struct ringbuf_t *self) {
    return self->in == self->out;
};

#define mymin(a, b) ((a)<(b)?(a):(b))

static void ringbuf_copy_in(struct ringbuf_t *self, const void *src, unsigned int len, unsigned int off) {
	unsigned int size = self->mask + 1;
	unsigned int esize = self->esize;
	unsigned int l;

	off &= self->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		len *= esize;
	}
	l = mymin(len, size - off);

	memcpy(self->data + off, src, l);
	memcpy(self->data, (const unsigned char*)src + l, len - l);
}

unsigned int ringbuf_in(struct ringbuf_t *self, const void *buf, unsigned int item_count) {
    unsigned int avail = ringbuf_avail(self);
    if (item_count > avail)
        item_count = avail;
    
    ringbuf_copy_in(self, buf, item_count, self->in);
    
    self->in += item_count;
    return item_count;
}

static void ringbuf_copy_out(struct ringbuf_t *self, void *dst, unsigned int len, unsigned int off) {
	unsigned int size = self->mask + 1;
	unsigned int esize = self->esize;
	unsigned int l;

	off &= self->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		len *= esize;
	}
	l = mymin(len, size - off);

	memcpy(dst, self->data + off, l);
	memcpy((unsigned char*)dst + l, self->data, len - l);
}

unsigned int ringbuf_out_peek(struct ringbuf_t *self, void *buf, unsigned int len) {
	unsigned int l;
	l = self->in - self->out;
	if (len > l)
		len = l;
	ringbuf_copy_out(self, buf, len, self->out);
	return len;
}

unsigned int ringbuf_out(struct ringbuf_t *self, void *buf, unsigned int item_count) {
    item_count = ringbuf_out_peek(self, buf, item_count);
    self->out += item_count;
    return item_count;
}
