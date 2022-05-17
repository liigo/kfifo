#ifndef RINGBUF_H
#define RINGBUF_H

struct ringbuf_t {
    unsigned char *data;
    unsigned int in, out, mask, esize;
};

#ifdef __cplusplus
extern "C" {
#endif

void ringbuf_init(struct ringbuf_t *self, unsigned int item_size, void *buf, unsigned int bufsize);

// item count in buf
unsigned int ringbuf_len(struct ringbuf_t *self);

// max item count in buf
unsigned int ringbuf_cap(struct ringbuf_t *self);

// avail item count
unsigned int ringbuf_avail(struct ringbuf_t *self);

int ringbuf_is_full(struct ringbuf_t *self);
int ringbuf_is_empty(struct ringbuf_t *self);

unsigned int ringbuf_in(struct ringbuf_t *self, const void *buf, unsigned int item_count);
unsigned int ringbuf_out(struct ringbuf_t *self, void *buf, unsigned int item_count);
unsigned int ringbuf_out_peek(struct ringbuf_t *self, void *buf, unsigned int len);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // RINGBUF_H
