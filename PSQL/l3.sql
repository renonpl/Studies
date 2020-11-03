-- Dominik Hawryluk, rfe
-- Zadanie 1
CREATE VIEW ranking(
displayname, liczba_odpowiedzi) AS
SELECT displayname, liczba_odpowiedzi
FROM users JOIN 
	(SELECT p2.owneruserid, COUNT(p1.id) as liczba_odpowiedzi
	FROM posts p1 JOIN posts p2 ON p1.acceptedanswerid = p2.id
	GROUP BY p2.owneruserid) as temp ON id = owneruserid
ORDER BY liczba_odpowiedzi DESC, displayname;

-- Zadanie 2
WITH enlightups AS (SELECT users.id, upvotes
		FROM users LEFT JOIN badges ON users.id = badges.userid
		WHERE badges.name = 'Enlightened'
		GROUP BY users.id, upvotes),
	comms AS (SELECT comments.userid, COUNT(posts.id)
		 FROM comments JOIN posts ON comments.postid = posts.id
		WHERE EXTRACT(YEAR FROM posts.creationdate) = '2020'
		GROUP BY comments.userid
		HAVING COUNT(posts.id) > 1)

SELECT id, displayname, reputation
FROM users u
WHERE NOT EXISTS(SELECT * FROM badges
		WHERE badges.name = 'Enlightened' AND u.id = badges.userid)
	AND upvotes > (SELECT AVG(upvotes) FROM enlightups)
	AND u.id IN (SELECT userid FROM comms)
ORDER BY creationdate ASC;


-- Zadanie 3
WITH recposts AS(SELECT users.id, displayname, posts.id AS pid
		FROM users JOIN posts ON users.id = posts.owneruserid
		WHERE body LIKE '%recurrence%')

(SELECT users.id, displayname
FROM users JOIN comments ON users.id = comments.userid
WHERE comments.postid IN (SELECT pid FROM recposts))
UNION
(SELECT id, displayname FROM recposts);

