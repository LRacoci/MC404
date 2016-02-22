	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"main.c"
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.text
.Ltext0:
	.align	2
	.global	_start
	.type	_start, %function
_start:
.LFB0:
	.file 1 "main.c"
	.loc 1 13 0
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI0:
	add	fp, sp, #4
.LCFI1:
	sub	sp, sp, #72
.LCFI2:
	.loc 1 16 0
	mov	r0, #0
	mov	r1, #0
	bl	set_speed_motors
.L5:
	.loc 1 18 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-12]
	.loc 1 19 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-8]
	.loc 1 20 0
	ldr	r2, [fp, #-12]
	ldr	r3, .L7
	cmp	r2, r3
	bls	.L2
	ldr	r2, [fp, #-8]
	ldr	r3, .L7
	cmp	r2, r3
	bhi	.L3
.L2:
	.loc 1 21 0
	mov	r0, #0
	mov	r1, #0
	bl	set_speed_motors
	.loc 1 22 0
	ldr	r0, [fp, #-12]
	ldr	r1, [fp, #-8]
	bl	swerve
	.loc 1 20 0
	mov	r0, r0	@ nop
	.loc 1 26 0
	b	.L5
.L3:
	.loc 1 24 0
	mov	r0, #20
	mov	r1, #20
	bl	set_speed_motors
	.loc 1 26 0
	b	.L5
.L8:
	.align	2
.L7:
	.word	1199
.LFE0:
	.size	_start, .-_start
	.align	2
	.global	delay
	.type	delay, %function
delay:
.LFB1:
	.loc 1 31 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
.LCFI3:
	add	fp, sp, #0
.LCFI4:
	sub	sp, sp, #12
.LCFI5:
	.loc 1 34 0
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L10
.L11:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L10:
	ldr	r2, [fp, #-8]
	ldr	r3, .L13
	cmp	r2, r3
	ble	.L11
	.loc 1 35 0
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L14:
	.align	2
.L13:
	.word	9999
.LFE1:
	.size	delay, .-delay
	.align	2
	.global	turn_left
	.type	turn_left, %function
turn_left:
.LFB2:
	.loc 1 37 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI6:
	add	fp, sp, #4
.LCFI7:
	sub	sp, sp, #8
.LCFI8:
	mov	r3, r0
	strb	r3, [fp, #-5]
	.loc 1 38 0
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	mov	r0, r3
	mov	r1, #0
	bl	set_speed_motors
	.loc 1 39 0
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.LFE2:
	.size	turn_left, .-turn_left
	.align	2
	.global	turn_right
	.type	turn_right, %function
turn_right:
.LFB3:
	.loc 1 41 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI9:
	add	fp, sp, #4
.LCFI10:
	sub	sp, sp, #8
.LCFI11:
	mov	r3, r0
	strb	r3, [fp, #-5]
	.loc 1 42 0
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	mov	r0, #0
	mov	r1, r3
	bl	set_speed_motors
	.loc 1 43 0
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.LFE3:
	.size	turn_right, .-turn_right
	.align	2
	.global	swerve
	.type	swerve, %function
swerve:
.LFB4:
	.loc 1 45 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI12:
	add	fp, sp, #4
.LCFI13:
	sub	sp, sp, #8
.LCFI14:
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	.loc 1 46 0
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	bcs	.L20
.L21:
	.loc 1 48 0
	mov	r0, #15
	bl	turn_right
	.loc 1 49 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-8]
	.loc 1 50 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-12]
	.loc 1 51 0
	ldr	r2, [fp, #-8]
	ldr	r3, .L24
	cmp	r2, r3
	bls	.L21
	ldr	r2, [fp, #-12]
	ldr	r3, .L24
	cmp	r2, r3
	bls	.L21
	b	.L23
.L20:
	.loc 1 55 0
	mov	r0, #15
	bl	turn_left
	.loc 1 56 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-8]
	.loc 1 57 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-12]
	.loc 1 58 0
	ldr	r2, [fp, #-8]
	ldr	r3, .L24
	cmp	r2, r3
	bls	.L20
	ldr	r2, [fp, #-12]
	ldr	r3, .L24
	cmp	r2, r3
	bls	.L20
.L23:
	.loc 1 61 0
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L25:
	.align	2
.L24:
	.word	1199
.LFE4:
	.size	swerve, .-swerve
	.section	.debug_frame,"",%progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 -4
	.byte	0xe
	.byte	0xc
	.uleb128 0xd
	.uleb128 0x0
	.align	2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.byte	0x4
	.4byte	.LCFI0-.LFB0
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x4
	.4byte	.LCFI3-.LFB1
	.byte	0xe
	.uleb128 0x4
	.byte	0x11
	.uleb128 0xb
	.sleb128 1
	.byte	0x4
	.4byte	.LCFI4-.LCFI3
	.byte	0xd
	.uleb128 0xb
	.align	2
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x4
	.4byte	.LCFI6-.LFB2
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI7-.LCFI6
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.byte	0x4
	.4byte	.LCFI9-.LFB3
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI10-.LCFI9
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.byte	0x4
	.4byte	.LCFI12-.LFB4
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI13-.LCFI12
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE8:
	.text
.Letext0:
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LFB0-.Ltext0
	.4byte	.LCFI0-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0-.Ltext0
	.4byte	.LCFI1-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI1-.Ltext0
	.4byte	.LFE0-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST1:
	.4byte	.LFB1-.Ltext0
	.4byte	.LCFI3-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI3-.Ltext0
	.4byte	.LCFI4-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI4-.Ltext0
	.4byte	.LFE1-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST2:
	.4byte	.LFB2-.Ltext0
	.4byte	.LCFI6-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI6-.Ltext0
	.4byte	.LCFI7-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI7-.Ltext0
	.4byte	.LFE2-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST3:
	.4byte	.LFB3-.Ltext0
	.4byte	.LCFI9-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI9-.Ltext0
	.4byte	.LCFI10-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI10-.Ltext0
	.4byte	.LFE3-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST4:
	.4byte	.LFB4-.Ltext0
	.4byte	.LCFI12-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI12-.Ltext0
	.4byte	.LCFI13-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI13-.Ltext0
	.4byte	.LFE4-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
	.section	.debug_info
	.4byte	0x132
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF8
	.byte	0x1
	.4byte	.LASF9
	.4byte	.LASF10
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.4byte	.LASF2
	.byte	0x1
	.byte	0xd
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.4byte	.LLST0
	.4byte	0x68
	.uleb128 0x3
	.ascii	"s3\000"
	.byte	0x1
	.byte	0xf
	.4byte	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x3
	.ascii	"s4\000"
	.byte	0x1
	.byte	0xf
	.4byte	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x4
	.4byte	.LASF0
	.byte	0x1
	.byte	0xf
	.4byte	0x6f
	.byte	0x3
	.byte	0x91
	.sleb128 -80
	.byte	0x0
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x6
	.4byte	0x68
	.4byte	0x7f
	.uleb128 0x7
	.4byte	0x7f
	.byte	0xf
	.byte	0x0
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
	.uleb128 0x9
	.byte	0x1
	.4byte	.LASF6
	.byte	0x1
	.byte	0x1e
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LLST1
	.4byte	0xa7
	.uleb128 0x3
	.ascii	"i\000"
	.byte	0x1
	.byte	0x20
	.4byte	0xa7
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0x0
	.uleb128 0xa
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x1
	.4byte	.LASF3
	.byte	0x1
	.byte	0x25
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	.LLST2
	.4byte	0xd6
	.uleb128 0xb
	.ascii	"vel\000"
	.byte	0x1
	.byte	0x25
	.4byte	0xd6
	.byte	0x2
	.byte	0x91
	.sleb128 -9
	.byte	0x0
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x2
	.byte	0x1
	.4byte	.LASF5
	.byte	0x1
	.byte	0x29
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	.LLST3
	.4byte	0x105
	.uleb128 0xb
	.ascii	"vel\000"
	.byte	0x1
	.byte	0x29
	.4byte	0xd6
	.byte	0x2
	.byte	0x91
	.sleb128 -9
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.4byte	.LASF7
	.byte	0x1
	.byte	0x2d
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.4byte	.LLST4
	.uleb128 0xb
	.ascii	"s3\000"
	.byte	0x1
	.byte	0x2d
	.4byte	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xb
	.ascii	"s4\000"
	.byte	0x1
	.byte	0x2d
	.4byte	0x68
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.byte	0x0
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",%progbits
	.4byte	0x4b
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x136
	.4byte	0x25
	.ascii	"_start\000"
	.4byte	0x82
	.ascii	"delay\000"
	.4byte	0xae
	.ascii	"turn_left\000"
	.4byte	0xdd
	.ascii	"turn_right\000"
	.4byte	0x105
	.ascii	"swerve\000"
	.4byte	0x0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_str,"MS",%progbits,1
.LASF2:
	.ascii	"_start\000"
.LASF1:
	.ascii	"unsigned int\000"
.LASF3:
	.ascii	"turn_left\000"
.LASF10:
	.ascii	"/home/mc404/Documentos/lab7\000"
.LASF6:
	.ascii	"delay\000"
.LASF7:
	.ascii	"swerve\000"
.LASF5:
	.ascii	"turn_right\000"
.LASF9:
	.ascii	"main.c\000"
.LASF0:
	.ascii	"distances\000"
.LASF4:
	.ascii	"unsigned char\000"
.LASF8:
	.ascii	"GNU C 4.4.3\000"
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
