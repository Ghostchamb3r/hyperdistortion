<CsoundSynthesizer>
<CsOptions>
-odac --opcode-lib=hyperdistort.dylib

</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 64
nchnls = 1
0dbfs = 1

;basic implementation of BlitB3
instr 1
iphase = 0.6
kcps cpsmidib
kamp = 0.7
asig vco2 kamp, kcps
outs asig*0.3

endin



</CsInstruments>
<CsScore>

</CsScore>
</CsoundSynthesizer>






















































<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="background">
  <r>240</r>
  <g>240</g>
  <b>240</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
