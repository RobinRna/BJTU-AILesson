from faker import Faker
import random
from datetime import datetime, timedelta

faker = Faker(locale='en_US')
random.seed(42)

# 参数设置
num_passengers = 100000
tickets_per_passenger = 2

# ====== 生成机场列表（共20个）======
airport_codes = set()
while len(airport_codes) < 20:
    airport_codes.add(faker.unique.lexify(text='???').upper())
airport_list = [
    (code, f"{faker.city()} International Airport",
     faker.city(), random.choice(['3C', '4D', '4F', '4C']))
    for code in airport_codes
]

# ====== 生成航空公司（共20个）======
airline_codes = set()
while len(airline_codes) < 20:
    airline_codes.add(faker.unique.lexify(text='??').upper())
airline_list = [
    (code, f"{faker.company()} Airlines", faker.phone_number())
    for code in airline_codes
]

# ====== 生成航班（共100个）======
flight_list = []
used_flight_numbers = set()
for _ in range(100):
    airline = random.choice(airline_list)
    while True:
        flight_number = f"{airline[0]}{random.randint(1000, 9999)}"
        if flight_number not in used_flight_numbers:
            used_flight_numbers.add(flight_number)
            break
    model = random.choice(
        ["Boeing737", "AirbusA320", "AirbusA321", "Boeing787", "AirbusA319"])
    departure, arrival = random.sample(airport_list, 2)
    flight_list.append(
        (flight_number, model, departure[0], arrival[0], airline[0]))

# ====== 写入 SQL 文件 ======
with open("exp3_data.sql", "w", encoding="utf-8") as f:
    # Airport
    f.write("-- INSERT INTO Airport\n")
    for a in airport_list:
        f.write(
            f"INSERT INTO Airport VALUES ('{a[0]}', '{a[1]}', '{a[2]}', '{a[3]}');\n")

    # Airline
    f.write("\n-- INSERT INTO Airline\n")
    for a in airline_list:
        f.write(
            f"INSERT INTO Airline VALUES ('{a[0]}', '{a[1]}', '{a[2]}');\n")

    # Flight
    f.write("\n-- INSERT INTO Flight\n")
    for fli in flight_list:
        dep_time = datetime(2024, 4, 10, 8, 0)
        arr_time = dep_time + timedelta(hours=2, minutes=30)
        f.write(f"INSERT INTO Flight VALUES ('{fli[0]}', '{fli[1]}', '{dep_time.strftime('%Y-%m-%d %H:%M:%S')}', "
                f"'{arr_time.strftime('%Y-%m-%d %H:%M:%S')}', '{fli[2]}', '{fli[3]}', '{fli[4]}');\n")

    # Passenger, Ticket, Orderinfo
    f.write("\n-- INSERT INTO Passenger, Ticket, Orderinfo\n")
    for i in range(num_passengers):
        id_card = f"ID{10000000 + i}"
        name = faker.first_name()
        age = random.randint(18, 65)
        phone = faker.phone_number()
        f.write(
            f"INSERT INTO Passenger VALUES ('{id_card}', '{name}', {age}, '{phone}');\n")

        for _ in range(tickets_per_passenger):
            flight = random.choice(flight_list)[0]
            seat = random.choice(["12A", "14C", "15B", "19D", "20E"])
            gate = random.choice(["A01", "B05", "C12", "D03"])
            boarding_time = faker.date_time_between(
                start_date=datetime(2024, 4, 10, 6, 0),
                end_date=datetime(2024, 4, 10, 9, 0)
            ).strftime('%Y-%m-%d %H:%M:%S')
            cabin = random.choice(["Y", "C"])
            f.write(f"INSERT INTO Ticket (flight_number, id_card, seat_number, gate, boarding_time, cabin_seat) "
                    f"VALUES ('{flight}', '{id_card}', '{seat}', '{gate}', '{boarding_time}', '{cabin}');\n")

            amount = round(random.uniform(300.0, 1500.0), 2)
            payment = random.choice([0, 1])
            f.write(
                f"INSERT INTO Orderinfo (id_card, moneys, payment) VALUES ('{id_card}', {amount}, {payment});\n")

print("SQL generation complete: exp3_data.sql")
