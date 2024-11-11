#include "jack_process.h"
#include <jack/types.h>
#include <jack/ringbuffer.h>
#include <unistd.h>
#include <jack/jack.h>

int process(jack_nframes_t nframes, void* jack_stuff_raw)
{
  JackStuff* jack_stuff = (JackStuff*)jack_stuff_raw;

  for (size_t ch = 0; ch < 2; ch++){
      float* outputBuffer = (float*)jack_port_get_buffer ( jack_stuff->out_port[ch], nframes);

      if(jack_stuff->ringbuffer[ch]){
        size_t num_bytes = jack_ringbuffer_read_space (jack_stuff->ringbuffer[ch]);
        if(num_bytes >= (nframes* sizeof(float))) {
          jack_ringbuffer_read(jack_stuff->ringbuffer[ch], (char*)outputBuffer, nframes * sizeof(float));
        } else {
          for ( int i = 0; i < (int) nframes; i++){
            outputBuffer[i] = 0.0;
          }
        }
      }
  }
  return 0;
}
