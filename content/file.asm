brk	;00
srp #00h	;0100
add r0, r1	;0201
add r0, @r2	;0302
add 04h, 03h	;040304
add 06h, @05h	;050506
add 07h, #08h	;060708
add @09h, #0Ah	;07090A
addx C0Dh, 0B0h	;080B0C0D
addx F10h, #0Eh	;090E0F10
djnz r0, 17	;0A11
jr F, 18	;0B12
ld r0, #13h	;0C13
jp F, 140Eh	;0D140E
nop	;0F
rlc 15h	;1015
rlc @16h	;1116
adc r1, r7	;1217
adc r1, @r8	;1318
adc 1Ah, 19h	;14191A
adc 1Ch, @1Bh	;151B1C
adc 1Dh, #1Eh	;161D1E
adc @1Fh, #20h	;171F20
adcx 223h, 212h	;18212223
adcx 526h, #24h	;19242526
djnz r1, 39	;1A27
jr LT, 40	;1B28
ld r1, #29h	;1C29
jp LT, 2A1Eh	;1D2A1E
inc 2Bh	;202B
inc @2Ch	;212C
sub r2, r13	;222D
sub r2, @r14	;232E
sub 30h, 2Fh	;242F30
sub 32h, @31h	;253132
sub 33h, #34h	;263334
sub @35h, #36h	;273536
subx 839h, 373h	;28373839
subx B3Ch, #3Ah	;293A3B3C
djnz r2, 61	;2A3D
jr LE, 62	;2B3E
ld r2, #3Fh	;2C3F
jp LE, 402Eh	;2D402E
atm	;2F
dec 41h	;3041
dec @42h	;3142
sbc r4, r3	;3243
sbc r4, @r4	;3344
sbc 46h, 45h	;344546
sbc 48h, @47h	;354748
sbc 49h, #4Ah	;36494A
sbc @4Bh, #4Ch	;374B4C
sbcx E4Fh, 4D4h	;384D4E4F
sbcx 152h, #50h	;39505152
djnz r3, 83	;3A53
jr ULE, 84	;3B54
ld r3, #55h	;3C55
jp ULE, 563Eh	;3D563E
da 57h	;4057
da @58h	;4158
or r5, r9	;4259
or r5, @r10	;435A
or 5Ch, 5Bh	;445B5C
or 5Eh, @5Dh	;455D5E
or 5Fh, #60h	;465F60
or @61h, #62h	;476162
orx 465h, 636h	;48636465
orx 768h, #66h	;49666768
djnz r4, 105	;4A69
jr OV, 106	;4B6A
ld r4, #6Bh	;4C6B
jp OV, 6C4Eh	;4D6C4E
pop 6Dh	;506D
pop @6Eh	;516E
and r6, r15	;526F
and r7, @r0	;5370
and 72h, 71h	;547172
and 74h, @73h	;557374
and 75h, #76h	;567576
and @77h, #78h	;577778
andx A7Bh, 797h	;58797A7B
andx D7Eh, #7Ch	;597C7D7E
djnz r5, 127	;5A7F
jr MI, -128	;5B80
ld r5, #81h	;5C81
jp MI, 825Eh	;5D825E
wdt	;5F
com 83h	;6083
com @84h	;6184
tcm r8, r5	;6285
tcm r8, @r6	;6386
tcm 88h, 87h	;648788
tcm 8Ah, @89h	;65898A
tcm 8Bh, #8Ch	;668B8C
tcm @8Dh, #8Eh	;678D8E
tcmx 091h, 8F9h	;688F9091
tcmx 394h, #92h	;69929394
djnz r6, -107	;6A95
jr Z, -106	;6B96
ld r6, #97h	;6C97
jp Z, 986Eh	;6D986E
stop	;6F
push 99h	;7099
push @9Ah	;719A
tm r9, r11	;729B
tm r9, @r12	;739C
tm 9Eh, 9Dh	;749D9E
tm A0h, @9Fh	;759FA0
tm A1h, #A2h	;76A1A2
tm @A3h, #A4h	;77A3A4
tmx 6A7h, A5Ah	;78A5A6A7
tmx 9AAh, #A8h	;79A8A9AA
djnz r7, -85	;7AAB
jr C, -84	;7BAC
ld r7, #ADh	;7CAD
jp C, AE7Eh	;7DAE7E
halt	;7F
decw AFh	;80AF
decw @B0h	;81B0
lde r11, @rr1	;82B1
ldei @r11, @rr2	;83B2
ldx r11, 3B4h	;84B3B4
ldx @r11, 5B6h	;85B5B6
ldx B8h, @B7h	;86B7B8
ldx BAh, @.ER(@B9h)	;87B9BA
ldx r11, -68(rr11)	;88BBBC
ldx -66(rr11), r13	;89BDBE
djnz r8, -65	;8ABF
jr T, -64	;8BC0
ld r8, #C1h	;8CC1
jp T, C28Eh	;8DC28E
di	;8F
rl C3h	;90C3
rl @C4h	;91C4
lde @rr5, r12	;92C5
ldei @rr6, @r12	;93C6
ldx 7C8h, r12	;94C7C8
ldx 9Ch, @r12	;95C9CA
ldx @CCh, CBh	;96CBCC
ldx @.ER(@CDh), @CEh	;97CDCE
lea r12, -48(r15)	;98CFD0D1
lea rr13, -44(2D3h)	;99D2D3D4
djnz r9, -43	;9AD5
jr GE, -42	;9BD6
ld r9, #D7h	;9CD7
jp GE, D89Eh	;9DD89E
ei	;9F
incw D9h	;A0D9
incw @DAh	;A1DA
cp r13, r11	;A2DB
cp r13, @r12	;A3DC
cp DEh, DDh	;A4DDDE
cp E0h, @DFh	;A5DFE0
cp E1h, #E2h	;A6E1E2
cp @E3h, #E4h	;A7E3E4
cpx 6E7h, E5Eh	;A8E5E6E7
cpx 9EAh, #E8h	;A9E8E9EA
djnz r10, -21	;AAEB
jr GT, -20	;ABEC
ld r10, #EDh	;ACED
jp GT, EEAEh	;ADEEAE
ret	;AF
clr EFh	;B0EF
clr @F0h	;B1F0
xor r15, r1	;B2F1
xor r15, @r2	;B3F2
xor F4h, F3h	;B4F3F4
xor F6h, @F5h	;B5F5F6
xor F7h, #F8h	;B6F7F8
xor @F9h, #FAh	;B7F9FA
xorx CFDh, FBFh	;B8FBFCFD
xorx F00h, #FEh	;B9FEFF00
djnz r11, 1	;BA01
jr UGT, 2	;BB02
ld r11, #03h	;BC03
jp UGT, 04BEh	;BD04BE
iret	;BF
rrc 05h	;C005
rrc @06h	;C106
ldc r0, @rr7	;C207
ldci @r0, @rr8	;C308
jp @09h	;C409
ldc @r0, @rr10	;C50A
ld r0, 12(r11)	;C70B0C
pushx D0Eh	;C80D0E
djnz r12, 15	;CA0F
jr NOV, 16	;CB10
ld r12, #11h	;CC11
jp NOV, 12CEh	;CD12CE
rcf	;CF
sra 13h	;D013
sra @14h	;D114
ldc @rr5, r1	;D215
ldci @rr6, @r1	;D316
call @17h	;D417
bswap 18h	;D518
call 191Ah	;D6191A
ld 28(r11), r1	;D71B1C
popx D1Eh	;D81D1E
djnz r13, 31	;DA1F
jr PL, 32	;DB20
ld r13, #21h	;DC21
jp PL, 22DEh	;DD22DE
scf	;DF
rrc 23h	;E023
rrc @24h	;E124
bit 0, 0, r5	;E225
ld r2, @r6	;E326
ld 28h, 27h	;E42728
ld 2Ah, @29h	;E5292A
ld 2Bh, #2Ch	;E62B2C
ld @2Dh, #2Eh	;E72D2E
ldx 031h, 2F3h	;E82F3031
ldx 334h, #32h	;E9323334
djnz r14, 53	;EA35
jr NE, 54	;EB36
ld r14, #37h	;EC37
jp NE, 38EEh	;ED38EE
ccf	;EF
swap 39h	;F039
swap @3Ah	;F13A
trap V	;F23B
ld @r3, r12	;F33C
mult 3Dh	;F43D
ld 3Fh, 3Eh	;F53E3F
btj 0, 0, r0, 65	;F64041
btj 0, 0, r2, 67	;F74243
djnz r15, 68	;FA44
jr NC, 69	;FB45
ld r15, #46h	;FC46
jp NC, 47FEh	;FD47FE
push #48h	;7048
cpc r4, r9	;A249
cpc r4, @r10	;A34A
cpc 4Ch, 4Bh	;A44B4C
cpc 4Eh, @4Dh	;A54D4E
cpc 4Fh, #50h	;A64F50
cpc @51h, #52h	;A75152
cpcx 455h, 535h	;A8535455
cpcx 758h, #56h	;A9565758
srl 59h	;C059
srl @5Ah	;C15A
ldwx C5Dh, 5B5h	;E85B5C5D
