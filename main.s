	.file	"main.c"
	.text
	.globl	mutexQueue
	.bss
	.align 32
	.type	mutexQueue, @object
	.size	mutexQueue, 40
mutexQueue:
	.zero	40
	.globl	condQueue
	.align 32
	.type	condQueue, @object
	.size	condQueue, 48
condQueue:
	.zero	48
	.globl	threads
	.align 32
	.type	threads, @object
	.size	threads, 32
threads:
	.zero	32
	.globl	TaskQueue
	.align 32
	.type	TaskQueue, @object
	.size	TaskQueue, 400000
TaskQueue:
	.zero	400000
	.globl	TASKCOUNT
	.align 4
	.type	TASKCOUNT, @object
	.size	TASKCOUNT, 4
TASKCOUNT:
	.zero	4
	.globl	displ
	.align 8
	.type	displ, @object
	.size	displ, 8
displ:
	.zero	8
	.globl	win
	.align 8
	.type	win, @object
	.size	win, 8
win:
	.zero	8
	.globl	pixmap
	.align 8
	.type	pixmap, @object
	.size	pixmap, 8
pixmap:
	.zero	8
	.globl	gc
	.align 8
	.type	gc, @object
	.size	gc, 8
gc:
	.zero	8
	.globl	gcvalues
	.align 32
	.type	gcvalues, @object
	.size	gcvalues, 128
gcvalues:
	.zero	128
	.globl	wa
	.align 32
	.type	wa, @object
	.size	wa, 136
wa:
	.zero	136
	.globl	sa
	.align 32
	.type	sa, @object
	.size	sa, 112
sa:
	.zero	112
	.globl	wmatom
	.align 16
	.type	wmatom, @object
	.size	wmatom, 24
wmatom:
	.zero	24
	.globl	pixels
	.align 8
	.type	pixels, @object
	.size	pixels, 8
pixels:
	.zero	8
	.globl	frame_buffer
	.align 8
	.type	frame_buffer, @object
	.size	frame_buffer, 8
frame_buffer:
	.zero	8
	.globl	depth_buffer
	.align 8
	.type	depth_buffer, @object
	.size	depth_buffer, 8
depth_buffer:
	.zero	8
	.globl	shadow_buffer
	.align 8
	.type	shadow_buffer, @object
	.size	shadow_buffer, 8
shadow_buffer:
	.zero	8
	.globl	camera
	.data
	.align 32
	.type	camera, @object
	.size	camera, 80
camera:
	.long	0
	.long	0
	.long	1140391936
	.long	1065353216
	.long	1065353216
	.long	0
	.long	0
	.long	0
	.long	0
	.long	1065353216
	.long	0
	.long	0
	.long	0
	.long	0
	.long	1065353216
	.long	0
	.zero	16
	.globl	light
	.align 32
	.type	light, @object
	.size	light, 80
light:
	.long	-1033839555
	.long	-1036027938
	.long	1143439957
	.long	1065353216
	.long	-1083677627
	.long	-1114803859
	.long	-1093413915
	.long	0
	.long	-1103732238
	.long	1064623088
	.long	1047309723
	.long	0
	.long	1052929990
	.long	1049700208
	.long	-1084134034
	.long	0
	.long	1065353216
	.long	1065353216
	.long	1065353216
	.zero	4
	.globl	scene
	.bss
	.align 16
	.type	scene, @object
	.size	scene, 16
scene:
	.zero	16
	.globl	WorldMat
	.align 32
	.type	WorldMat, @object
	.size	WorldMat, 64
WorldMat:
	.zero	64
	.globl	LookAt
	.align 32
	.type	LookAt, @object
	.size	LookAt, 64
LookAt:
	.zero	64
	.globl	ViewMat
	.align 32
	.type	ViewMat, @object
	.size	ViewMat, 64
ViewMat:
	.zero	64
	.globl	PerspMat
	.align 32
	.type	PerspMat, @object
	.size	PerspMat, 64
PerspMat:
	.zero	64
	.globl	rePerspMat
	.align 32
	.type	rePerspMat, @object
	.size	rePerspMat, 64
rePerspMat:
	.zero	64
	.globl	OrthoMat
	.align 32
	.type	OrthoMat, @object
	.size	OrthoMat, 64
OrthoMat:
	.zero	64
	.globl	LightMat
	.align 32
	.type	LightMat, @object
	.size	LightMat, 64
LightMat:
	.zero	64
	.globl	model
	.align 32
	.type	model, @object
	.size	model, 96
model:
	.zero	96
	.local	INIT
	.comm	INIT,4,4
	.data
	.align 4
	.type	RUNNING, @object
	.size	RUNNING, 4
RUNNING:
	.long	1
	.globl	HALFW
	.bss
	.align 4
	.type	HALFW, @object
	.size	HALFW, 4
HALFW:
	.zero	4
	.globl	HALFH
	.align 4
	.type	HALFH, @object
	.size	HALFH, 4
HALFH:
	.zero	4
	.local	EYEPOINT
	.comm	EYEPOINT,4,4
	.local	PROJECTIONVIEW
	.comm	PROJECTIONVIEW,4,4
	.data
	.align 4
	.type	PROJECTBUFFER, @object
	.size	PROJECTBUFFER, 4
PROJECTBUFFER:
	.long	1
	.local	AspectRatio
	.comm	AspectRatio,4,4
	.align 4
	.type	FOV, @object
	.size	FOV, 4
FOV:
	.long	1110704128
	.align 4
	.type	Angle, @object
	.size	Angle, 4
Angle:
	.long	1073741824
	.align 4
	.type	bias, @object
	.size	bias, 4
bias:
	.long	956016770
	.local	AdjustShadow
	.comm	AdjustShadow,4,4
	.local	AdjustScene
	.comm	AdjustScene,4,4
	.align 4
	.type	NPlane, @object
	.size	NPlane, 4
NPlane:
	.long	1065353216
	.align 4
	.type	FPlane, @object
	.size	FPlane, 4
FPlane:
	.long	925353388
	.align 4
	.type	Scale, @object
	.size	Scale, 4
Scale:
	.long	1022739087
	.local	DEBUG
	.comm	DEBUG,4,4
	.section	.data.rel.local,"aw"
	.align 32
	.type	handler, @object
	.size	handler, 288
handler:
	.zero	16
	.quad	keypress
	.zero	8
	.quad	buttonpress
	.zero	112
	.quad	mapnotify
	.zero	8
	.quad	reparentnotify
	.quad	configurenotify
	.zero	16
	.quad	resizerequest
	.zero	56
	.quad	clientmessage
	.zero	16
	.section	.rodata
.LC0:
	.string	"Received client message event"
.LC1:
	.string	"WM_DELETE_WINDOW"
.LC2:
	.string	"Reached step 1"
.LC3:
	.string	"Reached step 2"
.LC4:
	.string	"Reached step 3"
.LC5:
	.string	"Reached step 4"
.LC6:
	.string	"Reached step 5"
.LC7:
	.string	"Reached step 6"
.LC8:
	.string	"Reached step 7"
.LC9:
	.string	"Reached step 8"
	.align 8
.LC10:
	.string	"Thread Cancelation of thead[%d] returned an error.\n"
	.text
	.type	clientmessage, @function
