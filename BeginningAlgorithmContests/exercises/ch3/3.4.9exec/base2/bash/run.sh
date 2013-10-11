while true; do
./10
./10tob
./bto10
diff 10.outa 10.outb
if [ $? -ne 0 ]; then break; fi
done
