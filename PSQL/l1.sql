-- Dominik Hawryluk, rfe
-- Zadanie 1
SELECT creationdate
FROM posts
WHERE body LIKE '%Turing%'
ORDER BY creationdate desc;

-- Zadanie 2
SELECT id, title
FROM posts
WHERE title IS NOT null AND
	creationdate > '10.10.2018' AND
	EXTRACT(MONTH FROM creationdate) >= 9 AND
	score >= 9
ORDER BY title;

-- Zadanie 3
SELECT DISTINCT displayname, reputation
FROM posts 
	JOIN users ON posts.owneruserid = users.id
	JOIN comments ON posts.id = comments.postid
WHERE posts.body LIKE '%deterministic%' AND
	comments.text LIKE '%deterministic%'
ORDER BY reputation;

-- Zadanie 4
SELECT DISTINCT displayname
FROM users
	JOIN posts ON users.id =posts.owneruserid
	LEFT JOIN comments ON users.id = comments.userid
WHERE comments.id IS null
ORDER BY displayname limit 10;

