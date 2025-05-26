#include "csdl.h"
#include <math.h>

/*
To Compile:

This is the correct command lol
gcc -O2 -dynamiclib -o hyperdistort.dylib hyperdistort.c -DUSE_DOUBLE -I/Library/Frameworks/CsoundLib64.framework/Versions/6.0/Headers -arch x86_64

*/
/*
Might need to manually define pi
const float pi = 3.141592653589793;
*/
// implement tanh as a table lookup instead of calling tanh every sample
// try macros instead of redefining table values over and over
/*
Hyperbolic Tangent Waveshaping Oscillator sourced from:
Lazzarini, V. & Timoney, J.
 "New Perspectives on Distortion Synthesis for Virtual Analog Oscillators", 
 Computer music journal, vol. 34, no. 1, 2010, pp. 28-40.

*/
#define tanh_table_size 2048
#define tanh_min -1.0
#define tanh_max 1.0

static MYFLT tanh_Table[tanh_table_size];

void generate_tanh_table(){
    for(int i = 0; i < tanh_table_size; i++){
        MYFLT jenerate = tanh_min + (i * (tanh_max - tanh_min) / (tanh_table_size - 1));
        tanh_Table[i] = tanh(jenerate);
    }
}

static MYFLT compute_tanh(MYFLT *ain){
    if (*ain <= tanh_min) return tanh_Table[0];
    if (*ain >= tanh_max) return tanh_Table[tanh_table_size - 1];

    MYFLT base_index = ((*ain - tanh_min) / (tanh_max - tanh_min)) * (tanh_table_size - 1);
    int index = (int)base_index;
    MYFLT fracture = base_index = index;
    return tanh_Table[index] * (1.0 - fracture) + tanh_Table[index + 1] * fracture;

}


// DATA
typedef struct _hyperdistort{
OPDS h;
MYFLT *out;
MYFLT *in1, *in2;
MYFLT phase;
} hyperdistort;

// INITIALIZE 

int hyperdistort_init(CSOUND *csound, hyperdistort *p){
    p->phase = 0.5;
    generate_tanh_table(); 

return OK;
}


// PROCESS

int hyperdistort_process_audio(CSOUND *csound, hyperdistort *p){

int inNumSamples = CS_KSMPS;
MYFLT *aout = p->out;
MYFLT *ain = p->in1;
MYFLT phase = *p->in2;

MYFLT sr = csound->GetSr(csound);


for(int i = 0; i < inNumSamples; i++){
    
    
    float shapedwave = compute_tanh(ain);
    // apply ring modulation with cosine to shape signal
    float ringmodder = shapedwave * cos(phase);

    aout[i] = ringmodder;
   

}

return OK;
}

// REGISTER

static OENTRY localops[] = {
{ "hyperdistort", sizeof(hyperdistort), 0, 7, "a", "ai",(SUBR) hyperdistort_init,
(SUBR) hyperdistort_process_audio }
};


LINKAGE