#!/bin/bash
# Builds editorial-fa.pdf from editorial-fa.md (needs python3, pandoc, Playwright/Chromium).
set -e
cd "$(dirname "$0")"
python3 figures.py > /dev/null
pandoc editorial-fa.md -s --mathml --highlight-style=breezedark -V lang=fa -V dir=rtl -c style.css -o editorial-fa.html
sed -i 's#<math #<bdi dir="ltr"><math dir="ltr" #g; s#</math>#</math></bdi>#g' editorial-fa.html
node -e '
const {chromium}=require("playwright");
(async()=>{const b=await chromium.launch();const p=await b.newPage();
await p.goto("file://"+process.cwd()+"/editorial-fa.html");await p.evaluate(()=>document.fonts.ready);
await p.pdf({path:"editorial-fa.pdf",format:"A4",margin:{top:"16mm",bottom:"18mm",left:"16mm",right:"16mm"},printBackground:true,
 displayHeaderFooter:true,headerTemplate:"<span></span>",
 footerTemplate:"<div style=\"width:100%;text-align:center;font-size:9px;color:#888\"><span class=\"pageNumber\"></span> / <span class=\"totalPages\"></span></div>"});
await b.close();})();'
rm -f editorial-fa.html
