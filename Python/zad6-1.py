import bs4
import requests
import re

def searchPython(bs):
    zdania = bs.get_text().split('\n')
    wynik = list()
    pattern = re.compile(".*Python.*")
    for s in zdania:
        if  pattern.match(s):
            wynik.append(s)
    return wynik

def crawl(start_page, distance, action):
    wynik = {}
    sess = requests.Session()
    sess.allow_redirects = False
    def aux(url, distance):
        response = requests.get(url,allow_redirects = False)
        bs = bs4.BeautifulSoup(response.text, 'html.parser')
        #  print(bs)
        if distance > 0:
            for url in bs.find_all('a', attrs={'href': re.compile("^https?://")}):
                # print(url['href'])
                adres = url['href']
                if adres in wynik:
                    continue
                aux(adres, distance - 1)

        if url not in wynik:
             s = action(bs)
             wynik[url] = s
        return wynik
    return aux(start_page, distance)


p = crawl("https://docs.python.org/3/index.html",3,searchPython)

for k, v in p.items():
    print(k)
    print(v)