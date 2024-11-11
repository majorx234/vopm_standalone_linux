#include <jack/types.h>
#include <jack/ringbuffer.h>
#include <jack/jack.h>

typedef struct JackStuff{
  jack_port_t* out_port[2];
  jack_ringbuffer_t* ringbuffer[2];
} JackStuff;

int process(jack_nframes_t nframes, void* jack_stuff_raw);
