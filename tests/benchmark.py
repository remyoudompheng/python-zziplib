import sys
import time
import zziplib
import traceback
import zipfile

def infiniteloop():
    while True:
        z = zziplib.open("truc.zip")
        entry = z.open("toto.234")
        while True:
            s = entry.read(512)
            if not s:
                break
        entry.close()

        entry = z.open("toto.234")
        while True:
            s = entry.read(512)
            if not s:
                break
        entry.close()

def begin():
    z = zipfile.ZipFile("truc.zip", "w")
    for i in xrange(3000):
        z.writestr("toto.%d" % i, ("toto%d" % i) * 5000, compress_type = zipfile.ZIP_DEFLATED)

def test_bigfile():
    t = time.time()
    for i in xrange(100):
        z = zziplib.open("truc.zip")
        entry = z.open("toto.234")
        s = entry.read(1024)
    print s[:60]

    print (time.time() - t) * 10, " ms per open()"

def test_zipfile():
    t = time.time()
    for i in xrange(100):
        z = zipfile.ZipFile("truc.zip")
        entry = z.open("toto.234")
        s = entry.read(1024)
    print s[:60]

    print (time.time() - t) * 10, " ms per open()"

begin()
test_bigfile()
test_zipfile()
