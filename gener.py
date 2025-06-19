import random
from random import randint

def generate_apartments(num_records, filename):
    first_names_m = ['Алексей', 'Дмитрий', 'Сергей', 'Николай', 'Иван', 'Андрей', 'Владимир', 'Михаил']
    first_names_f = ['Анна', 'Мария', 'Ольга', 'Елена', 'Татьяна', 'Наталья', 'Ирина', 'Светлана']
    last_names = ['Иванов', 'Петров', 'Сидоров', 'Смирнов', 'Кузнецов', 'Попов', 'Васильев', 'Новиков', 'Фёдоров', 'Морозов', 'Волков', 'Соколов']
    middle_names = ['Алексеевич', 'Дмитриевич', 'Сергеевич', 'Иванович', 'Петрович', 'Анатольевич', 'Николаевич', 'Владимирович', 'Андреевич', 'Михайлович']
    middle_names_f = ['Алексеевна', 'Дмитриевна', 'Сергеевна', 'Ивановна', 'Петровна', 'Анатольевна', 'Николаевна', 'Владимировна', 'Андреевна', 'Михайловна']

    with open(filename, 'w', encoding='utf-8') as f:
        for _ in range(num_records):
            apartment = randint(1, 20)
            area = randint(5, 300)
            rooms = randint(1, 5)
            price = round(random.uniform(20.0, 150.0), 1)
            floor = randint(1, 6)
            
            # Randomly choose gender for name
            if random.random() > 0.5:
                first_name = random.choice(first_names_m)
                middle_name = random.choice(middle_names)
                gender = 'm'
            else:
                first_name = random.choice(first_names_f)
                middle_name = random.choice(middle_names_f)
                gender = 'f'
            
            last_name = random.choice(last_names)
            if gender == 'f' and last_name[-1] not in ['а', 'я']:
                last_name += 'а'
            
            full_name = f"{last_name} {first_name} {middle_name}"
            
            line = f"{apartment},{area},{rooms},{price},{full_name},{floor}\n"
            f.write(line)

# Generate all files
sizes = [100, 1000, 5000, 10000, 20000, 30000, 50000, 70000, 90000, 100000]
for size in sizes:
    generate_apartments(size, f"apartments_{size}.txt")