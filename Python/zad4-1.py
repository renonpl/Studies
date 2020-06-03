import timeit

def pierwsze_imperatywnie(n):
    lista = list(range(2, n))
    wynik = []
    for el in lista:
        pierwsza = True
        for i in range (2, el):
            if el%i == 0:
                pierwsza = False
                break
        if pierwsza:
            wynik.append(el)
    return wynik

print(pierwsze_imperatywnie(1000))


def pierwsza(x):
    for i in range (2, x):
        if  x % i == 0:
            return False
    return True

def pierwsze_skladane(n):
    lista = range(2, n)
    wynik = [x for x in lista if pierwsza(x)]
    return wynik

print(pierwsze_skladane(1000))


def pierwsze_funkcyjne(n):
    lista = range(2, n)
    lista = list(filter(pierwsza, lista))
    return lista

print(pierwsze_funkcyjne(1000))


setup = ''
t = timeit.Timer('pierwsze_imperatywnie(100)',globals=globals())
print(t.timeit(number=100))
t = timeit.Timer('pierwsze_skladane(100)',globals=globals())
print(t.timeit(number=100))
t = timeit.Timer('pierwsze_funkcyjne(100)',globals=globals())
print(t.timeit(number=100))