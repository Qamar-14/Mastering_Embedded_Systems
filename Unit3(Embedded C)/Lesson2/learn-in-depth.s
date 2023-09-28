
learn-in-depth.elf:     file format elf32-littlearm


Disassembly of section .startup:

00010000 <reset>:
   10000:	e59fd004 	ldr	sp, [pc, #4]	; 1000c <stop+0x4>
   10004:	eb000001 	bl	10010 <main>

00010008 <stop>:
   10008:	eafffffe 	b	10008 <stop>
   1000c:	000111a4 	andeq	r1, r1, r4, lsr #3

Disassembly of section .text:

00010010 <main>:
   10010:	e92d4800 	push	{fp, lr}
   10014:	e28db004 	add	fp, sp, #4
   10018:	e59f0004 	ldr	r0, [pc, #4]	; 10024 <main+0x14>
   1001c:	eb000001 	bl	10028 <Uart_Send_string>
   10020:	e8bd8800 	pop	{fp, pc}
   10024:	000100dc 	ldrdeq	r0, [r1], -ip

00010028 <Uart_Send_string>:
   10028:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
   1002c:	e28db000 	add	fp, sp, #0
   10030:	e24dd00c 	sub	sp, sp, #12
   10034:	e50b0008 	str	r0, [fp, #-8]
   10038:	ea000006 	b	10058 <Uart_Send_string+0x30>
   1003c:	e59f3030 	ldr	r3, [pc, #48]	; 10074 <Uart_Send_string+0x4c>
   10040:	e51b2008 	ldr	r2, [fp, #-8]
   10044:	e5d22000 	ldrb	r2, [r2]
   10048:	e5832000 	str	r2, [r3]
   1004c:	e51b3008 	ldr	r3, [fp, #-8]
   10050:	e2833001 	add	r3, r3, #1
   10054:	e50b3008 	str	r3, [fp, #-8]
   10058:	e51b3008 	ldr	r3, [fp, #-8]
   1005c:	e5d33000 	ldrb	r3, [r3]
   10060:	e3530000 	cmp	r3, #0
   10064:	1afffff4 	bne	1003c <Uart_Send_string+0x14>
   10068:	e28bd000 	add	sp, fp, #0
   1006c:	e8bd0800 	ldmfd	sp!, {fp}
   10070:	e12fff1e 	bx	lr
   10074:	101f1000 	andsne	r1, pc, r0

00010078 <stringBuffer3>:
   10078:	61646f72 	smcvs	18162	; 0x46f2
   1007c:	53206174 	teqpl	r0, #116, 2
   10080:	69746365 	ldmdbvs	r4!, {r0, r2, r5, r6, r8, r9, sp, lr}^
   10084:	00006e6f 	andeq	r6, r0, pc, ror #28
	...

Disassembly of section .data:

000100dc <string_buffer>:
   100dc:	7261656c 	rsbvc	r6, r1, #108, 10	; 0x1b000000
   100e0:	6e692d6e 	cdpvs	13, 6, cr2, cr9, cr14, {3}
   100e4:	7065642d 	rsbvc	r6, r5, sp, lsr #8
   100e8:	6b3a6874 	blvs	eaa2c0 <stack_top+0xe9911c>
   100ec:	6c6f7265 	sfmvs	f7, 2, [pc], #-404	; ff60 <reset-0xa0>
   100f0:	00007365 	andeq	r7, r0, r5, ror #6
	...

Disassembly of section .bss:

00010140 <stringBuffer2>:
	...

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002d41 	andeq	r2, r0, r1, asr #26
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000023 	andeq	r0, r0, r3, lsr #32
  10:	4d524105 	ldfmie	f4, [r2, #-20]	; 0xffffffec
  14:	45363239 	ldrmi	r3, [r6, #-569]!	; 0x239
  18:	00532d4a 	subseq	r2, r3, sl, asr #26
  1c:	01080506 	tsteq	r8, r6, lsl #10
  20:	04120109 	ldreq	r0, [r2], #-265	; 0x109
  24:	01150114 	tsteq	r5, r4, lsl r1
  28:	01180317 	tsteq	r8, r7, lsl r3
  2c:	Address 0x0000002c is out of bounds.


Disassembly of section .comment:

00000000 <.comment>:
   0:	3a434347 	bcc	10d0d24 <stack_top+0x10bfb80>
   4:	4e472820 	cdpmi	8, 4, cr2, cr7, cr0, {1}
   8:	34202955 	strtcc	r2, [r0], #-2389	; 0x955
   c:	322e372e 	eorcc	r3, lr, #12058624	; 0xb80000
	...

Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	00000058 	andeq	r0, r0, r8, asr r0
   4:	00000002 	andeq	r0, r0, r2
   8:	01040000 	mrseq	r0, (UNDEF: 4)
   c:	00000047 	andeq	r0, r0, r7, asr #32
  10:	00005f01 	andeq	r5, r0, r1, lsl #30
  14:	00000000 	andeq	r0, r0, r0
  18:	01002800 	tsteq	r0, r0, lsl #16
  1c:	01007800 	tsteq	r0, r0, lsl #16
  20:	00000000 	andeq	r0, r0, r0
  24:	36010200 	strcc	r0, [r1], -r0, lsl #4
  28:	01000000 	mrseq	r0, (UNDEF: 0)
  2c:	00280104 	eoreq	r0, r8, r4, lsl #2
  30:	00780001 	rsbseq	r0, r8, r1
  34:	00000001 	andeq	r0, r0, r1
  38:	4e010000 	cdpmi	0, 0, cr0, cr1, cr0, {0}
  3c:	03000000 	movweq	r0, #0
  40:	00000053 	andeq	r0, r0, r3, asr r0
  44:	004e0401 	subeq	r0, lr, r1, lsl #8
  48:	91020000 	mrsls	r0, (UNDEF: 2)
  4c:	04040074 	streq	r0, [r4], #-116	; 0x74
  50:	00000054 	andeq	r0, r0, r4, asr r0
  54:	28080105 	stmdacs	r8, {r0, r2, r8}
  58:	00000000 	andeq	r0, r0, r0

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	25011101 	strcs	r1, [r1, #-257]	; 0x101
   4:	030b130e 	movweq	r1, #45838	; 0xb30e
   8:	110e1b0e 	tstne	lr, lr, lsl #22
   c:	10011201 	andne	r1, r1, r1, lsl #4
  10:	02000006 	andeq	r0, r0, #6
  14:	0c3f012e 	ldfeqs	f0, [pc], #-184	; ffffff64 <stack_top+0xfffeedc0>
  18:	0b3a0e03 	bleq	e8382c <stack_top+0xe72688>
  1c:	0c270b3b 	stceq	11, cr0, [r7], #-236	; 0xffffff14
  20:	01120111 	tsteq	r2, r1, lsl r1
  24:	42970640 	addsmi	r0, r7, #64, 12	; 0x4000000
  28:	0013010c 	andseq	r0, r3, ip, lsl #2
  2c:	00050300 	andeq	r0, r5, r0, lsl #6
  30:	0b3a0e03 	bleq	e83844 <stack_top+0xe726a0>
  34:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  38:	00000a02 	andeq	r0, r0, r2, lsl #20
  3c:	0b000f04 	bleq	3c54 <reset-0xc3ac>
  40:	0013490b 	andseq	r4, r3, fp, lsl #18
  44:	00240500 	eoreq	r0, r4, r0, lsl #10
  48:	0b3e0b0b 	bleq	f82c7c <stack_top+0xf71ad8>
  4c:	00000e03 	andeq	r0, r0, r3, lsl #28
	...

Disassembly of section .debug_loc:

00000000 <.debug_loc>:
   0:	00000000 	andeq	r0, r0, r0
   4:	00000004 	andeq	r0, r0, r4
   8:	007d0002 	rsbseq	r0, sp, r2
   c:	00000004 	andeq	r0, r0, r4
  10:	00000008 	andeq	r0, r0, r8
  14:	047d0002 	ldrbteq	r0, [sp], #-2
  18:	00000008 	andeq	r0, r0, r8
  1c:	00000050 	andeq	r0, r0, r0, asr r0
  20:	047b0002 	ldrbteq	r0, [fp], #-2
	...

Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	0000001c 	andeq	r0, r0, ip, lsl r0
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
   c:	00000000 	andeq	r0, r0, r0
  10:	00010028 	andeq	r0, r1, r8, lsr #32
  14:	00000050 	andeq	r0, r0, r0, asr r0
	...

Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	00000039 	andeq	r0, r0, r9, lsr r0
   4:	001d0002 	andseq	r0, sp, r2
   8:	01020000 	mrseq	r0, (UNDEF: 2)
   c:	000d0efb 	strdeq	r0, [sp], -fp
  10:	01010101 	tsteq	r1, r1, lsl #2
  14:	01000000 	mrseq	r0, (UNDEF: 0)
  18:	00010000 	andeq	r0, r1, r0
  1c:	74726175 	ldrbtvc	r6, [r2], #-373	; 0x175
  20:	0000632e 	andeq	r6, r0, lr, lsr #6
  24:	00000000 	andeq	r0, r0, r0
  28:	00280205 	eoreq	r0, r8, r5, lsl #4
  2c:	83160001 	tsthi	r6, #1
  30:	02008330 	andeq	r8, r0, #48, 6	; 0xc0000000
  34:	87630104 	strbhi	r0, [r3, -r4, lsl #2]!
  38:	01000802 	tsteq	r0, r2, lsl #16
  3c:	Address 0x0000003c is out of bounds.


Disassembly of section .debug_str:

00000000 <.debug_str>:
   0:	555c3a43 	ldrbpl	r3, [ip, #-2627]	; 0xa43
   4:	73726573 	cmnvc	r2, #482344960	; 0x1cc00000
   8:	6d61715c 	stfvse	f7, [r1, #-368]!	; 0xfffffe90
   c:	4f5c7261 	svcmi	0x005c7261
  10:	7244656e 	subvc	r6, r4, #461373440	; 0x1b800000
  14:	5c657669 	stclpl	6, cr7, [r5], #-420	; 0xfffffe5c
  18:	6b736544 	blvs	1cd9530 <stack_top+0x1cc838c>
  1c:	5c706f74 	ldclpl	15, cr6, [r0], #-464	; 0xfffffe30
  20:	7373654c 	cmnvc	r3, #76, 10	; 0x13000000
  24:	00336e6f 	eorseq	r6, r3, pc, ror #28
  28:	69736e75 	ldmdbvs	r3!, {r0, r2, r4, r5, r6, r9, sl, fp, sp, lr}^
  2c:	64656e67 	strbtvs	r6, [r5], #-3687	; 0xe67
  30:	61686320 	cmnvs	r8, r0, lsr #6
  34:	61550072 	cmpvs	r5, r2, ror r0
  38:	535f7472 	cmppl	pc, #1912602624	; 0x72000000
  3c:	5f646e65 	svcpl	0x00646e65
  40:	69727473 	ldmdbvs	r2!, {r0, r1, r4, r5, r6, sl, ip, sp, lr}^
  44:	4700676e 	strmi	r6, [r0, -lr, ror #14]
  48:	4320554e 	teqmi	r0, #327155712	; 0x13800000
  4c:	372e3420 	strcc	r3, [lr, -r0, lsr #8]!
  50:	5000322e 	andpl	r3, r0, lr, lsr #4
  54:	5f78745f 	svcpl	0x0078745f
  58:	69727473 	ldmdbvs	r2!, {r0, r1, r4, r5, r6, sl, ip, sp, lr}^
  5c:	7500676e 	strvc	r6, [r0, #-1902]	; 0x76e
  60:	2e747261 	cdpcs	2, 7, cr7, cr4, cr1, {3}
  64:	Address 0x00000064 is out of bounds.


Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	andeq	r0, r0, ip
   4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
   8:	7c020001 	stcvc	0, cr0, [r2], {1}
   c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  10:	00000014 	andeq	r0, r0, r4, lsl r0
  14:	00000000 	andeq	r0, r0, r0
  18:	00010028 	andeq	r0, r1, r8, lsr #32
  1c:	00000050 	andeq	r0, r0, r0, asr r0
  20:	8b040e42 	blhi	103930 <stack_top+0xf278c>
  24:	0b0d4201 	bleq	350830 <stack_top+0x33f68c>
