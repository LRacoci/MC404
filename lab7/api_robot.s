@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@  Nome: Lucas Alves Racoci
@  RA: 156331
@ 
@ 2 syscalls serao utilizadas para controlar o robo:
@   write_motors  (syscall de numero 124)
@                 Parametros:
@                       r0 : velocidade para o motor 0  (valor de 6 bits)
@                       r1 : velocidade para o motor 1  (valor de 6 bits)
@
@  read_sonar (syscall de numero 125)
@                 Parametros:
@                       r0 : identificador do sonar   (valor de 4 bits)
@                 Retorno:
@                       r0 : distancia capturada pelo sonar consultado (valor de 12 bits)
@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	@ Global symbol
		.global set_speed_motor
		.global set_speed_motors
		.global read_sonar
		.global read_sonars

	.align 4

set_speed_motor: 	@ unsigned char (r0) speed, unsigned char (r1) id
		stmfd sp!, {r7, lr}	@ Save the callee-save registers
								@ and the return address.
		
		cmp 	r1, 	#1
		moveq 	r7, 	#127
		movne 	r7, 	#126
		svc 0x0


		ldmfd sp!, {r7, pc} @ Restore the registers and return

set_speed_motors:
		stmfd sp!, {r7, lr}	@ Save the callee-save registers
							@ and the return address.
	mov 	r7, 	#124
	svc 	0x0

		ldmfd sp!, {r7, pc} @ Restore the registers and return

read_sonar: @ unsigned char (r0) sonar_id
		stmfd sp!, {r7, lr}	@ Save the callee-save registers
							@ and the return address.

	mov 	r7, 	#125
	svc 	0x0

		ldmfd sp!, {r7, pc} @ Restore the registers and return

read_sonars: @ unsigned char (r0) sonar_id
		stmfd sp!, {lr}	@ Save the callee-save registers
								@ and the return address.
	mov r1, r0

	@ Inicialização
			mov r2, #0 
	for:
			cmp r2, #16
			bhs end_for
		@ Corpo
		mov r0, r2

			stmfd sp!, {r1-r2}
		bl read_sonar
			ldmfd sp!, {r1-r2}

		str r0, [r1]
		add r1, r1, #4

		@ Passo
			add r2, r2, #1
			b for
	end_for:


		ldmfd sp!, {pc} @ Restore the registers and return


