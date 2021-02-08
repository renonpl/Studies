var http=require('http')
var server=http.createServer((function(request,response)
{
	response.setHeader('Content-Disposition','attachment');
	console.log("Header is set");
	response.writeHead(200,
	{"Content-Type" : "text/plain",});
	response.end("Hello World\n");
}));
server.listen(3000);