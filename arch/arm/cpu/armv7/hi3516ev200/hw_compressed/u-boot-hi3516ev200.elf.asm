
u-boot-hi3516ev200.elf:     file format elf32-littlearm


Disassembly of section .text:

40700000 <__image_copy_start>:
40700000:	ea000515 	b	4070145c <reset>
40700004:	eafffffe 	b	40700004 <__image_copy_start+0x4>
40700008:	eafffffe 	b	40700008 <__image_copy_start+0x8>
4070000c:	eafffffe 	b	4070000c <__image_copy_start+0xc>
40700010:	eafffffe 	b	40700010 <__image_copy_start+0x10>
40700014:	eafffffe 	b	40700014 <__image_copy_start+0x14>
40700018:	eafffffe 	b	40700018 <__image_copy_start+0x18>
4070001c:	eafffffe 	b	4070001c <__image_copy_start+0x1c>
40700020:	deadbeef 	.word	0xdeadbeef
40700024:	deadbeef 	.word	0xdeadbeef
40700028:	deadbeef 	.word	0xdeadbeef
4070002c:	deadbeef 	.word	0xdeadbeef
40700030:	deadbeef 	.word	0xdeadbeef
40700034:	deadbeef 	.word	0xdeadbeef
40700038:	deadbeef 	.word	0xdeadbeef
4070003c:	deadbeef 	.word	0xdeadbeef

40700040 <__blank_zone_start>:
	...

40701440 <_blank_zone_start>:
40701440:	40700040 	.word	0x40700040

40701444 <_blank_zone_end>:
40701444:	40701440 	.word	0x40701440
40701448:	deadbeef 	.word	0xdeadbeef
4070144c:	deadbeef 	.word	0xdeadbeef

40701450 <_TEXT_BASE>:
40701450:	40700000 	.word	0x40700000

40701454 <_clr_remap_fmc_entry>:
40701454:	14001554 	.word	0x14001554

40701458 <_start_armboot>:
40701458:	4070456c 	.word	0x4070456c

4070145c <reset>:
4070145c:	ea000087 	b	40701680 <save_boot_params>

