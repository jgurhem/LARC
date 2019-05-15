#!/bin/bash
set -e
#print="-print"
size=7

echo "=== test pmv   ==="
initv $size 111 v.bin
initv $size 111 vs.bin
initm $size $size 222 m.bin
pmv $size m.bin v.bin
check_results -A m.bin -V vs.bin -R v.bin -s $size -b 1 -ff binR -op mv $print


echo "=== test pmm1  ==="
initm $size $size 222 m1.bin
initm $size $size 222 ms.bin
initm $size $size 333 m2.bin
pmm1 $size m1.bin m2.bin
check_results -A ms.bin -B m2.bin -C m1.bin -s $size -b 1 -ff binR -op mm $print


echo "=== test pmm2  ==="
initm $size $size 222 m1.bin
initm $size $size 333 ms.bin
initm $size $size 333 m2.bin
pmm2 $size m1.bin m2.bin
check_results -A m1.bin -B ms.bin -C m2.bin -s $size -b 1 -ff binR -op mm $print


echo "=== test pmm_d ==="
initm $size $size 222 a.bin
initm $size $size 333 b.bin
initm $size $size 444 c.bin
initm $size $size 444 cs.bin
pmm_d $size a.bin b.bin c.bin
check_results -A a.bin -B b.bin -C cs.bin -D c.bin -s $size -b 1 -ff binR -op mm_d $print

echo "=== test pmv_d ==="
initm $size $size 222 a.bin
initv $size 333 b.bin
initv $size 444 c.bin
initv $size 444 cs.bin
pmv_d $size a.bin b.bin c.bin
#check_results -a a.bin -b b.bin -c cs.bin -d c.bin -s $size -b 1 -ff binr -op mv_d $print

echo "=== test inv_gj ==="
initm $size $size 222 m.bin
inv_gj $size m.bin inv.bin
check_results -A m.bin -B inv.bin -s $size -b 1 -ff binR -op invgj $print

rm *.bin
