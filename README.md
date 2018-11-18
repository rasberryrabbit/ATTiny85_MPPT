# ATTiny85
Solar MPPT circuit.
Fianally working first firmware, but it need more testing.

Coding by Arduino 1.8.7 / ATTinycore.
~Algorithm convert from old MPPT code of mine.~
It implement new simple algorithm that work well with high solar output.
But it have low power output under low solar output condition(stuck in high voltage).
It has less PWM noise at high load.(hopely)
It has 16KHz switching frequency. ~But with 16kHz, Vgs exceed 10V, it is about 20V.~
It works better than old 16f676 or 12f675 due to better FET bootstrap voltage.


11 milli-ohm N-ch logic level FET(BUK9511) used for current sensor. 
It can replace by 11 mili-ohm or higher Rds-on(<40 milli) resistance logic level FET.

Transistor 2N2222A -> BC547 or compatible
Transistor 2N2907A -> BC557 or compatible

L1 100~330uH

LM358N can replace by other pin-compatible regular OP-AMP.

D8-D9 used for 3.6v Reference. Each has about 1.8v voltage drop.

Q1 gate voltage is 3.6v. It's depend on FET specification.

Q1, Q2 can skip heat spreader with low POWER Solar panel. No heat with 10W panel.
