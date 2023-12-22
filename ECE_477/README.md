This folder contains an archive of the ECE 47700 (Senior Design) course project at purdue, under professor Walter in Fall 2023.

The course project was the development of an Embedded Systems project in a 4 person team that fufilled certain requirements. The final product/prototype had to be on a PCB, have a microcontroller, have at least 4 custom hardware interfaces/components, and at least one custom software component. The team was myself, Gabriel Wang, Giang Nguyen, and Lee Dongeun. I was mostly responsible for firmware/software, with some assistance in PCB design.

A description of the poject:
In light of the growing utilization of shared spaces and the challenges they pose in terms of occupancy management, the Smart Seating System effectively tackles the issue by tracking seating in common spaces, and reporting that information to visitors in a convenient way. It consists of three major components: the Control Unit, Web Server, and Phone App. Every seat in a public space can be equipped with a dedicated Control Unit, enabling real-time tracking. The Control Unit houses an ESP32 microcontroller, 3.7v li-ion battery supply, 3.3v Buck-Boost, and wireless connection (BLE/WIFI), along with supporting circuitry. By connecting to Force, and Temperature sensors the control unit collects data regarding seat occupancy. Its responsibility is to process the sensor data and send it to the Web Server, which receives data from all Control Units and employs intelligent analysis to determine seat occupancy. The Web Server will exist on a standard PC and be wall-powered. For users, the Phone App provides a user-friendly interface to access seating information remotely. By connecting to the Web Server, the app retrieves real-time occupancy data and statistics, empowering visitors to make informed decisions about seating availability, especially during peak periods.

Project video link: https://www.youtube.com/watch?v=54trdqOZMno

The Documents folder contains the general documentation and presentations of the project as required by the course.
The Electrical folder contains documenation relevant to PCB design, and a folder with .json schematic and PCB files. Import them into EasyEDA for viewing/editing.
The Mechanical folder contains documenation relevant to the packaging, and a folder containing images of packaging internals.
The Software folder contains documenation relevant to software development, and a folder containing all code for the project. A README is present there for further details.
