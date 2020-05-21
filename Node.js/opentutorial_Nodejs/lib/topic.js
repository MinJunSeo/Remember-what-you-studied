var db = require('./db.js');
var template = require('./template.js');

exports.home = function(reqyuest, response)
{
    db.query(`SELECT * FROM topic`, function(error, topics)
    {
        if(error) { throw error; }

        var title = 'Welcome';
        var description = 'Hello, Node.js';
        var list = template.list(topics);
        var html = template.HTML(title, list,
            `<h2>${title}</h2>${description}`,
            `<a href = "/create">create</a>`);

        response.writeHead(200);
        response.end(html);
    });
}