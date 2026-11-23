#!/bin/bash
# Builds statement.pdf (English) and statement-fa.pdf (Persian) from the markdown sources.
# Needs pandoc + Playwright/Chromium.
set -e
cd "$(dirname "$0")"
build(){ # $1=md $2=css $3=pdf $4=lang $5=dir
  pandoc "$1" -s --mathml -V lang="$4" -V dir="$5" -c "$2" -o "${3%.pdf}.html"
  sed -i 's#<math #<bdi dir="ltr"><math dir="ltr" #g; s#</math>#</math></bdi>#g' "${3%.pdf}.html"
  node -e '
const {chromium}=require("playwright");
(async()=>{const b=await chromium.launch();const p=await b.newPage();
await p.goto("file://"+process.cwd()+"/"+process.argv[1]);await p.evaluate(()=>document.fonts.ready);
await p.pdf({path:process.argv[2],format:"A4",margin:{top:"18mm",bottom:"18mm",left:"18mm",right:"18mm"},printBackground:true});
await b.close();})();' "${3%.pdf}.html" "$3"
  rm -f "${3%.pdf}.html"
}
build statement.md style.css statement.pdf en ltr
build statement-fa.md style-fa.css statement-fa.pdf fa rtl
