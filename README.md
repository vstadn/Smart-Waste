# Smart-Waste
Senior Capstone Project (Smart Waste Monitoring System)

Demand for provisioning services and civilian infrastructure appeared with an increase of population and its density in urban centers. Waste collection is a very important and at the same time costly operation which prevents a lot of countries from having a complete solid waste collection system. This paper presents the process of developing a cheap waste monitoring system that can notify collection service workers about critical locations. The system consists of physical hardware mounted within a trash can that reports the current fill level of the garbage bin to the web server. The web server stores all values in the database and presents the doughnut chart of current fill level along with graph of historic fill data. The developed system is believed to have a positive impact on efficiency and cost associated with garbage collection. 

app.py 
Web server written in Python to receive and save data from Arduino board. 

database.py
Connecting to the database with Python using Psycopg2

Arduino.ino
Arduino software that takes readings from 2 Ultrasonic sensors and sends it to the web server.