40701460 <save_boot_params_ret>:
40701460:	e10f0000 	mrs	r0, CPSR
40701464:	e200101f 	and	r1, r0, #31
40701468:	e331001a 	teq	r1, #26
4070146c:	13c0001f 	bicne	r0, r0, #31
40701470:	13800013 	orrne	r0, r0, #19
40701474:	e38000c0 	orr	r0, r0, #192	; 0xc0
40701478:	e129f000 	msr	CPSR_fc, r0
4070147c:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
40701480:	e3c00a02 	bic	r0, r0, #8192	; 0x2000
40701484:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
40701488:	e24f0090 	sub	r0, pc, #144	; 0x90
4070148c:	e2400c14 	sub	r0, r0, #20, 24	; 0x1400
40701490:	ee0c0f10 	mcr	15, 0, r0, cr12, cr0, {0}
40701494:	e59f023c 	ldr	r0, [pc, #572]	; 407016d8 <cpu_init_cp15+0x54>
40701498:	e5901140 	ldr	r1, [r0, #320]	; 0x140
4070149c:	e59f2238 	ldr	r2, [pc, #568]	; 407016dc <cpu_init_cp15+0x58>
407014a0:	e1510002 	cmp	r1, r2
407014a4:	1a000019 	bne	40701510 <normal_start_flow>
407014a8:	e1a0100d 	mov	r1, sp
407014ac:	e5801140 	str	r1, [r0, #320]	; 0x140
407014b0:	e51f0078 	ldr	r0, [pc, #-120]	; 40701440 <_blank_zone_start>
407014b4:	e51f106c 	ldr	r1, [pc, #-108]	; 40701450 <_TEXT_BASE>
407014b8:	e0400001 	sub	r0, r0, r1
407014bc:	e59f121c 	ldr	r1, [pc, #540]	; 407016e0 <cpu_init_cp15+0x5c>
407014c0:	e59fd21c 	ldr	sp, [pc, #540]	; 407016e4 <cpu_init_cp15+0x60>
407014c4:	e0800001 	add	r0, r0, r1
407014c8:	e3a01000 	mov	r1, #0
407014cc:	eb0000ad 	bl	40701788 <init_registers>
407014d0:	e59f0200 	ldr	r0, [pc, #512]	; 407016d8 <cpu_init_cp15+0x54>
407014d4:	eb0001b8 	bl	40701bbc <start_ddr_training>
407014d8:	e59f01f8 	ldr	r0, [pc, #504]	; 407016d8 <cpu_init_cp15+0x54>
407014dc:	e5901140 	ldr	r1, [r0, #320]	; 0x140
407014e0:	e1a0d001 	mov	sp, r1
407014e4:	e5901144 	ldr	r1, [r0, #324]	; 0x144
407014e8:	e1a0f001 	mov	pc, r1
407014ec:	e320f000 	nop	{0}
407014f0:	e320f000 	nop	{0}
407014f4:	e320f000 	nop	{0}
407014f8:	e320f000 	nop	{0}
407014fc:	e320f000 	nop	{0}
40701500:	e320f000 	nop	{0}
40701504:	e320f000 	nop	{0}
40701508:	e320f000 	nop	{0}
4070150c:	eafffffe 	b	4070150c <save_boot_params_ret+0xac>

40701510 <normal_start_flow>:
40701510:	e59fd1cc 	ldr	sp, [pc, #460]	; 407016e4 <cpu_init_cp15+0x60>
40701514:	eb000ad3 	bl	40704068 <uart_early_init>
40701518:	eb00004a 	bl	40701648 <msg_main_cpu_startup>
4070151c:	e59f01c4 	ldr	r0, [pc, #452]	; 407016e8 <cpu_init_cp15+0x64>
40701520:	e59f31c4 	ldr	r3, [pc, #452]	; 407016ec <cpu_init_cp15+0x68>
40701524:	e5803020 	str	r3, [r0, #32]
40701528:	e3a03001 	mov	r3, #1
4070152c:	e5803000 	str	r3, [r0]
40701530:	e1a00c2f 	lsr	r0, pc, #24
40701534:	e3500000 	cmp	r0, #0
40701538:	1a000005 	bne	40701554 <do_clr_remap>

4070153c <check_boot_type>:
4070153c:	e59f0194 	ldr	r0, [pc, #404]	; 407016d8 <cpu_init_cp15+0x54>
40701540:	e590008c 	ldr	r0, [r0, #140]	; 0x8c
40701544:	e1a06220 	lsr	r6, r0, #4
40701548:	e2066001 	and	r6, r6, #1
4070154c:	e3560001 	cmp	r6, #1
40701550:	351ff104 	ldrcc	pc, [pc, #-260]	; 40701454 <_clr_remap_fmc_entry>

40701554 <do_clr_remap>:
40701554:	e59f417c 	ldr	r4, [pc, #380]	; 407016d8 <cpu_init_cp15+0x54>
40701558:	e5940000 	ldr	r0, [r4]
4070155c:	e3800c01 	orr	r0, r0, #256	; 0x100
40701560:	e5840000 	str	r0, [r4]
40701564:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
40701568:	e3800a01 	orr	r0, r0, #4096	; 0x1000
4070156c:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
40701570:	e1a00e2f 	lsr	r0, pc, #28
40701574:	e3500004 	cmp	r0, #4
40701578:	3a000002 	bcc	40701588 <ddr_init>

4070157c <no_ddr_init>:
4070157c:	e24f0084 	sub	r0, pc, #132	; 0x84
40701580:	e2400c15 	sub	r0, r0, #5376	; 0x1500
40701584:	ea000017 	b	407015e8 <copy_to_ddr>

40701588 <ddr_init>:
40701588:	e51f0150 	ldr	r0, [pc, #-336]	; 40701440 <_blank_zone_start>
4070158c:	e51f1144 	ldr	r1, [pc, #-324]	; 40701450 <_TEXT_BASE>
40701590:	e0400001 	sub	r0, r0, r1
40701594:	e24f109c 	sub	r1, pc, #156	; 0x9c
40701598:	e2411c15 	sub	r1, r1, #5376	; 0x1500
4070159c:	e0800001 	add	r0, r0, r1
407015a0:	e3a01000 	mov	r1, #0
407015a4:	eb000077 	bl	40701788 <init_registers>
407015a8:	e59fd134 	ldr	sp, [pc, #308]	; 407016e4 <cpu_init_cp15+0x60>
407015ac:	e59f0124 	ldr	r0, [pc, #292]	; 407016d8 <cpu_init_cp15+0x54>
407015b0:	eb000181 	bl	40701bbc <start_ddr_training>

407015b4 <check_boot_mode>:
407015b4:	e59f011c 	ldr	r0, [pc, #284]	; 407016d8 <cpu_init_cp15+0x54>
407015b8:	e590008c 	ldr	r0, [r0, #140]	; 0x8c
407015bc:	e1a06220 	lsr	r6, r0, #4
407015c0:	e2066001 	and	r6, r6, #1
407015c4:	e3560001 	cmp	r6, #1
407015c8:	1a000005 	bne	407015e4 <copy_flash_to_ddr>

407015cc <emmc_boot>:
407015cc:	e51f0184 	ldr	r0, [pc, #-388]	; 40701450 <_TEXT_BASE>
407015d0:	e59f1118 	ldr	r1, [pc, #280]	; 407016f0 <cpu_init_cp15+0x6c>
407015d4:	e59f2118 	ldr	r2, [pc, #280]	; 407016f4 <cpu_init_cp15+0x70>
407015d8:	e0421001 	sub	r1, r2, r1
407015dc:	eb000b1b 	bl	40704250 <emmc_boot_read>
407015e0:	ea000007 	b	40701604 <relocate>

407015e4 <copy_flash_to_ddr>:
407015e4:	e3a00305 	mov	r0, #335544320	; 0x14000000

407015e8 <copy_to_ddr>:
407015e8:	e59f1100 	ldr	r1, [pc, #256]	; 407016f0 <cpu_init_cp15+0x6c>
407015ec:	e1500001 	cmp	r0, r1
407015f0:	0a000bdd 	beq	4070456c <start_armboot>
407015f4:	e59f20f4 	ldr	r2, [pc, #244]	; 407016f0 <cpu_init_cp15+0x6c>
407015f8:	e59f30f4 	ldr	r3, [pc, #244]	; 407016f4 <cpu_init_cp15+0x70>
407015fc:	e0432002 	sub	r2, r3, r2
40701600:	eb00000a 	bl	40701630 <memcpy>

40701604 <relocate>:
40701604:	e59f00ec 	ldr	r0, [pc, #236]	; 407016f8 <cpu_init_cp15+0x74>
40701608:	e590f000 	ldr	pc, [r0]

4070160c <bug>:
4070160c:	e320f000 	nop	{0}
40701610:	e320f000 	nop	{0}
40701614:	e320f000 	nop	{0}
40701618:	e320f000 	nop	{0}
4070161c:	e320f000 	nop	{0}
40701620:	e320f000 	nop	{0}
40701624:	e320f000 	nop	{0}
40701628:	e320f000 	nop	{0}
4070162c:	eafffffe 	b	4070162c <bug+0x20>

40701630 <memcpy>:
40701630:	e0802002 	add	r2, r0, r2

40701634 <memcpy_loop>:
40701634:	e8b007f8 	ldm	r0!, {r3, r4, r5, r6, r7, r8, r9, sl}
40701638:	e8a107f8 	stmia	r1!, {r3, r4, r5, r6, r7, r8, r9, sl}
4070163c:	e1500002 	cmp	r0, r2
40701640:	dafffffb 	ble	40701634 <memcpy_loop>
40701644:	e1a0f00e 	mov	pc, lr

40701648 <msg_main_cpu_startup>:
40701648:	e1a0500e 	mov	r5, lr
4070164c:	e28f0004 	add	r0, pc, #4
40701650:	eb000a91 	bl	4070409c <uart_early_puts>
40701654:	e1a0f005 	mov	pc, r5

40701658 <L10>:
40701658:	0a0d0a0d 	.word	0x0a0d0a0d
4070165c:	74737953 	.word	0x74737953
40701660:	73206d65 	.word	0x73206d65
40701664:	74726174 	.word	0x74726174
40701668:	0a0d7075 	.word	0x0a0d7075
4070166c:	00          	.byte	0x00
4070166d:	00          	.byte	0x00
	...

40701670 <c_runtime_cpu_setup>:
40701670:	ee070f15 	mcr	15, 0, r0, cr7, cr5, {0}
40701674:	ee070f9a 	mcr	15, 0, r0, cr7, cr10, {4}
40701678:	ee070f95 	mcr	15, 0, r0, cr7, cr5, {4}
4070167c:	e12fff1e 	bx	lr

40701680 <save_boot_params>:
40701680:	eaffff76 	b	40701460 <save_boot_params_ret>

40701684 <cpu_init_cp15>:
40701684:	e3a00000 	mov	r0, #0
40701688:	ee080f17 	mcr	15, 0, r0, cr8, cr7, {0}
4070168c:	ee070f15 	mcr	15, 0, r0, cr7, cr5, {0}
40701690:	ee070fd5 	mcr	15, 0, r0, cr7, cr5, {6}
40701694:	ee070f9a 	mcr	15, 0, r0, cr7, cr10, {4}
40701698:	ee070f95 	mcr	15, 0, r0, cr7, cr5, {4}
4070169c:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
407016a0:	e3c00a02 	bic	r0, r0, #8192	; 0x2000
407016a4:	e3c00007 	bic	r0, r0, #7
407016a8:	e3800002 	orr	r0, r0, #2
407016ac:	e3800b02 	orr	r0, r0, #2048	; 0x800
407016b0:	e3800a01 	orr	r0, r0, #4096	; 0x1000
407016b4:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
407016b8:	e1a0500e 	mov	r5, lr
407016bc:	ee101f10 	mrc	15, 0, r1, cr0, cr0, {0}
407016c0:	e1a03a21 	lsr	r3, r1, #20
407016c4:	e203300f 	and	r3, r3, #15
407016c8:	e201400f 	and	r4, r1, #15
407016cc:	e1a02203 	lsl	r2, r3, #4
407016d0:	e1842002 	orr	r2, r4, r2
407016d4:	e1a0f005 	mov	pc, r5
407016d8:	12020000 	.word	0x12020000
407016dc:	7a696a75 	.word	0x7a696a75
407016e0:	04010500 	.word	0x04010500
407016e4:	0401a000 	.word	0x0401a000
407016e8:	12050000 	.word	0x12050000
407016ec:	02faf080 	.word	0x02faf080
407016f0:	40700000 	.word	0x40700000
407016f4:	4073bda4 	.word	0x4073bda4
407016f8:	40701458 	.word	0x40701458

407016fc <reg_read>:
407016fc:	e590300c 	ldr	r3, [r0, #12]
40701700:	e5902000 	ldr	r2, [r0]
40701704:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
40701708:	e1a0eda3 	lsr	lr, r3, #27
4070170c:	e7e439d3 	ubfx	r3, r3, #19, #5
40701710:	e5922000 	ldr	r2, [r2]
40701714:	e2833001 	add	r3, r3, #1
40701718:	e3530020 	cmp	r3, #32
4070171c:	13e0c000 	mvnne	ip, #0
40701720:	11e0331c 	mvnne	r3, ip, lsl r3
40701724:	10032e32 	andne	r2, r3, r2, lsr lr
40701728:	e5903004 	ldr	r3, [r0, #4]
4070172c:	e0533002 	subs	r3, r3, r2
40701730:	13a03001 	movne	r3, #1
40701734:	e5813000 	str	r3, [r1]
40701738:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)

4070173c <reg_write>:
4070173c:	e92d4010 	push	{r4, lr}
40701740:	e590200c 	ldr	r2, [r0, #12]
40701744:	e5904000 	ldr	r4, [r0]
40701748:	e7e411d2 	ubfx	r1, r2, #3, #5
4070174c:	e5903004 	ldr	r3, [r0, #4]
40701750:	e2811001 	add	r1, r1, #1
40701754:	e590c008 	ldr	ip, [r0, #8]
40701758:	e3510020 	cmp	r1, #32
4070175c:	e594e000 	ldr	lr, [r4]
40701760:	17e425d2 	ubfxne	r2, r2, #11, #5
40701764:	13e00000 	mvnne	r0, #0
40701768:	11e01110 	mvnne	r1, r0, lsl r1
4070176c:	11ce1211 	bicne	r1, lr, r1, lsl r2
40701770:	11813213 	orrne	r3, r1, r3, lsl r2
40701774:	e5843000 	str	r3, [r4]
40701778:	e320f000 	nop	{0}
4070177c:	e25cc001 	subs	ip, ip, #1
40701780:	2afffffc 	bcs	40701778 <reg_write+0x3c>
40701784:	e8bd8010 	pop	{r4, pc}

40701788 <init_registers>:
40701788:	e92d40f7 	push	{r0, r1, r2, r4, r5, r6, r7, lr}
4070178c:	e1a06001 	mov	r6, r1
40701790:	e1a04000 	mov	r4, r0
40701794:	e3a07000 	mov	r7, #0
40701798:	e5943000 	ldr	r3, [r4]
4070179c:	e3530000 	cmp	r3, #0
407017a0:	1a000008 	bne	407017c8 <init_registers+0x40>
407017a4:	e5943004 	ldr	r3, [r4, #4]
407017a8:	e3530000 	cmp	r3, #0
407017ac:	1a000005 	bne	407017c8 <init_registers+0x40>
407017b0:	e5943008 	ldr	r3, [r4, #8]
407017b4:	e3530000 	cmp	r3, #0
407017b8:	1a000002 	bne	407017c8 <init_registers+0x40>
407017bc:	e594300c 	ldr	r3, [r4, #12]
407017c0:	e3530000 	cmp	r3, #0
407017c4:	0a00002e 	beq	40701884 <init_registers+0xfc>
407017c8:	e3560000 	cmp	r6, #0
407017cc:	e58d7004 	str	r7, [sp, #4]
407017d0:	e5945008 	ldr	r5, [r4, #8]
407017d4:	e594300c 	ldr	r3, [r4, #12]
407017d8:	0a000016 	beq	40701838 <init_registers+0xb0>
407017dc:	e3130002 	tst	r3, #2
407017e0:	0a000002 	beq	407017f0 <init_registers+0x68>
407017e4:	e1a00004 	mov	r0, r4
407017e8:	ebffffd3 	bl	4070173c <reg_write>
407017ec:	ea00000b 	b	40701820 <init_registers+0x98>
407017f0:	e3130802 	tst	r3, #131072	; 0x20000
407017f4:	0a00000b 	beq	40701828 <init_registers+0xa0>
407017f8:	e28d1004 	add	r1, sp, #4
407017fc:	e1a00004 	mov	r0, r4
40701800:	ebffffbd 	bl	407016fc <reg_read>
40701804:	e320f000 	nop	{0}
40701808:	e59d3004 	ldr	r3, [sp, #4]
4070180c:	e3530000 	cmp	r3, #0
40701810:	1afffff8 	bne	407017f8 <init_registers+0x70>
40701814:	e320f000 	nop	{0}
40701818:	e2555001 	subs	r5, r5, #1
4070181c:	2afffffc 	bcs	40701814 <init_registers+0x8c>
40701820:	e2844010 	add	r4, r4, #16
40701824:	eaffffdb 	b	40701798 <init_registers+0x10>
40701828:	e320f000 	nop	{0}
4070182c:	e2555001 	subs	r5, r5, #1
40701830:	2afffffc 	bcs	40701828 <init_registers+0xa0>
40701834:	eafffff9 	b	40701820 <init_registers+0x98>
40701838:	e3130004 	tst	r3, #4
4070183c:	1affffe8 	bne	407017e4 <init_registers+0x5c>
40701840:	e3130701 	tst	r3, #262144	; 0x40000
40701844:	0a00000a 	beq	40701874 <init_registers+0xec>
40701848:	e28d1004 	add	r1, sp, #4
4070184c:	e1a00004 	mov	r0, r4
40701850:	ebffffa9 	bl	407016fc <reg_read>
40701854:	e320f000 	nop	{0}
40701858:	e59d3004 	ldr	r3, [sp, #4]
4070185c:	e3530000 	cmp	r3, #0
40701860:	1afffff8 	bne	40701848 <init_registers+0xc0>
40701864:	e320f000 	nop	{0}
40701868:	e2555001 	subs	r5, r5, #1
4070186c:	2afffffc 	bcs	40701864 <init_registers+0xdc>
40701870:	eaffffea 	b	40701820 <init_registers+0x98>
40701874:	e320f000 	nop	{0}
40701878:	e2555001 	subs	r5, r5, #1
4070187c:	2afffffc 	bcs	40701874 <init_registers+0xec>
40701880:	eaffffe6 	b	40701820 <init_registers+0x98>
40701884:	e320f000 	nop	{0}
40701888:	e28dd00c 	add	sp, sp, #12
4070188c:	e8bd80f0 	pop	{r4, r5, r6, r7, pc}

40701890 <delay>:
40701890:	e24dd008 	sub	sp, sp, #8
40701894:	e3a03000 	mov	r3, #0
40701898:	e58d3004 	str	r3, [sp, #4]
4070189c:	e3a03064 	mov	r3, #100	; 0x64
407018a0:	e0000093 	mul	r0, r3, r0
407018a4:	e59d3004 	ldr	r3, [sp, #4]
407018a8:	e1500003 	cmp	r0, r3
407018ac:	8a000001 	bhi	407018b8 <delay+0x28>
407018b0:	e28dd008 	add	sp, sp, #8
407018b4:	e12fff1e 	bx	lr
407018b8:	e320f000 	nop	{0}
407018bc:	e59d3004 	ldr	r3, [sp, #4]
407018c0:	e2833001 	add	r3, r3, #1
407018c4:	e58d3004 	str	r3, [sp, #4]
407018c8:	eafffff5 	b	407018a4 <delay+0x14>

407018cc <get_random_num>:
407018cc:	e59f2014 	ldr	r2, [pc, #20]	; 407018e8 <get_random_num+0x1c>
407018d0:	e5923208 	ldr	r3, [r2, #520]	; 0x208
407018d4:	e7e73453 	ubfx	r3, r3, #8, #8
407018d8:	e3530000 	cmp	r3, #0
407018dc:	0afffffb 	beq	407018d0 <get_random_num+0x4>
407018e0:	e5920204 	ldr	r0, [r2, #516]	; 0x204
407018e4:	e12fff1e 	bx	lr
407018e8:	10090000 	.word	0x10090000

407018ec <trng_init>:
407018ec:	e59f2018 	ldr	r2, [pc, #24]	; 4070190c <trng_init+0x20>
407018f0:	e59231a0 	ldr	r3, [r2, #416]	; 0x1a0
407018f4:	e3833008 	orr	r3, r3, #8
407018f8:	e58231a0 	str	r3, [r2, #416]	; 0x1a0
407018fc:	e59f300c 	ldr	r3, [pc, #12]	; 40701910 <trng_init+0x24>
40701900:	e3a0200a 	mov	r2, #10
40701904:	e5832200 	str	r2, [r3, #512]	; 0x200
40701908:	e12fff1e 	bx	lr
4070190c:	12010000 	.word	0x12010000
40701910:	10090000 	.word	0x10090000

40701914 <trng_deinit>:
40701914:	e59f200c 	ldr	r2, [pc, #12]	; 40701928 <trng_deinit+0x14>
40701918:	e59231a0 	ldr	r3, [r2, #416]	; 0x1a0
4070191c:	e3c33008 	bic	r3, r3, #8
40701920:	e58231a0 	str	r3, [r2, #416]	; 0x1a0
40701924:	e12fff1e 	bx	lr
40701928:	12010000 	.word	0x12010000

4070192c <ddr_scramb>:
4070192c:	e59f309c 	ldr	r3, [pc, #156]	; 407019d0 <ddr_scramb+0xa4>
40701930:	e92d4010 	push	{r4, lr}
40701934:	e5932050 	ldr	r2, [r3, #80]	; 0x50
40701938:	e212100f 	ands	r1, r2, #15
4070193c:	1a000016 	bne	4070199c <ddr_scramb+0x70>
40701940:	ebffffe9 	bl	407018ec <trng_init>
40701944:	ebffffe0 	bl	407018cc <get_random_num>
40701948:	e1a04000 	mov	r4, r0
4070194c:	ebffffde 	bl	407018cc <get_random_num>
40701950:	e59f207c 	ldr	r2, [pc, #124]	; 407019d4 <ddr_scramb+0xa8>
40701954:	e3a03010 	mov	r3, #16
40701958:	e5824028 	str	r4, [r2, #40]	; 0x28
4070195c:	e3a04000 	mov	r4, #0
40701960:	e582002c 	str	r0, [r2, #44]	; 0x2c
40701964:	e3a00ffa 	mov	r0, #1000	; 0x3e8
40701968:	e5824030 	str	r4, [r2, #48]	; 0x30
4070196c:	e5823030 	str	r3, [r2, #48]	; 0x30
40701970:	ebffffc6 	bl	40701890 <delay>
40701974:	e5824028 	str	r4, [r2, #40]	; 0x28
40701978:	e582402c 	str	r4, [r2, #44]	; 0x2c
4070197c:	ebffffd2 	bl	407018cc <get_random_num>
40701980:	ebffffd1 	bl	407018cc <get_random_num>
40701984:	ebffffd0 	bl	407018cc <get_random_num>
40701988:	ebffffcf 	bl	407018cc <get_random_num>
4070198c:	ebffffe0 	bl	40701914 <trng_deinit>
40701990:	e1510004 	cmp	r1, r4
40701994:	1a000006 	bne	407019b4 <ddr_scramb+0x88>
40701998:	e8bd8010 	pop	{r4, pc}
4070199c:	e3a02001 	mov	r2, #1
407019a0:	e5832000 	str	r2, [r3]
407019a4:	e5932294 	ldr	r2, [r3, #660]	; 0x294
407019a8:	e3120001 	tst	r2, #1
407019ac:	0afffffc 	beq	407019a4 <ddr_scramb+0x78>
407019b0:	eaffffe2 	b	40701940 <ddr_scramb+0x14>
407019b4:	e59f3014 	ldr	r3, [pc, #20]	; 407019d0 <ddr_scramb+0xa4>
407019b8:	e3a02002 	mov	r2, #2
407019bc:	e5832000 	str	r2, [r3]
407019c0:	e5932294 	ldr	r2, [r3, #660]	; 0x294
407019c4:	e3120001 	tst	r2, #1
407019c8:	1afffffc 	bne	407019c0 <ddr_scramb+0x94>
407019cc:	e8bd8010 	pop	{r4, pc}
407019d0:	120d8000 	.word	0x120d8000
407019d4:	12030000 	.word	0x12030000

407019d8 <start_svb>:
407019d8:	e59f21c4 	ldr	r2, [pc, #452]	; 40701ba4 <start_svb+0x1cc>
407019dc:	e92d4030 	push	{r4, r5, lr}
407019e0:	e24dd014 	sub	sp, sp, #20
407019e4:	e5923168 	ldr	r3, [r2, #360]	; 0x168
407019e8:	e3c338ff 	bic	r3, r3, #16711680	; 0xff0000
407019ec:	e3833601 	orr	r3, r3, #1048576	; 0x100000
407019f0:	e5823168 	str	r3, [r2, #360]	; 0x168
407019f4:	e59f31ac 	ldr	r3, [pc, #428]	; 40701ba8 <start_svb+0x1d0>
407019f8:	e59310bc 	ldr	r1, [r3, #188]	; 0xbc
407019fc:	e7e93051 	ubfx	r3, r1, #0, #10
40701a00:	e3530075 	cmp	r3, #117	; 0x75
40701a04:	93e01027 	mvnls	r1, #39	; 0x27
40701a08:	9a000007 	bls	40701a2c <start_svb+0x54>
40701a0c:	e3530fd2 	cmp	r3, #840	; 0x348
40701a10:	93a010d4 	movls	r1, #212	; 0xd4
40701a14:	83a0106e 	movhi	r1, #110	; 0x6e
40701a18:	90010391 	mulls	r1, r1, r3
40701a1c:	92411a06 	subls	r1, r1, #24576	; 0x6000
40701a20:	924110e4 	subls	r1, r1, #228	; 0xe4
40701a24:	91a01521 	lsrls	r1, r1, #10
40701a28:	92411028 	subls	r1, r1, #40	; 0x28
40701a2c:	e59f5174 	ldr	r5, [pc, #372]	; 40701ba8 <start_svb+0x1d0>
40701a30:	e3a04004 	mov	r4, #4
40701a34:	e3a03000 	mov	r3, #0
40701a38:	e58d3000 	str	r3, [sp]
40701a3c:	e58d3004 	str	r3, [sp, #4]
40701a40:	e58d3008 	str	r3, [sp, #8]
40701a44:	e58d300c 	str	r3, [sp, #12]
40701a48:	e3a0000a 	mov	r0, #10
40701a4c:	ebffff8f 	bl	40701890 <delay>
40701a50:	e59530d8 	ldr	r3, [r5, #216]	; 0xd8
40701a54:	e59d2004 	ldr	r2, [sp, #4]
40701a58:	e2544001 	subs	r4, r4, #1
40701a5c:	e7e90853 	ubfx	r0, r3, #16, #10
40701a60:	e7e93053 	ubfx	r3, r3, #0, #10
40701a64:	e0802002 	add	r2, r0, r2
40701a68:	e59d0000 	ldr	r0, [sp]
40701a6c:	e58d2004 	str	r2, [sp, #4]
40701a70:	e0833000 	add	r3, r3, r0
40701a74:	e58d3000 	str	r3, [sp]
40701a78:	e59500dc 	ldr	r0, [r5, #220]	; 0xdc
40701a7c:	e59de00c 	ldr	lr, [sp, #12]
40701a80:	e7e9c850 	ubfx	ip, r0, #16, #10
40701a84:	e7e90050 	ubfx	r0, r0, #0, #10
40701a88:	e08cc00e 	add	ip, ip, lr
40701a8c:	e59de008 	ldr	lr, [sp, #8]
40701a90:	e58dc00c 	str	ip, [sp, #12]
40701a94:	e080000e 	add	r0, r0, lr
40701a98:	e58d0008 	str	r0, [sp, #8]
40701a9c:	1affffe9 	bne	40701a48 <start_svb+0x70>
40701aa0:	e1a02122 	lsr	r2, r2, #2
40701aa4:	e0823123 	add	r3, r2, r3, lsr #2
40701aa8:	e300211a 	movw	r2, #282	; 0x11a
40701aac:	e0833120 	add	r3, r3, r0, lsr #2
40701ab0:	e083312c 	add	r3, r3, ip, lsr #2
40701ab4:	e1a03123 	lsr	r3, r3, #2
40701ab8:	e1530002 	cmp	r3, r2
40701abc:	9a000030 	bls	40701b84 <start_svb+0x1ac>
40701ac0:	e3510045 	cmp	r1, #69	; 0x45
40701ac4:	9a000005 	bls	40701ae0 <start_svb+0x108>
40701ac8:	e3a020cd 	mov	r2, #205	; 0xcd
40701acc:	e0010192 	mul	r1, r2, r1
40701ad0:	e2411b0e 	sub	r1, r1, #14336	; 0x3800
40701ad4:	e241100e 	sub	r1, r1, #14
40701ad8:	e0833521 	add	r3, r3, r1, lsr #10
40701adc:	e2833004 	add	r3, r3, #4
40701ae0:	e59f10bc 	ldr	r1, [pc, #188]	; 40701ba4 <start_svb+0x1cc>
40701ae4:	e3530095 	cmp	r3, #149	; 0x95
40701ae8:	93a03096 	movls	r3, #150	; 0x96
40701aec:	e591215c 	ldr	r2, [r1, #348]	; 0x15c
40701af0:	e7d8281f 	bfc	r2, #16, #9
40701af4:	93822301 	orrls	r2, r2, #67108864	; 0x4000000
40701af8:	9a000004 	bls	40701b10 <start_svb+0x138>
40701afc:	e300015e 	movw	r0, #350	; 0x15e
40701b00:	e1530000 	cmp	r3, r0
40701b04:	97da2d1f 	bfcls	r2, #26, #1
40701b08:	83822301 	orrhi	r2, r2, #67108864	; 0x4000000
40701b0c:	81a03000 	movhi	r3, r0
40701b10:	e7d82813 	bfi	r2, r3, #16, #9
40701b14:	e581215c 	str	r2, [r1, #348]	; 0x15c
40701b18:	e59f208c 	ldr	r2, [pc, #140]	; 40701bac <start_svb+0x1d4>
40701b1c:	e35300be 	cmp	r3, #190	; 0xbe
40701b20:	93a03e3e 	movls	r3, #992	; 0x3e0
40701b24:	e592102c 	ldr	r1, [r2, #44]	; 0x2c
40701b28:	9a000006 	bls	40701b48 <start_svb+0x170>
40701b2c:	e3002135 	movw	r2, #309	; 0x135
40701b30:	e1530002 	cmp	r3, r2
40701b34:	93002601 	movwls	r2, #1537	; 0x601
40701b38:	83a03fcb 	movhi	r3, #812	; 0x32c
40701b3c:	90020392 	mulls	r2, r2, r3
40701b40:	930034fd 	movwls	r3, #1277	; 0x4fd
40701b44:	90433522 	subls	r3, r3, r2, lsr #10
40701b48:	e59f2054 	ldr	r2, [pc, #84]	; 40701ba4 <start_svb+0x1cc>
40701b4c:	e0833841 	add	r3, r3, r1, asr #16
40701b50:	e59f1058 	ldr	r1, [pc, #88]	; 40701bb0 <start_svb+0x1d8>
40701b54:	e3a000c8 	mov	r0, #200	; 0xc8
40701b58:	e5823158 	str	r3, [r2, #344]	; 0x158
40701b5c:	e59f2050 	ldr	r2, [pc, #80]	; 40701bb4 <start_svb+0x1dc>
40701b60:	e0232391 	mla	r3, r1, r3, r2
40701b64:	e59f204c 	ldr	r2, [pc, #76]	; 40701bb8 <start_svb+0x1e0>
40701b68:	e1a03523 	lsr	r3, r3, #10
40701b6c:	e5823004 	str	r3, [r2, #4]
40701b70:	e3a03005 	mov	r3, #5
40701b74:	e582300c 	str	r3, [r2, #12]
40701b78:	e28dd014 	add	sp, sp, #20
40701b7c:	e8bd4030 	pop	{r4, r5, lr}
40701b80:	eaffff42 	b	40701890 <delay>
40701b84:	e35300de 	cmp	r3, #222	; 0xde
40701b88:	93a02001 	movls	r2, #1
40701b8c:	83a02000 	movhi	r2, #0
40701b90:	e3510045 	cmp	r1, #69	; 0x45
40701b94:	93a02000 	movls	r2, #0
40701b98:	e3520000 	cmp	r2, #0
40701b9c:	12433004 	subne	r3, r3, #4
40701ba0:	eaffffce 	b	40701ae0 <start_svb+0x108>
40701ba4:	12020000 	.word	0x12020000
40701ba8:	12028000 	.word	0x12028000
40701bac:	100a0000 	.word	0x100a0000
40701bb0:	fffffe34 	.word	0xfffffe34
40701bb4:	0007b6c4 	.word	0x0007b6c4
40701bb8:	12080000 	.word	0x12080000

40701bbc <start_ddr_training>:
40701bbc:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40701bc0:	ebffff84 	bl	407019d8 <start_svb>
40701bc4:	e59f3154 	ldr	r3, [pc, #340]	; 40701d20 <start_ddr_training+0x164>
40701bc8:	e5937010 	ldr	r7, [r3, #16]
40701bcc:	e3c72020 	bic	r2, r7, #32
40701bd0:	e5832010 	str	r2, [r3, #16]
40701bd4:	e2433906 	sub	r3, r3, #98304	; 0x18000
40701bd8:	e5936198 	ldr	r6, [r3, #408]	; 0x198
40701bdc:	e3862002 	orr	r2, r6, #2
40701be0:	e5832198 	str	r2, [r3, #408]	; 0x198
40701be4:	e320f000 	nop	{0}
40701be8:	e59f4134 	ldr	r4, [pc, #308]	; 40701d24 <start_ddr_training+0x168>
40701bec:	e3a00000 	mov	r0, #0
40701bf0:	e5932198 	ldr	r2, [r3, #408]	; 0x198
40701bf4:	e59fa12c 	ldr	sl, [pc, #300]	; 40701d28 <start_ddr_training+0x16c>
40701bf8:	e3c22001 	bic	r2, r2, #1
40701bfc:	e5832198 	str	r2, [r3, #408]	; 0x198
40701c00:	e59450b0 	ldr	r5, [r4, #176]	; 0xb0
40701c04:	e3c53102 	bic	r3, r5, #-2147483648	; 0x80000000
40701c08:	e58430b0 	str	r3, [r4, #176]	; 0xb0
40701c0c:	eb0008d7 	bl	40703f70 <ddr_pcode_training_if>
40701c10:	e3a00000 	mov	r0, #0
40701c14:	eb0008d4 	bl	40703f6c <ddr_hw_training_if>
40701c18:	e3a00000 	mov	r0, #0
40701c1c:	eb0008d1 	bl	40703f68 <ddr_sw_training_if>
40701c20:	e594222c 	ldr	r2, [r4, #556]	; 0x22c
40701c24:	e594e21c 	ldr	lr, [r4, #540]	; 0x21c
40701c28:	e1a03004 	mov	r3, r4
40701c2c:	e5948220 	ldr	r8, [r4, #544]	; 0x220
40701c30:	e594c224 	ldr	ip, [r4, #548]	; 0x224
40701c34:	e1a0100e 	mov	r1, lr
40701c38:	e04cc002 	sub	ip, ip, r2
40701c3c:	e2020003 	and	r0, r2, #3
40701c40:	e3500003 	cmp	r0, #3
40701c44:	0a000009 	beq	40701c70 <start_ddr_training+0xb4>
40701c48:	e081100a 	add	r1, r1, sl
40701c4c:	e2822001 	add	r2, r2, #1
40701c50:	e0880001 	add	r0, r8, r1
40701c54:	e583222c 	str	r2, [r3, #556]	; 0x22c
40701c58:	e040000e 	sub	r0, r0, lr
40701c5c:	e583121c 	str	r1, [r3, #540]	; 0x21c
40701c60:	e08c4002 	add	r4, ip, r2
40701c64:	e5830220 	str	r0, [r3, #544]	; 0x220
40701c68:	e5834224 	str	r4, [r3, #548]	; 0x224
40701c6c:	eafffff2 	b	40701c3c <start_ddr_training+0x80>
40701c70:	e59322ac 	ldr	r2, [r3, #684]	; 0x2ac
40701c74:	e593e29c 	ldr	lr, [r3, #668]	; 0x29c
40701c78:	e59382a0 	ldr	r8, [r3, #672]	; 0x2a0
40701c7c:	e593c2a4 	ldr	ip, [r3, #676]	; 0x2a4
40701c80:	e59fa0a0 	ldr	sl, [pc, #160]	; 40701d28 <start_ddr_training+0x16c>
40701c84:	e1a0100e 	mov	r1, lr
40701c88:	e59f3094 	ldr	r3, [pc, #148]	; 40701d24 <start_ddr_training+0x168>
40701c8c:	e04cc002 	sub	ip, ip, r2
40701c90:	e2020003 	and	r0, r2, #3
40701c94:	e3500003 	cmp	r0, #3
40701c98:	0a000009 	beq	40701cc4 <start_ddr_training+0x108>
40701c9c:	e081100a 	add	r1, r1, sl
40701ca0:	e2822001 	add	r2, r2, #1
40701ca4:	e0880001 	add	r0, r8, r1
40701ca8:	e58322ac 	str	r2, [r3, #684]	; 0x2ac
40701cac:	e040000e 	sub	r0, r0, lr
40701cb0:	e583129c 	str	r1, [r3, #668]	; 0x29c
40701cb4:	e08c4002 	add	r4, ip, r2
40701cb8:	e58302a0 	str	r0, [r3, #672]	; 0x2a0
40701cbc:	e58342a4 	str	r4, [r3, #676]	; 0x2a4
40701cc0:	eafffff2 	b	40701c90 <start_ddr_training+0xd4>
40701cc4:	e5932070 	ldr	r2, [r3, #112]	; 0x70
40701cc8:	e3821702 	orr	r1, r2, #524288	; 0x80000
40701ccc:	e3c22702 	bic	r2, r2, #524288	; 0x80000
40701cd0:	e5831070 	str	r1, [r3, #112]	; 0x70
40701cd4:	e5832070 	str	r2, [r3, #112]	; 0x70
40701cd8:	e5932004 	ldr	r2, [r3, #4]
40701cdc:	e3821902 	orr	r1, r2, #32768	; 0x8000
40701ce0:	e3c22902 	bic	r2, r2, #32768	; 0x8000
40701ce4:	e5831004 	str	r1, [r3, #4]
40701ce8:	e5832004 	str	r2, [r3, #4]
40701cec:	e59f202c 	ldr	r2, [pc, #44]	; 40701d20 <start_ddr_training+0x164>
40701cf0:	e5827010 	str	r7, [r2, #16]
40701cf4:	e2422906 	sub	r2, r2, #98304	; 0x18000
40701cf8:	e5826198 	str	r6, [r2, #408]	; 0x198
40701cfc:	e3002401 	movw	r2, #1025	; 0x401
40701d00:	e58350b0 	str	r5, [r3, #176]	; 0xb0
40701d04:	e593302c 	ldr	r3, [r3, #44]	; 0x2c
40701d08:	e203300f 	and	r3, r3, #15
40701d0c:	e3530006 	cmp	r3, #6
40701d10:	e59f3014 	ldr	r3, [pc, #20]	; 40701d2c <start_ddr_training+0x170>
40701d14:	e5832028 	str	r2, [r3, #40]	; 0x28
40701d18:	05832028 	streq	r2, [r3, #40]	; 0x28
40701d1c:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40701d20:	12028000 	.word	0x12028000
40701d24:	120dc000 	.word	0x120dc000
40701d28:	01010101 	.word	0x01010101
40701d2c:	120d8000 	.word	0x120d8000

40701d30 <ddr_adjust_get_average>:
40701d30:	e5902060 	ldr	r2, [r0, #96]	; 0x60
40701d34:	e5901040 	ldr	r1, [r0, #64]	; 0x40
40701d38:	e5903054 	ldr	r3, [r0, #84]	; 0x54
40701d3c:	e5900050 	ldr	r0, [r0, #80]	; 0x50
40701d40:	e1a02502 	lsl	r2, r2, #10
40701d44:	e3500002 	cmp	r0, #2
40701d48:	1a000004 	bne	40701d60 <ddr_adjust_get_average+0x30>
40701d4c:	e2811f86 	add	r1, r1, #536	; 0x218
40701d50:	e0822001 	add	r2, r2, r1
40701d54:	e7920383 	ldr	r0, [r2, r3, lsl #7]
40701d58:	e200007f 	and	r0, r0, #127	; 0x7f
40701d5c:	e12fff1e 	bx	lr
40701d60:	e0823383 	add	r3, r2, r3, lsl #7
40701d64:	e0833001 	add	r3, r3, r1
40701d68:	e593221c 	ldr	r2, [r3, #540]	; 0x21c
40701d6c:	e5933220 	ldr	r3, [r3, #544]	; 0x220
40701d70:	e202007f 	and	r0, r2, #127	; 0x7f
40701d74:	e203107f 	and	r1, r3, #127	; 0x7f
40701d78:	e0800001 	add	r0, r0, r1
40701d7c:	e7e61452 	ubfx	r1, r2, #8, #7
40701d80:	e0800001 	add	r0, r0, r1
40701d84:	e7e61852 	ubfx	r1, r2, #16, #7
40701d88:	e0800001 	add	r0, r0, r1
40701d8c:	e7e62c52 	ubfx	r2, r2, #24, #7
40701d90:	e0800002 	add	r0, r0, r2
40701d94:	e7e62453 	ubfx	r2, r3, #8, #7
40701d98:	e0800002 	add	r0, r0, r2
40701d9c:	e7e62853 	ubfx	r2, r3, #16, #7
40701da0:	e0800002 	add	r0, r0, r2
40701da4:	e7e63c53 	ubfx	r3, r3, #24, #7
40701da8:	e0800003 	add	r0, r0, r3
40701dac:	e1a001a0 	lsr	r0, r0, #3
40701db0:	e12fff1e 	bx	lr

40701db4 <ddrtr_memcpy>:
40701db4:	e2403001 	sub	r3, r0, #1
40701db8:	e0812002 	add	r2, r1, r2
40701dbc:	e1510002 	cmp	r1, r2
40701dc0:	1a000000 	bne	40701dc8 <ddrtr_memcpy+0x14>
40701dc4:	e12fff1e 	bx	lr
40701dc8:	e4d1c001 	ldrb	ip, [r1], #1
40701dcc:	e5e3c001 	strb	ip, [r3, #1]!
40701dd0:	eafffff9 	b	40701dbc <ddrtr_memcpy+0x8>

40701dd4 <ddrtr_memset>:
40701dd4:	e0802002 	add	r2, r0, r2
40701dd8:	e1a03000 	mov	r3, r0
40701ddc:	e1530002 	cmp	r3, r2
40701de0:	1a000000 	bne	40701de8 <ddrtr_memset+0x14>
40701de4:	e12fff1e 	bx	lr
40701de8:	e4c31001 	strb	r1, [r3], #1
40701dec:	eafffffa 	b	40701ddc <ddrtr_memset+0x8>

40701df0 <ddr_training_by_dmc>:
40701df0:	e5903070 	ldr	r3, [r0, #112]	; 0x70
40701df4:	e3530000 	cmp	r3, #0
40701df8:	1a000000 	bne	40701e00 <ddr_training_by_dmc+0x10>
40701dfc:	ea0007f2 	b	40703dcc <ddr_training_boot_func>
40701e00:	e3a00000 	mov	r0, #0
40701e04:	e12fff1e 	bx	lr

40701e08 <ddr_training_by_rank>:
40701e08:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40701e0c:	e3a05000 	mov	r5, #0
40701e10:	e5902040 	ldr	r2, [r0, #64]	; 0x40
40701e14:	e1a04000 	mov	r4, r0
40701e18:	e5901060 	ldr	r1, [r0, #96]	; 0x60
40701e1c:	e1a06005 	mov	r6, r5
40701e20:	e3a0703c 	mov	r7, #60	; 0x3c
40701e24:	e3a0800c 	mov	r8, #12
40701e28:	e5923048 	ldr	r3, [r2, #72]	; 0x48
40701e2c:	e3c3300f 	bic	r3, r3, #15
40701e30:	e1833001 	orr	r3, r3, r1
40701e34:	e5823048 	str	r3, [r2, #72]	; 0x48
40701e38:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40701e3c:	e0030397 	mul	r3, r7, r3
40701e40:	e0842003 	add	r2, r4, r3
40701e44:	e5922008 	ldr	r2, [r2, #8]
40701e48:	e1520005 	cmp	r2, r5
40701e4c:	8a000001 	bhi	40701e58 <ddr_training_by_rank+0x50>
40701e50:	e1a00006 	mov	r0, r6
40701e54:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40701e58:	e0233598 	mla	r3, r8, r5, r3
40701e5c:	e5845064 	str	r5, [r4, #100]	; 0x64
40701e60:	e1a00004 	mov	r0, r4
40701e64:	e2855001 	add	r5, r5, #1
40701e68:	e0843003 	add	r3, r4, r3
40701e6c:	e5932014 	ldr	r2, [r3, #20]
40701e70:	e5842044 	str	r2, [r4, #68]	; 0x44
40701e74:	e593301c 	ldr	r3, [r3, #28]
40701e78:	e584304c 	str	r3, [r4, #76]	; 0x4c
40701e7c:	ebffffdb 	bl	40701df0 <ddr_training_by_dmc>
40701e80:	e0866000 	add	r6, r6, r0
40701e84:	eaffffeb 	b	40701e38 <ddr_training_by_rank+0x30>

40701e88 <ddr_training_by_phy>:
40701e88:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40701e8c:	e3a07001 	mov	r7, #1
40701e90:	e590305c 	ldr	r3, [r0, #92]	; 0x5c
40701e94:	e3a0603c 	mov	r6, #60	; 0x3c
40701e98:	e3a05000 	mov	r5, #0
40701e9c:	e1a04000 	mov	r4, r0
40701ea0:	e1a07317 	lsl	r7, r7, r3
40701ea4:	e1a08005 	mov	r8, r5
40701ea8:	e0230396 	mla	r3, r6, r3, r0
40701eac:	e593a00c 	ldr	sl, [r3, #12]
40701eb0:	e155000a 	cmp	r5, sl
40701eb4:	1a000001 	bne	40701ec0 <ddr_training_by_phy+0x38>
40701eb8:	e1a00008 	mov	r0, r8
40701ebc:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40701ec0:	e594205c 	ldr	r2, [r4, #92]	; 0x5c
40701ec4:	e2853005 	add	r3, r5, #5
40701ec8:	e5845060 	str	r5, [r4, #96]	; 0x60
40701ecc:	e0020296 	mul	r2, r6, r2
40701ed0:	e0823183 	add	r3, r2, r3, lsl #3
40701ed4:	e0843003 	add	r3, r4, r3
40701ed8:	e5933004 	ldr	r3, [r3, #4]
40701edc:	e1170003 	tst	r7, r3
40701ee0:	e5843048 	str	r3, [r4, #72]	; 0x48
40701ee4:	0a000001 	beq	40701ef0 <ddr_training_by_phy+0x68>
40701ee8:	e2855001 	add	r5, r5, #1
40701eec:	eaffffef 	b	40701eb0 <ddr_training_by_phy+0x28>
40701ef0:	e1a00004 	mov	r0, r4
40701ef4:	ebffffc3 	bl	40701e08 <ddr_training_by_rank>
40701ef8:	e0888000 	add	r8, r8, r0
40701efc:	eafffff9 	b	40701ee8 <ddr_training_by_phy+0x60>

40701f00 <ddr_training_all>:
40701f00:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40701f04:	e3a04000 	mov	r4, #0
40701f08:	e1a05000 	mov	r5, r0
40701f0c:	e1a06004 	mov	r6, r4
40701f10:	e3a0703c 	mov	r7, #60	; 0x3c
40701f14:	e595303c 	ldr	r3, [r5, #60]	; 0x3c
40701f18:	e1530004 	cmp	r3, r4
40701f1c:	8a000001 	bhi	40701f28 <ddr_training_all+0x28>
40701f20:	e1a00006 	mov	r0, r6
40701f24:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40701f28:	e0030497 	mul	r3, r7, r4
40701f2c:	e585405c 	str	r4, [r5, #92]	; 0x5c
40701f30:	e1a00005 	mov	r0, r5
40701f34:	e2844001 	add	r4, r4, #1
40701f38:	e7953003 	ldr	r3, [r5, r3]
40701f3c:	e5853040 	str	r3, [r5, #64]	; 0x40
40701f40:	ebffffd0 	bl	40701e88 <ddr_training_by_phy>
40701f44:	e0866000 	add	r6, r6, r0
40701f48:	eafffff1 	b	40701f14 <ddr_training_all+0x14>

40701f4c <ddr_training_cfg_set_rank>:
40701f4c:	e3a03001 	mov	r3, #1
40701f50:	e580300c 	str	r3, [r0, #12]
40701f54:	e59f3030 	ldr	r3, [pc, #48]	; 40701f8c <ddr_training_cfg_set_rank+0x40>
40701f58:	e59320a0 	ldr	r2, [r3, #160]	; 0xa0
40701f5c:	e580202c 	str	r2, [r0, #44]	; 0x2c
40701f60:	e5932090 	ldr	r2, [r3, #144]	; 0x90
40701f64:	e5802030 	str	r2, [r0, #48]	; 0x30
40701f68:	e59320a4 	ldr	r2, [r3, #164]	; 0xa4
40701f6c:	e5802034 	str	r2, [r0, #52]	; 0x34
40701f70:	e5932094 	ldr	r2, [r3, #148]	; 0x94
40701f74:	e5802038 	str	r2, [r0, #56]	; 0x38
40701f78:	e5933094 	ldr	r3, [r3, #148]	; 0x94
40701f7c:	e3530000 	cmp	r3, #0
40701f80:	13a03002 	movne	r3, #2
40701f84:	1580300c 	strne	r3, [r0, #12]
40701f88:	e12fff1e 	bx	lr
40701f8c:	12020000 	.word	0x12020000

40701f90 <ddr_training_cfg_set_phy>:
40701f90:	e3a03001 	mov	r3, #1
40701f94:	e580303c 	str	r3, [r0, #60]	; 0x3c
40701f98:	e59f3010 	ldr	r3, [pc, #16]	; 40701fb0 <ddr_training_cfg_set_phy+0x20>
40701f9c:	e5803000 	str	r3, [r0]
40701fa0:	e593302c 	ldr	r3, [r3, #44]	; 0x2c
40701fa4:	e203300f 	and	r3, r3, #15
40701fa8:	e5803004 	str	r3, [r0, #4]
40701fac:	e12fff1e 	bx	lr
40701fb0:	120dc000 	.word	0x120dc000

40701fb4 <ddr_training_set_timing>:
40701fb4:	e30033e9 	movw	r3, #1001	; 0x3e9
40701fb8:	e2533001 	subs	r3, r3, #1
40701fbc:	1a000004 	bne	40701fd4 <ddr_training_set_timing+0x20>
40701fc0:	e30033e9 	movw	r3, #1001	; 0x3e9
40701fc4:	e5801108 	str	r1, [r0, #264]	; 0x108
40701fc8:	e2533001 	subs	r3, r3, #1
40701fcc:	1a000002 	bne	40701fdc <ddr_training_set_timing+0x28>
40701fd0:	e12fff1e 	bx	lr
40701fd4:	e320f000 	nop	{0}
40701fd8:	eafffff6 	b	40701fb8 <ddr_training_set_timing+0x4>
40701fdc:	e320f000 	nop	{0}
40701fe0:	eafffff8 	b	40701fc8 <ddr_training_set_timing+0x14>

40701fe4 <ddr_vref_set>:
40701fe4:	e5903050 	ldr	r3, [r0, #80]	; 0x50
40701fe8:	e3530001 	cmp	r3, #1
40701fec:	1a000010 	bne	40702034 <ddr_vref_set+0x50>
40701ff0:	e5903060 	ldr	r3, [r0, #96]	; 0x60
40701ff4:	e5902040 	ldr	r2, [r0, #64]	; 0x40
40701ff8:	e590c054 	ldr	ip, [r0, #84]	; 0x54
40701ffc:	e2822f9d 	add	r2, r2, #628	; 0x274
40702000:	e0822503 	add	r2, r2, r3, lsl #10
40702004:	e792338c 	ldr	r3, [r2, ip, lsl #7]
40702008:	e3c3301f 	bic	r3, r3, #31
4070200c:	e1831001 	orr	r1, r3, r1
40702010:	e782138c 	str	r1, [r2, ip, lsl #7]
40702014:	e5902060 	ldr	r2, [r0, #96]	; 0x60
40702018:	e5903040 	ldr	r3, [r0, #64]	; 0x40
4070201c:	e2833f9d 	add	r3, r3, #628	; 0x274
40702020:	e0833502 	add	r3, r3, r2, lsl #10
40702024:	e5902054 	ldr	r2, [r0, #84]	; 0x54
40702028:	e2822001 	add	r2, r2, #1
4070202c:	e7831382 	str	r1, [r3, r2, lsl #7]
40702030:	e12fff1e 	bx	lr
40702034:	e1a02000 	mov	r2, r0
40702038:	e92d4070 	push	{r4, r5, r6, lr}
4070203c:	e1a04001 	mov	r4, r1
40702040:	e5900044 	ldr	r0, [r0, #68]	; 0x44
40702044:	e5905108 	ldr	r5, [r0, #264]	; 0x108
40702048:	e3c51eff 	bic	r1, r5, #4080	; 0xff0
4070204c:	e3c1100f 	bic	r1, r1, #15
40702050:	ebffffd7 	bl	40701fb4 <ddr_training_set_timing>
40702054:	e5921040 	ldr	r1, [r2, #64]	; 0x40
40702058:	e59130c0 	ldr	r3, [r1, #192]	; 0xc0
4070205c:	e3833102 	orr	r3, r3, #-2147483648	; 0x80000000
40702060:	e58130c0 	str	r3, [r1, #192]	; 0xc0
40702064:	e5920040 	ldr	r0, [r2, #64]	; 0x40
40702068:	e592c054 	ldr	ip, [r2, #84]	; 0x54
4070206c:	e2803e27 	add	r3, r0, #624	; 0x270
40702070:	e59010c4 	ldr	r1, [r0, #196]	; 0xc4
40702074:	e793338c 	ldr	r3, [r3, ip, lsl #7]
40702078:	e381c102 	orr	ip, r1, #-2147483648	; 0x80000000
4070207c:	e580c0c4 	str	ip, [r0, #196]	; 0xc4
40702080:	e5920040 	ldr	r0, [r2, #64]	; 0x40
40702084:	e3c3303f 	bic	r3, r3, #63	; 0x3f
40702088:	e592c054 	ldr	ip, [r2, #84]	; 0x54
4070208c:	e1833004 	orr	r3, r3, r4
40702090:	e2800e27 	add	r0, r0, #624	; 0x270
40702094:	e780338c 	str	r3, [r0, ip, lsl #7]
40702098:	e59f00f8 	ldr	r0, [pc, #248]	; 40702198 <ddr_vref_set+0x1b4>
4070209c:	e5923040 	ldr	r3, [r2, #64]	; 0x40
407020a0:	e5830004 	str	r0, [r3, #4]
407020a4:	e5923040 	ldr	r3, [r2, #64]	; 0x40
407020a8:	e283c004 	add	ip, r3, #4
407020ac:	e59c0000 	ldr	r0, [ip]
407020b0:	e3100001 	tst	r0, #1
407020b4:	1afffffc 	bne	407020ac <ddr_vref_set+0xc8>
407020b8:	e3c11102 	bic	r1, r1, #-2147483648	; 0x80000000
407020bc:	e58310c4 	str	r1, [r3, #196]	; 0xc4
407020c0:	e5920040 	ldr	r0, [r2, #64]	; 0x40
407020c4:	e592c054 	ldr	ip, [r2, #84]	; 0x54
407020c8:	e2803e27 	add	r3, r0, #624	; 0x270
407020cc:	e59010c4 	ldr	r1, [r0, #196]	; 0xc4
407020d0:	e793338c 	ldr	r3, [r3, ip, lsl #7]
407020d4:	e381c102 	orr	ip, r1, #-2147483648	; 0x80000000
407020d8:	e580c0c4 	str	ip, [r0, #196]	; 0xc4
407020dc:	e5920040 	ldr	r0, [r2, #64]	; 0x40
407020e0:	e3c3303f 	bic	r3, r3, #63	; 0x3f
407020e4:	e592c054 	ldr	ip, [r2, #84]	; 0x54
407020e8:	e1833004 	orr	r3, r3, r4
407020ec:	e2800e27 	add	r0, r0, #624	; 0x270
407020f0:	e780338c 	str	r3, [r0, ip, lsl #7]
407020f4:	e59f009c 	ldr	r0, [pc, #156]	; 40702198 <ddr_vref_set+0x1b4>
407020f8:	e5923040 	ldr	r3, [r2, #64]	; 0x40
407020fc:	e5830004 	str	r0, [r3, #4]
40702100:	e5923040 	ldr	r3, [r2, #64]	; 0x40
40702104:	e283c004 	add	ip, r3, #4
40702108:	e59c0000 	ldr	r0, [ip]
4070210c:	e3100001 	tst	r0, #1
40702110:	1afffffc 	bne	40702108 <ddr_vref_set+0x124>
40702114:	e3c11102 	bic	r1, r1, #-2147483648	; 0x80000000
40702118:	e58310c4 	str	r1, [r3, #196]	; 0xc4
4070211c:	e5921040 	ldr	r1, [r2, #64]	; 0x40
40702120:	e59130c0 	ldr	r3, [r1, #192]	; 0xc0
40702124:	e3c33102 	bic	r3, r3, #-2147483648	; 0x80000000
40702128:	e58130c0 	str	r3, [r1, #192]	; 0xc0
4070212c:	e5920040 	ldr	r0, [r2, #64]	; 0x40
40702130:	e592c054 	ldr	ip, [r2, #84]	; 0x54
40702134:	e2801e27 	add	r1, r0, #624	; 0x270
40702138:	e59030c4 	ldr	r3, [r0, #196]	; 0xc4
4070213c:	e791138c 	ldr	r1, [r1, ip, lsl #7]
40702140:	e383c102 	orr	ip, r3, #-2147483648	; 0x80000000
40702144:	e580c0c4 	str	ip, [r0, #196]	; 0xc4
40702148:	e5920040 	ldr	r0, [r2, #64]	; 0x40
4070214c:	e3c1103f 	bic	r1, r1, #63	; 0x3f
40702150:	e592c054 	ldr	ip, [r2, #84]	; 0x54
40702154:	e1814004 	orr	r4, r1, r4
40702158:	e2800e27 	add	r0, r0, #624	; 0x270
4070215c:	e780438c 	str	r4, [r0, ip, lsl #7]
40702160:	e59f0030 	ldr	r0, [pc, #48]	; 40702198 <ddr_vref_set+0x1b4>
40702164:	e5921040 	ldr	r1, [r2, #64]	; 0x40
40702168:	e5810004 	str	r0, [r1, #4]
4070216c:	e5921040 	ldr	r1, [r2, #64]	; 0x40
40702170:	e281c004 	add	ip, r1, #4
40702174:	e59c0000 	ldr	r0, [ip]
40702178:	e3100001 	tst	r0, #1
4070217c:	1afffffc 	bne	40702174 <ddr_vref_set+0x190>
40702180:	e3c33102 	bic	r3, r3, #-2147483648	; 0x80000000
40702184:	e58130c4 	str	r3, [r1, #196]	; 0xc4
40702188:	e1a01005 	mov	r1, r5
4070218c:	e5920044 	ldr	r0, [r2, #68]	; 0x44
40702190:	e8bd4070 	pop	{r4, r5, r6, lr}
40702194:	eaffff86 	b	40701fb4 <ddr_training_set_timing>
40702198:	00040001 	.word	0x00040001

4070219c <ddr_training_stat>:
4070219c:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
407021a0:	e1a06003 	mov	r6, r3
407021a4:	e1a04000 	mov	r4, r0
407021a8:	e1a05001 	mov	r5, r1
407021ac:	e1a07002 	mov	r7, r2
407021b0:	eb000773 	bl	40703f84 <ddr_training_error>
407021b4:	e59f3040 	ldr	r3, [pc, #64]	; 407021fc <ddr_training_stat+0x60>
407021b8:	e59330b0 	ldr	r3, [r3, #176]	; 0xb0
407021bc:	e3530000 	cmp	r3, #0
407021c0:	18bd81f0 	popne	{r4, r5, r6, r7, r8, pc}
407021c4:	e3550000 	cmp	r5, #0
407021c8:	0a000004 	beq	407021e0 <ddr_training_stat+0x44>
407021cc:	e59f302c 	ldr	r3, [pc, #44]	; 40702200 <ddr_training_stat+0x64>
407021d0:	e1550003 	cmp	r5, r3
407021d4:	03a05a01 	moveq	r5, #4096	; 0x1000
407021d8:	13a05a02 	movne	r5, #8192	; 0x2000
407021dc:	e1844005 	orr	r4, r4, r5
407021e0:	e59f3014 	ldr	r3, [pc, #20]	; 407021fc <ddr_training_stat+0x60>
407021e4:	e3770001 	cmn	r7, #1
407021e8:	11844c07 	orrne	r4, r4, r7, lsl #24
407021ec:	e3760001 	cmn	r6, #1
407021f0:	11844a06 	orrne	r4, r4, r6, lsl #20
407021f4:	e58340b0 	str	r4, [r3, #176]	; 0xb0
407021f8:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
407021fc:	12020000 	.word	0x12020000
40702200:	120dc000 	.word	0x120dc000

40702204 <ddr_hw_training_process>:
40702204:	e92d4df3 	push	{r0, r1, r4, r5, r6, r7, r8, sl, fp, lr}
40702208:	e2516000 	subs	r6, r1, #0
4070220c:	e5905040 	ldr	r5, [r0, #64]	; 0x40
40702210:	e2853004 	add	r3, r5, #4
40702214:	e58d3004 	str	r3, [sp, #4]
40702218:	e5952004 	ldr	r2, [r5, #4]
4070221c:	1a000002 	bne	4070222c <ddr_hw_training_process+0x28>
40702220:	e3a00000 	mov	r0, #0
40702224:	e28dd008 	add	sp, sp, #8
40702228:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
4070222c:	e3160a01 	tst	r6, #4096	; 0x1000
40702230:	e3863001 	orr	r3, r6, #1
40702234:	e1833002 	orr	r3, r3, r2
40702238:	e1a07000 	mov	r7, r0
4070223c:	e5853004 	str	r3, [r5, #4]
40702240:	1a00000d 	bne	4070227c <ddr_hw_training_process+0x78>
40702244:	e3a04000 	mov	r4, #0
40702248:	e59d3004 	ldr	r3, [sp, #4]
4070224c:	e2844001 	add	r4, r4, #1
40702250:	e5933000 	ldr	r3, [r3]
40702254:	e3130001 	tst	r3, #1
40702258:	0a00002d 	beq	40702314 <ddr_hw_training_process+0x110>
4070225c:	e3740001 	cmn	r4, #1
40702260:	1afffff8 	bne	40702248 <ddr_hw_training_process+0x44>
40702264:	e5953008 	ldr	r3, [r5, #8]
40702268:	e1a02006 	mov	r2, r6
4070226c:	e1a01005 	mov	r1, r5
40702270:	e3a00010 	mov	r0, #16
40702274:	ebffffc8 	bl	4070219c <ddr_training_stat>
40702278:	ea00000b 	b	407022ac <ddr_hw_training_process+0xa8>
4070227c:	e590305c 	ldr	r3, [r0, #92]	; 0x5c
40702280:	e3a0203c 	mov	r2, #60	; 0x3c
40702284:	e3a08000 	mov	r8, #0
40702288:	e1a0a008 	mov	sl, r8
4070228c:	e0030392 	mul	r3, r2, r3
40702290:	e080b003 	add	fp, r0, r3
40702294:	e58d3000 	str	r3, [sp]
40702298:	e59b3008 	ldr	r3, [fp, #8]
4070229c:	e1530008 	cmp	r3, r8
407022a0:	8a000003 	bhi	407022b4 <ddr_hw_training_process+0xb0>
407022a4:	e35a0000 	cmp	sl, #0
407022a8:	0affffe5 	beq	40702244 <ddr_hw_training_process+0x40>
407022ac:	e3e00000 	mvn	r0, #0
407022b0:	eaffffdb 	b	40702224 <ddr_hw_training_process+0x20>
407022b4:	e59d2000 	ldr	r2, [sp]
407022b8:	e3a0300c 	mov	r3, #12
407022bc:	e3a04000 	mov	r4, #0
407022c0:	e0232893 	mla	r3, r3, r8, r2
407022c4:	e0873003 	add	r3, r7, r3
407022c8:	e5932014 	ldr	r2, [r3, #20]
407022cc:	e3a03002 	mov	r3, #2
407022d0:	e5823000 	str	r3, [r2]
407022d4:	e5923294 	ldr	r3, [r2, #660]	; 0x294
407022d8:	e2844001 	add	r4, r4, #1
407022dc:	e2133001 	ands	r3, r3, #1
407022e0:	0a000007 	beq	40702304 <ddr_hw_training_process+0x100>
407022e4:	e3740001 	cmn	r4, #1
407022e8:	1afffff9 	bne	407022d4 <ddr_hw_training_process+0xd0>
407022ec:	e1a03004 	mov	r3, r4
407022f0:	e1a02004 	mov	r2, r4
407022f4:	e1a01004 	mov	r1, r4
407022f8:	e3a00010 	mov	r0, #16
407022fc:	ebffffa6 	bl	4070219c <ddr_training_stat>
40702300:	ea000000 	b	40702308 <ddr_hw_training_process+0x104>
40702304:	e1a04003 	mov	r4, r3
40702308:	e08aa004 	add	sl, sl, r4
4070230c:	e2888001 	add	r8, r8, #1
40702310:	eaffffe0 	b	40702298 <ddr_hw_training_process+0x94>
40702314:	e5953008 	ldr	r3, [r5, #8]
40702318:	e3530000 	cmp	r3, #0
4070231c:	0affffbf 	beq	40702220 <ddr_hw_training_process+0x1c>
40702320:	eaffffcf 	b	40702264 <ddr_hw_training_process+0x60>

40702324 <ddr_training_check_bypass>:
40702324:	e5903048 	ldr	r3, [r0, #72]	; 0x48
40702328:	e1110003 	tst	r1, r3
4070232c:	13a00001 	movne	r0, #1
40702330:	03a00000 	moveq	r0, #0
40702334:	e12fff1e 	bx	lr

40702338 <ddr_training_phy_disable>:
40702338:	e3a00000 	mov	r0, #0
4070233c:	e12fff1e 	bx	lr

40702340 <ddr_training_switch_axi>:
40702340:	e590105c 	ldr	r1, [r0, #92]	; 0x5c
40702344:	e3a0303c 	mov	r3, #60	; 0x3c
40702348:	e59fc054 	ldr	ip, [pc, #84]	; 407023a4 <ddr_training_switch_axi+0x64>
4070234c:	e0230193 	mla	r3, r3, r1, r0
40702350:	e59c2104 	ldr	r2, [ip, #260]	; 0x104
40702354:	e3c2200f 	bic	r2, r2, #15
40702358:	e3822004 	orr	r2, r2, #4
4070235c:	e5933004 	ldr	r3, [r3, #4]
40702360:	e3530006 	cmp	r3, #6
40702364:	05903064 	ldreq	r3, [r0, #100]	; 0x64
40702368:	00831081 	addeq	r1, r3, r1, lsl #1
4070236c:	e1822001 	orr	r2, r2, r1
40702370:	e58c2104 	str	r2, [ip, #260]	; 0x104
40702374:	e59c3114 	ldr	r3, [ip, #276]	; 0x114
40702378:	e3c3300f 	bic	r3, r3, #15
4070237c:	e3833004 	orr	r3, r3, #4
40702380:	e1833001 	orr	r3, r3, r1
40702384:	e58c3114 	str	r3, [ip, #276]	; 0x114
40702388:	e5903060 	ldr	r3, [r0, #96]	; 0x60
4070238c:	e3530001 	cmp	r3, #1
40702390:	05902044 	ldreq	r2, [r0, #68]	; 0x44
40702394:	05923060 	ldreq	r3, [r2, #96]	; 0x60
40702398:	03c33007 	biceq	r3, r3, #7
4070239c:	05823060 	streq	r3, [r2, #96]	; 0x60
407023a0:	e12fff1e 	bx	lr
407023a4:	120d0000 	.word	0x120d0000

407023a8 <ddr_phy_cfg_update>:
407023a8:	e5903070 	ldr	r3, [r0, #112]	; 0x70
407023ac:	e3832702 	orr	r2, r3, #524288	; 0x80000
407023b0:	e3c33702 	bic	r3, r3, #524288	; 0x80000
407023b4:	e5802070 	str	r2, [r0, #112]	; 0x70
407023b8:	e5803070 	str	r3, [r0, #112]	; 0x70
407023bc:	e5903004 	ldr	r3, [r0, #4]
407023c0:	e3832902 	orr	r2, r3, #32768	; 0x8000
407023c4:	e3c33902 	bic	r3, r3, #32768	; 0x8000
407023c8:	e5802004 	str	r2, [r0, #4]
407023cc:	e5803004 	str	r3, [r0, #4]
407023d0:	f57ff04f 	dsb	sy
407023d4:	e12fff1e 	bx	lr

407023d8 <ddr_training_save_reg>:
407023d8:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
407023dc:	e1a04001 	mov	r4, r1
407023e0:	e5906044 	ldr	r6, [r0, #68]	; 0x44
407023e4:	e3017064 	movw	r7, #4196	; 0x1064
407023e8:	e5905040 	ldr	r5, [r0, #64]	; 0x40
407023ec:	e3520c01 	cmp	r2, #256	; 0x100
407023f0:	e5961108 	ldr	r1, [r6, #264]	; 0x108
407023f4:	e5841000 	str	r1, [r4]
407023f8:	e5963028 	ldr	r3, [r6, #40]	; 0x28
407023fc:	e5843004 	str	r3, [r4, #4]
40702400:	e5953070 	ldr	r3, [r5, #112]	; 0x70
40702404:	e5843010 	str	r3, [r4, #16]
40702408:	e7953007 	ldr	r3, [r5, r7]
4070240c:	e5843014 	str	r3, [r4, #20]
40702410:	e7953007 	ldr	r3, [r5, r7]
40702414:	e5843014 	str	r3, [r4, #20]
40702418:	0a000022 	beq	407024a8 <ddr_training_save_reg+0xd0>
4070241c:	8a00001d 	bhi	40702498 <ddr_training_save_reg+0xc0>
40702420:	e3520010 	cmp	r2, #16
40702424:	1a000003 	bne	40702438 <ddr_training_save_reg+0x60>
40702428:	e3c11eff 	bic	r1, r1, #4080	; 0xff0
4070242c:	e1a00006 	mov	r0, r6
40702430:	e3c1100f 	bic	r1, r1, #15
40702434:	ebfffede 	bl	40701fb4 <ddr_training_set_timing>
40702438:	e5943004 	ldr	r3, [r4, #4]
4070243c:	e1a00004 	mov	r0, r4
40702440:	e3c33001 	bic	r3, r3, #1
40702444:	e5863028 	str	r3, [r6, #40]	; 0x28
40702448:	e5943010 	ldr	r3, [r4, #16]
4070244c:	e3c33801 	bic	r3, r3, #65536	; 0x10000
40702450:	e5853070 	str	r3, [r5, #112]	; 0x70
40702454:	e5953084 	ldr	r3, [r5, #132]	; 0x84
40702458:	e5843018 	str	r3, [r4, #24]
4070245c:	e3c33407 	bic	r3, r3, #117440512	; 0x7000000
40702460:	e5853084 	str	r3, [r5, #132]	; 0x84
40702464:	e59f305c 	ldr	r3, [pc, #92]	; 407024c8 <ddr_training_save_reg+0xf0>
40702468:	e5931104 	ldr	r1, [r3, #260]	; 0x104
4070246c:	e584102c 	str	r1, [r4, #44]	; 0x2c
40702470:	e1a01002 	mov	r1, r2
40702474:	e5933114 	ldr	r3, [r3, #276]	; 0x114
40702478:	e5843030 	str	r3, [r4, #48]	; 0x30
4070247c:	e5963060 	ldr	r3, [r6, #96]	; 0x60
40702480:	e5843034 	str	r3, [r4, #52]	; 0x34
40702484:	eb0006e9 	bl	40704030 <ddr_training_save_reg_custom>
40702488:	e1a00005 	mov	r0, r5
4070248c:	ebffffc5 	bl	407023a8 <ddr_phy_cfg_update>
40702490:	f57ff04f 	dsb	sy
40702494:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40702498:	e3520601 	cmp	r2, #1048576	; 0x100000
4070249c:	0a000005 	beq	407024b8 <ddr_training_save_reg+0xe0>
407024a0:	e3520502 	cmp	r2, #8388608	; 0x800000
407024a4:	eaffffde 	b	40702424 <ddr_training_save_reg+0x4c>
407024a8:	e3c11eff 	bic	r1, r1, #4080	; 0xff0
407024ac:	e1a00006 	mov	r0, r6
407024b0:	e3c1100f 	bic	r1, r1, #15
407024b4:	ebfffebe 	bl	40701fb4 <ddr_training_set_timing>
407024b8:	e595302c 	ldr	r3, [r5, #44]	; 0x2c
407024bc:	e2133020 	ands	r3, r3, #32
407024c0:	07853007 	streq	r3, [r5, r7]
407024c4:	eaffffdb 	b	40702438 <ddr_training_save_reg+0x60>
407024c8:	120d0000 	.word	0x120d0000

407024cc <ddr_training_restore_reg>:
407024cc:	e92d4070 	push	{r4, r5, r6, lr}
407024d0:	e1a02001 	mov	r2, r1
407024d4:	e5905044 	ldr	r5, [r0, #68]	; 0x44
407024d8:	e5904040 	ldr	r4, [r0, #64]	; 0x40
407024dc:	e5911000 	ldr	r1, [r1]
407024e0:	e1a00005 	mov	r0, r5
407024e4:	ebfffeb2 	bl	40701fb4 <ddr_training_set_timing>
407024e8:	e5923004 	ldr	r3, [r2, #4]
407024ec:	e1a00002 	mov	r0, r2
407024f0:	e5853028 	str	r3, [r5, #40]	; 0x28
407024f4:	e5923010 	ldr	r3, [r2, #16]
407024f8:	e5843070 	str	r3, [r4, #112]	; 0x70
407024fc:	e594302c 	ldr	r3, [r4, #44]	; 0x2c
40702500:	e3130020 	tst	r3, #32
40702504:	05921014 	ldreq	r1, [r2, #20]
40702508:	03013064 	movweq	r3, #4196	; 0x1064
4070250c:	07841003 	streq	r1, [r4, r3]
40702510:	e5923018 	ldr	r3, [r2, #24]
40702514:	e5843084 	str	r3, [r4, #132]	; 0x84
40702518:	e59f3028 	ldr	r3, [pc, #40]	; 40702548 <ddr_training_restore_reg+0x7c>
4070251c:	e592102c 	ldr	r1, [r2, #44]	; 0x2c
40702520:	e5831104 	str	r1, [r3, #260]	; 0x104
40702524:	e5921030 	ldr	r1, [r2, #48]	; 0x30
40702528:	e5831114 	str	r1, [r3, #276]	; 0x114
4070252c:	e5923034 	ldr	r3, [r2, #52]	; 0x34
40702530:	e5853060 	str	r3, [r5, #96]	; 0x60
40702534:	eb0006be 	bl	40704034 <ddr_training_restore_reg_custom>
40702538:	e1a00004 	mov	r0, r4
4070253c:	ebffff99 	bl	407023a8 <ddr_phy_cfg_update>
40702540:	f57ff04f 	dsb	sy
40702544:	e8bd8070 	pop	{r4, r5, r6, pc}
40702548:	120d0000 	.word	0x120d0000

4070254c <ddr_phy_set_dq_bdl>:
4070254c:	e92d4010 	push	{r4, lr}
40702550:	e1a0e000 	mov	lr, r0
40702554:	e59ec054 	ldr	ip, [lr, #84]	; 0x54
40702558:	e59e3060 	ldr	r3, [lr, #96]	; 0x60
4070255c:	e59e2058 	ldr	r2, [lr, #88]	; 0x58
40702560:	e59ee050 	ldr	lr, [lr, #80]	; 0x50
40702564:	e1a0c38c 	lsl	ip, ip, #7
40702568:	e1a03503 	lsl	r3, r3, #10
4070256c:	e5900040 	ldr	r0, [r0, #64]	; 0x40
40702570:	e35e0002 	cmp	lr, #2
40702574:	e2024007 	and	r4, r2, #7
40702578:	e083300c 	add	r3, r3, ip
4070257c:	1a00000c 	bne	407025b4 <ddr_phy_set_dq_bdl+0x68>
40702580:	e3540003 	cmp	r4, #3
40702584:	92833e21 	addls	r3, r3, #528	; 0x210
40702588:	82833f85 	addhi	r3, r3, #532	; 0x214
4070258c:	e793c000 	ldr	ip, [r3, r0]
40702590:	e1a02182 	lsl	r2, r2, #3
40702594:	e2022018 	and	r2, r2, #24
40702598:	e3a0e0ff 	mov	lr, #255	; 0xff
4070259c:	e201107f 	and	r1, r1, #127	; 0x7f
407025a0:	e1ccc21e 	bic	ip, ip, lr, lsl r2
407025a4:	e18c2211 	orr	r2, ip, r1, lsl r2
407025a8:	e7832000 	str	r2, [r3, r0]
407025ac:	e8bd4010 	pop	{r4, lr}
407025b0:	eaffff7c 	b	407023a8 <ddr_phy_cfg_update>
407025b4:	e3540003 	cmp	r4, #3
407025b8:	92833f87 	addls	r3, r3, #540	; 0x21c
407025bc:	82833e22 	addhi	r3, r3, #544	; 0x220
407025c0:	eafffff1 	b	4070258c <ddr_phy_set_dq_bdl+0x40>

407025c4 <ddr_phy_get_dq_bdl>:
407025c4:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
407025c8:	e5901054 	ldr	r1, [r0, #84]	; 0x54
407025cc:	e5903060 	ldr	r3, [r0, #96]	; 0x60
407025d0:	e590e050 	ldr	lr, [r0, #80]	; 0x50
407025d4:	e5902058 	ldr	r2, [r0, #88]	; 0x58
407025d8:	e1a01381 	lsl	r1, r1, #7
407025dc:	e35e0002 	cmp	lr, #2
407025e0:	e1a03503 	lsl	r3, r3, #10
407025e4:	e202c007 	and	ip, r2, #7
407025e8:	e0833001 	add	r3, r3, r1
407025ec:	1a000009 	bne	40702618 <ddr_phy_get_dq_bdl+0x54>
407025f0:	e35c0003 	cmp	ip, #3
407025f4:	92833e21 	addls	r3, r3, #528	; 0x210
407025f8:	82833f85 	addhi	r3, r3, #532	; 0x214
407025fc:	e5901040 	ldr	r1, [r0, #64]	; 0x40
40702600:	e1a02182 	lsl	r2, r2, #3
40702604:	e2022018 	and	r2, r2, #24
40702608:	e7930001 	ldr	r0, [r3, r1]
4070260c:	e1a00230 	lsr	r0, r0, r2
40702610:	e200007f 	and	r0, r0, #127	; 0x7f
40702614:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)
40702618:	e35c0003 	cmp	ip, #3
4070261c:	92833f87 	addls	r3, r3, #540	; 0x21c
40702620:	82833e22 	addhi	r3, r3, #544	; 0x220
40702624:	eafffff4 	b	407025fc <ddr_phy_get_dq_bdl+0x38>

40702628 <ddr_rdqs_sync_rank_rdq>:
40702628:	e92d4070 	push	{r4, r5, r6, lr}
4070262c:	e1a04000 	mov	r4, r0
40702630:	e5902060 	ldr	r2, [r0, #96]	; 0x60
40702634:	e1a05001 	mov	r5, r1
40702638:	e5903040 	ldr	r3, [r0, #64]	; 0x40
4070263c:	e3a06000 	mov	r6, #0
40702640:	e5900054 	ldr	r0, [r0, #84]	; 0x54
40702644:	e2833f89 	add	r3, r3, #548	; 0x224
40702648:	e0833502 	add	r3, r3, r2, lsl #10
4070264c:	e7932380 	ldr	r2, [r3, r0, lsl #7]
40702650:	e202107f 	and	r1, r2, #127	; 0x7f
40702654:	e3c2207f 	bic	r2, r2, #127	; 0x7f
40702658:	e0851001 	add	r1, r5, r1
4070265c:	e6e71011 	usat	r1, #7, r1
40702660:	e1822001 	orr	r2, r2, r1
40702664:	e7832380 	str	r2, [r3, r0, lsl #7]
40702668:	e5846058 	str	r6, [r4, #88]	; 0x58
4070266c:	e1a00004 	mov	r0, r4
40702670:	ebffffd3 	bl	407025c4 <ddr_phy_get_dq_bdl>
40702674:	e2866001 	add	r6, r6, #1
40702678:	e0851000 	add	r1, r5, r0
4070267c:	e1a00004 	mov	r0, r4
40702680:	e6e71011 	usat	r1, #7, r1
40702684:	ebffffb0 	bl	4070254c <ddr_phy_set_dq_bdl>
40702688:	e3560008 	cmp	r6, #8
4070268c:	1afffff5 	bne	40702668 <ddr_rdqs_sync_rank_rdq+0x40>
40702690:	e8bd8070 	pop	{r4, r5, r6, pc}

40702694 <ddr_adjust_set_val>:
40702694:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40702698:	e1a04000 	mov	r4, r0
4070269c:	e5903050 	ldr	r3, [r0, #80]	; 0x50
407026a0:	e1a07001 	mov	r7, r1
407026a4:	e5902054 	ldr	r2, [r0, #84]	; 0x54
407026a8:	e3530001 	cmp	r3, #1
407026ac:	e5908060 	ldr	r8, [r0, #96]	; 0x60
407026b0:	e5903040 	ldr	r3, [r0, #64]	; 0x40
407026b4:	1a00001c 	bne	4070272c <ddr_adjust_set_val+0x98>
407026b8:	e2833f8b 	add	r3, r3, #556	; 0x22c
407026bc:	e7935382 	ldr	r5, [r3, r2, lsl #7]
407026c0:	e7936382 	ldr	r6, [r3, r2, lsl #7]
407026c4:	e7e86056 	ubfx	r6, r6, #0, #9
407026c8:	e0416006 	sub	r6, r1, r6
407026cc:	e1a01006 	mov	r1, r6
407026d0:	ebffffd4 	bl	40702628 <ddr_rdqs_sync_rank_rdq>
407026d4:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
407026d8:	e3a0203c 	mov	r2, #60	; 0x3c
407026dc:	e0234392 	mla	r3, r2, r3, r4
407026e0:	e593300c 	ldr	r3, [r3, #12]
407026e4:	e3530001 	cmp	r3, #1
407026e8:	0a000005 	beq	40702704 <ddr_adjust_set_val+0x70>
407026ec:	e2683001 	rsb	r3, r8, #1
407026f0:	e1a01006 	mov	r1, r6
407026f4:	e5843060 	str	r3, [r4, #96]	; 0x60
407026f8:	e1a00004 	mov	r0, r4
407026fc:	ebffffc9 	bl	40702628 <ddr_rdqs_sync_rank_rdq>
40702700:	e5848060 	str	r8, [r4, #96]	; 0x60
40702704:	e5943040 	ldr	r3, [r4, #64]	; 0x40
40702708:	e3c51f7f 	bic	r1, r5, #508	; 0x1fc
4070270c:	e3c11003 	bic	r1, r1, #3
40702710:	e5942054 	ldr	r2, [r4, #84]	; 0x54
40702714:	e2833f8b 	add	r3, r3, #556	; 0x22c
40702718:	e1811007 	orr	r1, r1, r7
4070271c:	e7831382 	str	r1, [r3, r2, lsl #7]
40702720:	e5940040 	ldr	r0, [r4, #64]	; 0x40
40702724:	e8bd41f0 	pop	{r4, r5, r6, r7, r8, lr}
40702728:	eaffff1e 	b	407023a8 <ddr_phy_cfg_update>
4070272c:	e2833f8d 	add	r3, r3, #564	; 0x234
40702730:	e0833508 	add	r3, r3, r8, lsl #10
40702734:	e7931382 	ldr	r1, [r3, r2, lsl #7]
40702738:	e3c11c1f 	bic	r1, r1, #7936	; 0x1f00
4070273c:	e1811407 	orr	r1, r1, r7, lsl #8
40702740:	eafffff5 	b	4070271c <ddr_adjust_set_val+0x88>

40702744 <ddr_phy_get_byte_num>:
40702744:	e5900050 	ldr	r0, [r0, #80]	; 0x50
40702748:	e1a001a0 	lsr	r0, r0, #3
4070274c:	e2000006 	and	r0, r0, #6
40702750:	e3500004 	cmp	r0, #4
40702754:	23a00004 	movcs	r0, #4
40702758:	e12fff1e 	bx	lr

4070275c <ddr_training_cfg_set_dmc>:
4070275c:	e92d4010 	push	{r4, lr}
40702760:	e1a03000 	mov	r3, r0
40702764:	e5902004 	ldr	r2, [r0, #4]
40702768:	e59f1078 	ldr	r1, [pc, #120]	; 407027e8 <ddr_training_cfg_set_dmc+0x8c>
4070276c:	e3520006 	cmp	r2, #6
40702770:	e59f2074 	ldr	r2, [pc, #116]	; 407027ec <ddr_training_cfg_set_dmc+0x90>
40702774:	1a000012 	bne	407027c4 <ddr_training_cfg_set_dmc+0x68>
40702778:	e3a00002 	mov	r0, #2
4070277c:	e5830008 	str	r0, [r3, #8]
40702780:	e59110a8 	ldr	r1, [r1, #168]	; 0xa8
40702784:	e5832014 	str	r2, [r3, #20]
40702788:	e6ff0071 	uxth	r0, r1
4070278c:	e583001c 	str	r0, [r3, #28]
40702790:	e1a00002 	mov	r0, r2
40702794:	ebffffea 	bl	40702744 <ddr_phy_get_byte_num>
40702798:	e5830018 	str	r0, [r3, #24]
4070279c:	e1a01821 	lsr	r1, r1, #16
407027a0:	e5832020 	str	r2, [r3, #32]
407027a4:	e1a00002 	mov	r0, r2
407027a8:	e5831028 	str	r1, [r3, #40]	; 0x28
407027ac:	ebffffe4 	bl	40702744 <ddr_phy_get_byte_num>
407027b0:	e5932018 	ldr	r2, [r3, #24]
407027b4:	e5830024 	str	r0, [r3, #36]	; 0x24
407027b8:	e0820000 	add	r0, r2, r0
407027bc:	e5830010 	str	r0, [r3, #16]
407027c0:	e8bd8010 	pop	{r4, pc}
407027c4:	e3a00001 	mov	r0, #1
407027c8:	e5832014 	str	r2, [r3, #20]
407027cc:	e5830008 	str	r0, [r3, #8]
407027d0:	e1a00002 	mov	r0, r2
407027d4:	e59110a8 	ldr	r1, [r1, #168]	; 0xa8
407027d8:	e583101c 	str	r1, [r3, #28]
407027dc:	ebffffd8 	bl	40702744 <ddr_phy_get_byte_num>
407027e0:	e5830018 	str	r0, [r3, #24]
407027e4:	eafffff4 	b	407027bc <ddr_training_cfg_set_dmc+0x60>
407027e8:	12020000 	.word	0x12020000
407027ec:	120d8000 	.word	0x120d8000

407027f0 <ddr_training_cfg_init>:
407027f0:	e92d4010 	push	{r4, lr}
407027f4:	e3a02078 	mov	r2, #120	; 0x78
407027f8:	e1a04000 	mov	r4, r0
407027fc:	e3a01000 	mov	r1, #0
40702800:	ebfffd73 	bl	40701dd4 <ddrtr_memset>
40702804:	e1a00004 	mov	r0, r4
40702808:	ebfffde0 	bl	40701f90 <ddr_training_cfg_set_phy>
4070280c:	e1a00004 	mov	r0, r4
40702810:	ebffffd1 	bl	4070275c <ddr_training_cfg_set_dmc>
40702814:	e1a00004 	mov	r0, r4
40702818:	e8bd4010 	pop	{r4, lr}
4070281c:	eafffdca 	b	40701f4c <ddr_training_cfg_set_rank>

40702820 <ddr_ddrt_init>:
40702820:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40702824:	e1a05000 	mov	r5, r0
40702828:	e5906060 	ldr	r6, [r0, #96]	; 0x60
4070282c:	e1a07001 	mov	r7, r1
40702830:	e3560001 	cmp	r6, #1
40702834:	13a06000 	movne	r6, #0
40702838:	1a00000b 	bne	4070286c <ddr_ddrt_init+0x4c>
4070283c:	e5903044 	ldr	r3, [r0, #68]	; 0x44
40702840:	e5932050 	ldr	r2, [r3, #80]	; 0x50
40702844:	e5933060 	ldr	r3, [r3, #96]	; 0x60
40702848:	e7e12252 	ubfx	r2, r2, #4, #2
4070284c:	e2030007 	and	r0, r3, #7
40702850:	e2800015 	add	r0, r0, #21
40702854:	e0800002 	add	r0, r0, r2
40702858:	e7e12453 	ubfx	r2, r3, #8, #2
4070285c:	e0800002 	add	r0, r0, r2
40702860:	e7e23253 	ubfx	r3, r3, #4, #3
40702864:	e0800003 	add	r0, r0, r3
40702868:	e1a06016 	lsl	r6, r6, r0
4070286c:	e5953044 	ldr	r3, [r5, #68]	; 0x44
40702870:	e3002152 	movw	r2, #338	; 0x152
40702874:	e59f40a0 	ldr	r4, [pc, #160]	; 4070291c <ddr_ddrt_init+0xfc>
40702878:	e5933050 	ldr	r3, [r3, #80]	; 0x50
4070287c:	e7e13253 	ubfx	r3, r3, #4, #2
40702880:	e2433001 	sub	r3, r3, #1
40702884:	e1823603 	orr	r3, r2, r3, lsl #12
40702888:	e584300c 	str	r3, [r4, #12]
4070288c:	e3a03101 	mov	r3, #1073741824	; 0x40000000
40702890:	e584301c 	str	r3, [r4, #28]
40702894:	eb0005b8 	bl	40703f7c <ddr_ddrt_get_test_addr>
40702898:	e59f3080 	ldr	r3, [pc, #128]	; 40702920 <ddr_ddrt_init+0x100>
4070289c:	e3570001 	cmp	r7, #1
407028a0:	e0800006 	add	r0, r0, r6
407028a4:	e5840020 	str	r0, [r4, #32]
407028a8:	e5843038 	str	r3, [r4, #56]	; 0x38
407028ac:	1a000008 	bne	407028d4 <ddr_ddrt_init+0xb4>
407028b0:	e3a03043 	mov	r3, #67	; 0x43
407028b4:	e5843008 	str	r3, [r4, #8]
407028b8:	e3a03000 	mov	r3, #0
407028bc:	e5843010 	str	r3, [r4, #16]
407028c0:	e5843014 	str	r3, [r4, #20]
407028c4:	e5843018 	str	r3, [r4, #24]
407028c8:	e59f3054 	ldr	r3, [pc, #84]	; 40702924 <ddr_ddrt_init+0x104>
407028cc:	e5843030 	str	r3, [r4, #48]	; 0x30
407028d0:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
407028d4:	e3a0304f 	mov	r3, #79	; 0x4f
407028d8:	e5843008 	str	r3, [r4, #8]
407028dc:	e595105c 	ldr	r1, [r5, #92]	; 0x5c
407028e0:	e3a0203c 	mov	r2, #60	; 0x3c
407028e4:	e5953064 	ldr	r3, [r5, #100]	; 0x64
407028e8:	e0020192 	mul	r2, r2, r1
407028ec:	e3a0100c 	mov	r1, #12
407028f0:	e0232391 	mla	r3, r1, r3, r2
407028f4:	e0855003 	add	r5, r5, r3
407028f8:	e595301c 	ldr	r3, [r5, #28]
407028fc:	e5843030 	str	r3, [r4, #48]	; 0x30
40702900:	e3a0307f 	mov	r3, #127	; 0x7f
40702904:	e5843010 	str	r3, [r4, #16]
40702908:	e3e03000 	mvn	r3, #0
4070290c:	e5843014 	str	r3, [r4, #20]
40702910:	e3a03000 	mov	r3, #0
40702914:	e5843018 	str	r3, [r4, #24]
40702918:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
4070291c:	11330000 	.word	0x11330000
40702920:	6d6d6d6d 	.word	0x6d6d6d6d
40702924:	55aa55aa 	.word	0x55aa55aa

40702928 <ddr_ddrt_test>:
40702928:	e59f3108 	ldr	r3, [pc, #264]	; 40702a38 <ddr_ddrt_test+0x110>
4070292c:	e380c001 	orr	ip, r0, #1
40702930:	e92d4010 	push	{r4, lr}
40702934:	e583c000 	str	ip, [r3]
40702938:	e3a0c000 	mov	ip, #0
4070293c:	e583c004 	str	ip, [r3, #4]
40702940:	f57ff04f 	dsb	sy
40702944:	e59f40f0 	ldr	r4, [pc, #240]	; 40702a3c <ddr_ddrt_test+0x114>
40702948:	e593e004 	ldr	lr, [r3, #4]
4070294c:	e28cc001 	add	ip, ip, #1
40702950:	e31e0001 	tst	lr, #1
40702954:	1a000008 	bne	4070297c <ddr_ddrt_test+0x54>
40702958:	e15c0004 	cmp	ip, r4
4070295c:	1afffff9 	bne	40702948 <ddr_ddrt_test+0x20>
40702960:	e3e03000 	mvn	r3, #0
40702964:	e3a01000 	mov	r1, #0
40702968:	e1a02003 	mov	r2, r3
4070296c:	e3a00008 	mov	r0, #8
40702970:	ebfffe09 	bl	4070219c <ddr_training_stat>
40702974:	e3e02000 	mvn	r2, #0
40702978:	ea000019 	b	407029e4 <ddr_ddrt_test+0xbc>
4070297c:	e15c0004 	cmp	ip, r4
40702980:	0afffff6 	beq	40702960 <ddr_ddrt_test+0x38>
40702984:	e2000c03 	and	r0, r0, #768	; 0x300
40702988:	e3500c02 	cmp	r0, #512	; 0x200
4070298c:	0a000027 	beq	40702a30 <ddr_ddrt_test+0x108>
40702990:	e21ee002 	ands	lr, lr, #2
40702994:	1a000025 	bne	40702a30 <ddr_ddrt_test+0x108>
40702998:	e3720001 	cmn	r2, #1
4070299c:	0a000012 	beq	407029ec <ddr_ddrt_test+0xc4>
407029a0:	e5930080 	ldr	r0, [r3, #128]	; 0x80
407029a4:	e3a0c001 	mov	ip, #1
407029a8:	e0823181 	add	r3, r2, r1, lsl #3
407029ac:	e010331c 	ands	r3, r0, ip, lsl r3
407029b0:	1affffef 	bne	40702974 <ddr_ddrt_test+0x4c>
407029b4:	e3520003 	cmp	r2, #3
407029b8:	c2423004 	subgt	r3, r2, #4
407029bc:	d1a03182 	lslle	r3, r2, #3
407029c0:	e1a02122 	lsr	r2, r2, #2
407029c4:	e0821081 	add	r1, r2, r1, lsl #1
407029c8:	e59f2070 	ldr	r2, [pc, #112]	; 40702a40 <ddr_ddrt_test+0x118>
407029cc:	c1a03183 	lslgt	r3, r3, #3
407029d0:	e7922101 	ldr	r2, [r2, r1, lsl #2]
407029d4:	e3a010ff 	mov	r1, #255	; 0xff
407029d8:	e0123311 	ands	r3, r2, r1, lsl r3
407029dc:	13e02000 	mvnne	r2, #0
407029e0:	03a02000 	moveq	r2, #0
407029e4:	e1a00002 	mov	r0, r2
407029e8:	e8bd8010 	pop	{r4, pc}
407029ec:	e3710001 	cmn	r1, #1
407029f0:	01a0200e 	moveq	r2, lr
407029f4:	0afffffa 	beq	407029e4 <ddr_ddrt_test+0xbc>
407029f8:	e5930080 	ldr	r0, [r3, #128]	; 0x80
407029fc:	e3a0c0ff 	mov	ip, #255	; 0xff
40702a00:	e1a03181 	lsl	r3, r1, #3
40702a04:	e010331c 	ands	r3, r0, ip, lsl r3
40702a08:	1afffff5 	bne	407029e4 <ddr_ddrt_test+0xbc>
40702a0c:	e59f302c 	ldr	r3, [pc, #44]	; 40702a40 <ddr_ddrt_test+0x118>
40702a10:	e7932181 	ldr	r2, [r3, r1, lsl #3]
40702a14:	e1a01081 	lsl	r1, r1, #1
40702a18:	e2811001 	add	r1, r1, #1
40702a1c:	e7933101 	ldr	r3, [r3, r1, lsl #2]
40702a20:	e1720003 	cmn	r2, r3
40702a24:	13e02000 	mvnne	r2, #0
40702a28:	03a02000 	moveq	r2, #0
40702a2c:	eaffffec 	b	407029e4 <ddr_ddrt_test+0xbc>
40702a30:	e3a02000 	mov	r2, #0
40702a34:	eaffffea 	b	407029e4 <ddr_ddrt_test+0xbc>
40702a38:	11330000 	.word	0x11330000
40702a3c:	000f4240 	.word	0x000f4240
40702a40:	11330060 	.word	0x11330060

40702a44 <ddr_dataeye_check_dq>:
40702a44:	e590306c 	ldr	r3, [r0, #108]	; 0x6c
40702a48:	e3530001 	cmp	r3, #1
40702a4c:	1a000018 	bne	40702ab4 <ddr_dataeye_check_dq+0x70>
40702a50:	e92d4070 	push	{r4, r5, r6, lr}
40702a54:	e1a04000 	mov	r4, r0
40702a58:	e5903064 	ldr	r3, [r0, #100]	; 0x64
40702a5c:	e5905054 	ldr	r5, [r0, #84]	; 0x54
40702a60:	e3a00000 	mov	r0, #0
40702a64:	e59f6058 	ldr	r6, [pc, #88]	; 40702ac4 <ddr_dataeye_check_dq+0x80>
40702a68:	e1a03083 	lsl	r3, r3, #1
40702a6c:	e1550003 	cmp	r5, r3
40702a70:	20455003 	subcs	r5, r5, r3
40702a74:	e5860030 	str	r0, [r6, #48]	; 0x30
40702a78:	e5942058 	ldr	r2, [r4, #88]	; 0x58
40702a7c:	e1a01005 	mov	r1, r5
40702a80:	ebffffa8 	bl	40702928 <ddr_ddrt_test>
40702a84:	e3500000 	cmp	r0, #0
40702a88:	1a00000b 	bne	40702abc <ddr_dataeye_check_dq+0x78>
40702a8c:	e594304c 	ldr	r3, [r4, #76]	; 0x4c
40702a90:	e1a01005 	mov	r1, r5
40702a94:	e3a00a02 	mov	r0, #8192	; 0x2000
40702a98:	e5863030 	str	r3, [r6, #48]	; 0x30
40702a9c:	e5942058 	ldr	r2, [r4, #88]	; 0x58
40702aa0:	ebffffa0 	bl	40702928 <ddr_ddrt_test>
40702aa4:	e2900000 	adds	r0, r0, #0
40702aa8:	13a00001 	movne	r0, #1
40702aac:	e2600000 	rsb	r0, r0, #0
40702ab0:	e8bd8070 	pop	{r4, r5, r6, pc}
40702ab4:	e3a00000 	mov	r0, #0
40702ab8:	e12fff1e 	bx	lr
40702abc:	e3e00000 	mvn	r0, #0
40702ac0:	e8bd8070 	pop	{r4, r5, r6, pc}
40702ac4:	11330000 	.word	0x11330000

40702ac8 <ddr_dataeye_search_dq>:
40702ac8:	e92d4df3 	push	{r0, r1, r4, r5, r6, r7, r8, sl, fp, lr}
40702acc:	e1a06000 	mov	r6, r0
40702ad0:	e59d5028 	ldr	r5, [sp, #40]	; 0x28
40702ad4:	e1a0a001 	mov	sl, r1
40702ad8:	e1a0b002 	mov	fp, r2
40702adc:	e1a08003 	mov	r8, r3
40702ae0:	e04a4006 	sub	r4, sl, r6
40702ae4:	e1a00005 	mov	r0, r5
40702ae8:	e08640a4 	add	r4, r6, r4, lsr #1
40702aec:	e1a01004 	mov	r1, r4
40702af0:	ebfffe95 	bl	4070254c <ddr_phy_set_dq_bdl>
40702af4:	e1a00005 	mov	r0, r5
40702af8:	ebffffd1 	bl	40702a44 <ddr_dataeye_check_dq>
40702afc:	e3580002 	cmp	r8, #2
40702b00:	0a000009 	beq	40702b2c <ddr_dataeye_search_dq+0x64>
40702b04:	e3580004 	cmp	r8, #4
40702b08:	0a00000f 	beq	40702b4c <ddr_dataeye_search_dq+0x84>
40702b0c:	e3580001 	cmp	r8, #1
40702b10:	03a07006 	moveq	r7, #6
40702b14:	13a07000 	movne	r7, #0
40702b18:	e3500000 	cmp	r0, #0
40702b1c:	1a00000f 	bne	40702b60 <ddr_dataeye_search_dq+0x98>
40702b20:	e58b4000 	str	r4, [fp]
40702b24:	e28dd008 	add	sp, sp, #8
40702b28:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40702b2c:	e3500000 	cmp	r0, #0
40702b30:	1a000009 	bne	40702b5c <ddr_dataeye_search_dq+0x94>
40702b34:	e1a01006 	mov	r1, r6
40702b38:	e1a00005 	mov	r0, r5
40702b3c:	ebfffe82 	bl	4070254c <ddr_phy_set_dq_bdl>
40702b40:	e1a00005 	mov	r0, r5
40702b44:	ebffffbe 	bl	40702a44 <ddr_dataeye_check_dq>
40702b48:	eafffff4 	b	40702b20 <ddr_dataeye_search_dq+0x58>
40702b4c:	e3500000 	cmp	r0, #0
40702b50:	1a000011 	bne	40702b9c <ddr_dataeye_search_dq+0xd4>
40702b54:	e1a0100a 	mov	r1, sl
40702b58:	eafffff6 	b	40702b38 <ddr_dataeye_search_dq+0x70>
40702b5c:	e3a07004 	mov	r7, #4
40702b60:	e154000a 	cmp	r4, sl
40702b64:	11560004 	cmpne	r6, r4
40702b68:	0affffed 	beq	40702b24 <ddr_dataeye_search_dq+0x5c>
40702b6c:	e3170002 	tst	r7, #2
40702b70:	0a000005 	beq	40702b8c <ddr_dataeye_search_dq+0xc4>
40702b74:	e58d5000 	str	r5, [sp]
40702b78:	e1a03008 	mov	r3, r8
40702b7c:	e1a0200b 	mov	r2, fp
40702b80:	e1a01004 	mov	r1, r4
40702b84:	e1a00006 	mov	r0, r6
40702b88:	ebffffce 	bl	40702ac8 <ddr_dataeye_search_dq>
40702b8c:	e3170004 	tst	r7, #4
40702b90:	e1a06004 	mov	r6, r4
40702b94:	0affffe2 	beq	40702b24 <ddr_dataeye_search_dq+0x5c>
40702b98:	eaffffd0 	b	40702ae0 <ddr_dataeye_search_dq+0x18>
40702b9c:	e3a07002 	mov	r7, #2
40702ba0:	eaffffee 	b	40702b60 <ddr_dataeye_search_dq+0x98>

40702ba4 <ddr_dataeye_deskew>:
40702ba4:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40702ba8:	e3a05000 	mov	r5, #0
40702bac:	e5903054 	ldr	r3, [r0, #84]	; 0x54
40702bb0:	e24dd028 	sub	sp, sp, #40	; 0x28
40702bb4:	e1a04000 	mov	r4, r0
40702bb8:	e1a06001 	mov	r6, r1
40702bbc:	e1a08005 	mov	r8, r5
40702bc0:	e1a0a005 	mov	sl, r5
40702bc4:	e58d3008 	str	r3, [sp, #8]
40702bc8:	e1a03183 	lsl	r3, r3, #3
40702bcc:	e5815100 	str	r5, [r1, #256]	; 0x100
40702bd0:	e58d300c 	str	r3, [sp, #12]
40702bd4:	e59d300c 	ldr	r3, [sp, #12]
40702bd8:	e1a00004 	mov	r0, r4
40702bdc:	e5845058 	str	r5, [r4, #88]	; 0x58
40702be0:	e0853003 	add	r3, r5, r3
40702be4:	e58d3010 	str	r3, [sp, #16]
40702be8:	ebfffe75 	bl	407025c4 <ddr_phy_get_dq_bdl>
40702bec:	e5943054 	ldr	r3, [r4, #84]	; 0x54
40702bf0:	e5947058 	ldr	r7, [r4, #88]	; 0x58
40702bf4:	e0877183 	add	r7, r7, r3, lsl #3
40702bf8:	e58d0014 	str	r0, [sp, #20]
40702bfc:	e1a00004 	mov	r0, r4
40702c00:	ebfffe6f 	bl	407025c4 <ddr_phy_get_dq_bdl>
40702c04:	e58d001c 	str	r0, [sp, #28]
40702c08:	e1a0b000 	mov	fp, r0
40702c0c:	e1a00004 	mov	r0, r4
40702c10:	ebffff8b 	bl	40702a44 <ddr_dataeye_check_dq>
40702c14:	e3500000 	cmp	r0, #0
40702c18:	0a000037 	beq	40702cfc <ddr_dataeye_deskew+0x158>
40702c1c:	e28d2028 	add	r2, sp, #40	; 0x28
40702c20:	e3e03000 	mvn	r3, #0
40702c24:	e3a0107f 	mov	r1, #127	; 0x7f
40702c28:	e3a00000 	mov	r0, #0
40702c2c:	e522300c 	str	r3, [r2, #-12]!
40702c30:	e3a03001 	mov	r3, #1
40702c34:	e58d4000 	str	r4, [sp]
40702c38:	ebffffa2 	bl	40702ac8 <ddr_dataeye_search_dq>
40702c3c:	e59d301c 	ldr	r3, [sp, #28]
40702c40:	e3730001 	cmn	r3, #1
40702c44:	1a00002c 	bne	40702cfc <ddr_dataeye_deskew+0x158>
40702c48:	e0862107 	add	r2, r6, r7, lsl #2
40702c4c:	e3a03000 	mov	r3, #0
40702c50:	e1a0100b 	mov	r1, fp
40702c54:	e7863107 	str	r3, [r6, r7, lsl #2]
40702c58:	e1a00004 	mov	r0, r4
40702c5c:	e5823080 	str	r3, [r2, #128]	; 0x80
40702c60:	ebfffe39 	bl	4070254c <ddr_phy_set_dq_bdl>
40702c64:	e59d3010 	ldr	r3, [sp, #16]
40702c68:	e2833020 	add	r3, r3, #32
40702c6c:	e7967103 	ldr	r7, [r6, r3, lsl #2]
40702c70:	e1a0b827 	lsr	fp, r7, #16
40702c74:	e35b0007 	cmp	fp, #7
40702c78:	8a000057 	bhi	40702ddc <ddr_dataeye_deskew+0x238>
40702c7c:	e35a0000 	cmp	sl, #0
40702c80:	02455001 	subeq	r5, r5, #1
40702c84:	03a0a001 	moveq	sl, #1
40702c88:	0a000009 	beq	40702cb4 <ddr_dataeye_deskew+0x110>
40702c8c:	e35b0000 	cmp	fp, #0
40702c90:	1a000051 	bne	40702ddc <ddr_dataeye_deskew+0x238>
40702c94:	e59d1014 	ldr	r1, [sp, #20]
40702c98:	e1a00004 	mov	r0, r4
40702c9c:	ebfffe2a 	bl	4070254c <ddr_phy_set_dq_bdl>
40702ca0:	e1a03005 	mov	r3, r5
40702ca4:	e59d2008 	ldr	r2, [sp, #8]
40702ca8:	e3a00040 	mov	r0, #64	; 0x40
40702cac:	e5941040 	ldr	r1, [r4, #64]	; 0x40
40702cb0:	ebfffd39 	bl	4070219c <ddr_training_stat>
40702cb4:	e2855001 	add	r5, r5, #1
40702cb8:	e3550007 	cmp	r5, #7
40702cbc:	daffffc4 	ble	40702bd4 <ddr_dataeye_deskew+0x30>
40702cc0:	e5943050 	ldr	r3, [r4, #80]	; 0x50
40702cc4:	e3530002 	cmp	r3, #2
40702cc8:	1a000006 	bne	40702ce8 <ddr_dataeye_deskew+0x144>
40702ccc:	e5942060 	ldr	r2, [r4, #96]	; 0x60
40702cd0:	e7e681d8 	ubfx	r8, r8, #3, #7
40702cd4:	e5943040 	ldr	r3, [r4, #64]	; 0x40
40702cd8:	e2833f86 	add	r3, r3, #536	; 0x218
40702cdc:	e0833502 	add	r3, r3, r2, lsl #10
40702ce0:	e59d2008 	ldr	r2, [sp, #8]
40702ce4:	e7838382 	str	r8, [r3, r2, lsl #7]
40702ce8:	e5940040 	ldr	r0, [r4, #64]	; 0x40
40702cec:	ebfffdad 	bl	407023a8 <ddr_phy_cfg_update>
40702cf0:	e3a00000 	mov	r0, #0
40702cf4:	e28dd028 	add	sp, sp, #40	; 0x28
40702cf8:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40702cfc:	e59d101c 	ldr	r1, [sp, #28]
40702d00:	e3a03002 	mov	r3, #2
40702d04:	e58d4000 	str	r4, [sp]
40702d08:	e28d2020 	add	r2, sp, #32
40702d0c:	e3a00000 	mov	r0, #0
40702d10:	e58d1020 	str	r1, [sp, #32]
40702d14:	ebffff6b 	bl	40702ac8 <ddr_dataeye_search_dq>
40702d18:	e59d1020 	ldr	r1, [sp, #32]
40702d1c:	e3510000 	cmp	r1, #0
40702d20:	da00000a 	ble	40702d50 <ddr_dataeye_deskew+0x1ac>
40702d24:	e2411001 	sub	r1, r1, #1
40702d28:	e1a00004 	mov	r0, r4
40702d2c:	e58d1020 	str	r1, [sp, #32]
40702d30:	ebfffe05 	bl	4070254c <ddr_phy_set_dq_bdl>
40702d34:	e1a00004 	mov	r0, r4
40702d38:	ebffff41 	bl	40702a44 <ddr_dataeye_check_dq>
40702d3c:	e3500000 	cmp	r0, #0
40702d40:	0afffff4 	beq	40702d18 <ddr_dataeye_deskew+0x174>
40702d44:	e59d3020 	ldr	r3, [sp, #32]
40702d48:	e2833001 	add	r3, r3, #1
40702d4c:	e58d3020 	str	r3, [sp, #32]
40702d50:	e59d001c 	ldr	r0, [sp, #28]
40702d54:	e28d2028 	add	r2, sp, #40	; 0x28
40702d58:	e3a03004 	mov	r3, #4
40702d5c:	e3a0107f 	mov	r1, #127	; 0x7f
40702d60:	e5220004 	str	r0, [r2, #-4]!
40702d64:	e58d4000 	str	r4, [sp]
40702d68:	ebffff56 	bl	40702ac8 <ddr_dataeye_search_dq>
40702d6c:	e59d1024 	ldr	r1, [sp, #36]	; 0x24
40702d70:	e351007e 	cmp	r1, #126	; 0x7e
40702d74:	ca00000a 	bgt	40702da4 <ddr_dataeye_deskew+0x200>
40702d78:	e2811001 	add	r1, r1, #1
40702d7c:	e1a00004 	mov	r0, r4
40702d80:	e58d1024 	str	r1, [sp, #36]	; 0x24
40702d84:	ebfffdf0 	bl	4070254c <ddr_phy_set_dq_bdl>
40702d88:	e1a00004 	mov	r0, r4
40702d8c:	ebffff2c 	bl	40702a44 <ddr_dataeye_check_dq>
40702d90:	e3500000 	cmp	r0, #0
40702d94:	0afffff4 	beq	40702d6c <ddr_dataeye_deskew+0x1c8>
40702d98:	e59d3024 	ldr	r3, [sp, #36]	; 0x24
40702d9c:	e2433001 	sub	r3, r3, #1
40702da0:	e58d3024 	str	r3, [sp, #36]	; 0x24
40702da4:	e1a0100b 	mov	r1, fp
40702da8:	e1a00004 	mov	r0, r4
40702dac:	ebfffde6 	bl	4070254c <ddr_phy_set_dq_bdl>
40702db0:	e59d3020 	ldr	r3, [sp, #32]
40702db4:	e59d1024 	ldr	r1, [sp, #36]	; 0x24
40702db8:	e0860107 	add	r0, r6, r7, lsl #2
40702dbc:	e0412003 	sub	r2, r1, r3
40702dc0:	e1811803 	orr	r1, r1, r3, lsl #16
40702dc4:	e2822001 	add	r2, r2, #1
40702dc8:	e7861107 	str	r1, [r6, r7, lsl #2]
40702dcc:	e08330a2 	add	r3, r3, r2, lsr #1
40702dd0:	e1833802 	orr	r3, r3, r2, lsl #16
40702dd4:	e5803080 	str	r3, [r0, #128]	; 0x80
40702dd8:	eaffffa1 	b	40702c64 <ddr_dataeye_deskew+0xc0>
40702ddc:	e6ff7077 	uxth	r7, r7
40702de0:	e1a00004 	mov	r0, r4
40702de4:	e0888007 	add	r8, r8, r7
40702de8:	e3a0a000 	mov	sl, #0
40702dec:	e1a01007 	mov	r1, r7
40702df0:	ebfffdd5 	bl	4070254c <ddr_phy_set_dq_bdl>
40702df4:	e5963100 	ldr	r3, [r6, #256]	; 0x100
40702df8:	e083b00b 	add	fp, r3, fp
40702dfc:	e586b100 	str	fp, [r6, #256]	; 0x100
40702e00:	eaffffab 	b	40702cb4 <ddr_dataeye_deskew+0x110>

40702e04 <ddr_vref_get_win>:
40702e04:	e92d4070 	push	{r4, r5, r6, lr}
40702e08:	e3a03000 	mov	r3, #0
40702e0c:	e5813100 	str	r3, [r1, #256]	; 0x100
40702e10:	e1a05001 	mov	r5, r1
40702e14:	e5903050 	ldr	r3, [r0, #80]	; 0x50
40702e18:	e1a04000 	mov	r4, r0
40702e1c:	e3530001 	cmp	r3, #1
40702e20:	13a01032 	movne	r1, #50	; 0x32
40702e24:	1a000003 	bne	40702e38 <ddr_vref_get_win+0x34>
40702e28:	e5903060 	ldr	r3, [r0, #96]	; 0x60
40702e2c:	e3530000 	cmp	r3, #0
40702e30:	03a0101f 	moveq	r1, #31
40702e34:	13a0100f 	movne	r1, #15
40702e38:	e1520001 	cmp	r2, r1
40702e3c:	e1a00004 	mov	r0, r4
40702e40:	31a01002 	movcc	r1, r2
40702e44:	ebfffc66 	bl	40701fe4 <ddr_vref_set>
40702e48:	e1a01005 	mov	r1, r5
40702e4c:	e1a00004 	mov	r0, r4
40702e50:	ebffff53 	bl	40702ba4 <ddr_dataeye_deskew>
40702e54:	e5950100 	ldr	r0, [r5, #256]	; 0x100
40702e58:	e8bd8070 	pop	{r4, r5, r6, pc}

40702e5c <ddr_vref_find_best>:
40702e5c:	e92d4df3 	push	{r0, r1, r4, r5, r6, r7, r8, sl, fp, lr}
40702e60:	e1a0b003 	mov	fp, r3
40702e64:	e5903050 	ldr	r3, [r0, #80]	; 0x50
40702e68:	e1a08000 	mov	r8, r0
40702e6c:	e1a0a001 	mov	sl, r1
40702e70:	e3530001 	cmp	r3, #1
40702e74:	13a07032 	movne	r7, #50	; 0x32
40702e78:	1a000003 	bne	40702e8c <ddr_vref_find_best+0x30>
40702e7c:	e5903060 	ldr	r3, [r0, #96]	; 0x60
40702e80:	e3530000 	cmp	r3, #0
40702e84:	03a0701f 	moveq	r7, #31
40702e88:	13a0700f 	movne	r7, #15
40702e8c:	e1570002 	cmp	r7, r2
40702e90:	e3a06000 	mov	r6, #0
40702e94:	e08b5002 	add	r5, fp, r2
40702e98:	e1a03006 	mov	r3, r6
40702e9c:	31a04007 	movcc	r4, r7
40702ea0:	21a04002 	movcs	r4, r2
40702ea4:	e1570005 	cmp	r7, r5
40702ea8:	3a00000a 	bcc	40702ed8 <ddr_vref_find_best+0x7c>
40702eac:	e1a02005 	mov	r2, r5
40702eb0:	e1a0100a 	mov	r1, sl
40702eb4:	e1a00008 	mov	r0, r8
40702eb8:	e58d3004 	str	r3, [sp, #4]
40702ebc:	ebffffd0 	bl	40702e04 <ddr_vref_get_win>
40702ec0:	e59d3004 	ldr	r3, [sp, #4]
40702ec4:	e1530000 	cmp	r3, r0
40702ec8:	9a000005 	bls	40702ee4 <ddr_vref_find_best+0x88>
40702ecc:	e2866001 	add	r6, r6, #1
40702ed0:	e3560003 	cmp	r6, #3
40702ed4:	1a000005 	bne	40702ef0 <ddr_vref_find_best+0x94>
40702ed8:	e1a00004 	mov	r0, r4
40702edc:	e28dd008 	add	sp, sp, #8
40702ee0:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40702ee4:	e1a03000 	mov	r3, r0
40702ee8:	e1a04005 	mov	r4, r5
40702eec:	e3a06000 	mov	r6, #0
40702ef0:	e085500b 	add	r5, r5, fp
40702ef4:	eaffffea 	b	40702ea4 <ddr_vref_find_best+0x48>

40702ef8 <ddr_vref_cal>:
40702ef8:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40702efc:	e1a06001 	mov	r6, r1
40702f00:	e5903050 	ldr	r3, [r0, #80]	; 0x50
40702f04:	e1a04000 	mov	r4, r0
40702f08:	e5902054 	ldr	r2, [r0, #84]	; 0x54
40702f0c:	e3530001 	cmp	r3, #1
40702f10:	e5903040 	ldr	r3, [r0, #64]	; 0x40
40702f14:	05901060 	ldreq	r1, [r0, #96]	; 0x60
40702f18:	02833f9d 	addeq	r3, r3, #628	; 0x274
40702f1c:	12833e27 	addne	r3, r3, #624	; 0x270
40702f20:	00833501 	addeq	r3, r3, r1, lsl #10
40702f24:	17935382 	ldrne	r5, [r3, r2, lsl #7]
40702f28:	e1a01006 	mov	r1, r6
40702f2c:	07935382 	ldreq	r5, [r3, r2, lsl #7]
40702f30:	1205503f 	andne	r5, r5, #63	; 0x3f
40702f34:	0205501f 	andeq	r5, r5, #31
40702f38:	e2452003 	sub	r2, r5, #3
40702f3c:	ebffffb0 	bl	40702e04 <ddr_vref_get_win>
40702f40:	e2852003 	add	r2, r5, #3
40702f44:	e1a01006 	mov	r1, r6
40702f48:	e1a07000 	mov	r7, r0
40702f4c:	e1a00004 	mov	r0, r4
40702f50:	ebffffab 	bl	40702e04 <ddr_vref_get_win>
40702f54:	e1570000 	cmp	r7, r0
40702f58:	2a000008 	bcs	40702f80 <ddr_vref_cal+0x88>
40702f5c:	e3a03001 	mov	r3, #1
40702f60:	e1a01006 	mov	r1, r6
40702f64:	e1a02005 	mov	r2, r5
40702f68:	e1a00004 	mov	r0, r4
40702f6c:	ebffffba 	bl	40702e5c <ddr_vref_find_best>
40702f70:	e1a01000 	mov	r1, r0
40702f74:	e1a00004 	mov	r0, r4
40702f78:	e8bd41f0 	pop	{r4, r5, r6, r7, r8, lr}
40702f7c:	eafffc18 	b	40701fe4 <ddr_vref_set>
40702f80:	9a000001 	bls	40702f8c <ddr_vref_cal+0x94>
40702f84:	e3e03000 	mvn	r3, #0
40702f88:	eafffff4 	b	40702f60 <ddr_vref_cal+0x68>
40702f8c:	e5943050 	ldr	r3, [r4, #80]	; 0x50
40702f90:	e3530001 	cmp	r3, #1
40702f94:	13a03032 	movne	r3, #50	; 0x32
40702f98:	1a000003 	bne	40702fac <ddr_vref_cal+0xb4>
40702f9c:	e5943060 	ldr	r3, [r4, #96]	; 0x60
40702fa0:	e3530000 	cmp	r3, #0
40702fa4:	03a0301f 	moveq	r3, #31
40702fa8:	13a0300f 	movne	r3, #15
40702fac:	e15500a3 	cmp	r5, r3, lsr #1
40702fb0:	2afffff3 	bcs	40702f84 <ddr_vref_cal+0x8c>
40702fb4:	eaffffe8 	b	40702f5c <ddr_vref_cal+0x64>

40702fb8 <ddr_adjust_move_win.constprop.14>:
40702fb8:	e92d4df3 	push	{r0, r1, r4, r5, r6, r7, r8, sl, fp, lr}
40702fbc:	e1a0b001 	mov	fp, r1
40702fc0:	e5901050 	ldr	r1, [r0, #80]	; 0x50
40702fc4:	e1a0a002 	mov	sl, r2
40702fc8:	e1a04000 	mov	r4, r0
40702fcc:	e5902054 	ldr	r2, [r0, #84]	; 0x54
40702fd0:	e3510002 	cmp	r1, #2
40702fd4:	e5903040 	ldr	r3, [r0, #64]	; 0x40
40702fd8:	0a000024 	beq	40703070 <ddr_adjust_move_win.constprop.14+0xb8>
40702fdc:	e3510001 	cmp	r1, #1
40702fe0:	130081ff 	movwne	r8, #511	; 0x1ff
40702fe4:	1a000022 	bne	40703074 <ddr_adjust_move_win.constprop.14+0xbc>
40702fe8:	e2833f8b 	add	r3, r3, #556	; 0x22c
40702fec:	e30081ff 	movw	r8, #511	; 0x1ff
40702ff0:	e7936382 	ldr	r6, [r3, r2, lsl #7]
40702ff4:	e7e86056 	ubfx	r6, r6, #0, #9
40702ff8:	e1a05006 	mov	r5, r6
40702ffc:	e3a07000 	mov	r7, #0
40703000:	e1580007 	cmp	r8, r7
40703004:	3a000017 	bcc	40703068 <ddr_adjust_move_win.constprop.14+0xb0>
40703008:	e5943050 	ldr	r3, [r4, #80]	; 0x50
4070300c:	e3530002 	cmp	r3, #2
40703010:	1a00001d 	bne	4070308c <ddr_adjust_move_win.constprop.14+0xd4>
40703014:	e1a00004 	mov	r0, r4
40703018:	e58d3004 	str	r3, [sp, #4]
4070301c:	ebfffb43 	bl	40701d30 <ddr_adjust_get_average>
40703020:	e59d3004 	ldr	r3, [sp, #4]
40703024:	e3500037 	cmp	r0, #55	; 0x37
40703028:	9a000002 	bls	40703038 <ddr_adjust_move_win.constprop.14+0x80>
4070302c:	e3500048 	cmp	r0, #72	; 0x48
40703030:	83a03004 	movhi	r3, #4
40703034:	93a03001 	movls	r3, #1
40703038:	e3a02001 	mov	r2, #1
4070303c:	e153000a 	cmp	r3, sl
40703040:	13530001 	cmpne	r3, #1
40703044:	0a000007 	beq	40703068 <ddr_adjust_move_win.constprop.14+0xb0>
40703048:	e5943050 	ldr	r3, [r4, #80]	; 0x50
4070304c:	e3530001 	cmp	r3, #1
40703050:	1a00001c 	bne	407030c8 <ddr_adjust_move_win.constprop.14+0x110>
40703054:	e35a0004 	cmp	sl, #4
40703058:	00855002 	addeq	r5, r5, r2
4070305c:	10455002 	subne	r5, r5, r2
40703060:	e3550c02 	cmp	r5, #512	; 0x200
40703064:	3a00001c 	bcc	407030dc <ddr_adjust_move_win.constprop.14+0x124>
40703068:	e28dd008 	add	sp, sp, #8
4070306c:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40703070:	e3a0801f 	mov	r8, #31
40703074:	e5941060 	ldr	r1, [r4, #96]	; 0x60
40703078:	e2833f8d 	add	r3, r3, #564	; 0x234
4070307c:	e0833501 	add	r3, r3, r1, lsl #10
40703080:	e7936382 	ldr	r6, [r3, r2, lsl #7]
40703084:	e7e46456 	ubfx	r6, r6, #8, #5
40703088:	eaffffda 	b	40702ff8 <ddr_adjust_move_win.constprop.14+0x40>
4070308c:	e1a00004 	mov	r0, r4
40703090:	ebfffb26 	bl	40701d30 <ddr_adjust_get_average>
40703094:	e3500040 	cmp	r0, #64	; 0x40
40703098:	9a000004 	bls	407030b0 <ddr_adjust_move_win.constprop.14+0xf8>
4070309c:	e3500048 	cmp	r0, #72	; 0x48
407030a0:	e2402040 	sub	r2, r0, #64	; 0x40
407030a4:	83a03004 	movhi	r3, #4
407030a8:	93a03001 	movls	r3, #1
407030ac:	eaffffe2 	b	4070303c <ddr_adjust_move_win.constprop.14+0x84>
407030b0:	12602040 	rsbne	r2, r0, #64	; 0x40
407030b4:	03a02001 	moveq	r2, #1
407030b8:	e3500037 	cmp	r0, #55	; 0x37
407030bc:	83a03001 	movhi	r3, #1
407030c0:	93a03002 	movls	r3, #2
407030c4:	eaffffdc 	b	4070303c <ddr_adjust_move_win.constprop.14+0x84>
407030c8:	e35a0004 	cmp	sl, #4
407030cc:	00455002 	subeq	r5, r5, r2
407030d0:	10855002 	addne	r5, r5, r2
407030d4:	e355001f 	cmp	r5, #31
407030d8:	8affffe2 	bhi	40703068 <ddr_adjust_move_win.constprop.14+0xb0>
407030dc:	e1a01005 	mov	r1, r5
407030e0:	e1a00004 	mov	r0, r4
407030e4:	ebfffd6a 	bl	40702694 <ddr_adjust_set_val>
407030e8:	e1a0100b 	mov	r1, fp
407030ec:	e1a00004 	mov	r0, r4
407030f0:	ebfffeab 	bl	40702ba4 <ddr_dataeye_deskew>
407030f4:	e3500000 	cmp	r0, #0
407030f8:	0a000007 	beq	4070311c <ddr_adjust_move_win.constprop.14+0x164>
407030fc:	e1a01006 	mov	r1, r6
40703100:	e1a00004 	mov	r0, r4
40703104:	ebfffd62 	bl	40702694 <ddr_adjust_set_val>
40703108:	e1a0100b 	mov	r1, fp
4070310c:	e1a00004 	mov	r0, r4
40703110:	e28dd008 	add	sp, sp, #8
40703114:	e8bd4df0 	pop	{r4, r5, r6, r7, r8, sl, fp, lr}
40703118:	eafffea1 	b	40702ba4 <ddr_dataeye_deskew>
4070311c:	e2877001 	add	r7, r7, #1
40703120:	eaffffb6 	b	40703000 <ddr_adjust_move_win.constprop.14+0x48>

40703124 <ddr_adjust_dataeye>:
40703124:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40703128:	e5905048 	ldr	r5, [r0, #72]	; 0x48
4070312c:	e2155201 	ands	r5, r5, #268435456	; 0x10000000
40703130:	0a000014 	beq	40703188 <ddr_adjust_dataeye+0x64>
40703134:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40703138:	e0852082 	add	r2, r5, r2, lsl #1
4070313c:	e1a00004 	mov	r0, r4
40703140:	e5842054 	str	r2, [r4, #84]	; 0x54
40703144:	ebfffaf9 	bl	40701d30 <ddr_adjust_get_average>
40703148:	e3500037 	cmp	r0, #55	; 0x37
4070314c:	93a02004 	movls	r2, #4
40703150:	9a000014 	bls	407031a8 <ddr_adjust_dataeye+0x84>
40703154:	e3500048 	cmp	r0, #72	; 0x48
40703158:	83a02002 	movhi	r2, #2
4070315c:	8a000011 	bhi	407031a8 <ddr_adjust_dataeye+0x84>
40703160:	e2855001 	add	r5, r5, #1
40703164:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703168:	e5942064 	ldr	r2, [r4, #100]	; 0x64
4070316c:	e0030398 	mul	r3, r8, r3
40703170:	e0233297 	mla	r3, r7, r2, r3
40703174:	e0843003 	add	r3, r4, r3
40703178:	e5933018 	ldr	r3, [r3, #24]
4070317c:	e1550003 	cmp	r5, r3
40703180:	3affffec 	bcc	40703138 <ddr_adjust_dataeye+0x14>
40703184:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40703188:	e5903068 	ldr	r3, [r0, #104]	; 0x68
4070318c:	e3530000 	cmp	r3, #0
40703190:	08bd81f0 	popeq	{r4, r5, r6, r7, r8, pc}
40703194:	e1a06001 	mov	r6, r1
40703198:	e1a04000 	mov	r4, r0
4070319c:	e3a0700c 	mov	r7, #12
407031a0:	e3a0803c 	mov	r8, #60	; 0x3c
407031a4:	eaffffee 	b	40703164 <ddr_adjust_dataeye+0x40>
407031a8:	e1a01006 	mov	r1, r6
407031ac:	e1a00004 	mov	r0, r4
407031b0:	ebffff80 	bl	40702fb8 <ddr_adjust_move_win.constprop.14>
407031b4:	eaffffe9 	b	40703160 <ddr_adjust_dataeye+0x3c>

407031b8 <ddr_dataeye_process>:
407031b8:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
407031bc:	e3a06000 	mov	r6, #0
407031c0:	e1a04000 	mov	r4, r0
407031c4:	e1a07001 	mov	r7, r1
407031c8:	e1a05006 	mov	r5, r6
407031cc:	e3a0800c 	mov	r8, #12
407031d0:	e3a0a03c 	mov	sl, #60	; 0x3c
407031d4:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
407031d8:	e5942064 	ldr	r2, [r4, #100]	; 0x64
407031dc:	e003039a 	mul	r3, sl, r3
407031e0:	e0233298 	mla	r3, r8, r2, r3
407031e4:	e0843003 	add	r3, r4, r3
407031e8:	e5933018 	ldr	r3, [r3, #24]
407031ec:	e1530006 	cmp	r3, r6
407031f0:	8a00000a 	bhi	40703220 <ddr_dataeye_process+0x68>
407031f4:	e3550000 	cmp	r5, #0
407031f8:	13e05000 	mvnne	r5, #0
407031fc:	1a000002 	bne	4070320c <ddr_dataeye_process+0x54>
40703200:	e1a01007 	mov	r1, r7
40703204:	e1a00004 	mov	r0, r4
40703208:	ebffffc5 	bl	40703124 <ddr_adjust_dataeye>
4070320c:	e1a00004 	mov	r0, r4
40703210:	e1a01007 	mov	r1, r7
40703214:	eb000356 	bl	40703f74 <ddr_result_data_save>
40703218:	e1a00005 	mov	r0, r5
4070321c:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40703220:	e0862082 	add	r2, r6, r2, lsl #1
40703224:	e1a01007 	mov	r1, r7
40703228:	e5842054 	str	r2, [r4, #84]	; 0x54
4070322c:	e1a00004 	mov	r0, r4
40703230:	ebfffe5b 	bl	40702ba4 <ddr_dataeye_deskew>
40703234:	e2866001 	add	r6, r6, #1
40703238:	e0855000 	add	r5, r5, r0
4070323c:	eaffffe4 	b	407031d4 <ddr_dataeye_process+0x1c>

40703240 <ddr_dataeye_training>:
40703240:	e92d4030 	push	{r4, r5, lr}
40703244:	e24ddf43 	sub	sp, sp, #268	; 0x10c
40703248:	e1a04000 	mov	r4, r0
4070324c:	e3a03002 	mov	r3, #2
40703250:	e3a02f41 	mov	r2, #260	; 0x104
40703254:	e5803050 	str	r3, [r0, #80]	; 0x50
40703258:	e3a01000 	mov	r1, #0
4070325c:	e28d0004 	add	r0, sp, #4
40703260:	ebfffadb 	bl	40701dd4 <ddrtr_memset>
40703264:	e28d1004 	add	r1, sp, #4
40703268:	e1a00004 	mov	r0, r4
4070326c:	ebffffd1 	bl	407031b8 <ddr_dataeye_process>
40703270:	e3a03001 	mov	r3, #1
40703274:	e3a02f41 	mov	r2, #260	; 0x104
40703278:	e5843050 	str	r3, [r4, #80]	; 0x50
4070327c:	e3a01000 	mov	r1, #0
40703280:	e1a05000 	mov	r5, r0
40703284:	e28d0004 	add	r0, sp, #4
40703288:	ebfffad1 	bl	40701dd4 <ddrtr_memset>
4070328c:	e28d1004 	add	r1, sp, #4
40703290:	e1a00004 	mov	r0, r4
40703294:	ebffffc7 	bl	407031b8 <ddr_dataeye_process>
40703298:	e1953000 	orrs	r3, r5, r0
4070329c:	13e00000 	mvnne	r0, #0
407032a0:	03a00000 	moveq	r0, #0
407032a4:	e28ddf43 	add	sp, sp, #268	; 0x10c
407032a8:	e8bd8030 	pop	{r4, r5, pc}

407032ac <ddr_dataeye_training_func>:
407032ac:	e92d4030 	push	{r4, r5, lr}
407032b0:	e24dd03c 	sub	sp, sp, #60	; 0x3c
407032b4:	e5903048 	ldr	r3, [r0, #72]	; 0x48
407032b8:	e3130801 	tst	r3, #65536	; 0x10000
407032bc:	13a05000 	movne	r5, #0
407032c0:	1a000011 	bne	4070330c <ddr_dataeye_training_func+0x60>
407032c4:	e1a04000 	mov	r4, r0
407032c8:	e3a02801 	mov	r2, #65536	; 0x10000
407032cc:	e1a0100d 	mov	r1, sp
407032d0:	ebfffc40 	bl	407023d8 <ddr_training_save_reg>
407032d4:	e1a00004 	mov	r0, r4
407032d8:	ebfffc18 	bl	40702340 <ddr_training_switch_axi>
407032dc:	e3a01002 	mov	r1, #2
407032e0:	e1a00004 	mov	r0, r4
407032e4:	ebfffd4d 	bl	40702820 <ddr_ddrt_init>
407032e8:	e3a03001 	mov	r3, #1
407032ec:	e1a00004 	mov	r0, r4
407032f0:	e5843068 	str	r3, [r4, #104]	; 0x68
407032f4:	e584306c 	str	r3, [r4, #108]	; 0x6c
407032f8:	ebffffd0 	bl	40703240 <ddr_dataeye_training>
407032fc:	e1a0100d 	mov	r1, sp
40703300:	e1a05000 	mov	r5, r0
40703304:	e1a00004 	mov	r0, r4
40703308:	ebfffc6f 	bl	407024cc <ddr_training_restore_reg>
4070330c:	e1a00005 	mov	r0, r5
40703310:	e28dd03c 	add	sp, sp, #60	; 0x3c
40703314:	e8bd8030 	pop	{r4, r5, pc}

40703318 <ddr_hw_dataeye_read>:
40703318:	e92d4070 	push	{r4, r5, r6, lr}
4070331c:	e3a0203c 	mov	r2, #60	; 0x3c
40703320:	e590305c 	ldr	r3, [r0, #92]	; 0x5c
40703324:	e1a04000 	mov	r4, r0
40703328:	e5905040 	ldr	r5, [r0, #64]	; 0x40
4070332c:	e0230392 	mla	r3, r2, r3, r0
40703330:	e5936010 	ldr	r6, [r3, #16]
40703334:	ebfffd2d 	bl	407027f0 <ddr_training_cfg_init>
40703338:	e3a03000 	mov	r3, #0
4070333c:	e2850f8b 	add	r0, r5, #556	; 0x22c
40703340:	e285cf87 	add	ip, r5, #540	; 0x21c
40703344:	e285ee22 	add	lr, r5, #544	; 0x220
40703348:	e1a02003 	mov	r2, r3
4070334c:	e1530006 	cmp	r3, r6
40703350:	1a000005 	bne	4070336c <ddr_hw_dataeye_read+0x54>
40703354:	e1a00005 	mov	r0, r5
40703358:	ebfffc12 	bl	407023a8 <ddr_phy_cfg_update>
4070335c:	e1a00004 	mov	r0, r4
40703360:	e3a01c01 	mov	r1, #256	; 0x100
40703364:	e8bd4070 	pop	{r4, r5, r6, lr}
40703368:	eafffba5 	b	40702204 <ddr_hw_training_process>
4070336c:	e5941060 	ldr	r1, [r4, #96]	; 0x60
40703370:	e08c1501 	add	r1, ip, r1, lsl #10
40703374:	e7812383 	str	r2, [r1, r3, lsl #7]
40703378:	e5941060 	ldr	r1, [r4, #96]	; 0x60
4070337c:	e08e1501 	add	r1, lr, r1, lsl #10
40703380:	e7812383 	str	r2, [r1, r3, lsl #7]
40703384:	e2833001 	add	r3, r3, #1
40703388:	e4802080 	str	r2, [r0], #128	; 0x80
4070338c:	eaffffee 	b	4070334c <ddr_hw_dataeye_read+0x34>

40703390 <ddr_hw_training_ctl>:
40703390:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40703394:	e28db01c 	add	fp, sp, #28
40703398:	e24dd040 	sub	sp, sp, #64	; 0x40
4070339c:	e5905040 	ldr	r5, [r0, #64]	; 0x40
407033a0:	e5907074 	ldr	r7, [r0, #116]	; 0x74
407033a4:	e5906048 	ldr	r6, [r0, #72]	; 0x48
407033a8:	e59530c4 	ldr	r3, [r5, #196]	; 0xc4
407033ac:	e3570000 	cmp	r7, #0
407033b0:	13560000 	cmpne	r6, #0
407033b4:	e50b3020 	str	r3, [fp, #-32]	; 0xffffffe0
407033b8:	03a07000 	moveq	r7, #0
407033bc:	0a00005e 	beq	4070353c <ddr_hw_training_ctl+0x1ac>
407033c0:	e590305c 	ldr	r3, [r0, #92]	; 0x5c
407033c4:	e3a0803c 	mov	r8, #60	; 0x3c
407033c8:	e1a04000 	mov	r4, r0
407033cc:	e0230398 	mla	r3, r8, r3, r0
407033d0:	e1a00005 	mov	r0, r5
407033d4:	e5933010 	ldr	r3, [r3, #16]
407033d8:	e50b3040 	str	r3, [fp, #-64]	; 0xffffffc0
407033dc:	ebfffbf1 	bl	407023a8 <ddr_phy_cfg_update>
407033e0:	e2061902 	and	r1, r6, #32768	; 0x8000
407033e4:	e1a00004 	mov	r0, r4
407033e8:	ebfffb85 	bl	40702204 <ddr_hw_training_process>
407033ec:	e206100e 	and	r1, r6, #14
407033f0:	e1a0a000 	mov	sl, r0
407033f4:	e1a00004 	mov	r0, r4
407033f8:	ebfffb81 	bl	40702204 <ddr_hw_training_process>
407033fc:	e5943060 	ldr	r3, [r4, #96]	; 0x60
40703400:	e3530000 	cmp	r3, #0
40703404:	e08aa000 	add	sl, sl, r0
40703408:	0a00004e 	beq	40703548 <ddr_hw_training_ctl+0x1b8>
4070340c:	e3a0e000 	mov	lr, #0
40703410:	e51b3040 	ldr	r3, [fp, #-64]	; 0xffffffc0
40703414:	e15e0003 	cmp	lr, r3
40703418:	1a000055 	bne	40703574 <ddr_hw_training_ctl+0x1e4>
4070341c:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703420:	e3a0203c 	mov	r2, #60	; 0x3c
40703424:	e2061b05 	and	r1, r6, #5120	; 0x1400
40703428:	e0234392 	mla	r3, r2, r3, r4
4070342c:	e5933004 	ldr	r3, [r3, #4]
40703430:	e3530006 	cmp	r3, #6
40703434:	1a0000af 	bne	407036f8 <ddr_hw_training_ctl+0x368>
40703438:	e5958064 	ldr	r8, [r5, #100]	; 0x64
4070343c:	e1a00004 	mov	r0, r4
40703440:	e3c8320f 	bic	r3, r8, #-268435456	; 0xf0000000
40703444:	e5853064 	str	r3, [r5, #100]	; 0x64
40703448:	ebfffb6d 	bl	40702204 <ddr_hw_training_process>
4070344c:	e5858064 	str	r8, [r5, #100]	; 0x64
40703450:	e5958048 	ldr	r8, [r5, #72]	; 0x48
40703454:	e3c83001 	bic	r3, r8, #1
40703458:	e5853048 	str	r3, [r5, #72]	; 0x48
4070345c:	e08a7000 	add	r7, sl, r0
40703460:	e206a602 	and	sl, r6, #2097152	; 0x200000
40703464:	e1a00004 	mov	r0, r4
40703468:	e1a0100a 	mov	r1, sl
4070346c:	ebfffb64 	bl	40702204 <ddr_hw_training_process>
40703470:	e3883001 	orr	r3, r8, #1
40703474:	e1a0100a 	mov	r1, sl
40703478:	e5853048 	str	r3, [r5, #72]	; 0x48
4070347c:	e0877000 	add	r7, r7, r0
40703480:	e1a00004 	mov	r0, r4
40703484:	ebfffb5e 	bl	40702204 <ddr_hw_training_process>
40703488:	e5858048 	str	r8, [r5, #72]	; 0x48
4070348c:	e2061b01 	and	r1, r6, #1024	; 0x400
40703490:	e0877000 	add	r7, r7, r0
40703494:	e1a00004 	mov	r0, r4
40703498:	ebfffb59 	bl	40702204 <ddr_hw_training_process>
4070349c:	e0877000 	add	r7, r7, r0
407034a0:	e2061b02 	and	r1, r6, #2048	; 0x800
407034a4:	e1a00004 	mov	r0, r4
407034a8:	ebfffb55 	bl	40702204 <ddr_hw_training_process>
407034ac:	e2061501 	and	r1, r6, #4194304	; 0x400000
407034b0:	e2068701 	and	r8, r6, #262144	; 0x40000
407034b4:	e0877000 	add	r7, r7, r0
407034b8:	e1a00004 	mov	r0, r4
407034bc:	ebfffb50 	bl	40702204 <ddr_hw_training_process>
407034c0:	e51b3020 	ldr	r3, [fp, #-32]	; 0xffffffe0
407034c4:	e1a01008 	mov	r1, r8
407034c8:	e3c33102 	bic	r3, r3, #-2147483648	; 0x80000000
407034cc:	e58530c4 	str	r3, [r5, #196]	; 0xc4
407034d0:	e59530c0 	ldr	r3, [r5, #192]	; 0xc0
407034d4:	e3833102 	orr	r3, r3, #-2147483648	; 0x80000000
407034d8:	e58530c0 	str	r3, [r5, #192]	; 0xc0
407034dc:	e0877000 	add	r7, r7, r0
407034e0:	e1a00004 	mov	r0, r4
407034e4:	ebfffb46 	bl	40702204 <ddr_hw_training_process>
407034e8:	e1a01008 	mov	r1, r8
407034ec:	e0877000 	add	r7, r7, r0
407034f0:	e1a00004 	mov	r0, r4
407034f4:	ebfffb42 	bl	40702204 <ddr_hw_training_process>
407034f8:	e59530c0 	ldr	r3, [r5, #192]	; 0xc0
407034fc:	e1a01008 	mov	r1, r8
40703500:	e3c33102 	bic	r3, r3, #-2147483648	; 0x80000000
40703504:	e58530c0 	str	r3, [r5, #192]	; 0xc0
40703508:	e0877000 	add	r7, r7, r0
4070350c:	e1a00004 	mov	r0, r4
40703510:	ebfffb3b 	bl	40702204 <ddr_hw_training_process>
40703514:	e51b3020 	ldr	r3, [fp, #-32]	; 0xffffffe0
40703518:	e59f11e8 	ldr	r1, [pc, #488]	; 40703708 <ddr_hw_training_ctl+0x378>
4070351c:	e58530c4 	str	r3, [r5, #196]	; 0xc4
40703520:	e0011006 	and	r1, r1, r6
40703524:	e0877000 	add	r7, r7, r0
40703528:	e1a00004 	mov	r0, r4
4070352c:	ebfffb34 	bl	40702204 <ddr_hw_training_process>
40703530:	e0877000 	add	r7, r7, r0
40703534:	e1a00005 	mov	r0, r5
40703538:	ebfffb9a 	bl	407023a8 <ddr_phy_cfg_update>
4070353c:	e1a00007 	mov	r0, r7
40703540:	e24bd01c 	sub	sp, fp, #28
40703544:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40703548:	e594205c 	ldr	r2, [r4, #92]	; 0x5c
4070354c:	e0284298 	mla	r8, r8, r2, r4
40703550:	e5942040 	ldr	r2, [r4, #64]	; 0x40
40703554:	e2822f8b 	add	r2, r2, #556	; 0x22c
40703558:	e5981010 	ldr	r1, [r8, #16]
4070355c:	e1510003 	cmp	r1, r3
40703560:	0affffa9 	beq	4070340c <ddr_hw_training_ctl+0x7c>
40703564:	e4920080 	ldr	r0, [r2], #128	; 0x80
40703568:	e7870103 	str	r0, [r7, r3, lsl #2]
4070356c:	e2833001 	add	r3, r3, #1
40703570:	eafffff9 	b	4070355c <ddr_hw_training_ctl+0x1cc>
40703574:	e5941060 	ldr	r1, [r4, #96]	; 0x60
40703578:	e1a0238e 	lsl	r2, lr, #7
4070357c:	e594c040 	ldr	ip, [r4, #64]	; 0x40
40703580:	e584e054 	str	lr, [r4, #84]	; 0x54
40703584:	e08c1501 	add	r1, ip, r1, lsl #10
40703588:	e28ccf8b 	add	ip, ip, #556	; 0x22c
4070358c:	e0811002 	add	r1, r1, r2
40703590:	e50b2054 	str	r2, [fp, #-84]	; 0xffffffac
40703594:	e50bc03c 	str	ip, [fp, #-60]	; 0xffffffc4
40703598:	e591021c 	ldr	r0, [r1, #540]	; 0x21c
4070359c:	e5912220 	ldr	r2, [r1, #544]	; 0x220
407035a0:	e5917224 	ldr	r7, [r1, #548]	; 0x224
407035a4:	e79cc38e 	ldr	ip, [ip, lr, lsl #7]
407035a8:	e50bd044 	str	sp, [fp, #-68]	; 0xffffffbc
407035ac:	e24dd030 	sub	sp, sp, #48	; 0x30
407035b0:	e50b7024 	str	r7, [fp, #-36]	; 0xffffffdc
407035b4:	e7e67450 	ubfx	r7, r0, #8, #7
407035b8:	e50bc028 	str	ip, [fp, #-40]	; 0xffffffd8
407035bc:	e200c07f 	and	ip, r0, #127	; 0x7f
407035c0:	e50bc048 	str	ip, [fp, #-72]	; 0xffffffb8
407035c4:	e24d8004 	sub	r8, sp, #4
407035c8:	e58dc000 	str	ip, [sp]
407035cc:	e7e6c850 	ubfx	ip, r0, #16, #7
407035d0:	e7e60c50 	ubfx	r0, r0, #24, #7
407035d4:	e50b002c 	str	r0, [fp, #-44]	; 0xffffffd4
407035d8:	e58d000c 	str	r0, [sp, #12]
407035dc:	e202007f 	and	r0, r2, #127	; 0x7f
407035e0:	e50b004c 	str	r0, [fp, #-76]	; 0xffffffb4
407035e4:	e28d3024 	add	r3, sp, #36	; 0x24
407035e8:	e58d0010 	str	r0, [sp, #16]
407035ec:	e7e60452 	ubfx	r0, r2, #8, #7
407035f0:	e50b0050 	str	r0, [fp, #-80]	; 0xffffffb0
407035f4:	e58d0014 	str	r0, [sp, #20]
407035f8:	e7e60852 	ubfx	r0, r2, #16, #7
407035fc:	e7e62c52 	ubfx	r2, r2, #24, #7
40703600:	e50b2030 	str	r2, [fp, #-48]	; 0xffffffd0
40703604:	e58d201c 	str	r2, [sp, #28]
40703608:	e51b2024 	ldr	r2, [fp, #-36]	; 0xffffffdc
4070360c:	e58d7004 	str	r7, [sp, #4]
40703610:	e202207f 	and	r2, r2, #127	; 0x7f
40703614:	e50b2034 	str	r2, [fp, #-52]	; 0xffffffcc
40703618:	e58d2020 	str	r2, [sp, #32]
4070361c:	e51b2028 	ldr	r2, [fp, #-40]	; 0xffffffd8
40703620:	e58dc008 	str	ip, [sp, #8]
40703624:	e7e82052 	ubfx	r2, r2, #0, #9
40703628:	e50b2038 	str	r2, [fp, #-56]	; 0xffffffc8
4070362c:	e58d2024 	str	r2, [sp, #36]	; 0x24
40703630:	e3e02000 	mvn	r2, #0
40703634:	e58d0018 	str	r0, [sp, #24]
40703638:	e50b3058 	str	r3, [fp, #-88]	; 0xffffffa8
4070363c:	e5b83004 	ldr	r3, [r8, #4]!
40703640:	e1520003 	cmp	r2, r3
40703644:	21a02003 	movcs	r2, r3
40703648:	e51b3058 	ldr	r3, [fp, #-88]	; 0xffffffa8
4070364c:	e1530008 	cmp	r3, r8
40703650:	1afffff9 	bne	4070363c <ddr_hw_training_ctl+0x2ac>
40703654:	e04cc002 	sub	ip, ip, r2
40703658:	e51b3048 	ldr	r3, [fp, #-72]	; 0xffffffb8
4070365c:	e0477002 	sub	r7, r7, r2
40703660:	e0400002 	sub	r0, r0, r2
40703664:	e1a0c80c 	lsl	ip, ip, #16
40703668:	e0433002 	sub	r3, r3, r2
4070366c:	e18c7407 	orr	r7, ip, r7, lsl #8
40703670:	e1a00800 	lsl	r0, r0, #16
40703674:	e1877003 	orr	r7, r7, r3
40703678:	e51b302c 	ldr	r3, [fp, #-44]	; 0xffffffd4
4070367c:	e51bc034 	ldr	ip, [fp, #-52]	; 0xffffffcc
40703680:	e28ee001 	add	lr, lr, #1
40703684:	e0433002 	sub	r3, r3, r2
40703688:	e51b8038 	ldr	r8, [fp, #-56]	; 0xffffffc8
4070368c:	e04cc002 	sub	ip, ip, r2
40703690:	e1877c03 	orr	r7, r7, r3, lsl #24
40703694:	e51b3050 	ldr	r3, [fp, #-80]	; 0xffffffb0
40703698:	e581721c 	str	r7, [r1, #540]	; 0x21c
4070369c:	e0433002 	sub	r3, r3, r2
407036a0:	e1800403 	orr	r0, r0, r3, lsl #8
407036a4:	e51b304c 	ldr	r3, [fp, #-76]	; 0xffffffb4
407036a8:	e0433002 	sub	r3, r3, r2
407036ac:	e1800003 	orr	r0, r0, r3
407036b0:	e51b3030 	ldr	r3, [fp, #-48]	; 0xffffffd0
407036b4:	e0433002 	sub	r3, r3, r2
407036b8:	e0482002 	sub	r2, r8, r2
407036bc:	e1800c03 	orr	r0, r0, r3, lsl #24
407036c0:	e51b3024 	ldr	r3, [fp, #-36]	; 0xffffffdc
407036c4:	e5810220 	str	r0, [r1, #544]	; 0x220
407036c8:	e3c3307f 	bic	r3, r3, #127	; 0x7f
407036cc:	e18c3003 	orr	r3, ip, r3
407036d0:	e51bc028 	ldr	ip, [fp, #-40]	; 0xffffffd8
407036d4:	e5813224 	str	r3, [r1, #548]	; 0x224
407036d8:	e51b303c 	ldr	r3, [fp, #-60]	; 0xffffffc4
407036dc:	e3cccf7f 	bic	ip, ip, #508	; 0x1fc
407036e0:	e51b1054 	ldr	r1, [fp, #-84]	; 0xffffffac
407036e4:	e3ccc003 	bic	ip, ip, #3
407036e8:	e182200c 	orr	r2, r2, ip
407036ec:	e7832001 	str	r2, [r3, r1]
407036f0:	e51bd044 	ldr	sp, [fp, #-68]	; 0xffffffbc
407036f4:	eaffff45 	b	40703410 <ddr_hw_training_ctl+0x80>
407036f8:	e1a00004 	mov	r0, r4
407036fc:	ebfffac0 	bl	40702204 <ddr_hw_training_process>
40703700:	e08a7000 	add	r7, sl, r0
40703704:	eaffff65 	b	407034a0 <ddr_hw_training_ctl+0x110>
40703708:	100303f0 	.word	0x100303f0

4070370c <ddr_hw_training>:
4070370c:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40703710:	e1a04000 	mov	r4, r0
40703714:	e24dd080 	sub	sp, sp, #128	; 0x80
40703718:	e3a01001 	mov	r1, #1
4070371c:	e28d0048 	add	r0, sp, #72	; 0x48
40703720:	e1a06004 	mov	r6, r4
40703724:	eb000241 	bl	40704030 <ddr_training_save_reg_custom>
40703728:	e3a07000 	mov	r7, #0
4070372c:	e58d7004 	str	r7, [sp, #4]
40703730:	e594303c 	ldr	r3, [r4, #60]	; 0x3c
40703734:	e1530007 	cmp	r3, r7
40703738:	8a000004 	bhi	40703750 <ddr_hw_training+0x44>
4070373c:	e28d0048 	add	r0, sp, #72	; 0x48
40703740:	eb00023b 	bl	40704034 <ddr_training_restore_reg_custom>
40703744:	e59d0004 	ldr	r0, [sp, #4]
40703748:	e28dd080 	add	sp, sp, #128	; 0x80
4070374c:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40703750:	e584705c 	str	r7, [r4, #92]	; 0x5c
40703754:	e3a02000 	mov	r2, #0
40703758:	e5963000 	ldr	r3, [r6]
4070375c:	e3a0500c 	mov	r5, #12
40703760:	e28da018 	add	sl, sp, #24
40703764:	e5843040 	str	r3, [r4, #64]	; 0x40
40703768:	e596800c 	ldr	r8, [r6, #12]
4070376c:	e584a074 	str	sl, [r4, #116]	; 0x74
40703770:	e5963008 	ldr	r3, [r6, #8]
40703774:	e1530002 	cmp	r3, r2
40703778:	8a000026 	bhi	40703818 <ddr_hw_training+0x10c>
4070377c:	e3a0b03c 	mov	fp, #60	; 0x3c
40703780:	e3a05000 	mov	r5, #0
40703784:	e58d5000 	str	r5, [sp]
40703788:	e1550008 	cmp	r5, r8
4070378c:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703790:	1a00002a 	bne	40703840 <ddr_hw_training+0x134>
40703794:	e3550002 	cmp	r5, #2
40703798:	1a000010 	bne	407037e0 <ddr_hw_training+0xd4>
4070379c:	e3a0203c 	mov	r2, #60	; 0x3c
407037a0:	e3a05000 	mov	r5, #0
407037a4:	e0234392 	mla	r3, r2, r3, r4
407037a8:	e28d8024 	add	r8, sp, #36	; 0x24
407037ac:	e1a0b005 	mov	fp, r5
407037b0:	e3a0a001 	mov	sl, #1
407037b4:	e5933010 	ldr	r3, [r3, #16]
407037b8:	e58d3008 	str	r3, [sp, #8]
407037bc:	e5943060 	ldr	r3, [r4, #96]	; 0x60
407037c0:	e58d300c 	str	r3, [sp, #12]
407037c4:	e59d3008 	ldr	r3, [sp, #8]
407037c8:	e1530005 	cmp	r3, r5
407037cc:	1a000048 	bne	407038f4 <ddr_hw_training+0x1e8>
407037d0:	e59d300c 	ldr	r3, [sp, #12]
407037d4:	e5940040 	ldr	r0, [r4, #64]	; 0x40
407037d8:	e5843060 	str	r3, [r4, #96]	; 0x60
407037dc:	ebfffaf1 	bl	407023a8 <ddr_phy_cfg_update>
407037e0:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
407037e4:	e3a0503c 	mov	r5, #60	; 0x3c
407037e8:	e3a02000 	mov	r2, #0
407037ec:	e0050395 	mul	r5, r5, r3
407037f0:	e0848005 	add	r8, r4, r5
407037f4:	e5983008 	ldr	r3, [r8, #8]
407037f8:	e1530002 	cmp	r3, r2
407037fc:	8a00004f 	bhi	40703940 <ddr_hw_training+0x234>
40703800:	e89d000c 	ldm	sp, {r2, r3}
40703804:	e2877001 	add	r7, r7, #1
40703808:	e286603c 	add	r6, r6, #60	; 0x3c
4070380c:	e0833002 	add	r3, r3, r2
40703810:	e58d3004 	str	r3, [sp, #4]
40703814:	eaffffc5 	b	40703730 <ddr_hw_training+0x24>
40703818:	e0236295 	mla	r3, r5, r2, r6
4070381c:	e5930014 	ldr	r0, [r3, #20]
40703820:	e28d3010 	add	r3, sp, #16
40703824:	e5901108 	ldr	r1, [r0, #264]	; 0x108
40703828:	e7831102 	str	r1, [r3, r2, lsl #2]
4070382c:	e3c11eff 	bic	r1, r1, #4080	; 0xff0
40703830:	e3c1100f 	bic	r1, r1, #15
40703834:	ebfff9de 	bl	40701fb4 <ddr_training_set_timing>
40703838:	e2822001 	add	r2, r2, #1
4070383c:	eaffffcb 	b	40703770 <ddr_hw_training+0x64>
40703840:	e002039b 	mul	r2, fp, r3
40703844:	e2851005 	add	r1, r5, #5
40703848:	e5845060 	str	r5, [r4, #96]	; 0x60
4070384c:	e1a00004 	mov	r0, r4
40703850:	e0823181 	add	r3, r2, r1, lsl #3
40703854:	e5942040 	ldr	r2, [r4, #64]	; 0x40
40703858:	e0843003 	add	r3, r4, r3
4070385c:	e5933008 	ldr	r3, [r3, #8]
40703860:	e5843048 	str	r3, [r4, #72]	; 0x48
40703864:	e5923048 	ldr	r3, [r2, #72]	; 0x48
40703868:	e3c3300f 	bic	r3, r3, #15
4070386c:	e1833005 	orr	r3, r3, r5
40703870:	e5823048 	str	r3, [r2, #72]	; 0x48
40703874:	ebfffec5 	bl	40703390 <ddr_hw_training_ctl>
40703878:	e59d3000 	ldr	r3, [sp]
4070387c:	e3580002 	cmp	r8, #2
40703880:	e0833000 	add	r3, r3, r0
40703884:	e58d3000 	str	r3, [sp]
40703888:	1affffd4 	bne	407037e0 <ddr_hw_training+0xd4>
4070388c:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703890:	e08a1205 	add	r1, sl, r5, lsl #4
40703894:	e281100c 	add	r1, r1, #12
40703898:	e3a02000 	mov	r2, #0
4070389c:	e023439b 	mla	r3, fp, r3, r4
407038a0:	e593c010 	ldr	ip, [r3, #16]
407038a4:	e5943040 	ldr	r3, [r4, #64]	; 0x40
407038a8:	e2833f8b 	add	r3, r3, #556	; 0x22c
407038ac:	e1a00003 	mov	r0, r3
407038b0:	e15c0002 	cmp	ip, r2
407038b4:	1a000004 	bne	407038cc <ddr_hw_training+0x1c0>
407038b8:	e3550001 	cmp	r5, #1
407038bc:	13a01000 	movne	r1, #0
407038c0:	1a000008 	bne	407038e8 <ddr_hw_training+0x1dc>
407038c4:	e2855001 	add	r5, r5, #1
407038c8:	eaffffae 	b	40703788 <ddr_hw_training+0x7c>
407038cc:	e490e080 	ldr	lr, [r0], #128	; 0x80
407038d0:	e2822001 	add	r2, r2, #1
407038d4:	e5a1e004 	str	lr, [r1, #4]!
407038d8:	eafffff4 	b	407038b0 <ddr_hw_training+0x1a4>
407038dc:	e79a0101 	ldr	r0, [sl, r1, lsl #2]
407038e0:	e2811001 	add	r1, r1, #1
407038e4:	e4830080 	str	r0, [r3], #128	; 0x80
407038e8:	e1520001 	cmp	r2, r1
407038ec:	1afffffa 	bne	407038dc <ddr_hw_training+0x1d0>
407038f0:	eafffff3 	b	407038c4 <ddr_hw_training+0x1b8>
407038f4:	e5b8c004 	ldr	ip, [r8, #4]!
407038f8:	e5943040 	ldr	r3, [r4, #64]	; 0x40
407038fc:	e7e8105c 	ubfx	r1, ip, #0, #9
40703900:	e5845054 	str	r5, [r4, #84]	; 0x54
40703904:	e5980010 	ldr	r0, [r8, #16]
40703908:	e7e82050 	ubfx	r2, r0, #0, #9
4070390c:	e1510002 	cmp	r1, r2
40703910:	82833f8b 	addhi	r3, r3, #556	; 0x22c
40703914:	92833f8b 	addls	r3, r3, #556	; 0x22c
40703918:	80411002 	subhi	r1, r1, r2
4070391c:	90421001 	subls	r1, r2, r1
40703920:	97830385 	strls	r0, [r3, r5, lsl #7]
40703924:	e1a00004 	mov	r0, r4
40703928:	8783c385 	strhi	ip, [r3, r5, lsl #7]
4070392c:	e2855001 	add	r5, r5, #1
40703930:	8584a060 	strhi	sl, [r4, #96]	; 0x60
40703934:	9584b060 	strls	fp, [r4, #96]	; 0x60
40703938:	ebfffb3a 	bl	40702628 <ddr_rdqs_sync_rank_rdq>
4070393c:	eaffffa0 	b	407037c4 <ddr_hw_training+0xb8>
40703940:	e3a0300c 	mov	r3, #12
40703944:	e28d1010 	add	r1, sp, #16
40703948:	e0235293 	mla	r3, r3, r2, r5
4070394c:	e7911102 	ldr	r1, [r1, r2, lsl #2]
40703950:	e0843003 	add	r3, r4, r3
40703954:	e5930014 	ldr	r0, [r3, #20]
40703958:	ebfff995 	bl	40701fb4 <ddr_training_set_timing>
4070395c:	e2822001 	add	r2, r2, #1
40703960:	eaffffa3 	b	407037f4 <ddr_hw_training+0xe8>

40703964 <ddr_vref_training>:
40703964:	e92d45f0 	push	{r4, r5, r6, r7, r8, sl, lr}
40703968:	e1a04000 	mov	r4, r0
4070396c:	e5903060 	ldr	r3, [r0, #96]	; 0x60
40703970:	e24ddf57 	sub	sp, sp, #348	; 0x15c
40703974:	e5902040 	ldr	r2, [r0, #64]	; 0x40
40703978:	e28d5004 	add	r5, sp, #4
4070397c:	e590e064 	ldr	lr, [r0, #100]	; 0x64
40703980:	e1a0c503 	lsl	ip, r3, #10
40703984:	e2823f87 	add	r3, r2, #540	; 0x21c
40703988:	e082100c 	add	r1, r2, ip
4070398c:	e083300c 	add	r3, r3, ip
40703990:	e594c05c 	ldr	ip, [r4, #92]	; 0x5c
40703994:	e3a0203c 	mov	r2, #60	; 0x3c
40703998:	e1a0640e 	lsl	r6, lr, #8
4070399c:	e0860001 	add	r0, r6, r1
407039a0:	e2811e21 	add	r1, r1, #528	; 0x210
407039a4:	e00c0c92 	mul	ip, r2, ip
407039a8:	e3a0200c 	mov	r2, #12
407039ac:	e022ce92 	mla	r2, r2, lr, ip
407039b0:	e2800e21 	add	r0, r0, #528	; 0x210
407039b4:	e0833006 	add	r3, r3, r6
407039b8:	e0842002 	add	r2, r4, r2
407039bc:	e5922018 	ldr	r2, [r2, #24]
407039c0:	e082e08e 	add	lr, r2, lr, lsl #1
407039c4:	e1a02005 	mov	r2, r5
407039c8:	e081138e 	add	r1, r1, lr, lsl #7
407039cc:	e1510000 	cmp	r1, r0
407039d0:	1a00002e 	bne	40703a90 <ddr_vref_training+0x12c>
407039d4:	e3a02f41 	mov	r2, #260	; 0x104
407039d8:	e3a01000 	mov	r1, #0
407039dc:	e28d0054 	add	r0, sp, #84	; 0x54
407039e0:	ebfff8fb 	bl	40701dd4 <ddrtr_memset>
407039e4:	e5943050 	ldr	r3, [r4, #80]	; 0x50
407039e8:	e3530001 	cmp	r3, #1
407039ec:	03a06000 	moveq	r6, #0
407039f0:	03a0700c 	moveq	r7, #12
407039f4:	03a0803c 	moveq	r8, #60	; 0x3c
407039f8:	0a00003d 	beq	40703af4 <ddr_vref_training+0x190>
407039fc:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703a00:	e3a0203c 	mov	r2, #60	; 0x3c
40703a04:	e5941060 	ldr	r1, [r4, #96]	; 0x60
40703a08:	e0234392 	mla	r3, r2, r3, r4
40703a0c:	e5932004 	ldr	r2, [r3, #4]
40703a10:	e5943044 	ldr	r3, [r4, #68]	; 0x44
40703a14:	e2833060 	add	r3, r3, #96	; 0x60
40703a18:	e7937101 	ldr	r7, [r3, r1, lsl #2]
40703a1c:	e2423006 	sub	r3, r2, #6
40703a20:	e3d33004 	bics	r3, r3, #4
40703a24:	1a00004b 	bne	40703b58 <ddr_vref_training+0x1f4>
40703a28:	e3520006 	cmp	r2, #6
40703a2c:	e3a06000 	mov	r6, #0
40703a30:	17e17557 	ubfxne	r7, r7, #10, #2
40703a34:	e3a0800c 	mov	r8, #12
40703a38:	03a07001 	moveq	r7, #1
40703a3c:	e3a0a03c 	mov	sl, #60	; 0x3c
40703a40:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703a44:	e5942064 	ldr	r2, [r4, #100]	; 0x64
40703a48:	e003039a 	mul	r3, sl, r3
40703a4c:	e0233298 	mla	r3, r8, r2, r3
40703a50:	e0843003 	add	r3, r4, r3
40703a54:	e5933018 	ldr	r3, [r3, #24]
40703a58:	e1530006 	cmp	r3, r6
40703a5c:	9a00002c 	bls	40703b14 <ddr_vref_training+0x1b0>
40703a60:	e3570001 	cmp	r7, #1
40703a64:	e0862082 	add	r2, r6, r2, lsl #1
40703a68:	e5842054 	str	r2, [r4, #84]	; 0x54
40703a6c:	1a000002 	bne	40703a7c <ddr_vref_training+0x118>
40703a70:	e3c63002 	bic	r3, r6, #2
40703a74:	e3530001 	cmp	r3, #1
40703a78:	0a000002 	beq	40703a88 <ddr_vref_training+0x124>
40703a7c:	e28d1054 	add	r1, sp, #84	; 0x54
40703a80:	e1a00004 	mov	r0, r4
40703a84:	ebfffd1b 	bl	40702ef8 <ddr_vref_cal>
40703a88:	e2866001 	add	r6, r6, #1
40703a8c:	eaffffeb 	b	40703a40 <ddr_vref_training+0xdc>
40703a90:	e594c050 	ldr	ip, [r4, #80]	; 0x50
40703a94:	e2800080 	add	r0, r0, #128	; 0x80
40703a98:	e2822004 	add	r2, r2, #4
40703a9c:	e2833080 	add	r3, r3, #128	; 0x80
40703aa0:	e35c0002 	cmp	ip, #2
40703aa4:	0510c080 	ldreq	ip, [r0, #-128]	; 0xffffff80
40703aa8:	1513c080 	ldrne	ip, [r3, #-128]	; 0xffffff80
40703aac:	0502c004 	streq	ip, [r2, #-4]
40703ab0:	0510c07c 	ldreq	ip, [r0, #-124]	; 0xffffff84
40703ab4:	1502c004 	strne	ip, [r2, #-4]
40703ab8:	1513c07c 	ldrne	ip, [r3, #-124]	; 0xffffff84
40703abc:	0582c00c 	streq	ip, [r2, #12]
40703ac0:	0510c078 	ldreq	ip, [r0, #-120]	; 0xffffff88
40703ac4:	1582c00c 	strne	ip, [r2, #12]
40703ac8:	0582c03c 	streq	ip, [r2, #60]	; 0x3c
40703acc:	eaffffbe 	b	407039cc <ddr_vref_training+0x68>
40703ad0:	e0862082 	add	r2, r6, r2, lsl #1
40703ad4:	e5842054 	str	r2, [r4, #84]	; 0x54
40703ad8:	e3c22002 	bic	r2, r2, #2
40703adc:	e3520001 	cmp	r2, #1
40703ae0:	0a000002 	beq	40703af0 <ddr_vref_training+0x18c>
40703ae4:	e28d1054 	add	r1, sp, #84	; 0x54
40703ae8:	e1a00004 	mov	r0, r4
40703aec:	ebfffd01 	bl	40702ef8 <ddr_vref_cal>
40703af0:	e2866001 	add	r6, r6, #1
40703af4:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703af8:	e5942064 	ldr	r2, [r4, #100]	; 0x64
40703afc:	e0030398 	mul	r3, r8, r3
40703b00:	e0233297 	mla	r3, r7, r2, r3
40703b04:	e0843003 	add	r3, r4, r3
40703b08:	e5933018 	ldr	r3, [r3, #24]
40703b0c:	e1530006 	cmp	r3, r6
40703b10:	8affffee 	bhi	40703ad0 <ddr_vref_training+0x16c>
40703b14:	e5943060 	ldr	r3, [r4, #96]	; 0x60
40703b18:	e3a01000 	mov	r1, #0
40703b1c:	e5940040 	ldr	r0, [r4, #64]	; 0x40
40703b20:	e3a0c00c 	mov	ip, #12
40703b24:	e3a0e03c 	mov	lr, #60	; 0x3c
40703b28:	e0800503 	add	r0, r0, r3, lsl #10
40703b2c:	e594205c 	ldr	r2, [r4, #92]	; 0x5c
40703b30:	e5943064 	ldr	r3, [r4, #100]	; 0x64
40703b34:	e002029e 	mul	r2, lr, r2
40703b38:	e022239c 	mla	r2, ip, r3, r2
40703b3c:	e0842002 	add	r2, r4, r2
40703b40:	e5922018 	ldr	r2, [r2, #24]
40703b44:	e1510002 	cmp	r1, r2
40703b48:	3a000005 	bcc	40703b64 <ddr_vref_training+0x200>
40703b4c:	e28d1054 	add	r1, sp, #84	; 0x54
40703b50:	e1a00004 	mov	r0, r4
40703b54:	eb000106 	bl	40703f74 <ddr_result_data_save>
40703b58:	e3a00000 	mov	r0, #0
40703b5c:	e28ddf57 	add	sp, sp, #348	; 0x15c
40703b60:	e8bd85f0 	pop	{r4, r5, r6, r7, r8, sl, pc}
40703b64:	e5942050 	ldr	r2, [r4, #80]	; 0x50
40703b68:	e0813083 	add	r3, r1, r3, lsl #1
40703b6c:	e2855004 	add	r5, r5, #4
40703b70:	e2811001 	add	r1, r1, #1
40703b74:	e3520002 	cmp	r2, #2
40703b78:	e1a03383 	lsl	r3, r3, #7
40703b7c:	e5152004 	ldr	r2, [r5, #-4]
40703b80:	e0833000 	add	r3, r3, r0
40703b84:	05832210 	streq	r2, [r3, #528]	; 0x210
40703b88:	0595200c 	ldreq	r2, [r5, #12]
40703b8c:	1583221c 	strne	r2, [r3, #540]	; 0x21c
40703b90:	1595200c 	ldrne	r2, [r5, #12]
40703b94:	05832214 	streq	r2, [r3, #532]	; 0x214
40703b98:	0595203c 	ldreq	r2, [r5, #60]	; 0x3c
40703b9c:	15832220 	strne	r2, [r3, #544]	; 0x220
40703ba0:	05832218 	streq	r2, [r3, #536]	; 0x218
40703ba4:	eaffffe0 	b	40703b2c <ddr_vref_training+0x1c8>

40703ba8 <ddr_vref_training_func>:
40703ba8:	e92d4030 	push	{r4, r5, lr}
40703bac:	e24dd03c 	sub	sp, sp, #60	; 0x3c
40703bb0:	e1a04000 	mov	r4, r0
40703bb4:	e3a02401 	mov	r2, #16777216	; 0x1000000
40703bb8:	e1a0100d 	mov	r1, sp
40703bbc:	ebfffa05 	bl	407023d8 <ddr_training_save_reg>
40703bc0:	e1a00004 	mov	r0, r4
40703bc4:	ebfff9dd 	bl	40702340 <ddr_training_switch_axi>
40703bc8:	e3a01002 	mov	r1, #2
40703bcc:	e1a00004 	mov	r0, r4
40703bd0:	ebfffb12 	bl	40702820 <ddr_ddrt_init>
40703bd4:	e5942048 	ldr	r2, [r4, #72]	; 0x48
40703bd8:	e3a03001 	mov	r3, #1
40703bdc:	e584306c 	str	r3, [r4, #108]	; 0x6c
40703be0:	e3120401 	tst	r2, #16777216	; 0x1000000
40703be4:	0a000009 	beq	40703c10 <ddr_vref_training_func+0x68>
40703be8:	e3a05000 	mov	r5, #0
40703bec:	e5943048 	ldr	r3, [r4, #72]	; 0x48
40703bf0:	e3130402 	tst	r3, #33554432	; 0x2000000
40703bf4:	0a00000a 	beq	40703c24 <ddr_vref_training_func+0x7c>
40703bf8:	e1a00004 	mov	r0, r4
40703bfc:	e1a0100d 	mov	r1, sp
40703c00:	ebfffa31 	bl	407024cc <ddr_training_restore_reg>
40703c04:	e1a00005 	mov	r0, r5
40703c08:	e28dd03c 	add	sp, sp, #60	; 0x3c
40703c0c:	e8bd8030 	pop	{r4, r5, pc}
40703c10:	e5843050 	str	r3, [r4, #80]	; 0x50
40703c14:	e1a00004 	mov	r0, r4
40703c18:	ebffff51 	bl	40703964 <ddr_vref_training>
40703c1c:	e1a05000 	mov	r5, r0
40703c20:	eafffff1 	b	40703bec <ddr_vref_training_func+0x44>
40703c24:	e3a03002 	mov	r3, #2
40703c28:	e1a00004 	mov	r0, r4
40703c2c:	e5843050 	str	r3, [r4, #80]	; 0x50
40703c30:	ebffff4b 	bl	40703964 <ddr_vref_training>
40703c34:	e0855000 	add	r5, r5, r0
40703c38:	eaffffee 	b	40703bf8 <ddr_vref_training_func+0x50>

40703c3c <ddr_wl_func>:
40703c3c:	e3a00000 	mov	r0, #0
40703c40:	e12fff1e 	bx	lr

40703c44 <ddr_gating_func>:
40703c44:	e3a00000 	mov	r0, #0
40703c48:	e12fff1e 	bx	lr

40703c4c <ddr_ac_training_func>:
40703c4c:	e3a00000 	mov	r0, #0
40703c50:	e12fff1e 	bx	lr

40703c54 <ddr_lpca_training_func>:
40703c54:	e3a00000 	mov	r0, #0
40703c58:	e12fff1e 	bx	lr

40703c5c <ddr_dcc_training_func>:
40703c5c:	e3a00000 	mov	r0, #0
40703c60:	e12fff1e 	bx	lr

40703c64 <ddr_pcode_training>:
40703c64:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40703c68:	e3a07000 	mov	r7, #0
40703c6c:	e59fb140 	ldr	fp, [pc, #320]	; 40703db4 <ddr_pcode_training+0x150>
40703c70:	e24dd040 	sub	sp, sp, #64	; 0x40
40703c74:	e1a06000 	mov	r6, r0
40703c78:	e1a0a000 	mov	sl, r0
40703c7c:	e1a08007 	mov	r8, r7
40703c80:	e596203c 	ldr	r2, [r6, #60]	; 0x3c
40703c84:	e1520007 	cmp	r2, r7
40703c88:	8a000002 	bhi	40703c98 <ddr_pcode_training+0x34>
40703c8c:	e1a00008 	mov	r0, r8
40703c90:	e28dd040 	add	sp, sp, #64	; 0x40
40703c94:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40703c98:	e586705c 	str	r7, [r6, #92]	; 0x5c
40703c9c:	e3a05001 	mov	r5, #1
40703ca0:	e59a2000 	ldr	r2, [sl]
40703ca4:	e1a05715 	lsl	r5, r5, r7
40703ca8:	e3855701 	orr	r5, r5, #262144	; 0x40000
40703cac:	e5862040 	str	r2, [r6, #64]	; 0x40
40703cb0:	e59a202c 	ldr	r2, [sl, #44]	; 0x2c
40703cb4:	e0155002 	ands	r5, r5, r2
40703cb8:	e5862048 	str	r2, [r6, #72]	; 0x48
40703cbc:	1a000039 	bne	40703da8 <ddr_pcode_training+0x144>
40703cc0:	e3a02701 	mov	r2, #262144	; 0x40000
40703cc4:	e28d1008 	add	r1, sp, #8
40703cc8:	e1a00006 	mov	r0, r6
40703ccc:	ebfff9c1 	bl	407023d8 <ddr_training_save_reg>
40703cd0:	e5964040 	ldr	r4, [r6, #64]	; 0x40
40703cd4:	e301204c 	movw	r2, #4172	; 0x104c
40703cd8:	e59fc0d8 	ldr	ip, [pc, #216]	; 40703db8 <ddr_pcode_training+0x154>
40703cdc:	e0840002 	add	r0, r4, r2
40703ce0:	e7941002 	ldr	r1, [r4, r2]
40703ce4:	e3811001 	orr	r1, r1, #1
40703ce8:	e7841002 	str	r1, [r4, r2]
40703cec:	e590e000 	ldr	lr, [r0]
40703cf0:	e2855001 	add	r5, r5, #1
40703cf4:	e155000c 	cmp	r5, ip
40703cf8:	83a01000 	movhi	r1, #0
40703cfc:	93a01001 	movls	r1, #1
40703d00:	e1d137ae 	bics	r3, r1, lr, lsr #15
40703d04:	e58d3004 	str	r3, [sp, #4]
40703d08:	1afffff7 	bne	40703cec <ddr_pcode_training+0x88>
40703d0c:	e155000c 	cmp	r5, ip
40703d10:	83e01000 	mvnhi	r1, #0
40703d14:	8a00001f 	bhi	40703d98 <ddr_pcode_training+0x134>
40703d18:	e7945002 	ldr	r5, [r4, r2]
40703d1c:	e7940002 	ldr	r0, [r4, r2]
40703d20:	e3c00001 	bic	r0, r0, #1
40703d24:	e7840002 	str	r0, [r4, r2]
40703d28:	eb0000c2 	bl	40704038 <ddr_get_cksel>
40703d2c:	e1a05825 	lsr	r5, r5, #16
40703d30:	e3a02059 	mov	r2, #89	; 0x59
40703d34:	e59f3080 	ldr	r3, [pc, #128]	; 40703dbc <ddr_pcode_training+0x158>
40703d38:	e0020592 	mul	r2, r2, r5
40703d3c:	e0000290 	mul	r0, r0, r2
40703d40:	e59f2078 	ldr	r2, [pc, #120]	; 40703dc0 <ddr_pcode_training+0x15c>
40703d44:	e0810390 	umull	r0, r1, r0, r3
40703d48:	e5940028 	ldr	r0, [r4, #40]	; 0x28
40703d4c:	e3c0083f 	bic	r0, r0, #4128768	; 0x3f0000
40703d50:	e04222a1 	sub	r2, r2, r1, lsr #5
40703d54:	e59d1004 	ldr	r1, [sp, #4]
40703d58:	e0832b92 	umull	r2, r3, r2, fp
40703d5c:	e1a026a3 	lsr	r2, r3, #13
40703d60:	e3520024 	cmp	r2, #36	; 0x24
40703d64:	23a02024 	movcs	r2, #36	; 0x24
40703d68:	e3520014 	cmp	r2, #20
40703d6c:	33a02014 	movcc	r2, #20
40703d70:	e1800802 	orr	r0, r0, r2, lsl #16
40703d74:	e5840028 	str	r0, [r4, #40]	; 0x28
40703d78:	e594c170 	ldr	ip, [r4, #368]	; 0x170
40703d7c:	e3cc0c01 	bic	r0, ip, #256	; 0x100
40703d80:	e5840170 	str	r0, [r4, #368]	; 0x170
40703d84:	e5940174 	ldr	r0, [r4, #372]	; 0x174
40703d88:	e3c0043f 	bic	r0, r0, #1056964608	; 0x3f000000
40703d8c:	e1802c02 	orr	r2, r0, r2, lsl #24
40703d90:	e5842174 	str	r2, [r4, #372]	; 0x174
40703d94:	e584c170 	str	ip, [r4, #368]	; 0x170
40703d98:	e0888001 	add	r8, r8, r1
40703d9c:	e1a00006 	mov	r0, r6
40703da0:	e28d1008 	add	r1, sp, #8
40703da4:	ebfff9c8 	bl	407024cc <ddr_training_restore_reg>
40703da8:	e2877001 	add	r7, r7, #1
40703dac:	e28aa03c 	add	sl, sl, #60	; 0x3c
40703db0:	eaffffb2 	b	40703c80 <ddr_pcode_training+0x1c>
40703db4:	d1b71759 	.word	0xd1b71759
40703db8:	0001869f 	.word	0x0001869f
40703dbc:	1b4e81b5 	.word	0x1b4e81b5
40703dc0:	00077dd0 	.word	0x00077dd0

40703dc4 <ddr_training_console_if>:
40703dc4:	e3a00000 	mov	r0, #0
40703dc8:	e12fff1e 	bx	lr

40703dcc <ddr_training_boot_func>:
40703dcc:	e92d4030 	push	{r4, r5, lr}
40703dd0:	e1a04000 	mov	r4, r0
40703dd4:	e5901040 	ldr	r1, [r0, #64]	; 0x40
40703dd8:	e24dd03c 	sub	sp, sp, #60	; 0x3c
40703ddc:	e5913008 	ldr	r3, [r1, #8]
40703de0:	e3130020 	tst	r3, #32
40703de4:	0a000003 	beq	40703df8 <ddr_training_boot_func+0x2c>
40703de8:	e3e03000 	mvn	r3, #0
40703dec:	e3a00002 	mov	r0, #2
40703df0:	e1a02003 	mov	r2, r3
40703df4:	ebfff8e8 	bl	4070219c <ddr_training_stat>
40703df8:	e1a00004 	mov	r0, r4
40703dfc:	ebffff94 	bl	40703c54 <ddr_lpca_training_func>
40703e00:	e1a05000 	mov	r5, r0
40703e04:	e1a00004 	mov	r0, r4
40703e08:	ebffff8b 	bl	40703c3c <ddr_wl_func>
40703e0c:	e0855000 	add	r5, r5, r0
40703e10:	e1a00004 	mov	r0, r4
40703e14:	ebfffd24 	bl	407032ac <ddr_dataeye_training_func>
40703e18:	e0955000 	adds	r5, r5, r0
40703e1c:	0a000013 	beq	40703e70 <ddr_training_boot_func+0xa4>
40703e20:	e3a01601 	mov	r1, #1048576	; 0x100000
40703e24:	e1a00004 	mov	r0, r4
40703e28:	ebfff93d 	bl	40702324 <ddr_training_check_bypass>
40703e2c:	e3500000 	cmp	r0, #0
40703e30:	1a00000e 	bne	40703e70 <ddr_training_boot_func+0xa4>
40703e34:	e3a02601 	mov	r2, #1048576	; 0x100000
40703e38:	e1a0100d 	mov	r1, sp
40703e3c:	e1a00004 	mov	r0, r4
40703e40:	ebfff964 	bl	407023d8 <ddr_training_save_reg>
40703e44:	e1a00004 	mov	r0, r4
40703e48:	ebfffd32 	bl	40703318 <ddr_hw_dataeye_read>
40703e4c:	e1a0100d 	mov	r1, sp
40703e50:	e1a05000 	mov	r5, r0
40703e54:	e1a00004 	mov	r0, r4
40703e58:	ebfff99b 	bl	407024cc <ddr_training_restore_reg>
40703e5c:	e3a03001 	mov	r3, #1
40703e60:	e1a00004 	mov	r0, r4
40703e64:	e5843068 	str	r3, [r4, #104]	; 0x68
40703e68:	ebfffcf4 	bl	40703240 <ddr_dataeye_training>
40703e6c:	e0855000 	add	r5, r5, r0
40703e70:	e1a00004 	mov	r0, r4
40703e74:	ebffff72 	bl	40703c44 <ddr_gating_func>
40703e78:	e0855000 	add	r5, r5, r0
40703e7c:	e1a00004 	mov	r0, r4
40703e80:	ebffff48 	bl	40703ba8 <ddr_vref_training_func>
40703e84:	e0850000 	add	r0, r5, r0
40703e88:	e28dd03c 	add	sp, sp, #60	; 0x3c
40703e8c:	e8bd8030 	pop	{r4, r5, pc}

40703e90 <ddr_sw_training_func>:
40703e90:	e59f208c 	ldr	r2, [pc, #140]	; 40703f24 <ddr_sw_training_func+0x94>
40703e94:	e92d4030 	push	{r4, r5, lr}
40703e98:	e24dd07c 	sub	sp, sp, #124	; 0x7c
40703e9c:	e59230b4 	ldr	r3, [r2, #180]	; 0xb4
40703ea0:	e1a04002 	mov	r4, r2
40703ea4:	e1a03823 	lsr	r3, r3, #16
40703ea8:	e1a03803 	lsl	r3, r3, #16
40703eac:	e3833f85 	orr	r3, r3, #532	; 0x214
40703eb0:	e3833002 	orr	r3, r3, #2
40703eb4:	e58230b4 	str	r3, [r2, #180]	; 0xb4
40703eb8:	e59230a0 	ldr	r3, [r2, #160]	; 0xa0
40703ebc:	e3730001 	cmn	r3, #1
40703ec0:	1a000003 	bne	40703ed4 <ddr_sw_training_func+0x44>
40703ec4:	e59230a4 	ldr	r3, [r2, #164]	; 0xa4
40703ec8:	e3730001 	cmn	r3, #1
40703ecc:	03a04000 	moveq	r4, #0
40703ed0:	0a00000d 	beq	40703f0c <ddr_sw_training_func+0x7c>
40703ed4:	eb00002c 	bl	40703f8c <ddr_training_start>
40703ed8:	e3a05000 	mov	r5, #0
40703edc:	e1a0000d 	mov	r0, sp
40703ee0:	e58450b0 	str	r5, [r4, #176]	; 0xb0
40703ee4:	ebfffa41 	bl	407027f0 <ddr_training_cfg_init>
40703ee8:	e1a0000d 	mov	r0, sp
40703eec:	e58d5070 	str	r5, [sp, #112]	; 0x70
40703ef0:	ebfff802 	bl	40701f00 <ddr_training_all>
40703ef4:	e1a04000 	mov	r4, r0
40703ef8:	e1a0000d 	mov	r0, sp
40703efc:	ebffff56 	bl	40703c5c <ddr_dcc_training_func>
40703f00:	e0944000 	adds	r4, r4, r0
40703f04:	1a000003 	bne	40703f18 <ddr_sw_training_func+0x88>
40703f08:	eb00001e 	bl	40703f88 <ddr_training_suc>
40703f0c:	e1a00004 	mov	r0, r4
40703f10:	e28dd07c 	add	sp, sp, #124	; 0x7c
40703f14:	e8bd8030 	pop	{r4, r5, pc}
40703f18:	e1a00005 	mov	r0, r5
40703f1c:	ebffffa8 	bl	40703dc4 <ddr_training_console_if>
40703f20:	eafffff9 	b	40703f0c <ddr_sw_training_func+0x7c>
40703f24:	12020000 	.word	0x12020000

40703f28 <ddr_pcode_training_func>:
40703f28:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
40703f2c:	e24dd07c 	sub	sp, sp, #124	; 0x7c
40703f30:	e1a0000d 	mov	r0, sp
40703f34:	ebfffa2d 	bl	407027f0 <ddr_training_cfg_init>
40703f38:	e1a0000d 	mov	r0, sp
40703f3c:	ebffff48 	bl	40703c64 <ddr_pcode_training>
40703f40:	e28dd07c 	add	sp, sp, #124	; 0x7c
40703f44:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)

40703f48 <ddr_hw_training_func>:
40703f48:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
40703f4c:	e24dd07c 	sub	sp, sp, #124	; 0x7c
40703f50:	e1a0000d 	mov	r0, sp
40703f54:	ebfffa25 	bl	407027f0 <ddr_training_cfg_init>
40703f58:	e1a0000d 	mov	r0, sp
40703f5c:	ebfffdea 	bl	4070370c <ddr_hw_training>
40703f60:	e28dd07c 	add	sp, sp, #124	; 0x7c
40703f64:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)

40703f68 <ddr_sw_training_if>:
40703f68:	eaffffc8 	b	40703e90 <ddr_sw_training_func>

40703f6c <ddr_hw_training_if>:
40703f6c:	eafffff5 	b	40703f48 <ddr_hw_training_func>

40703f70 <ddr_pcode_training_if>:
40703f70:	eaffffec 	b	40703f28 <ddr_pcode_training_func>

40703f74 <ddr_result_data_save>:
40703f74:	e12fff1e 	bx	lr

40703f78 <ddr_lpca_data_save>:
40703f78:	e12fff1e 	bx	lr

40703f7c <ddr_ddrt_get_test_addr>:
40703f7c:	e3a00101 	mov	r0, #1073741824	; 0x40000000
40703f80:	e12fff1e 	bx	lr

40703f84 <ddr_training_error>:
40703f84:	e12fff1e 	bx	lr

40703f88 <ddr_training_suc>:
40703f88:	e12fff1e 	bx	lr

40703f8c <ddr_training_start>:
40703f8c:	e12fff1e 	bx	lr

40703f90 <ddr_cmd_prepare_copy>:
40703f90:	e12fff1e 	bx	lr

40703f94 <ddr_cmd_site_save>:
40703f94:	e59f204c 	ldr	r2, [pc, #76]	; 40703fe8 <ddr_cmd_site_save+0x54>
40703f98:	e59f104c 	ldr	r1, [pc, #76]	; 40703fec <ddr_cmd_site_save+0x58>
40703f9c:	e5923010 	ldr	r3, [r2, #16]
40703fa0:	e581301c 	str	r3, [r1, #28]
40703fa4:	e3c33020 	bic	r3, r3, #32
40703fa8:	e5823010 	str	r3, [r2, #16]
40703fac:	e59f303c 	ldr	r3, [pc, #60]	; 40703ff0 <ddr_cmd_site_save+0x5c>
40703fb0:	e5932198 	ldr	r2, [r3, #408]	; 0x198
40703fb4:	e5812020 	str	r2, [r1, #32]
40703fb8:	e3822002 	orr	r2, r2, #2
40703fbc:	e5832198 	str	r2, [r3, #408]	; 0x198
40703fc0:	e320f000 	nop	{0}
40703fc4:	e5932198 	ldr	r2, [r3, #408]	; 0x198
40703fc8:	e3c22001 	bic	r2, r2, #1
40703fcc:	e5832198 	str	r2, [r3, #408]	; 0x198
40703fd0:	e59f201c 	ldr	r2, [pc, #28]	; 40703ff4 <ddr_cmd_site_save+0x60>
40703fd4:	e59230b0 	ldr	r3, [r2, #176]	; 0xb0
40703fd8:	e5813024 	str	r3, [r1, #36]	; 0x24
40703fdc:	e3c33102 	bic	r3, r3, #-2147483648	; 0x80000000
40703fe0:	e58230b0 	str	r3, [r2, #176]	; 0xb0
40703fe4:	e12fff1e 	bx	lr
40703fe8:	12028000 	.word	0x12028000
40703fec:	4073bda4 	.word	0x4073bda4
40703ff0:	12010000 	.word	0x12010000
40703ff4:	120dc000 	.word	0x120dc000

40703ff8 <ddr_cmd_site_restore>:
40703ff8:	e59f3024 	ldr	r3, [pc, #36]	; 40704024 <ddr_cmd_site_restore+0x2c>
40703ffc:	e59f2024 	ldr	r2, [pc, #36]	; 40704028 <ddr_cmd_site_restore+0x30>
40704000:	e593101c 	ldr	r1, [r3, #28]
40704004:	e5821010 	str	r1, [r2, #16]
40704008:	e2422906 	sub	r2, r2, #98304	; 0x18000
4070400c:	e5931020 	ldr	r1, [r3, #32]
40704010:	e5821198 	str	r1, [r2, #408]	; 0x198
40704014:	e5932024 	ldr	r2, [r3, #36]	; 0x24
40704018:	e59f300c 	ldr	r3, [pc, #12]	; 4070402c <ddr_cmd_site_restore+0x34>
4070401c:	e58320b0 	str	r2, [r3, #176]	; 0xb0
40704020:	e12fff1e 	bx	lr
40704024:	4073bda4 	.word	0x4073bda4
40704028:	12028000 	.word	0x12028000
4070402c:	120dc000 	.word	0x120dc000

40704030 <ddr_training_save_reg_custom>:
40704030:	e12fff1e 	bx	lr

40704034 <ddr_training_restore_reg_custom>:
40704034:	e12fff1e 	bx	lr

40704038 <ddr_get_cksel>:
40704038:	e59f3024 	ldr	r3, [pc, #36]	; 40704064 <ddr_get_cksel+0x2c>
4070403c:	e5933080 	ldr	r3, [r3, #128]	; 0x80
40704040:	e7e231d3 	ubfx	r3, r3, #3, #3
40704044:	e3530000 	cmp	r3, #0
40704048:	0a000003 	beq	4070405c <ddr_get_cksel+0x24>
4070404c:	e3530001 	cmp	r3, #1
40704050:	e30001c2 	movw	r0, #450	; 0x1c2
40704054:	13a00f4b 	movne	r0, #300	; 0x12c
40704058:	e12fff1e 	bx	lr
4070405c:	e3a00018 	mov	r0, #24
40704060:	e12fff1e 	bx	lr
40704064:	12010000 	.word	0x12010000

40704068 <uart_early_init>:
40704068:	e59f3028 	ldr	r3, [pc, #40]	; 40704098 <uart_base_addr_L0>
4070406c:	e3a02000 	mov	r2, #0
40704070:	e5832030 	str	r2, [r3, #48]	; 0x30
40704074:	e282200d 	add	r2, r2, #13
40704078:	e5832024 	str	r2, [r3, #36]	; 0x24
4070407c:	e3a02001 	mov	r2, #1
40704080:	e5832028 	str	r2, [r3, #40]	; 0x28
40704084:	e3a02070 	mov	r2, #112	; 0x70
40704088:	e583202c 	str	r2, [r3, #44]	; 0x2c
4070408c:	e59f2098 	ldr	r2, [pc, #152]	; 4070412c <uart_base_addr_L3+0x4>
40704090:	e5832030 	str	r2, [r3, #48]	; 0x30
40704094:	e12fff1e 	bx	lr

40704098 <uart_base_addr_L0>:
40704098:	12040000 	.word	0x12040000

4070409c <uart_early_puts>:
4070409c:	e59f1024 	ldr	r1, [pc, #36]	; 407040c8 <uart_base_addr_L1>
407040a0:	ea000004 	b	407040b8 <next_char>

407040a4 <output>:
407040a4:	e5913018 	ldr	r3, [r1, #24]
407040a8:	e3130020 	tst	r3, #32
407040ac:	1afffffc 	bne	407040a4 <output>
407040b0:	e5812000 	str	r2, [r1]
407040b4:	e2800001 	add	r0, r0, #1

407040b8 <next_char>:
407040b8:	e5d02000 	ldrb	r2, [r0]
407040bc:	e3520000 	cmp	r2, #0
407040c0:	1afffff7 	bne	407040a4 <output>
407040c4:	e12fff1e 	bx	lr

407040c8 <uart_base_addr_L1>:
407040c8:	12040000 	.word	0x12040000

407040cc <uart_early_put_hex>:
407040cc:	e59f1038 	ldr	r1, [pc, #56]	; 4070410c <uart_base_addr_L2>
407040d0:	e3a0201c 	mov	r2, #28

407040d4 <wait2>:
407040d4:	e5913018 	ldr	r3, [r1, #24]
407040d8:	e3130020 	tst	r3, #32
407040dc:	1afffffc 	bne	407040d4 <wait2>
407040e0:	e3a0300f 	mov	r3, #15
407040e4:	e0033230 	and	r3, r3, r0, lsr r2
407040e8:	e3530009 	cmp	r3, #9
407040ec:	d2833030 	addle	r3, r3, #48	; 0x30
407040f0:	c2833037 	addgt	r3, r3, #55	; 0x37
407040f4:	e5813000 	str	r3, [r1]
407040f8:	e3520000 	cmp	r2, #0
407040fc:	0a000001 	beq	40704108 <exit2>
40704100:	e2422004 	sub	r2, r2, #4
40704104:	eafffff2 	b	407040d4 <wait2>

40704108 <exit2>:
40704108:	e12fff1e 	bx	lr

4070410c <uart_base_addr_L2>:
4070410c:	12040000 	.word	0x12040000

40704110 <uart_early_putc>:
40704110:	e59f1010 	ldr	r1, [pc, #16]	; 40704128 <uart_base_addr_L3>

40704114 <wait3>:
40704114:	e5913018 	ldr	r3, [r1, #24]
40704118:	e3130020 	tst	r3, #32
4070411c:	1afffffc 	bne	40704114 <wait3>
40704120:	e5810000 	str	r0, [r1]
40704124:	e12fff1e 	bx	lr

40704128 <uart_base_addr_L3>:
40704128:	12040000 	.word	0x12040000
4070412c:	00000301 	.word	0x00000301

40704130 <__div0>:
40704130:	ea00013c 	b	40704628 <hang>

40704134 <sdhci_check_int_status>:
40704134:	e59f2040 	ldr	r2, [pc, #64]	; 4070417c <sdhci_check_int_status+0x48>
40704138:	e59fc040 	ldr	ip, [pc, #64]	; 40704180 <sdhci_check_int_status+0x4c>
4070413c:	e5923030 	ldr	r3, [r2, #48]	; 0x30
40704140:	e1100003 	tst	r0, r3
40704144:	1a000008 	bne	4070416c <sdhci_check_int_status+0x38>
40704148:	e2511001 	subs	r1, r1, #1
4070414c:	0a000008 	beq	40704174 <sdhci_check_int_status+0x40>
40704150:	e113000c 	tst	r3, ip
40704154:	1a000006 	bne	40704174 <sdhci_check_int_status+0x40>
40704158:	e3023711 	movw	r3, #10001	; 0x2711
4070415c:	e2533001 	subs	r3, r3, #1
40704160:	0afffff5 	beq	4070413c <sdhci_check_int_status+0x8>
40704164:	e320f000 	nop	{0}
40704168:	eafffffb 	b	4070415c <sdhci_check_int_status+0x28>
4070416c:	e3a00000 	mov	r0, #0
40704170:	e12fff1e 	bx	lr
40704174:	e3e00000 	mvn	r0, #0
40704178:	e12fff1e 	bx	lr
4070417c:	10010000 	.word	0x10010000
40704180:	ffff8000 	.word	0xffff8000

40704184 <sdhci_read_boot_data>:
40704184:	e3510a06 	cmp	r1, #24576	; 0x6000
40704188:	8a000009 	bhi	407041b4 <sdhci_read_boot_data+0x30>
4070418c:	e3c11003 	bic	r1, r1, #3
40704190:	e59f30ac 	ldr	r3, [pc, #172]	; 40704244 <sdhci_read_boot_data+0xc0>
40704194:	e0801001 	add	r1, r0, r1
40704198:	e1500001 	cmp	r0, r1
4070419c:	1a000001 	bne	407041a8 <sdhci_read_boot_data+0x24>
407041a0:	e3a00000 	mov	r0, #0
407041a4:	e12fff1e 	bx	lr
407041a8:	e4932004 	ldr	r2, [r3], #4
407041ac:	e4802004 	str	r2, [r0], #4
407041b0:	eafffff8 	b	40704198 <sdhci_read_boot_data+0x14>
407041b4:	e59f3088 	ldr	r3, [pc, #136]	; 40704244 <sdhci_read_boot_data+0xc0>
407041b8:	e2402004 	sub	r2, r0, #4
407041bc:	e59fc084 	ldr	ip, [pc, #132]	; 40704248 <sdhci_read_boot_data+0xc4>
407041c0:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
407041c4:	e493e004 	ldr	lr, [r3], #4
407041c8:	e153000c 	cmp	r3, ip
407041cc:	e5a2e004 	str	lr, [r2, #4]!
407041d0:	1afffffb 	bne	407041c4 <sdhci_read_boot_data+0x40>
407041d4:	e2414a06 	sub	r4, r1, #24576	; 0x6000
407041d8:	e59f706c 	ldr	r7, [pc, #108]	; 4070424c <sdhci_read_boot_data+0xc8>
407041dc:	e7e83054 	ubfx	r3, r4, #0, #9
407041e0:	e2805a06 	add	r5, r0, #24576	; 0x6000
407041e4:	e3530000 	cmp	r3, #0
407041e8:	e1a044a4 	lsr	r4, r4, #9
407041ec:	12844001 	addne	r4, r4, #1
407041f0:	e3a06000 	mov	r6, #0
407041f4:	e3a01e7d 	mov	r1, #2000	; 0x7d0
407041f8:	e3a00020 	mov	r0, #32
407041fc:	ebffffcc 	bl	40704134 <sdhci_check_int_status>
40704200:	e3500000 	cmp	r0, #0
40704204:	1a00000c 	bne	4070423c <sdhci_read_boot_data+0xb8>
40704208:	e3a03020 	mov	r3, #32
4070420c:	e5873030 	str	r3, [r7, #48]	; 0x30
40704210:	e1a03005 	mov	r3, r5
40704214:	e2855c02 	add	r5, r5, #512	; 0x200
40704218:	e5972020 	ldr	r2, [r7, #32]
4070421c:	e4832004 	str	r2, [r3], #4
40704220:	e1530005 	cmp	r3, r5
40704224:	1afffffb 	bne	40704218 <sdhci_read_boot_data+0x94>
40704228:	e2866001 	add	r6, r6, #1
4070422c:	e1560004 	cmp	r6, r4
40704230:	1affffef 	bne	407041f4 <sdhci_read_boot_data+0x70>
40704234:	e3a00000 	mov	r0, #0
40704238:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
4070423c:	e3e00000 	mvn	r0, #0
40704240:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40704244:	04010500 	.word	0x04010500
40704248:	04016500 	.word	0x04016500
4070424c:	10010000 	.word	0x10010000

40704250 <emmc_boot_read>:
40704250:	eaffffcb 	b	40704184 <sdhci_read_boot_data>

40704254 <hw_dec_sop_eop_first_set>:
40704254:	e59f2034 	ldr	r2, [pc, #52]	; 40704290 <hw_dec_sop_eop_first_set+0x3c>
40704258:	e3500001 	cmp	r0, #1
4070425c:	e59f3030 	ldr	r3, [pc, #48]	; 40704294 <hw_dec_sop_eop_first_set+0x40>
40704260:	13a01001 	movne	r1, #1
40704264:	15821000 	strne	r1, [r2]
40704268:	13a02000 	movne	r2, #0
4070426c:	05830000 	streq	r0, [r3]
40704270:	15832000 	strne	r2, [r3]
40704274:	e59f301c 	ldr	r3, [pc, #28]	; 40704298 <hw_dec_sop_eop_first_set+0x44>
40704278:	05820000 	streq	r0, [r2]
4070427c:	e3a02000 	mov	r2, #0
40704280:	e5832000 	str	r2, [r3]
40704284:	e59f3010 	ldr	r3, [pc, #16]	; 4070429c <hw_dec_sop_eop_first_set+0x48>
40704288:	e5830000 	str	r0, [r3]
4070428c:	e12fff1e 	bx	lr
40704290:	4073bde8 	.word	0x4073bde8
40704294:	4073bde4 	.word	0x4073bde4
40704298:	4073bde0 	.word	0x4073bde0
4070429c:	4073bddc 	.word	0x4073bddc

407042a0 <hw_dec_intr_proc>:
407042a0:	e59f30a0 	ldr	r3, [pc, #160]	; 40704348 <hw_dec_intr_proc+0xa8>
407042a4:	e5931124 	ldr	r1, [r3, #292]	; 0x124
407042a8:	f57ff05f 	dmb	sy
407042ac:	e3110002 	tst	r1, #2
407042b0:	0a00000c 	beq	407042e8 <hw_dec_intr_proc+0x48>
407042b4:	e59f2090 	ldr	r2, [pc, #144]	; 4070434c <hw_dec_intr_proc+0xac>
407042b8:	e5920080 	ldr	r0, [r2, #128]	; 0x80
407042bc:	f57ff05f 	dmb	sy
407042c0:	e3500000 	cmp	r0, #0
407042c4:	aa000002 	bge	407042d4 <hw_dec_intr_proc+0x34>
407042c8:	f57ff05f 	dmb	sy
407042cc:	e3a00001 	mov	r0, #1
407042d0:	e5820090 	str	r0, [r2, #144]	; 0x90
407042d4:	e5932130 	ldr	r2, [r3, #304]	; 0x130
407042d8:	f57ff05f 	dmb	sy
407042dc:	e3822002 	orr	r2, r2, #2
407042e0:	f57ff05f 	dmb	sy
407042e4:	e5832130 	str	r2, [r3, #304]	; 0x130
407042e8:	e3110001 	tst	r1, #1
407042ec:	0a000013 	beq	40704340 <hw_dec_intr_proc+0xa0>
407042f0:	e59f2054 	ldr	r2, [pc, #84]	; 4070434c <hw_dec_intr_proc+0xac>
407042f4:	e5923084 	ldr	r3, [r2, #132]	; 0x84
407042f8:	f57ff05f 	dmb	sy
407042fc:	e3530000 	cmp	r3, #0
40704300:	a3a00000 	movge	r0, #0
40704304:	aa000006 	bge	40704324 <hw_dec_intr_proc+0x84>
40704308:	e6ef3073 	uxtb	r3, r3
4070430c:	e3530000 	cmp	r3, #0
40704310:	03a00000 	moveq	r0, #0
40704314:	13e00001 	mvnne	r0, #1
40704318:	f57ff05f 	dmb	sy
4070431c:	e3a03001 	mov	r3, #1
40704320:	e5823094 	str	r3, [r2, #148]	; 0x94
40704324:	e59f201c 	ldr	r2, [pc, #28]	; 40704348 <hw_dec_intr_proc+0xa8>
40704328:	e5923130 	ldr	r3, [r2, #304]	; 0x130
4070432c:	f57ff05f 	dmb	sy
40704330:	e3833001 	orr	r3, r3, #1
40704334:	f57ff05f 	dmb	sy
40704338:	e5823130 	str	r3, [r2, #304]	; 0x130
4070433c:	e12fff1e 	bx	lr
40704340:	e3e00000 	mvn	r0, #0
40704344:	e12fff1e 	bx	lr
40704348:	11310000 	.word	0x11310000
4070434c:	11312000 	.word	0x11312000

40704350 <hw_dec_start>:
40704350:	e59fc0a0 	ldr	ip, [pc, #160]	; 407043f8 <hw_dec_start+0xa8>
40704354:	e92d4010 	push	{r4, lr}
40704358:	e59ce000 	ldr	lr, [ip]
4070435c:	e59d4010 	ldr	r4, [sp, #16]
40704360:	e35e0000 	cmp	lr, #0
40704364:	0a000006 	beq	40704384 <hw_dec_start+0x34>
40704368:	e3540000 	cmp	r4, #0
4070436c:	e59fe088 	ldr	lr, [pc, #136]	; 407043fc <hw_dec_start+0xac>
40704370:	1a000017 	bne	407043d4 <hw_dec_start+0x84>
40704374:	f57ff05f 	dmb	sy
40704378:	e58e1020 	str	r1, [lr, #32]
4070437c:	f57ff05f 	dmb	sy
40704380:	e58e3024 	str	r3, [lr, #36]	; 0x24
40704384:	f57ff05f 	dmb	sy
40704388:	e59f106c 	ldr	r1, [pc, #108]	; 407043fc <hw_dec_start+0xac>
4070438c:	e3540000 	cmp	r4, #0
40704390:	e59f3068 	ldr	r3, [pc, #104]	; 40704400 <hw_dec_start+0xb0>
40704394:	e5810040 	str	r0, [r1, #64]	; 0x40
40704398:	e5933000 	ldr	r3, [r3]
4070439c:	e59c0000 	ldr	r0, [ip]
407043a0:	e1a03e83 	lsl	r3, r3, #29
407043a4:	e1833e00 	orr	r3, r3, r0, lsl #28
407043a8:	e1832002 	orr	r2, r3, r2
407043ac:	03a03102 	moveq	r3, #-2147483648	; 0x80000000
407043b0:	13a03000 	movne	r3, #0
407043b4:	e1832002 	orr	r2, r3, r2
407043b8:	f57ff05f 	dmb	sy
407043bc:	e5812044 	str	r2, [r1, #68]	; 0x44
407043c0:	f57ff05f 	dmb	sy
407043c4:	e59f3038 	ldr	r3, [pc, #56]	; 40704404 <hw_dec_start+0xb4>
407043c8:	e59d2008 	ldr	r2, [sp, #8]
407043cc:	e5832000 	str	r2, [r3]
407043d0:	e8bd8010 	pop	{r4, pc}
407043d4:	f57ff05f 	dmb	sy
407043d8:	e2833eff 	add	r3, r3, #4080	; 0xff0
407043dc:	e58e1028 	str	r1, [lr, #40]	; 0x28
407043e0:	e283300f 	add	r3, r3, #15
407043e4:	e1a03623 	lsr	r3, r3, #12
407043e8:	e1a03103 	lsl	r3, r3, #2
407043ec:	f57ff05f 	dmb	sy
407043f0:	e58e302c 	str	r3, [lr, #44]	; 0x2c
407043f4:	eaffffe2 	b	40704384 <hw_dec_start+0x34>
407043f8:	4073bde8 	.word	0x4073bde8
407043fc:	11312000 	.word	0x11312000
40704400:	4073bde4 	.word	0x4073bde4
40704404:	11314000 	.word	0x11314000

40704408 <hw_dec_wait_finish>:
40704408:	e92d4070 	push	{r4, r5, r6, lr}
4070440c:	e3a04000 	mov	r4, #0
40704410:	e59f5028 	ldr	r5, [pc, #40]	; 40704440 <hw_dec_wait_finish+0x38>
40704414:	e3a01000 	mov	r1, #0
40704418:	e3a00056 	mov	r0, #86	; 0x56
4070441c:	ebffff9f 	bl	407042a0 <hw_dec_intr_proc>
40704420:	e2844001 	add	r4, r4, #1
40704424:	e0543005 	subs	r3, r4, r5
40704428:	13a03001 	movne	r3, #1
4070442c:	e3700001 	cmn	r0, #1
40704430:	13a03000 	movne	r3, #0
40704434:	e3530000 	cmp	r3, #0
40704438:	1afffff5 	bne	40704414 <hw_dec_wait_finish+0xc>
4070443c:	e8bd8070 	pop	{r4, r5, r6, pc}
40704440:	000186a1 	.word	0x000186a1

40704444 <hw_dec_decompress>:
40704444:	e92d40f0 	push	{r4, r5, r6, r7, lr}
40704448:	e1a06000 	mov	r6, r0
4070444c:	e24dd014 	sub	sp, sp, #20
40704450:	e3a00001 	mov	r0, #1
40704454:	e1a04001 	mov	r4, r1
40704458:	e1a05002 	mov	r5, r2
4070445c:	e1a07003 	mov	r7, r3
40704460:	ebffff7b 	bl	40704254 <hw_dec_sop_eop_first_set>
40704464:	e59f304c 	ldr	r3, [pc, #76]	; 407044b8 <hw_dec_decompress+0x74>
40704468:	e1a01006 	mov	r1, r6
4070446c:	e1a00005 	mov	r0, r5
40704470:	e3a02001 	mov	r2, #1
40704474:	e5933000 	ldr	r3, [r3]
40704478:	e58d3008 	str	r3, [sp, #8]
4070447c:	e3a03000 	mov	r3, #0
40704480:	e88d000c 	stm	sp, {r2, r3}
40704484:	e1a02007 	mov	r2, r7
40704488:	e5943000 	ldr	r3, [r4]
4070448c:	ebffffaf 	bl	40704350 <hw_dec_start>
40704490:	ebffffdc 	bl	40704408 <hw_dec_wait_finish>
40704494:	e59f3020 	ldr	r3, [pc, #32]	; 407044bc <hw_dec_decompress+0x78>
40704498:	e5933088 	ldr	r3, [r3, #136]	; 0x88
4070449c:	f57ff05f 	dmb	sy
407044a0:	e2900000 	adds	r0, r0, #0
407044a4:	e5843000 	str	r3, [r4]
407044a8:	13a00001 	movne	r0, #1
407044ac:	e2600000 	rsb	r0, r0, #0
407044b0:	e28dd014 	add	sp, sp, #20
407044b4:	e8bd80f0 	pop	{r4, r5, r6, r7, pc}
407044b8:	4073bdec 	.word	0x4073bdec
407044bc:	11312000 	.word	0x11312000

407044c0 <hw_dec_init>:
407044c0:	e59f2054 	ldr	r2, [pc, #84]	; 4070451c <hw_dec_init+0x5c>
407044c4:	e5923190 	ldr	r3, [r2, #400]	; 0x190
407044c8:	f57ff05f 	dmb	sy
407044cc:	e3833001 	orr	r3, r3, #1
407044d0:	f57ff05f 	dmb	sy
407044d4:	e5823190 	str	r3, [r2, #400]	; 0x190
407044d8:	f57ff05f 	dmb	sy
407044dc:	e59f303c 	ldr	r3, [pc, #60]	; 40704520 <hw_dec_init+0x60>
407044e0:	e3a01000 	mov	r1, #0
407044e4:	e5831108 	str	r1, [r3, #264]	; 0x108
407044e8:	f57ff05f 	dmb	sy
407044ec:	e3a02003 	mov	r2, #3
407044f0:	e583210c 	str	r2, [r3, #268]	; 0x10c
407044f4:	f57ff05f 	dmb	sy
407044f8:	e5831110 	str	r1, [r3, #272]	; 0x110
407044fc:	f57ff05f 	dmb	sy
40704500:	e5832114 	str	r2, [r3, #276]	; 0x114
40704504:	f57ff05f 	dmb	sy
40704508:	e5832128 	str	r2, [r3, #296]	; 0x128
4070450c:	f57ff05f 	dmb	sy
40704510:	e3a02001 	mov	r2, #1
40704514:	e5832100 	str	r2, [r3, #256]	; 0x100
40704518:	e12fff1e 	bx	lr
4070451c:	12010000 	.word	0x12010000
40704520:	11310000 	.word	0x11310000

40704524 <hw_dec_uinit>:
40704524:	f57ff05f 	dmb	sy
40704528:	e59f1034 	ldr	r1, [pc, #52]	; 40704564 <hw_dec_uinit+0x40>
4070452c:	e3a02000 	mov	r2, #0
40704530:	e1a03002 	mov	r3, r2
40704534:	e7c03012 	bfi	r3, r2, #0, #1
40704538:	e7c13092 	bfi	r3, r2, #1, #1
4070453c:	e5812100 	str	r2, [r1, #256]	; 0x100
40704540:	f57ff05f 	dmb	sy
40704544:	e59f201c 	ldr	r2, [pc, #28]	; 40704568 <hw_dec_uinit+0x44>
40704548:	e5813128 	str	r3, [r1, #296]	; 0x128
4070454c:	e5923190 	ldr	r3, [r2, #400]	; 0x190
40704550:	f57ff05f 	dmb	sy
40704554:	e3c33001 	bic	r3, r3, #1
40704558:	f57ff05f 	dmb	sy
4070455c:	e5823190 	str	r3, [r2, #400]	; 0x190
40704560:	e12fff1e 	bx	lr
40704564:	11310000 	.word	0x11310000
40704568:	12010000 	.word	0x12010000

4070456c <start_armboot>:
4070456c:	e92d4030 	push	{r4, r5, lr}
40704570:	e24dd014 	sub	sp, sp, #20
40704574:	ebfffebb 	bl	40704068 <uart_early_init>
40704578:	e59f008c 	ldr	r0, [pc, #140]	; 4070460c <start_armboot+0xa0>
4070457c:	ebfffec6 	bl	4070409c <uart_early_puts>
40704580:	e59f3088 	ldr	r3, [pc, #136]	; 40704610 <start_armboot+0xa4>
40704584:	e3a00000 	mov	r0, #0
40704588:	e59f4084 	ldr	r4, [pc, #132]	; 40704614 <start_armboot+0xa8>
4070458c:	e5830000 	str	r0, [r3]
40704590:	ebffffca 	bl	407044c0 <hw_dec_init>
40704594:	e59f307c 	ldr	r3, [pc, #124]	; 40704618 <start_armboot+0xac>
40704598:	e28d100c 	add	r1, sp, #12
4070459c:	e5532004 	ldrb	r2, [r3, #-4]
407045a0:	e5cd200c 	strb	r2, [sp, #12]
407045a4:	e5532003 	ldrb	r2, [r3, #-3]
407045a8:	e5cd200d 	strb	r2, [sp, #13]
407045ac:	e5532002 	ldrb	r2, [r3, #-2]
407045b0:	e5cd200e 	strb	r2, [sp, #14]
407045b4:	e5532001 	ldrb	r2, [r3, #-1]
407045b8:	e5cd200f 	strb	r2, [sp, #15]
407045bc:	e59f2058 	ldr	r2, [pc, #88]	; 4070461c <start_armboot+0xb0>
407045c0:	e0433002 	sub	r3, r3, r2
407045c4:	e58d0000 	str	r0, [sp]
407045c8:	e1a00004 	mov	r0, r4
407045cc:	ebffff9c 	bl	40704444 <hw_dec_decompress>
407045d0:	e2505000 	subs	r5, r0, #0
407045d4:	1a000009 	bne	40704600 <start_armboot+0x94>
407045d8:	e59f0040 	ldr	r0, [pc, #64]	; 40704620 <start_armboot+0xb4>
407045dc:	ebfffeae 	bl	4070409c <uart_early_puts>
407045e0:	ebffffcf 	bl	40704524 <hw_dec_uinit>
407045e4:	ee075f15 	mcr	15, 0, r5, cr7, cr5, {0}
407045e8:	ee075fd5 	mcr	15, 0, r5, cr7, cr5, {6}
407045ec:	f57ff04f 	dsb	sy
407045f0:	f57ff06f 	isb	sy
407045f4:	e12fff34 	blx	r4
407045f8:	e28dd014 	add	sp, sp, #20
407045fc:	e8bd8030 	pop	{r4, r5, pc}
40704600:	e59f001c 	ldr	r0, [pc, #28]	; 40704624 <start_armboot+0xb8>
40704604:	ebfffea4 	bl	4070409c <uart_early_puts>
40704608:	eafffffe 	b	40704608 <start_armboot+0x9c>
4070460c:	4073bd8c 	.word	0x4073bd8c
40704610:	4073bdec 	.word	0x4073bdec
40704614:	40800000 	.word	0x40800000
40704618:	4073bcf6 	.word	0x4073bcf6
4070461c:	407047a0 	.word	0x407047a0
40704620:	4073bd9a 	.word	0x4073bd9a
40704624:	4073bd9e 	.word	0x4073bd9e

40704628 <hang>:
40704628:	e92d4010 	push	{r4, lr}
4070462c:	e59f0004 	ldr	r0, [pc, #4]	; 40704638 <hang+0x10>
40704630:	ebfffe99 	bl	4070409c <uart_early_puts>
40704634:	eafffffe 	b	40704634 <hang+0xc>
40704638:	4073bd62 	.word	0x4073bd62

4070463c <do_bad_sync>:
4070463c:	e92d4010 	push	{r4, lr}
40704640:	e59f0014 	ldr	r0, [pc, #20]	; 4070465c <do_bad_sync+0x20>
40704644:	ebfffe94 	bl	4070409c <uart_early_puts>
40704648:	e59f0010 	ldr	r0, [pc, #16]	; 40704660 <do_bad_sync+0x24>
4070464c:	ebfffe92 	bl	4070409c <uart_early_puts>
40704650:	e3a00000 	mov	r0, #0
40704654:	e8bd4010 	pop	{r4, lr}
40704658:	ea000047 	b	4070477c <reset_cpu>
4070465c:	4073bd3d 	.word	0x4073bd3d
40704660:	4073bd4e 	.word	0x4073bd4e

40704664 <do_sync>:
40704664:	e92d4010 	push	{r4, lr}
40704668:	e59f0014 	ldr	r0, [pc, #20]	; 40704684 <do_sync+0x20>
4070466c:	ebfffe8a 	bl	4070409c <uart_early_puts>
40704670:	e59f0010 	ldr	r0, [pc, #16]	; 40704688 <do_sync+0x24>
40704674:	ebfffe88 	bl	4070409c <uart_early_puts>
40704678:	e3a00000 	mov	r0, #0
4070467c:	e8bd4010 	pop	{r4, lr}
40704680:	ea00003d 	b	4070477c <reset_cpu>
40704684:	4073bd41 	.word	0x4073bd41
40704688:	4073bd4e 	.word	0x4073bd4e

4070468c <do_bad_error>:
4070468c:	e92d4010 	push	{r4, lr}
40704690:	e59f0014 	ldr	r0, [pc, #20]	; 407046ac <do_bad_error+0x20>
40704694:	ebfffe80 	bl	4070409c <uart_early_puts>
40704698:	e59f0010 	ldr	r0, [pc, #16]	; 407046b0 <do_bad_error+0x24>
4070469c:	ebfffe7e 	bl	4070409c <uart_early_puts>
407046a0:	e3a00000 	mov	r0, #0
407046a4:	e8bd4010 	pop	{r4, lr}
407046a8:	ea000033 	b	4070477c <reset_cpu>
407046ac:	4073bcfc 	.word	0x4073bcfc
407046b0:	4073bd4e 	.word	0x4073bd4e

407046b4 <do_error>:
407046b4:	e92d4010 	push	{r4, lr}
407046b8:	e59f0014 	ldr	r0, [pc, #20]	; 407046d4 <do_error+0x20>
407046bc:	ebfffe76 	bl	4070409c <uart_early_puts>
407046c0:	e59f0010 	ldr	r0, [pc, #16]	; 407046d8 <do_error+0x24>
407046c4:	ebfffe74 	bl	4070409c <uart_early_puts>
407046c8:	e3a00000 	mov	r0, #0
407046cc:	e8bd4010 	pop	{r4, lr}
407046d0:	ea000029 	b	4070477c <reset_cpu>
407046d4:	4073bd00 	.word	0x4073bd00
407046d8:	4073bd4e 	.word	0x4073bd4e

407046dc <do_bad_fiq>:
407046dc:	e92d4010 	push	{r4, lr}
407046e0:	e59f0014 	ldr	r0, [pc, #20]	; 407046fc <do_bad_fiq+0x20>
407046e4:	ebfffe6c 	bl	4070409c <uart_early_puts>
407046e8:	e59f0010 	ldr	r0, [pc, #16]	; 40704700 <do_bad_fiq+0x24>
407046ec:	ebfffe6a 	bl	4070409c <uart_early_puts>
407046f0:	e3a00000 	mov	r0, #0
407046f4:	e8bd4010 	pop	{r4, lr}
407046f8:	ea00001f 	b	4070477c <reset_cpu>
407046fc:	4073bd08 	.word	0x4073bd08
40704700:	4073bd4e 	.word	0x4073bd4e

40704704 <do_bad_irq>:
40704704:	e92d4010 	push	{r4, lr}
40704708:	e59f0014 	ldr	r0, [pc, #20]	; 40704724 <do_bad_irq+0x20>
4070470c:	ebfffe62 	bl	4070409c <uart_early_puts>
40704710:	e59f0010 	ldr	r0, [pc, #16]	; 40704728 <do_bad_irq+0x24>
40704714:	ebfffe60 	bl	4070409c <uart_early_puts>
40704718:	e3a00000 	mov	r0, #0
4070471c:	e8bd4010 	pop	{r4, lr}
40704720:	ea000015 	b	4070477c <reset_cpu>
40704724:	4073bd25 	.word	0x4073bd25
40704728:	4073bd4e 	.word	0x4073bd4e

4070472c <do_fiq>:
4070472c:	e92d4010 	push	{r4, lr}
40704730:	e59f0014 	ldr	r0, [pc, #20]	; 4070474c <do_fiq+0x20>
40704734:	ebfffe58 	bl	4070409c <uart_early_puts>
40704738:	e59f0010 	ldr	r0, [pc, #16]	; 40704750 <do_fiq+0x24>
4070473c:	ebfffe56 	bl	4070409c <uart_early_puts>
40704740:	e3a00000 	mov	r0, #0
40704744:	e8bd4010 	pop	{r4, lr}
40704748:	ea00000b 	b	4070477c <reset_cpu>
4070474c:	4073bd0c 	.word	0x4073bd0c
40704750:	4073bd4e 	.word	0x4073bd4e

40704754 <do_irq>:
40704754:	e92d4010 	push	{r4, lr}
40704758:	e59f0014 	ldr	r0, [pc, #20]	; 40704774 <do_irq+0x20>
4070475c:	ebfffe4e 	bl	4070409c <uart_early_puts>
40704760:	e59f0010 	ldr	r0, [pc, #16]	; 40704778 <do_irq+0x24>
40704764:	ebfffe4c 	bl	4070409c <uart_early_puts>
40704768:	e3a00000 	mov	r0, #0
4070476c:	e8bd4010 	pop	{r4, lr}
40704770:	ea000001 	b	4070477c <reset_cpu>
40704774:	4073bd29 	.word	0x4073bd29
40704778:	4073bd4e 	.word	0x4073bd4e

4070477c <reset_cpu>:
4070477c:	e59f100c 	ldr	r1, [pc, #12]	; 40704790 <rstctl>
40704780:	e3a03002 	mov	r3, #2
40704784:	e5813000 	str	r3, [r1]
40704788:	e1a00000 	nop			; (mov r0, r0)

4070478c <_loop_forever>:
4070478c:	eafffffe 	b	4070478c <_loop_forever>

40704790 <rstctl>:
40704790:	12020004 	.word	0x12020004
