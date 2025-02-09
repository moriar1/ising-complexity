import matplotlib.pyplot as plt
import numpy as np


def average_data(x, y, num_intervals):
    # Разбиваем данные на интервалы
    intervals = np.linspace(min(x), max(x), num_intervals + 1)

    # Определяем, к какому интервалу принадлежит каждая точка
    indices = np.digitize(x, intervals)

    # Вычисляем средние значения для каждого интервала
    x_avg = [np.mean(x[indices == i]) for i in range(1, len(intervals))]
    y_avg = [np.mean(y[indices == i]) for i in range(1, len(intervals))]

    return np.array(x_avg), np.array(y_avg)


data = np.loadtxt("data.txt")
x = data[:, 0]
y = data[:, 1]


num_intervals = 100
x_avg, y_avg = average_data(x, y, num_intervals)

plt.plot(x_avg, y_avg)
plt.xlabel("Temperature")
plt.ylabel("Complexity")
plt.grid()
plt.show()

deriv = np.gradient(y_avg, x_avg)

# idx0 = np.isclose(x_avg, 2.08).nonzero()[0][0]
# idx1 = np.isclose(x_avg, 2.68).nonzero()[0][0]
# plt.plot(x_avg[idx0:idx1], deriv[idx0:idx1])

plt.plot(x_avg, deriv)
plt.xlabel("Temperature")
plt.ylabel("Derivative of the complexity")
plt.grid()
plt.show()
