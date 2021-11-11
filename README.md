# ATOOP-Final-Project
**Final project in Advanced Topics in Object-Oriented Programming<br/>**
<br/>
**Description:**<br/>
This project deals with the time-dependent simulation of vessels, and is designed to use the [Controller-View-Model paradigm](https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller).  
<br/>
**Objects:**<br/>
**Port** : This is a simulation object with a fixed location and fuel reservoirs (without storage limit), and it is the responsibility of unloading, loading, and refueling a vessel. <br/>
**Ship** : This is an object that can travel between ports and can load na unload containers in every port , every ship has a fuel tank and moves in a specific speed.<br/>
**Types of ships :** <br/>
**1) Freighter:**<br/>
This vessel transports containers (from port to port, according to the loading and unloading orders, and cruises at a given speed from point to point subject to regular fuel consumption. Fill its cargo capacity to the maximum number of containers and aim to fill the fuel tank (depending on the existing fuel inventory in the port.) The creation of the ship occurs during the simulation.<br/>
**2) Patrol_boat:**<br/>
This vessel patrols between the various ports in the maritime space, anchors in them, and completes a return route to the point of departure. The creation of the ship occurs during the simulation.<br/>
**3) Cruiser:**<br/>
This vessel attacks and robs cargo ships or attacks patrol ships; It is not allowed to dock in ports. The creation of the ship occurs during the simulation. <br/>
**Model** : This is a single object which is required to be defined in the Singleton format; It is his responsibility to monitor the world of simulation in all its aspects, from time management to object storage. In particular, it must hold using pointers all the vessels and ports participating in the simulation, and provide access services to them. In addition, the object is responsible for providing update services for the view object.<br/>
**View** : This object has one responsibility and is to display the world map using ascii-based graphics.Each object is represented on the map by the first two characters of its name. The information update is based on interaction with the model.<br/>
**Controller** : This is a single object whose responsibility is to manage the interaction with the user, and to route the inputs obtained for the model. This warranty also includes the management of errors in the user inputs. <br/><br/>
*All the commands are defined in the file src/Controller.cpp (void Controller::run())*
<br/>
*& in the folder console there is some examples of the i/o*
