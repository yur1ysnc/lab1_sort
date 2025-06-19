import matplotlib.pyplot as plt
import re
from collections import defaultdict

# Словарь для хранения данных: алгоритм -> (размер, время)
data = defaultdict(list)

with open("file.txt", "r") as file:
    for line in file:
        match = re.match(r"apartments_(\d+).txt \| (.+?): ([\deE+.-]+)", line.strip())
        if match:
            size = int(match.group(1))
            algorithm = match.group(2)
            time = float(match.group(3))
            data[algorithm].append((size, time))

# Построение графиков
plt.figure(figsize=(10, 6))

for algorithm, values in data.items():
    values.sort()  # сортируем по размеру массива
    sizes = [v[0] for v in values]
    times = [v[1] for v in values]
    plt.plot(sizes, times, marker='o', label=algorithm)

plt.title("Сравнение времени сортировки (log)")
plt.xlabel("Размер массива")
plt.ylabel("Время выполнения (сек)")
plt.yscale('log')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()