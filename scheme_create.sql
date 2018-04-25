--- Vitalii Stadnyk
--- Senior Capstone Project
--- Smart Waste Monitoring System
--- Creating Database for the project
--- April 25th, 2018 

drop table if exists readings cascade;

create table readings(
  data float,
  time_val time
);