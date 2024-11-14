#include "jack_process.h"
#include <jack/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <jack/midiport.h>

int process(jack_nframes_t nframes, void* jack_stuff_raw)
{
  JackStuff* jack_stuff = (JackStuff*)jack_stuff_raw;
  // midi_in event handling:
  void* jack_midi_buffer =  jack_port_get_buffer ( jack_stuff->midi_in_port, nframes);
  int event_count = jack_midi_get_event_count(jack_midi_buffer);
 
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

JackStuff* create_jack_stuff(char* client_name){
  JackStuff* jack_stuff = (JackStuff*)malloc(sizeof(JackStuff));

  jack_stuff->midi_in_port = NULL;
  jack_stuff->out_port[0] = NULL;
  jack_stuff->ringbuffer[0] = NULL;
  jack_stuff->out_port[1] = NULL;
  jack_stuff->ringbuffer[1] = NULL;
  jack_stuff->client = NULL;

  jack_stuff->client = jack_client_open (client_name,
                                         JackNullOption,
                                         0,
                                         0 );
  const size_t ringbuffer_size = 4096 * sizeof(float);
    jack_stuff->midi_in_port  = jack_port_register (jack_stuff->client,
                                                    "midi_input",
                                                    JACK_DEFAULT_MIDI_TYPE,
                                                    JackPortIsInput, 0);
  for (size_t ch = 0; ch < 2; ch++){
    jack_stuff->out_port[ch] = jack_port_register (jack_stuff->client,
                                                   "output",
                                                   JACK_DEFAULT_AUDIO_TYPE,
                                                   JackPortIsOutput,
                                                   0 );
    jack_stuff->ringbuffer[ch] = jack_ringbuffer_create(ringbuffer_size);
  }

  jack_set_process_callback(jack_stuff->client, process, (void*)jack_stuff);
  //client.set_sample_rate(48000);
  jack_activate(jack_stuff->client);
  return jack_stuff;
}

void jack_stuff_clear(JackStuff* jack_stuff) {
  jack_deactivate(jack_stuff->client);
  jack_client_close(jack_stuff->client);
  jack_ringbuffer_free(jack_stuff->ringbuffer[0]);
  jack_ringbuffer_free(jack_stuff->ringbuffer[1]);
  free(jack_stuff);
}
