INSERT INTO Airport VALUES
('PEK', 'Beijing Capital International Airport', 'Beijing', '4F'),
('PVG', 'Shanghai Pudong International Airport', 'Shanghai', '4F');

INSERT INTO Airline VALUES
('CA', 'Air China', '010-95583'),
('MU', 'China Eastern', '021-95530');

INSERT INTO Flight VALUES
('CA1234', 'Boeing737', '2024-04-10 08:00:00', '2024-04-10 10:30:00', 'PEK', 'PVG', 'CA'),
('MU5678', 'AirbusA320', '2024-04-10 09:00:00', '2024-04-10 11:45:00', 'PVG', 'PEK', 'MU');

INSERT INTO Passenger VALUES
('110101199001011234', 'Zhangsan', 30, '13800138000'),
('110101199002022345', 'Lisi', 28, '13900139000');

INSERT INTO Ticket (flight_number, id_card, seat_number, gate, boarding_time, cabin_seat) VALUES
('CA1234', '110101199001011234', '12A', 'B12', '2024-04-10 07:20:00', 'Y'),
('MU5678', '110101199002022345', '14C', 'A05', '2024-04-10 08:30:00', 'C');

INSERT INTO Orderinfo (id_card, moneys, payment) VALUES
('110101199001011234', 1250.50, 1),
('110101199002022345', 3150.00, 0);

