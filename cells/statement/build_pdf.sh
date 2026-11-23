#!/bin/bash
# Builds statement.pdf from statement.md (needs pandoc + Playwright/Chromium).
set -e
cd "$(dirname "$0")"
pandoc statement.md -s --mathml --metadata pagetitle="Cells Blocking" -c style.css -o statement.html
node -e '
const {chromium}=require("playwright");
(async()=>{const b=await chromium.launch();const p=await b.newPage();
await p.goto("file://"+process.cwd()+"/statement.html");
await p.pdf({path:"statement.pdf",format:"A4",margin:{top:"18mm",bottom:"18mm",left:"18mm",right:"18mm"},printBackground:true});
await b.close();})();'
rm -f statement.html
