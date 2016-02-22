.text
.align 4
foo:                    @   Os unicos argumentos usados são:
@                           int b   em r1
@                           int f   em [sp, #4]
stmda sp! {r4, r5, fp, lr}
add fp, #(4<<2)
mov r0, sp      @ r0 = &x
sub sp, sp, #4  @ Aloca x
mov r4, r1      @ Salva o  b em r4
ldr r5, [r0]    @ Carrega  x em r5
ldr r1, =y      @ Carrega &y em r1
ldr r1, [r1]    @ Carrega  y em r1

bl bar          @ Chama funcao bar

add r0, r4, r5  @ Guarda x + b em r0
ldr r4, [sp, #8]
add r0, r4      @ Acumula f em r0


ldmib sp! {r4, r5, fp, pc}

bar:

.data
y:
    .word   2
