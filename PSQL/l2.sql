-- Dominik Hawryluk, rfe
-- Zadanie 1

SELECT users.id, displayname, reputation, COUNT(postlinks.postid) as total
FROM users LEFT JOIN posts ON users.id = posts.owneruserid
	LEFT JOIN postlinks ON posts.id = postlinks.postid
WHERE relatedpostid IS NOT null AND linktypeid = 3
GROUP BY users.id, displayname, reputation
HAVING COUNT(postlinks.postid) > 0
ORDER BY total DESC, displayname ASC
LIMIT 20;

-- Zadanie 2

SELECT users.id, displayname, reputation, COUNT(comments.id) as total, AVG(comments.score)
FROM users JOIN badges ON badges.userid = users.id 
	LEFT JOIN posts ON users.id = posts.owneruserid
	LEFT JOIN comments ON posts.id = comments.postid
WHERE badges.name = 'Fanatic'
GROUP BY users.id, displayname, reputation
HAVING COUNT(comments.id) <= 100
ORDER BY total DESC, displayname ASC
LIMIT 20;
-- Zadanie 3
ALTER TABLE users ADD PRIMARY KEY (id);
ALTER TABLE badges ADD FOREIGN KEY (userid) REFERENCES users(id);
ALTER TABLE posts DROP viewcount;
DELETE FROM posts WHERE body IS NULL OR body = '';

-- Zadanie 4

CREATE SEQUENCE comment_id;
SELECT setval('comment_id', max(id))
FROM posts;

INSERT INTO posts(id, posttypeid, parentid, owneruserid, body, creationdate, score)
SELECT nextval('comment_id'), '3', postid, userid, text, creationdate, score
FROM comments;