clientmessage:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-24(%rbp), %rax
	movq	56(%rax), %rax
	movq	wmatom(%rip), %rdx
	cmpq	%rdx, %rax
	jne	.L6
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	scene(%rip), %rax
	movq	%rax, %rdi
	call	releaseScene
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	12+wa(%rip), %edx
	movq	pixels(%rip), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	free2darray@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	12+wa(%rip), %edx
	movq	depth_buffer(%rip), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	free2darray@PLT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	12+wa(%rip), %edx
	movq	shadow_buffer(%rip), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	free2darray@PLT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	frame_buffer(%rip), %rax
	movq	%rax, %rdi
	call	free@PLT
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	gc(%rip), %rdx
	movq	displ(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	XFreeGC@PLT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	pixmap(%rip), %rdx
	movq	displ(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	XFreePixmap@PLT
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	win(%rip), %rdx
	movq	displ(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	XDestroyWindow@PLT
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L3
.L5:
	cmpl	$0, -4(%rbp)
	je	.L4
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	threads(%rip), %rax
	movq	(%rdx,%rax), %rax
	movq	%rax, %rdi
	call	pthread_cancel@PLT
.L4:
	addl	$1, -4(%rbp)
.L3:
	cmpl	$3, -4(%rbp)
	jle	.L5
	movq	stderr(%rip), %rax
	movl	-4(%rbp), %edx
	leaq	.LC10(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	$0, RUNNING(%rip)
.L6:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	clientmessage, .-clientmessage
	.section	.rodata
.LC11:
	.string	"reparentnotify event received"
	.text
	.type	reparentnotify, @function
reparentnotify:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	reparentnotify, .-reparentnotify
	.section	.rodata
.LC12:
	.string	"mapnotify event received"
	.text
	.type	mapnotify, @function
mapnotify:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	mapnotify, .-mapnotify
	.section	.rodata
.LC13:
	.string	"resizerequest event received"
	.text
	.type	resizerequest, @function
resizerequest:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	resizerequest, .-resizerequest
	.section	.rodata
	.align 8
.LC14:
	.string	"configurenotify event received"
	.text
	.type	configurenotify, @function
configurenotify:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	16(%rax), %eax
	testl	%eax, %eax
	jne	.L13
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	12+wa(%rip), %eax
	movl	%eax, -4(%rbp)
	movq	win(%rip), %rcx
	movq	displ(%rip), %rax
	leaq	wa(%rip), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	XGetWindowAttributes@PLT
	movl	INIT(%rip), %eax
	testl	%eax, %eax
	je	.L12
	movq	pixels(%rip), %rax
	movl	-4(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	free2darray@PLT
	movq	depth_buffer(%rip), %rax
	movl	-4(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	free2darray@PLT
	movq	shadow_buffer(%rip), %rax
	movl	-4(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	free2darray@PLT
	movq	frame_buffer(%rip), %rax
	movq	%rax, %rdi
	call	free@PLT
	call	pixmapcreate
	call	initBuffers
.L12:
	call	initDependedVariables
	movl	INIT(%rip), %eax
	testl	%eax, %eax
	jne	.L13
	movl	$1, INIT(%rip)
.L13:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	configurenotify, .-configurenotify
	.section	.rodata
.LC15:
	.string	"buttonpress event received"
.LC17:
	.string	"X: %f\n"
.LC18:
	.string	"Y: %f\n"
	.text
	.type	buttonpress, @function
buttonpress:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-72(%rbp), %rax
	movl	64(%rax), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC16(%rip), %xmm1
	subsd	%xmm1, %xmm0
	movsd	.LC16(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leaq	.LC17(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movq	-72(%rbp), %rax
	movl	68(%rax), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC16(%rip), %xmm1
	subsd	%xmm1, %xmm0
	movsd	.LC16(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leaq	.LC18(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, -20(%rbp)
	jmp	.L15
.L16:
	leaq	printTask(%rip), %rax
	movq	%rax, -64(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -56(%rbp)
	movss	.LC20(%rip), %xmm0
	movss	%xmm0, -52(%rbp)
	movss	.LC21(%rip), %xmm0
	movss	%xmm0, -48(%rbp)
	movss	.LC22(%rip), %xmm0
	movss	%xmm0, -44(%rbp)
	movq	camera(%rip), %rax
	movq	8+camera(%rip), %rdx
	movq	%rax, -40(%rbp)
	movq	%rdx, -32(%rbp)
	subq	$8, %rsp
	subq	$40, %rsp
	movq	%rsp, %rax
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-32(%rbp), %rdx
	movq	%rdx, 32(%rax)
	call	submitTask
	addq	$48, %rsp
	addl	$1, -20(%rbp)
.L15:
	cmpl	$9999, -20(%rbp)
	jle	.L16
	nop
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	buttonpress, .-buttonpress
	.section	.rodata
.LC23:
	.string	"Key Pressed: %ld\n"
.LC24:
	.string	"\033[H\033[J"
	.align 8
.LC26:
	.string	"Projecting Pixels -- PROJECTBUFFER: %d\n"
	.align 8
.LC27:
	.string	"Projecting Depth buffer -- PROJECTBUFFER: %d\n"
	.align 8
.LC28:
	.string	"Projecting Shadow buffer -- PROJECTBUFFER: %d\n"
.LC30:
	.string	"Bias: %f\n"
.LC32:
	.string	"FPlane: %f\n"
.LC34:
	.string	"NPlane: %f\n"
.LC36:
	.string	"Scale: %f\n"
	.text
	.type	keypress, @function
keypress:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$184, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	getKeysym
	movq	%rax, -32(%rbp)
	movl	EYEPOINT(%rip), %eax
	testl	%eax, %eax
	je	.L18
	leaq	light(%rip), %rax
	movq	%rax, -24(%rbp)
	jmp	.L19
.L18:
	leaq	camera(%rip), %rax
	movq	%rax, -24(%rbp)
.L19:
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC23(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC24(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	cmpq	$65465, -32(%rbp)
	ja	.L71
	cmpq	$65361, -32(%rbp)
	jnb	.L21
	cmpq	$122, -32(%rbp)
	ja	.L22
	cmpq	$43, -32(%rbp)
	jnb	.L23
	jmp	.L71
.L21:
	movq	-32(%rbp), %rax
	subq	$65361, %rax
	cmpq	$104, %rax
	ja	.L71
	leaq	0(,%rax,4), %rdx
	leaq	.L25(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L25(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L25:
	.long	.L38-.L25
	.long	.L37-.L25
	.long	.L36-.L25
	.long	.L35-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L34-.L25
	.long	.L33-.L25
	.long	.L71-.L25
	.long	.L32-.L25
	.long	.L71-.L25
	.long	.L31-.L25
	.long	.L71-.L25
	.long	.L71-.L25
	.long	.L30-.L25
	.long	.L29-.L25
	.long	.L28-.L25
	.long	.L71-.L25
	.long	.L27-.L25
	.long	.L71-.L25
	.long	.L26-.L25
	.long	.L24-.L25
	.text
.L23:
	movq	-32(%rbp), %rax
	subq	$43, %rax
	cmpq	$79, %rax
	ja	.L71
	leaq	0(,%rax,4), %rdx
	leaq	.L40(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L40(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L40:
	.long	.L58-.L40
	.long	.L71-.L40
	.long	.L57-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L56-.L40
	.long	.L55-.L40
	.long	.L54-.L40
	.long	.L53-.L40
	.long	.L52-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L71-.L40
	.long	.L51-.L40
	.long	.L71-.L40
	.long	.L50-.L40
	.long	.L71-.L40
	.long	.L49-.L40
	.long	.L48-.L40
	.long	.L47-.L40
	.long	.L46-.L40
	.long	.L71-.L40
	.long	.L45-.L40
	.long	.L44-.L40
	.long	.L43-.L40
	.long	.L42-.L40
	.long	.L41-.L40
	.long	.L39-.L40
	.text
.L22:
	cmpq	$65289, -32(%rbp)
	je	.L59
	jmp	.L71
.L56:
	movl	Angle(%rip), %edx
	movq	-24(%rbp), %rax
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	look_left@PLT
	jmp	.L60
.L53:
	movl	Angle(%rip), %edx
	movq	-24(%rbp), %rax
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	look_right@PLT
	jmp	.L60
.L43:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	move_forward@PLT
	jmp	.L60
.L46:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	move_backward@PLT
	jmp	.L60
.L48:
	movl	Angle(%rip), %edx
	movq	-24(%rbp), %rax
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	look_up@PLT
	jmp	.L60
.L52:
	movl	Angle(%rip), %edx
	movq	-24(%rbp), %rax
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	look_down@PLT
	jmp	.L60
.L38:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	move_left@PLT
	jmp	.L60
.L36:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	move_right@PLT
	jmp	.L60
.L37:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	move_up@PLT
	jmp	.L60
.L35:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	move_down@PLT
	jmp	.L60
.L42:
	movl	Angle(%rip), %eax
	movq	scene(%rip), %rdx
	addq	$96, %rdx
	movd	%eax, %xmm0
	movq	%rdx, %rdi
	call	rotate_x
	jmp	.L60
.L41:
	movl	Angle(%rip), %eax
	movq	scene(%rip), %rdx
	addq	$96, %rdx
	movd	%eax, %xmm0
	movq	%rdx, %rdi
	call	rotate_y
	jmp	.L60
.L39:
	movl	Angle(%rip), %edx
	movq	scene(%rip), %rax
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	rotate_z
	jmp	.L60
.L47:
	movl	Angle(%rip), %edx
	subq	$80, %rsp
	movq	%rsp, %rax
	movq	light(%rip), %rcx
	movq	8+light(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+light(%rip), %rcx
	movq	24+light(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+light(%rip), %rcx
	movq	40+light(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+light(%rip), %rcx
	movq	56+light(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	64+light(%rip), %rcx
	movq	72+light(%rip), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	pxor	%xmm3, %xmm3
	movss	.LC19(%rip), %xmm2
	pxor	%xmm1, %xmm1
	movd	%edx, %xmm0
	call	rotate_light
	addq	$80, %rsp
	jmp	.L60
.L54:
	movl	Angle(%rip), %eax
	movq	scene(%rip), %rdx
	addq	$192, %rdx
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	movss	.LC19(%rip), %xmm1
	movd	%eax, %xmm0
	movq	%rdx, %rdi
	call	rotate_origin
	jmp	.L60
.L55:
	call	exportScene
	jmp	.L60
.L49:
	movl	PROJECTBUFFER(%rip), %eax
	cmpl	$3, %eax
	jne	.L61
	movl	$0, PROJECTBUFFER(%rip)
.L61:
	movl	PROJECTBUFFER(%rip), %eax
	addl	$1, %eax
	movl	%eax, PROJECTBUFFER(%rip)
	movl	PROJECTBUFFER(%rip), %eax
	cmpl	$1, %eax
	jne	.L62
	movl	PROJECTBUFFER(%rip), %edx
	movq	stderr(%rip), %rax
	leaq	.LC26(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	jmp	.L72
.L62:
	movl	PROJECTBUFFER(%rip), %eax
	cmpl	$2, %eax
	jne	.L64
	movl	PROJECTBUFFER(%rip), %edx
	movq	stderr(%rip), %rax
	leaq	.LC27(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	jmp	.L72
.L64:
	movl	PROJECTBUFFER(%rip), %eax
	cmpl	$3, %eax
	jne	.L72
	movl	PROJECTBUFFER(%rip), %edx
	movq	stderr(%rip), %rax
	leaq	.LC28(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	jmp	.L72
.L50:
	movss	bias(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC29(%rip), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, bias(%rip)
	movss	bias(%rip), %xmm0
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm0, %xmm4
	movq	%xmm4, %rax
	movq	%rax, %xmm0
	leaq	.LC30(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L60
.L45:
	movss	bias(%rip), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC29(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, bias(%rip)
	movss	bias(%rip), %xmm0
	pxor	%xmm5, %xmm5
	cvtss2sd	%xmm0, %xmm5
	movq	%xmm5, %rax
	movq	%rax, %xmm0
	leaq	.LC30(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L60
.L44:
	movl	PROJECTIONVIEW(%rip), %eax
	testl	%eax, %eax
	jne	.L65
	movl	PROJECTIONVIEW(%rip), %eax
	addl	$1, %eax
	movl	%eax, PROJECTIONVIEW(%rip)
	jmp	.L60
.L65:
	movl	$0, PROJECTIONVIEW(%rip)
	jmp	.L60
.L33:
	movss	FPlane(%rip), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC31(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, FPlane(%rip)
	movss	FPlane(%rip), %xmm0
	pxor	%xmm6, %xmm6
	cvtss2sd	%xmm0, %xmm6
	movq	%xmm6, %rax
	movq	%rax, %xmm0
	leaq	.LC32(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L60
.L32:
	movss	FPlane(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC31(%rip), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, FPlane(%rip)
	movss	FPlane(%rip), %xmm0
	pxor	%xmm7, %xmm7
	cvtss2sd	%xmm0, %xmm7
	movq	%xmm7, %rax
	movq	%rax, %xmm0
	leaq	.LC32(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L60
.L34:
	movss	NPlane(%rip), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC33(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, NPlane(%rip)
	movss	NPlane(%rip), %xmm0
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm0, %xmm4
	movq	%xmm4, %rax
	movq	%rax, %xmm0
	leaq	.LC34(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L60
.L31:
	movss	NPlane(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC33(%rip), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, NPlane(%rip)
	movss	NPlane(%rip), %xmm0
	pxor	%xmm5, %xmm5
	cvtss2sd	%xmm0, %xmm5
	movq	%xmm5, %rax
	movq	%rax, %xmm0
	leaq	.LC34(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	jmp	.L60
.L51:
	movl	EYEPOINT(%rip), %eax
	testl	%eax, %eax
	jne	.L67
	movl	$1, EYEPOINT(%rip)
	jmp	.L60
.L67:
	movl	$0, EYEPOINT(%rip)
	jmp	.L60
.L27:
	movss	light(%rip), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC35(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, light(%rip)
	jmp	.L60
.L28:
	movss	light(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC35(%rip), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, light(%rip)
	jmp	.L60
.L30:
	movss	8+light(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC35(%rip), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, 8+light(%rip)
	jmp	.L60
.L26:
	movss	8+light(%rip), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC35(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, 8+light(%rip)
	jmp	.L60
.L24:
	movss	4+light(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC35(%rip), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, 4+light(%rip)
	jmp	.L60
.L29:
	movss	4+light(%rip), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC35(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, 4+light(%rip)
	jmp	.L60
.L58:
	movss	Scale(%rip), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC33(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, Scale(%rip)
	movss	Scale(%rip), %xmm0
	pxor	%xmm6, %xmm6
	cvtss2sd	%xmm0, %xmm6
	movq	%xmm6, %rax
	movq	%rax, %xmm0
	leaq	.LC36(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movss	Scale(%rip), %xmm0
	movl	Scale(%rip), %edx
	leaq	-112(%rbp), %rax
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	movaps	%xmm0, %xmm1
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	orthographic_mat@PLT
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, OrthoMat(%rip)
	movq	%rdx, 8+OrthoMat(%rip)
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rax, 16+OrthoMat(%rip)
	movq	%rdx, 24+OrthoMat(%rip)
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, 32+OrthoMat(%rip)
	movq	%rdx, 40+OrthoMat(%rip)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, 48+OrthoMat(%rip)
	movq	%rdx, 56+OrthoMat(%rip)
	jmp	.L60
.L57:
	movss	Scale(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC33(%rip), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, Scale(%rip)
	movss	Scale(%rip), %xmm0
	pxor	%xmm7, %xmm7
	cvtss2sd	%xmm0, %xmm7
	movq	%xmm7, %rax
	movq	%rax, %xmm0
	leaq	.LC36(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movss	Scale(%rip), %xmm0
	movl	Scale(%rip), %edx
	leaq	-112(%rbp), %rax
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	movaps	%xmm0, %xmm1
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	orthographic_mat@PLT
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, OrthoMat(%rip)
	movq	%rdx, 8+OrthoMat(%rip)
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rax, 16+OrthoMat(%rip)
	movq	%rdx, 24+OrthoMat(%rip)
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, 32+OrthoMat(%rip)
	movq	%rdx, 40+OrthoMat(%rip)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, 48+OrthoMat(%rip)
	movq	%rdx, 56+OrthoMat(%rip)
	jmp	.L60
.L59:
	leaq	-192(%rbp), %rdx
	subq	$80, %rsp
	movq	%rsp, %rax
	movq	light(%rip), %rcx
	movq	8+light(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+light(%rip), %rcx
	movq	24+light(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+light(%rip), %rcx
	movq	40+light(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+light(%rip), %rcx
	movq	56+light(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	64+light(%rip), %rcx
	movq	72+light(%rip), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	%rdx, %rdi
	call	rerasterize
	addq	$80, %rsp
	jmp	.L60
.L72:
	nop
.L60:
	leaq	-192(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	48(%rax), %r11
	movq	56(%rax), %r10
	movq	-24(%rbp), %rax
	movq	32(%rax), %r9
	movq	40(%rax), %r8
	movq	-24(%rbp), %rax
	movq	16(%rax), %rdi
	movq	24(%rax), %rsi
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rax
	movq	%r11, %xmm6
	movq	%r10, %xmm7
	movq	%r9, %xmm4
	movq	%r8, %xmm5
	movq	%rdi, %xmm2
	movq	%rsi, %xmm3
	movq	%rcx, %xmm0
	movq	%rax, %xmm1
	movq	%rdx, %rdi
	call	lookat@PLT
	movq	-192(%rbp), %rax
	movq	-184(%rbp), %rdx
	movq	%rax, LookAt(%rip)
	movq	%rdx, 8+LookAt(%rip)
	movq	-176(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rax, 16+LookAt(%rip)
	movq	%rdx, 24+LookAt(%rip)
	movq	-160(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rax, 32+LookAt(%rip)
	movq	%rdx, 40+LookAt(%rip)
	movq	-144(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rax, 48+LookAt(%rip)
	movq	%rdx, 56+LookAt(%rip)
	leaq	-192(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	LookAt(%rip), %rcx
	movq	8+LookAt(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+LookAt(%rip), %rcx
	movq	24+LookAt(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+LookAt(%rip), %rcx
	movq	40+LookAt(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+LookAt(%rip), %rcx
	movq	56+LookAt(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	inverse_mat@PLT
	addq	$64, %rsp
	movq	-192(%rbp), %rax
	movq	-184(%rbp), %rdx
	movq	%rax, ViewMat(%rip)
	movq	%rdx, 8+ViewMat(%rip)
	movq	-176(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rax, 16+ViewMat(%rip)
	movq	%rdx, 24+ViewMat(%rip)
	movq	-160(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rax, 32+ViewMat(%rip)
	movq	%rdx, 40+ViewMat(%rip)
	movq	-144(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rax, 48+ViewMat(%rip)
	movq	%rdx, 56+ViewMat(%rip)
	movq	light(%rip), %rdx
	movq	8+light(%rip), %rsi
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	ViewMat(%rip), %rcx
	movq	8+ViewMat(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+ViewMat(%rip), %rcx
	movq	24+ViewMat(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+ViewMat(%rip), %rcx
	movq	40+ViewMat(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+ViewMat(%rip), %rcx
	movq	56+ViewMat(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %xmm0
	movq	%rsi, %xmm1
	call	vecxm@PLT
	addq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, model(%rip)
	movq	%xmm0, 8+model(%rip)
	movl	$1, AdjustShadow(%rip)
	movl	$1, AdjustScene(%rip)
	movl	PROJECTIONVIEW(%rip), %eax
	testl	%eax, %eax
	jne	.L70
	leaq	-192(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	PerspMat(%rip), %rcx
	movq	8+PerspMat(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+PerspMat(%rip), %rcx
	movq	24+PerspMat(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+PerspMat(%rip), %rcx
	movq	40+PerspMat(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+PerspMat(%rip), %rcx
	movq	56+PerspMat(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	ViewMat(%rip), %rcx
	movq	8+ViewMat(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+ViewMat(%rip), %rcx
	movq	24+ViewMat(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+ViewMat(%rip), %rcx
	movq	40+ViewMat(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+ViewMat(%rip), %rcx
	movq	56+ViewMat(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	mxm@PLT
	subq	$-128, %rsp
	movq	-192(%rbp), %rax
	movq	-184(%rbp), %rdx
	movq	%rax, WorldMat(%rip)
	movq	%rdx, 8+WorldMat(%rip)
	movq	-176(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rax, 16+WorldMat(%rip)
	movq	%rdx, 24+WorldMat(%rip)
	movq	-160(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rax, 32+WorldMat(%rip)
	movq	%rdx, 40+WorldMat(%rip)
	movq	-144(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rax, 48+WorldMat(%rip)
	movq	%rdx, 56+WorldMat(%rip)
	jmp	.L17
.L70:
	leaq	-192(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	OrthoMat(%rip), %rcx
	movq	8+OrthoMat(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+OrthoMat(%rip), %rcx
	movq	24+OrthoMat(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+OrthoMat(%rip), %rcx
	movq	40+OrthoMat(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+OrthoMat(%rip), %rcx
	movq	56+OrthoMat(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	ViewMat(%rip), %rcx
	movq	8+ViewMat(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+ViewMat(%rip), %rcx
	movq	24+ViewMat(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+ViewMat(%rip), %rcx
	movq	40+ViewMat(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+ViewMat(%rip), %rcx
	movq	56+ViewMat(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	mxm@PLT
	subq	$-128, %rsp
	movq	-192(%rbp), %rax
	movq	-184(%rbp), %rdx
	movq	%rax, WorldMat(%rip)
	movq	%rdx, 8+WorldMat(%rip)
	movq	-176(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rax, 16+WorldMat(%rip)
	movq	%rdx, 24+WorldMat(%rip)
	movq	-160(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rax, 32+WorldMat(%rip)
	movq	%rdx, 40+WorldMat(%rip)
	movq	-144(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rax, 48+WorldMat(%rip)
	movq	%rdx, 56+WorldMat(%rip)
	jmp	.L17
.L71:
	nop
.L17:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	keypress, .-keypress
	.type	rotate_x, @function
rotate_x:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$280, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -184(%rbp)
	movss	%xmm0, -188(%rbp)
	movl	-188(%rbp), %eax
	movd	%eax, %xmm0
	call	radians@PLT
	movd	%xmm0, %eax
	leaq	-80(%rbp), %rdx
	movd	%eax, %xmm0
	movq	%rdx, %rdi
	call	rotate_xmat@PLT
	movq	-184(%rbp), %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -176(%rbp)
	movq	%rbx, -168(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -160(%rbp)
	movq	%rbx, -152(%rbp)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, -144(%rbp)
	movq	%rbx, -136(%rbp)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, -128(%rbp)
	movq	%rbx, -120(%rbp)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, -112(%rbp)
	movq	%rbx, -104(%rbp)
	movq	88(%rax), %rdx
	movq	80(%rax), %rax
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	movq	-184(%rbp), %rbx
	leaq	-288(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-80(%rbp), %rsi
	movq	-72(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-64(%rbp), %rsi
	movq	-56(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-32(%rbp), %rsi
	movq	-24(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-176(%rbp), %rsi
	movq	-168(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-160(%rbp), %rsi
	movq	-152(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-144(%rbp), %rsi
	movq	-136(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-128(%rbp), %rsi
	movq	-120(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	movq	-112(%rbp), %rsi
	movq	-104(%rbp), %rdi
	movq	%rsi, 64(%rax)
	movq	%rdi, 72(%rax)
	movq	-96(%rbp), %rsi
	movq	-88(%rbp), %rdi
	movq	%rsi, 80(%rax)
	movq	%rdi, 88(%rax)
	movq	%rdx, %rdi
	call	meshxm@PLT
	addq	$160, %rsp
	movq	-288(%rbp), %rax
	movq	-280(%rbp), %rdx
	movq	%rax, (%rbx)
	movq	%rdx, 8(%rbx)
	movq	-272(%rbp), %rax
	movq	-264(%rbp), %rdx
	movq	%rax, 16(%rbx)
	movq	%rdx, 24(%rbx)
	movq	-256(%rbp), %rax
	movq	-248(%rbp), %rdx
	movq	%rax, 32(%rbx)
	movq	%rdx, 40(%rbx)
	movq	-240(%rbp), %rax
	movq	-232(%rbp), %rdx
	movq	%rax, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	-224(%rbp), %rax
	movq	-216(%rbp), %rdx
	movq	%rax, 64(%rbx)
	movq	%rdx, 72(%rbx)
	movq	-208(%rbp), %rax
	movq	-200(%rbp), %rdx
	movq	%rax, 80(%rbx)
	movq	%rdx, 88(%rbx)
	movq	-176(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-168(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	rotate_x, .-rotate_x
	.type	rotate_y, @function
rotate_y:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$280, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -184(%rbp)
	movss	%xmm0, -188(%rbp)
	movl	-188(%rbp), %eax
	movd	%eax, %xmm0
	call	radians@PLT
	movd	%xmm0, %eax
	leaq	-80(%rbp), %rdx
	movd	%eax, %xmm0
	movq	%rdx, %rdi
	call	rotate_ymat@PLT
	movq	-184(%rbp), %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -176(%rbp)
	movq	%rbx, -168(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -160(%rbp)
	movq	%rbx, -152(%rbp)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, -144(%rbp)
	movq	%rbx, -136(%rbp)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, -128(%rbp)
	movq	%rbx, -120(%rbp)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, -112(%rbp)
	movq	%rbx, -104(%rbp)
	movq	88(%rax), %rdx
	movq	80(%rax), %rax
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	movq	-184(%rbp), %rbx
	leaq	-288(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-80(%rbp), %rsi
	movq	-72(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-64(%rbp), %rsi
	movq	-56(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-32(%rbp), %rsi
	movq	-24(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-176(%rbp), %rsi
	movq	-168(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-160(%rbp), %rsi
	movq	-152(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-144(%rbp), %rsi
	movq	-136(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-128(%rbp), %rsi
	movq	-120(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	movq	-112(%rbp), %rsi
	movq	-104(%rbp), %rdi
	movq	%rsi, 64(%rax)
	movq	%rdi, 72(%rax)
	movq	-96(%rbp), %rsi
	movq	-88(%rbp), %rdi
	movq	%rsi, 80(%rax)
	movq	%rdi, 88(%rax)
	movq	%rdx, %rdi
	call	meshxm@PLT
	addq	$160, %rsp
	movq	-288(%rbp), %rax
	movq	-280(%rbp), %rdx
	movq	%rax, (%rbx)
	movq	%rdx, 8(%rbx)
	movq	-272(%rbp), %rax
	movq	-264(%rbp), %rdx
	movq	%rax, 16(%rbx)
	movq	%rdx, 24(%rbx)
	movq	-256(%rbp), %rax
	movq	-248(%rbp), %rdx
	movq	%rax, 32(%rbx)
	movq	%rdx, 40(%rbx)
	movq	-240(%rbp), %rax
	movq	-232(%rbp), %rdx
	movq	%rax, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	-224(%rbp), %rax
	movq	-216(%rbp), %rdx
	movq	%rax, 64(%rbx)
	movq	%rdx, 72(%rbx)
	movq	-208(%rbp), %rax
	movq	-200(%rbp), %rdx
	movq	%rax, 80(%rbx)
	movq	%rdx, 88(%rbx)
	movq	-176(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-168(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	rotate_y, .-rotate_y
	.type	rotate_z, @function
rotate_z:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$280, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -184(%rbp)
	movss	%xmm0, -188(%rbp)
	movl	-188(%rbp), %eax
	movd	%eax, %xmm0
	call	radians@PLT
	movd	%xmm0, %eax
	leaq	-80(%rbp), %rdx
	movd	%eax, %xmm0
	movq	%rdx, %rdi
	call	rotate_zmat@PLT
	movq	-184(%rbp), %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -176(%rbp)
	movq	%rbx, -168(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -160(%rbp)
	movq	%rbx, -152(%rbp)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, -144(%rbp)
	movq	%rbx, -136(%rbp)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, -128(%rbp)
	movq	%rbx, -120(%rbp)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, -112(%rbp)
	movq	%rbx, -104(%rbp)
	movq	88(%rax), %rdx
	movq	80(%rax), %rax
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	movq	-184(%rbp), %rbx
	leaq	-288(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-80(%rbp), %rsi
	movq	-72(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-64(%rbp), %rsi
	movq	-56(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-32(%rbp), %rsi
	movq	-24(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-176(%rbp), %rsi
	movq	-168(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-160(%rbp), %rsi
	movq	-152(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-144(%rbp), %rsi
	movq	-136(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-128(%rbp), %rsi
	movq	-120(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	movq	-112(%rbp), %rsi
	movq	-104(%rbp), %rdi
	movq	%rsi, 64(%rax)
	movq	%rdi, 72(%rax)
	movq	-96(%rbp), %rsi
	movq	-88(%rbp), %rdi
	movq	%rsi, 80(%rax)
	movq	%rdi, 88(%rax)
	movq	%rdx, %rdi
	call	meshxm@PLT
	addq	$160, %rsp
	movq	-288(%rbp), %rax
	movq	-280(%rbp), %rdx
	movq	%rax, (%rbx)
	movq	%rdx, 8(%rbx)
	movq	-272(%rbp), %rax
	movq	-264(%rbp), %rdx
	movq	%rax, 16(%rbx)
	movq	%rdx, 24(%rbx)
	movq	-256(%rbp), %rax
	movq	-248(%rbp), %rdx
	movq	%rax, 32(%rbx)
	movq	%rdx, 40(%rbx)
	movq	-240(%rbp), %rax
	movq	-232(%rbp), %rdx
	movq	%rax, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	-224(%rbp), %rax
	movq	-216(%rbp), %rdx
	movq	%rax, 64(%rbx)
	movq	%rdx, 72(%rbx)
	movq	-208(%rbp), %rax
	movq	-200(%rbp), %rdx
	movq	%rax, 80(%rbx)
	movq	%rdx, 88(%rbx)
	movq	-176(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-168(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	rotate_z, .-rotate_z
	.type	rotate_origin, @function
rotate_origin:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$392, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -280(%rbp)
	movss	%xmm0, -284(%rbp)
	movss	%xmm1, -288(%rbp)
	movss	%xmm2, -292(%rbp)
	movss	%xmm3, -296(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -32(%rbp)
	movss	.LC37(%rip), %xmm0
	movss	%xmm0, -28(%rbp)
	movss	.LC38(%rip), %xmm0
	movss	%xmm0, -24(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movss	-288(%rbp), %xmm0
	movss	%xmm0, -48(%rbp)
	movss	-292(%rbp), %xmm0
	movss	%xmm0, -44(%rbp)
	movss	-296(%rbp), %xmm0
	movss	%xmm0, -40(%rbp)
	leaq	-80(%rbp), %rax
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	%rcx, %xmm1
	movq	%rdx, %xmm2
	movl	.LC25(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	setQuat@PLT
	leaq	-112(%rbp), %rax
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rcx
	movl	-284(%rbp), %edx
	movq	%rsi, %xmm1
	movq	%rcx, %xmm2
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	rotationQuat@PLT
	leaq	-176(%rbp), %rsi
	movq	-76(%rbp), %rdi
	movq	-68(%rbp), %r8
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movl	-96(%rbp), %eax
	movl	%eax, 16(%rcx)
	movq	%rdi, %xmm0
	movq	%r8, %xmm1
	movq	%rsi, %rdi
	call	MatfromQuat@PLT
	addq	$32, %rsp
	movq	-280(%rbp), %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -272(%rbp)
	movq	%rbx, -264(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -256(%rbp)
	movq	%rbx, -248(%rbp)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, -240(%rbp)
	movq	%rbx, -232(%rbp)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, -224(%rbp)
	movq	%rbx, -216(%rbp)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, -208(%rbp)
	movq	%rbx, -200(%rbp)
	movq	88(%rax), %rdx
	movq	80(%rax), %rax
	movq	%rax, -192(%rbp)
	movq	%rdx, -184(%rbp)
	leaq	-272(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-176(%rbp), %rcx
	movq	-168(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-160(%rbp), %rcx
	movq	-152(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	normalsxm@PLT
	addq	$64, %rsp
	movq	-280(%rbp), %rbx
	leaq	-400(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-176(%rbp), %rsi
	movq	-168(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-160(%rbp), %rsi
	movq	-152(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-144(%rbp), %rsi
	movq	-136(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-128(%rbp), %rsi
	movq	-120(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-272(%rbp), %rsi
	movq	-264(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-256(%rbp), %rsi
	movq	-248(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-240(%rbp), %rsi
	movq	-232(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-224(%rbp), %rsi
	movq	-216(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	movq	-208(%rbp), %rsi
	movq	-200(%rbp), %rdi
	movq	%rsi, 64(%rax)
	movq	%rdi, 72(%rax)
	movq	-192(%rbp), %rsi
	movq	-184(%rbp), %rdi
	movq	%rsi, 80(%rax)
	movq	%rdi, 88(%rax)
	movq	%rdx, %rdi
	call	meshxm@PLT
	addq	$160, %rsp
	movq	-400(%rbp), %rax
	movq	-392(%rbp), %rdx
	movq	%rax, (%rbx)
	movq	%rdx, 8(%rbx)
	movq	-384(%rbp), %rax
	movq	-376(%rbp), %rdx
	movq	%rax, 16(%rbx)
	movq	%rdx, 24(%rbx)
	movq	-368(%rbp), %rax
	movq	-360(%rbp), %rdx
	movq	%rax, 32(%rbx)
	movq	%rdx, 40(%rbx)
	movq	-352(%rbp), %rax
	movq	-344(%rbp), %rdx
	movq	%rax, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	-336(%rbp), %rax
	movq	-328(%rbp), %rdx
	movq	%rax, 64(%rbx)
	movq	%rdx, 72(%rbx)
	movq	-320(%rbp), %rax
	movq	-312(%rbp), %rdx
	movq	%rax, 80(%rbx)
	movq	%rdx, 88(%rbx)
	movq	-272(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-264(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	rotate_origin, .-rotate_origin
	.type	rotate_light, @function
rotate_light:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$184, %rsp
	.cfi_offset 3, -24
	movss	%xmm0, -180(%rbp)
	movss	%xmm1, -184(%rbp)
	movss	%xmm2, -188(%rbp)
	movss	%xmm3, -192(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movss	.LC39(%rip), %xmm0
	movss	%xmm0, -24(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movss	-184(%rbp), %xmm0
	movss	%xmm0, -48(%rbp)
	movss	-188(%rbp), %xmm0
	movss	%xmm0, -44(%rbp)
	movss	-192(%rbp), %xmm0
	movss	%xmm0, -40(%rbp)
	leaq	-80(%rbp), %rax
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	%rcx, %xmm1
	movq	%rdx, %xmm2
	movl	.LC25(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	setQuat@PLT
	leaq	-112(%rbp), %rax
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	%rcx, %xmm1
	movq	%rdx, %xmm2
	movl	.LC19(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	rotationQuat@PLT
	leaq	-176(%rbp), %rsi
	movq	-76(%rbp), %rdi
	movq	-68(%rbp), %r8
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movl	-96(%rbp), %eax
	movl	%eax, 16(%rcx)
	movq	%rdi, %xmm0
	movq	%r8, %xmm1
	movq	%rsi, %rdi
	call	MatfromQuat@PLT
	addq	$32, %rsp
	movq	16(%rbp), %rdx
	movq	24(%rbp), %rsi
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-176(%rbp), %rcx
	movq	-168(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-160(%rbp), %rcx
	movq	-152(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %xmm0
	movq	%rsi, %xmm1
	call	vecxm@PLT
	addq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, light(%rip)
	movq	%xmm0, 8+light(%rip)
	movq	32(%rbp), %rdx
	movq	40(%rbp), %rsi
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-176(%rbp), %rcx
	movq	-168(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-160(%rbp), %rcx
	movq	-152(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %xmm0
	movq	%rsi, %xmm1
	call	vecxm@PLT
	addq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, 16+light(%rip)
	movq	%xmm0, 24+light(%rip)
	movq	48(%rbp), %rdx
	movq	56(%rbp), %rsi
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-176(%rbp), %rcx
	movq	-168(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-160(%rbp), %rcx
	movq	-152(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %xmm0
	movq	%rsi, %xmm1
	call	vecxm@PLT
	addq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, 32+light(%rip)
	movq	%xmm0, 40+light(%rip)
	movq	64(%rbp), %rdx
	movq	72(%rbp), %rsi
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-176(%rbp), %rcx
	movq	-168(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-160(%rbp), %rcx
	movq	-152(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %xmm0
	movq	%rsi, %xmm1
	call	vecxm@PLT
	addq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, 48+light(%rip)
	movq	%xmm0, 56+light(%rip)
	subq	$80, %rsp
	movq	%rsp, %rax
	movq	light(%rip), %rcx
	movq	8+light(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+light(%rip), %rcx
	movq	24+light(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+light(%rip), %rcx
	movq	40+light(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+light(%rip), %rcx
	movq	56+light(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	64+light(%rip), %rcx
	movq	72+light(%rip), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	call	logGlobal@PLT
	addq	$80, %rsp
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	rotate_light, .-rotate_light
	.type	initBuffers, @function
initBuffers:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	8+wa(%rip), %ecx
	movl	12+wa(%rip), %edx
	movq	pixels(%rip), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	create2darray@PLT
	movq	%rax, pixels(%rip)
	movl	8+wa(%rip), %ecx
	movl	12+wa(%rip), %edx
	movq	depth_buffer(%rip), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	create2darray@PLT
	movq	%rax, depth_buffer(%rip)
	movl	8+wa(%rip), %ecx
	movl	12+wa(%rip), %edx
	movq	shadow_buffer(%rip), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	create2darray@PLT
	movq	%rax, shadow_buffer(%rip)
	movl	8+wa(%rip), %edx
	movl	12+wa(%rip), %eax
	imull	%edx, %eax
	sall	$2, %eax
	cltq
	movl	$1, %esi
	movq	%rax, %rdi
	call	calloc@PLT
	movq	%rax, frame_buffer(%rip)
	movl	$0, -4(%rbp)
	jmp	.L79
.L80:
	movl	8+wa(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rax, %rdx
	movq	pixels(%rip), %rax
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rax
	movq	(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movl	8+wa(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	depth_buffer(%rip), %rax
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rax
	movq	(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movl	8+wa(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	shadow_buffer(%rip), %rax
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rax
	movq	(%rax), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	memset@PLT
	addl	$1, -4(%rbp)
.L79:
	movl	12+wa(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L80
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	initBuffers, .-initBuffers
	.section	.rodata
.LC40:
	.string	"objects/terrain.obj"
.LC41:
	.string	"textures/stones.bmp"
.LC44:
	.string	"objects/earth.obj"
.LC47:
	.string	"textures/Earth.bmp"
.LC49:
	.string	"objects/spacedom.obj"
.LC50:
	.string	"textures/light.bmp"
	.text
	.type	initMeshes, @function
initMeshes:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$792, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -696(%rbp)
	leaq	-112(%rbp), %rdx
	movl	$0, %eax
	movl	$12, %ecx
	movq	%rdx, %rdi
	rep stosq
	leaq	-208(%rbp), %rdx
	movl	$0, %eax
	movl	$12, %ecx
	movq	%rdx, %rdi
	rep stosq
	leaq	-304(%rbp), %rdx
	movl	$0, %eax
	movl	$12, %ecx
	movq	%rdx, %rdi
	rep stosq
	leaq	-400(%rbp), %rdx
	movl	$0, %eax
	movl	$12, %ecx
	movq	%rdx, %rdi
	rep stosq
	leaq	-496(%rbp), %rdx
	movl	$0, %eax
	movl	$12, %ecx
	movq	%rdx, %rdi
	rep stosq
	leaq	-800(%rbp), %rax
	leaq	.LC40(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	load_obj@PLT
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -208(%rbp)
	movq	%rdx, -200(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -192(%rbp)
	movq	%rdx, -184(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -176(%rbp)
	movq	%rdx, -168(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -160(%rbp)
	movq	%rdx, -152(%rbp)
	movq	-736(%rbp), %rax
	movq	-728(%rbp), %rdx
	movq	%rax, -144(%rbp)
	movq	%rdx, -136(%rbp)
	movq	-720(%rbp), %rax
	movq	-712(%rbp), %rdx
	movq	%rax, -128(%rbp)
	movq	%rdx, -120(%rbp)
	leaq	-208(%rbp), %rax
	addq	$24, %rax
	movl	$20, %edx
	leaq	.LC41(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	leaq	-208(%rbp), %rax
	movq	%rax, %rdi
	call	loadTexture
	leaq	-560(%rbp), %rax
	movl	.LC42(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	scale_mat@PLT
	leaq	-624(%rbp), %rax
	movss	.LC43(%rip), %xmm2
	pxor	%xmm1, %xmm1
	movl	.LC25(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	translation_mat@PLT
	leaq	-688(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-624(%rbp), %rcx
	movq	-616(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-608(%rbp), %rcx
	movq	-600(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-592(%rbp), %rcx
	movq	-584(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-576(%rbp), %rcx
	movq	-568(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-560(%rbp), %rcx
	movq	-552(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-528(%rbp), %rcx
	movq	-520(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-512(%rbp), %rcx
	movq	-504(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	mxm@PLT
	subq	$-128, %rsp
	movq	-696(%rbp), %rax
	movq	(%rax), %rbx
	leaq	-800(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-688(%rbp), %rsi
	movq	-680(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-672(%rbp), %rsi
	movq	-664(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-656(%rbp), %rsi
	movq	-648(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-640(%rbp), %rsi
	movq	-632(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-208(%rbp), %rsi
	movq	-200(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-192(%rbp), %rsi
	movq	-184(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-176(%rbp), %rsi
	movq	-168(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-160(%rbp), %rsi
	movq	-152(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	movq	-144(%rbp), %rsi
	movq	-136(%rbp), %rdi
	movq	%rsi, 64(%rax)
	movq	%rdi, 72(%rax)
	movq	-128(%rbp), %rsi
	movq	-120(%rbp), %rdi
	movq	%rsi, 80(%rax)
	movq	%rdi, 88(%rax)
	movq	%rdx, %rdi
	call	meshxm@PLT
	addq	$160, %rsp
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, (%rbx)
	movq	%rdx, 8(%rbx)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, 16(%rbx)
	movq	%rdx, 24(%rbx)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, 32(%rbx)
	movq	%rdx, 40(%rbx)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	-736(%rbp), %rax
	movq	-728(%rbp), %rdx
	movq	%rax, 64(%rbx)
	movq	%rdx, 72(%rbx)
	movq	-720(%rbp), %rax
	movq	-712(%rbp), %rdx
	movq	%rax, 80(%rbx)
	movq	%rdx, 88(%rbx)
	movq	-200(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-208(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	leaq	-800(%rbp), %rax
	leaq	.LC44(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	load_obj@PLT
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -304(%rbp)
	movq	%rdx, -296(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -288(%rbp)
	movq	%rdx, -280(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -272(%rbp)
	movq	%rdx, -264(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -256(%rbp)
	movq	%rdx, -248(%rbp)
	movq	-736(%rbp), %rax
	movq	-728(%rbp), %rdx
	movq	%rax, -240(%rbp)
	movq	%rdx, -232(%rbp)
	movq	-720(%rbp), %rax
	movq	-712(%rbp), %rdx
	movq	%rax, -224(%rbp)
	movq	%rdx, -216(%rbp)
	leaq	-304(%rbp), %rax
	addq	$24, %rax
	movl	$20, %edx
	leaq	.LC41(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	leaq	-304(%rbp), %rax
	movq	%rax, %rdi
	call	loadTexture
	leaq	-800(%rbp), %rax
	movl	.LC42(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	scale_mat@PLT
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -560(%rbp)
	movq	%rdx, -552(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -544(%rbp)
	movq	%rdx, -536(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -528(%rbp)
	movq	%rdx, -520(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -512(%rbp)
	movq	%rdx, -504(%rbp)
	leaq	-800(%rbp), %rax
	movss	.LC45(%rip), %xmm2
	pxor	%xmm1, %xmm1
	movl	.LC46(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	translation_mat@PLT
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -624(%rbp)
	movq	%rdx, -616(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -608(%rbp)
	movq	%rdx, -600(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -592(%rbp)
	movq	%rdx, -584(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -576(%rbp)
	movq	%rdx, -568(%rbp)
	leaq	-800(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-624(%rbp), %rcx
	movq	-616(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-608(%rbp), %rcx
	movq	-600(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-592(%rbp), %rcx
	movq	-584(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-576(%rbp), %rcx
	movq	-568(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-560(%rbp), %rcx
	movq	-552(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-528(%rbp), %rcx
	movq	-520(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-512(%rbp), %rcx
	movq	-504(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	mxm@PLT
	subq	$-128, %rsp
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -688(%rbp)
	movq	%rdx, -680(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -672(%rbp)
	movq	%rdx, -664(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -656(%rbp)
	movq	%rdx, -648(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -640(%rbp)
	movq	%rdx, -632(%rbp)
	movq	-696(%rbp), %rax
	movq	(%rax), %rax
	leaq	96(%rax), %rbx
	leaq	-800(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-688(%rbp), %rsi
	movq	-680(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-672(%rbp), %rsi
	movq	-664(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-656(%rbp), %rsi
	movq	-648(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-640(%rbp), %rsi
	movq	-632(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-304(%rbp), %rsi
	movq	-296(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-288(%rbp), %rsi
	movq	-280(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-272(%rbp), %rsi
	movq	-264(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-256(%rbp), %rsi
	movq	-248(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	movq	-240(%rbp), %rsi
	movq	-232(%rbp), %rdi
	movq	%rsi, 64(%rax)
	movq	%rdi, 72(%rax)
	movq	-224(%rbp), %rsi
	movq	-216(%rbp), %rdi
	movq	%rsi, 80(%rax)
	movq	%rdi, 88(%rax)
	movq	%rdx, %rdi
	call	meshxm@PLT
	addq	$160, %rsp
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, (%rbx)
	movq	%rdx, 8(%rbx)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, 16(%rbx)
	movq	%rdx, 24(%rbx)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, 32(%rbx)
	movq	%rdx, 40(%rbx)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	-736(%rbp), %rax
	movq	-728(%rbp), %rdx
	movq	%rax, 64(%rbx)
	movq	%rdx, 72(%rbx)
	movq	-720(%rbp), %rax
	movq	-712(%rbp), %rdx
	movq	%rax, 80(%rbx)
	movq	%rdx, 88(%rbx)
	movq	-296(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-304(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	leaq	-800(%rbp), %rax
	leaq	.LC44(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	load_obj@PLT
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -400(%rbp)
	movq	%rdx, -392(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -384(%rbp)
	movq	%rdx, -376(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -368(%rbp)
	movq	%rdx, -360(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -352(%rbp)
	movq	%rdx, -344(%rbp)
	movq	-736(%rbp), %rax
	movq	-728(%rbp), %rdx
	movq	%rax, -336(%rbp)
	movq	%rdx, -328(%rbp)
	movq	-720(%rbp), %rax
	movq	-712(%rbp), %rdx
	movq	%rax, -320(%rbp)
	movq	%rdx, -312(%rbp)
	leaq	-400(%rbp), %rax
	addq	$24, %rax
	movl	$19, %edx
	leaq	.LC47(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	leaq	-400(%rbp), %rax
	movq	%rax, %rdi
	call	loadTexture
	leaq	-800(%rbp), %rax
	movl	.LC48(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	scale_mat@PLT
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -560(%rbp)
	movq	%rdx, -552(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -544(%rbp)
	movq	%rdx, -536(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -528(%rbp)
	movq	%rdx, -520(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -512(%rbp)
	movq	%rdx, -504(%rbp)
	leaq	-800(%rbp), %rax
	movss	.LC38(%rip), %xmm2
	movss	.LC37(%rip), %xmm1
	movl	.LC19(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	translation_mat@PLT
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -624(%rbp)
	movq	%rdx, -616(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -608(%rbp)
	movq	%rdx, -600(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -592(%rbp)
	movq	%rdx, -584(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -576(%rbp)
	movq	%rdx, -568(%rbp)
	leaq	-800(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-624(%rbp), %rcx
	movq	-616(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-608(%rbp), %rcx
	movq	-600(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-592(%rbp), %rcx
	movq	-584(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-576(%rbp), %rcx
	movq	-568(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-560(%rbp), %rcx
	movq	-552(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-528(%rbp), %rcx
	movq	-520(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-512(%rbp), %rcx
	movq	-504(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	mxm@PLT
	subq	$-128, %rsp
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -688(%rbp)
	movq	%rdx, -680(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -672(%rbp)
	movq	%rdx, -664(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -656(%rbp)
	movq	%rdx, -648(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -640(%rbp)
	movq	%rdx, -632(%rbp)
	movq	-696(%rbp), %rax
	movq	(%rax), %rax
	leaq	192(%rax), %rbx
	leaq	-800(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-688(%rbp), %rsi
	movq	-680(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-672(%rbp), %rsi
	movq	-664(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-656(%rbp), %rsi
	movq	-648(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-640(%rbp), %rsi
	movq	-632(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-400(%rbp), %rsi
	movq	-392(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-384(%rbp), %rsi
	movq	-376(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-368(%rbp), %rsi
	movq	-360(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-352(%rbp), %rsi
	movq	-344(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	movq	-336(%rbp), %rsi
	movq	-328(%rbp), %rdi
	movq	%rsi, 64(%rax)
	movq	%rdi, 72(%rax)
	movq	-320(%rbp), %rsi
	movq	-312(%rbp), %rdi
	movq	%rsi, 80(%rax)
	movq	%rdi, 88(%rax)
	movq	%rdx, %rdi
	call	meshxm@PLT
	addq	$160, %rsp
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, (%rbx)
	movq	%rdx, 8(%rbx)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, 16(%rbx)
	movq	%rdx, 24(%rbx)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, 32(%rbx)
	movq	%rdx, 40(%rbx)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	-736(%rbp), %rax
	movq	-728(%rbp), %rdx
	movq	%rax, 64(%rbx)
	movq	%rdx, 72(%rbx)
	movq	-720(%rbp), %rax
	movq	-712(%rbp), %rdx
	movq	%rax, 80(%rbx)
	movq	%rdx, 88(%rbx)
	movq	-392(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-400(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	leaq	-800(%rbp), %rax
	leaq	.LC49(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	load_obj@PLT
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -496(%rbp)
	movq	%rdx, -488(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -480(%rbp)
	movq	%rdx, -472(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -464(%rbp)
	movq	%rdx, -456(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -448(%rbp)
	movq	%rdx, -440(%rbp)
	movq	-736(%rbp), %rax
	movq	-728(%rbp), %rdx
	movq	%rax, -432(%rbp)
	movq	%rdx, -424(%rbp)
	movq	-720(%rbp), %rax
	movq	-712(%rbp), %rdx
	movq	%rax, -416(%rbp)
	movq	%rdx, -408(%rbp)
	leaq	-496(%rbp), %rax
	addq	$24, %rax
	movl	$19, %edx
	leaq	.LC50(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	leaq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	loadTexture
	leaq	-800(%rbp), %rax
	movl	.LC48(%rip), %edx
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	scale_mat@PLT
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -560(%rbp)
	movq	%rdx, -552(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -544(%rbp)
	movq	%rdx, -536(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -528(%rbp)
	movq	%rdx, -520(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -512(%rbp)
	movq	%rdx, -504(%rbp)
	movss	8+light(%rip), %xmm1
	movss	4+light(%rip), %xmm0
	movl	light(%rip), %edx
	leaq	-800(%rbp), %rax
	movaps	%xmm1, %xmm2
	movaps	%xmm0, %xmm1
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	translation_mat@PLT
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -624(%rbp)
	movq	%rdx, -616(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -608(%rbp)
	movq	%rdx, -600(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -592(%rbp)
	movq	%rdx, -584(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -576(%rbp)
	movq	%rdx, -568(%rbp)
	leaq	-800(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-624(%rbp), %rcx
	movq	-616(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-608(%rbp), %rcx
	movq	-600(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-592(%rbp), %rcx
	movq	-584(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-576(%rbp), %rcx
	movq	-568(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-560(%rbp), %rcx
	movq	-552(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-528(%rbp), %rcx
	movq	-520(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-512(%rbp), %rcx
	movq	-504(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	mxm@PLT
	subq	$-128, %rsp
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, -688(%rbp)
	movq	%rdx, -680(%rbp)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, -672(%rbp)
	movq	%rdx, -664(%rbp)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, -656(%rbp)
	movq	%rdx, -648(%rbp)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, -640(%rbp)
	movq	%rdx, -632(%rbp)
	movq	-696(%rbp), %rax
	movq	(%rax), %rax
	leaq	288(%rax), %rbx
	leaq	-800(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-688(%rbp), %rsi
	movq	-680(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-672(%rbp), %rsi
	movq	-664(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-656(%rbp), %rsi
	movq	-648(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-640(%rbp), %rsi
	movq	-632(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-496(%rbp), %rsi
	movq	-488(%rbp), %rdi
	movq	%rsi, (%rax)
	movq	%rdi, 8(%rax)
	movq	-480(%rbp), %rsi
	movq	-472(%rbp), %rdi
	movq	%rsi, 16(%rax)
	movq	%rdi, 24(%rax)
	movq	-464(%rbp), %rsi
	movq	-456(%rbp), %rdi
	movq	%rsi, 32(%rax)
	movq	%rdi, 40(%rax)
	movq	-448(%rbp), %rsi
	movq	-440(%rbp), %rdi
	movq	%rsi, 48(%rax)
	movq	%rdi, 56(%rax)
	movq	-432(%rbp), %rsi
	movq	-424(%rbp), %rdi
	movq	%rsi, 64(%rax)
	movq	%rdi, 72(%rax)
	movq	-416(%rbp), %rsi
	movq	-408(%rbp), %rdi
	movq	%rsi, 80(%rax)
	movq	%rdi, 88(%rax)
	movq	%rdx, %rdi
	call	meshxm@PLT
	addq	$160, %rsp
	movq	-800(%rbp), %rax
	movq	-792(%rbp), %rdx
	movq	%rax, (%rbx)
	movq	%rdx, 8(%rbx)
	movq	-784(%rbp), %rax
	movq	-776(%rbp), %rdx
	movq	%rax, 16(%rbx)
	movq	%rdx, 24(%rbx)
	movq	-768(%rbp), %rax
	movq	-760(%rbp), %rdx
	movq	%rax, 32(%rbx)
	movq	%rdx, 40(%rbx)
	movq	-752(%rbp), %rax
	movq	-744(%rbp), %rdx
	movq	%rax, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	-736(%rbp), %rax
	movq	-728(%rbp), %rdx
	movq	%rax, 64(%rbx)
	movq	%rdx, 72(%rbx)
	movq	-720(%rbp), %rax
	movq	-712(%rbp), %rdx
	movq	%rax, 80(%rbx)
	movq	%rdx, 88(%rbx)
	movq	-488(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-496(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	initMeshes, .-initMeshes
	.section	.rodata
.LC51:
	.string	"rb"
	.align 8
.LC52:
	.string	"Could not open file < %s >! loadTexture() -- fopen().\n"
	.text
	.type	loadTexture, @function
loadTexture:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	-72(%rbp), %rax
	addq	$24, %rax
	leaq	.LC51(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L83
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movq	-72(%rbp), %rax
	leaq	24(%rax), %rdx
	movq	stderr(%rip), %rax
	leaq	.LC52(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	jmp	.L84
.L83:
	movq	-16(%rbp), %rdx
	leaq	-28(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$12, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	-16(%rbp), %rax
	movl	$0, %edx
	movl	$14, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$36, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	-64(%rbp), %eax
	addl	$14, %eax
	movl	%eax, %ecx
	movq	-16(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-56(%rbp), %edx
	movq	-72(%rbp), %rax
	movl	%edx, 76(%rax)
	movl	-60(%rbp), %edx
	movq	-72(%rbp), %rax
	movl	%edx, 80(%rax)
	movl	-60(%rbp), %ecx
	movl	-56(%rbp), %edx
	movq	-72(%rbp), %rax
	movq	88(%rax), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	create2darray@PLT
	movq	-72(%rbp), %rdx
	movq	%rax, 88(%rdx)
	movl	-56(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	.L85
.L88:
	movl	$0, -8(%rbp)
	jmp	.L86
.L87:
	movq	-72(%rbp), %rax
	movq	88(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	(%rcx,%rax), %rdi
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	movl	$1, %edx
	movl	$3, %esi
	call	fread@PLT
	addl	$1, -8(%rbp)
.L86:
	movl	-60(%rbp), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L87
	subl	$1, -4(%rbp)
.L85:
	cmpl	$0, -4(%rbp)
	jns	.L88
.L84:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	loadTexture, .-loadTexture
	.type	createScene, @function
createScene:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$384, %edi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movl	$4, 8(%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	createScene, .-createScene
	.type	releaseScene, @function
releaseScene:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L91
.L92:
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movl	76(%rax), %ecx
	movq	-24(%rbp), %rax
	movq	(%rax), %rsi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rsi, %rax
	movq	88(%rax), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	free2darray@PLT
	addl	$1, -4(%rbp)
.L91:
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L92
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	releaseScene, .-releaseScene
	.type	project, @function
project:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, %rax
	movq	%rsi, %rcx
	movq	%rcx, %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	AdjustShadow(%rip), %eax
	testl	%eax, %eax
	je	.L94
	movl	$0, -4(%rbp)
	jmp	.L95
.L98:
	movl	$0, -8(%rbp)
	jmp	.L96
.L97:
	movq	shadow_buffer(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, (%rax)
	addl	$1, -8(%rbp)
.L96:
	movl	8+wa(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L97
	addl	$1, -4(%rbp)
.L95:
	movl	12+wa(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L98
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, %rsi
	call	applyShadows
	movl	$0, AdjustShadow(%rip)
.L94:
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, %rsi
	call	pipeLine
	call	displayScene
	movl	8+wa(%rip), %edx
	movl	12+wa(%rip), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	clearBuffers
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	project, .-project
	.type	applyShadows, @function
applyShadows:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$648, %rsp
	.cfi_offset 3, -24
	movq	%rdi, %rax
	movq	%rsi, %rcx
	movq	%rcx, %rdx
	movq	%rax, -592(%rbp)
	movq	%rdx, -584(%rbp)
	leaq	-96(%rbp), %rax
	movq	48+light(%rip), %r11
	movq	56+light(%rip), %r10
	movq	32+light(%rip), %r9
	movq	40+light(%rip), %r8
	movq	16+light(%rip), %rdi
	movq	24+light(%rip), %rsi
	movq	light(%rip), %rdx
	movq	8+light(%rip), %rcx
	movq	%r11, %xmm6
	movq	%r10, %xmm7
	movq	%r9, %xmm4
	movq	%r8, %xmm5
	movq	%rdi, %xmm2
	movq	%rsi, %xmm3
	movq	%rdx, %xmm0
	movq	%rcx, %xmm1
	movq	%rax, %rdi
	call	lookat@PLT
	leaq	-160(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	inverse_mat@PLT
	addq	$64, %rsp
	leaq	-656(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	OrthoMat(%rip), %rcx
	movq	8+OrthoMat(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+OrthoMat(%rip), %rcx
	movq	24+OrthoMat(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+OrthoMat(%rip), %rcx
	movq	40+OrthoMat(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+OrthoMat(%rip), %rcx
	movq	56+OrthoMat(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-160(%rbp), %rcx
	movq	-152(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-112(%rbp), %rcx
	movq	-104(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	mxm@PLT
	subq	$-128, %rsp
	movq	-656(%rbp), %rax
	movq	-648(%rbp), %rdx
	movq	%rax, LightMat(%rip)
	movq	%rdx, 8+LightMat(%rip)
	movq	-640(%rbp), %rax
	movq	-632(%rbp), %rdx
	movq	%rax, 16+LightMat(%rip)
	movq	%rdx, 24+LightMat(%rip)
	movq	-624(%rbp), %rax
	movq	-616(%rbp), %rdx
	movq	%rax, 32+LightMat(%rip)
	movq	%rdx, 40+LightMat(%rip)
	movq	-608(%rbp), %rax
	movq	-600(%rbp), %rdx
	movq	%rax, 48+LightMat(%rip)
	movq	%rdx, 56+LightMat(%rip)
	movl	$0, -20(%rbp)
	jmp	.L100
.L103:
	movq	-592(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	leaq	-576(%rbp), %rsi
	subq	$64, %rsp
	movq	%rsp, %rdx
	movq	LightMat(%rip), %rcx
	movq	8+LightMat(%rip), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16+LightMat(%rip), %rcx
	movq	24+LightMat(%rip), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32+LightMat(%rip), %rcx
	movq	40+LightMat(%rip), %rbx
	movq	%rcx, 32(%rdx)
	movq	%rbx, 40(%rdx)
	movq	48+LightMat(%rip), %rcx
	movq	56+LightMat(%rip), %rbx
	movq	%rcx, 48(%rdx)
	movq	%rbx, 56(%rdx)
	subq	$96, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, 32(%rdx)
	movq	%rbx, 40(%rdx)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, 48(%rdx)
	movq	%rbx, 56(%rdx)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, 64(%rdx)
	movq	%rbx, 72(%rdx)
	movq	80(%rax), %rcx
	movq	88(%rax), %rbx
	movq	%rcx, 80(%rdx)
	movq	%rbx, 88(%rdx)
	movq	%rsi, %rdi
	call	meshxm@PLT
	addq	$160, %rsp
	movq	$0, -176(%rbp)
	movq	$0, -168(%rbp)
	movss	NPlane(%rip), %xmm0
	movss	%xmm0, -168(%rbp)
	movq	$0, -192(%rbp)
	movq	$0, -184(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -184(%rbp)
	leaq	-480(%rbp), %rdx
	movq	-192(%rbp), %r9
	movq	-184(%rbp), %r8
	movq	-176(%rbp), %rsi
	movq	-168(%rbp), %rdi
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-576(%rbp), %rcx
	movq	-568(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-560(%rbp), %rcx
	movq	-552(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-528(%rbp), %rcx
	movq	-520(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-512(%rbp), %rcx
	movq	-504(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-496(%rbp), %rcx
	movq	-488(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%r9, %xmm2
	movq	%r8, %xmm3
	movq	%rsi, %xmm0
	movq	%rdi, %xmm1
	movq	%rdx, %rdi
	call	clipp@PLT
	addq	$96, %rsp
	movl	-460(%rbp), %eax
	testl	%eax, %eax
	je	.L101
	leaq	-384(%rbp), %rdx
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-480(%rbp), %rcx
	movq	-472(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-464(%rbp), %rcx
	movq	-456(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-448(%rbp), %rcx
	movq	-440(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-432(%rbp), %rcx
	movq	-424(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-416(%rbp), %rcx
	movq	-408(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-400(%rbp), %rcx
	movq	-392(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%rdx, %rdi
	call	shadowcull
	addq	$96, %rsp
	leaq	-288(%rbp), %rdx
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-384(%rbp), %rcx
	movq	-376(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-368(%rbp), %rcx
	movq	-360(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-352(%rbp), %rcx
	movq	-344(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-336(%rbp), %rcx
	movq	-328(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-320(%rbp), %rcx
	movq	-312(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-304(%rbp), %rcx
	movq	-296(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%rdx, %rdi
	call	viewtoscreen
	addq	$96, %rsp
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-288(%rbp), %rcx
	movq	-280(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-272(%rbp), %rcx
	movq	-264(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-256(%rbp), %rcx
	movq	-248(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-240(%rbp), %rcx
	movq	-232(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-224(%rbp), %rcx
	movq	-216(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-208(%rbp), %rcx
	movq	-200(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	call	createShadowmap@PLT
	addq	$96, %rsp
	movq	-288(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-280(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L102
.L101:
	movq	-480(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-472(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L102:
	addl	$1, -20(%rbp)
.L100:
	movl	-584(%rbp), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L103
	movl	$0, %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	applyShadows, .-applyShadows
	.type	pipeLine, @function
pipeLine:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$456, %rsp
	.cfi_offset 3, -24
	movq	%rdi, %rax
	movq	%rsi, %rcx
	movq	%rcx, %rdx
	movq	%rax, -464(%rbp)
	movq	%rdx, -456(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L106
.L109:
	movq	-464(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	leaq	-448(%rbp), %rsi
	subq	$64, %rsp
	movq	%rsp, %rdx
	movq	WorldMat(%rip), %rcx
	movq	8+WorldMat(%rip), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16+WorldMat(%rip), %rcx
	movq	24+WorldMat(%rip), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32+WorldMat(%rip), %rcx
	movq	40+WorldMat(%rip), %rbx
	movq	%rcx, 32(%rdx)
	movq	%rbx, 40(%rdx)
	movq	48+WorldMat(%rip), %rcx
	movq	56+WorldMat(%rip), %rbx
	movq	%rcx, 48(%rdx)
	movq	%rbx, 56(%rdx)
	subq	$96, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, 32(%rdx)
	movq	%rbx, 40(%rdx)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, 48(%rdx)
	movq	%rbx, 56(%rdx)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, 64(%rdx)
	movq	%rbx, 72(%rdx)
	movq	80(%rax), %rcx
	movq	88(%rax), %rbx
	movq	%rcx, 80(%rdx)
	movq	%rbx, 88(%rdx)
	movq	%rsi, %rdi
	call	meshxm@PLT
	addq	$160, %rsp
	leaq	-448(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	ViewMat(%rip), %rcx
	movq	8+ViewMat(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+ViewMat(%rip), %rcx
	movq	24+ViewMat(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+ViewMat(%rip), %rcx
	movq	40+ViewMat(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+ViewMat(%rip), %rcx
	movq	56+ViewMat(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	normalsxm@PLT
	addq	$64, %rsp
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movss	NPlane(%rip), %xmm0
	movss	%xmm0, -40(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -56(%rbp)
	leaq	-352(%rbp), %rdx
	movq	-64(%rbp), %r9
	movq	-56(%rbp), %r8
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rdi
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-448(%rbp), %rcx
	movq	-440(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-432(%rbp), %rcx
	movq	-424(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-416(%rbp), %rcx
	movq	-408(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-400(%rbp), %rcx
	movq	-392(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-384(%rbp), %rcx
	movq	-376(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-368(%rbp), %rcx
	movq	-360(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%r9, %xmm2
	movq	%r8, %xmm3
	movq	%rsi, %xmm0
	movq	%rdi, %xmm1
	movq	%rdx, %rdi
	call	clipp@PLT
	addq	$96, %rsp
	movl	-332(%rbp), %eax
	testl	%eax, %eax
	je	.L107
	leaq	-352(%rbp), %rax
	movq	%rax, %rdi
	call	ppdiv
	leaq	-256(%rbp), %rdx
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-352(%rbp), %rcx
	movq	-344(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-336(%rbp), %rcx
	movq	-328(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-320(%rbp), %rcx
	movq	-312(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-304(%rbp), %rcx
	movq	-296(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-288(%rbp), %rcx
	movq	-280(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-272(%rbp), %rcx
	movq	-264(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%rdx, %rdi
	call	bfculling
	addq	$96, %rsp
	leaq	-160(%rbp), %rdx
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-256(%rbp), %rcx
	movq	-248(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-240(%rbp), %rcx
	movq	-232(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-224(%rbp), %rcx
	movq	-216(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-208(%rbp), %rcx
	movq	-200(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-192(%rbp), %rcx
	movq	-184(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-176(%rbp), %rcx
	movq	-168(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%rdx, %rdi
	call	viewtoscreen
	addq	$96, %rsp
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-160(%rbp), %rcx
	movq	-152(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-112(%rbp), %rcx
	movq	-104(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	call	rasterize
	addq	$96, %rsp
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-152(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L108
.L107:
	movq	-352(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-344(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L108:
	addl	$1, -20(%rbp)
.L106:
	movl	-456(%rbp), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L109
	movl	$0, %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE25:
	.size	pipeLine, .-pipeLine
	.type	ppdiv, @function
ppdiv:
.LFB26:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L112
.L117:
	movl	$0, -8(%rbp)
	jmp	.L113
.L116:
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$24, %rax
	movss	(%rax), %xmm0
	pxor	%xmm1, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L114
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$12, %rax
	movss	(%rax), %xmm0
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$24, %rax
	movss	(%rax), %xmm1
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	divss	%xmm1, %xmm0
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$12, %rax
	movss	%xmm0, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$16, %rax
	movss	(%rax), %xmm0
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$24, %rax
	movss	(%rax), %xmm1
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	divss	%xmm1, %xmm0
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$16, %rax
	movss	%xmm0, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$20, %rax
	movss	(%rax), %xmm0
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$24, %rax
	movss	(%rax), %xmm1
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	divss	%xmm1, %xmm0
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$20, %rax
	movss	%xmm0, (%rax)
.L114:
	addl	$1, -8(%rbp)
.L113:
	cmpl	$2, -8(%rbp)
	jle	.L116
	addl	$1, -4(%rbp)
.L112:
	movq	-24(%rbp), %rax
	movl	20(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L117
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	ppdiv, .-ppdiv
	.section	.rodata
	.align 8
.LC53:
	.string	"Could not allocate memory - bfculling() - malloc\n"
	.align 8
.LC54:
	.string	"Could not allocate memory - bfculling() - realloc\n"
	.text
	.type	shadowcull, @function
shadowcull:
.LFB27:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -152(%rbp)
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, -128(%rbp)
	movq	%rdx, -120(%rbp)
	movq	32(%rbp), %rax
	movq	40(%rbp), %rdx
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	movq	48(%rbp), %rax
	movq	56(%rbp), %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	movq	64(%rbp), %rax
	movq	72(%rbp), %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movq	80(%rbp), %rax
	movq	88(%rbp), %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	96(%rbp), %rax
	movq	104(%rbp), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$1, -20(%rbp)
	movl	$0, -24(%rbp)
	movl	$160, %edi
	call	malloc@PLT
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	testq	%rax, %rax
	jne	.L120
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$49, %edx
	movl	$1, %esi
	leaq	.LC53(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
.L120:
	movl	$0, -28(%rbp)
	jmp	.L121
.L125:
	movq	16(%rbp), %rcx
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	subq	$160, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, 32(%rdx)
	movq	%rbx, 40(%rdx)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, 48(%rdx)
	movq	%rbx, 56(%rdx)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, 64(%rdx)
	movq	%rbx, 72(%rdx)
	movq	80(%rax), %rcx
	movq	88(%rax), %rbx
	movq	%rcx, 80(%rdx)
	movq	%rbx, 88(%rdx)
	movq	96(%rax), %rcx
	movq	104(%rax), %rbx
	movq	%rcx, 96(%rdx)
	movq	%rbx, 104(%rdx)
	movq	112(%rax), %rcx
	movq	120(%rax), %rbx
	movq	%rcx, 112(%rdx)
	movq	%rbx, 120(%rdx)
	movq	128(%rax), %rcx
	movq	136(%rax), %rbx
	movq	%rcx, 128(%rdx)
	movq	%rbx, 136(%rdx)
	movq	144(%rax), %rcx
	movq	152(%rax), %rbx
	movq	%rcx, 144(%rdx)
	movq	%rbx, 152(%rdx)
	call	winding3D@PLT
	addq	$160, %rsp
	movd	%xmm0, %eax
	movl	%eax, -32(%rbp)
	movss	-32(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L122
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-128(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	testq	%rax, %rax
	jne	.L124
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$50, %edx
	movl	$1, %esi
	leaq	.LC54(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
.L124:
	movq	16(%rbp), %rcx
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movq	-128(%rbp), %rsi
	movl	-24(%rbp), %eax
	movslq	%eax, %rcx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$5, %rax
	addq	%rsi, %rax
	movq	(%rdx), %rcx
	movq	8(%rdx), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16(%rdx), %rcx
	movq	24(%rdx), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32(%rdx), %rcx
	movq	40(%rdx), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48(%rdx), %rcx
	movq	56(%rdx), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	64(%rdx), %rcx
	movq	72(%rdx), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	80(%rdx), %rcx
	movq	88(%rdx), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	96(%rdx), %rcx
	movq	104(%rdx), %rbx
	movq	%rcx, 96(%rax)
	movq	%rbx, 104(%rax)
	movq	112(%rdx), %rcx
	movq	120(%rdx), %rbx
	movq	%rcx, 112(%rax)
	movq	%rbx, 120(%rax)
	movq	128(%rdx), %rcx
	movq	136(%rdx), %rbx
	movq	%rcx, 128(%rax)
	movq	%rbx, 136(%rax)
	movq	144(%rdx), %rcx
	movq	152(%rdx), %rbx
	movq	%rcx, 144(%rax)
	movq	%rbx, 152(%rax)
	addl	$1, -20(%rbp)
	addl	$1, -24(%rbp)
.L122:
	addl	$1, -28(%rbp)
.L121:
	movl	36(%rbp), %eax
	cmpl	%eax, -28(%rbp)
	jl	.L125
	movl	-24(%rbp), %eax
	movl	%eax, -108(%rbp)
	movq	16(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-152(%rbp), %rax
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-112(%rbp), %rcx
	movq	-104(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	-152(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	shadowcull, .-shadowcull
	.type	bfculling, @function
bfculling:
.LFB28:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -152(%rbp)
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, -128(%rbp)
	movq	%rdx, -120(%rbp)
	movq	32(%rbp), %rax
	movq	40(%rbp), %rdx
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	movq	48(%rbp), %rax
	movq	56(%rbp), %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	movq	64(%rbp), %rax
	movq	72(%rbp), %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movq	80(%rbp), %rax
	movq	88(%rbp), %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	96(%rbp), %rax
	movq	104(%rbp), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$1, -20(%rbp)
	movl	$0, -24(%rbp)
	movl	$160, %edi
	call	malloc@PLT
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	testq	%rax, %rax
	jne	.L129
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$49, %edx
	movl	$1, %esi
	leaq	.LC53(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
.L129:
	movl	$0, -28(%rbp)
	jmp	.L130
.L134:
	movq	16(%rbp), %rcx
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	subq	$160, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, 32(%rdx)
	movq	%rbx, 40(%rdx)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, 48(%rdx)
	movq	%rbx, 56(%rdx)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, 64(%rdx)
	movq	%rbx, 72(%rdx)
	movq	80(%rax), %rcx
	movq	88(%rax), %rbx
	movq	%rcx, 80(%rdx)
	movq	%rbx, 88(%rdx)
	movq	96(%rax), %rcx
	movq	104(%rax), %rbx
	movq	%rcx, 96(%rdx)
	movq	%rbx, 104(%rdx)
	movq	112(%rax), %rcx
	movq	120(%rax), %rbx
	movq	%rcx, 112(%rdx)
	movq	%rbx, 120(%rdx)
	movq	128(%rax), %rcx
	movq	136(%rax), %rbx
	movq	%rcx, 128(%rdx)
	movq	%rbx, 136(%rdx)
	movq	144(%rax), %rcx
	movq	152(%rax), %rbx
	movq	%rcx, 144(%rdx)
	movq	%rbx, 152(%rdx)
	call	winding3D@PLT
	addq	$160, %rsp
	movd	%xmm0, %eax
	movl	%eax, -32(%rbp)
	movss	-32(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L131
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-128(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	testq	%rax, %rax
	jne	.L133
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$50, %edx
	movl	$1, %esi
	leaq	.LC54(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
.L133:
	movq	16(%rbp), %rcx
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movq	-128(%rbp), %rsi
	movl	-24(%rbp), %eax
	movslq	%eax, %rcx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$5, %rax
	addq	%rsi, %rax
	movq	(%rdx), %rcx
	movq	8(%rdx), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16(%rdx), %rcx
	movq	24(%rdx), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32(%rdx), %rcx
	movq	40(%rdx), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48(%rdx), %rcx
	movq	56(%rdx), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	64(%rdx), %rcx
	movq	72(%rdx), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	80(%rdx), %rcx
	movq	88(%rdx), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	96(%rdx), %rcx
	movq	104(%rdx), %rbx
	movq	%rcx, 96(%rax)
	movq	%rbx, 104(%rax)
	movq	112(%rdx), %rcx
	movq	120(%rdx), %rbx
	movq	%rcx, 112(%rax)
	movq	%rbx, 120(%rax)
	movq	128(%rdx), %rcx
	movq	136(%rdx), %rbx
	movq	%rcx, 128(%rax)
	movq	%rbx, 136(%rax)
	movq	144(%rdx), %rcx
	movq	152(%rdx), %rbx
	movq	%rcx, 144(%rax)
	movq	%rbx, 152(%rax)
	addl	$1, -20(%rbp)
	addl	$1, -24(%rbp)
.L131:
	addl	$1, -28(%rbp)
.L130:
	movl	36(%rbp), %eax
	cmpl	%eax, -28(%rbp)
	jl	.L134
	movl	-24(%rbp), %eax
	movl	%eax, -108(%rbp)
	movq	16(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-152(%rbp), %rax
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-112(%rbp), %rcx
	movq	-104(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	-152(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	bfculling, .-bfculling
	.type	viewtoscreen, @function
viewtoscreen:
.LFB29:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$680, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -680(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L138
.L141:
	movl	$0, -24(%rbp)
	jmp	.L139
.L140:
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$24, %rax
	movss	(%rax), %xmm0
	movss	%xmm0, -28(%rbp)
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rax, %rdx
	addq	$12, %rdx
	movss	(%rdx), %xmm1
	movss	.LC19(%rip), %xmm0
	addss	%xmm1, %xmm0
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rax, %rdx
	addq	$12, %rdx
	movss	%xmm0, (%rdx)
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	addq	$12, %rax
	movss	(%rax), %xmm1
	movl	HALFW(%rip), %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	mulss	%xmm1, %xmm0
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$12, %rax
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rax, %rdx
	addq	$16, %rdx
	movss	(%rdx), %xmm1
	movss	.LC19(%rip), %xmm0
	addss	%xmm1, %xmm0
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rax, %rdx
	addq	$16, %rdx
	movss	%xmm0, (%rdx)
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	addq	$16, %rax
	movss	(%rax), %xmm1
	movl	HALFH(%rip), %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	mulss	%xmm1, %xmm0
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$16, %rax
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$20, %rax
	movss	(%rax), %xmm1
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movss	.LC48(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$20, %rax
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rdx
	movss	.LC19(%rip), %xmm0
	divss	-28(%rbp), %xmm0
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rdx, %rax
	addq	$24, %rax
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rax, %rcx
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	addq	$60, %rax
	movss	(%rax), %xmm0
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rax, %rcx
	divss	-28(%rbp), %xmm0
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	addq	$60, %rax
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rax, %rcx
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	addq	$64, %rax
	movss	(%rax), %xmm0
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rax, %rcx
	divss	-28(%rbp), %xmm0
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	addq	$64, %rax
	movss	%xmm0, (%rax)
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	leaq	(%rcx,%rax), %rsi
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rax, %rcx
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rsi, %rax
	addq	$24, %rax
	movss	(%rax), %xmm0
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	addq	$68, %rax
	movss	%xmm0, (%rax)
	addl	$1, -24(%rbp)
.L139:
	cmpl	$2, -24(%rbp)
	jle	.L140
	addl	$1, -20(%rbp)
.L138:
	movl	36(%rbp), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L141
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movss	FPlane(%rip), %xmm0
	movss	%xmm0, -40(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -56(%rbp)
	leaq	-160(%rbp), %rdx
	movq	-64(%rbp), %r9
	movq	-56(%rbp), %r8
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rdi
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	16(%rbp), %rcx
	movq	24(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	32(%rbp), %rcx
	movq	40(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	48(%rbp), %rcx
	movq	56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	64(%rbp), %rcx
	movq	72(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	80(%rbp), %rcx
	movq	88(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	96(%rbp), %rcx
	movq	104(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%r9, %xmm2
	movq	%r8, %xmm3
	movq	%rsi, %xmm0
	movq	%rdi, %xmm1
	movq	%rdx, %rdi
	call	clipp@PLT
	addq	$96, %rsp
	movq	$0, -176(%rbp)
	movq	$0, -168(%rbp)
	movl	8+wa(%rip), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC55(%rip), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -176(%rbp)
	movq	$0, -192(%rbp)
	movq	$0, -184(%rbp)
	movss	.LC37(%rip), %xmm0
	movss	%xmm0, -192(%rbp)
	leaq	-288(%rbp), %rdx
	movq	-192(%rbp), %r9
	movq	-184(%rbp), %r8
	movq	-176(%rbp), %rsi
	movq	-168(%rbp), %rdi
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-160(%rbp), %rcx
	movq	-152(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-112(%rbp), %rcx
	movq	-104(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%r9, %xmm2
	movq	%r8, %xmm3
	movq	%rsi, %xmm0
	movq	%rdi, %xmm1
	movq	%rdx, %rdi
	call	clipp@PLT
	addq	$96, %rsp
	movq	$0, -304(%rbp)
	movq	$0, -296(%rbp)
	movl	12+wa(%rip), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC55(%rip), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -300(%rbp)
	movq	$0, -320(%rbp)
	movq	$0, -312(%rbp)
	movss	.LC37(%rip), %xmm0
	movss	%xmm0, -316(%rbp)
	leaq	-416(%rbp), %rdx
	movq	-320(%rbp), %r9
	movq	-312(%rbp), %r8
	movq	-304(%rbp), %rsi
	movq	-296(%rbp), %rdi
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-288(%rbp), %rcx
	movq	-280(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-272(%rbp), %rcx
	movq	-264(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-256(%rbp), %rcx
	movq	-248(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-240(%rbp), %rcx
	movq	-232(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-224(%rbp), %rcx
	movq	-216(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-208(%rbp), %rcx
	movq	-200(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%r9, %xmm2
	movq	%r8, %xmm3
	movq	%rsi, %xmm0
	movq	%rdi, %xmm1
	movq	%rdx, %rdi
	call	clipp@PLT
	addq	$96, %rsp
	movq	$0, -432(%rbp)
	movq	$0, -424(%rbp)
	movq	$0, -448(%rbp)
	movq	$0, -440(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -448(%rbp)
	leaq	-544(%rbp), %rdx
	movq	-448(%rbp), %r9
	movq	-440(%rbp), %r8
	movq	-432(%rbp), %rsi
	movq	-424(%rbp), %rdi
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-416(%rbp), %rcx
	movq	-408(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-400(%rbp), %rcx
	movq	-392(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-384(%rbp), %rcx
	movq	-376(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-368(%rbp), %rcx
	movq	-360(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-352(%rbp), %rcx
	movq	-344(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-336(%rbp), %rcx
	movq	-328(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%r9, %xmm2
	movq	%r8, %xmm3
	movq	%rsi, %xmm0
	movq	%rdi, %xmm1
	movq	%rdx, %rdi
	call	clipp@PLT
	addq	$96, %rsp
	movq	$0, -560(%rbp)
	movq	$0, -552(%rbp)
	movq	$0, -576(%rbp)
	movq	$0, -568(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -572(%rbp)
	leaq	-672(%rbp), %rdx
	movq	-576(%rbp), %r9
	movq	-568(%rbp), %r8
	movq	-560(%rbp), %rsi
	movq	-552(%rbp), %rdi
	subq	$96, %rsp
	movq	%rsp, %rax
	movq	-544(%rbp), %rcx
	movq	-536(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-528(%rbp), %rcx
	movq	-520(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-512(%rbp), %rcx
	movq	-504(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-496(%rbp), %rcx
	movq	-488(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-480(%rbp), %rcx
	movq	-472(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-464(%rbp), %rcx
	movq	-456(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	%r9, %xmm2
	movq	%r8, %xmm3
	movq	%rsi, %xmm0
	movq	%rdi, %xmm1
	movq	%rdx, %rdi
	call	clipp@PLT
	addq	$96, %rsp
	movq	-680(%rbp), %rax
	movq	-672(%rbp), %rcx
	movq	-664(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-656(%rbp), %rcx
	movq	-648(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-640(%rbp), %rcx
	movq	-632(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-624(%rbp), %rcx
	movq	-616(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-608(%rbp), %rcx
	movq	-600(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-592(%rbp), %rcx
	movq	-584(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	-680(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE29:
	.size	viewtoscreen, .-viewtoscreen
	.type	rasterize, @function
rasterize:
.LFB30:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	92(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -24(%rbp)
	movl	96(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -28(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L144
.L148:
	movl	DEBUG(%rip), %eax
	cmpl	$1, %eax
	jne	.L145
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movss	32(%rax), %xmm2
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movss	28(%rax), %xmm1
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movss	16(%rax), %xmm0
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movl	12(%rax), %eax
	pxor	%xmm6, %xmm6
	pxor	%xmm5, %xmm5
	movss	.LC56(%rip), %xmm4
	movaps	%xmm2, %xmm3
	movaps	%xmm1, %xmm2
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	drawLine@PLT
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movss	48(%rax), %xmm2
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movss	44(%rax), %xmm1
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movss	32(%rax), %xmm0
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movl	28(%rax), %eax
	pxor	%xmm6, %xmm6
	pxor	%xmm5, %xmm5
	movss	.LC56(%rip), %xmm4
	movaps	%xmm2, %xmm3
	movaps	%xmm1, %xmm2
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	drawLine@PLT
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movss	16(%rax), %xmm2
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movss	12(%rax), %xmm1
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movss	48(%rax), %xmm0
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movl	44(%rax), %eax
	pxor	%xmm6, %xmm6
	pxor	%xmm5, %xmm5
	movss	.LC56(%rip), %xmm4
	movaps	%xmm2, %xmm3
	movaps	%xmm1, %xmm2
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	drawLine@PLT
	jmp	.L146
.L145:
	movl	DEBUG(%rip), %eax
	cmpl	$2, %eax
	jne	.L147
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	subq	$160, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, 32(%rdx)
	movq	%rbx, 40(%rdx)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, 48(%rdx)
	movq	%rbx, 56(%rdx)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, 64(%rdx)
	movq	%rbx, 72(%rdx)
	movq	80(%rax), %rcx
	movq	88(%rax), %rbx
	movq	%rcx, 80(%rdx)
	movq	%rbx, 88(%rdx)
	movq	96(%rax), %rcx
	movq	104(%rax), %rbx
	movq	%rcx, 96(%rdx)
	movq	%rbx, 104(%rdx)
	movq	112(%rax), %rcx
	movq	120(%rax), %rbx
	movq	%rcx, 112(%rdx)
	movq	%rbx, 120(%rdx)
	movq	128(%rax), %rcx
	movq	136(%rax), %rbx
	movq	%rcx, 128(%rdx)
	movq	%rbx, 136(%rdx)
	movq	144(%rax), %rcx
	movq	152(%rax), %rbx
	movq	%rcx, 144(%rdx)
	movq	%rbx, 152(%rdx)
	call	fillTriangle@PLT
	addq	$160, %rsp
	jmp	.L146
.L147:
	movq	104(%rbp), %rdi
	movq	16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movl	-28(%rbp), %r8d
	movl	-24(%rbp), %esi
	subq	$160, %rsp
	movq	%rsp, %rdx
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, 16(%rdx)
	movq	%rbx, 24(%rdx)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, 32(%rdx)
	movq	%rbx, 40(%rdx)
	movq	48(%rax), %rcx
	movq	56(%rax), %rbx
	movq	%rcx, 48(%rdx)
	movq	%rbx, 56(%rdx)
	movq	64(%rax), %rcx
	movq	72(%rax), %rbx
	movq	%rcx, 64(%rdx)
	movq	%rbx, 72(%rdx)
	movq	80(%rax), %rcx
	movq	88(%rax), %rbx
	movq	%rcx, 80(%rdx)
	movq	%rbx, 88(%rdx)
	movq	96(%rax), %rcx
	movq	104(%rax), %rbx
	movq	%rcx, 96(%rdx)
	movq	%rbx, 104(%rdx)
	movq	112(%rax), %rcx
	movq	120(%rax), %rbx
	movq	%rcx, 112(%rdx)
	movq	%rbx, 120(%rdx)
	movq	128(%rax), %rcx
	movq	136(%rax), %rbx
	movq	%rcx, 128(%rdx)
	movq	%rbx, 136(%rdx)
	movq	144(%rax), %rcx
	movq	152(%rax), %rbx
	movq	%rcx, 144(%rdx)
	movq	%rbx, 152(%rdx)
	movl	%r8d, %edx
	call	texTriangle@PLT
	addq	$160, %rsp
.L146:
	addl	$1, -20(%rbp)
.L144:
	movl	36(%rbp), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L148
	nop
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE30:
	.size	rasterize, .-rasterize
	.type	initLightModel, @function
initLightModel:
.LFB31:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -152(%rbp)
	leaq	-112(%rbp), %rdx
	movl	$0, %eax
	movl	$12, %ecx
	movq	%rdx, %rdi
	rep stosq
	movq	light(%rip), %rdx
	movq	8+light(%rip), %rsi
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	ViewMat(%rip), %rcx
	movq	8+ViewMat(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+ViewMat(%rip), %rcx
	movq	24+ViewMat(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+ViewMat(%rip), %rcx
	movq	40+ViewMat(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+ViewMat(%rip), %rcx
	movq	56+ViewMat(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %xmm0
	movq	%rsi, %xmm1
	call	vecxm@PLT
	addq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -112(%rbp)
	movq	%xmm0, -104(%rbp)
	movq	$0, -128(%rbp)
	movq	$0, -120(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -128(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -124(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -120(%rbp)
	movq	$0, -144(%rbp)
	movq	$0, -136(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -140(%rbp)
	movq	-128(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	movb	$32, -78(%rbp)
	movb	$121, -79(%rbp)
	movb	$-100, -80(%rbp)
	movss	.LC57(%rip), %xmm0
	movss	%xmm0, -60(%rbp)
	movss	-60(%rbp), %xmm0
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	movaps	%xmm0, %xmm2
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	call	multiply_vec@PLT
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -56(%rbp)
	movq	%xmm0, -48(%rbp)
	movss	.LC58(%rip), %xmm0
	movss	%xmm0, -40(%rbp)
	movss	-40(%rbp), %xmm0
	movq	-144(%rbp), %rax
	movq	-136(%rbp), %rdx
	movaps	%xmm0, %xmm2
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	call	multiply_vec@PLT
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -36(%rbp)
	movq	%xmm0, -28(%rbp)
	movq	-152(%rbp), %rax
	movq	-112(%rbp), %rcx
	movq	-104(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rbx
	movq	%rcx, 80(%rax)
	movq	%rbx, 88(%rax)
	movq	-152(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE31:
	.size	initLightModel, .-initLightModel
	.type	displayScene, @function
displayScene:
.LFB32:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	8+wa(%rip), %edx
	movl	12+wa(%rip), %eax
	imull	%edx, %eax
	sall	$2, %eax
	movl	%eax, -16(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L152
.L157:
	movl	PROJECTBUFFER(%rip), %eax
	cmpl	$1, %eax
	jg	.L153
	movq	pixels(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	addq	%rax, %rcx
	movq	frame_buffer(%rip), %rdx
	movl	-12(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	$3, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	jmp	.L154
.L153:
	movl	PROJECTBUFFER(%rip), %eax
	cmpl	$2, %eax
	jne	.L155
	movq	depth_buffer(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movq	frame_buffer(%rip), %rcx
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	jmp	.L154
.L155:
	movl	PROJECTBUFFER(%rip), %eax
	cmpl	$3, %eax
	jne	.L154
	movq	shadow_buffer(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movq	frame_buffer(%rip), %rcx
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
.L154:
	addl	$3, -12(%rbp)
	addl	$1, -8(%rbp)
	movl	8+wa(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jne	.L156
	addl	$1, -4(%rbp)
	movl	$0, -8(%rbp)
.L156:
	addl	$1, -12(%rbp)
.L152:
	movl	-12(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl	.L157
	movl	8+wa(%rip), %eax
	leal	0(,%rax,4), %edx
	movl	12+wa(%rip), %eax
	movl	%eax, %r9d
	movl	8+wa(%rip), %eax
	movl	%eax, %r8d
	movq	frame_buffer(%rip), %rcx
	movl	20+wa(%rip), %eax
	movl	%eax, %edi
	movq	24+wa(%rip), %rsi
	movq	displ(%rip), %rax
	pushq	%rdx
	pushq	$32
	pushq	%r9
	pushq	%r8
	movq	%rcx, %r9
	movl	$0, %r8d
	movl	$2, %ecx
	movl	%edi, %edx
	movq	%rax, %rdi
	call	XCreateImage@PLT
	addq	$32, %rsp
	movq	%rax, -24(%rbp)
	movl	12+wa(%rip), %eax
	movl	%eax, %r8d
	movl	8+wa(%rip), %eax
	movl	%eax, %edi
	movq	gc(%rip), %rdx
	movq	pixmap(%rip), %rsi
	movq	displ(%rip), %rax
	movq	-24(%rbp), %rcx
	pushq	%r8
	pushq	%rdi
	pushq	$0
	pushq	$0
	movl	$0, %r9d
	movl	$0, %r8d
	movq	%rax, %rdi
	call	XPutImage@PLT
	addq	$32, %rsp
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	call	pixmapdisplay
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE32:
	.size	displayScene, .-displayScene
	.type	clearBuffers, @function
clearBuffers:
.LFB33:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L159
.L160:
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rax, %rdx
	movq	pixels(%rip), %rax
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rax
	movq	(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movl	-24(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	depth_buffer(%rip), %rax
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rcx, %rax
	movq	(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	addl	$1, -4(%rbp)
.L159:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L160
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE33:
	.size	clearBuffers, .-clearBuffers
	.section	.rodata
.LC59:
	.string	"wb"
.LC60:
	.string	"textures/export.bmp"
	.text
	.globl	exportScene
	.type	exportScene, @function
exportScene:
.LFB34:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movw	$19778, -28(%rbp)
	movl	8+wa(%rip), %edx
	movl	12+wa(%rip), %eax
	imull	%edx, %eax
	sall	$2, %eax
	movl	%eax, -24(%rbp)
	movl	$54, -20(%rbp)
	pxor	%xmm0, %xmm0
	movaps	%xmm0, -64(%rbp)
	movaps	%xmm0, -48(%rbp)
	movd	%xmm0, -32(%rbp)
	movl	$40, -64(%rbp)
	movl	8+wa(%rip), %eax
	movl	%eax, -60(%rbp)
	movl	12+wa(%rip), %eax
	movl	%eax, -56(%rbp)
	movw	$1, -52(%rbp)
	movw	$32, -50(%rbp)
	leaq	.LC59(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC60(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	leaq	-28(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$12, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-16(%rbp), %rax
	movl	$0, %edx
	movl	$14, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-16(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$36, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	-64(%rbp), %eax
	addl	$14, %eax
	movl	%eax, %ecx
	movq	-16(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	12+wa(%rip), %eax
	subl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	.L162
.L165:
	movl	$0, -8(%rbp)
	jmp	.L163
.L164:
	movq	pixels(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	(%rcx,%rax), %rdi
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	movl	$1, %edx
	movl	$4, %esi
	call	fwrite@PLT
	addl	$1, -8(%rbp)
.L163:
	movl	8+wa(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L164
	subl	$1, -4(%rbp)
.L162:
	cmpl	$0, -4(%rbp)
	jns	.L165
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE34:
	.size	exportScene, .-exportScene
	.section	.rodata
.LC61:
	.string	"keypress() - XOpenIM()"
.LC62:
	.string	"clientWindow"
.LC63:
	.string	"inputStyle"
.LC64:
	.string	"keypress() - XreateIC()"
.LC65:
	.string	"Buffer Overflow...\n"
	.text
	.type	getKeysym, @function
getKeysym:
.LFB35:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -88(%rbp)
	movq	$0, -8(%rbp)
	movq	displ(%rip), %rax
	movl	$0, %ecx
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	XOpenIM@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L167
	leaq	.LC61(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
.L167:
	movq	$0, -16(%rbp)
	movq	win(%rip), %rdx
	movq	-8(%rbp), %rax
	movl	$0, %r9d
	movq	%rdx, %r8
	leaq	.LC62(%rip), %rdx
	movq	%rdx, %rcx
	movl	$1032, %edx
	leaq	.LC63(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	XCreateIC@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L168
	leaq	.LC64(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
.L168:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	XSetICFocus@PLT
	movq	$0, -24(%rbp)
	movl	$0, -68(%rbp)
	movq	-88(%rbp), %rsi
	leaq	-68(%rbp), %rdi
	leaq	-24(%rbp), %rcx
	leaq	-64(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdi, %r9
	movq	%rcx, %r8
	movl	$32, %ecx
	movq	%rax, %rdi
	call	Xutf8LookupString@PLT
	movl	-68(%rbp), %eax
	cmpl	$-1, %eax
	jne	.L169
	leaq	.LC65(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
.L169:
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE35:
	.size	getKeysym, .-getKeysym
	.type	initMainWindow, @function
initMainWindow:
.LFB36:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	$131077, 72+sa(%rip)
	movq	$0, 8+sa(%rip)
	movq	displ(%rip), %rax
	movq	%rax, %rdi
	call	XDefaultScreen@PLT
	movl	%eax, %edx
	movq	displ(%rip), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	XRootWindow@PLT
	movq	%rax, %rsi
	movq	displ(%rip), %rax
	leaq	sa(%rip), %rdx
	pushq	%rdx
	pushq	$2050
	pushq	$0
	pushq	$1
	pushq	$0
	pushq	$0
	movl	$800, %r9d
	movl	$800, %r8d
	movl	$0, %ecx
	movl	$0, %edx
	movq	%rax, %rdi
	call	XCreateWindow@PLT
	addq	$48, %rsp
	movq	%rax, win(%rip)
	movq	win(%rip), %rdx
	movq	displ(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	XMapWindow@PLT
	movq	win(%rip), %rcx
	movq	displ(%rip), %rax
	leaq	wa(%rip), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	XGetWindowAttributes@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE36:
	.size	initMainWindow, .-initMainWindow
	.type	initGlobalGC, @function
initGlobalGC:
.LFB37:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	$16777215, 16+gcvalues(%rip)
	movq	$0, 24+gcvalues(%rip)
	movl	$0, 100+gcvalues(%rip)
	movq	win(%rip), %rsi
	movq	displ(%rip), %rax
	leaq	gcvalues(%rip), %rdx
	movq	%rdx, %rcx
	movl	$65548, %edx
	movq	%rax, %rdi
	call	XCreateGC@PLT
	movq	%rax, gc(%rip)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE37:
	.size	initGlobalGC, .-initGlobalGC
	.type	initDependedVariables, @function
initDependedVariables:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movl	8+wa(%rip), %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movl	12+wa(%rip), %eax
	pxor	%xmm1, %xmm1
	cvtsi2ssl	%eax, %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, AspectRatio(%rip)
	movl	8+wa(%rip), %eax
	sarl	%eax
	movl	%eax, HALFW(%rip)
	movl	12+wa(%rip), %eax
	sarl	%eax
	movl	%eax, HALFH(%rip)
	movss	AspectRatio(%rip), %xmm0
	movl	FOV(%rip), %edx
	leaq	-80(%rbp), %rax
	movaps	%xmm0, %xmm1
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	perspective_mat@PLT
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, PerspMat(%rip)
	movq	%rdx, 8+PerspMat(%rip)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, 16+PerspMat(%rip)
	movq	%rdx, 24+PerspMat(%rip)
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, 32+PerspMat(%rip)
	movq	%rdx, 40+PerspMat(%rip)
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, 48+PerspMat(%rip)
	movq	%rdx, 56+PerspMat(%rip)
	movss	AspectRatio(%rip), %xmm0
	movl	FOV(%rip), %edx
	leaq	-80(%rbp), %rax
	movaps	%xmm0, %xmm1
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	reperspective_mat@PLT
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, rePerspMat(%rip)
	movq	%rdx, 8+rePerspMat(%rip)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, 16+rePerspMat(%rip)
	movq	%rdx, 24+rePerspMat(%rip)
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, 32+rePerspMat(%rip)
	movq	%rdx, 40+rePerspMat(%rip)
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, 48+rePerspMat(%rip)
	movq	%rdx, 56+rePerspMat(%rip)
	movss	Scale(%rip), %xmm0
	movl	Scale(%rip), %edx
	leaq	-80(%rbp), %rax
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	movaps	%xmm0, %xmm1
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	orthographic_mat@PLT
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, OrthoMat(%rip)
	movq	%rdx, 8+OrthoMat(%rip)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, 16+OrthoMat(%rip)
	movq	%rdx, 24+OrthoMat(%rip)
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, 32+OrthoMat(%rip)
	movq	%rdx, 40+OrthoMat(%rip)
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, 48+OrthoMat(%rip)
	movq	%rdx, 56+OrthoMat(%rip)
	leaq	-80(%rbp), %rax
	movq	48+camera(%rip), %r11
	movq	56+camera(%rip), %r10
	movq	32+camera(%rip), %r9
	movq	40+camera(%rip), %r8
	movq	16+camera(%rip), %rdi
	movq	24+camera(%rip), %rsi
	movq	camera(%rip), %rdx
	movq	8+camera(%rip), %rcx
	movq	%r11, %xmm6
	movq	%r10, %xmm7
	movq	%r9, %xmm4
	movq	%r8, %xmm5
	movq	%rdi, %xmm2
	movq	%rsi, %xmm3
	movq	%rdx, %xmm0
	movq	%rcx, %xmm1
	movq	%rax, %rdi
	call	lookat@PLT
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, LookAt(%rip)
	movq	%rdx, 8+LookAt(%rip)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, 16+LookAt(%rip)
	movq	%rdx, 24+LookAt(%rip)
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, 32+LookAt(%rip)
	movq	%rdx, 40+LookAt(%rip)
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, 48+LookAt(%rip)
	movq	%rdx, 56+LookAt(%rip)
	leaq	-80(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	LookAt(%rip), %rcx
	movq	8+LookAt(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+LookAt(%rip), %rcx
	movq	24+LookAt(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+LookAt(%rip), %rcx
	movq	40+LookAt(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+LookAt(%rip), %rcx
	movq	56+LookAt(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	inverse_mat@PLT
	addq	$64, %rsp
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, ViewMat(%rip)
	movq	%rdx, 8+ViewMat(%rip)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, 16+ViewMat(%rip)
	movq	%rdx, 24+ViewMat(%rip)
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, 32+ViewMat(%rip)
	movq	%rdx, 40+ViewMat(%rip)
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, 48+ViewMat(%rip)
	movq	%rdx, 56+ViewMat(%rip)
	leaq	-80(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	PerspMat(%rip), %rcx
	movq	8+PerspMat(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+PerspMat(%rip), %rcx
	movq	24+PerspMat(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+PerspMat(%rip), %rcx
	movq	40+PerspMat(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+PerspMat(%rip), %rcx
	movq	56+PerspMat(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	ViewMat(%rip), %rcx
	movq	8+ViewMat(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+ViewMat(%rip), %rcx
	movq	24+ViewMat(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+ViewMat(%rip), %rcx
	movq	40+ViewMat(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+ViewMat(%rip), %rcx
	movq	56+ViewMat(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	mxm@PLT
	subq	$-128, %rsp
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, WorldMat(%rip)
	movq	%rdx, 8+WorldMat(%rip)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, 16+WorldMat(%rip)
	movq	%rdx, 24+WorldMat(%rip)
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, 32+WorldMat(%rip)
	movq	%rdx, 40+WorldMat(%rip)
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, 48+WorldMat(%rip)
	movq	%rdx, 56+WorldMat(%rip)
	movl	$1, AdjustShadow(%rip)
	movl	$1, AdjustScene(%rip)
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE38:
	.size	initDependedVariables, .-initDependedVariables
	.type	pixmapcreate, @function
pixmapcreate:
.LFB39:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	20+wa(%rip), %eax
	movl	%eax, %edi
	movl	12+wa(%rip), %eax
	movl	%eax, %ecx
	movl	8+wa(%rip), %eax
	movl	%eax, %edx
	movq	win(%rip), %rsi
	movq	displ(%rip), %rax
	movl	%edi, %r8d
	movq	%rax, %rdi
	call	XCreatePixmap@PLT
	movq	%rax, pixmap(%rip)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE39:
	.size	pixmapcreate, .-pixmapcreate
	.type	pixmapdisplay, @function
pixmapdisplay:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	12+wa(%rip), %eax
	movl	%eax, %r8d
	movl	8+wa(%rip), %eax
	movl	%eax, %edi
	movq	gc(%rip), %rcx
	movq	win(%rip), %rdx
	movq	pixmap(%rip), %rsi
	movq	displ(%rip), %rax
	pushq	$0
	pushq	$0
	pushq	%r8
	pushq	%rdi
	movl	$0, %r9d
	movl	$0, %r8d
	movq	%rax, %rdi
	call	XCopyArea@PLT
	addq	$32, %rsp
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE40:
	.size	pixmapdisplay, .-pixmapdisplay
	.section	.rodata
.LC66:
	.string	"WM_NAME"
.LC67:
	.string	"STRING"
.LC68:
	.string	"Anvil"
	.text
	.type	atomsinit, @function
atomsinit:
.LFB41:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	displ(%rip), %rax
	movl	$0, %edx
	leaq	.LC1(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	XInternAtom@PLT
	movq	%rax, wmatom(%rip)
	movq	win(%rip), %rsi
	movq	displ(%rip), %rax
	movl	$1, %ecx
	leaq	wmatom(%rip), %rdx
	movq	%rax, %rdi
	call	XSetWMProtocols@PLT
	movq	displ(%rip), %rax
	movl	$0, %edx
	leaq	.LC66(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	XInternAtom@PLT
	movq	%rax, 8+wmatom(%rip)
	movq	displ(%rip), %rax
	movl	$0, %edx
	leaq	.LC67(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	XInternAtom@PLT
	movq	%rax, 16+wmatom(%rip)
	movq	16+wmatom(%rip), %rcx
	movq	8+wmatom(%rip), %rdx
	movq	win(%rip), %rsi
	movq	displ(%rip), %rax
	pushq	$5
	leaq	.LC68(%rip), %rdi
	pushq	%rdi
	movl	$0, %r9d
	movl	$8, %r8d
	movq	%rax, %rdi
	call	XChangeProperty@PLT
	addq	$16, %rsp
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE41:
	.size	atomsinit, .-atomsinit
	.section	.rodata
	.align 8
.LC69:
	.string	"Received Signal from OS with ID: %d\n"
	.text
	.type	sigsegv_handler, @function
sigsegv_handler:
.LFB42:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movl	%edi, -196(%rbp)
	movl	-196(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC69(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-192(%rbp), %rdx
	movl	$0, %eax
	movl	$24, %ecx
	movq	%rdx, %rdi
	rep stosq
	movl	$33, -192(%rbp)
	movq	wmatom(%rip), %rax
	movq	%rax, -136(%rbp)
	movl	-192(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	handler(%rip), %rax
	movq	(%rdx,%rax), %rdx
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	*%rdx
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE42:
	.size	sigsegv_handler, .-sigsegv_handler
	.section	.rodata
	.align 8
.LC70:
	.string	"Warning: board() -- sigaction()\n"
	.text
	.type	registerSig, @function
registerSig:
.LFB43:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	movl	%edi, -164(%rbp)
	leaq	-160(%rbp), %rdx
	movl	$0, %eax
	movl	$19, %ecx
	movq	%rdx, %rdi
	rep stosq
	leaq	sigsegv_handler(%rip), %rax
	movq	%rax, -160(%rbp)
	leaq	-160(%rbp), %rcx
	movl	-164(%rbp), %eax
	movl	$0, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	sigaction@PLT
	movl	%eax, -4(%rbp)
	cmpl	$-1, -4(%rbp)
	jne	.L179
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$32, %edx
	movl	$1, %esi
	leaq	.LC70(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$1, %eax
	jmp	.L181
.L179:
	movl	$0, %eax
.L181:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE43:
	.size	registerSig, .-registerSig
	.globl	executeTask
	.type	executeTask, @function
executeTask:
.LFB44:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movss	20(%rax), %xmm3
	movq	-8(%rbp), %rax
	movss	16(%rax), %xmm2
	movq	-8(%rbp), %rax
	movss	12(%rax), %xmm1
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rcx
	movq	32(%rax), %rax
	movaps	%xmm3, %xmm5
	movaps	%xmm2, %xmm4
	movaps	%xmm1, %xmm3
	movaps	%xmm0, %xmm2
	movq	%rcx, %xmm0
	movq	%rax, %xmm1
	call	*%rdx
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE44:
	.size	executeTask, .-executeTask
	.globl	startThread
	.type	startThread, @function
startThread:
.LFB45:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
.L188:
	leaq	mutexQueue(%rip), %rax
	movq	%rax, %rdi
	call	pthread_mutex_lock@PLT
	jmp	.L184
.L185:
	leaq	mutexQueue(%rip), %rax
	movq	%rax, %rsi
	leaq	condQueue(%rip), %rax
	movq	%rax, %rdi
	call	pthread_cond_wait@PLT
.L184:
	movl	TASKCOUNT(%rip), %eax
	testl	%eax, %eax
	je	.L185
	movq	TaskQueue(%rip), %rax
	movq	8+TaskQueue(%rip), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	16+TaskQueue(%rip), %rax
	movq	24+TaskQueue(%rip), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	32+TaskQueue(%rip), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L186
.L187:
	movl	-4(%rbp), %eax
	leal	1(%rax), %esi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rcx
	leaq	TaskQueue(%rip), %rdx
	movslq	%esi, %rsi
	movq	%rsi, %rax
	salq	$2, %rax
	addq	%rsi, %rax
	salq	$3, %rax
	movq	%rax, %rsi
	leaq	TaskQueue(%rip), %rax
	movq	(%rsi,%rax), %r8
	movq	8(%rsi,%rax), %r9
	movq	%r8, (%rcx,%rdx)
	movq	%r9, 8(%rcx,%rdx)
	movq	16(%rsi,%rax), %r8
	movq	24(%rsi,%rax), %r9
	movq	%r8, 16(%rcx,%rdx)
	movq	%r9, 24(%rcx,%rdx)
	movq	32(%rsi,%rax), %rax
	movq	%rax, 32(%rcx,%rdx)
	addl	$1, -4(%rbp)
.L186:
	movl	TASKCOUNT(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L187
	movl	TASKCOUNT(%rip), %eax
	subl	$1, %eax
	movl	%eax, TASKCOUNT(%rip)
	leaq	mutexQueue(%rip), %rax
	movq	%rax, %rdi
	call	pthread_mutex_unlock@PLT
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	executeTask
	jmp	.L188
	.cfi_endproc
.LFE45:
	.size	startThread, .-startThread
	.globl	submitTask
	.type	submitTask, @function
submitTask:
.LFB46:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$8, %rsp
	.cfi_offset 3, -24
	leaq	mutexQueue(%rip), %rax
	movq	%rax, %rdi
	call	pthread_mutex_lock@PLT
	movl	TASKCOUNT(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	TaskQueue(%rip), %rax
	movq	16(%rbp), %rcx
	movq	24(%rbp), %rbx
	movq	%rcx, (%rdx,%rax)
	movq	%rbx, 8(%rdx,%rax)
	movq	32(%rbp), %rcx
	movq	40(%rbp), %rbx
	movq	%rcx, 16(%rdx,%rax)
	movq	%rbx, 24(%rdx,%rax)
	movq	48(%rbp), %rcx
	movq	%rcx, 32(%rdx,%rax)
	movl	TASKCOUNT(%rip), %eax
	addl	$1, %eax
	movl	%eax, TASKCOUNT(%rip)
	leaq	mutexQueue(%rip), %rax
	movq	%rax, %rdi
	call	pthread_mutex_unlock@PLT
	leaq	condQueue(%rip), %rax
	movq	%rax, %rdi
	call	pthread_cond_signal@PLT
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE46:
	.size	submitTask, .-submitTask
	.section	.rodata
	.align 8
.LC71:
	.string	"a: %f,    b: %f,    c: %f,    d: %f\n"
	.text
	.globl	printTask
	.type	printTask, @function
printTask:
.LFB47:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%xmm0, %rdx
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	movss	%xmm2, -20(%rbp)
	movss	%xmm3, -24(%rbp)
	movss	%xmm4, -28(%rbp)
	movss	%xmm5, -32(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	call	logVector@PLT
	pxor	%xmm2, %xmm2
	cvtss2sd	-32(%rbp), %xmm2
	pxor	%xmm1, %xmm1
	cvtss2sd	-28(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	cvtss2sd	-24(%rbp), %xmm0
	pxor	%xmm6, %xmm6
	cvtss2sd	-20(%rbp), %xmm6
	movq	%xmm6, %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC71(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE47:
	.size	printTask, .-printTask
	.section	.rodata
	.align 8
.LC72:
	.string	"Warning: board() -- XInitThreads()\n"
	.align 8
.LC73:
	.string	"Warning: board() -- XOpenDisplay()\n"
	.text
	.type	board, @function
board:
.LFB48:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$320, %rsp
	movq	%rdi, -216(%rbp)
	call	XInitThreads@PLT
	testl	%eax, %eax
	jne	.L192
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$35, %edx
	movl	$1, %esi
	leaq	.LC72(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
.L192:
	movl	$0, %edi
	call	XOpenDisplay@PLT
	movq	%rax, displ(%rip)
	movq	displ(%rip), %rax
	testq	%rax, %rax
	jne	.L193
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$35, %edx
	movl	$1, %esi
	leaq	.LC73(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
.L193:
	call	initMainWindow
	call	initGlobalGC
	call	pixmapcreate
	call	atomsinit
	movl	$11, %edi
	call	registerSig
	call	initDependedVariables
	call	initBuffers
	leaq	scene(%rip), %rax
	movq	%rax, %rdi
	call	createScene
	leaq	scene(%rip), %rax
	movq	%rax, %rdi
	call	initMeshes
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	initLightModel
	movq	-320(%rbp), %rax
	movq	-312(%rbp), %rdx
	movq	%rax, model(%rip)
	movq	%rdx, 8+model(%rip)
	movq	-304(%rbp), %rax
	movq	-296(%rbp), %rdx
	movq	%rax, 16+model(%rip)
	movq	%rdx, 24+model(%rip)
	movq	-288(%rbp), %rax
	movq	-280(%rbp), %rdx
	movq	%rax, 32+model(%rip)
	movq	%rdx, 40+model(%rip)
	movq	-272(%rbp), %rax
	movq	-264(%rbp), %rdx
	movq	%rax, 48+model(%rip)
	movq	%rdx, 56+model(%rip)
	movq	-256(%rbp), %rax
	movq	-248(%rbp), %rdx
	movq	%rax, 64+model(%rip)
	movq	%rdx, 72+model(%rip)
	movq	-240(%rbp), %rax
	movq	-232(%rbp), %rdx
	movq	%rax, 80+model(%rip)
	movq	%rdx, 88+model(%rip)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	jmp	.L194
.L197:
	call	start@PLT
	movq	%rax, -16(%rbp)
	movq	scene(%rip), %rdx
	movq	8+scene(%rip), %rax
	movq	%rdx, %rdi
	movq	%rax, %rsi
	call	project
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	end@PLT
	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	jmp	.L195
.L196:
	movq	displ(%rip), %rax
	leaq	-208(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	XNextEvent@PLT
	movl	-208(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	handler(%rip), %rax
	movq	(%rdx,%rax), %rax
	testq	%rax, %rax
	je	.L195
	movl	-208(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	handler(%rip), %rax
	movq	(%rdx,%rax), %rdx
	leaq	-208(%rbp), %rax
	movq	%rax, %rdi
	call	*%rdx
.L195:
	movq	displ(%rip), %rax
	movq	%rax, %rdi
	call	XPending@PLT
	testl	%eax, %eax
	jne	.L196
	movss	-4(%rbp), %xmm1
	movss	.LC74(%rip), %xmm0
	mulss	%xmm0, %xmm1
	movss	.LC75(%rip), %xmm0
	subss	%xmm1, %xmm0
	cvttss2siq	%xmm0, %rax
	movl	%eax, %edi
	call	usleep@PLT
.L194:
	movl	RUNNING(%rip), %eax
	testl	%eax, %eax
	jne	.L197
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE48:
	.size	board, .-board
	.section	.rodata
.LC76:
	.string	"Warning: main() -locale()\n"
.LC77:
	.string	"argc: %d\n"
.LC78:
	.string	"Debug"
.LC79:
	.string	"1"
.LC80:
	.string	"INFO : ENABLED DEBUG Level 1\n"
.LC81:
	.string	"2"
.LC82:
	.string	"INFO : ENABLED DEBUG Level 2\n"
	.align 8
.LC83:
	.string	"Failed to create thread [ %d ]\n"
.LC84:
	.string	"Failed to join thread [ %d ]\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB49:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	call	locale_init@PLT
	testl	%eax, %eax
	je	.L199
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$26, %edx
	movl	$1, %esi
	leaq	.LC76(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
.L199:
	cmpl	$1, -20(%rbp)
	jle	.L200
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC77(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	leaq	.LC78(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcasecmp@PLT
	testl	%eax, %eax
	jne	.L200
	movq	-32(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	leaq	.LC79(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcasecmp@PLT
	testl	%eax, %eax
	jne	.L201
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$29, %edx
	movl	$1, %esi
	leaq	.LC80(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$1, DEBUG(%rip)
	jmp	.L200
.L201:
	movq	-32(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	leaq	.LC81(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcasecmp@PLT
	testl	%eax, %eax
	jne	.L200
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$29, %edx
	movl	$1, %esi
	leaq	.LC82(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$2, DEBUG(%rip)
.L200:
	movl	$0, %esi
	leaq	mutexQueue(%rip), %rax
	movq	%rax, %rdi
	call	pthread_mutex_init@PLT
	movl	$0, %esi
	leaq	condQueue(%rip), %rax
	movq	%rax, %rdi
	call	pthread_cond_init@PLT
	movl	$0, -4(%rbp)
	jmp	.L202
.L204:
	cmpl	$0, -4(%rbp)
	jne	.L203
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	threads(%rip), %rax
	addq	%rdx, %rax
	movl	$0, %ecx
	leaq	board(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	testl	%eax, %eax
	jne	.L203
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	threads(%rip), %rax
	addq	%rdx, %rax
	movl	$0, %ecx
	leaq	startThread(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	testl	%eax, %eax
	je	.L203
	movq	stderr(%rip), %rax
	movl	-4(%rbp), %edx
	leaq	.LC83(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
.L203:
	addl	$1, -4(%rbp)
.L202:
	cmpl	$3, -4(%rbp)
	jle	.L204
	movl	$0, -8(%rbp)
	jmp	.L205
.L207:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	threads(%rip), %rax
	movq	(%rdx,%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	testl	%eax, %eax
	je	.L206
	movq	stderr(%rip), %rax
	movl	-8(%rbp), %edx
	leaq	.LC84(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
.L206:
	addl	$1, -8(%rbp)
.L205:
	cmpl	$3, -8(%rbp)
	jle	.L207
	leaq	mutexQueue(%rip), %rax
	movq	%rax, %rdi
	call	pthread_mutex_destroy@PLT
	leaq	condQueue(%rip), %rax
	movq	%rax, %rdi
	call	pthread_cond_destroy@PLT
	movq	displ(%rip), %rax
	movq	%rax, %rdi
	call	XCloseDisplay@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE49:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC85:
	.string	"World Space:  r.x: %f,   r.y: %f,    r.z: %f,    r.w: %f\n"
	.align 8
.LC86:
	.string	"Camera Space: r.x: %f,   r.y: %f,    r.z: %f,    r.w: %f\n"
	.align 8
.LC87:
	.string	"Perspec Clipp Space: r.x: %f,   r.y: %f,    r.z: %f,    r.w: %f\n"
	.align 8
.LC88:
	.string	"NDC Space:    r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n"
	.align 8
.LC89:
	.string	"Screen Space: r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n"
	.align 8
.LC90:
	.string	"To NDC:       r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n"
	.align 8
.LC91:
	.string	"To Clipp:    r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n"
	.align 8
.LC92:
	.string	"To Camera:   r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n"
	.align 8
.LC93:
	.string	"To World:   r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n"
	.text
	.type	rerasterize, @function
rerasterize:
.LFB50:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$296, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -296(%rbp)
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	movq	32(%rbp), %rax
	movq	40(%rbp), %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movq	48(%rbp), %rax
	movq	56(%rbp), %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	64(%rbp), %rax
	movq	72(%rbp), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	80(%rbp), %rax
	movq	88(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movss	-84(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-96(%rbp), %xmm3
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm3, %xmm4
	movq	%xmm4, %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC85(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
	leaq	-160(%rbp), %rdx
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	LookAt(%rip), %rcx
	movq	8+LookAt(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+LookAt(%rip), %rcx
	movq	24+LookAt(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+LookAt(%rip), %rcx
	movq	40+LookAt(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+LookAt(%rip), %rcx
	movq	56+LookAt(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %rdi
	call	inverse_mat@PLT
	addq	$64, %rsp
	movq	-96(%rbp), %rdx
	movq	-88(%rbp), %rsi
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-160(%rbp), %rcx
	movq	-152(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-144(%rbp), %rcx
	movq	-136(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-128(%rbp), %rcx
	movq	-120(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-112(%rbp), %rcx
	movq	-104(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %xmm0
	movq	%rsi, %xmm1
	call	vecxm@PLT
	addq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -96(%rbp)
	movq	%xmm0, -88(%rbp)
	movss	-84(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-96(%rbp), %xmm3
	pxor	%xmm5, %xmm5
	cvtss2sd	%xmm3, %xmm5
	movq	%xmm5, %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC86(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
	movss	AspectRatio(%rip), %xmm0
	movl	FOV(%rip), %edx
	leaq	-224(%rbp), %rax
	movaps	%xmm0, %xmm1
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	perspective_mat@PLT
	movq	-96(%rbp), %rdx
	movq	-88(%rbp), %rsi
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-224(%rbp), %rcx
	movq	-216(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-208(%rbp), %rcx
	movq	-200(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-192(%rbp), %rcx
	movq	-184(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-176(%rbp), %rcx
	movq	-168(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %xmm0
	movq	%rsi, %xmm1
	call	vecxm@PLT
	addq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -96(%rbp)
	movq	%xmm0, -88(%rbp)
	movss	-84(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-96(%rbp), %xmm3
	pxor	%xmm6, %xmm6
	cvtss2sd	%xmm3, %xmm6
	movq	%xmm6, %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC87(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
	movss	-84(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L210
	movss	-96(%rbp), %xmm0
	movss	-84(%rbp), %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, -96(%rbp)
	movss	-92(%rbp), %xmm0
	movss	-84(%rbp), %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, -92(%rbp)
	movss	-88(%rbp), %xmm0
	movss	-84(%rbp), %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, -88(%rbp)
.L210:
	movss	-84(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-96(%rbp), %xmm3
	pxor	%xmm7, %xmm7
	cvtss2sd	%xmm3, %xmm7
	movq	%xmm7, %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC88(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
	movss	-96(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC55(%rip), %xmm0
	addsd	%xmm0, %xmm1
	movl	HALFW(%rip), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	mulsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -96(%rbp)
	movss	-92(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC55(%rip), %xmm0
	addsd	%xmm0, %xmm1
	movl	HALFH(%rip), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	mulsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -92(%rbp)
	movss	-84(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-96(%rbp), %xmm3
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm3, %xmm4
	movq	%xmm4, %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC89(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
	movss	-96(%rbp), %xmm0
	movl	HALFW(%rip), %eax
	pxor	%xmm1, %xmm1
	cvtsi2ssl	%eax, %xmm1
	divss	%xmm1, %xmm0
	movss	.LC19(%rip), %xmm1
	subss	%xmm1, %xmm0
	movss	%xmm0, -96(%rbp)
	movss	-92(%rbp), %xmm0
	movl	HALFH(%rip), %eax
	pxor	%xmm1, %xmm1
	cvtsi2ssl	%eax, %xmm1
	divss	%xmm1, %xmm0
	movss	.LC19(%rip), %xmm1
	subss	%xmm1, %xmm0
	movss	%xmm0, -92(%rbp)
	movss	-84(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-96(%rbp), %xmm3
	pxor	%xmm5, %xmm5
	cvtss2sd	%xmm3, %xmm5
	movq	%xmm5, %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC90(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
	movss	-84(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L212
	movss	-96(%rbp), %xmm1
	movss	-84(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -96(%rbp)
	movss	-92(%rbp), %xmm1
	movss	-84(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -92(%rbp)
	movss	-88(%rbp), %xmm1
	movss	-84(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -88(%rbp)
.L212:
	movss	-84(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-96(%rbp), %xmm3
	pxor	%xmm6, %xmm6
	cvtss2sd	%xmm3, %xmm6
	movq	%xmm6, %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC91(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
	movss	AspectRatio(%rip), %xmm0
	movl	FOV(%rip), %edx
	leaq	-288(%rbp), %rax
	movaps	%xmm0, %xmm1
	movd	%edx, %xmm0
	movq	%rax, %rdi
	call	reperspective_mat@PLT
	movq	-96(%rbp), %rdx
	movq	-88(%rbp), %rsi
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	-288(%rbp), %rcx
	movq	-280(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-272(%rbp), %rcx
	movq	-264(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-256(%rbp), %rcx
	movq	-248(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-240(%rbp), %rcx
	movq	-232(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %xmm0
	movq	%rsi, %xmm1
	call	vecxm@PLT
	addq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -96(%rbp)
	movq	%xmm0, -88(%rbp)
	movss	.LC19(%rip), %xmm0
	movss	%xmm0, -84(%rbp)
	movss	-84(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-96(%rbp), %xmm3
	pxor	%xmm7, %xmm7
	cvtss2sd	%xmm3, %xmm7
	movq	%xmm7, %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC92(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
	movq	-96(%rbp), %rdx
	movq	-88(%rbp), %rsi
	subq	$64, %rsp
	movq	%rsp, %rax
	movq	LookAt(%rip), %rcx
	movq	8+LookAt(%rip), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	16+LookAt(%rip), %rcx
	movq	24+LookAt(%rip), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	32+LookAt(%rip), %rcx
	movq	40+LookAt(%rip), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	48+LookAt(%rip), %rcx
	movq	56+LookAt(%rip), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	%rdx, %xmm0
	movq	%rsi, %xmm1
	call	vecxm@PLT
	addq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -96(%rbp)
	movq	%xmm0, -88(%rbp)
	movss	-84(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movss	-88(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-96(%rbp), %xmm3
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm3, %xmm4
	movq	%xmm4, %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC93(%rip), %rax
	movq	%rax, %rdi
	movl	$4, %eax
	call	printf@PLT
	movq	-296(%rbp), %rax
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rbx
	movq	%rcx, 64(%rax)
	movq	%rbx, 72(%rax)
	movq	-296(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE50:
	.size	rerasterize, .-rerasterize
	.section	.rodata
	.align 8
.LC16:
	.long	0
	.long	1081671680
	.align 4
.LC19:
	.long	1065353216
	.align 4
.LC20:
	.long	1073741824
	.align 4
.LC21:
	.long	1077936128
	.align 4
.LC22:
	.long	1082130432
	.align 4
.LC25:
	.long	0
	.align 8
.LC29:
	.long	-1998362383
	.long	1055193269
	.align 8
.LC31:
	.long	-350469331
	.long	1058682594
	.align 8
.LC33:
	.long	1202590843
	.long	1065646817
	.align 8
.LC35:
	.long	858993459
	.long	1076114227
	.align 4
.LC37:
	.long	-1082130432
	.align 4
.LC38:
	.long	1140785152
	.align 4
.LC39:
	.long	1140391936
	.align 4
.LC42:
	.long	1092616192
	.align 4
.LC43:
	.long	1140457472
	.align 4
.LC45:
	.long	1141964800
	.align 4
.LC46:
	.long	-1054867456
	.align 4
.LC48:
	.long	1056964608
	.align 8
.LC55:
	.long	0
	.long	1072693248
	.align 4
.LC56:
	.long	1132396544
	.align 4
.LC57:
	.long	1036831949
	.align 4
.LC58:
	.long	1061158912
	.align 4
.LC74:
	.long	1148846080
	.align 4
.LC75:
	.long	1182938624
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
