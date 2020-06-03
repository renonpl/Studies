import timeit

def doskonale_imperatywna(n):
    lista = []
    for i in range(1, n+1):
        suma = 0
        dziel = 1
        while dziel <= i / 2:
            if i % dziel == 0:
                suma += dziel
            dziel += 1
        if i == suma:
            lista.append(i)
    return lista


print(doskonale_imperatywna(1000))


def doskonale_skladana(n):
    lista = range(1,n)
    wynik = [x for x in lista if sum([i for i in range(1, x) if x % i == 0]) == x]
    return wynik

print(doskonale_skladana(1000))


def doskonala(x):
    s = sum([i for i in range(1, x) if x % i == 0])
    return s == x


def doskonale_funkcyjna(n):
    lista = range(1, n)
    return list(filter(doskonala, lista))

print(doskonale_funkcyjna(1000))

setup = ''
t = timeit.Timer('doskonale_imperatywna(1000)',globals=globals())
print(t.timeit(number=10))
t = timeit.Timer('doskonale_skladana(1000)',globals=globals())
print(t.timeit(number=10))
t = timeit.Timer('doskonale_funkcyjna(1000)',globals=globals())
print(t.timeit(number=10))