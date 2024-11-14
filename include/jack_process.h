#include <jack/types.h>
#include <jack/ringbuffer.h>
#include <jack/jack.h>

typedef struct JackStuff{
  jack_client_t* client;
  jack_port_t* midi_in_port;
  jack_port_t* out_port[2];
  jack_ringbuffer_t* ringbuffer[2];
} JackStuff;

int process(jack_nframes_t nframes, void* jack_stuff_raw);
JackStuff* create_jack_stuff(char* client_name);
void jack_stuff_clear(JackStuff* jack_stuff);
