# 
**<br>shipSimulatorInTerminalATOOP-Final-Project</br>**
**my Final project in Advanced Topics in Object-Oriented Programming<br/>**
<br/>
**Description:**<br/>
This project is a time-dependent simulation of ships/ports , implemented using the [Controller-View-Model paradigm](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller).  
<br/>
**Objects:**<br/>
**Port** : an object with a fixed location that contains unlimited fuel reservoirs , it's responsible of unloading, loading, and refueling a Ship. <br/>
**Ship** : an object that can travel between ports; some types of ship such as the freighter can load containers from port and unload containers in port , all ships have a fuel tank of set size and moves in a set speed.<br/>
**Types of ships :** <br/>
    **1) Freighter:**<br/>
    This Freighter main function is to transports containers it move froms port to port loads and unloads cargo accordding to the input provided at each port it fills the fuel        tank and travel to the next port.<br/>
    **2) Patrol_boat:**<br/>
    This Patrol_boat patrols the ports in the simulation, docks in them, once the route is completed ,it returns to the point of origin/departure.<br/>
    **3) Cruiser:**<br/>
    This Cruiser aka pirate attacks and robs cargo ships or attacks patrol ships; It cant dock in ports.  <br/>
The creation of any ship occurs during the simulation.
