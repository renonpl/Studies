import random
def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    zdania = tekst.split('.')
    wynik = []
    for z in zdania:
        slowa = z.split()
        for s in slowa:
            if len(s) > dl_slowa:
                slowa.remove(s)
        i = len(slowa)
        while i > liczba_slow:
            r = random.randint(0, i-1)
            slowa.remove(slowa[r])
            i -= 1
        wynik.extend(slowa)
    return " ".join(wynik)


tekst = "Podział peryklinalny inicjałów wrzecionowatych kambium charakteryzuje się ścianą podziałową inicjowaną w płaszczyźnie maksymalnej."
print(uprosc_zdanie(tekst, 10, 5))

tekst2 = "Litwo! Ojczyzno moja! ty jesteś jak zdrowie. Ile cię trzeba cenić, ten tylko się dowie, Kto cię stracił. Dziś piękność twą w całej ozdobie Widzę i opisuję, bo tęsknię po tobie. Panno Święta, co Jasnej bronisz Częstochowy I w Ostrej świecisz Bramie! Ty, co gród zamkowy Nowogródzki ochraniasz z jego wiernym ludem!Jak mnie dziecko do zdrowia powróciłaś cudem."

print(uprosc_zdanie(tekst2, 10, 5))
