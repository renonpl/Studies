def pierwiastek(n):
    suma = 0
    k = 1
    while True:
        suma += 2*k-1
        if suma >= n:
            return k
        k += 1


print(pierwiastek(16))
print(pierwiastek(25))
print(pierwiastek(36))
print(pierwiastek(81))
print(pierwiastek(625))
print(pierwiastek(5))

