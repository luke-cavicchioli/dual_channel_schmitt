# Dual channel Schmitt trigger
Arduino code for a simple Schmitt trigger. Used at the
[K-Rb](https://quantumgases.lens.unifi.it/exp/krb) experiment at LENS for the
stabilization of a dual magneto-optical trap.

## Inputs and outputs
For each channel, there are two inputs and an output: the **reference in** is
the set point, the **signal in** is the signal that we want to stabilize.
There is also a **hist** value that controls the hysteresis of the Schmitt
trigger. The output is a digital output.

When the signal is below reference - hist, the output is turned on, and when it
is above reference + hist, it is turned off; otherwise, the signal remains the
same as before.
