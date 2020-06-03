
def kompresja(tekst):
    komp = []
    licz = 0
    znak = 0
    for c in tekst:
        if znak == c:
            licz += 1
        else:
            if licz == 1:
                komp.extend(znak)
            else:
                if licz != 0:
                    komp.extend(str(licz)+znak)
            znak = c
            licz = 1
    komp.extend(str(licz)+znak)
    return "".join(komp)




def dekompresja(tekst):
    komp = []
    licz = 0
    for c in tekst:
        if c >= '0' and c <= '9':
            licz = licz * 10 + ord(c) - ord('0')
        else:
            if licz == 0:
                komp.extend(c)
            else:
                while licz > 0:
                    komp.extend(c)
                    licz -= 1
    return "".join(komp)

print(dekompresja("5a6cd"))
print(kompresja("abbcccddddeeeeeffffffz::::????!!((())))))"))
print(dekompresja(kompresja("abbcccddddeeeeeffffffz::::????!!((())))))")))



print(dekompresja(kompresja("aaaaaaaaaaaaaabbbbbbbbcdddd")))