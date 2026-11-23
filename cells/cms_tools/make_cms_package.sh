#!/bin/bash
# Rebuilds cms_upload/ from the TPS task. Run `tps gen` first.
set -e
T="$(cd "$(dirname "$0")/.." && pwd)"; cd "$T"
O=cms_upload
rm -rf "$O"; mkdir -p "$O/attachments"
statement/build_pdf.sh
cp statement/statement.pdf statement/statement-fa.pdf "$O/"
(cd tests && zip -q -X -9 "$T/$O/tests.zip" *.in *.out)
for i in 1 2 3; do
  cp "tests/00-0$i.in" "$O/attachments/sample-0$i.in"
  cp "tests/00-0$i.out" "$O/attachments/sample-0$i.out"
done
cp cms_tools/score_type_params.json "$O/score_type.txt"
cp cms_tools/task_settings.txt "$O/task_settings.txt"
python3 cms_tools/verify_score_type.py "$O/tests.zip" "$O/score_type.txt" tests/mapping subtasks.json
echo "tests in zip: $(unzip -l "$O/tests.zip" | grep -c '\.in$')"
ls -la "$O" "$O/attachments"
