a = ?;

f1 = 0;
f2 = 1;
c = 0;
i = 0;
while (c < a) {
	i = i + 1;
	c = f2;
	f2 = f1 + f2;
	f1 = c;
}

if (c == a) {
	print i;
}
if (c != a) {
    print 0;
}

