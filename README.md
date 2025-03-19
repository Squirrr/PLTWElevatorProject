<h1>PLTW PoE Control Design Project: Elevator </h1>
<h2>Designed and Programmed By: Abdullah Khaled, Gabriel Garabedian, Brandon Chiou, and Kristian Little </h2>

<h3>Explanation:</h3>
This project was made for our PLTW Principles of Engineering (PoE) class during our VEX V5/Robotics Unit. 
This project asked us to create a machine that completed a specific goal, and we chose to do the elevators. We were tasked with creating an elevator with the following criteria and constraints:

Criteria:
<ul>
<li>Carriage must go to any floor in any order</li>
<li>Display the elevator’s current floor</li>
<li>Each floor must have a way for someone to call the elevator to that floor.</li>
<li>Users, once in the elevator, must be able to choose their desired floor to go to.</li>
<li>Return to ground floor after user-determined period of time</li>
<li>Include a “Maintenance Mode” where the lights blink and all doors open</li>
</ul>
Constraints:
<ul>
<li>Prevent residents from entering elevator shaft</li>
<li>Doors must not interfere with other floors</li>
<li>Order of carriage should not matter</li>
</ul>

<h3>Design</h3>
The CAD for our final design can be found <a href="https://cad.onshape.com/documents/7fc7cdf066143723a8bdc489/w/654f85b88952b507438878c5/e/f4604c28202e600802e5376b?renderMode=0&uiState=67da0cb376fb087c0d7d7448">here</a>
Some design changes we made included (but are not limited to)
<ul>
  <li>Switching servo-operated doors to motors due to limited 3-wire ports</li>
  <li>Added limit switches instead of bumpers to carriage</li>
  <li>Moved floor selector bumper switches to other side of elevator for ease-of-use and wiring ease</li>
  <li>Added battery mount</li>
  <li>Switched rack-and-pinion mount since we did not have that part, which made it slightly less stable</li>
</ul>

<h3>Programming</h3>
For programming, we decided on using one distance sensor and used a P controller to determine the desired velocity of the elevator motor to get to each floor quickly and accurately.
We also struggled with LED logic, so we decided to bypass that in our final design but keep the control logic in case someone else is able to make it work. Our code can be found in the
MachineControlProject.cpp file, but if you decide to use our design/code be sure to configure your motor and three-wire ports or else it will not work (I found this out the hard way!).

<h3>Final Thoughts</h3>
Overall, we felt that this project went quite well. Some things we could have done better include ensuring a more stable support for the rack and pinion and implementing LEDs into
our maintenance mode, but in general there was not much we wanted to improve on.
