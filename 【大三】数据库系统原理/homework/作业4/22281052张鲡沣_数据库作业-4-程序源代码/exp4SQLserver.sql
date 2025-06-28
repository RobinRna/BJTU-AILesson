CREATE DATABASE airlinedb;
GO
USE airlinedb;
GO

CREATE TABLE Airport
(
    airport_code VARCHAR(10) PRIMARY KEY,
    airport_name VARCHAR(100) NOT NULL,
    city VARCHAR(50) NOT NULL,
    flight_zone VARCHAR(10) NOT NULL
);
GO

CREATE TABLE Airline
(
    airline_code VARCHAR(10) PRIMARY KEY,
    airline_name VARCHAR(100) NOT NULL,
    contact_info VARCHAR(100)
);
GO

CREATE TABLE Flight
(
    flight_number VARCHAR(20) PRIMARY KEY,
    air_model VARCHAR(50) NOT NULL,
    departure_time DATETIME NOT NULL,
    arrival_time DATETIME NOT NULL,
    departure_airport VARCHAR(10) NOT NULL,
    arrival_airport VARCHAR(10) NOT NULL,
    airline_code VARCHAR(10) NOT NULL,
    FOREIGN KEY (departure_airport) REFERENCES Airport (airport_code),
    FOREIGN KEY (arrival_airport) REFERENCES Airport (airport_code),
    FOREIGN KEY (airline_code) REFERENCES Airline (airline_code)
);
GO

CREATE TABLE Passenger
(
    id_card VARCHAR(20) PRIMARY KEY,
    passname VARCHAR(50) NOT NULL,
    age INT NOT NULL,
    phone VARCHAR(100),
    CONSTRAINT chk_age CHECK (age >= 0 AND age < 120)
);
GO

CREATE TABLE Ticket
(
    ticket_id INT IDENTITY(1,1) PRIMARY KEY,
    flight_number VARCHAR(20) NOT NULL,
    id_card VARCHAR(20) NOT NULL,
    seat_number VARCHAR(10) NOT NULL,
    gate VARCHAR(10),
    boarding_time DATETIME NOT NULL,
    cabin_seat VARCHAR(10),
    FOREIGN KEY (flight_number) REFERENCES Flight (flight_number),
    FOREIGN KEY (id_card) REFERENCES Passenger (id_card)
);
GO

CREATE TABLE Orderinfo
(
    order_id INT IDENTITY(1,1) PRIMARY KEY,
    id_card VARCHAR(20) NOT NULL,
    moneys DECIMAL(10, 2) NOT NULL,
    payment INT NOT NULL,
    CONSTRAINT chk_payment CHECK (payment IN (0, 1)),
    FOREIGN KEY (id_card) REFERENCES Passenger(id_card)
);
GO

CREATE VIEW Flightsum
AS
    SELECT flight_number, departure_time, arrival_time,
        (SELECT airport_code
        FROM Airport
        WHERE Airport.airport_code = Flight.departure_airport) AS departure_airport_name,
        (SELECT city
        FROM Airport
        WHERE Airport.airport_code = Flight.departure_airport) AS departure_city,
        (SELECT airport_code
        FROM Airport
        WHERE Airport.airport_code = Flight.arrival_airport) AS arrival_airport_name,
        (SELECT city
        FROM Airport
        WHERE Airport.airport_code = Flight.arrival_airport) AS arrival_city
    FROM Flight;
GO

CREATE VIEW Passhistoryfli
AS
    SELECT id_card, passname,
        (SELECT flight_number
        FROM Ticket
        WHERE Ticket.id_card = Passenger.id_card) AS flight_number,
        (SELECT departure_time
        FROM Flight
        WHERE Flight.flight_number = (SELECT flight_number
            FROM Ticket
            WHERE Ticket.id_card = Passenger.id_card) AND departure_time <= GETDATE()) AS departure_time,
        (SELECT arrival_time
        FROM Flight
        WHERE Flight.flight_number = (SELECT flight_number
            FROM Ticket
            WHERE Ticket.id_card = Passenger.id_card) AND departure_time <= GETDATE()) AS arrival_time
    FROM Passenger;
GO

CREATE VIEW Passfeturefli
AS
    SELECT id_card, passname,
        (SELECT flight_number
        FROM Ticket
        WHERE Ticket.id_card = Passenger.id_card) AS flight_number,
        (SELECT departure_time
        FROM Flight
        WHERE Flight.flight_number = (SELECT flight_number
            FROM Ticket
            WHERE Ticket.id_card = Passenger.id_card) AND departure_time > GETDATE()) AS departure_time,
        (SELECT arrival_time
        FROM Flight
        WHERE Flight.flight_number = (SELECT flight_number
            FROM Ticket
            WHERE Ticket.id_card = Passenger.id_card) AND departure_time > GETDATE()) AS arrival_time,
        (SELECT airline_name
        FROM Airline
        WHERE Airline.airline_code = (SELECT airline_code
        FROM Flight
        WHERE Flight.flight_number = (SELECT flight_number
        FROM Ticket
        WHERE Ticket.id_card = Passenger.id_card))) AS airline_name
    FROM Passenger;
GO

CREATE VIEW UserInfo
AS
    SELECT id_card, passname, age, phone
    FROM Passenger;
GO

CREATE VIEW FlightTime
AS
    SELECT flight_number, departure_time, arrival_time,
        DATEDIFF(MINUTE, departure_time, arrival_time) AS flight_time
    FROM Flight;
GO

CREATE VIEW Airlineflicount
AS
    SELECT airline_code, COUNT(*) AS flight_count
    FROM Flight
    GROUP BY airline_code;
GO
