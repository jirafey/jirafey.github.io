const express = require('express');
const fs = require('fs');
const path = require('path');

const app = express();
const port = 3000;

app.use(express.static('public'));

app.get('/', (req, res) => {
    const currentPath = ''; // Initial path is empty
    const files = getFiles('./public');
    res.render('index.ejs', { files, currentPath });
});

app.get('/:path(*)', (req, res) => {
    const currentPath = req.params.path || '';
    const folderPath = path.join('./public', currentPath);
    const files = getFiles(folderPath);
    res.render('index.ejs', { files, currentPath });
});

function getFiles(folderPath) {
    try {
        const resolvedPath = path.resolve(folderPath);
        const items = fs.readdirSync(resolvedPath);
        return items.map(item => {
            const fullItemPath = path.join(resolvedPath, item);
            return {
                name: item,
                isDirectory: fs.statSync(fullItemPath).isDirectory()
            };
        });
    } catch (error) {
        console.error(`Error reading directory: ${folderPath}`, error);
        return [];
    }
}

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});

