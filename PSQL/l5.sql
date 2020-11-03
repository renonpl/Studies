-- Dominik Hawryluk, rfe
-- Zadanie 1
SELECT t.name AS odznaka, COUNT(*) AS liczba
FROM posts p RIGHT JOIN 
(SELECT b.name, b.date, u.id
FROM badges b LEFT JOIN users u ON b.userid = u.id) t ON p.owneruserid = t.id
GROUP BY t.name
ORDER BY liczba DESC;

-- Zadanie 2
CREATE OR REPLACE FUNCTION textmatch(input text) RETURNS SETOF text AS $$
BEGIN
RETURN QUERY
	SELECT match[1] FROM 
	(select regexp_matches(input,'(?:\A|\s|[^\w])(\w{3,})','g') as match) A
	GROUP BY match[1]
	HAVING COUNT(*) > 1;
RETURN;
END;
$$ LANGUAGE plpgsql;



SELECT DISTINCT textmatch(text) AS word FROM comments
ORDER BY word ASC;

-- Zadanie 3
ALTER TABLE posts
ADD FOREIGN KEY (owneruserid) REFERENCES users(id);
 
--b
--Pierwszym spoosobem, byłoby znaleznienie maksymalnego id użytkownika, a następnie stworzenie, dla każdego posta z nullem, nowego użytkownika, z kolejnym id. Zaletą jest tylko zlikwidowanie nulli. Negatywnie odbije się to, na naszej bazie danych użytkowników, ponieważ dostaniemy masę "pustych" użytkowników z jednym postem, których mogło by ciężko odróżniać od osób fizycznych z nowych kontem.
--Drugim rozwiązaniem byłoby stworzenie jednego użytkownika ze specjalnym id, do którego przypisane by zostały wszystkie te posty. Łatwiej, niż w pierszym przypadku, sprawdzimy, czy ten post należy do kogoś. Nie zaśmieca on nam aż tak bazy, ale trza by było pamiętać, że przy jakichkolwiek przeszukiwaniach, prawdopodobnie nie chcemy go uwzględniać np. byłby on najbardziej aktywnym członkiem forum.
--Według mnie najlepiej zostawić pola z wartością null. Łatwiej zadbać o uwzględnianie (lub nie) tych pól w naszych poleceniach niż pamiętać za każdym razem o uwzględnianiu tego specjalnego użytkownika. Tworzenie dodatkowych użytkowników dla każdego "pustego" posta na pewno obniży nam wydajność baz.
